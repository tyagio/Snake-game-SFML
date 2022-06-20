#include "stdafx.h"
#include "../headers/endgame.h"

endgame::endgame(std::shared_ptr<context>& context,const std::string& _title) :m_context(context),title(_title)
{
}

endgame::~endgame()
{
}

void endgame::init()
{
	game_title.setFont(m_context->m_assets->get_font(0));
	game_title.setCharacterSize(60);
	game_title.setFillColor(sf::Color::Green);
	game_title.setString(title);
	game_title.setOrigin(game_title.getLocalBounds().width / 2.f, 0);
	game_title.setPosition(m_context->m_window->getSize().x / 2.f, 0.f);
	color_text[0] = sf::Color::White;
	color_text[1] = sf::Color::Red;
	options[0].setString("Main Menu");
	options[0].setPosition(m_context->m_window->getSize().x / 2.f, m_context->m_window->getSize().y / 2.f - 50.f);
	options[0].setFillColor(color_text[1]);
	options[1].setString("Retry");
	options[1].setPosition(m_context->m_window->getSize().x / 2.f, m_context->m_window->getSize().y / 2.f);
	options[1].setFillColor(color_text[0]);
	options[2].setString("Exit");
	options[2].setPosition(m_context->m_window->getSize().x / 2.f, m_context->m_window->getSize().y / 2.f + 50.f);
	options[2].setFillColor(color_text[0]);
	option_no[0] = 0;
	option_no[1] = 0;
	for (auto& i : options) {
		i.setFont(m_context->m_assets->get_font(0));
		i.setCharacterSize(30);
		i.setOrigin(i.getLocalBounds().width / 2.f, 0);

	}
}

void endgame::pollevents()
{
	sf::Event event;
	while (m_context->m_window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			m_context->m_window->close();
		}
		else if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code) {
			case sf::Keyboard::W:
				if (option_no[0] > 0) {
					option_no[0] -= 1;
					m_context->m_assets->play_sound(2);
				}
				break;
			case sf::Keyboard::S:
				if (option_no[0] < 2) {
					option_no[0] += 1;
					m_context->m_assets->play_sound(2);
				}
				break;
			case sf::Keyboard::Enter:
				switch (option_no[0]) {
				case 0:
					m_context->m_assets->play_sound(1);
					m_context->m_states->Add(std::make_unique<mainmenu>(m_context), true);
					break;
				case 1:
					m_context->m_assets->play_sound(0);
					m_context->m_states->Add(std::make_unique<gameplay>(m_context), true);
					break;
				case 2:
					m_context->m_window->close();
					break;
				default:
					printf("ERROR::ENDGAME::INVALID OPTION VALUE\n");
				}
				break;
				
			default:
				break;

			}
		}

	}
}

void endgame::update(float & deltatime)
{
	if (option_no[0] != option_no[1]) {
		for (auto& i : options) { i.setFillColor(color_text[0]); }
		options[option_no[0]].setFillColor(color_text[1]);
		option_no[1] = option_no[0];
	}
}
void endgame::render()
{
	m_context->m_window->clear(sf::Color::Blue);
	m_context->m_window->draw(game_title);
	for (const auto i : options) {
		m_context->m_window->draw(i);
	}
	m_context->m_window->display();
}
