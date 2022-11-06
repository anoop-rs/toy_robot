// Toy Robot coding challenge
//  Author: Anoop R. S.
//  Date: 6/11/2022

#ifndef SRC_CONSTANTS_H_
#define SRC_CONSTANTS_H_

#include <string>
#include <unordered_map>
#include "toy_robot.h"

namespace constants {
// All string constans used frequently are defined in this namespace
// Commands
const std::string &kPlace = "PLACE";
const std::string &kMove = "MOVE";
const std::string &kLeft = "LEFT";
const std::string &kRight = "RIGHT";
const std::string &kReport = "REPORT";
// Directions
const std::string &kNorth = "NORTH";
const std::string &kSouth = "SOUTH";
const std::string &kEast = "EAST";
const std::string &kWest = "WEST";
// Map to convert the Direction enum values to printable format, so that this
// map can be looked up when printing the facing
const std::unordered_map<Direction, std::string> kFacingStringMap{
    {Direction::kNorth, kNorth},
    {Direction::kSouth, kSouth},
    {Direction::kEast, kEast},
    {Direction::kWest, kWest}};
}  // namespace constants

#endif