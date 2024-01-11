//Group Members:
//1. Emaan Shakeel   (22i-1279)  Section : A
//2. Ammara Masood   (21i-0639)  Section : D
//-----------------------------------------------
#include "Menu.h"
#include <SFML/Graphics.hpp>
using namespace std;
Menu::Menu(sf::RenderWindow& window) : window(window), paused(false) {
    if (!font.loadFromFile("C:\\Users\\LENOVO\\Desktop\\new proj oop\\new proj oop\\img\\techno-hideo\\TechnoHideo.ttf")) {
        cout << "Error loading font file." << endl;
    }

    if (!backgroundTexture.loadFromFile("C:\\Users\\LENOVO\\Downloads\\bg.jpg")) {
        cout << "Error loading background image." << endl;
    }

    backgroundSprite.setTexture(backgroundTexture);
}

void Menu::display_menu() {
    while (window.isOpen()) {
        sf::Text title("Menu", font, 50);
        title.setFillColor(sf::Color::Red);
        title.setPosition((window.getSize().x - title.getGlobalBounds().width) / 2.f, 60.f);

        sf::Text startGame("1) Start game", font, 50);
        startGame.setFillColor(sf::Color::Red);
        startGame.setPosition((window.getSize().x - startGame.getGlobalBounds().width) / 2.f, title.getPosition().y + 60.f);

        sf::Text highScores("2) See high-scores", font, 50);
        highScores.setFillColor(sf::Color::Red);
        highScores.setPosition((window.getSize().x - highScores.getGlobalBounds().width) / 2.f, startGame.getPosition().y + 60.f);

        sf::Text help("3) Help", font, 50);
        help.setFillColor(sf::Color::Red);
        help.setPosition((window.getSize().x - help.getGlobalBounds().width) / 2.f, highScores.getPosition().y + 60.f);

        sf::Text exitGame("4) Exit", font, 50);
        exitGame.setFillColor(sf::Color::Red);
        exitGame.setPosition((window.getSize().x - exitGame.getGlobalBounds().width) / 2.f, help.getPosition().y + 60.f);

        if (paused) {
            sf::Text continueGame("5) Continue", font, 50);
            title.setFillColor(sf::Color::Red);
            continueGame.setPosition((window.getSize().x - continueGame.getGlobalBounds().width) / 2.f, exitGame.getPosition().y + 60.f);

            while (window.pollEvent(event)) {
                handle_event();
            }

            window.clear();
            window.draw(backgroundSprite);  // Draw the background
            window.draw(title);
            window.draw(startGame);
            window.draw(highScores);
            window.draw(help);
            window.draw(exitGame);
            window.draw(continueGame);
            window.display();
        }
        else {
            while (window.pollEvent(event)) {
                handle_event();
            }

            window.clear();
            window.draw(backgroundSprite);  // Draw the background
            window.draw(title);
            window.draw(startGame);
            window.draw(highScores);
            window.draw(help);
            window.draw(exitGame);
            window.display();
        }
    }
}

bool Menu::isPaused() const {
    return paused;
}

void Menu::pause_game() {
    paused = true;
    display_menu();
}

void Menu::resume_game() {
    paused = false;
}

void Menu::handle_event() {
    if (event.type == sf::Event::Closed) {
        window.close();
    }

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Num1) {
            // Start new game
            cout << "Starting game\n";
            window.close();

        }
        else if (event.key.code == sf::Keyboard::Num2) {
            // See high scores
            cout << "High Scores Menu (not implemented)\n";
        }
        else if (event.key.code == sf::Keyboard::Num3) {
            // Help
            display_help();
        }
        else if (event.key.code == sf::Keyboard::Num4) {
            // Exit
            window.close();
        }
        else if (event.key.code == sf::Keyboard::Num5 && paused) {
            // Continue game
            paused = false;
        }
    }
}

void Menu::display_help() {
    sf::Texture helpBackgroundTexture;
    if (!helpBackgroundTexture.loadFromFile("C:\\Users\\LENOVO\\Downloads\\bg.jpg")) {
        cout << "Error loading help background image." << endl;
        return;
    }

    sf::Sprite helpBackgroundSprite(helpBackgroundTexture);

    window.clear();

    // Draw the background image for help
    window.draw(helpBackgroundSprite);

    sf::Text helpText("Help:\n\nPress '1' to start a new game\n\nPress '2' to see high scores\n\nPress '3' for help\n\nPress '4' to exit", font, 30);
    helpText.setPosition((window.getSize().x - helpText.getGlobalBounds().width) / 2.f, 50.f);
    helpText.setFillColor(sf::Color::Red);
    window.draw(helpText);

    // Display additional help information if needed

    window.display();

    sf::Event helpEvent;
    while (window.waitEvent(helpEvent)) {
        if (helpEvent.type == sf::Event::KeyPressed) {
            break;
        }
    }
}

void Menu::cont() {
    sf::Texture helpBackgroundTexture;
    if (!helpBackgroundTexture.loadFromFile("C:\\Users\\LENOVO\\Downloads\\bg.jpg")) {
        cout << "Error loading help background image." << endl;
        return;
    }

    sf::Sprite helpBackgroundSprite(helpBackgroundTexture);

    window.clear();

    // Draw the background image for help
    window.draw(helpBackgroundSprite);

    sf::Text helpText("    Game Paused \n\n\n    Press enter to\n continue", font, 40);
    helpText.setPosition((window.getSize().x - helpText.getGlobalBounds().width) / 2.f, 30.f);
    helpText.setFillColor(sf::Color::Red);
    window.draw(helpText);


    window.display();

    sf::Event helpEvent;
    while (window.waitEvent(helpEvent)) {
        if (helpEvent.type == sf::Event::KeyPressed) {
            break;
        }


    }
}





   



