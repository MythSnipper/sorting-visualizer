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

void shell_sort(Visualizer& v, std::vector<int>& arr);
void shell_sort_gapped_insertion(Visualizer& v, std::vector<int>& arr, int gapsize);

void radix_sort_LSD(Visualizer& v, std::vector<int>& arr, int base);
void radix_sort_LSD_base4(Visualizer& v, std::vector<int>& arr);

void radix_sort_MSD(Visualizer& v, std::vector<int>& arr, int base);
void radix_sort_MSD_helper(Visualizer& v, std::vector<int>& arr, int base, int startI, int endI, int divisor);
void radix_sort_MSD_base4(Visualizer& v, std::vector<int>& arr);

void bucket_sort_helper(Visualizer& v, std::vector<int>& arr, int NumOfBuckets);
void bucket_sort_sortbucket(Visualizer& v, std::vector<int>& arr, int startI, int endI);
void bucket_sort(Visualizer& v, std::vector<int>& arr);

void counting_sort(Visualizer& v, std::vector<int>& arr);

void gravity_sort(Visualizer& v, std::vector<int>& arr);

void pancake_sort(Visualizer& v, std::vector<int>& arr);
void pancake_sort_flip(Visualizer& v, std::vector<int>& arr, int start, int end);




void bogo_sort(Visualizer& v, std::vector<int>& arr);

void stalin_sort(Visualizer& v, std::vector<int>& arr);








