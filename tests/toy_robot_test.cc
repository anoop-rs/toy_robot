// Toy Robot coding challenge
//  Author: Anoop R. S.
//  Date: 6/11/2022

// Tests for testing toy robot
#include "toy_robot.h"
#include <iostream>
#include <memory>
#include "gtest/gtest.h"
#include "table.h"

class ToyRobotTest : public ::testing::Test {
 protected:
  void SetUp() override {
    table.reset(new Table());
    toy.reset(new ToyRobot(table.get()));
  }
  void TearDown() override {}
  std::unique_ptr<Table> table;
  std::unique_ptr<Toy> toy;
};

TEST_F(ToyRobotTest, TestPlace) {
  toy->Place(0, 0, Direction::kNorth);
  Position pos;
  Direction facing_dir;
  ASSERT_EQ(toy->Report(pos, facing_dir), true);
  ASSERT_EQ(pos.x_pos, 0);
  ASSERT_EQ(pos.y_pos, 0);
  ASSERT_EQ(facing_dir, Direction::kNorth);
}

TEST_F(ToyRobotTest, TestLeftRight) {
  toy->Place(0, 0, Direction::kNorth);
  toy->Left();
  toy->Right();
  Position pos;
  Direction facing_dir;
  ASSERT_EQ(toy->Report(pos, facing_dir), true);
  ASSERT_EQ(pos.x_pos, 0);
  ASSERT_EQ(pos.y_pos, 0);
  ASSERT_EQ(facing_dir, Direction::kNorth);
}

TEST_F(ToyRobotTest, TestLeft) {
  toy->Place(0, 0, Direction::kNorth);
  toy->Left();
  Position pos;
  Direction facing_dir;
  ASSERT_EQ(toy->Report(pos, facing_dir), true);
  ASSERT_EQ(pos.x_pos, 0);
  ASSERT_EQ(pos.y_pos, 0);
  ASSERT_EQ(facing_dir, Direction::kWest);
}

TEST_F(ToyRobotTest, TestRight) {
  toy->Place(0, 0, Direction::kNorth);
  toy->Right();
  Position pos;
  Direction facing_dir;
  ASSERT_EQ(toy->Report(pos, facing_dir), true);
  ASSERT_EQ(pos.x_pos, 0);
  ASSERT_EQ(pos.y_pos, 0);
  ASSERT_EQ(facing_dir, Direction::kEast);
}

TEST_F(ToyRobotTest, TestRightWithoutPlacing) {
  ASSERT_EQ(toy->Right(), false);
}

TEST_F(ToyRobotTest, TestLeftWithoutPlacing) {
  ASSERT_EQ(toy->Left(), false);
}

TEST_F(ToyRobotTest, TestReportWithoutPlacing) {
  Position pos;
  Direction facing_dir;
  ASSERT_EQ(toy->Report(pos, facing_dir), false);
}

TEST_F(ToyRobotTest, TestPlaceOutside) {
  ASSERT_EQ(toy->Place(5, 5, Direction::kNorth), false);
}

TEST_F(ToyRobotTest, TestPlaceFirstCorner) {
  ASSERT_EQ(toy->Place(0, 0, Direction::kNorth), true);
}

TEST_F(ToyRobotTest, TestPlaceSecondCorner) {
  ASSERT_EQ(toy->Place(0, 4, Direction::kNorth), true);
}

TEST_F(ToyRobotTest, TestPlaceThirdCorner) {
  ASSERT_EQ(toy->Place(4, 4, Direction::kNorth), true);
}

TEST_F(ToyRobotTest, TestPlaceFourthCorner) {
  ASSERT_EQ(toy->Place(4, 0, Direction::kNorth), true);
}

TEST_F(ToyRobotTest, TestMoveAfterPlacingOnEdge) {
  ASSERT_EQ(toy->Place(4, 4, Direction::kNorth), true);
  ASSERT_EQ(toy->Move(), false);
}

TEST_F(ToyRobotTest, Rotate360Left) {
  ASSERT_EQ(toy->Place(4, 4, Direction::kNorth), true);
  ASSERT_EQ(toy->Left(), true);
  Position pos;
  Direction facing_dir;
  ASSERT_EQ(toy->Report(pos, facing_dir), true);
  ASSERT_EQ(facing_dir, Direction::kWest);
  ASSERT_EQ(toy->Left(), true);
  ASSERT_EQ(toy->Report(pos, facing_dir), true);
  ASSERT_EQ(facing_dir, Direction::kSouth);
  ASSERT_EQ(toy->Left(), true);
  ASSERT_EQ(toy->Report(pos, facing_dir), true);
  ASSERT_EQ(facing_dir, Direction::kEast);
  ASSERT_EQ(toy->Left(), true);
  ASSERT_EQ(toy->Report(pos, facing_dir), true);
  ASSERT_EQ(facing_dir, Direction::kNorth);
}

