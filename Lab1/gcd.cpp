/*******************************************************************************
 * Name    : gcd.cpp
 * Author  : Ryan J. Hartman    
 * Version : 1.1
 * Date    : August 30th, 2019
 * Description : Computes the GCD of two command-line arguments.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

// Prototypes
int gcd_iterative(int m, int n);
int gcd_recursive(int m, int n);

int main(int argc, char* const argv[]) {
    int m, n;
    istringstream iss;

    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <integer m> <integer n>"
             << endl;
        return 1;
    }
    iss.str(argv[1]);
    if ( !(iss >> m) ) {
        cerr << "Error: The first argument is not a valid integer."
             << endl;
        return 1;
    }
    iss.clear(); // clear the error code
    iss.str(argv[2]);
    if ( !(iss >> n) ) {
        cerr << "Error: The second argument is not a valid integer."
             << endl;
        return 1;
    }

    cout << "Iterative: gcd(" << m << ", " << n << ") = " << gcd_iterative(m,n) << endl;
    cout << "Recursive: gcd(" << m << ", " << n << ") = " << gcd_recursive(m,n) << endl;
    return 0;
}

// Iterative adaptation of the euclidian algorithm
int gcd_iterative(int m, int n) {
    int temp;
    while(n != 0) {
        temp = m;
        m = n;
        n = temp % n; 
    }
    return abs(m);
}

// Euclidian algorithm
int gcd_recursive(int m, int n) {
    if (m == 0) {
        return abs(n);
    }
    return gcd_recursive(n % m, m);
}