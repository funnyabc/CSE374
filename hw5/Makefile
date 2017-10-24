#Daniel Tran
#CSE 374
#16 February 2017
#Homework 5
#This is a Makefile that allows for the t9 program to be run in one command

t9: t9.o TrieNode.o
	gcc -Wall -std=c11 -g -o t9 t9.o TrieNode.o

t9.o: t9.c TrieNode.h
	gcc -Wall -std=c11 -g -c t9.c

TrieNode.o: TrieNode.c TrieNode.h
	gcc -Wall -std=c11 -g -c TrieNode.c