TEST_F(ToyRobotTest, Rotate360Right) {
  ASSERT_EQ(toy->Place(4, 4, Direction::kNorth), true);
  ASSERT_EQ(toy->Right(), true);
  Position pos;
  Direction facing_dir;
  ASSERT_EQ(toy->Report(pos, facing_dir), true);
  ASSERT_EQ(facing_dir, Direction::kEast);
  ASSERT_EQ(toy->Right(), true);
  ASSERT_EQ(toy->Report(pos, facing_dir), true);
  ASSERT_EQ(facing_dir, Direction::kSouth);
  ASSERT_EQ(toy->Right(), true);
  ASSERT_EQ(toy->Report(pos, facing_dir), true);
  ASSERT_EQ(facing_dir, Direction::kWest);
  ASSERT_EQ(toy->Right(), true);
  ASSERT_EQ(toy->Report(pos, facing_dir), true);
  ASSERT_EQ(facing_dir, Direction::kNorth);
}

TEST_F(ToyRobotTest, InvalidBackward) {
  ASSERT_EQ(toy->Place(0, 0, Direction::kNorth), true);
  ASSERT_EQ(toy->Right(), true);
  ASSERT_EQ(toy->Right(), true);
  Position pos;
  Direction facing_dir;
  ASSERT_EQ(toy->Report(pos, facing_dir), true);
  ASSERT_EQ(facing_dir, Direction::kSouth);
  ASSERT_EQ(toy->Move(), false);
}

TEST_F(ToyRobotTest, InvalidMoveOutNorth) {
  // Try to move forward and outside the table
  ASSERT_EQ(toy->Place(0, 0, Direction::kNorth), true);
  ASSERT_EQ(toy->Move(), true);
  ASSERT_EQ(toy->Move(), true);
  ASSERT_EQ(toy->Move(), true);
  ASSERT_EQ(toy->Move(), true);
  ASSERT_EQ(toy->Move(), false);
}

TEST_F(ToyRobotTest, InvalidMoveOutEast) {
  // Try to move forward and outside the table
  ASSERT_EQ(toy->Place(0, 0, Direction::kEast), true);
  ASSERT_EQ(toy->Move(), true);
  ASSERT_EQ(toy->Move(), true);
  ASSERT_EQ(toy->Move(), true);
  ASSERT_EQ(toy->Move(), true);
  ASSERT_EQ(toy->Move(), false);
}

TEST_F(ToyRobotTest, InvalidMoveSouthValidMoveNorth) {
  // Try to move forward and outside the table
  ASSERT_EQ(toy->Place(0, 0, Direction::kSouth), true);
  ASSERT_EQ(toy->Move(), false);
  ASSERT_EQ(toy->Left(), true);
  ASSERT_EQ(toy->Left(), true);
  ASSERT_EQ(toy->Move(), true);
}

TEST_F(ToyRobotTest, VisitAllOuterCells) {
  // Starting from 0,0 and facing North, do a visit of all outer cells so that
  // toy robot ends up in 0,0 and facing North
  ASSERT_EQ(toy->Place(0, 0, Direction::kNorth), true);
  ASSERT_EQ(toy->Move(), true);
  ASSERT_EQ(toy->Move(), true);
  ASSERT_EQ(toy->Move(), true);
  ASSERT_EQ(toy->Move(), true);
  Position pos;
  Direction facing_dir;
  ASSERT_EQ(toy->Right(), true);
  ASSERT_EQ(toy->Report(pos, facing_dir), true);
  ASSERT_EQ(pos.x_pos, 0);
  ASSERT_EQ(pos.y_pos, 4);
  ASSERT_EQ(facing_dir, Direction::kEast);
  ASSERT_EQ(toy->Move(), true);
  ASSERT_EQ(toy->Move(), true);
  ASSERT_EQ(toy->Move(), true);
  ASSERT_EQ(toy->Move(), true);
  ASSERT_EQ(toy->Right(), true);
  ASSERT_EQ(toy->Report(pos, facing_dir), true);
  ASSERT_EQ(pos.x_pos, 4);
  ASSERT_EQ(pos.y_pos, 4);
  ASSERT_EQ(facing_dir, Direction::kSouth);
  ASSERT_EQ(toy->Move(), true);
  ASSERT_EQ(toy->Move(), true);
  ASSERT_EQ(toy->Move(), true);
  ASSERT_EQ(toy->Move(), true);
  ASSERT_EQ(toy->Right(), true);
  ASSERT_EQ(toy->Report(pos, facing_dir), true);
  ASSERT_EQ(pos.x_pos, 4);
  ASSERT_EQ(pos.y_pos, 0);
  ASSERT_EQ(facing_dir, Direction::kWest);
  ASSERT_EQ(toy->Move(), true);
  ASSERT_EQ(toy->Move(), true);
  ASSERT_EQ(toy->Move(), true);
  ASSERT_EQ(toy->Move(), true);
  ASSERT_EQ(toy->Right(), true);
  ASSERT_EQ(toy->Report(pos, facing_dir), true);
  ASSERT_EQ(pos.x_pos, 0);
  ASSERT_EQ(pos.y_pos, 0);
  ASSERT_EQ(facing_dir, Direction::kNorth);
}

TEST_F(ToyRobotTest, InvalidPlace) {
  ASSERT_EQ(toy->Place(0xff, 0xff, Direction::kNorth), false);
}

TEST_F(ToyRobotTest, InvalidDirection) {
  ASSERT_EQ(toy->Place(0, 0, Direction::kInvalid), false);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}