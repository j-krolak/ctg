#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>

#include <CellularGenerator.h>

using namespace std;


void display_help();

int main(int argc, char** argv){

    int width=300, height=300, points=50; 
    string output_file = "cellularTex.png";
    bool view = false, invert = false;
    CellularGenerator::Type type = CellularGenerator::Type::Simple;
    double intensity = 1;
    
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


            if(!strcmp(argv[i], "-i")){
                if(i + 1 < argc){
                    intensity = stod(argv[i+1]);
                }
                continue;

            }

            if(!strcmp(argv[i], "-I")){
                invert = true;
                continue;

            }


            if(!strcmp(argv[i], "-t")){
                if(i + 1 < argc){
                    if(stoi(argv[i+1]) > 2){
                        display_help();
                        return 0;
                    }
                    type = static_cast<CellularGenerator::Type>(stoi(argv[i+1]));    
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

    const int image_size = width*height*4;

    cout << "Generating...\n";
    CellularGenerator cellularGen({width, height});
    double* values = cellularGen.generate(points, type, invert);
    
    sf::Uint8* cellularTex = new sf::Uint8[width*height*4];
    sf::Texture texture;
    texture.create(width, height);

    for(int i = 0; i < image_size; i += 4){
        sf::Uint8 val = static_cast<sf::Uint8>(values[i/4]*255*intensity)%256;
        cellularTex[i] = val;
        cellularTex[i+1] = val;
        cellularTex[i+2] = val;
        cellularTex[i+3] = 255;
    } 

    texture.update(cellularTex);
    texture.copyToImage().saveToFile(output_file);
    
    cout << "Done!\n";



   
    if(view){
        sf::RenderWindow window(sf::VideoMode(width, height), "cellular Texture Generator");
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




    delete [] cellularTex;


    return 0;
}


void display_help(){
    cout << R"(Usage: ctg [options] output
Options:
	-w <int>	Width of texture
	-h <int>	Height of texture
	-p <int>	Number of points
    	-i <double> 	Intensity
    	-I		Invert
    	-t <int>    	Type (0 - Simple, 1 - Tiled, 2 - Smooth) 
	-v		View
	--help	Display this information)" << endl;
}