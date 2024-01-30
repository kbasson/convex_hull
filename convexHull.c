/*
    Name: Karanvir Basson
    Title: Convex Hull Algorithm
    Date: 04-26-2022
*/

#include "convexHull.h" //INCLUDE HEADER FILES

int main() {

    FILE* file = fopen(FILENAME, "r"); //GET ALL POINTS FROM FILE

    if (file == NULL) { //If file doesn't exist

        printf("File doesn't exist!\n");
        return -1;

    }

    Node* nodes[NUM_POINTS]; //Define array of points

    int i = 0; //Index counter to store points into array
    char str[SIZE]; //Holds text line from file

    while (fgets(str, SIZE, file)) { //Gets line of text
        
        char* token = strtok(str, " \n"); //Gets first float    
        int x = atoi(token); //Saves first float as x value

        token = strtok(NULL, " \n"); //Gets next float
        int y = atoi(token); //Saves next float as y value

        nodes[i] = createNode(x, y); //Creates node using x and y values
        if (nodes[i] == NULL) return -1;

        i++; //Go to next node

    }

    fclose(file); //Close textfile upon completion
    printf("\n");

    for (int i = 0; i < NUM_POINTS; i++) { //for each point i

        for (int j = 0; j < NUM_POINTS; j++) { //for each point j, create a line between p and j

            if (i == j) continue; //If the 2 points are the same

            //CALCULATE A, B and C
            int a = (nodes[j] -> y) - (nodes[i] -> y);
            int b = (nodes[i] -> x) - (nodes[j] -> x);
            int c = ((nodes[i] -> x) * (nodes[j] -> y)) - ((nodes[i] -> y) * (nodes[j] -> x));

            //Count num points above/below/on line
            int numPos = 0;
            int numNeg = 0;

            for (int k = 0; k < NUM_POINTS; k++) { //for each point k create lines between p and k to compare to line pj

                //FIND IF LINE FROM P TO K IS ABOVE/BELOW LINE FROM P TO J
                int newC = (a * (nodes[k] -> x)) + (b * (nodes[k] -> y));
                int res = newC - c;

                if (res > 0) numPos++; //If point is above line
                if (res < 0) numNeg++; //If point is below line

                if (numPos > 0 && numNeg > 0) break; //If not boundary, exit loop early

            }

            if (numPos == 0 || numNeg == 0) { //If boundary

                //Add dest pointer to point 1
                if (nodes[i] -> dest1 == NULL) nodes[i] -> dest1 = nodes[j];
                else nodes[i] -> dest2 = nodes[j];

                //Add dest pointer to point 2
                if (nodes[j] -> dest1 == NULL) nodes[j] -> dest1 = nodes[i];
                else nodes[j] -> dest2 = nodes[i];

                printf("Line between (%d, %d) and (%d, %d) is boundary\n", nodes[i] -> x, nodes[i] -> y, nodes[j] -> x, nodes[j] -> y); //Print new line

            }

        }

    }

    int s1x = 4;
    int s1y = 3;

    int s2x = 49;
    int s2y = 42;

    //Gets s1 from user
    printf("\nEnter x and y coordinates of s1: ");
    scanf("%d %d", &s1x, &s1y);

    //Gets s2 from user
    printf("Enter x and y coordinates of s2: ");
    scanf("%d %d", &s2x, &s2y);

    //Holds s1 and s2 nodes
    Node* s1 = NULL;
    Node* s2 = NULL;

    for (int i = 0; i < NUM_POINTS; i++) { //for each point i

        if (nodes[i] -> dest1 == NULL || nodes[i] -> dest2 == NULL) continue; //If current point not on convex hull, continue

        if ((nodes[i] -> x) == s1x && (nodes[i] -> y) == s1y) s1 = nodes[i]; //If user input for s1 == current point, set s1 == current point
        if ((nodes[i] -> x) == s2x && (nodes[i] -> y) == s2y) s2 = nodes[i]; //If user input for s2 == current point, set s2 == current point

    }

    if (s1 == NULL || s2 == NULL) { //If one of the points were not found
        
        printf("These points don't exist in the convex hull!\n\n"); //If s1 and s2 not on convex hull
        return -1;

    } else { //If points found, display info
        
        printf("s1 = (%d, %d) and s2 = (%d, %d)\n\n", s1 -> x, s1 -> y, s2 -> x, s2 -> y);

    }

    float minDist = 0; //Holds smaller of the 2 traversal distances

    for (int z = 0; z < 2; z++) { //Traverse both paths

        printf("\nIteration %d\n", z + 1); //Print which iteration it is

        Node* temp = s1; //Holds current point
        float totalDist = 0; //Holds distance of current traversal

        while (temp != s2) { //While destination has not been reached

            temp -> visited = 1; //Set current point to visited
            printNode(temp); //Print current point

            //FIND NEXT POINT TO VISIT

            if (temp -> dest1 -> visited) { //If dest1 was visited
                
                totalDist += getDist(temp, temp -> dest2); //Calculate distance from current to dest2
                temp = temp -> dest2; //Set current to dest2

            } else { //If dest1 was not visited
                
                totalDist += getDist(temp, temp -> dest1); //Calculate distance from current to dest1
                temp = temp -> dest1; //Set current to dest1

            }

        }

        printf("\ntotalDist = %f\n", totalDist); //Print total distance traveled in current traversal

        if (z == 0) { //If first traversal
            
            minDist = totalDist; //Set min dist

        } else { //If second traversal

            if (totalDist < minDist) minDist = totalDist; //If current dist is smaller, set as min dist

        }

    }

    printf("\nminDist = %f\n\n", minDist); //Display min dist

    for (int i = 0; i < NUM_POINTS; i++) { //Free all points

        free(nodes[i]);

    }

    return 1;

}
