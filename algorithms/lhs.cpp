#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <cmath>
using namespace std;

main(){
	// demenar la matriu
	int nhashFunctions = 200;
	int ndocuments = 2;
	
	vector<vector<int>> signatureMatrix(nhashFunctions, vector<int>(ndocuments));
	srand(45);
	
	for (int i = 0; i < nhashFunctions; ++i){
		for (int j = 0; j < ndocuments; ++j){
			signatureMatrix[i][j] = rand()%9;
		}
	}
	
	for (int i = 0; i < nhashFunctions; ++i){
		 for (int d = 0; d < ndocuments; ++d){
			 cout << signatureMatrix[i][d] << "   ";
		 }
		 cout << endl;
	 }
	
	int b = 100;
	int r = nhashFunctions / b; //2
	
	// https://hal.inria.fr/inria-00567191/document


	/*
	* HAsh functtion (Potser md5(n) 
	*/
	/*
	vector<vector<int>> lshMatrix(pow(10,r), vector<int>(ndocuments, 0));

	for (int d = 0; d < ndocuments; ++d){
		for (int i = 0; i < nhashFunctions; i = i + r){
			int val = 0;
			for (int j = 0; j < r; ++j){
				cout << signatureMatrix[i+j][d] << " ";
				val = val*10 + signatureMatrix[i+j][d];
			}
			cout << "-> " << val << endl; 
		lshMatrix[val][d] = 1;
		}
	}

	for (int i = 0; i < pow(10,r); ++i){
		for (int d = 0; d < ndocuments; ++d){
			cout << lshMatrix[i][d] << "   ";
		}
		cout << endl;
	}
	*/
	vector<vector<int>> lshMatrix(b, vector<int>(ndocuments, 0));
	for (int d = 0; d < ndocuments; ++d){
		for (int i = 0; i < nhashFunctions; i = i + r){
			int nb = i/r;
			int val = 0;
			for (int j = 0; j < r; ++j){
				cout << signatureMatrix[i+j][d] << " ";
				val = val*10 + signatureMatrix[i+j][d];
			}
		cout << "-> " << val << endl; 
		lshMatrix[nb][d] = val;
		}
	}



	for (int i = 0; i < b; ++i){
		for (int d = 0; d < ndocuments; ++d){
			cout << lshMatrix[i][d] << "   ";
		}
		cout << endl;
	}

	int doc1 = 0;
	int doc2 = 1;
	int interseccio = 0;
	for (int i = 0; i < b; i++) {
		if (lshMatrix[i][doc1] == lshMatrix[i][doc2]) ++interseccio;
	}

	double result = ((double)interseccio/(double)nhashFunctions);
	
	cout << endl << "The Jaccard Similarity using lhs is: " << result * 100 << "%" << endl;
}
