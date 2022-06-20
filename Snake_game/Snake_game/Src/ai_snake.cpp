#include "stdafx.h"
#include "../headers/ai_snake.h"

int ai_snake::compute_dir(sf::Vector2f food, sf::RenderWindow* target, std::list<sf::RectangleShape>& other_snake)
{
	float temp_min_distance = std::numeric_limits<float>::infinity();
	int planned_direction = current_direction;
	for (int test_dir : {LEFT, RIGHT, UP, DOWN}) {
		if (test_dir + current_direction != 0) {
			sf::Vector2f temp_vec = get_move_vector(test_dir);
			if (self_collide(target, head_centre + temp_vec) || is_collide(other_snake, head_centre + temp_vec)) { }
			else {
				float temp_dist=sqrtf(powf(fabs((food.x+(base_size*0.5f)) - (head_centre.x + temp_vec.x)), 2) + powf(fabs((food.y + (base_size*0.5f)) - (head_centre.y + temp_vec.y)), 2));
				if (temp_dist <= temp_min_distance) {
					temp_min_distance = temp_dist;
					planned_direction = test_dir;
				}
			}
		}
	}
	return planned_direction;

	
}


ai_snake::ai_snake(sf::Vector2u init_pos, int dir,asset_holder* assets) : snake()
{
	m_assets = assets;
	body=std::list<sf::RectangleShape>(4);
	texture_snake = &m_assets->get_texture(2);
	alive = true;
	current_direction = dir;
	previous_direction = dir;
	for (int x = 0; x < 4; x++) {
		display_frames[x] = sf::IntRect(16 * x, 0, 16, 16);
	}
	init_rect.setSize({ base_size, base_size });
	init_rect.setOrigin(base_size*0.5f, base_size*0.5f);
	current_movement = get_move_vector(current_direction);
	sf::Vector2f temp = sf::Vector2f((init_pos.x + 0.5f)*base_size, (init_pos.y + 0.5f)*base_size);
	for (auto it = body.begin(); it != body.end(); it++) {
		*it = init_rect;
		it->setPosition(temp);
		if (it == body.begin()) {
			texture_setter(*it, HEAD);
		}
		else if (it == --body.end()) {
			auto temp = --it;
			it++;
			texture_setter_tail((*it), (*temp));

		}
		else { texture_setter(*it, BODY); }
		temp = temp - current_movement;

	}
	head = &body.front();
	head_centre = head->getPosition();
	tail = &body.back();
}

ai_snake::~ai_snake()
{
}

void ai_snake::update_move(bool _grow,sf::RenderWindow * target, sf::Vector2f food, std::list<sf::RectangleShape>& other_snake)
{
	if (alive) {
		move(compute_dir(food, target, other_snake), _grow);
	}
}
void ai_snake::update_check( sf::RenderWindow* target, std::list<sf::RectangleShape>& other_snake) {
	if (alive) {
		alive = !(self_collide(target, head_centre) || is_collide(other_snake, get_head_centre()));
	}
}

