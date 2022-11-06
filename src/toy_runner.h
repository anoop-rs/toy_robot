// Toy Robot coding challenge
//  Author: Anoop R. S.
//  Date: 6/11/2022

#ifndef SRC_TOY_RUNNER_H_
#define SRC_TOY_RUNNER_H_

#include <limits.h>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <sstream>
#include <string>
#include "table.h"
#include "toy.h"

// Support class for running toy robot. This class creates an instance of table
// and toy robot. Then it performs either of:
//  1. Processing commands from file
//  2. Processing user input
class ToyRunner {
 private:
  std::unique_ptr<Table> table_;
  std::unique_ptr<Toy> toy_;
  std::ifstream ip_file_;
  void PlaceParamParser(const std::string &, Position &, Direction &);
  void ReportParamConverter(const Position &, const Direction &, std::string &);
  bool PushCommmand(const std::string &, std::string &);

 public:
  ToyRunner();
  ToyRunner(const std::string &);
  ~ToyRunner();
  void ProcessCommands();
};

#endif