#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Scene1.h"
#include "j1Scene2.h"
#include"j1Audio.h"
#include"j1Transitions.h"


j1Scene1::j1Scene1() : j1Module()
{
	name.append("scene1");
	active = true;
}

// Destructor
j1Scene1::~j1Scene1()
{}

// Called before the first frame
bool j1Scene1::Start()
{
	App->scene2->active = false;
	debug_tex = App->tex->Load("assets/Naruto.jpeg");
	return true;
}

// Called each loop iteration
bool j1Scene1::PostUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {
		App->transitions->Transition(which_animation::fade_to_black, (j1Module*)App->scene1, (j1Module*)App->scene2, 2);
	}
	else if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) {
		App->transitions->Transition(which_animation::wipe, (j1Module*)App->scene1, (j1Module*)App->scene2, 2);
	}

	SDL_Rect sec2 = { 0, 0, 1280, 720 };
	App->render->Blit(debug_tex, 0, 0, &sec2,0.0f,0);

	return true;
}

// Called before quitting
bool j1Scene1::CleanUp()
{
	App->tex->UnLoad(debug_tex);
	return true;
}