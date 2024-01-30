/*
    Name: Karanvir Basson
    Title: Convex Hull Algorithm
    Date: 04-26-2022
*/

//INCLUDE HEADER FILES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SIZE 50
#define NUM_POINTS 30000
#define FILENAME "points2.txt"

typedef struct node {

    int x;
    int y;
    int visited;

    struct node* dest1;
    struct node* dest2;

} Node;

Node* createNode(int x, int y); //Given an x and y value, create and return a node struct
void printNode(Node* node); //Given a node, print its info
float getDist(Node* node1, Node* node2); //Given 2 nodes, return distnace between them
