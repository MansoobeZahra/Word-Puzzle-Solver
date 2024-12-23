#include "Trie.h"

// Default Constructor
Trie::Trie()
{
    // create a new node for root
    root = new TrieNode();
}

// Destructor
Trie::~Trie() {
    // deleteTrie(root);
}

// Insert Function
void Trie::insert(const string &word)
{

    // Set a pointer for root
    TrieNode *current = root;

    // Iterate through each alphabet
    for (char c : word)
    {
        // If the word already exists in the trie
        if (current->children.find(c) == current->children.end())
        {

            // If not then insert the character manually
            current->children[c] = new TrieNode();
        }

        // Move pointer to the next child
        current = current->children[c];
    }

    // After inserting the entire word, mark the end of the word
    current->isEndOfWord = true;
}

// Search Function
bool Trie::search(const string &word) const
{
    //Set a pointer for root
    TrieNode *current = root;

    //Iterate through 
    for (char c : word)
    {
        //If the current character is empty
        if (current->children.find(c) == current->children.end())
        {
            return false;
        }
        
        //Move to pointer to the next character
        current = current->children[c];
    }

    //Return true if end of word is reached
    return current->isEndOfWord;
}

//Function to check the starting prefix 
bool Trie::startsWith(const string& prefix)
{

    //Start from root
    TrieNode* current = root;

    //Iterate through each character
    for(char c: prefix)
    {

        //If current character is null
        if(current->children.find(c) == current->children.end())
        {

            //Return false if element not found
            return false;
        }
        
        //Move to child
        current = current->children[c];
    }

    //return true if successfully iterated and no null node found
    return true;
}

//Recursive Function to delete the trie
void Trie::deleteTrie(TrieNode* node)
{
    for(auto& c : node->children)
    {
        //keep moving to child
        deleteTrie(c.second);
    }

    //deleting current child
    delete node;
}