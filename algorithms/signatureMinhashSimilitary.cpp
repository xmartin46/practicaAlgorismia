#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <fstream>
#include <algorithm>
#include <limits>
#include <time.h>
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

bool IsPrime(int number)
{

    if (number == 2 || number == 3)
        return true;

    if (number % 2 == 0 || number % 3 == 0)
        return false;

    int divisor = 6;
    while (divisor * divisor - 2 * divisor + 1 <= number)
    {

        if (number % (divisor - 1) == 0)
            return false;

        if (number % (divisor + 1) == 0)
            return false;

        divisor += 6;

    }

    return true;

}

int firstPrime(int a)
{

    while (!IsPrime(++a)) 
    { }
    return a;

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
	/*for (int j = 0; j < k; ++j) cout << " ";
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
	}*/
	
	//clock_t tStart = clock();
	int infinity = numeric_limits<int>::max();
	int nhashFunctions = 14;
	vector<vector<int>> hashingValues(shingles.size(), vector<int>(nhashFunctions));
	vector<vector<int>> signatureMatrix(nhashFunctions, vector<int>(ndocuments, infinity));
	
	auto it = shingles.begin();
	int l = firstPrime(shingles.size());
	for (int i = 0; i < shingles.size(); i++) {
		// Compute h(i)
		for (int j = 0; j < nhashFunctions; j++) {
			
			//cout << endl << endl << l << endl << endl;
			switch (j) {
				case 0:
					hashingValues[i][j] = (i + 1)%l;
					break;
				case 1:
					hashingValues[i][j] = (2*(i + 1)+1)%l;
					break;
				case 2:
					hashingValues[i][j] = (3*i + 1)%l;
					break;
				case 3:
					hashingValues[i][j] = (2*(5*i + 1)+1)%l;
					break;
				case 4:
					hashingValues[i][j] = (i + 10)%l;
					break;
				case 5:
					hashingValues[i][j] = (4*(i + 1)-1)%l;
					break;
				case 6:
					hashingValues[i][j] = (i)%l;
					break;
				case 7:
					hashingValues[i][j] = (i*4-2)%l;
					break;
				case 8:
					hashingValues[i][j] = (10*(i + 1)-1)%l;
					break;
				case 9:
					hashingValues[i][j] = (5*i + 2)%l;
					break;
				case 10:
					hashingValues[i][j] = (7*(5*i + 5)+1)%l;
					break;
				case 11:
					hashingValues[i][j] = (i/2)%l;
					break;
				case 12:
					hashingValues[i][j] = (4*(i + 1)/2)%l;
					break;
				case 13:
					hashingValues[i][j] = (i/7)%l;
					break;
			}
		}
		
		// Signature matrix
		for (int n = 0; n < ndocuments; n++) {
			if (documents[n].find(*it) != documents[i].end()) {
				for (int j = 0; j < nhashFunctions; j++) {
					if (hashingValues[i][j] < signatureMatrix[j][n]) {
						signatureMatrix[j][n] = hashingValues[i][j];
					}
				}
			}
		}
		
		++it;
	}
	
	// Hashing Values
	/*cout << endl << endl;
	for (int j = 0; j < k; ++j) cout << " ";
	for (int i = 0; i < nhashFunctions; i++) {
		cout << "	H" << i + 1;
	}
	cout << endl;
	it = shingles.begin();
	for (int i = 0; i < shingles.size(); i++) {
		
		cout << *it << "	";
		++it;
		for (int j = 0; j < nhashFunctions; j++) {
			cout << hashingValues[i][j] << "	";
		}
		cout << endl;
	}
	
	// Signature Matrix
	cout << endl << endl;
	for (int i = 0; i < nhashFunctions; i++) {
		for (int j = 0; j < ndocuments; j++) {
			cout << signatureMatrix[i][j] << "	";
		}
		cout << endl;
	}*/
		
	// Càlcul de jaccard similarity a signature matrix
	// Comparem els dos primers documents (es pot canviar)
	int doc1 = 0;
	int doc2 = 1;
	int interseccio = 0;
	for (int i = 0; i < nhashFunctions; i++) {
		if (signatureMatrix[i][doc1] == signatureMatrix[i][doc2] and signatureMatrix[i][doc1] != infinity) ++interseccio;
	}
	
	cout << endl;

	cout << "Jaccard Similarity in the Signature Matrix: " << ((double)interseccio/(double)nhashFunctions) * 100 << "%" << endl;
	//printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
}
