/*******************************************************************************
 * Name    : waterjugpuzzle.cpp
 * Author  : Ryan J. Hartman & Andrew S. Pantera
 * Version : 1.1
 * Date    : October 15th, 2019
 * Description : Finds the fastest possible solution to a valid water jug puzzle.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <vector>

using namespace std;

// Struct to represent state of water in the jugs.
struct State
{
    int a, b, c;
    string direction;
    State *parent;
    State(int _a, int _b, int _c) : a(_a), b(_b), c(_c) {}                                                                                                                                                    // String representation of state in tuple form.
    State(int _a, int _b, int _c, string _dir, State *_par) : a(_a), b(_b), c(_c), direction(_dir + " (" + std::to_string(_a) + ", " + std::to_string(_b) + ", " + std::to_string(_c) + ")"), parent(_par) {} // String representation of state in tuple form.
    string to_string()
    {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

// Function prototypes
bool check_input(int argc, char *const argv[], int data[7]);
State solve_puzzle(int a, int b, int c, int goal_a, int goal_b, int goal_c);
void output_steps(State end_state);

/**
 * Driver function. Validates input, calls solve_puzzle, and
 * interperets the output
 */
int main(int argc, char *const argv[])
{
    int data[7];
    if (!check_input(argc, argv, data))
        return 1;

    State solved_state = solve_puzzle(data[1], data[2], data[3], data[4], data[5], data[6]);
    if (solved_state.a == -1)
    {
        cout << "No solution.";
    }
    return 0;
}

/**
 * Function to solve the puzzle and perform a BFS. Will generate a graph as it searches.
 * Uses a queue to perform the search, and a 2d vector of state pointers to track which
 * states have already been visited.
 * For each pour, the function will check if the pour is possible before pushing it on the queue.
 */
