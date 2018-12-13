#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <fstream>
#include <algorithm>
using namespace std;

/*
Obtenir la similitud de Jaccard de dos documents representats per conjunts de
k-shingles. Recordeu que el grau de similitud de Jaccard de dos conjunts A i
B es defineix com Jsim(A, B) = |A n B|.
							   |A U B|
*/

double jaccardSimilarity(set<string> S1, set<string> S2) {
	// Vector that will have the intersections between S1 and S2
	vector<string> intersectionSets(max(S1.size(), S2.size()));
	
	// Vector that will have the union between S1 and S2
	vector<string> unionSets(S1.size() + S2.size());
	
	// This iterators will be at the last position of the intersection and union vectors
	// So, if we substract the value of the iterator to the size of the vector, we will
	// know the number of string in the intersection and in the union
	vector<string>::iterator it1;
	vector<string>::iterator it2;
	
	// Calculate the intersection between S1 and S2
	it1 = set_intersection(S1.begin(), S1.end(), S2.begin(), S2.end(), intersectionSets.begin());
	
	// Calculate the union between S1 and S2
	it2 = set_union(S1.begin(), S1.end(), S2.begin(), S2.end(), unionSets.begin());
	
	// Return the Jaccard Similarity (Intersection / Union)
	return (double)(it1 - intersectionSets.begin())/(double)(it2 - unionSets.begin());
}

set<string> kShingle(const string filePath, const int k) {
	fstream file;
    string word;
  	set<string> shingles;

    // Open the file 
    file.open(filePath);
    
    // True if we want to count spaces
    bool spaces = false;
    
    // String that will have all the words of the document
	string allWords = "";
	
    // Extracting words from the file
    while (file >> word) {
    	allWords += word;
    	if (spaces) allWords += " ";
	}
	
	// Delete the last " " of the string
	if (spaces) allWords = allWords.substr(0, allWords.size() - 1);
    
    for (int i = 0; i + k <= allWords.size(); i++) {
   	    shingles.insert(allWords.substr(i, k));
	}

	return shingles;
}

int main() {
	int k;
	cout << "Insert the k value to do the k-Shingling: ";
	cin >> k;
	
	string filePath1 = "./Jsim2documents/first.txt";
	string filePath2 = "./Jsim2documents/second.txt";
	set<string> D1 = kShingle(filePath1, k);
	set<string> D2 = kShingle(filePath2, k);

	cout << endl << "The Jaccard Similarity is: " << jaccardSimilarity(D1, D2)*100 << "%" << endl;
}
