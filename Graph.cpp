#include "Graph.h"

// Default Contructor
// Initialize attiributes to 0
template <typename T>
Graph<T>::Graph()
{
    numVertices = 0;
    Rows = 0;
    Cols = 0;
}

// Parameterized Constructor
// Assign values in class variables for matrix (graph)
template <typename T>
Graph<T>::Graph(int vertices, int rows, int cols, T **grid, Trie dictionary)
{

    numVertices = vertices;
    Rows = rows;
    Cols = cols;
    Grid = grid;
    Dictionary = dictionary;

    // Resize the matrix with the one passed
    adjMatrix.resize(vertices, vector<T>(vertices, 0));
}

// Destructor
// Destroy the object
template <typename T>
Graph<T>::~Graph(){}

// Function to add edge in undirected graph
template <typename T>
void Graph<T>::addEdge(int u, int v)
{

    // if the vertices are valid
    if (u >= 0 && u < numVertices && v >= 0 && v < numVertices)
    {
        //1 means there is an edge
        adjMatrix[u][v] = 1; 
        adjMatrix[v][u] = 1; 
    }
    else
    {
        //Print error
        cout << "Error: Invalid vertex index." << endl;
    }
}

// Remove an undirected edge between two vertices 
template <typename T>
void Graph<T>::removeEdge(int u, int v)
{
    if (u >= 0 && u < numVertices && v >= 0 && v < numVertices)
    {
        //0 means no edge
        adjMatrix[u][v] = 0;
        adjMatrix[v][u] = 0;
    }
    else
    {
        //Else print error
        cout << "Incorrect Index." << endl;
    }
}

// Display the graph
template <typename T>
void Graph<T>::display() const
{
    //Nested loop to iterate through all vertices
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            //Print the current vertex
            cout << " " << adjMatrix[i][j] << " ";
        }

        //Move to next line
        cout << endl;
    }
}

// Function to check if the edge exists
template <typename T>
bool Graph<T>::hasEdge(int u, int v) const
{

    //Checking if the indices are valid
    if (u >= 0 && u < numVertices && v >= 0 && v < numVertices)
    {

        //Bool return based on condition
        return (adjMatrix[u][v] == 1);
    }
    else
    {   
        //If indices not valid then return false
        cout << "\nError Invalid Index." << endl;
        return false;
    }
}


//Function to return the adjMatrix
template <typename T>
const vector<vector<T>> &Graph<T>::getAdjMatrix() const
{
    return adjMatrix;
}

//Function to return the number of vertices
template <typename T>
int Graph<T>::getNumVertices() const
{
    return numVertices;
}

// Function to get vertex at the current coordiantes
template <typename T>
int Graph<T>::getVertex(int r, int c, int cols) const
{
    return r * cols + c;
}

// Function to create Adjacency matrix
template <typename T>
void Graph<T>::CreateAdjMatrix()
{

    //Nested loop to iterate through each index
    for (int r = 0; r < Rows; r++)
    {
        for (int c = 0; c < Cols; c++)
        {
            // Getting the current vertex
            int current = getVertex(r, c, Cols);

            // Adding edges to neighbors
            if (r > 0)
                addEdge(current, getVertex(r - 1, c, Cols)); // Up
            if (r < Rows - 1)
                addEdge(current, getVertex(r + 1, c, Cols)); // Down
            if (c > 0)
                addEdge(current, getVertex(r, c - 1, Cols)); // left
            if (c < Cols - 1)
                addEdge(current, getVertex(r, c + 1, Cols)); // Right
            if(r>0 && c>0)
                addEdge(current, getVertex(r-1, c-1,Cols)); //Top-left
            if(r>0 && c<Cols-1)
                addEdge(current, getVertex(r-1, c+1, Cols)); //Top-Right
            if(r<Rows-1 && c>0)
                addEdge(current, getVertex(r+1, c-1, Cols)); //Bottom-left
            if(r<Rows-1 && c<Cols-1)
                addEdge(current, getVertex(r+1, c+1, Cols)); //Bottom-Right    
        }
    }
}

