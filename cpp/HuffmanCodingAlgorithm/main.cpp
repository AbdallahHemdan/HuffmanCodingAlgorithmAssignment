#include <bits\stdc++.h>
#include "Huffman.h"
using namespace std;


int main() {
	// Authors : HamDola members [Abdallah Hemdan - Adel Mohamed]
	cout << "Welcome eng Ahmed Bahget" << endl;
	cout << "Please enter your file name to compress" << endl;
	cout << "For example : In.txt" << endl;
	string fileName; cin >> fileName;
	cout << "======================================" << endl;

	ifstream myInputFile(fileName);
	if (!myInputFile.is_open()) {
		perror("Ohh Sorry, error while opening file");
		myInputFile.close();
		return 0;
	}
	
	cout << "Congratulations.... Check Out.txt in the solution folder to view the output" << endl;
	string textToCompress, lineOfInput;
	while (getline(myInputFile, lineOfInput)) {
		textToCompress += lineOfInput;
	}
	HuffmanCodingAlgorithm(textToCompress);
	myInputFile.close();


}