State solve_puzzle(int a, int b, int c, int goal_a, int goal_b, int goal_c)
{
    queue<State> *states = new queue<State>;              // State queue to perform search with
    states->push(State(0, 0, c, "Initial state.", NULL)); // Push initial state (3rd jug completely full)
    vector<vector<State *>> visited_states;               // 2D arary of state pointers, to track already visited states
    visited_states.resize(a + 1, vector<State *>(b + 1)); // Resize vector to account for all possible states
    State *currentState;                                  // Pointer to state current state in search
    while (!states->empty())
    {
        currentState = new State(states->front());
        states->pop();

        // If we haven't seen this state...
        if (!visited_states[currentState->a][currentState->b])
        {
            visited_states[currentState->a][currentState->b] = currentState; // Mark state as seen
            // If we've found the goal, output the steps and garbage collect
            if (currentState->a == goal_a && currentState->b == goal_b && currentState->c == goal_c)
            {
                output_steps(*currentState);
                State endState = *currentState;

                for (int i = 0; i < a + 1; ++i)
                {
                    for (int j = 0; j < b + 1; ++j)
                    {
                        if (visited_states[i][j])
                        {
                            currentState = visited_states[i][j];
                            delete currentState;
                        }
                    }
                }

                delete states;
                return endState;
            }
            else // If not seen before, perform all possible pours. Danger: Spaghetti code ahead
            {
                int amount_poured;
                // Pour C to A...
                if (currentState->a != a && currentState->c != 0)
                {
                    amount_poured = a - currentState->a;
                    if (amount_poured >= currentState->c)
                    {
                        if (currentState->c == 1)
                            states->push(State(currentState->a + currentState->c, currentState->b, 0, "Pour " + to_string(currentState->c) + " gallon from C to A.", currentState));
                        else
                            states->push(State(currentState->a + currentState->c, currentState->b, 0, "Pour " + to_string(currentState->c) + " gallons from C to A.", currentState));
                    }
                    else
                    {
                        if (amount_poured == 1)
                            states->push(State(a, currentState->b, currentState->c - amount_poured, "Pour " + to_string(amount_poured) + " gallon from C to A.", currentState));
                        else
                            states->push(State(a, currentState->b, currentState->c - amount_poured, "Pour " + to_string(amount_poured) + " gallons from C to A.", currentState));
                    }
                }
                // Pour B to A...
                if (currentState->a != a && currentState->b != 0)
                {
                    amount_poured = a - currentState->a;
                    if (amount_poured >= currentState->b)
                        if (currentState->b == 1)
                            states->push(State(currentState->a + currentState->b, 0, currentState->c, "Pour " + to_string(currentState->b) + " gallon from B to A.", currentState));
                        else
                            states->push(State(currentState->a + currentState->b, 0, currentState->c, "Pour " + to_string(currentState->b) + " gallons from B to A.", currentState));
                    else if (amount_poured == 1)
                        states->push(State(a, currentState->b - amount_poured, currentState->c, "Pour " + to_string(amount_poured) + " gallon from B to A.", currentState));
                    else
                        states->push(State(a, currentState->b - amount_poured, currentState->c, "Pour " + to_string(amount_poured) + " gallons from B to A.", currentState));
                }
                // Pour C to B...
                if (currentState->b != b && currentState->c != 0)
                {
                    amount_poured = b - currentState->b;
                    if (amount_poured >= currentState->c)
                        if (currentState->c == 1)
                            states->push(State(currentState->a, currentState->b + currentState->c, 0, "Pour " + to_string(currentState->c) + " gallon from C to B.", currentState));
                        else
                            states->push(State(currentState->a, currentState->b + currentState->c, 0, "Pour " + to_string(currentState->c) + " gallons from C to B.", currentState));
                    else if (amount_poured == 1)
                        states->push(State(currentState->a, b, currentState->c - amount_poured, "Pour " + to_string(amount_poured) + " gallon from C to B.", currentState));
                    else
                        states->push(State(currentState->a, b, currentState->c - amount_poured, "Pour " + to_string(amount_poured) + " gallons from C to B.", currentState));
                }
                // Pour A to B...
                if (currentState->b != b && currentState->a != 0)
                {
                    amount_poured = b - currentState->b;
                    if (amount_poured >= currentState->a)
                        if (currentState->a == 1)
                            states->push(State(0, currentState->b + currentState->a, currentState->c, "Pour " + to_string(currentState->a) + " gallon from A to B.", currentState));
                        else
                            states->push(State(0, currentState->b + currentState->a, currentState->c, "Pour " + to_string(currentState->a) + " gallons from A to B.", currentState));
                    else if (amount_poured == 1)
                        states->push(State(currentState->a - amount_poured, b, currentState->c, "Pour " + to_string(amount_poured) + " gallon from A to B.", currentState));
                    else
                        states->push(State(currentState->a - amount_poured, b, currentState->c, "Pour " + to_string(amount_poured) + " gallons from A to B.", currentState));
                }
                // Pour B to C...
                if (currentState->c != c && currentState->b != 0)
                {
                    amount_poured = c - currentState->c;
                    if (amount_poured >= currentState->b)
                        if (currentState->b == 1)
                            states->push(State(currentState->a, 0, currentState->c + currentState->b, "Pour " + to_string(currentState->b) + " gallon from B to C.", currentState));
                        else
                            states->push(State(currentState->a, 0, currentState->c + currentState->b, "Pour " + to_string(currentState->b) + " gallons from B to C.", currentState));
                    else if (amount_poured == 1)
                        states->push(State(currentState->a, currentState->b - amount_poured, c, "Pour " + to_string(amount_poured) + " gallon from B to C.", currentState));
                    else
                        states->push(State(currentState->a, currentState->b - amount_poured, c, "Pour " + to_string(amount_poured) + " gallons from B to C.", currentState));
                }
                // Pour A to C...
                if (currentState->c != c && currentState->a != 0)
                {
                    amount_poured = c - currentState->c;
                    if (amount_poured >= currentState->a)
                        if (currentState->a == 1)
                            states->push(State(0, currentState->b, currentState->c + currentState->a, "Pour " + to_string(currentState->a) + " gallon from A to C.", currentState));
                        else
                            states->push(State(0, currentState->b, currentState->c + currentState->a, "Pour " + to_string(currentState->a) + " gallons from A to C.", currentState));
                    else if (amount_poured == 1)
                        states->push(State(currentState->a - amount_poured, currentState->b, c, "Pour " + to_string(amount_poured) + " gallons from A to C.", currentState));
                    else
                        states->push(State(currentState->a - amount_poured, currentState->b, c, "Pour " + to_string(amount_poured) + " gallons from A to C.", currentState));
                }
            }
        }
        else
        {
            delete currentState; // If already visited, delete this state and its pointers.
        }
    }
    // If a solution can't be found, then garbage collect and return a sentinel state.
    for (int i = 0; i < a + 1; ++i)
    {
        for (int j = 0; j < b + 1; ++j)
        {
            if (visited_states[i][j])
            {
                currentState = visited_states[i][j];
                delete currentState;
            }
        }
    }
    delete states;
    return State(-1, -1, -1); // Return a state with -1 sentinel values, indicating no solution.
}

/**
 * Function to validate user input. Checks that amount of arguments is 6,
 * and that it is a valid water jug puzzle setup.
 */
bool check_input(int argc, char *const argv[], int data[7])
{
    if (argc != 7)
    {
        cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>";
        return false;
    }

    char jug_letters[7] = {'1', 'A', 'B', 'C', 'A', 'B', 'C'};

    for (int i = 1; i <= 6; i++)
    {
        istringstream iss(argv[i]);
        iss >> data[i];
        if (!iss || (data[i] <= 0 && i <= 3) || data[i] < 0)
        {
            if (i <= 3)
                cerr << "Error: Invalid capacity '" << argv[i] << "' for jug " << jug_letters[i] << ".";
            else
                cerr << "Error: Invalid goal '" << argv[i] << "' for jug " << jug_letters[i] << ".";

            return false;
        }
    }
    int total = 0;
    for (int i = 1; i <= 3; i++)
    {
        total += data[i + 3];
        if (data[i] < data[i + 3])
        {
            cerr << "Error: Goal cannot exceed capacity of jug " << jug_letters[i] << ".";
            return false;
        }
    }
    if (total != data[3])
    {
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C.";
        return false;
    }
    return true;
}

/**
 * Function to recursively output the steps up to the root. Uses recursion's rewinding
 * principle to output the steps in reverse order of being seen, so the root is output
 * first.
 */
void output_steps(State end_state)
{
    if (end_state.parent != NULL)
        output_steps(*end_state.parent);
    cout << end_state.direction << endl;
}
