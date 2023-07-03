/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include "testing/SimpleTest.h"
#include "strlib.h"
#include "filelib.h"
#include "simpio.h"
#include <fstream>
#include <cctype>
#include <string>
#include "set.h"
#include "vector.h"
using namespace std;

/* This function is intended to return a string which
 * contains only the letter characters from the original
 * (all non-letter characters are removed)
 *
 * WARNING: The provided code is buggy!
 *
 * Use unit tests to identify which inputs to this function
 * are incorrectly handled. Then, remove this comment and
 * replace it with a description of the bug you fixed.
 */
string removeNonLetters(string s) {
    string result = "";
    for (int i = 0; i < s.length(); i++) {
        if (isalpha(s[i])) {
            result += s[i];
        }
    }
    return result;
}

/* This function encode letters to digit according to encode table.
 * s is the input letters need to be encoded.
 */
string lettersToDigital(string s) {
    // set the table of letter encoding
    Set<char> encodeToZero = {'A', 'E', 'I', 'O', 'U', 'H', 'W', 'Y'};
    Set<char> encodeToOne = {'B', 'F', 'P', 'V'};
    Set<char> encodeToTwo = {'C', 'G', 'K', 'Q', 'S', 'X', 'Z'};
    Set<char> encodeToThree = {'D', 'T'};
    Set<char> encodeToFour = {'L'};
    Set<char> encodeToFive = {'M', 'N'};
    Set<char> encodeToSix = {'R'};
    // a string to store coded output
    string codedStr = "";
    for (int i = 0; i < s.length(); i++) {
        if (encodeToZero.contains(s[i])
        || encodeToZero.contains(toupper(s[i]))) {
            codedStr += '0';
        }
        else if (encodeToOne.contains(s[i])
        || encodeToOne.contains(toupper(s[i]))) {
            codedStr += '1';
        }
        else if (encodeToTwo.contains(s[i])
        || encodeToTwo.contains(toupper(s[i]))) {
            codedStr += '2';
        }
        else if (encodeToThree.contains(s[i])
        || encodeToThree.contains(toupper(s[i]))) {
            codedStr += '3';
        }
        else if (encodeToFour.contains(s[i])
        || encodeToFour.contains(toupper(s[i]))) {
            codedStr += '4';
        }
        else if(encodeToFive.contains(s[i])
        || encodeToFive.contains(toupper(s[i]))) {
            codedStr += '5';
        }
        else if(encodeToSix.contains(s[i])
        || encodeToSix.contains(toupper(s[i]))) {
            codedStr += '6';
        }
    }
    return codedStr;
}

/* This function remove adjacent duplicate digits from the code
 */
void delAdjDuplicate(string& s) {
    for (int i = 0; i < s.length();) {
        // if two adjacent digits have a same value, delete the first one
        if (s[i] == s[i + 1]) {
            s.erase(i, 1);  // remove the char indexed i
        }
        else {
            i++;  // if there is no adjacent duplicates, move to the next digit
        }
    }
}

/* This function remove all zeros from the code
 */
void removeZeros(string& s) {
    for (int i = 0; i < s.length();) {
        if (s[i] == '0') {
            s.erase(i, 1);
        }
        else {
            i++;
        }
    }
}

/* This function get a string of length 4
 */
void toLengthFour(string& s) {
    if (s.length() > 4) {
        s = s.substr(0, 4);
    }
    else if (s.length() < 4) {
        s += string(4 - s.length(), '0');
    }
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
string soundex(string s) {
    string codedStr = removeNonLetters(s);
    codedStr = lettersToDigital(codedStr);
    delAdjDuplicate(codedStr);

    codedStr.erase(0, 1);
    codedStr = toUpperCase(s[0]) + codedStr;
    
    removeZeros(codedStr);
    toLengthFour(codedStr);
    return codedStr;
}


/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
void soundexSearch(string filepath) {
    // The proivded code opens the file with the given name
    // and then reads the lines of that file into a vector.
    ifstream in;
    Vector<string> databaseNames;

    if (openFile(in, filepath)) {
        readEntireFile(in, databaseNames);
    }
    cout << "Read file " << filepath << ", "
         << databaseNames.size() << " names found." << endl;

    // The names in the database are now stored in the provided
    // vector named databaseNames

    /* TODO: Fill in the remainder of this function. */
    string inputSurname, soundexCode;
    Vector<string> matchSurname;
    while (true)
    {
        matchSurname.clear();
        inputSurname = getLine("Please input a surname (remain empty to exit): ");
        if (inputSurname == "") {
            break;
        }
        else {
            soundexCode = soundex(inputSurname);
            for (string surname : databaseNames) {
                if (soundexCode == soundex(surname)) {
                    matchSurname.add(surname);
                }
            }
        }
        matchSurname.sort();
        cout << matchSurname << endl;
    }
    
}


/* * * * * * Test Cases * * * * * */


PROVIDED_TEST("Test removing puntuation, digits, and spaces") {
    string s = "O'Hara";
    string result = removeNonLetters(s);
    EXPECT_EQUAL(result, "OHara");
    s = "Planet9";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "Planet");
    s = "tl dr";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "tldr");
}


