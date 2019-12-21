// Author: Justin S
/*
Description
    A program to generate a minimum spanning tree matrix given 
    a graph, which is represented by another matrix.
*/

#include <fstream>
#include <iostream>
#include <limits>   // set int max to represent infinity
#include <cstdlib>
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]){
    ifstream fileIn(argv[1]);
    ofstream fileOut;
    fileOut.open("mst.txt");
    int totV;
    fileIn >> totV;             // read # of vertices
    int matrix[totV][totV];     // Adjacency matrix
    int mst[totV][totV] = {};
    int table[totV][3];         // rows: 1 to totV, columns:  [0] Visited    [1] Distance    [2] Parent Pointer
    int root;

    //Read file into adjacency matrix
    for (int i = 0; i < totV; i++){
        for (int j = 0; j < totV; j++){
            fileIn >> matrix[i][j];
        }
    }

    // Initialize
    root = 0; //Vertex 1 @ index of 0
    for (int i = 0; i < totV; i++){
        table[i][0] = 0;                            // 0 for false, 1 for true
        table[i][1] = numeric_limits<int>::max();   // infinity
        table[i][2] = -1;                           // -1 indicates no parent node
    }
    table[root][1] = 0;                             // root distance to 0
    table[root][2] = root;
    
    // Visit
    table[root][0] = 1;                             // mark root as visited
    int currentV = root;
    int countV = 1;
    int countE = 0;
    int temp = 0;
    while(countV < totV && countE < totV - 1){
        int minVal = -1;
        int minInd = -1;
        for (int j = 0; j < totV; j++){
            // update connected vertice if it has not been visited
            if(table[j][0] == 0){
                if (matrix[currentV][j] != 0 && matrix[currentV][j] < table[j][1]){
                    table[j][1] = matrix[currentV][j];
                    table[j][2] = currentV;
                }
            }
        }
        //search for min distance value in table for vertices unvisited
        for (int i = 0; i < totV; i++){
            if(table[i][0] == 0){
                //find first min distance value of unvisited vertex in table
                if (table[i][1] != 0 && minVal == -1){
                    minVal = table[i][1];
                    minInd = i;
                }
                //compare rest of the #'s in the row to minVal and swap if true
                else if (table[i][1] < minVal && table[i][1] != 0){
                    minVal = table[i][1];
                    minInd = i;
                }
            }
        }
        table[minInd][0] = 1;                   //mark that vertex as visited in table[][]
        mst[table[minInd][2]][minInd] = minVal; //add vertice with lowest edge weight to MST
        mst[minInd][table[minInd][2]] = minVal;
        currentV = minInd;                      //set currentV to that vertex for next loop iteration
        countV++;                               //increment # of vertices and edges visited
        countE++;
    }

    //Write MST to mst.txt
    fileOut << "MST" << endl;
    for (int i = 0; i < totV; i++){         //print matrix read from graph
        for (int j = 0; j < totV; j++){
            fileOut << mst[i][j] << " ";
        }
        fileOut << endl;
    }
    cout << endl;

    /*  
    
    // Print out funcs for testing

    cout << "totV: " << totV << endl;       //print totV
    
    cout << "ADJACENCY MATRIX" << endl;
    for (int i = 0; i < totV; i++){         //print matrix read from graph
        for (int j = 0; j < totV; j++){
            cout << matrix[i][j];
        }
        cout << endl;
    }
    cout << endl;
    
    cout << "TABLE" << endl;
    for (int i = 0; i < totV; i++){         //print matrix read from graph
        for (int j = 0; j < 3; j++){
            cout << left << setw(12) << table[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "countV: " << countV << endl;
    cout << "countE: " << countE << endl;
    cout << endl;

    */

}