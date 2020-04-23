#ifndef __MODULEFADETOBLACK_H__
#define __MODULEFADETOBLACK_H__

#include "j1Module.h"
#include "SDL\include\SDL_rect.h"

enum which_animation {
	none,
	fade_to_black,
	fade_to_white,
	wipe
};

class j1Transitions : public j1Module
{
public:
	j1Transitions();
	~j1Transitions();

	bool Start();
	bool PostUpdate();


public:
	enum fade_step
	{
		none,
		fade_to_black,
		fade_from_black
	} current_step = fade_step::none;

	bool FadeToBlack(j1Module* module_offp, j1Module* module_onp, float time = 2);
	bool FadeToWhite(j1Module* module_offp, j1Module* module_onp, float time = 2);

private:
	which_animation w_anim=which_animation::none;

	j1Module* module_on = nullptr;
	j1Module* module_off = nullptr;
	bool changing_to_scene = false;

	Uint32 start_time = 0;
	Uint32 total_time = 0;
	SDL_Rect screen;
};

#endif //__MODULEFADETOBLACK_H__