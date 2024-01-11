
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
#include "menu.h"
#include "game.h"
using namespace std;
int main() {
    sf::Music music;

    // Load the music file
    if (!music.openFromFile("C:\\Users\\LENOVO\\Downloads\\audio.ogg")) {
       
        return -1;
    }

    // Play the music
    music.play();

    sf::RenderWindow window(sf::VideoMode(600, 450), "Menu Example");
    Menu menu(window);

    while (window.isOpen()) {
        menu.display_menu();

        // Check if the game is paused or not
        if (menu.isPaused()) {
          
            cout << "Game is paused\n";
        }
        else {
            //  run  game 
            Game game;
            game.run();
        }
    }

    Player HIGHEST_SCORE(0);

    ofstream outfile("Score.txt");

    if (outfile.is_open()) {

        outfile << HIGHEST_SCORE.getScore() << endl;
        outfile.close();
    }

    else {

        cout << "Error!!! Unable to open a file..." << endl;

    }
    return 0;
}
