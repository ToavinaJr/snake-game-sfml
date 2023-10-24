#pragma once

#include <memory>
#include <list>
#include <map>
#include <SFML/Graphics.hpp>

constexpr int SIZE_BOX = 24;
constexpr int WIDTH = 40;
constexpr int HEIGHT = 20;

enum class Direction {
    NONE, UP, DOWN, LEFT, RIGHT
};

class Snake{
    enum GameStates { PLAYING, PAUSED, GAME_OVER};
    public :
        Snake();
        ~Snake();
        void draw(sf::RenderWindow& )const;
        void move();
        void setDirection(const Direction& );
        bool isDead() const;
        void growUp();
        std::pair<int,int> generatePosition()const;

    private :
        std::list< std::pair<int, int> > m_positions;
        std::pair<int, int> m_foodPositions;
        Direction m_direction;
        bool m_isDead;
        int score;
};