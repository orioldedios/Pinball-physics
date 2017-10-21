#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> ricks;

	PhysBody* sensor;
	bool sensed;
	bool colision_coin[3] = { false,false,false };

	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* coin;
	SDL_Texture* back;
	SDL_Texture* flipperL;
	SDL_Texture* flipperR;

	uint coin_fx;
	p2Point<int> ray;
	bool ray_on;
};
