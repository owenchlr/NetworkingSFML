
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
    if (game_state == MENU)
    {
        if (host_text->getGlobalBounds().contains(sf::Vector2f(event->position)))
        {
            game_state = GAME;
            std::cout << "Creating Sever\n";
            server = std::make_unique<Server>();
            server->init();
            server->run();
        }
        else if (join_text->getGlobalBounds().contains(sf::Vector2f(event->position)))
        {
            game_state = GAME;
            std::cout << "Attempting connection to server\n";
            client = std::make_unique<Client>();
            client->connect();
        }
    }

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




