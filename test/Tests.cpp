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

TEST(STOSTests, Test0) { MyTest("0"); }
TEST(STOSTests, Test1) { MyTest("1"); }
TEST(STOSTests, Test2) { MyTest("2"); }
TEST(STOSTests, Test3) { MyTest("3"); }
TEST(STOSTests, Test4) { MyTest("4"); }
TEST(STOSTests, Test5) { MyTest("5"); }
TEST(STOSTests, Test6) { MyTest("6"); }
TEST(STOSTests, Test7) { MyTest("7"); }
TEST(STOSTests, Test8) { MyTest("8"); }
TEST(STOSTests, Test9) { MyTest("9"); }
TEST(STOSTests, Test10) { MyTest("10"); }
TEST(STOSTests, Test11) { MyTest("11"); }
TEST(STOSTests, Test12) { MyTest("12"); }
TEST(STOSTests, Test13) { MyTest("13"); }
TEST(STOSTests, Test14) { MyTest("14"); }
TEST(STOSTests, Test15) { MyTest("15"); }
TEST(STOSTests, Test16) { MyTest("16"); }
TEST(STOSTests, Test17) { MyTest("17"); }
TEST(STOSTests, Test18) { MyTest("18"); }
TEST(STOSTests, Test19) { MyTest("19"); }
TEST(STOSTests, Test20) { MyTest("20"); }
TEST(STOSTests, Test21) { MyTest("21"); }
TEST(STOSTests, Test22) { MyTest("22"); }
TEST(STOSTests, Test23) { MyTest("23"); }

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
    testPaths("input/" + number + ".in", "actual/actual-" + number + ".txt",
              "expected/" + number + ".out");
}