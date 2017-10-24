/*
  Daniel Tran
  CSE 374
  16 February 2017
  Homework 5
  This program allows a user to find words based on a t9 number pattern, which is the same standard
  used for phones. Each number corresponds to a set of three or four numbers and words can be 
  formed 
*/

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "TrieNode.h"

#define MAX_LENGTH 100

void buildTrie(FILE * f, struct TrieNode * root);
void interactiveSession();
void search(struct TrieNode * root);

// Main program
int main(int argc, char ** argv) {
  // Checks if just one file is provided
  if (argc != 2) {
    printf("Please provide only one dictionary file");
    return 1;
  }
  // Process dictionary
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Error in file processing");
    return 1;
  }
  // Builds Trie, using an array to represent the root
  struct TrieNode* root = newNode(0);
  buildTrie(f, root);
  fclose(f);
  // Initiates interactive session
  interactiveSession(root);
  // Frees memory after use
  deconstruct(root);
  return 0;
}

// Controls the interactions between the user and the program on
// the terminal
void interactiveSession(struct TrieNode * root) {
  printf("Enter \"exit\" to quit.\n");
  printf("Enter Key Sequence (or \"#\" for next word):\n");
  char input[100];
  scanf("%s", input);
  // Traverses the trie node and retrieves letter.
  struct TrieNode * travel = root;
  while (strncmp("exit", input, 4) != 0) {
    // Check if input is a hashtag. Reassigns local pointer to original root
    // if first input is a number.
    if (input[0] != '#') {
      travel = root;
    }
    // Goes through given pattern
    for (int i = 0; i < strlen(input); i++) {
      // Checks if null pops up
      int index = input[i] == '#' ? HASHTAG_INDEX : input[i] - '0';
        if (travel -> children[index] == NULL) {
          if (index == HASHTAG_INDEX) {
            printf("\tThere are no more T9onyms.\n");
            break;
          } else {
            printf("\tNot found in current dictionary.\n");
            break;
          }
        }
      // Advances to next node if clear
      travel = travel -> children[index];
      if (i + 1 == strlen(input)) {
        if (travel -> word != NULL)
          printf("\t\'%s\'\n", travel -> word);
        else
          printf("\tNot found in current dictionary.\n");
      }
    }
    printf("Enter Key Sequence (or \"#\" for next word):\n");
    scanf("%s", input);
  }
  return;
}

// Constructs the trie of the passed in dictionary
// Returns root of trie tree
void buildTrie(FILE * f, struct TrieNode * root) {
  char line[MAX_LENGTH];
  while (fgets(line, MAX_LENGTH, f)) {
    pathMaker(root, 0, line);
  }
}
