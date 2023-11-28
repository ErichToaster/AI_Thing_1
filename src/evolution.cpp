#include "../headers/evolution.hpp"

#include <ctime>
#include <cstdlib>

std::vector<std::vector<std::vector<float>>> mutate(std::vector<std::vector<std::vector<float>>> input) {
	std::srand(std::time(0));
	for(size_t i = 0; i < input.size(); i++) {
		for(size_t j = 0; j < input[i].size(); j++) {
			for(size_t k = 0; k < input[i][j].size(); k++) {
				float randomAlteration = (std::rand() % 200 - 100) / 100.0;
				input[i][j][k] += randomAlteration;
			}
		}
	}
	return input;
}

std::vector<std::vector<std::vector<float>>> recombination(std::vector<std::vector<std::vector<float>>> parentA, std::vector<std::vector<std::vector<float>>> parentB) {
	std::srand(std::time(0));
	for(size_t i = 0; i < parentA.size(); i++) {
		for(size_t j = 0; j < parentA[i].size(); j++) {
			for(size_t k = 0; k < parentA[i][j].size(); k++) {
				if(std::rand() % 2) {
					parentA[i][j][k] = parentB[i][j][k];
				}
			}
		}
	}
	return parentA;
}

std::vector<std::vector<std::vector<std::vector<float>>>> evolution(std::vector<std::vector<std::vector<std::vector<float>>>> pool, std::vector<float> scores, float purgeRatePercentage) {

	std::srand(std::time(0));

	int numToPurge = pool.size() * purgeRatePercentage;

	for(int i = 0; i < numToPurge; i++) {
		float maxValue = scores[0];
		size_t maxPosition = 0;
		for(size_t j = 0; j < scores.size(); j++) {
			if(scores[j] > maxValue) {
				maxValue = scores[j];
				maxPosition = j;
			}
		}
		scores.erase(scores.begin() + maxPosition);
		pool.erase(pool.begin() + maxPosition);
	}

	std::vector<std::vector<std::vector<std::vector<float>>>> toAdd = {};
	for(int i = 0; i < numToPurge; i++) {
		toAdd.push_back(mutate(recombination(pool[std::rand() % pool.size()], pool[std::rand() % pool.size()])));
	}
	while(toAdd.size() > 0) {
		pool.push_back(toAdd[0]);
		toAdd.erase(toAdd.begin());
	}

	return pool;
}