// Function to find the word using depthFirstSearch
template <typename T>
bool Graph<T>::DepthFirstSearch(const string &word)
{
    // Neighboring directions
    int direction[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    // Creating 2D vector array of bool type
    // In this for each row there are number of columns initially set to false
    vector<vector<bool>> visited(Rows, vector<bool>(Cols, false));

    // Nested loop to iterate through every element
    for (int r = 0; r < Rows; r++)
    {
        for (int c = 0; c < Cols; c++)
        {

            // If the first character matches
            if (Grid[r][c] == word[0])
            {

                // Create a stack having pairs
                // First element of pair is an int and second element is another pair of int
                stack<pair<int, pair<int, int>>> s;


                // Mark the current element as true
                visited[r][c] = true;

                // Push the element into stack first
                s.push({0, {r, c}});

                // Iterate until the stack is not empty
                while (!s.empty())
                {

                    // Storing the top of the stack element into variables
                    // In this case the first element would be stored in index and second in coord
                    auto [index, coord] = s.top();

                    // Pop the top element out of the stack
                    s.pop();

                    // Geting the row and column of the current stored element
                    int currRow = coord.first;
                    int currCol = coord.second;

                    // Return true if the word is found
                    if (index == word.size() - 1)
                    {
                        if(Dictionary.search(word))
                            return true;
                    }

                    // Iterate through every neighbor
                    for (int i = 0; i < 8; i++)
                    {

                        // Get the new rows and cols we want to check
                        int newRow = direction[i][0] + currRow;
                        int newCol = direction[i][1] + currCol;

                        // Making sure rows and cols are within bounds
                        if (newRow >= 0 && newRow < Rows && newCol >= 0 && newCol < Cols)
                        {

                            // If the node isn't visited and it matches the next character to the word
                            if (!visited[newRow][newCol] && Grid[newRow][newCol] == word[index + 1])
                            {

                                // Mark the element as true
                                visited[newRow][newCol] = true;

                                // Push into stack along with coordiantes
                                s.push({index + 1, {newRow, newCol}});
                            }
                        }
                    }
                }
            }
        }
    }

    // If none of the conditions are true
    return false;
}

//Function to search dictionary words from the grid
template<typename T>
void Graph<T>::BreathFirstSearch(Trie& dictionary)
{

    // Neighboring directions
    int direction[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};



    //Initialize a set to store found words
    unordered_set<string> foundWords;

    //Nested loop to iterate over every vertex
    for(int r = 0; r<Rows;r++)
    {
        for(int c = 0; c<Cols; c++)
        {
            //Creating an array to store the visited nodes
            //This is not initialized globally because we donot want it to change values 
            //for other words
            vector<vector<bool>> visited(Rows, vector<bool>(Cols, false));

            //Initializing a queue
            //First element string and second is coordinates
            queue<pair<string, pair<int, int>>> q;
            q.push({string(1, Grid[r][c]), {r, c}});

            //Mark the current vertex as true
            visited[r][c] = true;

            while(!q.empty())
            {

                //Storing queue's first element using structured binding
                auto [current, coord] = q.front();

                //Dequeueing
                q.pop();

                //Check if the word is in dictionary
                if(dictionary.search(current))
                {
                    //If so, insert in the set
                    foundWords.insert(current);
                }

                //Iterate through every direction
                for(int i = 0; i<8; i++)
                {

                    //Storing the new coordinates 
                    int newRow = coord.first + direction[i][0];
                    int newCol = coord.second + direction[i][1];

                    //Checking if the new coordinates are valid
                    if(newRow >= 0 && newRow <Rows && newCol>=0 && newCol< Cols)
                    {

                        //If so, check if they are visited 
                        //Also check if it concatinated with neighbor is a valid
                        if(!visited[newRow][newCol] && Dictionary.startsWith(current + string(1,Grid[newRow][newCol])) )
                        {

                            //Mark the current index as visited
                            visited[newRow][newCol] = true;

                            //Push the concatinated string with it's coordinates
                            q.push({current + string(1, Grid[newRow][newCol]), {newRow, newCol} } );
                        } 
                    }
                }
            }
        }
    }

    //Print all the words from the dictionary found in the grid
    cout<<"List of found words are: "<<endl;
    for(const string& word : foundWords)
    {
        cout<<word<<endl;
    }

}

//Function to solve the entire grid using Breadth First Search 
template<typename T>
void Graph<T>::solveGrid()
{

    //Call the BFS and pass the dictionary with it
    BreathFirstSearch(Dictionary);
}


// Explicit template instantiation for different types
template class Graph<int>;
template class Graph<double>;
template class Graph<char>;