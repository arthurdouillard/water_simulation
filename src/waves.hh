#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

std::vector<float>* init_height_map(unsigned char* data,
                                    float width, float height, float chan,
                                    float rec_width);

std::vector<float>* init_plane(int size, float width, float height);
std::vector<unsigned int>* init_indices(int size);

unsigned int load_object(std::vector<float>* vertices, std::vector<unsigned int>* indices);
unsigned int load_cubemap(void);

void top_left(std::vector<float>& vertices, float x, float y, float z);
void top_right(std::vector<float>& vertices, float width, float x, float y, float z);
void bottom_left(std::vector<float>& vertices, float width, float x, float y, float z);
void bottom_right(std::vector<float>& vertices, float width, float x, float y, float z);