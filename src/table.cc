// Toy Robot coding challenge
//  Author: Anoop R. S.
//  Date: 6/11/2022

#include "table.h"

Table::Table() : row_(kMaxRow), column_(kMaxColumn) {}

Table::~Table() {}

// Input: x pos and y pos
//  Output: true if x pos and y pos is inside the table, false if x pos or y pos
//  are outside the table
bool Table::IsValidPos(const uint8_t &x_pos, const uint8_t &y_pos) {
  // Check if the position is valid or not. If the position falls
  // outside the table, it is invalid. Return false. If the position falls
  // inside the table, it is valid, return true.
  // Check if the positions are greater than 0 since 0,0 is the lowest position
  // in the table.
  return ((x_pos >= 0 && x_pos < row_) && (y_pos >= 0 && y_pos < column_))
             ? true
             : false;
}