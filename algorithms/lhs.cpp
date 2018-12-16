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
	
	
	/*
	 * HAsh functtion (Potser md5(n) 
	 */
	 
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
}
