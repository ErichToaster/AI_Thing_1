#include "../headers/tools.hpp"
#include <cstdlib>
#include <ctime>

std::vector<std::vector<std::vector<float>>> get_random_network(std::vector<int> layerSizes) {
	std::srand(std::time(0));
	std::vector<std::vector<std::vector<float>>> toReturn = {};

	(void)layerSizes;
	for(size_t i = 1; i < layerSizes.size(); i++) {
		std::vector<std::vector<float>> toAdd = {};
		for(int j = 0; j < layerSizes[i]; j++) {
			std::vector<float> toAppend = {};
			for(int k = 0; k < layerSizes[i-1]; k++) {
				toAppend.push_back(static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * 2.0f);
			}
			toAdd.push_back(toAppend);
		}
		toReturn.push_back(toAdd);
	}
	return toReturn;
}

void print_net(std::vector<std::vector<std::vector<float>>> toPrint) {

	std::cout << "Network {\n";
	for(size_t i = 0; i < toPrint.size(); i++) {
		std::cout << "  Connections from Layer " << i << " to Layer " << (i+1) << " {\n";
		for(size_t j = 0; j < toPrint[i].size(); j++) {
			std::cout << "    Connections to neuron " << j << " {\n";
			for(size_t k = 0; k < toPrint[i][j].size(); k++) {
				std::cout << "      Connection from neuron " << k << ": " << toPrint[i][j][k] << "\n";
			}
			std::cout << "    }\n";
		}
		std::cout << "  }\n";
	}
	std::cout << "}\n";
	return;
}
