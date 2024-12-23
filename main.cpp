#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Graph.h"
#include "Trie.h"
#include<bits/stdc++.h>

using namespace std;

// Function to read string from grid
string ReadFile(string inputFile)
{

    // Read grid.txt file
    ifstream myfile(inputFile);
    string str, temp;

    // Check if the file is valid
    if (!myfile)
    {
        cout << "Grid.txt file not found" << endl;
        return " ";
    }

    // Iterate until end
    while (getline(myfile, temp))
    {

        // Append current line to previous one
        str += temp;

        // Check if line is empty insert a space
        if (!temp.empty())
        {
            str += " ";
        }
    }

    // Close the file
    myfile.close();

    // Return the overall grid
    return str;
}

// Function to populate a grid from string
char **populateGrid(string str, int &str_row, int &str_col)
{
    int rows = 0, cols = 0;

    // Determine the number of columns
    for (int i = 0; str[i] != ' '; i++)
    {
        cols++;
    }

    // Determine the number of rows
    for (char c : str)
    {
        if (c == ' ')
            rows++;
    }

    // Allocate the 2D array for the grid
    char **grid = new char *[rows];
    for (int i = 0; i < rows; i++)
    {
        grid[i] = new char[cols];
    }

    // Filling the grid
    int r = 0, c = 0;
    for (char ch : str)
    {
        if (ch == ' ')
        {
            r++;
            c = 0;
        }
        else
        {
            grid[r][c++] = ch;
        }
    }

    //Setting values of rows and columns globally
    str_row = rows;
    str_col = cols;

    //Return the grid
    return grid;
}

// Function to show the grid
void showGrid(int rows, int cols, char **grid)
{
    // Nested loop for iteration
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            // Priting the corresponding element
            cout << grid[r][c] << " ";
        }

        // Move to next line for new row
        cout << endl;
    }
}

// Function to load the dictionary
void loadDictionary(Trie &wordTrie)
{

    // Read the dictionary file
    ifstream wordFile("wordList.txt");

    // Check if the file is found
    if (!wordFile)
    {
        cout << "Error: File not found.." << endl;
        return;
    }

    // Insert the words in trie
    string word;

    //>> skips whitespaces, newlines etc.
    while (wordFile >> word)
    {
        wordTrie.insert(word);
    }
    wordFile.close();
}

int main()
{
    // Reading the file from which we want to make the grid
    string str = ReadFile("grid.txt");

    // Check if the file exists
    if (str.empty())
    {
        cout << "Grid File not found.\nExting Program..." << endl;
    }

    // Populating the grid of Alphabets
    int rows, cols;
    char **grid = populateGrid(str, rows, cols);

    // Displaying the grid
    showGrid(rows, cols, grid);

    // Making Trie object to store dictionary
    Trie wordTrie;

    // Load the dictionary
    loadDictionary(wordTrie);

    // Creating graph object
    int numVertices = rows * cols;
    Graph<char> graph(numVertices, rows, cols, grid, wordTrie);

    // Creating the Adjacency Matrix
    graph.CreateAdjMatrix();


    //Infinite while loop
    while (1)
    {

        // Taking user input
        string word;
        cout << "Enter the word you want to search or type 'exit': ";
        cin >> word;

        // Creating new variable to store the capitalized word
        string newWord;
        newWord = word;

        // If small case then convert it into capital letters
        for (int i = 0; i < word.length(); i++)
        {

            // If letter is small then capitalize it
            if (word[i] >= 'a' && word[i] <= 'z')
            {
                newWord[i] = word[i] - 32;
            }

            // Copy the word as it is if already capital
            else
                newWord[i] = word[i];
        }

        //Exit the program if user wants to..
        if (newWord == "EXIT")
        {
            cout << "Exiting Program..."<<endl;
            break;
        }

        //Call depth First search to search the word
        if (graph.DepthFirstSearch(newWord))
        {
            cout << "Word Found.." << endl;
        }
        else
        {
            //In case word not found in grid
            cout << "Word not found.." << endl;
        }
    }

    //Function to solve the whole grid
    graph.solveGrid();
}
