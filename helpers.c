/*
    Name: Karanvir Basson
    Title: Convex Hull Algorithm
    Date: 04-26-2022
*/

#include "convexHull.h"

Node* createNode(int x, int y) { //Given an x and y value, create and return a node struct

    Node* node = malloc(sizeof(Node)); //Allocate memory for node
    if (node == NULL) return NULL; //NULL ptr check

    //Initialize node
    node -> x = x;
    node -> y = y;
    node -> visited = 0;
    node -> dest1 = NULL;
    node -> dest2 = NULL;

    return node; //Return allocated node

}

void printNode(Node* node) { //Given a node, print its info

    if (node == NULL) return; //NULL ptr check

    //PRINT NODE INFO
    printf("\n(%d,%d)\n", node -> x, node -> y);
    printf("Visited = %d\n\n", node -> visited);

    if (node -> dest1 != NULL && node -> dest2 != NULL) { //If node on convex hull

        printf("DEST 1: (%d,%d)\n", node -> dest1 -> x, node -> dest1 -> y);
        printf("DEST 2: (%d,%d)\n", node -> dest2 -> x, node -> dest2 -> y);

    }

}

float getDist(Node* node1, Node* node2) { //Given 2 nodes, return distnace between them

    int x = ((node1 -> x) - (node2 -> x)) * ((node1 -> x) - (node2 -> x)); //Calculate (x1-x2)^2
    int y = ((node1 -> y) - (node2 -> y)) * ((node1 -> y) - (node2 -> y)); //Calculate (y1-y2)^2
    
    double res = sqrt(x + y); //Take sqrt of x + y
    return res; //Return result

}
