//
//  Project 1 Starter Code - DNA Profiling
//  TODO:  Put your header info here.  Update line above.
//  
//

#include "ourvector.h"
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

void printCharVec(ourvector<ourvector<char>> loaded_charVec, ourvector<int> strCounts) {
    for (int j = 0; j < loaded_charVec.size(); j++) {
        for( int k = 0; k < loaded_charVec[j].size(); k++) {
            cout << loaded_charVec[j][k];
        }
        cout << ": "<< strCounts[j] << endl;
    }
}


void printStrVec( ourvector<ourvector<string>> loaded_db) {
    for (int i = 0; i < loaded_db.size(); i++) {
        for (int j = 0; j < loaded_db[i].size(); j++) {
            cout << loaded_db[i][j] << " ";
        }
        cout << endl;
    }
}

void display(const ourvector<ourvector<string>> loaded_db, ourvector<char> loaded_dna, ourvector<ourvector<char>> loaded_str, ourvector<int> processed_counts) {
    
    if (loaded_db.size()) {
        cout << "Database loaded:"<< endl;
        printStrVec(loaded_db);
        cout << endl;
    }
    else {
        cout << "No Database loaded." << endl;
    }

    if (loaded_dna.size()) {
        cout << "DNA loaded:" << endl;
        for (int i = 0; i < loaded_dna.size(); i++) {
            cout << loaded_dna.at(i);
        }
        cout << endl;
    }
    else {
        cout << "\nNo DNA loaded.\n" << endl;
    }
    
    if (processed_counts.size()) {
        cout << "\nDNA processed, STR counts:" << endl;
        printCharVec(loaded_str, processed_counts);
    }
    else {
        cout << "No DNA has been processed." << endl;
    }
    
}

void strParse(ourvector<ourvector<char>>& strVec, string str) {
    istringstream ss(str);
    ourvector<char> temp;
    string tmp;
    char str_dna;

    getline(ss, tmp, ',');
    while (getline(ss, tmp, ',')){
        for (int i = 0; i < tmp.length(); i++) {
            temp.push_back(tmp[i]);
        }
        
        strVec.push_back(temp);
        temp.clear();
    }
    //DEBUGGING
    // for (int j = 0; j < strVec.size(); j++) {
    //     for( int k = 0; k < strVec[j].size(); k++) {
    //         cout << strVec[j][k] << " ";
    //     }
    //     cout << endl;
    // }
}

void db_strParse(ourvector<ourvector<string>>& vec, string str){
    istringstream ss(str);
    ourvector<string> temp;
    string tmpStr;

    while (getline(ss, tmpStr, ',')){
        temp.push_back(tmpStr);
    }
    vec.push_back(temp);
}

bool fileNotOpen(ifstream& inFS, string fileName) {
    if (!inFS) {
        cout << "Error: unable to open \'" << fileName << "\'" << endl;
        return true;
    }
    return false;
}

bool file_open(ifstream& inFS, int db_or_dna) {
    
    string fileName;
    
    cin >> fileName;
    if (db_or_dna) {
        cout << "Loading database...\n";
    }
    else {
        cout << "Loading DNA...\n";
    }
    inFS.open(fileName);

    if (fileNotOpen(inFS, fileName)) {
        return false;
    }
    return true;
}

void load_db(ourvector<ourvector<string>>& db_info, ourvector<ourvector<char>>& str_info) {
    ifstream inFS;
    string fileLine;

    db_info.clear();
    if (!file_open(inFS, 1)) {
        return;
    }
    
    getline(inFS,fileLine);
    strParse(str_info, fileLine);
    while(!inFS.eof()) {
        getline(inFS,fileLine);
        if(fileLine.length()==0) {
            break;
        }
        db_strParse(db_info, fileLine);
    }
    
}

void load_dna(ourvector<char>& dna_info) {
    ifstream inFS;
    string dnaLine;

    dna_info.clear();
    file_open(inFS, 0);
    getline(inFS, dnaLine);
    for (int i = 0; i < dnaLine.length(); i++) {
        dna_info.push_back(dnaLine.at(i));
    }
}
bool adjacency(int previous, int current, string word) {
    if (current == (previous + word.length())) {
        return true;
    }
    return false;
}
void process_dna(ourvector<ourvector<char>> loaded_str, ourvector<char> loaded_dna, ourvector<int>& results) {
    results.clear();
    ostringstream dnaStream;
    ostringstream strStream;
    for ( char c: loaded_dna) {
        dnaStream << c;
    }
    string dna_string(dnaStream.str());
    if (loaded_str.size() == 0) {
        cout << "No database loaded." << endl;
        return;
    }
    if (loaded_dna.size() == 0) {
        cout << "No DNA loaded." << endl;
        return;
    }
    cout << "Processing DNA..." << endl;
    for (int i = 0; i < loaded_str.size(); i++) {
        for ( char e: loaded_str[i]) {
            strStream << e;
        }
        string str_string(strStream.str());
        int str_size = str_string.length();
        int counter = 0;
        strStream.str("");
        strStream.clear();
        int found = dna_string.find(str_string);
        // cout << str_string << ": " << found << endl;
        
        while (found >= 0) {
            int prevFound = found;
            found = dna_string.find(str_string, found + 1);
            // if (!adjacency(prevFound, found, str_string)) {
            //     counter = 0;
            // }
            counter++;
        }
        results.push_back(counter);
    }
    
}

int main() {
    
    
    string userCommand;
    ourvector<ourvector<string>> current_db;
    ourvector<char> current_dna;
    ourvector<ourvector<char>> current_str;
    ourvector<int> dna_str_results;
    
    cout << "Welcome to the DNA Profiling Application." << endl;
    while(1) {
        cout << "Enter command or # to exit: ";
        cin >> userCommand;
        if (userCommand == "#") {
            break;
        }
        else if ( userCommand == "load_db") {
            load_db(current_db, current_str);
            
        }
        else if ( userCommand == "display") {
            display(current_db, current_dna, current_str, dna_str_results);
            
        }
        else if ( userCommand == "load_dna") {
            load_dna(current_dna);
        }
        else if ( userCommand == "process") {
            process_dna(current_str, current_dna, dna_str_results);
        }
    }
    

    return 0;
}
