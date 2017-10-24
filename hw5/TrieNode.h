/*
  Daniel Tran
  CSE 374
  16 February 2017
  Homework 5
  This file contains the header details for the TrieNode data structure
*/

#ifndef TRIENODE_H
#define TRIENODE_H

#define MAX_NODE 10
#define HASHTAG_INDEX 1

// Stores value of tree and its children

struct TrieNode {
  struct TrieNode * children[10];
  int number;
  char* word;
};

struct TrieNode * newNode(int n);
void deconstruct(struct TrieNode * root);
void pathMaker(struct TrieNode* current, int index, char* word);
int convertLetter(char ch);

#endif
