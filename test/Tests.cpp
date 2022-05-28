#include <gtest/gtest.h>

#include <fstream>
#include <iostream>
#include <string>

#include "../src/main.h"

using namespace std;



void MyTest(string number);

TEST(CompareStrings, StringEqual) {
    char charArr1[] = "thesamestring", charArr2[] = "thesamestring";
    bool t = equals(charArr1, charArr2);
    ASSERT_TRUE(t);
}

TEST(CompareStrings, StringNotEqual) {
    char charArr1[] = "kebabisto", charArr2[] = "zonker";
    bool f = equals(charArr1, charArr2);
    ASSERT_FALSE(f);
}

TEST(CompareFiles, LineEqual) {
    MyTest("0");
}

TEST(CompareFiles, MultipleLinesEqual){
    MyTest("1");
}

void checkLineEquality(fstream& expected, fstream& actual) {
    string expectedLine, actualLine;
    int line = 0;
    do {
        line++;
        getline(expected, expectedLine);
        getline(actual, actualLine);
        ASSERT_EQ(expectedLine, actualLine) << "Output line " << line << "\n";
    } while (!expected.eof() && !actual.eof());
    if (!actual.eof()) {
        FAIL() << "Too many lines in actual output: " << line << "\n";
    }
}

char* fullPath(string fileName) {
    // char* charName = new char[fileName.length()];
    // strcpy(charName, fileName.c_str());
    // return charName;

    int defaultDirectoryLength = 39;
    int fullPathLength = defaultDirectoryLength + fileName.length();
    char* fullPath = new char[fullPathLength];
    std::string directory = "/home/mimovnik/PG/AISD/nmkSolver/test/";
    directory += fileName;
    strcpy(fullPath, directory.c_str());
    return fullPath;
}

void testPaths(string inputPath, string actualPath, string expectedPath) {
    auto cinBuffer = cin.rdbuf();
    auto testInput = fstream(fullPath(inputPath), fstream::in);
    cin.rdbuf(testInput.rdbuf());

    auto coutBuffer = cout.rdbuf();
    auto testOutput =
        fstream(fullPath(actualPath), fstream::out | fstream::trunc);
    cout.rdbuf(testOutput.rdbuf());

    int program = MYmain();
    ASSERT_EQ(0, program);

    auto expected = fstream(fullPath(expectedPath), fstream::in);
    auto actual = fstream(fullPath(actualPath), fstream::in);
    checkLineEquality(expected, actual);
}

void MyTest(string number) {
    testPaths("input/input-" + number + ".txt",
              "actual/actual-" + number + ".txt",
              "expected/expected-" + number + ".txt");
}