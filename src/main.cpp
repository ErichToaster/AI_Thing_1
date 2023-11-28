#include "../headers/evolution.hpp"
#include "../headers/test_environments.hpp"
#include "../headers/tools.hpp"

#include <iostream>
#include <algorithm>

int main() {

	std::vector<std::vector<std::vector<std::vector<float>>>> networks = {};
	std::vector<float> scores = {};

	for(int i = 0; i < 20; i++) {
		networks.push_back(get_random_network({3, 4, 4, 3}));
		scores.push_back(0);
	}

	while(true) {
		std::cout << networks.size() << "\n";
		for(size_t i = 0; i < networks.size(); i++) {
			if(i == 0) {
				scores[i] = testenv1(networks[i], true, false);
			} else {
				scores[i] = testenv1(networks[i], false, false);
			}
		}

		std::cout << "scores:\n";
		for(size_t i = 0; i < scores.size(); i++) {
			std::cout << scores[i] << "\n";
		}
		std::cout << "\n";
		std::string buffer;
		std::getline(std::cin, buffer);
	
		networks = evolution(networks, scores, 0.5);
	}

	return 0;
}
