//Group Members:
//1. Emaan Shakeel   (22i-1279)  Section : A
//2. Ammara Masood   (21i-0639)  Section : D
//-----------------------------------------------
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

Player::Player(float x, float y) {
    speed = 3.5;
    lives = 3;  // Initialize lives
    score = 0;
    if (texture.loadFromFile("C:\\Users\\LENOVO\\Pictures\\orangecar.jpg")) {
        car_p.setTexture(texture);
        car_p.setScale(CELL_SIZE / texture.getSize().x, CELL_SIZE / texture.getSize().y);
        car_p.setPosition(x, y);
    }
    else {
        // Handle texture loading failure
        cout << "Failed to load player texture!" << endl;
    }
}

Player::Player(int Highest_score) : score(Highest_score) {}

void Player::move(sf::Vector2f direction) {
    car_p.move(direction * speed);
}

void Player::decreaseLives() {
    lives--;
}

int Player::getLives() const {
    return lives;
}

void Player::increaseScore(int points) {
    score += points;
}

int Player::getScore() const {
    return score;
}



Opponent::Opponent(float x, float y) {
    speed = 5;

    if (texture.loadFromFile("C:\\Users\\LENOVO\\Pictures\\bluecar.jpeg")) {
        car_o.setTexture(texture);
        car_o.setScale(CELL_SIZE / texture.getSize().x, CELL_SIZE / texture.getSize().y);
        car_o.setPosition(x - 100, y + 100);
    }
    else {
        // Handle texture loading failure
        cout << "Failed to load opponent texture!" << endl;
    }
}

void Opponent::move(sf::Vector2f direction) {
    car_o.move(direction * speed);
}

void Opponent::decideMovement(const sf::Vector2f& playerPosition, sf::RenderWindow& window, int maze[][MAP_HEIGHT]) {
    // Calculate the next position for the opponent
    sf::Vector2f nextOpponentPosition = car_o.getPosition() + sf::Vector2f(0, 0);

    // Calculate the corners of the opponent's rectangle
    float leftOpponent = nextOpponentPosition.x;
    float rightOpponent = nextOpponentPosition.x + CELL_SIZE;
    float topOpponent = nextOpponentPosition.y;
    float bottomOpponent = nextOpponentPosition.y + CELL_SIZE;

    // Perform boundary checks for the opponent
    if (leftOpponent >= 0 && rightOpponent <= window.getSize().x && topOpponent >= 0 &&
        bottomOpponent <= window.getSize().y) {

        // Check for collision with walls for the opponent
        int leftCellOpponent = static_cast<int>(leftOpponent / CELL_SIZE);
        int rightCellOpponent = static_cast<int>(rightOpponent / CELL_SIZE);
        int topCellOpponent = static_cast<int>(topOpponent / CELL_SIZE);
        int bottomCellOpponent = static_cast<int>(bottomOpponent / CELL_SIZE);

        // Check all four corners for collisions for the opponent
        if (maze[leftCellOpponent][topCellOpponent] != 1 || // Top left corner
            maze[rightCellOpponent][topCellOpponent] != 1 || // Top right corner
            maze[leftCellOpponent][bottomCellOpponent] != 1 || // Bottom left corner
            maze[rightCellOpponent][bottomCellOpponent] != 1)

            // Bottom right corner
        {
            // If any corner collides with a wall for the opponent, do not move

            return move(sf::Vector2f(0, -1));



        }
    }

    // Randomly decide to move horizontally or vertically
    if (rand() % 2 == 0) {
        moveHorizontally(playerPosition);
    }
    else {
        moveVertically(playerPosition);
    }
}

void Opponent::handleCollision(Player& player) {
    // Check for collision with player
    if (car_o.getGlobalBounds().intersects(player.car_p.getGlobalBounds())) {
        // Handle collision actions, e.g., decrease lives
        player.decreaseLives();
        if (player.getLives() == 0) {
            // Implement game over logic (e.g., display game over screen)
            cout << "Game Over!" << endl;

            
        }
        else {
            // Reset player position or perform other actions as needed
            player.car_p.setPosition(MAP_WIDTH / 2.0f * CELL_SIZE, CELL_SIZE);
        }
    }
}

