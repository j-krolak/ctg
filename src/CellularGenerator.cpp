#include <CellularGenerator.h>
#include <cmath>
#include <iostream>

using namespace std;

CellularGenerator::CellularGenerator(Vector2i size):
size{size}, rng{dev()}, rand{max(size.x, size.y)}
{
    values = new double [size.size()];
}

Vector2i CellularGenerator::get_size(){
    return size;
}

double* CellularGenerator::generate(int pointsNum){
    vector<Vector2i> points = generate_random_points(pointsNum);

    double minDist = INFINITY, maxDist = 0; 
    for(int x = 0; x < size.x; x++){
        for(int y = 0; y < size.y; y++){
            double dist = INFINITY;
            double tmpDist;

            for(auto p : points){
                tmpDist = sqrt(pow(p.x-x,2)+pow(p.y-y,2));
                dist = min(dist, tmpDist);
            }
            
            minDist = min(minDist, dist);
            maxDist = max(maxDist, dist);

            values[x + size.x * y] = dist;
        }
    }

    /**
     * Normalizing points' distances
     */

    for(int i = 0; i < size.size(); i++){
        values[i] = (values[i]-minDist)/(maxDist-minDist);
    }


    return values;
}

vector<Vector2i> CellularGenerator::generate_random_points(int pointNum){
    vector<Vector2i> points;

    for(int i = 0; i < pointNum; i++)
        points.push_back(randomize_point());

    return points;
}

Vector2i CellularGenerator::randomize_point(){
    return {rand(rng)%size.x, rand(rng)%size.y};
}

CellularGenerator::~CellularGenerator(){
    delete[] values;
}

