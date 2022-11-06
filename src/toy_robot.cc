// Toy Robot coding challenge
//  Author: Anoop R. S.
//  Date: 6/11/2022

#include "toy_robot.h"

// ToyRobot: Constructor
// Input: Pointer to Table
ToyRobot::ToyRobot(Table *table) {
  // Assign the maximum values as initial values of x_pos and y_pos
  pos_.x_pos = 0xff;
  pos_.y_pos = 0xff;
  table_ = table;
  facing_dir_ = Direction::kInvalid;
}

// Place : Place toy robot at the specified position facing the direction
// provided
//  Inputs: x_pos - X position
//  y_pos - Y position
//  facing_direction - Direction the toy robot will face
//  Output : True if placement is success, false if failed
bool ToyRobot::Place(const uint8_t &x_pos, const uint8_t &y_pos,
                     const Direction &facing_direction) {
  // Place toy robot on the table
  // Check with the table whether the position is valid or not
  bool ret = false;
  if (table_ && table_->IsValidPos(x_pos, y_pos)) {
    // The position is valid
    pos_.x_pos = x_pos;
    pos_.y_pos = y_pos;
    if (facing_direction != Direction::kInvalid) {
      facing_dir_ = facing_direction;
      placed_ = true;
      ret = true;
    }
  }
  // Otherwise, the status of the toy will be invalid
  return ret;
}

// Move: Move the toy robot by one cell along the direction facing
//  Input : None
//  Output : True if move is success, false if the move results in toy robot
//  going out of table or it was not placed
bool ToyRobot::Move() {
  // When moving, the facing direction will not change. Moving is always one
  // cell at a time
  bool ret = false;
  // Depending on the direction the toy is facing, we need to either increment
  // the x coordinate or the y coordinate
  //  Toy can move only if it is placed already
  if (placed_) {
    uint8_t new_x_pos = 0;
    uint8_t new_y_pos = 0;
    switch (facing_dir_) {
      case Direction::kNorth:
        new_x_pos = pos_.x_pos;
        new_y_pos = pos_.y_pos + 1;
        break;
      case Direction::kSouth:
        new_x_pos = pos_.x_pos;
        new_y_pos = pos_.y_pos - 1;
        break;
      case Direction::kEast:
        new_x_pos = pos_.x_pos + 1;
        new_y_pos = pos_.y_pos;
        break;
      case Direction::kWest:
        new_x_pos = pos_.x_pos - 1;
        new_y_pos = pos_.y_pos;
        break;
      default:
        new_x_pos = pos_.x_pos;
        new_y_pos = pos_.y_pos;
        break;
    }
    // Check the validity of new positions
    if (table_ && table_->IsValidPos(new_x_pos, new_y_pos)) {
      pos_.x_pos = new_x_pos;
      pos_.y_pos = new_y_pos;
      ret = true;
    }
  }
  return ret;
}

// Left : Rotate toy robot left
//   Input : None
//   Output : True if rotation is success, false if robot was not placed
bool ToyRobot::Left() {
  bool ret = false;
  if (placed_ && facing_dir_ != Direction::kInvalid) {
    switch (facing_dir_) {
      case Direction::kNorth:
        facing_dir_ = Direction::kWest;
        break;
      case Direction::kSouth:
        facing_dir_ = Direction::kEast;
        break;
      case Direction::kEast:
        facing_dir_ = Direction::kNorth;
        break;
      case Direction::kWest:
        facing_dir_ = Direction::kSouth;
        break;
      default:
        break;
    }
    ret = true;
  }
  return ret;
}

// Right : Rotate toy robot right
//   Input : None
//   Output : True if rotation is success, false if robot was not placed
bool ToyRobot::Right() {
  bool ret = false;
  if (placed_ && facing_dir_ != Direction::kInvalid) {
    switch (facing_dir_) {
      case Direction::kNorth:
        facing_dir_ = Direction::kEast;
        break;
      case Direction::kSouth:
        facing_dir_ = Direction::kWest;
        break;
      case Direction::kEast:
        facing_dir_ = Direction::kSouth;
        break;
      case Direction::kWest:
        facing_dir_ = Direction::kNorth;
        break;
      default:
        break;
    }
    ret = true;
  }
  return ret;
}

// Report: report the position of toy robot and direction it is facing
//  Inputs : pos - Reference to Position. Position of robot will be returned
//  via this variable
// facing_dir - Reference to Direction. Robot's direction will be returned via
// this variable
// Output : False if robot was not placed, else true
bool ToyRobot::Report(Position &pos, Direction &facing_dir) {
  bool ret = false;
  if (placed_) {
    pos = pos_;
    facing_dir = facing_dir_;
    ret = true;
  }
  return ret;
}

//~ToyRobot : Destructor
ToyRobot::~ToyRobot() {}
