#include "iostream"
#include "BinaryTree.h"
using namespace std;

int main() {

    BinaryTree marketSymbols;

    string testSymb;
    string findSymb;
    string buffer;
    char command;
    bool running = true;

    /*while(true) {
        cout << "Insert which symbol (quit to exit): " << endl;
        cin >> testSymb;
        if (testSymb.compare("quit") != 0) {
            cout << "Inserting " << testSymb << endl;
            marketSymbols.insert(testSymb);
        } else {
            cout << "Moving to finding stage" << endl;
            break;
        }
    }

    while (true) {

        cout << "Try to find what (quit to exit): " << endl; 
        cin  >> findSymb;

        if (findSymb.compare("quit") != 0) {
            cout << "Finding " << findSymb << endl;

            if (marketSymbols.find(findSymb)) {
            cout << "found" << endl;
            } else {
            cout << "Not there!" << endl;
            }
        } else {
            cout << "simulation over" << endl;
            break;
        }
    }*/

   
    /*int testValue;

    cout << "PLease enter a test value" << endl;
    cin >> testValue;

    cout << "test value: " << testValue << endl;*/


        while (running) {
                //command =         // reset command each time in loop
                cout << "Please enter a command ((i)nsert, "
                        << "(f)ind, (r)emove, (w)rite):  ";
                cin >> command;

                switch (command) {

                case 'i': {
                        cout << "Enter market Symbol to Insert:  ";
                        cin >> buffer;  // formatted input

                        /*cout << "Please enter UCSD student number:  ";
                        cin >> number;

                        UCSDStudent stu (buffer, number);*/

                        // create student and place in symbol table
                        marketSymbols.insert(buffer);
                        break;
                    }
                case 'f': { 
                        bool found;    // whether found or not

                        cout << "Please enter a Market Symbol to lookup:  ";
                        cin >> buffer;  // formatted input

                        found = marketSymbols.find(buffer);
                        
                        if (found)
                                cout << "Symbol Found: \n" << buffer << "\n";
                        else
                                cout << "Symbol: " << buffer << " not there!\n";
                        break;
                        }
                case 'r': { 
                        int removed;

                        cout << "Please enter Market Symbol to remove:  ";
                        cin >> buffer;  // formatted input

                        removed = marketSymbols.remove(buffer);

                        if (removed != 0)
                                cout << "Symbol removed!!!\n" << buffer << "\n";
                        else
                                cout << "Symbol: " << buffer << " not there!\n";
                        break;
                    }
                case 'w':{
                        marketSymbols.Write ();
                        break;
                }
                
                case 'q': {
                        marketSymbols.clear();
                        running = false;
                        break;
                    }
                }
        }


}
