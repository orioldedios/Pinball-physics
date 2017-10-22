#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleSceneIntro.h"
#include "ModuleFonts.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	ball = App->textures->Load("resources/sprites/ball.png");
	game_over = App->textures->Load("resources/sprites/game_over.png");

	if (font_score == -1)
		font_score = App->fonts->Load("resources/sprites/Alphabet.png", "0123456789abcdefghiklmnoprstuvwxyq<HIGH=!'·$%&/()-.€@ASD_GHJ", 6);

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

	if (balls.getFirst()==nullptr && lifes>0)
	{
		balls.add(App->physics->CreateBall(260, 430, 6));
		//balls.getLast()->data->listener = this;
	}
	else if (lifes == 0)
	{
		App->renderer->Blit(game_over, 41, 190);
		App->fonts->BlitText(136, 244, font_score, score_text);
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN &&
		lifes>0 &&
		METERS_TO_PIXELS(balls.getFirst()->data->body->GetPosition().x)>255 &&
		METERS_TO_PIXELS(balls.getFirst()->data->body->GetPosition().y)>217)
	{
		balls.getFirst()->data->body->ApplyLinearImpulse({ 0, -2 }, { 0, 0 }, true);
	}

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN &&
		lifes == 0)
	{
		lifes = 3;
		score = 0;
	}

	p2List_item<PhysBody*>* c = balls.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(ball, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	//score
	sprintf_s(score_text, "%06d", score);
	sprintf_s(balls_text, "%01d", lifes);

	App->fonts->BlitText(7, 485, font_score, score_text);
	App->fonts->BlitText(228, 486, font_score, balls_text);


	return UPDATE_CONTINUE;
}



