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
	p2List<PhysBody*> balls;
	p2List<PhysBody*> ricks;

	PhysBody* sensor_star[3];
	PhysBody* sensor_arrow_left[4];
	PhysBody* sensor_arrow_right[4];
	PhysBody* sensor_bonus_left;
	PhysBody* sensor_bonus_right;
	PhysBody* sensor_triangles[2];
	PhysBody* sensor_lose;

	bool sensed_bonus_left = false;
	bool sensed_bonus_right = false;
	bool sensed_star[3] = { false,false,false };
	bool sensed_arrow_left[4] = { false,false,false,false };
	bool sensed_arrow_right[4] = { false,false,false,false };
	bool colision_coin[3] = { false,false,false };
	bool sensed_triangles[2] = { false,false };

	SDL_Texture* circle;
	SDL_Texture* ball;
	SDL_Texture* box;
	SDL_Texture* coin;
	SDL_Texture* star;
	SDL_Texture* back;
	SDL_Texture* arrow_left;
	SDL_Texture* arrow_right;
	SDL_Texture* flipperL;
	SDL_Texture* flipperR;

	uint coin_fx;
	uint star_fx;
	uint bonus_left_fx;
	uint bonus_right_fx;
	uint triangle_fx;
	uint lose_fx;
};
