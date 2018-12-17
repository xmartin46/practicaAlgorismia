#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <fstream>
#include <algorithm>
#include <time.h>
#include "kShingles.h"
#include "signatureMinHashSimilarity.h"
using namespace std;

/*
Obtenir una aproximacio del grau de similitud de Jaccard a traves d una representacio via signatures minhash basades 
en t funcions de hash. La mesura de similitud de dos signatures a i b amb t components es defineix com:
*/

int main(int argc, char** argv) {
	// Default values
	int k;
	int nHashFunctions = 500;
	bool measuringTime = false;
	string filePath1 = "./20doc/13.txt";
	string filePath2 = "./20doc/0.txt";
	bool spaces = true;
	if (argc > 1) {
		k = stoi(argv[1]);
		filePath1 = "./20doc/" + (string)argv[2] + ".txt";
		filePath2 = "./20doc/" + (string)argv[3] + ".txt";
		nHashFunctions = stoi(argv[6]);
		measuringTime = stoi(argv[4]);
		spaces = stoi(argv[5]);
	}
	else {
		cout << "Insert the k value to do the k-Shingling: ";
		cin >> k;
	}

	bool allLowercase = true;

	clock_t tStart;
	if (measuringTime) {
		tStart = clock();
	}

	unordered_set<string> D1 = kShingleString(filePath1, k, spaces, allLowercase);
	unordered_set<string> D2 = kShingleString(filePath2, k, spaces, allLowercase);

	vector<unordered_set<string>> documents(2);
	documents[0] = D1;
	documents[1] = D2;

	unordered_set<int> I1 = kShingleInt(filePath1, k, spaces, allLowercase);
	unordered_set<int> I2 = kShingleInt(filePath2, k, spaces, allLowercase);

	vector<vector<int>> sm = signatureMatrix(documents, nHashFunctions);

	double simS = signatureMinHashSimilarity(sm, 0, 1) * 100;
	//double simD = signatureMinHashSimilarity(I1, I2) * 100;

	//cout << endl << "The Jaccard Similarity using Strings as Shingles is: " << simS << "%" << endl;
	//cout << endl << "The Jaccard Similarity using Integers as Shingles is: " << simD << "%" << endl;
	if (!measuringTime) {
		cout << simS;
	}
	else {
		printf("%.3f", (double)(clock() - tStart)/CLOCKS_PER_SEC);
	}
}
