#pragma once

#include <visualizer.hpp>
#include <sorts.hpp>

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>


std::vector<int> generateRandomArray(int length, int minValue, int maxValue);
std::vector<int> generateShuffledArray(int length);
std::vector<int> shuffleArray(std::vector<int>& arr);

void run_sort_anim(Visualizer& v, std::vector<int>& arr, void (*alg)(Visualizer&, std::vector<int>&), bool oneshot);
void shuffle_array_anim(Visualizer& v, std::vector<int>& arr, int size);



