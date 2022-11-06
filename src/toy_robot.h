// Toy Robot coding challenge
//  Author: Anoop R. S.
//  Date: 6/11/2022

#ifndef SRC_TOY_ROBOT_H_
#define SRC_TOY_ROBOT_H_

#include "table.h"
#include "toy.h"

// Class for implementing the functionalities of toy robot.
// It also implements Place, Let, Right, Move and Report actions of the toy
// While creating the toy robot, it accepts an instance of the table where it
// will move around
class ToyRobot : public Toy {
 private:
  Position pos_;
  bool placed_{false};
  Table *table_;
  Direction facing_dir_;

 public:
  ToyRobot(Table *);
  virtual ~ToyRobot();
  bool Place(const uint8_t &, const uint8_t &, const Direction &);
  bool Move();
  bool Left();
  bool Right();
  bool Report(Position &, Direction &);
};

#endif
