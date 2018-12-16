#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <cmath>
#include "signatureMinHashSimilarity.h"

using namespace std;

int main(int argc, char** argv){
	// demenar la matriu
	int k;
	int nHashFunctions;
	bool measureTime;
	double threshold = 0.20;
	if (argc > 1) {
		k = stoi(argv[1]);
		nHashFunctions = stoi(argv[2]);
		measureTime = stoi(argv[3]);
		threshold = stoi(argv[4]);
	}
	else {
		cout << "Insert the k value to do the k-Shingling: ";
		cin >> k;
		// Default value for number of hash functions
		// Simulating permutations
		nHashFunctions = 500;
		measureTime = false;
	}

	bool spaces = true;
	bool allLowercase = true;
	string pathString = "./20doc/";
	const char *path = pathString.c_str();
	vector<string> fileNames = list_dir(path);

	int nDocs = fileNames.size();

	vector<unordered_set<string>> shingles(nDocs);

	for (int i = 0; i < nDocs; ++i) {
		shingles[i] = kShingleString(path + fileNames[i], k, spaces, allLowercase);
	}
	

	vector<vector<int>> sm = signatureMatrix(shingles, nHashFunctions);
	
	int b = 1;
	int nhashFunctions = sm.size();
	
	double err_min = 1;
	
	for (int i = 1; i <= nhashFunctions; ++i){
		if (nhashFunctions%i==0){
			double aux = pow((1.0/(double)i),((double)i/(double)nhashFunctions));
			// cout << "Bands: " << i << " -> Error: " <<  aux << endl;
			double diff = abs(aux-threshold);
			if (diff < err_min) {
				err_min = diff;
				b = i;
			}
		}
	}
	//b = 8;
	int r = nhashFunctions / b;
	
	cout << b << "    " << r << endl;
	
	unordered_map<string, unordered_set<int>> container;
	unordered_map<int, unordered_set<int>> similardoc;
	for (int band_it = 0; band_it < nhashFunctions; band_it = band_it + r) {
		int nb = band_it/r;
		for (int d = 0; d < nDocs; ++d){
			string val = "";
			for (int j = 0; j < r; ++j){
				val += to_string(sm[band_it+j][d]) + "-";
				//cout << sm[band_it+j][d] << " ";
				//val = val*10 + sm[band_it+j][d];
			}
			//cout << "-> " << val << endl;
			container[val].insert(d);
		}
		for (auto i : container){
			auto it = i.second.begin();
			while (it != i.second.end()){
				auto it2 = it;
				++it2;
				while (it2 != i.second.end()){
					//cout << *it << "         " << *it2 << endl;
					// cout << "n'he trobar un " << endl;
					if (*it2 > *it) {
						similardoc[*it2].insert(*it);
					}
					else {
						similardoc[*it].insert(*it2);
					}
					++it2;
				}
				++it;
			}
		}
	}
	
	// cout << similardoc.size() << endl;
	int numCandidatePairs = 0;
	int numTruePairs = 0;
	double meanSimTrue = 0;
	double meanSimFalse = 0;
	for (auto it : similardoc){
		auto it2 = it.second.begin();
		while (it2 != it.second.end()){
			//cout << endl << fileNames[it.first] << " is similar " << fileNames[*it2] << ": " << signatureMinHashSimilarity(sm, it.first, *it2)*100 << endl;
			++numCandidatePairs;
			double sim = signatureMinHashSimilarity(sm, it.first, *it2);
			if (sim >= t) {
				meanSimTrue += sim;
				++numTruePairs;
			}
			else {
				meanSimFalse += sim;
			}
			++it2;
		}
	}
	meanSimTrue /= numTruePairs;
	meanSimFalse /= (double)(numCandidatePairs - numTruePairs);
	int numPossiblePairs = (nDocs*(nDocs-1))/2;
	cout << "nDocs: " << nDocs << endl;
	cout << "numPossiblePairs: " << numPossiblePairs << endl;
	cout << "numCandidatePairs: " << numCandidatePairs << endl; 
	cout << "numTruePairs: " << numTruePairs << endl; 
	cout << "numFalsePairs: " << (numCandidatePairs - numTruePairs) << endl; 
	cout << "falsePositives: " << ((double)(numCandidatePairs - numTruePairs)/numCandidatePairs) * 100 << "%" << endl;
	cout << "truePositives: " << ((double)(numTruePairs)/numCandidatePairs) * 100 << "%" << endl;
	cout << "meanSim of TruePairs: " << meanSimTrue * 100 << "%" << endl; 
	cout << "meanSim of FalsePositivePairs: " << meanSimFalse * 100 << "%" << endl; 
	cout << endl;
}
