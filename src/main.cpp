#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>

#include <CellurarGenerator.h>

using namespace std;


#define CELL_L width*height*4


void display_help();

int main(int argc, char** argv){

    int width=300, height=300, points=50; 
    string output_file = "cellurarTex.png";
    bool view = false;

    if(argc >= 2){
        for(int i = 0; i < argc; i++){
            if(!strcmp(argv[i], "--help")){
                display_help();
                return 0;
            }

            if(!strcmp(argv[i], "-v")){
                view = true;
                continue;
            }

            if(!strcmp(argv[i], "-w")){
                if(i + 1 < argc){
                    width = stoi(argv[i+1]);
                }
                continue;

            }

            if(!strcmp(argv[i], "-h")){
                if(i + 1 < argc){
                    height = stoi(argv[i+1]);
                }
                continue;

            }

            if(!strcmp(argv[i], "-p")){
                if(i + 1 < argc){
                    points = stoi(argv[i+1]);
                }
                continue;

            }

            if(i == argc-1){
                output_file = argv[i];
            }

        }
    }else{
        display_help();
        return 0;
    }

    
    cout << "Generating...\n";
    CellurarGenerator cellurarGen({width, height});
    double* values = cellurarGen.generate(points);
    
    sf::Uint8* cellurarTex = new sf::Uint8[width*height*4];
    
    sf::Texture texture;
    texture.create(width, height);

  

    double intensity = 5.;

    for(int i = 0; i < CELL_L; i += 4){
        sf::Uint8 val = static_cast<sf::Uint8>(values[i/4]*255);
        cellurarTex[i] = val;
        cellurarTex[i+1] = val;
        cellurarTex[i+2] = val;
        cellurarTex[i+3] = 255;
    } 

    texture.update(cellurarTex);
    texture.copyToImage().saveToFile(output_file);
    cout << "Done!\n";



   
    if(view){
        sf::RenderWindow window(sf::VideoMode(width, height), "Cellurar Texture Generator");
        sf::Sprite sprite{texture};

        while(window.isOpen()){
            sf::Event event;
            while(window.pollEvent(event)){
                if(event.type == sf::Event::EventType::Closed){
                    window.close();
                }
            }

            window.clear();
            window.draw(sprite);
            window.display();
        }
    }




    delete [] cellurarTex;


    return 0;
}


void display_help(){
    cout << R"(Usage: ctg [options] output
Options:
	-w <int>	Width of texture
	-h <int>	Height of texture
	-p <int>	Number of points
	-v		View
	--help	Display this information)" << endl;
}