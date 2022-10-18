// @author Mohammed Abdulaziz
// @date 10/02/22
// @brief Primitive search engine which mimics the process of early 2000's search engines
//        as well as uses an inverted index in order to make searching much more optimized.

#pragma once

#include <iostream>
#include <string>
#include <set>
#include <map>
#include <sstream>
#include <fstream>
#include <random>
using namespace std;

//This function checks whether there is an alphabet character in a string or not
int anyAlphaCheck(string str) {
    for (char c : str) {
        if(isalpha(c)) {
            return true;
        }
    }
    return false;
}

// This funciton reverses a string that is inputted and returns that value
string reverseStr(string& str)
{
    string rev = "";
    //loops in reverse to append last character into seperate string which is returned at end of string
    for (int i = str.length()-1; i >= 0; i--) {
        rev += str[i];
    }
    return rev;
}

// This function trims the beginning of a string of anything that triggers the ispunct() function and removes it until it reaches a character that does not at which point the word has started and exits loop
string rtrim(string& word) {
    // If word doesnt have any letter than returns and empty string
    if (!anyAlphaCheck(word)) {
        return "";
    }
    int i = 0;
    int wordStart = 0;
    for (char c : word) {
        // loops through each character and if it is a punctuation then increments the counter
        if ( ispunct(c) && wordStart != 1) {
            i++;
        }
        // If the character is not a punctuation or the word has started then break out the for loop
        else {
            wordStart = 1;
            break;
        }
    }
    // erase the number of characters away from the start as there is on the punctuation counter in order to return a word with the front punctuation removed
    word.erase(0,i);
    return word;
}

// This function simply reverses a string and uses the rtrim function to trim the back portion of the original string and reverses that in order to get a trimmed back portion
// This saves on time and doesn't repeat unnecessary calls or loops
string ltrim(string& word) {
    if (word == "") {
        return "";
    }
    string revWord = reverseStr(word); // reverses string
    string trimmedWord = rtrim(revWord);  // uses rtrim to trim reversed string
    string final = reverseStr(trimmedWord);  //reveses back the reversed string back to the original orientation to get a trimmed back portion of the original string
    return final;
}

// This function simply runs the back trimmer and the front trimmer and returns the completely trimmed string
string trimmer(string& word) {
    string first = ltrim(word);
    string last = rtrim(first);
    return last;
}

//This function simply loops through the string and lowercases every character that triggers isalpha()
string lowerStr(string& str) {
    for ( int i = 0; i < str.length(); i++) {
        if ( isalpha(str[i])) {
            str[i] = tolower(str[i]);
        }
    }
    return str;
}

// This function trims the front and back of a string literal of any punctuation, however does not remove punction thats in the middle of the string literal
string cleanToken(string s) {
    string token = s;
    string cleanedStr = "";
    if (token == "") {
        return "";
    }
    string trimmed = trimmer(token); 
    cleanedStr = lowerStr(trimmed);
    return cleanedStr;
}

// This function interates through string parameter and returns a set of the white space seperated strings, or "words", within the given parameter
set<string> gatherTokens(string text) {
    set<string> tokens;
    istringstream ss(text);
    string textToken;
    string temp = "";

    while(getline(ss, textToken, ' ')) {
        temp = cleanToken(textToken);
        if (!(temp == "")) {
            tokens.insert(temp);
        }
    }
    return tokens;
}

//Helper function mainly created to keep cycles low but also simplifies buildIndex operation
void indexSorting(string websiteLine, set<string>& websiteSet, set<string> cleanedTokens, set<string>& uniqueTokens, map<string, set<string>>& index) {
    for ( string str : cleanedTokens) {
        // loops through each token and if it is able to succesfully insert the token into a set, then that means it is a first time occurance and can be inserted into the final map
        // otherwise if it is not a first time occurance then insert will fail and result in a false which should then make a copy of the current websites at that index
        // in the map so that it can add the current website the for loop is on and insert it into the copy, then re-insert the updated website set alogn with the current token
        // into the final map
        if (uniqueTokens.insert(str).second == true) {
            index.emplace(str, websiteSet);
        }
        else {
            set<string> copy = index.at(str);
            copy.insert(websiteLine);
            index.erase(str);
            index.emplace(str, copy);
        }
    }
}

