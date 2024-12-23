#ifndef GRAPH_H
#define GRAPH_H
#include<bits/stdc++.h> //Includes all the libraries 
#include"Trie.h"
using namespace std;


//Using template class
template<typename T>
class Graph
{
public:

    //Name: Graph
    //Purpose: Default Contructor
    //Return: None
    //Parameters: None
    Graph();

    //Name: Graph
    //Purpose: Parameterized Contructor
    //Return: None
    //Parameters: vertices of the graph, rows and columns and grid we want to work on
    Graph(int vertices, int rows, int cols, T** grid, Trie dictionary);

    //Name: ~Graph
    //Purpose: Destructor (destroy the objects)
    //Return: None
    //Parameters: None
    virtual ~Graph();

    //Name: addEdge
    //Purpose: Add undirected edges between vertices
    //Return: None
    //Parameters: Vertices on which we want to add edges
    void addEdge(int u, int v);

    //Name: removeEdge
    //Purpose: Remove edges between vertices
    //Return: None
    //Parameters: Vertices from which edges need to be removed
    void removeEdge(int u, int v);

    //Name: hasEdge
    //Purpose: Check if an edge exists
    //Return: None
    //Parameters: Vertices whose edge we want to check
    bool hasEdge(int u, int v) const;

    //Name: display
    //Purpose: Display the adjacency matrix
    //Return: None
    //Parameters: None
    void display() const;

    //Name: getAdjMatrix
    //Purpose: Return the adjMatrix if needed
    //Return: AdjMatrix
    //Parameters: None
    const vector<vector<T>> &getAdjMatrix() const;

    //Name: getNumVertices
    //Purpose: Return the number of vertices
    //Return: Return the number of vertices
    //Parameters:None
    int getNumVertices() const;

    //Name: CreateAdjMatrix
    //Purpose: Create the adjaceny matrix 
    //Return: None
    //Parameters: None
    void CreateAdjMatrix();

    //Name: getVertex
    //Purpose: get the element at the specific coordinate
    //Return: Vertex
    //Parameters: row, column and total columns of a graph
    int getVertex(int row, int col, int cols) const;


    //Name: DepthFirstSearch
    //Purpose: Search the word using DFS using stack
    //Return: true or false based on word found
    //Parameters: Word we want to search
    bool DepthFirstSearch(const string& word);

    //Name: BreadthFirst Search
    //Purpose: Find all the dictionary words in the grid
    //Return: None
    //Paramteres: dictionaty from which we want to search the elements
    void BreathFirstSearch(Trie& dictionary);

    //NameL solveGrid
    //Purpose: Solve the grid using BreadthFirstSearch and print words
    //Return: None
    //Parameters: None
    void solveGrid();

protected:
private:

    //This ADT is created specifically for Adjaceny Matrix

    //Total vertices of a grid
    int numVertices;

    //Initialize Adjaceny matrix
    vector<vector<T>> adjMatrix;

    //variables to store rows, cols and grid on class level
    int Rows;
    int Cols;    
    T** Grid;

    //Storing the dictionary
    Trie Dictionary;
};

#endif // GRAPH_H