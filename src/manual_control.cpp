#include "../headers/manual_control.hpp"

#include <iostream>

std::vector<float> manual_control(std::vector<float> inputs) {
	std::cout << "Your inputs:\n";
	for(size_t i = 0; i < inputs.size(); i++) {
		std::cout << inputs[i] << "\n";
	}
	std::vector<float> toReturn = {};
	for(int i = 1; ; i++) {
		float floatValue = 0;
		std::string userInput;
		while(true) {
			std::cout << "\n\nEnter your " << i << ". output (or 'd' for 'done'): ";
			std::getline(std::cin, userInput);
			if(userInput == "d") {break;}
			try {
				floatValue = std::stof(userInput);
				break;
			} catch(std::exception& e) {
				std::cout << "Invalid, please retry\n";
			}
		}
		if(userInput == "d") {break;}

		toReturn.push_back(floatValue);
	}

	return toReturn;
}
