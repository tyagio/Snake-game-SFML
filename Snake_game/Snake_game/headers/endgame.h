#ifndef ENDGAME_H
#define ENDGAME_H

#include "context.h"
#include "mainmenu.h"
#include "gameplay.h"


class endgame :public state
{
private:
	std::shared_ptr<context>& m_context;
	sf::Text game_title;
	sf::Color color_text[2];
	sf::Text options[3];
	int option_no[2];
	std::string title;
public:
	endgame(std::shared_ptr<context>& context, const std::string& _title);
	virtual ~endgame();
	void init() override;
	void pollevents() override;
	void update(float& deltatime) override;
	void render() override;
};

#endif