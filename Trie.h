#ifndef TRIE_H
#define TRIE_H
#include<unordered_map> //Imports unordered map from hashmap
#include<string>    //Import string
#include<bits/stdc++.h> //Imports all libraries

using namespace std;

//Making struct for tree node
struct TrieNode{
    public:

    //Flag to check the word's end
    bool isEndOfWord;

    //Using unordered hash map for children
    //Because it would provide O(1) search time for children
    unordered_map<char, TrieNode*> children;

    //Constructor 
    TrieNode(){
        isEndOfWord = false;
    }
};


class Trie
{
    public:
        //Name: Trie
        //Purpose: Default Constructor
        //Return: None
        //Parameters: None
        Trie();

        //Name: ~Trie
        //Purpose: Destructor
        //Return: None
        //Parameters: None
        virtual ~Trie();

        //Name: insert
        //Purpose: insert a word in trie structure
        //Return: none
        //Parameters: Word we want to insert
        void insert(const string& word);

        //Name: search
        //Purpose: search a word in trie structure
        //Return: bool return based on word found
        //Parameters: Word we want to search
        bool search(const string& word) const;

        //Name: startsWith
        //Purpose: Check if the prefix passed is valid
        //Return: bool return based on check
        //Parameters: prefix who's validity we want to check
        bool startsWith(const string& prefix);

        //Name: deleteTrie
        //Purpose: delete the trie
        //Return: none
        //Parameters: Node from where we want to start deletion
        void deleteTrie(TrieNode* node);

    protected:

    private:

        //Pointer to root
        TrieNode* root;

        
};

#endif // TRIE_H
