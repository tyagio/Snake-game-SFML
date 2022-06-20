#include "stdafx.h"
#include "../headers/game.h"

void game::InitFonts()
{
	m_context->m_assets->add_font(0, "Fonts/KaushanScript-Regular.otf");
}

void game::InitTextures()
{
	m_context->m_assets->add_texture(asset_holder::APPLE, "Images/apple.png");
	m_context->m_assets->add_texture(asset_holder::ORGANIC_SNAKE, "Images/custom_organic_snake.png");
	m_context->m_assets->add_texture(asset_holder::CYBORG_SNAKE, "Images/custom_cyborg_snake.png");
	m_context->m_assets->add_texture(asset_holder::GRASS, "Images/grass_random_grid.png",true);
	m_context->m_assets->add_texture(asset_holder::WALL, "Images/custom_wall.png", true);
}

void game::InitSounds() {
	m_context->m_assets->add_sound_buffer(asset_holder::FORWARD_BUTTON, "Sounds/button_forward.flac");
	m_context->m_assets->add_sound_buffer(asset_holder::BACKWARD_BUTTON, "Sounds/button_backward.flac");
	m_context->m_assets->add_sound_buffer(asset_holder::BUTTON_CHANGE, "Sounds/beep.flac");
	m_context->m_assets->add_sound_buffer(asset_holder::CYBORG_GROW, "Sounds/cyborg_grow.wav");
	m_context->m_assets->add_sound_buffer(asset_holder::SNAKE_GROW, "Sounds/player_grow.flac");
	m_context->m_assets->add_sound_buffer(asset_holder::WIN, "Sounds/win_sound.flac");
	m_context->m_assets->add_sound_buffer(asset_holder::DRAW, "Sounds/draw_sound.flac");
	m_context->m_assets->add_sound_buffer(asset_holder::LOSS, "Sounds/loss_sound.flac");
	m_context->m_assets->add_sound_buffer(asset_holder::GRASS_SOUND1, "Sounds/grass_rustle_1.flac");
	m_context->m_assets->add_sound_buffer(asset_holder::GRASS_SOUND2, "Sounds/grass_rustle_2.flac");
	m_context->m_assets->add_sound_buffer(asset_holder::GRASS_SOUND3, "Sounds/grass_rustle_3.flac");
	m_context->m_assets->add_sound_buffer(asset_holder::GRASS_SOUND4, "Sounds/grass_rustle_4.flac");
}
game::game()

{
	m_context = std::make_shared<context>();
	m_context->m_window->create(sf::VideoMode(608,416), "2 Snakes, 1 Lawn", sf::Style::Close);
	InitTextures();
	InitFonts();
	InitSounds();
	m_context->m_states->Add(std::make_unique<mainmenu>(m_context));
}

game::~game()
{
}

void game::run()
{
	sf::Clock timer;
	float dt;
	m_context->m_states->ProcessStatechange();
	while ((m_context->m_window->isOpen()) && !(m_context->m_states->is_empty()))
	{
		    dt = timer.restart().asSeconds();
			m_context->m_assets->clear_sounds();
			m_context->m_states->Getcurrent()->pollevents();
			m_context->m_states->Getcurrent()->update(dt);
			m_context->m_states->Getcurrent()->render();
			m_context->m_states->ProcessStatechange();

	}
}
