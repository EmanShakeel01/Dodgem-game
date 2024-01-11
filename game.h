
#pragma once
#ifndef game_H
#define game_H

#include <SFML/Graphics.hpp>
#include <iostream>
const int MAP_WIDTH = 28;
const int MAP_HEIGHT = 26;
const float CELL_SIZE = 20.0f;
class Player {
private:// Add lives variable
    int score;
public:
    sf::Texture texture; // Texture for the player
    sf::Sprite car_p;
    // Sprite for the player with texture
    float speed;
    int lives;
    Player(float x, float y);
    Player(int Highest_score);
    void move(sf::Vector2f direction);
    void decreaseLives();
    int getLives() const;
    void increaseScore(int points);
    int getScore() const;


    

  
};

class Opponent {
public:
    sf::Texture texture;
    sf::Sprite car_o;
    float speed;
    Opponent(float x, float y);
    void move(sf::Vector2f direction);
    void decideMovement(const sf::Vector2f& playerPosition, sf::RenderWindow& window, int maze[][MAP_HEIGHT]);
    void handleCollision(Player& player);


    void moveHorizontally(const sf::Vector2f& playerPosition);
    void moveVertically(const sf::Vector2f& playerPosition);

   
};


class Game {
private:
    sf::RenderWindow window;

    int maze[MAP_WIDTH][MAP_HEIGHT];
    Player player;
    Opponent opponent;
    const int FOOD = 31;
    int foodPositionsX[31];
    int foodPositionsY[31];

    void handleEvents();
    void update();
    void render();
    void decideMovement();
    void drawPlayerAndOpponent();
    sf::Vector2f getPlayerDirection();

public:
   
    Game();
    void run();



   
};

#endif
