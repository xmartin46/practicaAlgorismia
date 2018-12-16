#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <cmath>

using namespace std;

main(){
	// demenar la matriu
	int nhashFunctions = 200;
	int ndocuments = 2;
	
	int threshold;
	
	cin >> threshold;
	
	vector<vector<int>> signatureMatrix(nhashFunctions, vector<int>(ndocuments));
	srand(45);
	
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
	//vector<vector<int>> lshMatrix(b, vector<int>(ndocuments, 0));
	//vector<int> container(1000000, 0);
	unordered_map<int, unordered_set<int>> container;
	unordered_set<pair<int, int>> similardoc;
	for (int d = 0; d < ndocuments; ++d){
		for (int i = 0; i < nhashFunctions; i = i + r){
			int nb = i/r;
			unsigned int val = 0;
			for (int j = 0; j < r; ++j){
				cout << signatureMatrix[i+j][d] << " ";
				val = val*10 + signatureMatrix[i+j][d];
			}
			cout << "-> " << val << endl;
			container[val].insert(d);
		}
		for (auto i : container){
			auto it = i.begin();
			while (it != i.end()){
				auto it2 = it+1;
				while (it2 != i.end()){
					//similardoc.insert(make_pair(*it,*it2));
				}
			}
		}
		container.clear();
	}


	/*for (int i = 0; i < 1000000; ++i){
		bool t = false;
		for (int d = 0; not t and d < ndocuments; ++d){
			if (container[i][d] == 1) t = true;
		}
		if (t){
			cout << i << "    ";
			for (int d = 0; d < ndocuments; ++d){
				cout << container[i][d] << "  ";
			}
			cout << endl;
		}
	}

	int doc1 = 0;
	int doc2 = 1;
	int interseccio = 0;
	int unio = 0;
	for (int i = 0; i < 1000000; i++) {
		if (container[i][doc1] == container[i][doc2] and container[i][doc1]!=0) ++interseccio;
		if (container[i][doc1] == 1 or  container[i][doc2] == 1) ++unio;
	}

	double result = ((double)interseccio/(double)unio)*100;
	cout << endl << "Probabilitat: " << result << "%" << endl;
	
	if (result >= threshold) cout << "Hi ha molta probabilitat de ser similars" << endl;
	else cout << "No son similars" << endl;*/
	
	
}
