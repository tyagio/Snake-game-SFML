#include "stdafx.h"
#include "../headers/gameplay.h"

void gameplay::initvariables()
{
	grass.setTexture(m_context->m_assets->get_texture(3));
	grass.setTextureRect(sf::IntRect(0, 0, m_context->m_window->getSize().x - 32, m_context->m_window->getSize().y - 32));
	grass.setPosition(16.f, 16.f);
	for (int i = 0; i < 4; i++) {
		walls[i].setTexture(m_context->m_assets->get_texture(4));
		if (i < 2) {
			walls[i].setTextureRect(sf::IntRect(0,0,m_context->m_window->getSize().x,16));
		}
		else {
			walls[i].setTextureRect(sf::IntRect(0, 0,16, m_context->m_window->getSize().y));
		}
	}
	walls[1].setPosition(0.f, m_context->m_window->getSize().y - 16.f);
	walls[3].setPosition(m_context->m_window->getSize().x - 16.f, 0.f);
	dir = snake::RIGHT;
	timer = 0.f;
	is_pause = false;
	grow_player = false;
	grow_solid_snake = false;
	alive_player = true;
	alive_solid_snake = true;
	apple.setTexture(m_context->m_assets->get_texture(0));
	apple.setScale(0.5f, 0.5f);
	srand(unsigned(time(0)));
	apple_generator(player_snake.getbody(), solid_snake.getbody());
}

void gameplay::inittext()
{
}

void gameplay::apple_generator(std::list<sf::RectangleShape>& snake1, std::list<sf::RectangleShape>& snake2)
{
	int x = (m_context->m_window->getSize().x - 32)/16;
	int y = (m_context->m_window->getSize().y - 32)/16;
	int max = x * y;
	std::vector<int> exclude_vec;
	for (const auto& it : snake1) {
		sf::Vector2f temp =it.getPosition() - sf::Vector2f(8.f,8.f);
		exclude_vec.emplace_back((roundf((temp.y-16.f)/16.f)*x)+roundf((temp.x-16.f)/16.f));
	}
	for (const auto& it : snake2) {
		sf::Vector2f temp = it.getPosition() - sf::Vector2f(8.f, 8.f);
		exclude_vec.emplace_back((roundf((temp.y - 16.f) / 16.f)*x) + roundf((temp.x - 16.f) / 16.f));
	}
	int temp_pos = rand() % max;
	bool temp_bool = true;
	while (temp_bool) {
		auto it = std::find(exclude_vec.begin(), exclude_vec.end(), temp_pos);
		if (it == exclude_vec.end()) {
			temp_bool = false;
		}
		else {
			(++temp_pos)% max ;
		}
	}
	apple.setPosition(((temp_pos%x) + 1)*16.f, (((temp_pos - (temp_pos%x)) / x) + 1)*16.f);

}

gameplay::gameplay(std::shared_ptr<context>& context):m_context(context),player_snake(sf::Vector2u(5U,5U), snake::move_direction::RIGHT,context->m_assets.get()), solid_snake(sf::Vector2u(32U,20U),snake::move_direction::LEFT, context->m_assets.get()) {

}

gameplay::~gameplay()
{
}

const bool gameplay::running() const
{
	return false;
}

void gameplay::init()
{
	initvariables();
}

void gameplay::pollevents()
{
	sf::Event event;
	while (m_context->m_window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			m_context->m_window->close();
		}
		if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code) {
			case sf::Keyboard::W:
				dir = snake::UP;
				break;
			case sf::Keyboard::S:
				dir = snake::DOWN;
				break;
			case sf::Keyboard::A:
				dir = snake::LEFT;
				break;
			case sf::Keyboard::D:
				dir = snake::RIGHT;
				break;
			default:
				break;

			}
		}
	}
}

void gameplay::update(float & _dt)
{
	timer += _dt;
	if ((timer > 0.125f) && (alive_player && alive_solid_snake)) {
		solid_snake.update_move(grow_solid_snake, m_context->m_window.get(), apple.getPosition(), player_snake.getbody());
		player_snake.update(dir, grow_player, m_context->m_window.get());
		alive_player = player_snake.is_alive();
		if (alive_player) {
			player_snake.set_alive(!player_snake.is_collide(solid_snake.getbody(), player_snake.get_head_centre()));
			alive_player = player_snake.is_alive();
		}
		solid_snake.update_check(m_context->m_window.get(), player_snake.getbody());
		alive_solid_snake = solid_snake.is_alive();
		timer = 0.f;
		grow_player = false;
		grow_solid_snake = false;
		if (apple.getGlobalBounds().contains(player_snake.get_head_centre())) {
			grow_player = true;
			m_context->m_assets->play_sound(asset_holder::SNAKE_GROW);
			apple_generator(player_snake.getbody(), solid_snake.getbody());
		}
		if (apple.getGlobalBounds().contains(solid_snake.get_head_centre())) {
			grow_solid_snake = true;
			m_context->m_assets->play_sound(asset_holder::CYBORG_GROW,30.f);
			apple_generator(player_snake.getbody(), solid_snake.getbody());
		}
		
	}
	else if(!(alive_player && alive_solid_snake)){
		if (timer > 0.2f) {
			if ((!alive_player) && (player_snake.getbody().size() != 0)) {
				player_snake.getbody().pop_front();
			}
			if ((!alive_solid_snake) && (solid_snake.getbody().size() != 0)) {
				solid_snake.getbody().pop_front();
			}
			timer = 0.f;
		}
		if (((solid_snake.getbody().size()==0 && !alive_solid_snake)||alive_solid_snake)&&(( player_snake.getbody().size() == 0&&(!alive_player))||(alive_player))) {
			if (alive_player == false && alive_solid_snake == false) { 
				m_context->m_assets->play_sound(asset_holder::DRAW);
				m_context->m_states->Add(std::make_unique<endgame>(m_context, "YOU DRAWED?!"), true); 
			}
			else if (alive_player == false) {
				m_context->m_assets->play_sound(asset_holder::LOSS);
				m_context->m_states->Add(std::make_unique<endgame>(m_context, "YOU LOST"), true);
			}
			else if (alive_solid_snake == false) {
				m_context->m_assets->play_sound(asset_holder::WIN);
				m_context->m_states->Add(std::make_unique<endgame>(m_context, "YOU WON"), true);
			}
		}
	}
}

void gameplay::render()
{
	m_context->m_window->clear();
	m_context->m_window->draw(grass);
	player_snake.draw(m_context->m_window.get());
	solid_snake.draw(m_context->m_window.get());
	for (const auto i : walls) {
		m_context->m_window->draw(i);
	}
	m_context->m_window->draw(apple);
	m_context->m_window->display();
}

void gameplay::pause()
{
	is_pause = true;
}

void gameplay::start()
{
	is_pause = false;
}
