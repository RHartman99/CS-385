/*******************************************************************************
 * Name    : inversioncounter.cpp
 * Author  : Ryan J. Hartman    
 * Version : 1.0
 * Date    : October 19th, 2019
 * Description : Counts the number of inversions in an array.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <string>
#include <cstring>

using namespace std;

void mergesort(int array[], int scratch[], int size)
{
    mergesort(array, scratch, 0, size - 1);
}
/**
 * Uses merge sort to count inversions.
 */
void mergesort(int array[], int scratch[], int low, int high)
{
    long count = 0;
    if (low < high)
    {
        int mid = low + (high - low) / 2;
        mergesort(array, scratch, low, mid);
        mergesort(array, scratch, mid + 1, high);
        int L = low;
        int H = mid + 1;
        for (int k = low; k <= high; k++)
        {
            if (L <= mid && (H > high || array[L] <= array[H]))
            {
                scratch[k] = array[L];
                L++;
            }
            // We are taking from the right side, so increment count by
            // the amount of elements between the middle and the current
            // left most index:
            else
            {
                scratch[k] = array[H];
                H++;
            }
        }
        for (int k = low; k <= high; k++)
        {
            array[k] = scratch[k];
        }
    }
}

int main(int argc, char *argv[])
{
    int array[12] = {987651,
                     975310,
                     12344,
                     -23454,
                     -74,
                     28,
                     40,
                     1234567891,
                     0,
                     555,
                     23,
                     76};
    int scratch_array[12];
    mergesort(array, scratch_array, 12);

    for (int el : array)
        cout << el << endl;

    return 0;
}
