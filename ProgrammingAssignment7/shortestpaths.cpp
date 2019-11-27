/*******************************************************************************
 * Name    : shortestpaths.cpp
 * Author  : Ryan J. Hartman & Daniel Pekata
 * Version : 1.0
 * Date    : December 3rd, 2019
 * Description : Uses Floyd's Algorithm to find the shortest path to each vertex in a graph.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <cctype>
#include <sstream>

using namespace std;

bool findPaths(ifstream &matrix_file)
{
    string line, v_1, v_2, edge_str;
    int line_number = 0, value = 0, edge_weight = 0, max_ascii = 0;
    while (getline(matrix_file, line))
    {
        line_number++;
        if (line_number == 1)
        {
            istringstream iss(line);
            if (!(iss >> value) || value <= 0 || value > 26)
            {
                cerr << "Error: Invalid number of vertices '" << line << "' on line 1.";
                return false;
            }
            max_ascii = 'A' + value - 1;
        }
        else
        {
            stringstream sstream(line);

            if(!(sstream >> v_1) || !(sstream >> v_2) || !(sstream >> edge_str)) {
                cerr << "Error: Invalid edge data '" << line << "' on line " << line_number << ".";
                return false;
            }

            istringstream iss(edge_str);

            if(!(iss >> edge_weight) || edge_weight <= 0) {
                cerr << "Error: Invalid edge weight '" << edge_str << "' on line " << line_number << ".";
                return false; 
            }

            if (v_1.length() > 1 || v_1[0] < 'A' || v_1[0] > max_ascii) {
                cerr << "Error: Starting vertex '" << v_1 << "' on line " << line_number << " is not among valid values A-" << char(max_ascii) << ".";
                return false;
            }

            if (v_2.length() > 1 || v_2[0] < 'A' || v_2[0] > max_ascii) {
                cerr << "Error: Ending vertex '" << v_2 << "' on line " << line_number << " is not among valid values A-" << char(max_ascii) << ".";
                return false;
            }

            if(iss >> line) {
                cerr << "Error: Too many entries on line '" << line_number << "'.";
                return false;
            }
        }
    }
    return true;
}

// void floydsAlgorithm(ifstream &matrix_file)
// {
// }

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: ./shortestpaths <filename>";
        return 1;
    }
    ifstream matrix_file(argv[1]);
    if (!matrix_file)
    {
        cerr << "Error: Cannot open file '" << argv[1] << "'.";
        return 1;
    }
    if (!findPaths(matrix_file))
    {
        matrix_file.close();
        return 1;
    }
    int succesful = findPaths(matrix_file);
    matrix_file.close();
    return succesful;
}