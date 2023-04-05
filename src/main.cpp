#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <cmath>
#include <iostream>
#include <CellurarGenerator.h>

using namespace std;


#define CELL_L width*height*4



int main(){

    const int width=600, height=600;

    sf::RenderWindow window(sf::VideoMode(width, height), "Cellurar Texture Generator");

    
    CellurarGenerator cellurarGen({width, height});
    double* values = cellurarGen.generate(100);


    sf::Uint8* cellurarStruct = new sf::Uint8[width*height*4];
    
    sf::Texture texture;
    texture.create(width, height);

    sf::Sprite sprite{texture};

    double intensity = 5.;

    for(int i = 0; i < CELL_L; i += 4){
        sf::Uint8 val = static_cast<sf::Uint8>(values[i/4]*255);
        cellurarStruct[i] = val;
        cellurarStruct[i+1] = val;
        cellurarStruct[i+2] = val;
        cellurarStruct[i+3] = 255;
    } 



    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::EventType::Closed){
                window.close();
            }
        }

        texture.update(cellurarStruct);
        window.clear();
        window.draw(sprite);
        window.display();
    }

    delete [] cellurarStruct;


    return 0;
}