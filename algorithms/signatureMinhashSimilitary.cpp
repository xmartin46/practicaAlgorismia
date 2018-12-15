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

int main() {
	int k;
	cout << "Insert the k value to do the k-Shingling: ";
	cin >> k;
	
	//string filePath1 = "./Jsim2documents/first.txt";
	//string filePath2 = "./Jsim2documents/second.txt";

	string filePath1 = "./20doc/13.txt";
	string filePath2 = "./20doc/0.txt";

	bool spaces = true;
	bool allLowercase = true;
	vector<unordered_set<string>> documents;

	unordered_set<string> D1 = kShingleString(filePath1, k, spaces, allLowercase);
	unordered_set<string> D2 = kShingleString(filePath2, k, spaces, allLowercase);

	double sim = signatureMinHashSimilarity(D1, D2);

	cout << endl << "Jaccard Similarity in the Signature Matrix: " << sim * 100 << "%" << endl;
	//printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
}
