#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include "minigit.hpp"

using namespace std;
namespace fs = std::filesystem;

//HELPER FUNCTIONS
void projectPrinter(doublyNode* startingNode){
    cout << "Here's some information about the files in your commits: " << endl;

    doublyNode* tempNodeDLL = startingNode;
    cout << "_________________________________" << endl;
    while(tempNodeDLL->next != NULL){
        cout << "Commit Number:" << tempNodeDLL->commitNumber << endl; 
        singlyNode* tempNodeSLL = tempNodeDLL->head;
       
       cout << "SLL files from head to tail: " << endl;
       while(tempNodeSLL != NULL){
           cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
           cout << "Filename: " << tempNodeSLL->fileName << endl;
           cout << "File Version: " << tempNodeSLL->fileVersion << endl;

           tempNodeSLL = tempNodeSLL->next;
       }
       cout << "_________________________________" << endl;
       cout << endl;
       tempNodeDLL = tempNodeDLL->next;
    }

    cout << endl;
    cout << endl;
}


void sllPrinter(doublyNode* printNode){
    cout << "Files which will be committed next:" << endl;
    cout << "----------------------------------" <<endl;
    singlyNode* tempNode = printNode->head;

    while(tempNode != NULL){
        cout << tempNode->fileName << endl;

        tempNode = tempNode->next;
    }
}
//true = files are same; false = files are different.
bool sameFileChecker(string directoryFilename, string minigitFilename){
    ifstream directoryFile(directoryFilename);
    ifstream minigitFile(minigitFilename);

    string directoryLine;
    string minigitLine;

    vector<string> dLine;
    vector<string> mLine;

    while(getline(directoryFile, directoryLine)){
        dLine.push_back(directoryLine);
    }

    while(getline(minigitFile, minigitLine)){
        mLine.push_back(minigitLine);
    }

    if(dLine.size() !=  mLine.size()){
        return false;
    }
    else{
        for(int i = 0; i < dLine.size(); i++){
            if(dLine[i] != mLine[i]){
                cout << "A difference was found." << endl;
                return false;
            }
        }
    }
//If we get to this point, the files must be the same.
return true;
}

void copyFilesOver(doublyNode* nodeToCopy){
    singlyNode* tempNode = nodeToCopy->head;

    while(tempNode != NULL){
        if(fs::exists(tempNode->fileName) == true){ 
            //Check if the files are the same. If not, change the files
            if(sameFileChecker(tempNode->fileName, tempNode->fileVersion) == false){
                //Copy the new file over
                ifstream minigitFile; //Input file (the file version in .minigit)
                minigitFile.open(".minigit/" + tempNode->fileVersion);
                string line;
                
                ofstream directoryFile;
                directoryFile.open(tempNode->fileName, ofstream::out | ofstream::trunc); //Opens the directory file, which is clear.

                while(getline(minigitFile, line)){
                    directoryFile << line << endl; //Copying each file from fileversion to official file.
                }
                minigitFile.close();
                directoryFile.close();
            } 
            else{
                continue; //Files are the same and no changes are needed.
            }

        }
        else{ //File does not exist and must be recreated
            ofstream newDirectoryFile;
            newDirectoryFile.open(tempNode->fileName);

            ifstream minigitFile2;
            minigitFile2.open(".minigit/" + tempNode->fileVersion);
            string line2;

            while(getline(minigitFile2, line2)){
                newDirectoryFile << line2 << endl;
            }

        }

        tempNode = tempNode->next;
    }                 
}

//_________________________________________________________________//
//CLASS FUNCTIONS

minigitSystem::minigitSystem(){
    fs::remove_all(".minigit"); //removes existing directory
    fs::create_directory(".minigit"); //creates new directory

    singlyNode* firstSNode = new singlyNode;
    firstSNode->fileName = "";
    firstSNode->fileVersion = "";
    firstSNode->next = NULL;

    //Create a doubly linked list with a single head node.
    doublyNode* firstDNode = new doublyNode;
    firstDNode->commitNumber = 0;
    firstDNode->next = NULL;
    firstDNode->previous = NULL;
    firstDNode->head = firstSNode;

    dHead = firstDNode; //Since this is the first DLL Node in the program, it is both the head and the tail.
    dTail = firstDNode;

    currentDLL = dTail;
}

