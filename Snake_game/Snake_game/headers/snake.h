#ifndef SNAKE_H
#define SNAKE_H

#include "asset_holder.h"
class snake
{
protected :
	enum texture_type {HEAD,BODY,TAIL};
	const float base_size =16.f;
	std::list<sf::RectangleShape> body;
	sf::RectangleShape* head;
	sf::RectangleShape* tail;
	sf::RectangleShape init_rect;
	sf::Vector2f current_movement;
	sf::Vector2f head_centre;
	int current_direction;
	int previous_direction;
	bool alive;
	asset_holder* m_assets;
	sf::IntRect display_frames[4];
	sf::Texture* texture_snake;
	void texture_setter(sf::RectangleShape& target, int type_texture);
	void texture_setter_tail(sf::RectangleShape& target,sf::RectangleShape& next_to_target);
public:
	enum move_direction {UP = -1,DOWN = 1,LEFT =-2 ,RIGHT= 2};
	sf::Vector2f get_move_vector(int move_dir);
	snake(sf::Vector2u init_pos ,int dir,asset_holder* assets);
	snake();
	~snake();
	sf::Vector2f& get_head_centre();
	void move(int _dir,bool _grow);
	virtual void update(int _dir,bool _grow, sf::RenderWindow * target);
	void draw(sf::RenderWindow* target);
	bool self_collide(sf::RenderWindow* target,sf::Vector2f checkpoint);
	bool is_collide(std::list<sf::RectangleShape>& snake_body, sf::Vector2f checkpoint);
	bool is_alive();
	void set_alive(bool status);
	std::list<sf::RectangleShape>& getbody();
};

#endif