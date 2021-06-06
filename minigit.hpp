#ifndef MINIGIT_HPP
#define MINIGIT_HPP

#include <string>
using namespace std;

struct singlyNode{
    string fileName;
    string fileVersion;
    singlyNode* next = NULL;
    int numVersions = 0;
};

struct doublyNode{
    int commitNumber;
    singlyNode* head = NULL;
    doublyNode* previous = NULL;
    doublyNode* next = NULL;
};
 
 class minigitSystem{
    private:
        doublyNode* dHead;
        doublyNode* dTail;
        doublyNode* previousDLL;
        doublyNode* currentDLL;

    public:
    
        minigitSystem(); //Constructor
        ~minigitSystem();

        int getMaxNode(); //Getter functions
        int getCurrentNode();

        void addFile(string filename);
        void commit();
        void remove(string filename);
        void checkout(int checkNumber);
 };
#endif

//Have some sort of current integer.
//Everytime a commit is made, the tail node's commit number updates to be the new commit number of the tail node.
//If you do a checkout, the current integer's value updates. 
//If the tail node commit number is not equal to the commit integer, then add, remove, and commit is not allowed. 
//Allow the user to leave the checkout node within commit.