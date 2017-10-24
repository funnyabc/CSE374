/*
  Daniel Tran
  CSE 374
  16 February 2017
  Homework 5
  This file contains the details for the TrieNode data structure
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "TrieNode.h"

// Creates a new node in memory and returns it
struct TrieNode * newNode(int n) {
  struct TrieNode * new = (struct TrieNode *) malloc(sizeof(struct TrieNode));
  memset(new, 0, sizeof(struct TrieNode));
  new -> number = n;
  for (int i = 0; i < 10; i++) {
    new -> children[i] = NULL;
  }
  return new;
}

// Deallocates the memory used for the Trie structure
void deconstruct(struct TrieNode * root) {
  for (int i = 0; i < MAX_NODE; i++) {
    if (root -> children[i] != NULL) deconstruct(root -> children[i]);
  }
  if (root -> word != NULL) free(root -> word);
  free(root);
}

// Constructs path on Trie structure based on
void pathMaker(struct TrieNode * root, int index, char * line) {
  if (index + 1 < strlen(line)) {
    int t9Number = convertLetter(line[index]);
    // Checks if node already exits. If none exists, creates node in the place
    if (root -> children[t9Number] == NULL) {
      root -> children[t9Number] = newNode(t9Number);
    }
    pathMaker(root -> children[t9Number], index + 1, line);
  } else {
    // Checks the contents of the word field when the correct spot is found in
    // the trie
    if (root -> word == NULL) {
      // Adds memory to the location to save the word
      root -> word = (char *) malloc(strlen(line) + 1);
      memset(root -> word, 0, strlen(line));
      strncpy(root -> word, line, strlen(line));
      root -> word[strlen(line) - 1] = '\0';
    } else {
      // If a word is already occupying the spot, traverses through the hashtag
      // index, 1, to find an open spot
      if (root -> children[HASHTAG_INDEX] == NULL) {
        root -> children[HASHTAG_INDEX] = newNode(HASHTAG_INDEX);
      }
      pathMaker(root -> children[HASHTAG_INDEX], index, line);
    }
  }
}

// Converts a given letter to its t9 representation.
int convertLetter(char ch) {
  int t9[26] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 8, 8,
    8, 9, 9, 9, 9};
  if (ch == '#') return 1;
  return t9[ch - 'a'];
}
