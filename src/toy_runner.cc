// Toy Robot coding challenge
//  Author: Anoop R. S.
//  Date: 6/11/2022

#include "toy_runner.h"
#include "constants.h"

ToyRunner::ToyRunner() {
  table_.reset(new Table());
  toy_.reset(new ToyRobot(table_.get()));
}

ToyRunner::ToyRunner(const std::string &file_path) : ToyRunner() {
  ip_file_.open(file_path);
}

ToyRunner::~ToyRunner() {
  ip_file_.close();
}

// Process commands either from stdin or from file, depending on whether
// ip_file_ is open or not
void ToyRunner::ProcessCommands() {
  if (!ip_file_.is_open()) {
    while (true) {
      int choice = 0;
      std::string command;
      std::string result;
      std::cout << "\n\n1. PLACE X,Y,F\n2. MOVE\n3. LEFT\n4. RIGHT\n5. "
                   "REPORT\nCtrl+C to Quit\nEnter choice : ";
      std::cin >> choice;
      switch (choice) {
        case 1: {
          // PLACE X,Y,Z
          command.append(constants::kPlace + " ");
          int x_pos = 0;
          int y_pos = 0;
          int f_choice = 0;
          std::cout << "Enter X : ";
          std::cin >> x_pos;
          command.append(std::to_string(x_pos) + ",");
          std::cout << "Enter Y : ";
          std::cin >> y_pos;
          command.append(std::to_string(y_pos) + ",");
          std::cout << "Enter F [North(1) South(2) East(3) West(4)] : ";
          std::cin >> f_choice;
          switch (f_choice) {
            case 1:
              command.append(constants::kNorth);
              break;
            case 2:
              command.append(constants::kSouth);
              break;
            case 3:
              command.append(constants::kEast);
              break;
            case 4:
              command.append(constants::kWest);
              break;
            default:
              command.clear();
              break;
          }
        } break;
        case 2:
          // Move
          command.append(constants::kMove);
          break;
        case 3:
          command.append(constants::kLeft);
          break;
        case 4:
          command.append(constants::kRight);
          break;
        case 5:
          command.append(constants::kReport);
          break;
        default:
          command.clear();
          break;
      }
      if (!command.empty()) {
        const auto &ret_val = PushCommmand(command, result);
        if (ret_val) {
          std::cout << command << "\t:\tSuccess";
        } else {
          std::cout << command << "\t:\tFail";
        }
        if (ret_val && command.find(constants::kReport) != std::string::npos) {
          std::cout << " (" << result << ")";
        }
      } else {
        std::cout << "Command is not well formed. Try again\n";
      }
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  } else {
    std::string line;
    std::cout << "Executing commands from file";
    while (std::getline(ip_file_, line)) {
      std::string result;
      const auto &ret_val = PushCommmand(line, result);
      if (ret_val) {
        std::cout << "\n" << line << "\t:\tSuccess";
      } else {
        std::cout << "\n" << line << "\t:\tFail";
      }
      if (ret_val && line.find(constants::kReport) != std::string::npos) {
        std::cout << " (" << result << ")";
      }
    }
    std::cout << std::endl;
  }
}

bool ToyRunner::PushCommmand(const std::string &command, std::string &result) {
  // Issues the command to the toy and returns whether it was success or not
  if (command.find(constants::kPlace) != std::string::npos) {
    // Parse the string and extract X Y and F
    //  Convert X and Y to integer
    //  Convert F from string to Direction enum value
    Position pos;
    Direction facing_dir;
    PlaceParamParser(command, pos, facing_dir);
    return toy_->Place(pos.x_pos, pos.y_pos, facing_dir);
  }
  if (command.find(constants::kMove) != std::string::npos) {
    return toy_->Move();
  }
  if (command.find(constants::kLeft) != std::string::npos) {
    return toy_->Left();
  }
  if (command.find(constants::kRight) != std::string::npos) {
    return toy_->Right();
  }
  if (command.find(constants::kReport) != std::string::npos) {
    Position pos;
    Direction facing_dir;
    const auto &res = toy_->Report(pos, facing_dir);
    // Convert pos and facing_dir to string and place in result. It should be in
    // the format X,Y,F
    ReportParamConverter(pos, facing_dir, result);
    return res;
  }
}

void ToyRunner::PlaceParamParser(const std::string &command, Position &pos,
                                 Direction &facing_dir) {
  // Place command will be in the format PLACE X,Y,F
  //  For simplicity of processing, we are assuming that there will be no extra
  //  spaces between X Y and F
  auto temp_command = command;
  // Find the space
  const auto &space_pos = command.find_first_of(" ");
  if (std::string::npos != space_pos) {
    temp_command.assign(command.begin() + space_pos + 1, command.end());
    auto comma_pos = temp_command.find_first_of(",");
    if (std::string::npos != comma_pos) {
      const std::string &x_pos{temp_command.begin(),
                               temp_command.begin() + comma_pos};
      if (!x_pos.empty()) {
        pos.x_pos = std::stoi(x_pos);
      }
      temp_command.assign(temp_command.begin() + comma_pos + 1,
                          temp_command.end());
    }
    comma_pos = temp_command.find_first_of(",");
    if (std::string::npos != comma_pos) {
      const std::string &y_pos{temp_command.begin(),
                               temp_command.begin() + comma_pos};
      if (!y_pos.empty()) {
        pos.y_pos = std::stoi(y_pos);
      }
      temp_command.assign(temp_command.begin() + comma_pos + 1,
                          temp_command.end());
      const std::string facing_dir_str = temp_command;
      if (!facing_dir_str.empty()) {
        if (facing_dir_str == constants::kNorth) {
          facing_dir = Direction::kNorth;
        } else if (facing_dir_str == constants::kSouth) {
          facing_dir = Direction::kSouth;
        } else if (facing_dir_str == constants::kEast) {
          facing_dir = Direction::kEast;
        } else if (facing_dir_str == constants::kWest) {
          facing_dir = Direction::kWest;
        }
      }
    }
  }
}

void ToyRunner::ReportParamConverter(const Position &pos,
                                     const Direction &facing_dir,
                                     std::string &report) {
  std::string facing_dir_str;
  const std::string &x_pos = std::to_string(pos.x_pos);
  const std::string &y_pos = std::to_string(pos.y_pos);
  const auto &iter = constants::kFacingStringMap.find(facing_dir);
  if (iter != constants::kFacingStringMap.end()) {
    facing_dir_str = iter->second;
  }
  report.assign(x_pos + "," + y_pos + "," + facing_dir_str);
}
