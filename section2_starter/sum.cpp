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
#include <vector.h>
#include "grid.h"
#include "filelib.h"
#include "testing/SimpleTest.h"
#include "testing/TextUtils.h"
using namespace std;

bool isNumber(string s)
{
    // strip negative sign off negative numbers
    if (s.length() > 0 && s[0] == '-') {
        s = s.substr(1);
    }
    for (char ch : s) {
        if (!isdigit(ch)) return false;
    }
    return s.length() > 0;
}

/*
 * Sum Numbers (Code Write)
 * ----------------------------------
 * Write a program to read through a given file and sum
 * all of the numbers in the file. You can assume that numbers
 * will be composed entirely of numerical digits, optionally
 * preceded by a single negative sign.
 */
int sumNumbers(string filename){
    ifstream in;
    Vector<string> lines;
    int sum = 0;

    if (!openFile(in, filename)) {
        return 0;
    }

    readEntireFile(in, lines);
    for (string line : lines) {
        Vector<string> tokens = stringSplit(line, " ");
        for (string t : tokens) {
            if (isNumber(t)) {
                sum += stringToInteger(t);
            }
        }
    }
    return sum;
}


/* * * * * Provided Tests Below This Point * * * * */
PROVIDED_TEST("given file in handout"){
    EXPECT_EQUAL(sumNumbers("res/numbers.txt"), 42);
}

PROVIDED_TEST("Nonexistent file should sum to zero") {
    EXPECT_EQUAL(sumNumbers("nonexistent_filename"), 0);
}

