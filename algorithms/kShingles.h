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
unordered_set<T> unionSets(unordered_set<T>& s1, unordered_set<T>& s2) {
	//First count all elements of s1
	unordered_set<T> unionSet(s1);
	//Then count all elements of s2 that are not in s1, so that
	//elements that are in the intersection aren't repeated
	for (T elem : s2) {
		if (s1.find(elem) == s1.end()) {
			unionSet.insert(elem);
		}
	}
	return unionSet;
}

template<typename T>
unordered_set<T> intersectionSets(unordered_set<T>& s1, unordered_set<T>& s2) {
	//Count all elements from one set that are in the other set
	unordered_set<T> intersectionSet;
	for (T elem : s1) {
		if (s2.find(elem) != s2.end()) {
			intersectionSet.insert(elem);
		}
	}
	return intersectionSet;
}

template<typename T>
double jaccardSimilarity(unordered_set<T>& s1, unordered_set<T>& s2) {	
	// Return the Jaccard Similarity (Intersection / Union)
	int sizeIntersection = intersectionSets(s1, s2).size();
	int sizeUnion = unionSets(s1, s2).size();
	return ((double)(sizeIntersection)/(double)(sizeUnion));
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