minigitSystem::~minigitSystem(){

}

void minigitSystem::addFile(string userFilename){
//2 Situations:
//First node being added: the creation of a new SLL
//Node being added to an existing linked list.

    singlyNode* tempNode = dTail->head;

    //Goes through each node of the SLL and checks whether the file exists.
    while(tempNode != NULL){
        if(tempNode->fileName == userFilename){
            cout << endl;
            cout << "File with that name already exists in the directory. No changes made." << endl;
            cout << endl;
            return;
        }
        tempNode = tempNode->next;
    }

    //If the program makes it here, the file does not currently exist in the list. We create a new node.
    singlyNode* prev = NULL;
    singlyNode* newNode = new singlyNode;

    newNode->fileName = userFilename; //Name of input file
    newNode->numVersions = newNode->numVersions++;//File version (Numerical value)
    newNode->fileVersion = to_string(newNode->numVersions) + "_" + userFilename; //Name of repository file
    newNode->next = NULL;//Pointer to next node

    //If the SLL is empty
    if(dTail->head->fileName == ""){
        delete dTail->head;
        dTail->head = newNode;
    }
    else{ //SLL is not empty
        tempNode = dTail->head;
        while(tempNode != NULL){
            prev = tempNode;
            tempNode = tempNode->next;
        }
        //At this point, tempNode should be NULL and prev should be the last node of the SLL.
        prev->next = newNode; //newNode is now the last node of the SLL.
    }
    cout << endl;
    cout << "SUCCESS: " + userFilename + " has been added to the repository." << endl;
    cout << endl;

    sllPrinter(dTail);
    cout << endl;
}

void minigitSystem::commit(){
//Go through current linked list:
    singlyNode* tempNode = dTail->head;

    while(tempNode != NULL){
        //A. Corresponding fileVersion exists in .minigit (First time only)  
        if(fs::exists(".minigit/" + tempNode->fileVersion) == false){
            //fileVersion file does not exist in .minigit. We must create a new file.
            //Copy all contents of the directory file.
            ifstream directoryFile;
            directoryFile.open(tempNode->fileName); //Input file
            ofstream minigitFile(".minigit/" + tempNode->fileVersion); //Output file
            string line;

            if(directoryFile.is_open() == true){
                while(getline(directoryFile, line)){
                    minigitFile << line << endl;
                }
                directoryFile.close();
                minigitFile.close();
            }
            else{
                cout << "File is not open. No changes made." << endl;
            }
        }
    //B. fileVersion does exist in .minigit       
        else if(fs::exists(".minigit/" + tempNode->fileVersion) == true){
            bool same = sameFileChecker(tempNode->fileName, ".minigit/" + tempNode->fileVersion);

            if(same == false){ //If the file is different, copy the new file to minigit with an incremented file number.
                tempNode->numVersions++;
                tempNode->fileVersion = to_string(tempNode->numVersions) + "_" + tempNode->fileName;

                ifstream directoryFile;
                directoryFile.open(tempNode->fileName); //Input file
                ofstream minigitFile(".minigit/" + tempNode->fileVersion);
                string line;

                if(directoryFile.is_open() == true){
                    while(getline(directoryFile, line)){
                        minigitFile << line << endl;
                    }
                    directoryFile.close();
                    minigitFile.close();                 
                }
                else{
                    cout << "File is not open. No changes made." << endl;
                }
            }
        }
        tempNode = tempNode->next;
    }

    //Now that files have been updated, it is time to create a new DLL node with a deep copy of the previous SLL.
    tempNode = dTail->head; //Reset tempNode before changing the DLL's tail.
    
    doublyNode* newDoublyNode = new doublyNode; //Allocates memory for new node.
    newDoublyNode->commitNumber = dTail->commitNumber + 1; //New commit number is one greater than the previous node's commit number.
    newDoublyNode->next = NULL;
    newDoublyNode->previous = dTail; //The tail is now the new node.
    dTail->next = newDoublyNode; //Current tail's next is now the new tail.
    dTail = newDoublyNode; //The new node is the new tail.

    while(tempNode != NULL){
        singlyNode* newSinglyNode = new singlyNode;

        //Copy tempNode information over to the new SLL node for deep copy.
        newSinglyNode->fileName = tempNode->fileName;
        newSinglyNode->fileVersion = tempNode->fileVersion;
        newSinglyNode->next = NULL;
        newSinglyNode->numVersions = tempNode->numVersions; 

        //Add the deep copy to the new DLL's SLL.
        if(dTail->head == NULL){ //For the first node being copied over.
            dTail->head = newSinglyNode;
        }
        else{//Node should be added to the end of the list.
            singlyNode* curr = dTail->head;
            singlyNode* prev = NULL;

            while(curr != NULL){
                prev = curr;
                curr = curr->next;
            }
            //At this point, curr should be NULL
            curr = newSinglyNode;
            prev->next = curr;
        }

        tempNode = tempNode->next;
    }
    currentDLL = dTail; //Updates the current DLL node
    projectPrinter(dHead);
}