// This function will open the file in parameter and parse data to be stored in a map<string, set<string>>  format
int buildIndex(string filename, map<string, set<string>>& index) {
    ifstream inFS;     // file is opened
    string websiteLine;
    string fileLine;
    set<string> uniqueTokens;
    set<string> websiteSet; // set to store appropriate website as well as to have inserted into map
    int webpageCounter = 0;
    inFS.open(filename);
    if (!inFS) {
        // If file doesn't open then just return 0
        return 0;
    }
    while(!inFS.eof()) {
        getline(inFS, websiteLine);  // firs grabs the website and if it is "" which usually happens at the bottom of the .txt file then exit
        if (websiteLine == "") {
            break;
        }
        websiteSet.insert(websiteLine);
        getline(inFS, fileLine);
        set<string> temp = gatherTokens(fileLine); // grabs body text and parses the single string literal into a set of unique words from within that string
        indexSorting(websiteLine, websiteSet, temp, uniqueTokens, index); // calls function to keep cycles low
        webpageCounter++; // end result counter
        websiteSet.clear(); // clears set because we do not need to acummulate websites which may not belong to its appropriate body text
    }
    return webpageCounter;
}

//Helper function which results in the set that contains elements from both a or b
set<string> setUnion(set<string>& a, set<string>& b) {
    set<string> result = a;
    for (string str: b) {
        result.insert(str);
    }
    return result;
}

//Helper function which results in the set that contains elements of a that are also in b
set<string> setIntersection(set<string>& a, set<string>& b) {
    set<string> temp = a;
    set<string> result;
    for (string str : b) {
        if (temp.count(str)) {
            result.insert(str);
        }
    }
    return result;
}

//Helper function which results in the set that contains elements of a but not b
set<string> setDifference(set<string>& a, set<string>& b) {
    set<string> result = a;
    for (string str : b) {
        if (a.count(str)) {
            result.erase(str);
        }
    }
    return result;
}

// This function takes a map of string, set key-value pairs and a string which should contain keywords
set<string> findQueryMatches(map<string, set<string>>& index, string sentence) {
    set<string> result;
    istringstream ss(sentence); // key word string is loaded into input buffer
    string sentenceToken;
    string prevTerm = "";
    string currTerm = "";

    while(getline(ss, sentenceToken, ' ')) {
        // breaks up the key word string into tokens
        currTerm = sentenceToken;
        // looks at the first character of each token and if it has a '+' or '-' then do the appropriate operations
        if (currTerm[0] == '+') {
            string cleanedQuery = cleanToken(sentenceToken);
            if (index.count(cleanedQuery)) {
                set<string> cleanedQueryResults = index.at(cleanedQuery);
                result = setIntersection(result, cleanedQueryResults); // should result in the set that contains websites relevant to both key words
            }
        }
        else if (currTerm[0] == '-') {
            string cleanedQuery = cleanToken(sentenceToken);
            if (index.count(cleanedQuery)) {
                set<string> cleanedQueryResults = index.at(cleanedQuery);
                result = setDifference(result, cleanedQueryResults); // should result in the set that contains websites from the former but removes websites that are from the latter parameter
            }
        }
        else {
            string cleanedQuery = cleanToken(sentenceToken);
            if (index.count(cleanedQuery)) {
                set<string> cleanedQueryResults = index.at(cleanedQuery);
                result = setUnion(result, cleanedQueryResults); // should by default, unless triggered by previous if conditions, add the current result set with the previous result set if there are multiple key words
            }
        }
        prevTerm = currTerm;
    }
    return result;  
}
// Helper function that recreates the "I'm feeling lucky" button as seen on Google with whatever index has been loaded at the time
set<string> feelingLucky( map<string, set<string>>& index, string& luckyWord) {
    srand(time(0));   // sets randomness
    set<string> luckResults;
    int indexNum = index.size();
    int counter = 0;
    int randomNum = rand()%indexNum;
    // Loops through index until the random number has been reached at which point return the set of random index
    for (auto x : index) {
        if (counter == randomNum) {
            luckyWord= x.first;   // saves the random word and saves the results for the related websites for said random word
            luckResults = x.second;
            return luckResults;
        }
        counter++;
    }
    return luckResults; // return set of related websites to random word
}
// CREATIVE COMPONENT SECTION
// This function essentially calls another function to get a random word from the index loaded and outputs all the search results for that random word as well as display what that word was
void creativeComponent(string& userInput, map<string, set<string>> index) {
    string luckyWord = "";
    set<string> luckResults = feelingLucky(index, luckyWord);
    cout << "Found " << luckResults.size() << " matching pages for " << luckyWord << endl;
    for (string relevantSites : luckResults) {
        cout << relevantSites << endl;  // lists out relevant websites from random search
    }
}

