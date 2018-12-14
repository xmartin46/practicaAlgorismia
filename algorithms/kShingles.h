#ifndef KSHINGLES
#define KSHINGLES

#include <iostream>
#include <string>
#include <unordered_set>
#include <fstream>
#include "stringToInt.h"

using namespace std;
//Un unordered_set te probabilitat de col·lisio = 1/(2^32) per ints

// es Template per si volem fer-ho amb strings o passar-ho a 4 bytes (ints)
template<typename T>
int unionSetsSize (unordered_set<T>& s1, unordered_set<T>& s2) {
	//First count all elements of s1
	int size = s1.size();
	//Then count all elements of s2 that are not in s1, so that
	//elements that are in the intersection aren't repeated
	for (T elem : s2) {
		if (s1.find(elem) == s1.end()) {
			++size;
		}
	}
	return size;
}

template<typename T>
int intersectionSetsSize (unordered_set<T>& s1, unordered_set<T>& s2) {
	//Count all elements from one set that are in the other set
	int size = 0;
	for (T elem : s1) {
		if (s2.find(elem) != s2.end()) {
			++size;
		}
	}
	return size;
}

template<typename T>
double jaccardSimilarity(unordered_set<T>& s1, unordered_set<T>& s2) {	
	// Return the Jaccard Similarity (Intersection / Union)
	return (double)(intersectionSetsSize(s1, s2))/(double)(unionSetsSize(s1, s2));
}

// spaces == true if we want to count spaces
unordered_set<string> kShingleString(const string filePath, const int k, bool spaces) {
	fstream file;
    string word;
  	unordered_set<string> shingles;

    // Open the file 
    file.open(filePath);
    
    // String that will have all the words of the document
	string allWords = "";

	// Extracting words from the file
	file >> word;
    allWords += word;
    while (file >> word) {
		if (spaces) allWords += " ";
    	allWords += word;
	}
    
    for (int i = 0; i + k <= allWords.size(); i++) {
   	    shingles.insert(allWords.substr(i, k));
	}

	file.close();

	return shingles;
}

unordered_set<int> kShingleInt(const string filePath, const int k, bool spaces) {
	fstream file;
    string word;
  	unordered_set<int> shingles;

    // Open the file 
    file.open(filePath);
    
    // String that will have all the words of the document
	string allWords = "";

	// Extracting words from the file
	file >> word;
    allWords += word;
    while (file >> word) {
		if (spaces) allWords += " ";
    	allWords += word;
	}
    
    for (int i = 0; i + k <= allWords.size(); i++) {
        StringToInt *st = StringToInt::getInstance();
        int mapping = st->toInt(allWords.substr(i, k));
   	    shingles.insert(mapping);
	}

	file.close();

	return shingles;
}

#endif