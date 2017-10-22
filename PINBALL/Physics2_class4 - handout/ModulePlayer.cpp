#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleSceneIntro.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	ball = App->textures->Load("pinball/ball.png");
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	////Ball test
	//if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	//{
	//	balls.add(App->physics->CreateBall(App->input->GetMouseX(), App->input->GetMouseY(), 6));
	//	//balls.getLast()->data->listener = this;
	//}

	if (ballCreated == false && lifes == 3)
	{
		balls.add(App->physics->CreateBall(260, 430, 6));
		//balls.getLast()->data->listener = this;
		ballCreated = true;
	}

	else if (ballCreated == false && lifes < 3 && lifes > 0) 
	{
		balls.add(App->physics->CreateBall(260, 430, 6));
		//balls.getLast()->data->listener = this;
		ballCreated = true;
	}
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		balls.getFirst()->data->body->ApplyLinearImpulse({ 0, -2 }, { 0, 0 }, true);
	}
	p2List_item<PhysBody*>* c = balls.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(ball, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}
	return UPDATE_CONTINUE;
}



