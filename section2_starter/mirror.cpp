/*
 * CS106B Section Handout Test Harness: Section 1
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Codified by Trip Master and Nick
 * Bowman for CS106B Spring 2020.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */
#include <iostream>
#include "grid.h"
#include "testing/SimpleTest.h"
#include "testing/TextUtils.h"
using namespace std;

/*
 * Mirror (Code Write)
 * ----------------------------------
 * Write a function that accepts a reference to a ​Grid​ of integers
 * as a parameter and flips the grid along its diagonal. You may
 * assume the grid is square; in other words, that it has the
 * same number of rows as columns.
 *
 */

void mirror(Grid<int> &nums){
    // TODO: Your code here
    int size = nums.numCols();
    for (int row = 0; row < size; row++) {
        for (int col = row + 1; col < size; col++) {
            int temp = nums[row][col];
            nums[row][col] = nums[col][row];
            nums[col][row] = temp;
        }
    }
}


/* * * * * Provided Tests Below This Point * * * * */


PROVIDED_TEST("test case from handout"){
    Grid<int> g = { { 6, 1, 9, 4},
                    {-2, 5, 8, 12},
                    {14, 39, -6, 18},
                    {21, 55, 73, -3}};

    Grid<int> soln = { {6, -2, 14, 21},
                       {1, 5, 39, 55},
                       {9, 8, -6, 73},
                       {4, 12, 18, -3} };
    mirror(g);
    EXPECT_EQUAL(g, soln);
}

