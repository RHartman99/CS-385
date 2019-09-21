/*******************************************************************************
 * Name    : unique.cpp
 * Author  : Ryan J. Hartman    
 * Version : 1.1
 * Date    : September 20th, 2019
 * Description : Checks if a string has a unique set of characters with data packing a single unsigned integer.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>
#include <string>

using namespace std;

bool is_all_lowercase(const string &s) {
    for(char ch : s)
        if(ch < 'a' || ch > 'z')
            return false;
    return true;
}

bool all_unique_letters(const string &s) {
    unsigned int x = 0;
    for(char ch : s) {
        if((x & (1 << (ch - 'a'))) > 0)
            return false;
        else
            x = x | (1 << (ch - 'a'));
    }
    return true;
}

int main(int argc, char * const argv[]) {
    if(!argv[1]) {
        cerr << "Usage: ./unique <string>";
    } else if(argv[2]) {
        cerr << "Usage: ./unique <string>";
    } else if(!is_all_lowercase(argv[1])) {
        cerr << "Error: String must contain only lowercase letters.";
    } else if(!all_unique_letters(argv[1])) {
        cout << "Duplicate letters found.";
    } else {
        cout << "All letters are unique.";
    }
}