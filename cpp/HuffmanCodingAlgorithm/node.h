#pragma once
#include <bits\stdc++.h>

struct node {
	char ch; 
	int charFreq;
	node* leftChild;
	node* rightChild;
	node(char ch, int freq, node* left, node* right) {
		this->ch = ch;
		this->charFreq = freq;
		this->leftChild = left;
		this->rightChild = right;
	}
};

struct compare {
	bool operator()(node* left, node* right) {
		return left->charFreq > right->charFreq;
	}
};

node* createNode(char ch, int freq, node* left, node* right) {
	node* newNode = new node(ch, freq, left, right);
	return newNode;
}
