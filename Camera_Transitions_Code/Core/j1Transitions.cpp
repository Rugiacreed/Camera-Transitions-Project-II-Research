#include <math.h>
#include "j1App.h"
#include "j1Transitions.h"
#include "j1Render.h"
#include "SDL/include/SDL_render.h"
#include "SDL/include/SDL_timer.h"
#include "j1Map.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Scene1.h"
#include "j1Scene2.h"
#include "j1Map.h"

j1Transitions::j1Transitions()
{
	screen = { 0, 0, 1280,720 };
}

j1Transitions::~j1Transitions()
{}

// Load assets
bool j1Transitions::Start()
{
	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);
	return true;
}

// Update: draw background
bool j1Transitions::PostUpdate()
{
	if (current_step == fade_step::none)
		return true;

	Uint32 now = SDL_GetTicks() - start_time;
	float normalized = MIN(1.0f, (float)now / (float)total_time);

	switch (current_step)
	{
	case fade_step::fade_to_black:
	{
		if (now >= total_time)
		{
			module_off->Disable();
			module_on->Enable();

			total_time += total_time;
			start_time = SDL_GetTicks();
			current_step = fade_step::fade_from_black;
		}
	} break;

	case fade_step::fade_from_black:
	{
		normalized = 1.0f - normalized;

		if (now >= total_time)
			current_step = fade_step::none;
	} break;
	}

	switch (w_anim) {
	case(which_animation::fade_to_black):
		// Finally render the black square with alpha on the screen
		SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, (Uint8)(normalized * 255.0f));
		SDL_RenderFillRect(App->render->renderer, &screen);
		break;
	case(which_animation::fade_to_white):
		// Finally render the black square with alpha on the screen
		SDL_SetRenderDrawColor(App->render->renderer, 255, 255, 255, (Uint8)(normalized * 255.0f));
		SDL_RenderFillRect(App->render->renderer, &screen);
		break;
	case (which_animation::wipe):

		break;
	}

	return true;
}

// Fade to black. At mid point deactivate one module, then activate the other
bool j1Transitions::FadeToBlack(j1Module* module_offp, j1Module* module_onp, float time)
{
	bool ret = false;

	w_anim = which_animation::fade_to_black;

	if (current_step == fade_step::none)
	{
		module_off = module_offp;
		module_on = module_onp;
		current_step = fade_step::fade_to_black;
		start_time = SDL_GetTicks();
		total_time = (Uint32)(time * 0.5f * 1000.0f);

		ret = true;
	}

	return ret;
}

// Fade to black. At mid point deactivate one module, then activate the other
bool j1Transitions::FadeToWhite(j1Module* module_offp, j1Module* module_onp, float time)
{
	bool ret = false;

	w_anim = which_animation::fade_to_white;

	if (current_step == fade_step::none)
	{
		module_off = module_offp;
		module_on = module_onp;
		current_step = fade_step::fade_to_black;
		start_time = SDL_GetTicks();
		total_time = (Uint32)(time * 0.5f * 1000.0f);

		ret = true;
	}

	return ret;
}