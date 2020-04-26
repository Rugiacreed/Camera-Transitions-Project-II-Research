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
	WipeTransRect = { -1280, 0, 1280,720 };
	
}

j1Transitions::~j1Transitions()
{}

// Load assets
bool j1Transitions::Start()
{
	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);
	CurtainTransRect = { -(int)App->win->GetWidth() / 2, 0, (int)App->win->GetWidth() / 2,720 };
	CurtainTransRect2 = { (int)App->win->GetWidth(), 0, (int)App->win->GetWidth() / 2,720 };
	return true;
}

// Update: draw background
bool j1Transitions::PostUpdate()
{
	if (ongoingstep == fade_step::none)
		return true;

	float normalized = MIN(1.0f, (float)timer.ReadSec() / (float)globaltime);

	switch (ongoingstep)
	{
	case fade_step::entering:
	{
		if (timer.ReadSec() >= globaltime)
		{
			module_off->Disable();
			module_on->Enable();
			
			timer.Start();
			ongoingstep = fade_step::exiting;
		}
	} break;

	case fade_step::exiting:
	{
		normalized = 1.0f - normalized;

		if (timer.ReadSec() >= globaltime)
			ongoingstep = fade_step::none;
	} break;
	}

	//the following switch decides which animation we're doing
	switch (w_anim) {

		//FADE TO BLACK TRANSITION
	case(which_animation::fade_to_black):
		// Finally render the black square with alpha on the screen
		SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, (Uint8)(normalized * 255.0f));
		SDL_RenderFillRect(App->render->renderer, &screen);
		break;

		//FADE TO WHITE TRANSITION
	case(which_animation::fade_to_white):
		// Finally render the white square with alpha on the screen
		SDL_SetRenderDrawColor(App->render->renderer, 255, 255, 255, (Uint8)(normalized * 255.0f));
		SDL_RenderFillRect(App->render->renderer, &screen);
		break;

		//WIPE TRANSITION
	case (which_animation::wipe):
		if (ongoingstep == fade_step::entering) {
			percentatge = timer.ReadSec() * (1 / (globaltime));
			float normalized_x_position = LerpValue(percentatge, -(int)App->win->GetWidth(), 0);

			if (normalized_x_position >= 0) {
				WipeTransRect.x = 0;
			}
			else WipeTransRect.x = normalized_x_position;

			
		}
		else if (ongoingstep== fade_step::exiting)
		{
			percentatge = timer.ReadSec() * (1 / globaltime);
			float normalized_x_position2 = LerpValue(percentatge, 0, -1280);

			if (normalized_x_position2 <= -1280) {
				WipeTransRect.x = -1280;
			}else WipeTransRect.x = normalized_x_position2;
		}
		//Finally we draw the two rect that will make the wipe
		SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(App->render->renderer, &WipeTransRect);
		break;

		//ZOOM TRANSITION
	case (which_animation::zoom):

		if (ongoingstep == fade_step::entering) {
			percentatge2 = timer.ReadSec() * (1 / globaltime);
			float normalized_scale = LerpValue(percentatge2, normal_scale, target_scale);

			float next_width = LerpValue(percentatge2, original_width, final_width);
			float next_height = LerpValue(percentatge2, original_height, final_height);

			float step_x = next_width - current_width;
			float step_y = next_height - current_height;

			App->render->camera.x += step_x;
			App->render->camera.y += step_y;

			current_scale = normalized_scale;
			SDL_RenderSetScale(App->render->renderer, normalized_scale, normalized_scale);
			current_height = next_height;
			current_width = next_width;
		}

		if (ongoingstep == fade_step::exiting) {
			//once we have done the zoom, we set the original scale for the next scene
			SDL_RenderSetScale(App->render->renderer, 1, 1);
			
		}
		break;

		//CURTAIN TRANSITION
	case (which_animation::curtain):
		if (ongoingstep == fade_step::entering) {
			percentatge = timer.ReadSec() * (1 / (globaltime));
			float normalized_x_positioncurtain1 = LerpValue(percentatge, -(int)App->win->GetWidth() / 2, 0);

			if (normalized_x_positioncurtain1 >= 0) {
				CurtainTransRect.x = 0;
			}
			else CurtainTransRect.x = normalized_x_positioncurtain1;

			float normalized_x_positioncurtain2 = LerpValue(percentatge, (int)App->win->GetWidth(), (int)App->win->GetWidth() / 2);

			if (normalized_x_positioncurtain2 <= (int)App->win->GetWidth() / 2) {
				CurtainTransRect2.x = (int)App->win->GetWidth() / 2;
			}
			else CurtainTransRect2.x = normalized_x_positioncurtain2;
		}
		else if (ongoingstep == fade_step::exiting)
		{
			percentatge = timer.ReadSec() * (1 / (globaltime));
			float normalized_x_positioncurtain1 = LerpValue(percentatge, 0, -(int)App->win->GetWidth() / 2);

			if (normalized_x_positioncurtain1 <= -(int)App->win->GetWidth() / 2) {
				CurtainTransRect.x = -(int)App->win->GetWidth() / 2;
			}
			else CurtainTransRect.x = normalized_x_positioncurtain1;

			float normalized_x_positioncurtain2 = LerpValue(percentatge, (int)App->win->GetWidth() / 2, (int)App->win->GetWidth());

			if (normalized_x_positioncurtain2 >= (int)App->win->GetWidth()) {
				CurtainTransRect2.x = (int)App->win->GetWidth();
			}
			else CurtainTransRect2.x = normalized_x_positioncurtain2;
		}
		//Finally we draw the two rects that will make the curtains
		SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(App->render->renderer, &CurtainTransRect);

		SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(App->render->renderer, &CurtainTransRect2);
		break;
	

	}

	return true;
}

// Fade to black. At mid point deactivate one module, then activate the other
bool j1Transitions::Transition(which_animation type, j1Module* module_offp, j1Module* module_onp, float time, float target_scalep)
{
	bool ret = false;

	w_anim = type;

	if (ongoingstep == fade_step::none)
	{
		
		module_off = module_offp;
		module_on = module_onp;
		ongoingstep = fade_step::entering;
		//start_time = SDL_GetTicks();
		globaltime = time;
		timer.Start();
		
		//for zoom
		target_scale = target_scalep;
		original_width = App->render->camera.w;
		original_height = App->render->camera.h;
		final_width = App->render->camera.w / target_scalep;
		final_height = App->render->camera.h / target_scalep;
		current_width = App->render->camera.w;
		current_height = App->render->camera.h;

		ret = true;
	}

	return ret;
}

float j1Transitions::LerpValue(float percent, float start, float end)
{
	return start + percent * (end - start);
}


void j1Transitions::SetTargetScale(int target_scalep)
{
	target_scale = target_scalep;
}