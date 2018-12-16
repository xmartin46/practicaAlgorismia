#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <cmath>
#include "signatureMinhashSimilarity.h"
//#include "constAndRand.h"

using namespace std;

int main(int argc, char** argv){
	// demenar la matriu
	int k;
	int nHashFunctions;
	bool measureTime;
	double threshold = 0.05;
	if (argc > 1) {
		k = stoi(argv[1]);
		nHashFunctions = stoi(argv[2]);
		measureTime = stoi(argv[3]);

	}
	else {
		cout << "Insert the k value to do the k-Shingling: ";
		cin >> k;
		// Default value for number of hash functions
		// Simulating permutations
		nHashFunctions = 200;
		measureTime = false;
	}

	int nDocs = 6;

	bool spaces = true;
	bool allLowercase = true;
	vector<unordered_set<string>> shingles(nDocs);
	vector<string> fileNames(nDocs);
	string filePath = "./20doc/";
	fileNames[0] = "0.txt";
	fileNames[1] = "HP0.txt";
	fileNames[2] = "documentBasic.txt";
	fileNames[3] = "first.txt";
	fileNames[4] = "HP13.txt";
	fileNames[5] = "second.txt";
	
	shingles[0] = kShingleString("./20doc/0.txt", k, spaces, allLowercase);
	shingles[1] = kShingleString("./20doc/HP0.txt", k, spaces, allLowercase);
	shingles[2] = kShingleString("./20doc/documentBasic.txt", k, spaces, allLowercase);
	shingles[3] = kShingleString("./Jsim2documents/first.txt", k, spaces, allLowercase);
	shingles[4] = kShingleString("./20doc/HP13.txt", k, spaces, allLowercase);
	shingles[5] = kShingleString("./Jsim2documents/second.txt", k, spaces, allLowercase);
	

	/*
	for (int i = 0; i < nDocs; ++i) {
		string filePath = "./20doc/" + to_string(i) + ".txt"; 
		shingles[i] = kShingleString(filePath, k, spaces, allLowercase);
	}
	*/

	vector<vector<int>> sm = signatureMatrix(shingles, nHashFunctions);
	
	int b = 1;
	int nhashFunctions = sm.size();
	
	double err_min = 1;
	
	for (int i = 1; i <= nhashFunctions; ++i){
		if (nhashFunctions%i==0){
			double aux = pow((1.0/(double)i),((double)i/(double)nhashFunctions));
			// cout << "Bands: " << i << " -> Error: " <<  aux << endl;
			if (abs(aux-threshold) < err_min){
				err_min = abs(aux-threshold);
				b = i;
			}
		}
	}
	int r = nhashFunctions / b;
	
	// cout << b << "    " << r << endl;
	
	
	unordered_map<int, unordered_set<int>> container;
	unordered_map<int, unordered_set<int>> similardoc;
	
	for (int band_it = 0; band_it < nhashFunctions; band_it = band_it + r){
		for (int d = 0; d < nDocs; ++d){
			int nb = band_it/r;
			unsigned int val = 0;
			for (int j = 0; j < r; ++j){
				//cout << sm[band_it+j][d] << " ";
				val = val*10 + sm[band_it+j][d];
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
					//similardoc.insert(make_pair(*it,*it2));
					if (/*similardoc[*it2].find(*it) != similardoc[*it2].end()*/ true){
						// cout << "n'he trobar un " << endl;
						similardoc[*it2].insert(*it);
					}
					++it2;
				}
				++it;
			}
		}
		container.clear();
	}
	
	// cout << similardoc.size() << endl;
	
	for (auto it : similardoc){
		auto it2 = it.second.begin();
		while (it2 != it.second.end()){
			cout << endl << fileNames[it.first] << " is similar " << fileNames[*it2] << ": " << signatureMinHashSimilarity(sm, it.first, *it2)*100 << endl;
			++it2;
		}
	}
	cout << endl;
	
}