void Opponent::moveHorizontally(const sf::Vector2f& playerPosition) {
    float deltaX = playerPosition.x - car_o.getPosition().x;
    if (deltaX > 0) {
        // Move right
        move(sf::Vector2f(1, 0));
    }
    else if (deltaX < 0) {
        // Move left
        move(sf::Vector2f(-1, 0));
    }
}

void Opponent::moveVertically(const sf::Vector2f& playerPosition) {
    float deltaY = playerPosition.y - car_o.getPosition().y;
    if (deltaY > 0) {
        // Move down
        move(sf::Vector2f(0, 1));
    }
    else if (deltaY < 0) {
        // Move up
        move(sf::Vector2f(0, -1));
    }
}


Game::Game()
    : window(sf::VideoMode(MAP_WIDTH* CELL_SIZE, MAP_HEIGHT* CELL_SIZE), "SFML Maze"),
    player(MAP_WIDTH / 2.0f * CELL_SIZE, CELL_SIZE),
    opponent(MAP_WIDTH / 2.0f * CELL_SIZE, CELL_SIZE) {

    // Set all cells to walls
    for (int i = 0; i < MAP_WIDTH; ++i) {
        for (int j = 0; j < MAP_HEIGHT; ++j) {
            maze[i][j] = 1; // Assuming 1 represents a wall, and 0 represents an empty cell
        }
    }

    // Make some cells empty to create a maze structure
    maze[2][5] = 0;
    maze[2][6] = 0;
    maze[2][7] = 0;
    maze[2][8] = 0;
    maze[2][9] = 0;
    maze[2][10] = 0;
    maze[2][11] = 0;
    maze[2][12] = 0;


    maze[25][5] = 0;
    maze[25][6] = 0;
    maze[25][7] = 0;
    maze[25][8] = 0;
    maze[25][9] = 0;
    maze[25][10] = 0;
    maze[25][11] = 0;
    maze[25][12] = 0;

    //neche wali line
    maze[2][15] = 0;
    maze[2][16] = 0;
    maze[2][17] = 0;
    maze[2][18] = 0;
    maze[2][19] = 0;
    maze[2][20] = 0;
    maze[2][21] = 0;
    maze[2][22] = 0;

    maze[25][15] = 0;
    maze[25][16] = 0;
    maze[25][17] = 0;
    maze[25][18] = 0;
    maze[25][19] = 0;
    maze[25][20] = 0;
    maze[25][21] = 0;
    maze[25][22] = 0;

    //uper - line
    maze[3][5] = 0;
    maze[4][5] = 0;
    maze[5][5] = 0;
    maze[6][5] = 0;
    maze[7][5] = 0;
    maze[8][5] = 0;
    maze[9][5] = 0;
    maze[10][5] = 0;
    maze[11][5] = 0;


    maze[17][5] = 0;
    maze[18][5] = 0;
    maze[19][5] = 0;
    maze[20][5] = 0;
    maze[21][5] = 0;
    maze[22][5] = 0;
    maze[23][5] = 0;
    maze[24][5] = 0;
    maze[25][5] = 0;

    //neeche - line
    maze[3][22] = 0;
    maze[4][22] = 0;
    maze[5][22] = 0;
    maze[6][22] = 0;
    maze[7][22] = 0;
    maze[8][22] = 0;
    maze[9][22] = 0;
    maze[10][22] = 0;
    maze[11][22] = 0;

    maze[17][22] = 0;
    maze[18][22] = 0;
    maze[19][22] = 0;
    maze[20][22] = 0;
    maze[21][22] = 0;
    maze[22][22] = 0;
    maze[23][22] = 0;
    maze[24][22] = 0;
    maze[25][22] = 0;



    //upar


    maze[5][8] = 0;
    maze[5][9] = 0;
    maze[5][10] = 0;
    maze[5][11] = 0;
    maze[5][12] = 0;



    maze[22][8] = 0;
    maze[22][9] = 0;
    maze[22][10] = 0;
    maze[22][11] = 0;
    maze[22][12] = 0;



    maze[5][15] = 0;
    maze[5][16] = 0;
    maze[5][17] = 0;
    maze[5][18] = 0;
    maze[5][19] = 0;


    maze[22][15] = 0;
    maze[22][16] = 0;
    maze[22][17] = 0;
    maze[22][18] = 0;
    maze[22][19] = 0;




    //uper - line


    maze[5][8] = 0;
    maze[6][8] = 0;
    maze[7][8] = 0;
    maze[8][8] = 0;
    maze[9][8] = 0;
    maze[10][8] = 0;


    //  maze[17][8] = 0;
    maze[18][8] = 0;
    maze[19][8] = 0;
    maze[20][8] = 0;
    maze[21][8] = 0;
    maze[22][8] = 0;




    maze[5][19] = 0;
    maze[6][19] = 0;
    maze[7][19] = 0;
    maze[8][19] = 0;
    maze[9][19] = 0;
    maze[10][19] = 0;


    maze[18][19] = 0;
    maze[19][19] = 0;
    maze[20][19] = 0;
    maze[21][19] = 0;
    maze[22][19] = 0;








    maze[8][11] = 0;
    maze[8][12] = 0;
    maze[9][11] = 0;




    maze[19][11] = 0;
    maze[19][12] = 0;
    maze[18][11] = 0;


    maze[8][15] = 0;
    maze[8][16] = 0;
    maze[9][16] = 0;



    maze[19][15] = 0;
    maze[19][16] = 0;
    maze[18][16] = 0;

    maze[13][14] = 0;
    maze[14][14] = 0;
    maze[13][13] = 0;
    maze[14][13] = 0;
    // ... (add more maze configuration as needed)
    // Initialize food positions
    foodPositionsX[0] = 5; foodPositionsY[0] = 7;
    foodPositionsX[1] = 9; foodPositionsY[1] = 7;
    foodPositionsX[2] = 4; foodPositionsY[2] = 9;
    foodPositionsX[3] = 4; foodPositionsY[3] = 12;
    foodPositionsX[4] = 4; foodPositionsY[4] = 16;
    foodPositionsX[5] = 4; foodPositionsY[5] = 19;
    foodPositionsX[6] = 5; foodPositionsY[6] = 21;
    foodPositionsX[7] = 9; foodPositionsY[7] = 21;
    foodPositionsX[8] = 19; foodPositionsY[8] = 21;
    foodPositionsX[9] = 22; foodPositionsY[9] = 21;

    foodPositionsX[10] = 24; foodPositionsY[10] = 19;
    foodPositionsX[11] = 24; foodPositionsY[11] = 16;
    foodPositionsX[12] = 24; foodPositionsY[12] = 12;
    foodPositionsX[13] = 24; foodPositionsY[13] = 9;
    foodPositionsX[14] = 22; foodPositionsY[14] = 7;
    foodPositionsX[15] = 19; foodPositionsY[15] = 7;
    foodPositionsX[16] = 10; foodPositionsY[16] = 10;
    foodPositionsX[17] = 7; foodPositionsY[17] = 10;
    foodPositionsX[18] = 7; foodPositionsY[18] = 12;
    foodPositionsX[19] = 7; foodPositionsY[19] = 16;

    foodPositionsX[20] = 7; foodPositionsY[20] = 18;
    foodPositionsX[21] = 9; foodPositionsY[21] = 18;
    foodPositionsX[22] = 19; foodPositionsY[22] = 18;
    foodPositionsX[23] = 21; foodPositionsY[23] = 18;
    foodPositionsX[24] = 21; foodPositionsY[24] = 16;
    foodPositionsX[25] = 21; foodPositionsY[25] = 12;
    foodPositionsX[26] = 21; foodPositionsY[26] = 10;
    foodPositionsX[27] = 18; foodPositionsY[27] = 10;
    foodPositionsX[28] = 9; foodPositionsY[28] = 12;
    foodPositionsX[29] = 18; foodPositionsY[29] = 15;
    foodPositionsX[30] = 10; foodPositionsY[30] = 15;
    foodPositionsX[31] = 18; foodPositionsY[31] = 12;

}

