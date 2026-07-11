#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <vector>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <sys/wait.h>

// To define OS based path spliter - different OS adaptible
#if _WIN32
constexpr char PATH_LIST_SEPARATOR = ';';
#else
constexpr char PATH_LIST_SEPARATOR = ':';
#endif

// Function to split the input string
std::vector<std::string> splitInput(const std::string& input)
{
	std::istringstream iss(input);
	std::vector<std::string> tokens;
	std::string token;

	while (iss >> token) {
		tokens.push_back(token);
	}

	return tokens;
}

// To Run external command
void runExternalCommand(const std::string& userInput)
{
	std::vector<std::string> tokens = splitInput(userInput);
	
	if (tokens.empty()) { return; }

	std::vector<char*> argv;
	for (auto& token : tokens)
	{
		argv.push_back(const_cast<char*>(token.c_str()));
	}
	argv.push_back(nullptr);

	pid_t pid = fork();

	if (pid < 0) { 
		std::cerr << "fork failed" << std::endl;
		return;
	}

	if (pid == 0) {
		execvp(argv[0], argv.data());
		std::cerr << userInput << ": command not found" << std::endl;
		_exit(1);
	}
	else {
		int status;
		waitpid(pid, &status, 0);
	}
}

// Logic for type command using vector to check for valid command
const std::vector<std::string> g_valid_commands = {"exit", "echo", "type"};

void commandType(std::string userInput)
{
	// Trime the input
	userInput.erase(0,5);

	// Finds the commands in the vector
	auto it = std::find(std::begin(g_valid_commands), std::end(g_valid_commands), userInput);

	// Evalutes if the command is found
	if (it != std::end(g_valid_commands)) {
		std::cout << userInput << " is a shell builtin" << std::endl;
	}
	else 
	{
		// Define path related variables
		std::string pathVar = std::getenv("PATH");
		std::istringstream path_stream(pathVar);
		std::string pathSplit;

		// get different PATH's and put it in pathSplit | the splitting is based on the defined constant speparator above  
		while (std::getline(path_stream, pathSplit, PATH_LIST_SEPARATOR))
		{
			std::string filePath = pathSplit + '/' + userInput;

			if (access(filePath.c_str(), X_OK) == 0)
			{
				std::cout << userInput << " is "
					<< filePath << std::endl;
				return;
			}
		}

		std::cout << userInput << ": not found" << std::endl;
	}
}

// Logic for echo command using the string part apart from "echo "
void commandEcho(std::string userInput)
{
	userInput.erase(0,5);
	std::cout << userInput << std::endl;
}

// Basic system of Read Evaluate and Printing for the Shell
int REP_System()
{
	std::cout << "$ ";

	std::string userInput;
	std::getline(std::cin, userInput);

	// Checks for appropriate user commands
	if (userInput == "exit") {
		return -1;
	}
	if (userInput.substr(0,5) == "echo ") {
		commandEcho(userInput);
		return 0;
	}
	if (userInput.substr(0,5) == "type ") {
		commandType(userInput);
		return 0;
	}

	runExternalCommand(userInput);
	return 0;
}

int main()
{
	// Flush after every std::cout / std:cerr
	std::cout << std::unitbuf;
	std::cerr << std::unitbuf;

	// Loop to keep the shell running and continuously prompting
	while (1)
	{
		int returnVal;
		returnVal = REP_System();

		// Checks for invalid running or breakage
		if (returnVal == -1) { break; }
	}

	return 0;
}