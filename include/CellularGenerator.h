#pragma once

#include <random>
#include <vector>

typedef unsigned int Uint8;

struct Vector2i{
    int x;
    int y;
    int size(){
        return x*y;
    }
};

class CellularGenerator{
public:
    enum class Type{Simple, Tiled, Smooth};
    CellularGenerator(Vector2i size = {500, 500});
    Vector2i get_size();
    double* generate(int pointsNum=100, Type type = Type::Simple, bool invert = false);
    ~CellularGenerator(); 
private:
    double* values;
    Vector2i size;

    
    std::random_device dev;
    std::mt19937 rng;
    std::uniform_int_distribution<std::mt19937::result_type> rand;

    std::vector<Vector2i> generate_random_points(int pointNum);

    Vector2i randomize_point();
};