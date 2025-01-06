#include "header.h"

void readFile(vector<string>& strings, string fileName) {
    strings.resize(0);
    ifstream fileInp(fileName);

    if (!fileInp.is_open()) {
		cout << "Error when trying to open file `" << fileName << '`' << endl;
		return;
	}

    string line;
    while (getline(fileInp, line)) {
        strings.push_back(line);
    }

    fileInp.close();
}

// Overloading for reading paragraph
void readFile(string& str, string fileName) {
    ifstream fileInp(fileName);

    if (!fileInp.is_open()) {
		cout << "Error when trying to open file `" << fileName << '`' << endl;
		return;
	}

    getline(fileInp, str);

    fileInp.close();
}

void writeFile(vector<string> strings, string fileName) {
    ofstream fileOut(fileName);

    for (int i = 0; i < strings.size(); i++) {
        fileOut << strings[i] << endl;
    }

    fileOut.close();
}

void getUserArguments() {
    // Command 1
    if (input_arguments[1] == "-c") {
        command_line = CommandLine::Command1;
        first_file = input_arguments[2];
        second_file = input_arguments[3];

        if (input_arguments.size() == 5) 
            output_parameter = OutputParameter::BWT;
        else
            output_parameter = OutputParameter::InverseBWT;
    }
    // Command 2
    else if (input_arguments[1] == "-p") {
        command_line = CommandLine::Command2;
        first_file = input_arguments[2];
        second_file = input_arguments[3];
        third_file = input_arguments[4];
    }
}

void processCommand() {
    switch (command_line) {
        case CommandLine::Command1:
        {   
            // Read input file
            vector<string> strings;
            readFile(strings, first_file);
            
            // Convert
            vector<string> convertedStrings;
            for (int i = 0; i < strings.size(); i++) {
                if (output_parameter == OutputParameter::BWT)
                    convertedStrings.push_back(burrowsWheelerTransform(strings[i]));
                else
                    convertedStrings.push_back(inverseBurrowsWheelerTransform(strings[i]));
            }

            // Write to output file
            writeFile(convertedStrings, second_file);
            break;
        }
        
        case CommandLine::Command2:
        {   
            string paragraph;
            readFile(paragraph, first_file);
            string bwt = burrowsWheelerTransform(paragraph);

            vector<string> patterns;
            readFile(patterns, second_file);

            ofstream fileOut(third_file);
            for (string pattern : patterns) {
                fileOut << pattern << ": ";
                
                vector<int> positions = BWTPatternMatching(bwt, pattern);
                for (int i = 0; i < positions.size() - 1; i++)
                    fileOut << positions[i] << ", ";
                    
                fileOut << positions.back() << endl;
            }

            fileOut.close();
            break;
        }

        default:
            break;
    }

    cout << "Command is successfully performed. The program is now terminated..." << endl;
}