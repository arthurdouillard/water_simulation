#include "waves.hh"

std::vector<unsigned int>* init_indices(int size)
{
    auto indices = new std::vector<unsigned int>();

    for (int z = 0; z < size - 1; ++z)
	{
	    for (int x = 0; x < size - 1; ++x)
	    {
            int start = x + z * size;
            indices->push_back(start);
            indices->push_back(start + 1);
            indices->push_back(start + size);
            indices->push_back(start + 1);
            indices->push_back(start + 1 + size);
            indices->push_back(start + size);
	    }
    }

    return indices;
}

std::vector<float>* init_waves(int size, float width)
{
    auto vertices = new std::vector<float>();

    float start = -(size / 2) * width;

    float pos_y = 0.0f;
    for (int x = 0; x < size; x++)
    {
        float pos_x = start + x * width;
        for (int z = 0; z < size; z++)
        {
            float pos_z = (start + z * width);
            vertices->push_back(pos_x);
            vertices->push_back(pos_y);
            vertices->push_back(pos_z);
        }
    }
    return vertices;
}

void top_left(std::vector<float>& vertices, float x, float y, float z)
{
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(z);

    vertices.push_back(x);
    vertices.push_back(z);
}

void top_right(std::vector<float>& vertices, float width, float x, float y, float z)
{
    vertices.push_back(x + width);
    vertices.push_back(y);
    vertices.push_back(z);

    vertices.push_back(x + width);
    vertices.push_back(z);
}

void bottom_left(std::vector<float>& vertices, float width, float x, float y, float z)
{
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(z + width);

    vertices.push_back(x);
    vertices.push_back(z + width);
}

void bottom_right(std::vector<float>& vertices, float width, float x, float y, float z)
{
    vertices.push_back(x + width);
    vertices.push_back(y);
    vertices.push_back(z + width);

    vertices.push_back(x + width);
    vertices.push_back(z + width);
}

