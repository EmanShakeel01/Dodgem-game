
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "game.h"
class Menu {

private:
    sf::RenderWindow& window;
    sf::Event event;
    bool paused;
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    void handle_event();
    void display_help();

public:
    Menu(sf::RenderWindow& window);
    void display_menu();
    bool isPaused() const;
    void pause_game();
    void resume_game();
    void cont();

};
