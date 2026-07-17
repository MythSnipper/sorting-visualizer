#pragma once

#include <visualizer.hpp>
#include <vector>



void selection_sort(Visualizer& v, std::vector<int>& arr);

void double_selection_sort(Visualizer& v, std::vector<int>& arr);

void insertion_sort(Visualizer& v, std::vector<int>& arr);

void binary_insertion_sort(Visualizer& v, std::vector<int>& arr);

void bubble_sort(Visualizer& v, std::vector<int>& arr);

void cocktail_shaker_sort(Visualizer& v, std::vector<int>& arr);

void quick_sort(Visualizer& v, std::vector<int>& arr);
void quick_sort_helper(Visualizer& v, std::vector<int>& arr, int start, int end);

void merge_sort(Visualizer& v, std::vector<int>& arr);
void merge_sort_helper(Visualizer& v, std::vector<int>& arr, int start, int end);

void heap_sort(Visualizer& v, std::vector<int>& arr);
void heap_sort_sift_down(Visualizer& v, std::vector<int>& arr, int start, int end);
bool heap_sort_get_left_child_i(Visualizer& v, std::vector<int>& arr, int index, int& ret, int heapsize);
bool heap_sort_get_right_child_i(Visualizer& v, std::vector<int>& arr, int index, int& ret, int heapsize);

void comb_sort(Visualizer& v, std::vector<int>& arr);
int comb_sort_get_next_combsize(int combsize);
bool comb_sort_comb(Visualizer& v, std::vector<int>& arr, int combsize);




void bogo_sort(Visualizer& v, std::vector<int>& arr);

void stalin_sort(Visualizer& v, std::vector<int>& arr);








