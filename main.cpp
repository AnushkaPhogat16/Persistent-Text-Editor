#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "Rope.h"

using namespace std;

int main(){

    //maintains rope versions
    vector<RopeNode*> versionHistory;
    int currVersion = 0;

    //start with empty text
    RopeNode* initial = buildRope("");
    versionHistory.push_back(initial);

    cout << " Welcome to Persistent Text Editor!\n";
    cout << "========================================\n";
    cout << " Available Commands: <3 \n";
    cout << "-----------------------------------------\n";
    cout << "  insert <pos> <text>  -- Insert text at position" << endl;
    cout << "  delete <pos> <len>   -- Delete len characters from pos" << endl;
    cout << "  print                -- Display current text" << endl;
    cout << "  undo                 -- Revert to previous version" << endl;
    cout << "  redo                 -- Reapply undone version" << endl;
    cout << "  exit                 -- Quit the editor" << endl;

    cout << "-----------------------------------------\n";
    cout << "Edit, save, and persist like a pro!\n";
    cout << "=========================================\n";


    string line;

    while(true){
        cout << ">";
        getline(cin, line);
        if(line.empty()) continue;;

        istringstream iss(line);
        string command;
        iss >> command;

        if(command == "insert"){
            int pos;
            iss >> pos;

            string text;
            getline(iss, text); 
            //Unlike iss >> textcaptures everything after pos inc _

            if(!text.empty() && text[0] == ' '){
                text.erase(0, 1);
            }
            RopeNode* current = versionHistory[currVersion];
            RopeNode* newVersion = insert(current, pos, text);

            if(currVersion != (int)versionHistory.size() - 1){
                versionHistory.resize(currVersion + 1);
            }
            versionHistory.push_back(newVersion);
            currVersion++;
        }
        else if(command == "print"){
            RopeNode* curr = versionHistory[currVersion];
            cout << toString(curr) <<endl;
        }
        else if(command == "undo"){
            if(currVersion > 0){
                currVersion--;
                cout<< "Undo performed <3" <<endl;
            }else{
                cout << "No earlier version. Cannot undo :( " <<endl;
            }
        }
        else if(command == "redo"){
            if(currVersion < (int)versionHistory.size() - 1){
                currVersion++;
                cout << "Redo performed <3" <<endl;
            }else{
                cout<<"No later version. Cannot redo :( "<<endl;
            }
        }
        else if(command == "delete"){
            int pos, len;
            iss >> pos >> len;

            RopeNode* current = versionHistory[currVersion];
            RopeNode* newVersion = deleteRange(current, pos, len);
            if(currVersion != (int)versionHistory.size() - 1){
                versionHistory.resize(currVersion + 1);
            }

            versionHistory.push_back(newVersion);
            currVersion++;
        }
        else if(command == "exit"){
            break;
        }
        else{
            cout<< "Invalid command :( "<< endl;
        }

    }


    return 0;
}