void::minigitSystem::remove(string filename){
    singlyNode* curr = dTail->head;
    singlyNode* prev = NULL;

    while(curr != NULL){
        if(curr->fileName == filename){
        //3 Conditions:
            //1. Node to remove is the head node
            if(prev == NULL){
                prev = curr->next;
                delete curr;
                dTail->head = prev;

                //Resetting the original, blank, single node

                if(dTail->head == NULL){
                    singlyNode* replace = new singlyNode;
                    replace->fileName = "";
                    replace->fileVersion = "";
                    replace->next = NULL;
                    replace->numVersions = 0;

                    dTail->head = replace;
                }

                cout << endl;
                cout << "SUCCESS: " << filename + " has been removed from the repository." << endl;
                cout << endl;
                return;
            }
            //2. Node to remove is the tail node
            else if(curr->next == NULL){
                prev->next = NULL;
                delete curr;

                cout << endl;
                cout << filename + " was successfully removed." << endl;
                cout << endl;
                return;
            }
            //3. Node to remove is in the middle
            else{
                prev->next = curr->next;
                delete curr;

                cout << endl;
                cout << filename + " was successfully removed." << endl;
                cout << endl;
                return;
            }     
        }
  
        prev = curr;
        curr = curr->next;
    }

    //If we get here, the filename was not found.
    cout << endl;
    cout << filename + " was not found. No changes were made." << endl;
    cout << endl;
}

void minigitSystem::checkout(int checkNumber){
    //Check if the number is a valid number. checkNumber should be between 0 and the commit number of the tail.

    if(checkNumber > dTail->commitNumber | checkNumber < 0){
        cout << "Commit number out of range!" << endl;
        cout << "NOTE: The largest commit number at the moment is " << dTail->commitNumber << '.' <<endl;
        cout << "      The smallest commit number is 0." << endl;
        cout << endl;
        return;
    }
    else{ //Warn the user that they will lose all of their local changes...
        if(currentDLL->commitNumber == dTail->commitNumber){
            cout << "WARNING: If you checkout another node without committing, any local changes you made after your previous commit will be erased. ";
            cout << "If you understand this risk, type CONTINUE (case sensitive) below." << endl;

            string understand;
            getline(cin, understand);
            cout << endl;
            if(understand != "CONTINUE"){
                cout << "You will remain at the current node. I'm sending you to the main menu." << endl;
                return;
            }            
        }
            cout << "Commencing Checkout." << endl;
            cout << endl;
    }

    //- The number is the current node's commit number
    if(checkNumber == currentDLL->commitNumber){
        cout << "You are already at that commit number!" << endl;
        cout << endl;
        return;
    }
    //- The number is less than the current node's number.  
    else if(checkNumber < currentDLL->commitNumber){
        //traverse backwards
        while(currentDLL->commitNumber != checkNumber){ //Takes the current node to the desired one.
            currentDLL = currentDLL->previous;
        } 
        //Now the program should go through the linked list and copy over files.
        copyFilesOver(currentDLL);

    }
    else if(checkNumber > currentDLL->commitNumber){
        //traverse forwards
        
        while(checkNumber > currentDLL->commitNumber){
            currentDLL = currentDLL->next;
        }

        copyFilesOver(currentDLL);
    }

}

int minigitSystem::getMaxNode(){
    return dTail->commitNumber;
}

int minigitSystem::getCurrentNode(){
    return currentDLL->commitNumber;
}