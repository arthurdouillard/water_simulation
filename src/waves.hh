#ifndef WAVES_H
# define WAVES_H

#include <vector>

std::vector<float>* init_waves(int size, float width);
std::vector<unsigned int>* init_indices(int size);

void top_left(std::vector<float>& vertices, float x, float y, float z);
void top_right(std::vector<float>& vertices, float width, float x, float y, float z);
void bottom_left(std::vector<float>& vertices, float width, float x, float y, float z);
void bottom_right(std::vector<float>& vertices, float width, float x, float y, float z);

#endif