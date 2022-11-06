// Toy Robot coding challenge
//  Author: Anoop R. S.
//  Date: 6/11/2022

#include <fstream>
#include <iostream>
#include "toy_runner.h"

// Main  function to start program execution
// Either provide the filename which contains a list of commands for
// manipulating the robot or blank command line argument
int main(int argc, char const *argv[]) {
  if (argc == 2) {
    // File name was provided as argument
    // Check if the file exists
    const std::string file_name = argv[1];
    std::ifstream ip_file(file_name.c_str());
    if (ip_file.good()) {
      ToyRunner runner(file_name);
      runner.ProcessCommands();
    } else {
      std::cout << "File not found" << std::endl;
    }
  } else if (argc == 1) {
    // Read from stdin
    ToyRunner runner;
    runner.ProcessCommands();
  } else {
    std::cout << "Usage : toy_robot_runner <filename with commands> or "
                 "toy_robot_runner to read commands from stdin"
              << std::endl;
    return 1;
  }
  return 0;
}
