#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <ctime>
#include <string>
#include "snake.hpp"

int main( )
{
    auto window = std::make_unique<sf::RenderWindow>(
        sf::VideoMode(WIDTH * SIZE_BOX, HEIGHT *SIZE_BOX), "JR Snake game"
    );

    auto snake = new Snake();

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed :
                    window->close();
                    break;
                
                case sf::Event::EventType::KeyReleased :
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Up :
                            snake->setDirection(Direction::UP);
                            break;
                        
                        case sf::Keyboard::Down :
                            snake->setDirection(Direction::DOWN);
                            break;
                        
                        case sf::Keyboard::Left :
                            snake->setDirection(Direction::LEFT);
                            break;
                        
                        case sf::Keyboard::Right :
                            snake->setDirection(Direction::RIGHT);
                            break;

                        case sf::Keyboard::Space :
                            snake->growUp();
                            break;
                    }
                    break;
                default: break;
            }
        }

        snake->move();
        
        if (snake->isDead()){
            window->close();
        }

        window->clear({52, 52, 52});
        snake->draw(*window);
        window->display();

        _sleep(200);
    }

    delete snake;
    return EXIT_SUCCESS;
}