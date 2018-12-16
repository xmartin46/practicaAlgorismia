#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <cmath>
//#include "constAndRand.h"

using namespace std;

double fun (const vector<vector<int>> & signatureMatrix, int x, int y){
	int intersection = 0;
	int nhash = signatureMatrix.size();
	for (int i = 0; i<nhash; i++){
		if (signatureMatrix[i][x] == signatureMatrix[i][y] /*and signatureMatrix[i][x]!=INFINITY*/){
			++intersection;
		}
	}
	return ((double)intersection/(double)nhash);
}

int main(){
	// demenar la matriu
	int nhashFunctions = 148;
	int ndocuments = 100;
	
	double tres = 0;
	
	cin >> tres;
	
	vector<vector<int>> signatureMatrix(nhashFunctions, vector<int>(ndocuments));
	srand(time(NULL));
	
	for (int i = 0; i < nhashFunctions; ++i){
		for (int j = 0; j < ndocuments; ++j){
			signatureMatrix[i][j] = rand()%10;
		}
	}
	
	/*for (int i = 0; i < nhashFunctions; ++i){
		 for (int d = 0; d < ndocuments; ++d){
			 cout << signatureMatrix[i][d] << "   ";
		 }
		 cout << endl;
	 }*/
	
	int b = 1;
	
	
	double err_min = 100;
	
	for (int i = 1; i <= nhashFunctions; ++i){
		if (nhashFunctions%i==0){
			double aux = pow((1.0/(double)i),((double)i/(double)nhashFunctions))*100;
			if (abs(aux-tres) < err_min){
				err_min = abs(aux-tres);
				b = i;
			}
		}
	}
	int r = nhashFunctions / b;
	
	cout << b << "    " << r << endl;
	
	
	unordered_map<int, unordered_set<int>> container;
	unordered_map<int, unordered_set<int>> similardoc;
	
	for (int band_it = 0; band_it < nhashFunctions; band_it = band_it + r){
		for (int d = 0; d < ndocuments; ++d){
			int nb = band_it/r;
			unsigned int val = 0;
			for (int j = 0; j < r; ++j){
				cout << signatureMatrix[band_it+j][d] << " ";
				val = val*10 + signatureMatrix[band_it+j][d];
			}
			cout << "-> " << val << endl;
			container[val].insert(d);
		}
		for (auto i : container){
			auto it = i.second.begin();
			while (it != i.second.end()){
				auto it2 = it;
				++it2;
				while (it2 != i.second.end()){
					cout << *it << "         " << *it2 << endl;
					//similardoc.insert(make_pair(*it,*it2));
					if (/*similardoc[*it2].find(*it) != similardoc[*it2].end()*/ true){
						cout << "n'he trobar un " << endl;
						similardoc[*it2].insert(*it);
					}
					++it2;
				}
				++it;
			}
		}
		container.clear();
	}
	
	cout << similardoc.size() << endl;
	
	for (auto it : similardoc){
		auto it2 = it.second.begin();
		while (it2 != it.second.end()){
			cout << it.first << " is similar " << *it2 << ": " << fun(signatureMatrix, it.first, *it2)*100 << endl;
			++it2;
		}
	}
}
