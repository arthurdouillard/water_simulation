#include "waves.hh"

void init_waves(std::vector<float>& vertices, int size, float width)
{
    float start = -(size / 2) * width;

    float pos_y = 0.0f;
    for (int x = 0; x < size; x++)
    {
        float pos_x = start + x * width;
        for (int z = 0; z < size; z++)
        {
            float pos_z = -(start + z * width);

            top_left(vertices, pos_x, pos_y, pos_z);
            bottom_left(vertices, width, pos_x, pos_y, pos_z);
            bottom_right(vertices, width, pos_x, pos_y, pos_z);

            top_left(vertices, pos_x, pos_y, pos_z);
            bottom_right(vertices, width, pos_x, pos_y, pos_z);
            top_right(vertices, width, pos_x, pos_y, pos_z);
        }
    }
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

