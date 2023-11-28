#pragma once

#include <vector>
#include <iostream>

std::vector<std::vector<std::vector<float>>> get_random_network(std::vector<int> layerSizes);
void print_net(std::vector<std::vector<std::vector<float>>> toPrint);