void Game::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
        if (player.getLives() == 0) {


            // Close the SFML window
            window.close();
        }
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.key.code == sf::Keyboard::Num4) {
            window.close();
        }
        if (event.key.code == sf::Keyboard::Num5) {
            Menu menu(window);
            menu.cont();
        }
    }
}

void Game::update() {
    sf::Vector2f playerDirection = getPlayerDirection();

    // Calculate the next position for the player
    sf::Vector2f nextPlayerPosition = player.car_p.getPosition() + playerDirection * player.speed;

    // Calculate the corners of the player's rectangle
    float leftPlayer = nextPlayerPosition.x;
    float rightPlayer = nextPlayerPosition.x + CELL_SIZE;
    float topPlayer = nextPlayerPosition.y;
    float bottomPlayer = nextPlayerPosition.y + CELL_SIZE;

    // Perform boundary checks for the player
    if (leftPlayer >= 0 && rightPlayer <= window.getSize().x && topPlayer >= 0 &&
        bottomPlayer <= window.getSize().y) {

        // Check for collision with walls for the player
        int leftCellPlayer = static_cast<int>(leftPlayer / CELL_SIZE);
        int rightCellPlayer = static_cast<int>(rightPlayer / CELL_SIZE);
        int topCellPlayer = static_cast<int>(topPlayer / CELL_SIZE);
        int bottomCellPlayer = static_cast<int>(bottomPlayer / CELL_SIZE);

        // Check all four corners for collisions for the player
        if (maze[leftCellPlayer][topCellPlayer] != 1 || // Top left corner
            maze[rightCellPlayer][topCellPlayer] != 1 || // Top right corner
            maze[leftCellPlayer][bottomCellPlayer] != 1 || // Bottom left corner
            maze[rightCellPlayer][bottomCellPlayer] != 1)  // Bottom right corner
        {
            // If any corner collides with a wall for the player, do not move
            return;
        }
        for (int i = 0; i <= 31; ++i) {
            if (leftCellPlayer == foodPositionsX[i] && topCellPlayer == foodPositionsY[i] ||
                rightCellPlayer == foodPositionsX[i] && bottomCellPlayer == foodPositionsY[i]) {
                player.increaseScore(10);
                foodPositionsX[i] = -1;
                foodPositionsY[i] = -1;
                break;
            }
        }
        // If no collision, move the player
        player.move(playerDirection);

        // Check for collision with opponent
        opponent.handleCollision(player);
    }

    opponent.decideMovement(player.car_p.getPosition(), window, maze);
}

