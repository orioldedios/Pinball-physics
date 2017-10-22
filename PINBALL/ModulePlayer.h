#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	p2List<PhysBody*> balls;
	SDL_Texture* ball;
	SDL_Texture* game_over;

	SDL_Texture* flipperL;
	SDL_Texture* flipperR;
	PhysBody* FlipperL;
	PhysBody* FlipperR;

	p2List_item<PhysBody*>* chainleft = nullptr;
	p2List_item<PhysBody*>* chainright = nullptr;

	int lifes = 3;
	int font_score = -1;

	char score_text[10];
	char balls_text[10];

	uint score = 0;
};