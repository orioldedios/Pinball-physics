#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = box = coin =star=back= arrow_left= arrow_right= flipperL= flipperR= NULL;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	//music
	App->audio->PlayMusic("resources/audio/bso/bso.ogg");

	// back_walls
	int background[66] = {
		113, 500,
		0, 499,
		0, 640,
		276, 640,
		276, 499,
		167, 499,
		178, 481,
		249, 448,
		246, 349,
		233, 337,
		234, 283,
		250, 222,
		250, 491,
		265, 491,
		264, 174,
		271, 134,
		271, 95,
		261, 63,
		242, 37,
		214, 18,
		174, 8,
		120, 6,
		63, 18,
		31, 45,
		12, 76,
		7, 121,
		11, 167,
		20, 219,
		40, 283,
		41, 337,
		21, 353,
		21, 445,
		100, 482
	};

	int wall1[40] = {
		60, 279,
		68, 270,
		57, 242,
		46, 203,
		42, 165,
		43, 144,
		54, 108,
		72, 88,
		104, 73,
		110, 72,
		111, 52,
		93, 34,
		72, 39,
		53, 52,
		40, 69,
		30, 96,
		26, 127,
		26, 153,
		34, 200,
		48, 243 };
	int wall2[38] = { 
		215, 277,
		207, 270,
		219, 238,
		230, 197,
		233, 160,
		230, 129,
		219, 104,
		203, 88,
		179, 77,
		164, 73,
		164, 52,
		182, 34,
		208, 42,
		229, 62,
		240, 81,
		249, 118,
		248, 154,
		241, 195,
		227, 244 };
	int wall3[26] = {
		197, 241,
		184, 232,
		193, 202,
		180, 195,
		163, 224,
		152, 219,
		182, 101,
		196, 113,
		212, 144,
		216, 159,
		216, 182,
		212, 207,
		204, 230
	};
	int wall4[42] = {
		124, 219,
		110, 224,
		91, 186,
		86, 180,
		80, 179,
		74, 182,
		74, 188,
		80, 203,
		90, 234,
		77, 241,
		67, 219,
		62, 204,
		59, 188,
		58, 171,
		59, 156,
		65, 139,
		71, 122,
		82, 108,
		92, 100,
		102, 123,
		124, 166
	};
	int wall5[18] = {
		97, 416,
		95, 408,
		73, 362,
		68, 358,
		64, 362,
		64, 402,
		67, 406,
		82, 414,
		92, 419
	};
	int wall6[20] = {
		178, 417,
		176, 413,
		177, 406,
		190, 377,
		197, 361,
		201, 358,
		208, 364,
		207, 404,
		191, 414,
		183, 418
	};
	int wall7[14] = {
		48, 366,
		41, 362,
		42, 422,
		54, 432,
		88, 448,
		96, 442,
		47, 417
	};
	int wall8[16] = {
		185, 447,
		180, 441,
		182, 437,
		225, 417,
		226, 361,
		231, 365,
		232, 419,
		229, 426
	};

	int flipperleft[18] = {
		3, 1,
		0, 5,
		1, 10,
		37, 25,
		41, 25,
		42, 22,
		40, 19,
		9, 1,
		6, 0
	};
	int flipperright[18] = {
		42, 3,
		42, 7,
		41, 10,
		5, 25,
		2, 24,
		2, 20,
		30, 3,
		35, 1,
		39, 1
	};

	App->physics->CreateChain(0, 0, background, 66, b2_staticBody);
	App->physics->CreateChain(0, 0, wall1, 40, b2_staticBody);
	App->physics->CreateChain(0, 0, wall2, 38, b2_staticBody);
	App->physics->CreateChain(0, 0, wall3, 26, b2_staticBody);
	App->physics->CreateChain(0, 0, wall4, 42, b2_staticBody);
	App->physics->CreateChain(0, 0, wall5, 18, b2_staticBody);
	App->physics->CreateChain(0, 0, wall6, 20, b2_staticBody);
	App->physics->CreateChain(0, 0, wall7, 14, b2_staticBody);
	App->physics->CreateChain(0, 0, wall8, 16, b2_staticBody);
	App->physics->CreateChain(85, 439, flipperleft, 18, b2_dynamicBody);
	App->physics->CreateChain(144, 439, flipperright, 18, b2_dynamicBody);

	circles.add(App->physics->CreateCircle(118, 100, 10));
	circles.add(App->physics->CreateCircle(155, 100, 10));
	circles.add(App->physics->CreateCircle(137, 68, 10));
	circles.add(App->physics->CreateCircle(73, 371, 7));
	circles.add(App->physics->CreateCircle(75, 376, 7));
	circles.add(App->physics->CreateCircle(77, 381, 7));
	circles.add(App->physics->CreateCircle(79, 386, 7));
	circles.add(App->physics->CreateCircle(81, 391, 7));
	circles.add(App->physics->CreateCircle(83, 396, 7));
	circles.add(App->physics->CreateCircle(85, 401, 7));
	circles.add(App->physics->CreateCircle(87, 406, 7));
	circles.add(App->physics->CreateCircle(197, 371, 7));
	circles.add(App->physics->CreateCircle(195, 376, 7));
	circles.add(App->physics->CreateCircle(193, 381, 7));
	circles.add(App->physics->CreateCircle(191, 386, 7));
	circles.add(App->physics->CreateCircle(189, 391, 7));
	circles.add(App->physics->CreateCircle(187, 396, 7));
	circles.add(App->physics->CreateCircle(185, 401, 7));
	circles.add(App->physics->CreateCircle(183, 406, 7));

	ball = App->textures->Load("resources/sprites/ball.png");
	back = App->textures->Load("resources/sprites/background.png");
	coin = App->textures->Load("resources/sprites/coin.png");
	star = App->textures->Load("resources/sprites/star.png");
	arrow_left = App->textures->Load("resources/sprites/arrow_left.png");
	arrow_right = App->textures->Load("resources/sprites/arrow_right.png");
	flipperL = App->textures->Load("resources/sprites/flipperleft.png");
	flipperR = App->textures->Load("resources/sprites/flipperright.png");

	coin_fx = App->audio->LoadFx("resources/audio/fx/coin.ogg");
	star_fx = App->audio->LoadFx("resources/audio/fx/star.wav");
	bonus_left_fx = App->audio->LoadFx("resources/audio/fx/bonus_left.ogg");
	bonus_right_fx = App->audio->LoadFx("resources/audio/fx/bonus_right.ogg");
	triangle_fx = App->audio->LoadFx("resources/audio/fx/triangles.ogg");
	lose_fx = App->audio->LoadFx("resources/audio/fx/game_over.ogg");

	sensor_star[0] = App->physics->CreateRectangleSensor(92, 218, 10, 9);
	sensor_star[1] = App->physics->CreateRectangleSensor(88, 206, 10, 9);
	sensor_star[2] = App->physics->CreateRectangleSensor(82, 195, 10, 9);

	sensor_arrow_left[0] = App->physics->CreateRectangleSensor(55, 125, 8, 8);
	sensor_arrow_left[1] = App->physics->CreateRectangleSensor(60, 113, 10, 9);
	sensor_arrow_left[2] = App->physics->CreateRectangleSensor(66, 103, 10, 9);
	sensor_arrow_left[3] = App->physics->CreateRectangleSensor(77, 94, 10, 9);

	sensor_arrow_right[0] = App->physics->CreateRectangleSensor(194, 96, 8, 8);
	sensor_arrow_right[1] = App->physics->CreateRectangleSensor(204, 105, 10, 9);
	sensor_arrow_right[2] = App->physics->CreateRectangleSensor(212, 116, 10, 9);
	sensor_arrow_right[3] = App->physics->CreateRectangleSensor(217, 126, 10, 9);

	sensor_bonus_left = App->physics->CreateRectangleSensor(78, 180, 8, 8);
	sensor_bonus_right = App->physics->CreateRectangleSensor(185, 200, 8, 8);

	sensor_triangles[0] = App->physics->CreateRectangleSensor(83, 387, 17, 43);
	sensor_triangles[1] = App->physics->CreateRectangleSensor(186, 387, 17, 43);

	sensor_lose= App->physics->CreateRectangleSensor(138, 496, 100, 8);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	circles.clear();
	balls.clear();

	App->textures->Unload(circle);
	App->textures->Unload(ball);
	App->textures->Unload(box);
	App->textures->Unload(coin);
	App->textures->Unload(star);
	App->textures->Unload(back);
	App->textures->Unload(arrow_left);
	App->textures->Unload(arrow_right);
	App->textures->Unload(flipperL);
	App->textures->Unload(flipperR);

	circle = nullptr;
	ball = nullptr;
	box = nullptr;
	coin = nullptr;
	star = nullptr;
	back = nullptr;
	arrow_left = nullptr;
	arrow_right = nullptr;
	flipperL = nullptr;
	flipperR = nullptr;

	coin_fx=0;
	star_fx = 0;
	bonus_left_fx = 0;
	bonus_right_fx = 0;
	triangle_fx = 0;
	lose_fx = 0;

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	//Blits
	App->renderer->Blit(back, 0, 0);
	App->renderer->Blit(flipperL, 85, 439);
	App->renderer->Blit(flipperR, 144, 439);

	if (sensed_star[0])
		App->renderer->Blit(star, 92, 218);
	if (sensed_star[1])
		App->renderer->Blit(star, 88, 206);
	if (sensed_star[2])
		App->renderer->Blit(star, 82, 195);
	if (sensed_bonus_left)
		App->renderer->Blit(star, 77, 182);
	if (sensed_arrow_left[0])
		App->renderer->Blit(arrow_left, 44, 120);
	if (sensed_arrow_left[1])
		App->renderer->Blit(arrow_left, 50, 109);
	if (sensed_arrow_left[2])
		App->renderer->Blit(arrow_left, 56, 99);
	if (sensed_arrow_left[3])
		App->renderer->Blit(arrow_left, 66, 90);
	if (sensed_arrow_right[0])
		App->renderer->Blit(arrow_right, 187, 90);
	if (sensed_arrow_right[1])
		App->renderer->Blit(arrow_right, 196, 98);
	if (sensed_arrow_right[2])
		App->renderer->Blit(arrow_right, 203, 108);
	if (sensed_arrow_right[3])
		App->renderer->Blit(arrow_right, 207, 119);



	//// Draw the Ball ------------------------------------------------------
	//p2List_item<PhysBody*>* c = balls.getFirst();

	//while (c != NULL)
	//{
	//	int x, y;
	//	c->data->GetPosition(x, y);
	//	App->renderer->Blit(ball, x, y, NULL, 1.0f, c->data->GetRotation());
	//	c = c->next;
	//}

	if (App->player->balls.getLast() != nullptr)
		App->player->balls.getLast()->data->listener = this;

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	//ignore walls
	if (bodyA->body->GetFixtureList()->GetShape()->GetType() != 3 &&
		bodyB->body->GetFixtureList()->GetShape()->GetType() != 3)
	{
		//coin1
		if (bodyA->body->GetFixtureList()->GetShape()->GetType() == 0 &&
			bodyB->body->GetFixtureList()->GetShape()->GetType() == 0 &&
			bodyA->body->GetType() == b2_dynamicBody &&
			bodyB->body->GetType() == b2_staticBody &&
			METERS_TO_PIXELS(bodyB->body->GetPosition().y == 100) &&
			METERS_TO_PIXELS(bodyB->body->GetPosition().x < 119))
		{
			App->player->score += 300;
			App->audio->PlayFx(coin_fx);
			colision_coin[0] = true;
		}
		else
		{
			colision_coin[0] = false;
		}

		//coin2
		if (bodyA->body->GetFixtureList()->GetShape()->GetType() == 0 &&
			bodyB->body->GetFixtureList()->GetShape()->GetType() == 0 &&
			bodyA->body->GetType() == b2_dynamicBody &&
			bodyB->body->GetType() == b2_staticBody &&
			METERS_TO_PIXELS(bodyB->body->GetPosition().y == 100) &&
			METERS_TO_PIXELS(bodyB->body->GetPosition().x > 119))
		{
			App->player->score += 300;
			App->audio->PlayFx(coin_fx);
			colision_coin[1] = true;
		}
		else
		{
			colision_coin[1] = false;
		}

		//coin3
		if (bodyA->body->GetFixtureList()->GetShape()->GetType() == 0 &&
			bodyB->body->GetFixtureList()->GetShape()->GetType() == 0 &&
			bodyA->body->GetType() == b2_dynamicBody &&
			bodyB->body->GetType() == b2_staticBody &&
			METERS_TO_PIXELS(bodyB->body->GetPosition().y < 100))
		{
			App->player->score += 300;
			App->audio->PlayFx(coin_fx);
			colision_coin[2] = true;
		}
		else
		{
			colision_coin[2] = false;
		}

		//stars
		for (uint i = 0; i < 3; i++) {
			if (bodyA == sensor_star[i] ||
				bodyB == sensor_star[i])
			{
				sensed_star[i] = true;
				App->audio->PlayFx(star_fx);
				App->player->score += 500;
			}
			else
			{
				sensed_star[i] = false;
			}
		}

		//left_arrows
		for (uint i = 0; i < 4; i++) {
			if (bodyA == sensor_arrow_left[i] ||
				bodyB == sensor_arrow_left[i])
			{
				sensed_arrow_left[i] = true;
				App->audio->PlayFx(star_fx);
				App->player->score += 150;
			}
			else
			{
				sensed_arrow_left[i] = false;
			}
		}

		//right_arrows
		for (uint i = 0; i < 4; i++) {
			if (bodyA == sensor_arrow_right[i] ||
				bodyB == sensor_arrow_right[i])
			{
				sensed_arrow_right[i] = true;
				App->audio->PlayFx(star_fx);
				App->player->score += 150;
			}
			else
			{
				sensed_arrow_right[i] = false;
			}
		}

		//bonus_left
		if (bodyA == sensor_bonus_left ||
			bodyB == sensor_bonus_left)
		{
			sensed_bonus_left = true;
			App->audio->PlayFx(bonus_left_fx);
			App->player->score += 10000;
		}
		else
		{
			sensed_bonus_left = false;
		}

		//bonus_right
		if (bodyA == sensor_bonus_right ||
			bodyB == sensor_bonus_right)
		{
			App->audio->PlayFx(bonus_right_fx);
			App->player->score += 10000;
		}

		//lose
		if (bodyA == sensor_lose ||
			bodyB == sensor_lose)
		{
			App->audio->PlayFx(lose_fx);
			App->player->lifes -= 1;
			App->player->balls.clear();
		}

		//triangles
		for (uint i = 0; i < 2; i++) {
			if (bodyA == sensor_triangles[i] ||
				bodyB == sensor_triangles[i])
			{
				App->audio->PlayFx(triangle_fx);
			}

		}
	}
}
