/*******************************************************************************
 * Name    : stairclimber.cpp
 * Author  : Ryan J. Hartman    
 * Version : 1.1
 * Date    : September 29th, 2019
 * Description : Lists the number of ways to climb n stairs.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char *const argv[])
{

    if (argc != 7)
    {
        cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>";
        return 1;
    }

    int data[7];
    char jug_letters[7] = {'1', 'A', 'B', 'C', 'A', 'B', 'C'};

    for (int i = 1; i <= 6; i++)
    {
        istringstream iss(argv[i]);
        if (!(iss >> data[i]) || (data[i] <= 0 && i <= 3) || data[i] < 0)
        {
            if (i <= 3)
                cerr << "Error: Invalid capacity '" << argv[i] << "' for jug " << jug_letters[i] << ".";
            else
                cerr << "Error: Invalid goal '" << argv[i] << "' for jug " << jug_letters[i] << ".";

            return 1;
        }
    }

    int total = 0;
    for (int i = 1; i <= 3; i++)
    {
        total += data[i + 3];
        if (data[i] < data[i + 3])
        {
            cerr << "Error: Goal cannot exceed capacity of jug " << jug_letters[i] << ".";
            return 1;
        }
    }
    if (total != data[3])
    {
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C.";
        return 1;
    }

    cout << "Good input";
    return 0;
}