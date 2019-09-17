/*******************************************************************************
 * Name    : sieve.cpp
 * Author  : Ryan J. Hartman    
 * Version : 1.1
 * Date    : September 11th, 2019
 * Description : Finds all prime numbers from 2 to n as long as n is greater than 2.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes();
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {

    int primesOutputted = 0;
    const int   max_prime_width = num_digits(max_prime_),
                primes_per_row = 80 / (max_prime_width + 1);

    for(int i = 2; i <= limit_; i++) {
        if(is_prime_[i]) {

            if(primesOutputted != 0) {
                cout << " ";
            }

            if(num_primes_ <= primes_per_row)
                if(primesOutputted == 0)
                    cout << i;
                else
                    cout << right << setw(num_digits(i)) << i;
            else
                cout << right << setw(max_prime_width) << i;
                
            primesOutputted++;

            if(primesOutputted % primes_per_row == 0) {
                primesOutputted = 0;
                cout << endl;
            }
        }
    }
}

int PrimesSieve::count_num_primes() {
    int numPrimes = 0;
    for(int i = 2; i <= limit_; i++) {
        if(is_prime_[i]) {
            numPrimes++;

            if(i > max_prime_) {
                max_prime_ = i; 
            }
        }
    }
    return numPrimes;
}

void PrimesSieve::sieve() {
    for(int i = 0; i <= limit_; i++) {
        is_prime_[i] = true;
    }
    for(int i = 2; i < (int) sqrt(limit_) + 1; i++) {
        if(is_prime_[i]) {
            int loopConstant = 0;
            for(int j = i*i; j <= limit_ + 1; j = i*i + loopConstant*i) {
                is_prime_[j] = false;
                loopConstant++;
            }
        }
    }

    num_primes_ = count_num_primes();
}

int PrimesSieve::num_digits(int num) {
    int numDigits = 0;
    while(num > 0) {
        num = num / 10;
        numDigits++;
    }
    return numDigits;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    istringstream iss(limit_str);

    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    PrimesSieve *Sieve = new PrimesSieve(limit);

    cout << endl << "Number of primes found: " << Sieve->num_primes() << endl;
    cout << "Primes up to " << limit << ":" << endl;
    Sieve->display_primes();

    delete Sieve;
    return 0;
}