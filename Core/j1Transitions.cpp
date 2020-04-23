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
#include "j1Window.h"

j1Transitions::j1Transitions()
{
	screen = { 0, 0, 1280,720 };
	WipeRect = { 0, 0, 1280,720 };
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

	float normalized = MIN(1.0f, (float)timer.ReadSec() / (float)total_time);

	switch (current_step)
	{
	case fade_step::entering:
	{
		if (timer.ReadSec() >= total_time)
		{
			module_off->Disable();
			module_on->Enable();

			total_time += total_time;
			current_step = fade_step::exiting;
		}
	} break;

	case fade_step::exiting:
	{
		normalized = 1.0f - normalized;

		if (timer.ReadSec() >= total_time)
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
		if (current_step == fade_step::entering) {
			percent = timer.ReadSec() * (1 / total_time);
			float normalized_x_position = LerpValue(percent, -(int)App->win->GetWidth(), 0);

			if (normalized_x_position >= 0)
				WipeRect.x = 0;
			else WipeRect.x = normalized_x_position;
			
		}
		else if (current_step== fade_step::exiting)
		{
			percent = timer.ReadSec() * (1 / total_time);
			float normalized_x_position = LerpValue(percent, 0, -(int)App->win->GetWidth());

			if (normalized_x_position <= -(int)App->win->GetWidth())
				WipeRect.x = -(int)App->win->GetWidth();
			else WipeRect.x = normalized_x_position;
		}
		SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(App->render->renderer, &WipeRect);
		break;

	}

	return true;
}

// Fade to black. At mid point deactivate one module, then activate the other
bool j1Transitions::Transition(which_animation type, j1Module* module_offp, j1Module* module_onp, float time)
{
	bool ret = false;

	w_anim = type;

	if (current_step == fade_step::none)
	{
		
		module_off = module_offp;
		module_on = module_onp;
		current_step = fade_step::entering;
		//start_time = SDL_GetTicks();
		total_time = time;
		timer.Start();
		ret = true;
	}

	return ret;
}

float j1Transitions::LerpValue(float percent, float start, float end)
{
	return start + percent * (end - start);
}