#include <iostream>
#include <fstream>
#include <stdio.h>
#include<algorithm>
#include <string.h>
#include <sstream>
#include <vector>
#include <cmath>
#include <set>
#include "Vocabulary.h"

VocabWrapper::VocabWrapper(const std::string& fileName) : fileName(fileName), uniqueWords()
{
    //Make sure to open the file within the constructor
    //std::ifstream in(fileName);
}

std::string VocabWrapper::get_filename() const
{
    //Just return the file name of type string to be used in the output of the program
	return fileName;
}

void VocabWrapper::read_vocab()
{
    //open the fileName (which is declared in the constructor) using ifstream, then initialize a string variable to be modified
    std::ifstream in;
    in.open(VocabWrapper::get_filename());
    //word1 in, create the string
    std::string word;

    while (in >> word)
    {
        //At each index of the word, check to see if it is upper case or lowercase using the if statement
        //If it's uppercase, change it to lowercase. That's it
        word[0] = tolower(word[0]);
        //Then insert all of these words into the set uniqueWords. We must use insert for sets, correct syntax
        uniqueWords.insert(word);
    }
    in.close();
    return;
}


size_t VocabWrapper::word_count() const
{  
    //Since the read_vocab function places all the lowercase terms from the file into the set uniqueWords,
        //all we have to do is return the size of the set which is the count of unique words. The reason why we use set
        //here is because sets do not include repeated terms when places elements in them
    size_t result = uniqueWords.size();
    return result;
}

int VocabWrapper::overlap_count(VocabWrapper& fileName1) const
{
    //initialize variable sim, for similar words
    std::set<std::string> secondSet = fileName1.uniqueWords;
    int sim = 0;

    //from the beginning of the uniqueWords set such that i does not equal the last term of the set
    for (auto i = VocabWrapper::uniqueWords.begin(); i != VocabWrapper::uniqueWords.end(); ++i)
    {
        //initialize variable auto by using the find function. This will search through each term
        auto result = secondSet.find(*i);
        //If the result does not equal the next term, go to the next
        if (result != secondSet.end())
        {
            ++sim;
        }
    }
    //return the int amount of similar words between each file
    return sim;
}

double similarity(VocabWrapper a, VocabWrapper b)
{
    a.read_vocab();
    b.read_vocab();
    //create variable for the overlapped count between two files
    int similarWords = a.overlap_count(b);
    //create variables for the count of unique words in each file
    //static cast to double in order for calculation to be accurate. We are outputting in double
    //similarWords / sqrt(Na*Nb)
    double root_NaNb = sqrt(static_cast<double>(a.word_count()) * static_cast<double>(b.word_count()));
    double similarity = static_cast<double>(similarWords / root_NaNb);
    //return the similarity score type double
    return similarity;
}