#include <iostream>

using namespace std;

void display_array(int array[], const int length) {
    cout << "[";

    if (length > 0) {
        cout << array[0];
    }

    for (int i = 1; i < length; i++) {
        cout << ", " << array[i];
    }
    cout << "]" << endl;
}

void display_array_ptr(int array[], const int length) {
    int *ptr = array, *end = array + length;

    cout << "[";

    if(length > 0) {
        cout << array[0];
        ptr++;
    }

    while(ptr < end) {
        cout << ", " << *ptr;
        ptr++;
    }
    cout << "]";
}

int main() {
    // Star declares a pointer and also dereferences a pointer.
    // An ampersand is the address of operator, and is required to assign pointers.
    int x = 5, y = 6, *z = &x; // Z is an integer pointer pointing to the memory address of x.
    
    cout << z << endl; // Memory location of where x is.
    cout << *z << endl; // Print a deferenced pointer, or the VALUE of z.
    cout << "x = " << x <<", y = " << y << endl;

    *z = 7; // We write in x's memory space.
    cout << "x = " << x <<", y = " << y << endl;

    z = &y; // Reassign z to y's memory address
    *z = 7; // Write 7 to y
    cout << "x = " << x <<", y = " << y << endl;

    // cout << ++z << endl; // Jumping to the next memory address, NOT increasing y.
    // cout << *z << endl; // Probably garbage data

    // z += 30000;         // TERRIBLE idea: z points outside the address space
    //                     // of this process

    // // *z = 30;            // Assigning a new value to the place z points
    // //                     // will cause a segmentation fault.

    int *values = new int[y]; // NEW allocates memory on the heap, not the stack.
                              // We have to delete this later, otherwise it will be a memory leak.
    for(int i= 0; i < y; i++) {
        values[i] = i;
    }

    display_array(values, y);
    display_array_ptr(values, y);

    delete [] values;

    return 0;
}