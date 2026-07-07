#include <iostream>
#include <string>

int main()
{
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // Loop to keep the shell running and continuously prompting
  while (true)
  {
    std::cout << "$ ";

    // Captures the user's command in the "command" variable
    std::string command;
    std::getline(std::cin, command);

    // To exit program with "exit"
    if (command == "exit") {
      break;
    }
    // Echo command : To print the arguments passed by the user
    else if (command.substr(0,5) == "echo ") {
      std::cout << command.substr(5) << std::endl;
    }
    else {
      // Prints the "<command>: command not found" message
      std::cout << command << ": command not found" << std::endl;
    }
  }
  
}
