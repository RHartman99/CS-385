 /*******************************************************************************
 * Name    : stairclimber.cpp
 * Author  : Ryan J. Hartman    
 * Version : 1.1
 * Date    : September 29th, 2019
 * Description : Lists the number of ways to climb n stairs.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

int num_digits(int num) {
    int numDigits = 0;
    while(num > 0) {
        num = num / 10;
        numDigits++;
    }
    return numDigits;
}

vector< vector<int> > get_ways(int num_stairs) {
    vector< vector<int> > ways;

    if(num_stairs <= 0 ) {
        vector<int> empty_vec;
        ways.push_back(empty_vec);
    }
    else {
        for(int i = 1; i <= 3; i++) {
            if(num_stairs >= i) {
                vector<vector<int>> result;
                result = get_ways(num_stairs - i);
                for(unsigned int j = 0; j < result.size(); j++) {
                    result.at(j).insert(result.at(j).begin(), i);
                }
                ways.insert(ways.end(), result.begin(), result.end());
            }
        }
    }
    return ways;
}

void display_ways(const vector< vector<int> > &ways, int num_stairs) {
    cout << ways.size() << " way"; 
    if( ways.size() > 1 ) 
        cout << "s";
    cout << " to climb " << num_stairs << " stair";
    if( ways.size() > 1 ) 
        cout << "s";
    cout << ".";
    int number_col_width = num_digits(ways.size());

    for(unsigned int i = 0; i < ways.size(); i++) {
        cout << endl << setw(number_col_width) << right << i + 1 << ". [";
        int j = 0;
        for(int num : ways.at(i)) {
            if(j > 0)
                cout << ", ";
            cout << num;
            j++;
        }
        cout << "]";
    }
}

int main(int argc, char * const argv[]) {
    if (argc > 2 || argc == 1) {
        cerr << "Usage: ./stairclimber <number of stairs>";
        return 1;
    } 

    int num_stairs;
    istringstream iss(argv[1]);

    if( !(iss >> num_stairs)) {
        cerr << "Error: Number of stairs must be a positive integer.";
        return 1;
    }
    if(num_stairs <= 0) {
        cerr << "Error: Number of stairs must be a positive integer.";
        return 1;
    }
    vector< vector<int> > ways = get_ways(num_stairs);
    display_ways(ways, num_stairs);
    return 0;
}
