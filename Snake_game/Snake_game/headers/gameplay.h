#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "endgame.h"
#include "snake.h"
#include "ai_snake.h"
class gameplay : public state
{
private:

	std::shared_ptr<context>& m_context;
	float timer;
	bool is_pause;
	bool alive_player;
	bool alive_solid_snake;

	int dir;

	snake player_snake;
	ai_snake solid_snake;

	sf::Sprite grass;
	sf::Sprite walls[4];

	bool grow_player;
	bool grow_solid_snake;

	sf::Sprite apple;

	void initvariables();
	void inittext();
	void apple_generator(std::list<sf::RectangleShape>& snake1, std::list<sf::RectangleShape>& snake2);
	
public:
	//constructor and destructor
	gameplay(std::shared_ptr<context> &context);
	virtual ~gameplay();
	const bool running() const;
	//functions from state 
	void init() override;
	void pollevents() override;
	void update(float& _dt) override;
	void render() override;
	void pause() override;
	void start() override;
};

#endif


