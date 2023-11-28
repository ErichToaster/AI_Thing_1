#include "../headers/testenv1.hpp"

#include "../headers/process.hpp"
#include "../headers/manual_control.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>

enum class direction {
	down,
	right,
	up,
	left
};

void print_grid(int posX, int posY, direction facing, int foodX, int foodY, int gridSizeX, int gridSizeY) {
	for(int y = 0; y < gridSizeY; y++) {
		for(int x = 0; x < gridSizeX; x++) {
			if(x == posX && y == posY) {
				switch(facing) {
					case direction::down:  std::cout << "V"; break;
					case direction::right: std::cout << ">"; break;
					case direction::up:    std::cout << "A"; break;
					case direction::left:  std::cout << "<"; break;
				}
			} else if(x == foodX && y == foodY) {
				std::cout << "O";
			} else {
				std::cout << "-";
			}
			std::cout << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

float testenv1(std::vector<std::vector<std::vector<float>>> network, bool visualise, bool manualControl) {

	std::srand(std::time(0));

	std::vector<int> timings = {};
	for(int i = 0; i < 10; i++) {

		if(visualise) {std::cout << "Test " << (i+1) << " out of 10\n";}

		int gridSizeX = 15;
		int gridSizeY = 15;
		int xpos = gridSizeX / 2;
		int ypos = gridSizeY / 2;
		direction facing = direction::up;
		int xfood = gridSizeX / 2;
		int yfood = gridSizeY / 2;
		while(xfood == xpos && yfood == ypos) {
			xfood = std::rand() % gridSizeX;
			yfood = std::rand() % gridSizeY;
		}

		std::vector<float> inputs = {0, 0, 0};
		//0 0 0 = no food in sight
		//1 0 0 = food to the left
		//0 1 0 = food straight ahead
		//0 0 1 = food to the right

		int timePassed = 0;
		for(int j = 0; j < 50; j++) {

			if(visualise) {print_grid(xpos, ypos, facing, xfood, yfood, gridSizeX, gridSizeY);}

			switch(facing) {
				case direction::down:
					if(yfood <= ypos) {inputs = {0, 0, 0};} else
					if(xfood >  xpos) {inputs = {1, 0, 0};} else
					if(xfood <  xpos) {inputs = {0, 0, 1};} else
					if(xfood == xpos) {inputs = {0, 1, 0};}
					break;
				case direction::right:
					if(xfood <= xpos) {inputs = {0, 0, 0};} else
					if(yfood >  ypos) {inputs = {0, 0, 1};} else
					if(yfood <  ypos) {inputs = {1, 0, 0};} else
					if(yfood == ypos) {inputs = {0, 1, 0};}
					break;
				case direction::up:
					if(yfood >= ypos) {inputs = {0, 0, 0};} else
					if(xfood >  xpos) {inputs = {0, 0, 1};} else
					if(xfood <  xpos) {inputs = {1, 0, 0};} else
					if(xfood == xpos) {inputs = {0, 1, 0};}
					break;
				case direction::left:
					if(xfood >= xpos) {inputs = {0, 0, 0};} else
					if(yfood >  ypos) {inputs = {1, 0, 0};} else
					if(yfood <  ypos) {inputs = {0, 0, 1};} else
					if(yfood == ypos) {inputs = {0, 1, 0};}
					break;
			}


			std::vector<float> outputs;
			if(manualControl) {
				outputs = manual_control(inputs);
			} else {
				outputs = process(inputs, network);
			}

			if(outputs[1] >= 0.5) {
				switch(facing) {
					case direction::down:  if(ypos < gridSizeY-1) {ypos++;} break;
					case direction::right: if(xpos < gridSizeX-1) {xpos++;} break;
					case direction::up:    if(ypos > 0)           {ypos--;} break;
					case direction::left:  if(xpos > 0)           {xpos--;} break;
				}
			} else if(outputs[0] >= 0.5 && outputs[2] < 0.5) {
				switch(facing) {
					case direction::down:  facing = direction::right; break;
					case direction::right: facing = direction::up;    break;
					case direction::up:    facing = direction::left;  break;
					case direction::left:  facing = direction::down;  break;
				}
			} else if(outputs[2] >= 0.5 && outputs[0] < 0.5) {
				switch(facing) {
					case direction::down:  facing = direction::left;  break;
					case direction::right: facing = direction::down;  break;
					case direction::up:    facing = direction::right; break;
					case direction::left:  facing = direction::up;    break;
				}
			}

			timePassed++;

			if(xpos == xfood && ypos == yfood) {break;}
		}
		if(visualise) {
			std::cout << "score: " << timePassed << "\n";
			std::string buffer;
			std::getline(std::cin, buffer);
		}

		timings.push_back(timePassed);
	}

	float totalTime = 0;
	for(size_t i = 0; i < timings.size(); i++) {
		totalTime += timings[i];
	}
	return totalTime / timings.size();
}
