#include <iostream>
#include <vector>
#include <string>
#include <math.h>
using namespace std;

int main(){
	int k;
	int d;
	cout << "Enter the number of k-singles" << endl;
	cin >> k;
	cout << "Enter the number of documents" << endl;
	cin >> d;
	int r = pow(26,k);
	bool m[d][r]{};
	for (int i = 0; i<d; ++i){
		cout << "Document " << i+1 << ":" << endl;
		string reader;
		cin >> reader;
		while (reader != "end"){
			int n = reader.length();
			if (n >= k){
				for (int j=0; j<=n-k; ++j){
					int r = 0;
					for (int l=0; l<k; ++l){
						r = r*26 + int(reader[j+l] - 'a');
					}
					m[i][r] = true;
				}
			}
			cin >> reader;
		}
	}
	for (int i = 0; i<r; ++i){
		string l = "";
		int aux = i;
		for (int n=0; n<k; ++n){
			l = ((char)(aux%26 + 'a')) + l;
			aux = aux/26;
		}
		cout << l << " ";
		for (int j = 0; j<d; ++j){
			cout << m[j][i] << " ";
		}
		cout << endl;
	}
}
	
