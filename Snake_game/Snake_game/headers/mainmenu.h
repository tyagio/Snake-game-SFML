#ifndef MAINMENU_H
#define MAINMENU_H
 
#include "help_screen.h"
#include "gameplay.h"

class mainmenu :public state
{
private:
	std::shared_ptr<context>& m_context;
	sf::Text game_title;
	sf::Text credits;
	sf::Color color_text[2];
	sf::Text options[3];
	int option_no[2];

public:
	mainmenu(std::shared_ptr<context>& context);
	virtual ~mainmenu();
	void init() override;
	void pollevents() override;
	void update(float& deltatime) override;
	void render() override;
};

#endif