PROVIDED_TEST("Sample inputs from handout") {
    EXPECT_EQUAL(soundex("Curie"), "C600");
    EXPECT_EQUAL(soundex("O'Conner"), "O256");
}

PROVIDED_TEST("hanrahan is in lowercase") {
    EXPECT_EQUAL(soundex("hanrahan"), "H565");
}

PROVIDED_TEST("DRELL is in uppercase") {
    EXPECT_EQUAL(soundex("DRELL"), "D640");
}

PROVIDED_TEST("Liu has to be padded with zeros") {
    EXPECT_EQUAL(soundex("Liu"), "L000");
}

PROVIDED_TEST("Tessier-Lavigne has a hyphen") {
    EXPECT_EQUAL(soundex("Tessier-Lavigne"), "T264");
}

PROVIDED_TEST("Au consists of only vowels") {
    EXPECT_EQUAL(soundex("Au"), "A000");
}

PROVIDED_TEST("Egilsdottir is long and starts with a vowel") {
    EXPECT_EQUAL(soundex("Egilsdottir"), "E242");
}

PROVIDED_TEST("Jackson has three adjcaent duplicate codes") {
    EXPECT_EQUAL(soundex("Jackson"), "J250");
}

PROVIDED_TEST("Schwarz begins with a pair of duplicate codes") {
    EXPECT_EQUAL(soundex("Schwarz"), "S620");
}

PROVIDED_TEST("Van Niekerk has a space between repeated n's") {
    EXPECT_EQUAL(soundex("Van Niekerk"), "V526");
}

PROVIDED_TEST("Wharton begins with Wh") {
    EXPECT_EQUAL(soundex("Wharton"), "W635");
}

PROVIDED_TEST("Ashcraft is not a special case") {
    // Some versions of Soundex make special case for consecutive codes split by hw
    // We do not make this special case, just treat same as codes split by vowel
    EXPECT_EQUAL(soundex("Ashcraft"), "A226");
}

// TODO: add your test cases here
STUDENT_TEST("Test for removeNonLetters()") {
    string s = "'abc";
    EXPECT_EQUAL(removeNonLetters(s), "abc");
}
STUDENT_TEST("Test for letter to digit encode") {
    string s = "abc";
    EXPECT_EQUAL(lettersToDigital(s), "012");
    s = "xuq";
    EXPECT_EQUAL(lettersToDigital(s), "202");
    s = "lbc";
    EXPECT_EQUAL(lettersToDigital(s), "412");
}
STUDENT_TEST("Test for delAdjDuliplate()") {
    string s = "2200";
    delAdjDuplicate(s);
    EXPECT_EQUAL(s, "20");
    s = "2023";
    delAdjDuplicate(s);
    EXPECT_EQUAL(s, "2023");
    s = "00002022";
    delAdjDuplicate(s);
    EXPECT_EQUAL(s, "0202");
}
STUDENT_TEST("Test for removeZeros()") {
    string s = "2023";
    removeZeros(s);
    EXPECT_EQUAL(s, "223");
    s = "00033";
    removeZeros(s);
    EXPECT_EQUAL(s, "33");
}
STUDENT_TEST("Test for toLengthFour()") {
    string s = "abc";
    toLengthFour(s);
    EXPECT_EQUAL(s, "abc0");
    s = "abcdefg";
    toLengthFour(s);
    EXPECT_EQUAL(s, "abcd");
    s = "abcd";
    toLengthFour(s);
    EXPECT_EQUAL(s, "abcd");

}
