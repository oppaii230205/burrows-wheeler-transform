#include "header.h"

// Assign the global variables with their initial value
CommandLine command_line = CommandLine::Unknown;
OutputParameter output_parameter = OutputParameter::Unknown;
vector<string> input_arguments;
string first_file;
string second_file;
string third_file;

int main(int argc, char* argv[]) {
    if (argc < 4) {
		cerr << "Insufficient arguments provided. Please check the usage!!!" << endl;
		return 1;
	}

	// Pushing the command line arguments for the global use
	for (int i = 0; i < argc; i++) {
		string arg = argv[i];
		input_arguments.push_back(arg);
	}

    getUserArguments();
    processCommand();
    return 0;
}