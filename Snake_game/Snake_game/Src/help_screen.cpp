#include "stdafx.h"
#include "../headers/help_screen.h"

help_screen::help_screen(std::shared_ptr<context>& context):m_context(context)
{
}

help_screen::~help_screen()
{
}

void help_screen::init()
{
	Helpfull_text.setFont(m_context->m_assets->get_font(0));
	Helpfull_text.setFillColor(sf::Color::White);
	Helpfull_text.setString("Use WASD for movement \n Avoid colliding into your body,walls\n and cyborg snake \n Collect apples to increase length of your snake\n Win by killing off cyborg snake \n\n\n Press Esc to exit help menu");
}

void help_screen::pollevents()
{
	sf::Event event;
	while (m_context->m_window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			m_context->m_window->close();
		}
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) {
				m_context->m_assets->play_sound(1);
				m_context->m_states->Popcurrent();
			}
	
		}

	}
}

void help_screen::update(float & deltatime)
{
}

void help_screen::render()
{
	m_context->m_window->clear(sf::Color::Blue);
	m_context->m_window->draw(Helpfull_text);
	m_context->m_window->display();
}
