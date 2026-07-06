#include <iostream>
#include <string>

int main() {
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
  
      // Prints the "<command>: command not found" message
      std::cout << command << ": command not found" << std::endl;
    }

}
