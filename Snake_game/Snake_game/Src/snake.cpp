#include "stdafx.h"
#include "../headers/snake.h"

void snake::texture_setter(sf::RectangleShape& target, int type_texture)
{
	switch (type_texture) {
	case HEAD:
		target.setTextureRect(display_frames[0]);
		if (current_direction != RIGHT) {
			target.setRotation(90.f*current_direction);
		}
		else { target.setRotation(0.f); }
		target.setTexture(texture_snake);
		break;
	case BODY:
		if (current_direction == previous_direction) {
			target.setTextureRect(display_frames[1]);
			if (current_direction != RIGHT) {
				target.setRotation(90.f*current_direction);
			}
			else { target.setRotation(0.f); }
		}
		else {
			target.setTextureRect(display_frames[2]);
			
			switch (current_direction - previous_direction) {
			case -3:
				target.setRotation(90.f);
				break;
			case -1:
				target.setRotation(0.f);
				break;
			case 1:
				target.setRotation(180.f);
				break;
			case 3:
				target.setRotation(-90.f);
				break;
			default:
				("ERROR::SNAKE::TEXTURE_SETTER::curved part setting failed\n");
			}
		}
		target.setTexture(texture_snake);
		break;
	default:
		printf("ERROR::SNAKE::TEXTURE_SETTER::invalid input");
		break;
	}
}

void snake::texture_setter_tail(sf::RectangleShape& target, sf::RectangleShape& next_to_target)
{
	if (next_to_target.getPosition().x - target.getPosition().x > base_size*0.1f) {
		target.setTextureRect(display_frames[3]);
		target.setRotation(180.f);
		target.setTexture(texture_snake);
		return;
	}
	else if (next_to_target.getPosition().x - target.getPosition().x < -base_size * 0.1f) {
		target.setTextureRect(display_frames[3]);
		target.setRotation(0.f);
		target.setTexture(texture_snake);
		return;
	}
	if (next_to_target.getPosition().y - target.getPosition().y > base_size*0.1f) {
		target.setTextureRect(display_frames[3]);
		target.setRotation(-90.f);
		target.setTexture(texture_snake);
		return;
	}
	else if (next_to_target.getPosition().y - target.getPosition().y < -base_size * 0.1f) {
		target.setTextureRect(display_frames[3]);
		target.setRotation(90.f);
		target.setTexture(texture_snake);
		return;
	}
}

sf::Vector2f snake::get_move_vector(int move_dir)
{
	switch (move_dir) {
	case UP:
		return sf::Vector2f(0.f, -base_size);
		break;
	case DOWN:
		return sf::Vector2f(0.f, base_size);
		break;
	case LEFT:
		return sf::Vector2f(-base_size,0.f);
		break;
	case RIGHT:
		return sf::Vector2f(base_size, 0.f);
		break;
	default:
		printf("ERROR::SNAKE::GET_MOVE_VECTOR\n");
		return current_movement;
		break;
	}
}

snake::snake(sf::Vector2u init_pos,int dir,asset_holder* assets):body(std::list<sf::RectangleShape>(4))
{
	m_assets = assets;
	texture_snake = &m_assets->get_texture(1);
	alive = true;
	current_direction = dir;
	previous_direction = dir;
	for (int x = 0; x < 4; x ++) {
		display_frames[x] = sf::IntRect(16 * x, 0, 16, 16);
	}
	init_rect.setSize({ base_size, base_size });
	init_rect.setOrigin(base_size*0.5f, base_size*0.5f);
	current_movement = get_move_vector(current_direction);
	sf::Vector2f temp = sf::Vector2f((init_pos.x +0.5f)*base_size, (init_pos.y+0.5f)*base_size);
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

snake::snake() {
}

snake::~snake()
{
}

sf::Vector2f& snake::get_head_centre()
{
	return head_centre;

}


void snake::move(int _dir,bool _grow)
{
	if (_dir + current_direction != 0) {
		previous_direction = current_direction;
		current_direction = _dir;
	}
	if (current_direction != previous_direction) {
		m_assets->play_sound(asset_holder::GRASS_SOUND1 + (rand() % 4));
	
	}
	current_movement = get_move_vector(current_direction);
	auto temp = *tail;
	temp.setPosition(head->getPosition() + current_movement);
	texture_setter(temp,HEAD);
	texture_setter(*head, BODY);
	if (!_grow) {
		body.pop_back();
		tail = &body.back();
		texture_setter_tail(*tail,*(--(--body.end())));
		
	}
	body.emplace_front(temp);
	head = &body.front();
	head_centre = (head->getPosition());
}

void snake::update(int _dir,bool _grow, sf::RenderWindow * target)
{
	if (alive){
		move(_dir, _grow);
		alive=!self_collide(target,head_centre);
	}
}

void snake::draw(sf::RenderWindow * target)
{
	for (const auto piece : body) {
		target->draw(piece);
	}
	
}

bool snake::self_collide(sf::RenderWindow* target, sf::Vector2f checkpoint)
{
	if (alive) {
		for (auto it = ++body.begin(); it != body.end(); it++) {
			if (it->getGlobalBounds().contains(checkpoint)){
				return true;
			}
		}
		if ((checkpoint.x < base_size) || ((checkpoint).x > target->getSize().x -base_size)) {
			return true;
		}
		if ((checkpoint.y < base_size ) || (checkpoint.y > target->getSize().y -base_size)) {
			return true;
		}
		return false;
	}
	else {
		return true;
	}
}

bool snake::is_collide(std::list<sf::RectangleShape>& snake_body, sf::Vector2f checkpoint)
{
	for (auto piece : snake_body) {
		if (piece.getGlobalBounds().contains(checkpoint)) {
			return true;
		}
	}
	return false;
}

bool snake::is_alive()
{
	return alive;
}

void snake::set_alive(bool status)
{
	alive = status;
}

std::list<sf::RectangleShape>& snake::getbody()
{
	return body;
}
