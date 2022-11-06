// Toy Robot coding challenge
//  Author: Anoop R. S.
//  Date: 6/11/2022

#ifndef SRC_TOY_H_
#define SRC_TOY_H_

#include <stdint.h>

// Enum for storing the direction which robot is facing
enum class Direction { kInvalid, kNorth, kSouth, kEast, kWest };

// Struct for grouping together position of toy
struct Position {
  uint8_t x_pos;
  uint8_t y_pos;
};

// Interface for a toy which will be moving around a table.
class Toy {
 public:
  virtual bool Place(const uint8_t &, const uint8_t &, const Direction &) = 0;
  virtual bool Move() = 0;
  virtual bool Left() = 0;
  virtual bool Right() = 0;
  virtual bool Report(Position &, Direction &) = 0;
  virtual ~Toy() {}
};

#endif