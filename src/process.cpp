#include "../headers/process.hpp"

#include <cmath>

float sigmoid(float input) {
	return 1.0 / (1.0 + std::exp(-input));
}

std::vector<float> process(std::vector<float> inputs, std::vector<std::vector<std::vector<float>>> network) {
	
	std::vector<std::vector<float>> values = {};
	for(size_t i = 0; i < network.size(); i++) {
		std::vector<float> toAppend = {};
		for(size_t j = 0; j < network[i].size(); j++) {
			float toCalculate = 0;
			for(size_t k = 0; k < network[i][j].size(); k++) {
				if(i == 0) {
					toCalculate += (inputs[k] * network[i][j][k]);
				} else {
					toCalculate += (values[i-1][k] * network[i][j][k]);
				}
			}
			toAppend.push_back(sigmoid(toCalculate));
		}
		values.push_back(toAppend);
	}
	return values.back();
}
