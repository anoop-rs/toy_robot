// Toy Robot coding challenge
//  Author: Anoop R. S.
//  Date: 6/11/2022

#ifndef SRC_TABLE_H_
#define SRC_TABLE_H_

#include <stdint.h>

// Constants for storing max number of rows and columns
const uint8_t kMaxRow = 5;
const uint8_t kMaxColumn = 5;
// Class to store the table details. The table is initialised with the maximum
// values of row and column defined as constants above
class Table {
 private:
  // The size of table
  const uint8_t row_;
  const uint8_t column_;

 public:
  Table();
  ~Table();
  bool IsValidPos(const uint8_t &, const uint8_t &);
};

#endif
