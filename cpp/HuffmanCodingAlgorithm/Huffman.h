#pragma once
#include <iostream>
#include <unordered_map>
#include <queue>
#include "node.h"
#include <fstream>

bool isLeafNode(node* root) {
	return (!root->leftChild && !root->rightChild);
}

void goEncoding(node* root, string code, unordered_map<char, string>& huffmanCodes) {
	if (root == nullptr) return; // base case
	if (isLeafNode(root)) { // I am a leaf node
		huffmanCodes[root->ch] = code;
	}

	// process my childs
	goEncoding(root->leftChild, code + '0', huffmanCodes);
	goEncoding(root->rightChild, code + '1', huffmanCodes);
}


char goDecoding(node* root, int& index, string encodedText) {
	if (root == nullptr) return char(0); // base case
	if (isLeafNode(root)) {
		return root->ch;
	}
	index++;
	if (encodedText[index] == '0') return goDecoding(root->leftChild, index, encodedText); // come from left node
	else return goDecoding(root->rightChild, index, encodedText); // come from right node
}

string getEncodedString(string textToCompress, unordered_map<char, string> huffmanCodes) {
	string ret;
	for (auto ch : textToCompress) {
		ret += huffmanCodes[ch];
	}
	return ret;
}

void HuffmanCodingAlgorithm(string textToCompress) {
	ofstream huffmanOut("Out.txt");
	unordered_map<char, int> frqOfChars;
	unordered_map<char, string> huffmanCodes;

	// get frequencies of chars
	for (auto ch : textToCompress) {
		frqOfChars[ch]++;
	}

	priority_queue<node*, vector<node*>, compare> huffmanTree;
	for (auto pair : frqOfChars) {
		char ch = pair.first;
		int frq = pair.second;
		huffmanTree.push(createNode(ch, frq, nullptr, nullptr));
	}

	// build huffman tree
	while (huffmanTree.size() != 1) { // ! one component yet
		node* left = huffmanTree.top();
		huffmanTree.pop();

		node* right = huffmanTree.top();
		huffmanTree.pop();

		int totalFreq = left->charFreq + right->charFreq;
		huffmanTree.push(createNode('\0', totalFreq, left, right));
	}

	// get root of tree and go to encode
	node* root = huffmanTree.top();
	goEncoding(root, "", huffmanCodes);


	if (!huffmanOut.is_open())
		perror("error while opening file");

	// Original text
	huffmanOut << "Original text : " << endl  
		<< textToCompress << endl << endl;
	huffmanOut << "=========================================" << endl;

	// Huffman frequnces
	huffmanOut << "Huffman frequences : " << endl << endl;
	for (auto pair : frqOfChars) {
		char outChar = pair.first;
		int frq = pair.second;
		huffmanOut << outChar << " " << frq << endl;
	}
	huffmanOut << "=========================================" << endl;
	// Huffman codes
	huffmanOut << endl << "Huffman codes : " << endl << endl;
	for (auto pair : huffmanCodes) {
		char outChar = pair.first;
		string outCharCode = pair.second;
		huffmanOut << outChar << " " << outCharCode << endl;
	}
	huffmanOut << "=========================================" << endl;

	// Encoded text
	huffmanOut << endl << "Encoded text :" << endl;
	string encodedText = getEncodedString(textToCompress, huffmanCodes);
	huffmanOut << encodedText << endl;
	huffmanOut << "=========================================" << endl;

	// Decoded text
	int index = -1;
	string decodedText = "";
	while (index < int(encodedText.size()) - 2) {
		decodedText += goDecoding(root, index, encodedText);
	}
	huffmanOut << endl << "Decoded text :" << endl;
	huffmanOut << decodedText << endl;
	huffmanOut << "=========================================" << endl;

	huffmanOut.close();
}