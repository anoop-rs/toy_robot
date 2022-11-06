INC=-I./include -I./src
CXX=g++
CXXFLAGS = -std=c++17 -pthread
LIBS = -L./lib/ -lgtest -lgtest_main 

all: toy_robot_runner toy_robot_test clean

main.o: ./src/main.cc
	$(CXX) $(CXXFLAGS) $(INC) -c ./src/main.cc 

toy_runner.o: ./src/toy_runner.cc
	$(CXX) $(CXXFLAGS) $(INC) -c ./src/toy_runner.cc
	
toy_robot_runner: main.o toy_runner.o table.o toy_robot.o
	$(CXX) $(CXXFLAGS) $(INC) -o toy_robot_runner main.o toy_runner.o table.o toy_robot.o

toy_robot.o: ./src/toy_robot.cc
	$(CXX) $(CXXFLAGS) $(INC) -c ./src/toy_robot.cc

table.o: ./src/table.cc
	$(CXX) $(CXXFLAGS) $(INC) -c ./src/table.cc

toy_robot_test.o: ./tests/toy_robot_test.cc
	$(CXX) $(CXXFLAGS) $(INC) -c ./tests/toy_robot_test.cc

toy_robot_test: toy_robot_test.o table.o toy_robot.o
	$(CXX) $(CXXFLAGS) $(INC) -o toy_robot_test toy_robot_test.o table.o toy_robot.o $(LIBS)
	
.PHONY: clean
clean:
	rm -f *.o
