#ifndef __MODULEFADETOBLACK_H__
#define __MODULEFADETOBLACK_H__

#include "j1Module.h"
#include "j1Timer.h"
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
		entering,
		exiting
	} current_step = fade_step::none;

	bool Transition(which_animation type, j1Module* module_offp, j1Module* module_onp, float time = 2);
	float LerpValue(float percent, float start, float end);
	

private:
	which_animation w_anim=which_animation::none;

	j1Module* module_on = nullptr;
	j1Module* module_off = nullptr;
	float percent = 0;
	float total_time = 0;
	j1Timer timer;
	SDL_Rect screen;
	SDL_Rect WipeRect;


};

#endif //__MODULEFADETOBLACK_H__