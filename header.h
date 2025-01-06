#ifndef _HEADER_H_
#define _HEADER_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <unordered_map>
#include <sstream>

using namespace std;

//-------------------------------------------------
// ___________ENUM CLASS__________

enum class CommandLine {
	Command1,
	Command2,
    Command3,
	Unknown
};

enum class OutputParameter {
    BWT,
    InverseBWT,
    Compress,
    Decompress,
    Unknown
};

// Any source file that includes this header this will be able to use these variables
extern CommandLine command_line;
extern OutputParameter output_parameter;
extern vector<string> input_arguments;
extern string first_file;
extern string second_file;
extern string third_file;


//-------------------------------------------------
// ___________COMMAND LINE ARGUMENTS FUNCTIONS__________
void getUserArguments();

void processCommand();

void readFile(vector<string>& strings, string fileName);

void readFile(string& str, string fileName);


void writeFile(vector<string> strings, string fileName);

//-------------------------------------------------
// ___________BURROWS-WHEELER TRANSFORM(BWT)__________
string burrowsWheelerTransform(string s);

string inverseBurrowsWheelerTransform(string bwt);

vector<int> BWTPatternMatching(string bwt, string pattern);

//-------------------------------------------------
// ___________COMPRESSION APPLICATION__________
string comp(string s);

string decomp(string s);

#endif