#include <iostream>
#include <fstream>
#include <filesystem>
#include "minigit.hpp"

namespace fs = std::filesystem;
using namespace std;

void displayMenu2();
void displayMenu1();
void runProgram();
bool validNodeChecker(int commitNum1, int commitNum2);

int main(){

    cout << "Welcome to Minigit!" << endl;
    displayMenu1();

    string init;
    cin.clear();
    getline(cin, init);

    while(true){
        if(init == "1" || init == "2"){
            int initConversion = stoi(init);

            switch(initConversion){
                case 1: {
                    runProgram();
                    return 0;
                }
                case 2: {
                    cout << "Quitting Minigit. Goodbye!" << endl;
                    return 0;
                }

            }
        }
        else{
            cout << "Invalid selection. Please choose a valid option." << endl;
            cout << endl;
            displayMenu1();
            cin.clear();
            getline(cin, init);
        }
    }
}

void runProgram(){
    minigitSystem initialize;

    string selection = "";
    while(selection != "5"){
        int currentCN = initialize.getCurrentNode();
        int tailCN = initialize.getMaxNode();

        displayMenu2();
        cin.clear();
        getline(cin, selection);

        if(selection == "1" || selection == "2" || selection == "3" || selection == "4" || selection == "5"){
            int selectionConvert = stoi(selection);

            switch(selectionConvert){
                case 1: {
                    //Get user input for the file's name
                    if(currentCN != tailCN){
                        cout << "You cannot make changes to this commit." << endl;
                        cout << "To make changes, go to checkout for commit number " << tailCN << '.' << endl;
                        break; 
                    }
                    cout << "Please enter the file's name: " << endl;
                    string filename;
                    getline(cin, filename);
                    bool found = false;
                    while(found != true){
                        found = fs::exists(filename);
                        if(found == false){
                            cout << "Invalid file name. Please enter a valid file name: " << endl;
                            getline(cin, filename);
                        }
                        else{
                            //call the addFile function.
                            initialize.addFile(filename);
                            found = true;
                        }
                    }
                    break;
                }
                case 2: {
                    if(currentCN != tailCN){
                        cout << "You cannot make changes to this commit." << endl;
                        cout << "To make changes, checkout commit number " << tailCN << endl;
                        break; 
                    }
                    cout << "Please enter the file's name: " << endl;
                    string filename;
                    getline(cin, filename);

                    bool found = false;
                    while(found != true){
                        found = fs::exists(filename);
                        if(found == false){
                            cout << "Invalid file name. Please enter a valid file name: " << endl;
                            getline(cin, filename);
                        }
                        else{
                            //call the remove function.
                            initialize.remove(filename);
                            found = true;
                        }
                    }
                    break;
                }
                case 3: {
                    if(currentCN != tailCN){
                        cout << "You cannot make changes to this commit." << endl;
                        cout << "To make changes, checkout commit number " << tailCN << '.' << endl;
                        break; 
                    }
                    initialize.commit();
                    break;
                }
                case 4: {
                    cout << "Please enter the commit number of the version you'd like to go to: " << endl;
                    string commitNum;
                    getline(cin, commitNum);

                    while(true){
                        bool valid = true;
                        for(int i = 0; i < commitNum.length(); i++){
                            if(isdigit(commitNum[i]) == false){
                                valid = false;
                                break;
                            }
                        }
                        if(valid == true){
                            initialize.checkout(stoi(commitNum));
                            break;
                        }
                        else{
                            cout << "Invalid Commit Number. Please enter a valid commit number: " << endl;
                            getline(cin, commitNum);
                        }
                    }
                    break;
                }
                case 5: {
                    cout << "Quitting. Thanks for the memories!" << endl;
                    return;
                }
            }
        }
        else{
            cout << "Invalid selection. Please choose a valid option." << endl;
            cout << endl;
            displayMenu2();
            cin.clear();
            getline(cin, selection);   
        }
    }
}

void displayMenu1(){
cout << "An empty repository is required for the use of minigit." << endl;
cout << "Would you like to initialize an empty repository? " << endl;
cout << "__________________________________" << endl;
cout << endl;
cout << "1. Yes" << endl;
cout << "2. No" << endl;
}

void displayMenu2(){
    cout << "Please pick an option: " << endl;
    cout << "__________________________________" << endl;
    cout << endl;
    cout << "1. Add Files" << endl;
    cout << "2. Remove Files" << endl;
    cout << "3. Commit Changes" << endl;
    cout << "4. Checkout" << endl;
    cout << "5. Quit" << endl;
}

bool validNodeChecker(int commitNum1, int commitNum2){
    if(commitNum1 == commitNum2){
        return true;
    }
    else{
        return false;
    }
}