void creativeSearch(string filename, string userInput, map<string, set<string>>& index) {
    while (1) {
        // very similar to the normalSearch function only difference is that it has the creative component implementation
        if ( userInput == "") {
            break;
        }
        cout << endl << "Enter query sentence, or type 'random' if you're Feeling Lucky!(press enter to quit): ";
        getline(cin, userInput);
        if (userInput == "") {
            break;
        }
        else if (lowerStr(userInput) == "random") {
            creativeComponent(userInput, index);   // RUNS creative component that calls the code written to implement the "I'm Feeling Lucky" feature that Google has on their homepage
        }
        else {
            set<string> results = findQueryMatches(index, userInput);  // runs Query here and saves size in next line to be shown to user
            int numResults = results.size();
            cout << "Found " << numResults << " matching pages" << endl;
            for (string relevantSites : results) {
                cout << relevantSites << endl;  // lists out relevant websites
            }
            results.clear(); // resets results for next search
        }
    }
}
//This is the normal search that hes digest larger operations into more readable code
void normalSearch(string filename, string userInput, map<string, set<string>>& index) {
    while (1) {
        // used 1 as while loop condition because it is much easier to just break it when I meet my conditons
        cout << endl << "Enter query sentence (press enter to quit): ";
        getline(cin, userInput);  // used to detect if userinput is "" which means user pressed enter only
        if (userInput == "") {
            break;
        }
        else {
            set<string> results = findQueryMatches(index, userInput);  // runs Query here and saves size in next line to be shown to user
            int numResults = results.size();
            cout << "Found " << numResults << " matching pages" << endl;
            for (string relevantSites : results) {
                cout << relevantSites << endl;  // lists out relevant websites
            }
            results.clear(); // resets results for next search
        }
    }
}
// This function will build an index out of the given input file and will use that parsed data to return sets that contain
// relevant URLs after asking for key word search terms.
// IMPORTANT: In order to activate the creative component, simply uncomment line 321 and comment out line 319 to switch search modes
void searchEngine(string filename) {
    cout << "Stand by while building index..." << endl;
    map<string, set<string>> index;
    int numPages = buildIndex(filename, index); // saves number but also runs buildIndex command at the same time
    int numWords = index.size();
    string userInput = "-";
    cout << "Indexed " << numPages << " pages containing " << numWords << " unique terms" << endl;
    normalSearch(filename, userInput, index);
    //CREATIVE COMPONENT (UNCOMMENT LINE 321 AND COMMENT OUT LINE 319)
    //creativeSearch(filename, userInput, index);
    cout << "Thank you for searching!";
}