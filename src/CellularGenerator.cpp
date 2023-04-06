#include <CellularGenerator.h>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

CellularGenerator::CellularGenerator(Vector2i size):
size{size}, rng{dev()}, rand{max(size.x, size.y)}
{
    values = new double [size.size()];
}

Vector2i CellularGenerator::get_size(){
    return size;
}

double* CellularGenerator::generate(int pointsNum, Type type, bool invert){
    vector<Vector2i> points = generate_random_points(pointsNum);

    double minDist = INFINITY, maxDist = 0; 
    for(int x = 0; x < size.x; x++){
        for(int y = 0; y < size.y; y++){
            vector<double> distBuffer;
            double dist;

            for(auto p : points){
                dist = sqrt(pow(p.x-x,2)+pow(p.y-y,2));
                distBuffer.push_back(dist);
            }
            

            sort(distBuffer.begin(), distBuffer.end());
            switch(type){
                case Type::Tiled:
                    dist = distBuffer[1] - distBuffer[0];
                    break;
                case Type::Smooth:
                    dist = distBuffer[1] * distBuffer[0];
                    break;
                default:
                    dist = distBuffer[0];
                    break;
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
        if(invert)
            values[i] = 1 - values[i];
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

