#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <vector>
#include "Vocabulary.h"

using namespace std;

int main()
{
	//output statement for user input for all the files
	cout << "Enter all file names for comparison separated by spaces: ";
	string fileName;
	getline(cin, fileName);
	//use stringstream INPUT
	stringstream iss(fileName);

	//create a new string of files and a vector that stores all of the files being inputted by the user
	string files;

	vector<VocabWrapper> inputFiles;
	//Use while loop for input string stream for all files
	while (iss >> files) 
	{
		//Add all the files to the vector
		inputFiles.push_back(VocabWrapper (files));
	}
	//Create a vector for the similarity numbers
	vector<double>vectorOfSimilarities;

	//Use a for loop for all of the input files that have been inputted by the user
	for (auto i = inputFiles.begin(); i != inputFiles.end(); ++i)
	{
		//Once this loop gets to the last file, end it
		if (i == inputFiles.end())
		{
			break;
		}
		//Another for loop to iterate through all of the file, using i and j interators and storing them as their own VocabWrapper class types
		for (auto j = i + 1; j != inputFiles.end(); ++j)
		{
			VocabWrapper first = *i;
			VocabWrapper second = *j;
			//Call the similarity function with pointers to the interators which are the classes
			double current = similarity(*i, *j);
			//Store all of the similarity numbers into the vector 
			vectorOfSimilarities.push_back(current);
			//Cout statement will appear ever time a file is compared until it is complete
			cout << "Comparison of " << first.get_filename() << " and " << second.get_filename() << ": " << similarity(first, second) << '\n';
		}
	}

	//Now store the number of files inputted by the user into an int
	long long int numberFiles = inputFiles.size();
	//OUtput string string sout
	ostringstream sout;
	//Number of files goes here, then create a newFile string that stores the number of files as a string
	//to be used in the new file name
	sout << numberFiles;
	string newFile = sout.str();
	ofstream outfile;// declaration of file pointer named outfile
	outfile.open("Results_Compare_" + newFile + ".txt"); // opens file for output
	//Copy the above loop to place the output into the file. 
	//The only thing different here is that now we are using outfile operator instead of cout
	//to store the data into the file
	for (auto i = inputFiles.begin(); i != inputFiles.end(); ++i)
	{
		if (i == inputFiles.end())
		{
			break;
		}
		for (auto j = i + 1; j != inputFiles.end(); ++j)
		{
			VocabWrapper first = *i;
			VocabWrapper second = *j;
			double current = similarity(*i, *j);
			vectorOfSimilarities.push_back(current);
			outfile << "Comparison of " << first.get_filename() << " and " << second.get_filename() << ": " << similarity(first, second) << '\n';
		}
	}
	outfile.close();// closes file; always do this when you are done using the file
	//output statement with the correct file name
	cout << "Results have been written to: Results_Compare_" << newFile << ".txt";

	return 0;
}