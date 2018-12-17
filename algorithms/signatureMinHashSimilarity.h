#ifndef SIGMAT
#define SIGMAT


#include "constAndRand.h"
#include "kShingles.h"
#include <stdlib.h>
using namespace std;

bool IsPrime(int number) {

    if (number == 2 || number == 3)
        return true;

    if (number % 2 == 0 || number % 3 == 0)
        return false;

    int divisor = 6;
    while (divisor * divisor - 2 * divisor + 1 <= number) {

        if (number % (divisor - 1) == 0)
            return false;

        if (number % (divisor + 1) == 0)
            return false;

        divisor += 6;

    }

    return true;

}

int firstPrime(int a) {
    while (!IsPrime(a)) ++a;
    return a;
}

// X hauria de ser un nombre primer per evitar colisions 
int modularHashFunction(int i, int x, int y, int z) {
	return (i*x+y)%z;
}

template<typename T>
vector<vector<int>> signatureMatrix (vector<unordered_set<T>>& documents, int nHashFunctions) {

	int ndocuments = documents.size();

	unordered_set<T> shingles = unionSets(documents[0], documents[1]);
    // In case we needed to compute union of > 2 documents
	for (int i = 2; i < ndocuments; i++) shingles = unionSets(shingles, documents[i]);

	vector<vector<int>> signatureMatrix(nHashFunctions, vector<int>(ndocuments, POSINFINITY));
	vector<vector<int>> hashFunctions(2, vector<int>(nHashFunctions));
	srand(genRand());
	int z = shingles.size();
	
	for (int i = 0; i < nHashFunctions; i++) {
		// x, y
		hashFunctions[0][i] = primes[i%primes.size()];
		hashFunctions[1][i] = rand()%z;
	}
	
	auto it = shingles.begin();

	for (int i = 0; i < shingles.size(); i++) {	
		// Signature matrix
		for (int n = 0; n < ndocuments; n++) {
			if (documents[n].find(*it) != documents[i].end()) {
				for (int j = 0; j < nHashFunctions; j++) {
					//int value = modularHashFunction(i, hashFunctions[0][j], hashFunctions[1][j], z);
					int value = mix(hashFunctions[0][j], hashFunctions[1][j], i);
					if (value < signatureMatrix[j][n]) {
						signatureMatrix[j][n] = value;
					}
				}
			}
		}
		
		++it;
	}
	return signatureMatrix;
}


double signatureMinHashSimilarity (vector<vector<int>>& signatureMatrix, int doc1, int doc2) {
	// Calcul de jaccard similarity a signature matrix
	// Comparem els dos primers documents (es pot canviar)
	int interseccio = 0;
	int nHashFunctions = signatureMatrix.size();
	for (int i = 0; i < nHashFunctions; i++) {
		if (signatureMatrix[i][doc1] == signatureMatrix[i][doc2] and signatureMatrix[i][doc1] != POSINFINITY) ++interseccio;
	}
	
    return ((double)interseccio/(double)nHashFunctions);
	//printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
}

#endif