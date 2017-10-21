#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = box = rick = NULL;
	ray_on = false;
	sensed = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

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
		254, 222,
		254, 491,
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

	App->physics->CreateChain(0, 0, background, 66, b2_staticBody);
	App->physics->CreateChain(0, 0, wall1, 40, b2_staticBody);
	App->physics->CreateChain(0, 0, wall2, 38, b2_staticBody);
	App->physics->CreateChain(0, 0, wall3, 26, b2_staticBody);
	App->physics->CreateChain(0, 0, wall4, 42, b2_staticBody);
	App->physics->CreateChain(0, 0, wall5, 18, b2_staticBody);
	App->physics->CreateChain(0, 0, wall6, 20, b2_staticBody);
	App->physics->CreateChain(0, 0, wall7, 14, b2_staticBody);
	App->physics->CreateChain(0, 0, wall8, 16, b2_staticBody);

	circles.add(App->physics->CreateCircle(118, 100, 10));
	circles.add(App->physics->CreateCircle(155, 100, 10));
	circles.add(App->physics->CreateCircle(137, 68, 10));

	box = App->textures->Load("pinball/crate.png");
	ball = App->textures->Load("pinball/wheel.png"); 
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");
	back = App->textures->Load("pinball/background.png");

	sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT+500, SCREEN_WIDTH, 1000);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{

	App->renderer->Blit(back, 0, 0);
	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		ray_on = !ray_on;
		ray.x = App->input->GetMouseX();
		ray.y = App->input->GetMouseY();
	}

	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		balls.add(App->physics->CreateBall(App->input->GetMouseX(), App->input->GetMouseY(), 6));
		balls.getLast()->data->listener = this;
	}

	if(App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		boxes.add(App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 100, 50));
	}

	

	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = balls.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
			App->renderer->Blit(ball, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = boxes.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		if(ray_on)
		{
			int hit = c->data->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);
			if(hit >= 0)
				ray_hit = hit;
		}
		c = c->next;
	}

	c = ricks.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	// ray -----------------
	if(ray_on == true)
	{
		fVector destination(mouse.x-ray.x, mouse.y-ray.y);
		destination.Normalize();
		destination *= ray_hit;

		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		if(normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;

	/*App->audio->PlayFx(bonus_fx);*/

	/*
	if(bodyA)
	{
		bodyA->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}

	if(bodyB)
	{
		bodyB->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}*/
}
