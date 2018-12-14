#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <fstream>
#include <algorithm>
using namespace std;

/*
Obtenir una aproximaci´o del grau de similitud de Jaccard a trav´es d’una representaci´o via signatures minhash basades 
en t funcions de hash. La mesura de similitud de dos signatures a i b amb t components es defineix com:
*/

template<typename T>
unordered_set<T> unionSets (unordered_set<T>& s1, unordered_set<T>& s2) {
	unordered_set<T> v = s1;

	for (T elem : s2) {
		if (s1.find(elem) == s1.end()) {
			v.insert(elem);
		}
	}
	
	return v;
}

template<typename T>
vector<T> intersectionSets (unordered_set<T>& s1, unordered_set<T>& s2) {
	vector<T> v;
	for (T elem : s1) {
		if (s2.find(elem) != s2.end()) {
			v.push_back(elem);
		}
	}
	return v;
}

template<typename T>
double jaccardSimilarity(unordered_set<T>& s1, unordered_set<T>& s2) {	
	// Return the Jaccard Similarity (Intersection / Union)
}

// spaces == true if we want to count spaces
unordered_set<string> kShingle(const string filePath, const int k, bool spaces) {
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
	
	// Delete the last " " of the string
	if (spaces) allWords = allWords.substr(0, allWords.size() - 1);
    
    for (int i = 0; i + k <= allWords.size(); i++) {
   	    shingles.insert(allWords.substr(i, k));
	}

	file.close();

	return shingles;
}

int main() {
	int k;
	cout << "Insert the k value to do the k-Shingling: ";
	cin >> k;
	
	string filePath1 = "./Jsim2documents/first.txt";
	string filePath2 = "./Jsim2documents/second.txt";

	bool spaces = false;
	vector<unordered_set<string>> documents;

	unordered_set<string> D1 = kShingle(filePath1, k, spaces);
	documents.push_back(D1);
	unordered_set<string> D2 = kShingle(filePath2, k, spaces);
	documents.push_back(D2);

	int ndocuments = documents.size();

	unordered_set<string> shingles = unionSets(D1, D2);
	for (int i = 2; i < ndocuments; i++) shingles = unionSets(shingles, documents[i]);
	
	// Matrix representation
	for (int j = 0; j < k; ++j) cout << " ";
	for (int i = 0; i < ndocuments; i++) {
		cout << "	D" << i + 1;
	}
	cout << endl;
	
	for (string shing : shingles) {
		cout << shing << "	";
		for (int i = 0; i < ndocuments; i++) {
			if (documents[i].find(shing) != documents[i].end()) cout << "1	";
			else cout << "0	";
		}
		cout << endl;
	}
	
	int infinity = 999999;
	int nhashFunctions = 2;
	vector<vector<int>> hashingValues(shingles.size(), vector<int>(nhashFunctions));
	vector<vector<int>> signatureMatrix(nhashFunctions, vector<int>(ndocuments, infinity));
	
	for (int i = 0; i < shingles.size(); i++) {
		for (int j = 0; j < nhashFunctions; j++) {
			switch (j) {
				case 0:
					hashingValues[i][j] = (i + 1)%5;
					break;
				case 1:
					hashingValues[i][j] = (2*(i + 1)+1)%5;
					break;
			}
		}
	}
	
		// Hashing Values
	cout << endl << endl;
	for (int j = 0; j < k; ++j) cout << " ";
	for (int i = 0; i < ndocuments; i++) {
		cout << "	D" << i + 1;
	}
	cout << endl;
	auto it = shingles.begin();
	for (int i = 0; i < shingles.size(); i++) {
		
		cout << *it << "	";
		++it;
		for (int j = 0; j < nhashFunctions; j++) {
			cout << hashingValues[i][j] << "	";
		}
		cout << endl;
	}
	
	
	
	int j = 0;
	for (int i = 0; i < ndocuments; i++) {
		for (string shing : shingles) {
			if (documents[i].find(shing) != documents[i].end()) {
				for (int k = 0; k < nhashFunctions; k++) {
					if (hashingValues[j][k] < signatureMatrix[j][i]) {
						signatureMatrix[j][i] = hashingValues[j][k];
					}
				}
			}
			j++;
		}
		j = 0;
	}
	// Signature Matrix
	cout << endl << endl;
	for (int i = 0; i < nhashFunctions; i++) {
		for (int j = 0; j < ndocuments; j++) {
			cout << signatureMatrix[i][j] << "	";
		}
		cout << endl;
	}
}
