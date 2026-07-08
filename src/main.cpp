#include <iostream>
#include <string>


// Logic for type command using vector to check for valid command
const std::vector<std::string> g_valid_commands = {"exit", "echo", "type"};

void commandType(std::string userInput)
{
	userInput.erase(0,5);

	auto it = std::find(std::begin(g_valid_commands), std::end(g_valid_commands), userInput);

	if (it != std::end(g_valid_commands)) {
		std::cout << userInput << " is a shell builtin" << std::endl;
	}
	else {
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
	}
	if (userInput.substr(0,5) == "type ") {
		commandType(userInput);
		return 0;
	}

	std::cout << userInput << ": command not found" << std::endl;
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
}
