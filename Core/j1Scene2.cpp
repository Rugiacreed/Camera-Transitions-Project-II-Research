#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Scene1.h"
#include "j1Scene2.h"
#include"j1Audio.h"
#include"j1FadeToBlack.h"

j1Scene2::j1Scene2() : j1Module()
{
	name.append("scene2");
	active = true;
}

// Destructor
j1Scene2::~j1Scene2()
{}

// Called before the first frame
bool j1Scene2::Start()
{
	debug_tex = App->tex->Load("assets/Naruto.jpeg");
	return true;
}

// Called each loop iteration
bool j1Scene2::PostUpdate()
{
	SDL_Rect sec2 = { 0, 0, 1280, 720 };
	App->render->Blit(debug_tex, 0, 0, &sec2, 0.0f, 0);

	return true;
}

// Called before quitting
bool j1Scene2::CleanUp()
{
	App->tex->UnLoad(debug_tex);
	return true;
}