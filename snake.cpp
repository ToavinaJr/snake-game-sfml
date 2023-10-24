#include <algorithm>
#include <iostream>
#include <random>
#include <map>
#include "./snake.hpp"

/************************************************************/

Snake::Snake(){
    srand(time(nullptr));

    this->m_isDead = false;
    this->m_direction = Direction::LEFT;
    this->m_foodPositions = this->generatePosition();
    for(int y=5; y<8; ++y)
        this->m_positions.push_back(std::make_pair(10,y));
    
    this->score = 0;
}

/************************************************************/

Snake::~Snake(){
    this->m_positions.clear();
}

/************************************************************/

void Snake::draw(sf::RenderWindow& wind)const {
    sf::RectangleShape rect;
    rect.setSize({SIZE_BOX-1, SIZE_BOX-1});

    for ( const auto position : this->m_positions ) {
        rect.setPosition(sf::Vector2f(position.first * SIZE_BOX, position.second * SIZE_BOX));
        if (position == this->m_positions.front())
            rect.setFillColor({0, 0, 00});
        else rect.setFillColor({255, 255, 255});
            wind.draw(rect);
    }

    sf::Font font;
    if (!font.loadFromFile("C:/Windows/fonts/arial.ttf")) {
        std::cerr << "Error when loading the font" << std::endl;
        exit(EXIT_FAILURE);
    }

    sf::Text text;
    
    text.setFont(font);
    text.setPosition(5, 5);
    text.setString("Your score :\n" + std::to_string(score));
    text.setFillColor(sf::Color::Green);
    wind.draw(text);

    // Afficher l aliment sous forme de led
    rect.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
    rect.setPosition(this->m_foodPositions.first * SIZE_BOX, this->m_foodPositions.second * SIZE_BOX);
    wind.draw(rect);
}

/************************************************************/

void Snake::move() {
    if (this->m_direction == Direction::NONE)
        return;

    auto nextPosition = std::make_pair<int, int>(-1, -1);
    switch (this->m_direction)
    {
        case Direction::UP :
            nextPosition.first = this->m_positions.front().first;
            nextPosition.second = this->m_positions.front().second-1;
            break;
        
        case Direction::DOWN :
            nextPosition.first = this->m_positions.front().first;
            nextPosition.second = this->m_positions.front().second+1;
            break;
        
        case Direction::LEFT :
            nextPosition.first = this->m_positions.front().first-1;
            nextPosition.second = this->m_positions.front().second;
            break;
        
        case Direction::RIGHT :
            nextPosition.first = this->m_positions.front().first+1;
            nextPosition.second = this->m_positions.front().second;
            break;

    }

    if (std::find(m_positions.begin(), m_positions.end(), nextPosition) != m_positions.end()) {
        this->m_isDead = true;
    }

    if(nextPosition == m_foodPositions) {
        this->m_foodPositions = generatePosition();
        this->growUp();
        this->score++;
    }

    this->m_positions.push_front(nextPosition);
    this->m_positions.pop_back();
}

/************************************************************/

void Snake::setDirection(const Direction& dir) {
    switch (dir)
    {
        case Direction::UP :
            if ( this->m_direction != Direction::DOWN)
                this->m_direction = Direction::UP;
            break;
        
        case Direction::DOWN :
            if ( this->m_direction != Direction::UP)
                this->m_direction = Direction::DOWN;
            break;
        
        case Direction::LEFT :
            if ( this->m_direction != Direction::RIGHT)
                this->m_direction = Direction::LEFT;
            break;
        
        case Direction::RIGHT :
            if ( this->m_direction != Direction::LEFT)
                this->m_direction = Direction::RIGHT;
            break;

        default: 
            this->m_direction = Direction::NONE;
            break;
    }
}

/************************************************************/

bool Snake::isDead()const { 
    return ( this->m_positions.front().first < 0 or this->m_positions.front().first >= WIDTH ) or 
            ( this->m_positions.front().second < 0 or this->m_positions.front().second >= HEIGHT ) or 
            this->m_isDead;
            // or (std::find(this->m_positions.begin(), this->m_positions.end(), this->m_positions.front()) != this->m_positions.end());
}

/************************************************************/

void Snake::growUp() {
    auto nextPosition = this->m_positions.front();
    this->m_positions.push_front(nextPosition);
}

/************************************************************/

std::pair<int,int> Snake::generatePosition()const{
    int x = rand() % WIDTH;
    int y = rand( ) % HEIGHT;
    auto foodPosition = std::make_pair(x,y);
    
    while (std::find(m_positions.begin(), m_positions.end(), foodPosition) != m_positions.end())
    {
        x = rand() % WIDTH;
        y = rand( ) % HEIGHT;
        foodPosition = std::make_pair(x,y);
    }

    return foodPosition;
    
}

/************************************************************/