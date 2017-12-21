#ifndef WAVES_H
# define WAVES_H

#include <vector>

void init_waves(std::vector<float>& vertices, int size, float width);

void top_left(std::vector<float>& vertices, float x, float y, float z);
void top_right(std::vector<float>& vertices, float width, float x, float y, float z);
void bottom_left(std::vector<float>& vertices, float width, float x, float y, float z);
void bottom_right(std::vector<float>& vertices, float width, float x, float y, float z);

#endif