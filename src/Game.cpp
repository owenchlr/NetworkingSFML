
#include "Game.h"
#include "Tile.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  
}

Game::~Game()
{
    
}

bool Game::init()
{
    board = std::make_shared<Board>(window);
    board->init();   

    font1 = std::make_unique<sf::Font>();
    if (!font1->openFromFile("../Data/Fonts/OpenSans-Bold.ttf"))
    {
        std::cout << "Font not loaded\n";
    }

    host_text = std::make_unique<sf::Text>(*font1);
    join_text = std::make_unique<sf::Text>(*font1);


    host_text->setFont(*font1);
    host_text->setString("Host Game");
    host_text->setPosition({ 900, 100 });
    host_text->setCharacterSize(60);

    join_text->setFont(*font1);
    join_text->setString("Join Game");
    join_text->setPosition({ 900, 300 });
    join_text->setCharacterSize(60);

    return true;
}

void Game::update(float dt)
{

}

void Game::render()
{
    board->render();    
    window.draw(*host_text);
    window.draw(*join_text);
}

void Game::mouseButtonPressed(const sf::Event::MouseButtonPressed* event)
{
    board->mouseButtonPressed(event);
}

void Game::mouseButtonReleased(const sf::Event::MouseButtonReleased* event)
{
    board->mouseButtonReleased(event);    
}

void Game::keyPressed(const sf::Event::KeyPressed* event)
{

}

void Game::keyReleased(const sf::Event::KeyReleased* event)
{

}

void Game::mouseMoved(const sf::Event::MouseMoved* event)
{
    board->mouseMoved(event);
}




