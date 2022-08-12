#ifndef _VOCABULARY_
#define _VOCABULARY_

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <set>

class VocabWrapper
{

public:

	/**
	Constructor: accepts the name of a file name and initializes the string variable of fileName

	@param txt file inputted by the user
	*/
	VocabWrapper(const std::string& fileName);

	/**
	This function returns the name of te file to be used for the output

	@return current score
	*/

	std::string get_filename() const;

	/**
	This function reads all of the words in from the file of the given name turning all capital letters to lowercase.
	This function will then store the lowercase words in a new vector uniqueWords

	@return nothing
	*/

	void read_vocab();

	/**
	This function returns how many unique words there were in the associated file

	@return an int representing the number of unique words ine file.
	*/

	size_t word_count() const;

	/**
	This function, accepts another VocabWrapper class, returning a count of how many words 
	their two associated files have in common (after capitalizations have been removed).

	@return an int representing the number of overlapping (set intersection) words in the two files
	*/

	int overlap_count(VocabWrapper& fileName1) const;

	//All variables here will be utilized/modified in the Vocabulary.cpp file
private:
	std::string fileName;
	std::set <std::string> uniqueWords;
};

/**
This function computes the similarity between two inputs of type VocabWrapper.
It is not included in the constructor because it is separate.

@return an double representing the similarity score
*/
double similarity(VocabWrapper a, VocabWrapper b);


#endif
