#ifndef AI_SNAKE_H
#define AI_SNAKE_H

#include "snake.h"
class ai_snake : public snake
{
private: 
	int compute_dir(sf::Vector2f food, sf::RenderWindow* target, std::list<sf::RectangleShape>& other_snake);
	int planned_direction;

public:
	ai_snake(sf::Vector2u init_pos, int dir,asset_holder* assets);
	~ai_snake();
	void update_move(bool _grow, sf::RenderWindow * target,sf::Vector2f food, std::list<sf::RectangleShape>& other_snake);
	void update_check( sf::RenderWindow* target, std::list<sf::RectangleShape>& other_snake);
};


#endif