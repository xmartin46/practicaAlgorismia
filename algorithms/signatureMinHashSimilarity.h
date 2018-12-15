#include "constAndRand.h"
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
double signatureMinHashSimilarity(unordered_set<T>& D1, unordered_set<T>& D2) {
	
    vector<unordered_set<T>> documents(2);
	documents[0] = (D1);
	documents[1] = (D2);

	int ndocuments = 2;

	unordered_set<T> shingles = unionSets(D1, D2);
    // In case we needed to compute union of > 2 documents
	for (int i = 2; i < ndocuments; i++) shingles = unionSets(shingles, documents[i]);
	
	//clock_t tStart = clock();
	int nhashFunctions = 200;

	vector<vector<int>> signatureMatrix(nhashFunctions, vector<int>(ndocuments, INFINITY));
	vector<vector<int>> hashFunctions(2, vector<int>(nhashFunctions));
	srand(genRand());
	int z = shingles.size();
	
	for (int i = 0; i < nhashFunctions; i++) {
		// x, y
		hashFunctions[0][i] = primes[i%primes.size()];
		hashFunctions[1][i] = rand()%z;
	}
	
	auto it = shingles.begin();

	for (int i = 0; i < shingles.size(); i++) {	
		// Signature matrix
		for (int n = 0; n < ndocuments; n++) {
			if (documents[n].find(*it) != documents[i].end()) {
				for (int j = 0; j < nhashFunctions; j++) {
					int value = modularHashFunction(i, hashFunctions[0][j], hashFunctions[1][j], z);
					if (value < signatureMatrix[j][n]) {
						signatureMatrix[j][n] = value;
					}
				}
			}
		}
		
		++it;
	}

	// Calcul de jaccard similarity a signature matrix
	// Comparem els dos primers documents (es pot canviar)
	int doc1 = 0;
	int doc2 = 1;
	int interseccio = 0;
	for (int i = 0; i < nhashFunctions; i++) {
		if (signatureMatrix[i][doc1] == signatureMatrix[i][doc2] and signatureMatrix[i][doc1] != INFINITY) ++interseccio;
	}
	
    return ((double)interseccio/(double)nhashFunctions);
	//printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
}