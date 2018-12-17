#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
#include "constAndRand.h"

using namespace std;

// Generates a random pair of numbers from 0 to 19
int main() {
    srand(genRand());
    string pathString = "./20doc/";
	const char *path = pathString.c_str();
	vector<string> fileNames = list_dir(path);

	int nDocs = fileNames.size();

    cout << rand()%nDocs << " " << rand()%nDocs;
}