void Game::render() {
    window.clear(sf::Color::Red); // Set background to red

    // Draw the maze and player
    drawPlayerAndOpponent();
    sf::Font font;
    if (font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        sf::Text livesText("Lives: " + to_string(player.getLives()), font, 17);
        livesText.setPosition(10, 10); // Adjust the position as needed
        livesText.setFillColor(sf::Color::White);
        window.draw(livesText);

        sf::Text ScoreText("Score: " + to_string(player.getScore()), font, 17);
        ScoreText.setPosition(80, 10); // Adjust the position as needed
        ScoreText.setFillColor(sf::Color::White);
        window.draw(ScoreText);
    }
    window.display();
}

void Game::drawPlayerAndOpponent() {
    // Draw the maze walls first
    for (int a = 0; a < MAP_WIDTH; ++a) {
        for (int b = 0; b < MAP_HEIGHT; ++b) {
            if (maze[a][b] == 1) {
                sf::RectangleShape wallShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                wallShape.setPosition(static_cast<float>(CELL_SIZE * a), static_cast<float>(CELL_SIZE * b));
                wallShape.setFillColor(sf::Color::Black);
                window.draw(wallShape);
            }
        }
    }
    window.draw(player.car_p);

    window.draw(opponent.car_o);

    for (int i = 0; i <= 31; ++i) {
        if (foodPositionsX[i] != -1 && foodPositionsY[i] != -1) {
            if ((i == 0)) {
                sf::RectangleShape foodShape(sf::Vector2f(8, 8));
                foodShape.setPosition(static_cast<float>(CELL_SIZE * 5), static_cast<float>(CELL_SIZE * 7));
                foodShape.setFillColor(sf::Color::Red);
                window.draw(foodShape);
            }


            if (i == 1) {
                sf::CircleShape foodShape(4.0f);  // Adjust the radius as needed
                foodShape.setPosition(static_cast<float>(CELL_SIZE * 9), static_cast<float>(CELL_SIZE * 7));
                foodShape.setFillColor(sf::Color::Green);
                window.draw(foodShape);
            }

            if ((i == 2)) {
                sf::RectangleShape foodShape(sf::Vector2f(8, 8));
                foodShape.setPosition(static_cast<float>(CELL_SIZE * 4), static_cast<float>(CELL_SIZE * 9));
                foodShape.setFillColor(sf::Color::Red);
                window.draw(foodShape);
            }
            if ((i == 3)) {
                sf::ConvexShape hexagon;
                hexagon.setPointCount(6);

                float radius = 7.0f;  // Adjust the radius as needed
                for (int i = 0; i < 6; ++i) {
                    float angle = i * 2 * 3.14159265359 / 6;
                    float x = CELL_SIZE * 4 + radius * cos(angle);
                    float y = CELL_SIZE * 12 + radius * sin(angle);
                    hexagon.setPoint(i, sf::Vector2f(x, y));
                }

                hexagon.setFillColor(sf::Color(255, 165, 0));  // Orange color
                window.draw(hexagon);
            }



            if ((i == 4)) {
                sf::RectangleShape foodShape(sf::Vector2f(8, 8));
                foodShape.setPosition(static_cast<float>(CELL_SIZE * 4), static_cast<float>(CELL_SIZE * 16));
                foodShape.setFillColor(sf::Color::Red);
                window.draw(foodShape);
            }

            if ((i == 5)) {
                float triangleSize = 0.4f;  // Adjust the size as needed

                sf::Vector2f p1(CELL_SIZE * 4, CELL_SIZE * 19);
                sf::Vector2f p2(CELL_SIZE * (4 + triangleSize), CELL_SIZE * 19);
                sf::Vector2f p3(CELL_SIZE * (4 + triangleSize / 2.0f), CELL_SIZE * (19 + triangleSize));

                sf::ConvexShape foodShape(3);
                foodShape.setPoint(0, p1);
                foodShape.setPoint(1, p2);
                foodShape.setPoint(2, p3);

                foodShape.setFillColor(sf::Color::White);
                window.draw(foodShape);
            }
            if ((i == 6)) {
                sf::CircleShape foodShape(4.0f);
                foodShape.setPosition(static_cast<float>(CELL_SIZE * 5), static_cast<float>(CELL_SIZE * 21));
                foodShape.setFillColor(sf::Color::Green);
                window.draw(foodShape);
            }

            if ((i == 7)) {
                sf::RectangleShape foodShape(sf::Vector2f(8, 8));
                foodShape.setPosition(static_cast<float>(CELL_SIZE * 9), static_cast<float>(CELL_SIZE * 21));
                foodShape.setFillColor(sf::Color::Red);
                window.draw(foodShape);
            }

            if ((i == 8)) {
                sf::RectangleShape foodShape(sf::Vector2f(8, 8));
                foodShape.setPosition(static_cast<float>(CELL_SIZE * 19), static_cast<float>(CELL_SIZE * 21));
                foodShape.setFillColor(sf::Color::Red);
                window.draw(foodShape);
            }

            if ((i == 9)) {
                float triangleSize = 0.4f;  // Adjust the size as needed

                sf::Vector2f p1(CELL_SIZE * 22, CELL_SIZE * 21);
                sf::Vector2f p2(CELL_SIZE * (22 + triangleSize), CELL_SIZE * 21);
                sf::Vector2f p3(CELL_SIZE * (22 + triangleSize / 2.0f), CELL_SIZE * (21 + triangleSize));

                sf::ConvexShape foodShape(3);
                foodShape.setPoint(0, p1);
                foodShape.setPoint(1, p2);
                foodShape.setPoint(2, p3);

                foodShape.setFillColor(sf::Color::White);
                window.draw(foodShape);
            }

            if ((i == 10)) {
                sf::CircleShape foodShape(4.0f);
                foodShape.setPosition(static_cast<float>(CELL_SIZE * 24), static_cast<float>(CELL_SIZE * 19));
                foodShape.setFillColor(sf::Color::Green);
                window.draw(foodShape);
            }

            if ((i == 11)) {
                sf::RectangleShape foodShape(sf::Vector2f(8, 8));
                foodShape.setPosition(static_cast<float>(CELL_SIZE * 24), static_cast<float>(CELL_SIZE * 16));
                foodShape.setFillColor(sf::Color::Red);
                window.draw(foodShape);
            }


            if ((i == 12)) {
                sf::CircleShape foodShape(4.0f);
                foodShape.setPosition(static_cast<float>(CELL_SIZE * 24), static_cast<float>(CELL_SIZE * 12));
                foodShape.setFillColor(sf::Color::Green);
                window.draw(foodShape);
            }

            if ((i == 13)) {
                float triangleSize = 0.4f;  // Adjust the size as needed

                sf::Vector2f p1(CELL_SIZE * 24, CELL_SIZE * 9);
                sf::Vector2f p2(CELL_SIZE * (24 + triangleSize), CELL_SIZE * 9);
                sf::Vector2f p3(CELL_SIZE * (24 + triangleSize / 2.0f), CELL_SIZE * (9 + triangleSize));

                sf::ConvexShape foodShape(3);
                foodShape.setPoint(0, p1);
                foodShape.setPoint(1, p2);
                foodShape.setPoint(2, p3);

                foodShape.setFillColor(sf::Color::White);
                window.draw(foodShape);
            }

            if ((i == 14)) {
                sf::RectangleShape foodShape(sf::Vector2f(8, 8));
                foodShape.setPosition(static_cast<float>(CELL_SIZE * 22), static_cast<float>(CELL_SIZE * 7));
                foodShape.setFillColor(sf::Color::Red);
                window.draw(foodShape);
            }

            if ((i == 15)) {
                sf::CircleShape foodShape(4.0f);
                foodShape.setPosition(static_cast<float>(CELL_SIZE * 19), static_cast<float>(CELL_SIZE * 7));
                foodShape.setFillColor(sf::Color::Green);
                window.draw(foodShape);
            }

            if ((i == 16)) {
                sf::RectangleShape foodShape(sf::Vector2f(8, 8));
                foodShape.setPosition(static_cast<float>(CELL_SIZE * 10), static_cast<float>(CELL_SIZE * 10));
                foodShape.setFillColor(sf::Color::Red);
                window.draw(foodShape);
            }

            if ((i == 17)) {
                sf::RectangleShape foodShape(sf::Vector2f(8, 8));
                foodShape.setPosition(static_cast<float>(CELL_SIZE * 7), static_cast<float>(CELL_SIZE * 10));
                foodShape.setFillColor(sf::Color::Red);
                window.draw(foodShape);
            }

            if ((i == 18)) {
                sf::CircleShape foodShape(4.0f);
                foodShape.setPosition(static_cast<float>(CELL_SIZE * 7), static_cast<float>(CELL_SIZE * 12));
                foodShape.setFillColor(sf::Color::Green);
                window.draw(foodShape);
            }

            if ((i == 19)) {
                sf::ConvexShape hexagon;
                hexagon.setPointCount(6);

                float radius = 7.0f;  // Adjust the radius as needed
                for (int i = 0; i < 6; ++i) {
                    float angle = i * 2 * 3.14159265359 / 6;
                    float x = CELL_SIZE * 7 + radius * cos(angle);
                    float y = CELL_SIZE * 16 + radius * sin(angle);
                    hexagon.setPoint(i, sf::Vector2f(x, y));
                }

                hexagon.setFillColor(sf::Color(255, 165, 0));  // Orange color
                window.draw(hexagon);
            }


            if ((i == 20)) {
                sf::RectangleShape foodShape(sf::Vector2f(8, 8));
                foodShape.setPosition(static_cast<float>(CELL_SIZE * 7), static_cast<float>(CELL_SIZE * 18));
                foodShape.setFillColor(sf::Color::Red);
                window.draw(foodShape);
            }


            if ((i == 21)) {
                sf::RectangleShape foodShape(sf::Vector2f(8, 8));
                foodShape.setPosition(static_cast<float>(CELL_SIZE * 9), static_cast<float>(CELL_SIZE * 18));
                foodShape.setFillColor(sf::Color::Red);
                window.draw(foodShape);
            }

            if ((i == 22)) {
                sf::ConvexShape hexagon;
                hexagon.setPointCount(6);

                float radius = 7.0f;  // Adjust the radius as needed
                for (int i = 0; i < 6; ++i) {
                    float angle = i * 2 * 3.14159265359 / 6;
                    float x = CELL_SIZE * 19 + radius * cos(angle);
                    float y = CELL_SIZE * 18 + radius * sin(angle);
                    hexagon.setPoint(i, sf::Vector2f(x, y));
                }

                hexagon.setFillColor(sf::Color(255, 165, 0));  // Orange color
                window.draw(hexagon);
            }

            if ((i == 23)) {
                sf::RectangleShape foodShape(sf::Vector2f(8, 8));
                foodShape.setPosition(static_cast<float>(CELL_SIZE * 21), static_cast<float>(CELL_SIZE * 18));
                foodShape.setFillColor(sf::Color::Red);
                window.draw(foodShape);
            }
            if ((i == 24)) {
                sf::RectangleShape foodShape(sf::Vector2f(8, 8));
                foodShape.setPosition(static_cast<float>(CELL_SIZE * 21), static_cast<float>(CELL_SIZE * 16));
                foodShape.setFillColor(sf::Color::Red);
                window.draw(foodShape);
            }
            if ((i == 25)) {
                sf::RectangleShape foodShape(sf::Vector2f(8, 8));
                foodShape.setPosition(static_cast<float>(CELL_SIZE * 21), static_cast<float>(CELL_SIZE * 12));
                foodShape.setFillColor(sf::Color::Red);
                window.draw(foodShape);
            }

            if ((i == 26)) {
                sf::CircleShape foodShape(4.0f);
                foodShape.setPosition(static_cast<float>(CELL_SIZE * 21), static_cast<float>(CELL_SIZE * 10));
                foodShape.setFillColor(sf::Color::Green);
                window.draw(foodShape);
            }
            if ((i == 27)) {
                sf::RectangleShape foodShape(sf::Vector2f(8, 8));
                foodShape.setPosition(static_cast<float>(CELL_SIZE * 18), static_cast<float>(CELL_SIZE * 10));
                foodShape.setFillColor(sf::Color::Red);
                window.draw(foodShape);
            }

            if ((i == 28)) {
                sf::RectangleShape foodShape(sf::Vector2f(8, 8));
                foodShape.setPosition(static_cast<float>(CELL_SIZE * 9), static_cast<float>(CELL_SIZE * 12));
                foodShape.setFillColor(sf::Color::Red);
                window.draw(foodShape);
            }
            if ((i == 29)) {
                float triangleSize = 0.4f;  // Adjust the size as needed

                sf::Vector2f p1(CELL_SIZE * 18, CELL_SIZE * 15);
                sf::Vector2f p2(CELL_SIZE * (18 + triangleSize), CELL_SIZE * 15);
                sf::Vector2f p3(CELL_SIZE * (18 + triangleSize / 2.0f), CELL_SIZE * (15 + triangleSize));

                sf::ConvexShape foodShape(3);
                foodShape.setPoint(0, p1);
                foodShape.setPoint(1, p2);
                foodShape.setPoint(2, p3);

                foodShape.setFillColor(sf::Color::White);
                window.draw(foodShape);
            }
            if (i == 30) {
                sf::ConvexShape hexagon;
                hexagon.setPointCount(6);

                float radius = 7.0f;  // Adjust the radius as needed
                for (int i = 0; i < 6; ++i) {
                    float angle = i * 2 * 3.14159265359 / 6;
                    float x = CELL_SIZE * 10 + radius * cos(angle);
                    float y = CELL_SIZE * 15 + radius * sin(angle);
                    hexagon.setPoint(i, sf::Vector2f(x, y));
                }

                hexagon.setFillColor(sf::Color(255, 165, 0));  // Orange color
                window.draw(hexagon);
            }
            if ((i == 31)) {
                sf::CircleShape foodShape(4.0f);
                foodShape.setPosition(static_cast<float>(CELL_SIZE * 18), static_cast<float>(CELL_SIZE * 12));
                foodShape.setFillColor(sf::Color::Green);
                window.draw(foodShape);
            }

        }
    }

}

sf::Vector2f Game::getPlayerDirection() {
    sf::Vector2f direction(0.0f, 0.0f);

    // Move clockwise on the right side
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        direction.x = 1.0f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        direction.y = 1.0f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        direction.x = -1.0f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        direction.y = -1.0f;
    }

    return direction;
}


