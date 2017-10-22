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

	int lifes = 3;
	int font_score = -1;

	char score_text[10];

	uint score = 0;

	bool ballCreated = false;

};