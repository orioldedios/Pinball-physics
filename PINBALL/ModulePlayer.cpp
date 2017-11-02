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

	flipperL = App->textures->Load("resources/sprites/flipperleft.png");
	flipperR = App->textures->Load("resources/sprites/flipperright.png");

	int flipperleft[14] = {
		103, 443,
		98, 443,
		96, 447,
		97, 452,
		126, 464,
		130, 462,
		130, 459
	};


	int flipperright[14] = {
		147, 458,
		147, 462,
		151, 463,
		179, 451,
		180, 447,
		178, 442,
		173, 442
	};

	anchorleft = App->physics->CreateCircle(100, 447, 1);
	anchorright = App->physics->CreateCircle(176, 446, 1);


	FlipperL = App->physics->CreateFlipper(flipperleft, 14, 0, anchorleft);
	FlipperR = App->physics->CreateFlipper(flipperright, 14, 0, anchorright);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(flipperL);
	App->textures->Unload(flipperR);
	App->textures->Unload(ball);

	flipperL = nullptr;
	flipperR = nullptr;
	ball = nullptr;

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

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		FlipperL->body->ApplyLinearImpulse({ 0, 1 }, { 0,0 }, true);
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		FlipperR->body->ApplyLinearImpulse({ 0, -1 }, { 0,0 }, true);
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

	//flippers
	App->renderer->Blit(flipperL, 96, 443, NULL, 1, FlipperL->GetRotation(), PIXEL_TO_METERS(110), PIXEL_TO_METERS(447));
	App->renderer->Blit(flipperR, 146, 442, NULL, 1, FlipperR->GetRotation(), PIXEL_TO_METERS(1450), PIXEL_TO_METERS(420));


	return UPDATE_CONTINUE;
}



