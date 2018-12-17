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

unordered_map<int, unordered_set<int>> getTrueCopies(vector<string>& fileNames, int k, bool spaces, bool allLowercase, double threshold) {
    string path = "./20doc/";
    int nDocs = fileNames.size();

	vector<unordered_set<string>> shingles(nDocs);

	for (int i = 0; i < nDocs; ++i) {
		shingles[i] = kShingleString(path + fileNames[i], k, spaces, allLowercase);
	}
    unordered_map<int, unordered_set<int>> trueCopies;
    for (int i = 0; i < nDocs; ++i) {
        for (int j = i; j < nDocs; ++j) {
            double sim = jaccardSimilarity(shingles[i], shingles[j]);
            if (sim >= threshold) {
                trueCopies[i].insert(j);
            }
        }
    }
    return trueCopies;
}

int main(int argc, char** argv){
	// demenar la matriu
	int k;
	int nHashFunctions = 500;
	bool measuringTime = false;
    bool spaces = true;
	bool allLowercase = true;
	double threshold = 0.42;
	if (argc > 1) {
		k = stoi(argv[1]);
		measuringTime = stoi(argv[2]);
		spaces = stoi(argv[3]);
        nHashFunctions = stoi(argv[4]);
        threshold = stof(argv[5]);
	}
	else {
		cout << "Insert the k value to do the k-Shingling: ";
		cin >> k;
	}
	
	string pathString = "./20doc/";
	const char *path = pathString.c_str();
	vector<string> fileNames = list_dir(path);

    clock_t tStart;


	if (measuringTime) {
		tStart = clock();
	}
    // Get all pairs that are considered copies without using lsh, just brute force
    // So that we can compare later
    unordered_map<int, unordered_set<int>> trueCopies = getTrueCopies(fileNames, k, spaces, allLowercase, threshold);

    int numTrueCopies = 0;
    for (auto s : trueCopies) {
        for (auto i : s.second) {
            ++numTrueCopies;
        }
    }
    if (measuringTime) {
        // Print time elapsed in s
		printf("%.3f", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    }
    else {
        //cout << numTrueCopies << endl;
    }



    if (measuringTime) {
        tStart = clock();
    }

    
	int nDocs = fileNames.size();

	vector<unordered_set<string>> shingles(nDocs);

	for (int i = 0; i < nDocs; ++i) {
		shingles[i] = kShingleString(path + fileNames[i], k, spaces, allLowercase);
	}
	
	vector<vector<int>> sm = signatureMatrix(shingles, nHashFunctions);
	
	int b = 1;
	int nhashFunctions = sm.size();
	
	double aux = POSINFINITY;
	double err_min = 1;
	int i = 1;
	while (aux > threshold && i <= nhashFunctions) {
		if (nhashFunctions%i==0){
			aux = pow((1.0/(double)i),((double)i/(double)nhashFunctions));
			// cout << "Bands: " << i << " -> Error: " <<  aux << endl;
			double diff = abs(aux-threshold);
			if (diff < err_min) {
				err_min = diff;
				b = i;
			}
		}
		++i;
	}

	int r = nhashFunctions / b;
	
	//cout << b << "    " << r << endl;
	
	unordered_map<string, unordered_set<int>> container;
	unordered_map<int, unordered_set<int>> similardoc;
	for (int band_it = 0; band_it < nhashFunctions; band_it = band_it + r) {
		int nb = band_it/r;
		for (int d = 0; d < nDocs; ++d){
			string val = "";
			for (int j = 0; j < r; ++j){
				val += to_string(sm[band_it+j][d]) + "-";
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
		container.clear();
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
			if (sim >= threshold) {
				meanSimTrue += sim;
				++numTruePairs;
                cout << fileNames[it.first] << "   is a copy of   " << fileNames[*it2] << endl;
			}
			else {
				meanSimFalse += sim;
			}
			++it2;
		}
	}

    if (measuringTime) {
        // Print time elapsed in s
		printf("%.3f", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    }


    /*
    //NumCandidats
    cout << numCandidatePairs << ",";
    //Encerts
    cout << numTruePairs << ",";
    //Falsos positius
    cout << max(0, (numCandidatePairs - numTruePairs)) << ",";
    //Falsos negatius
    cout << max(0, numTrueCopies - numTruePairs);
    */
    /*
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
    */
}
