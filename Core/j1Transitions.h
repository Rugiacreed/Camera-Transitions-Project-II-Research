#ifndef __MODULEFADETOBLACK_H__
#define __MODULEFADETOBLACK_H__

#include "j1Module.h"
#include "j1Timer.h"
#include "SDL\include\SDL_rect.h"

enum which_animation {
	none,
	fade_to_black,
	fade_to_white,
	wipe,
	zoom,
	lerp
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

	bool Transition(which_animation type, j1Module* module_offp, j1Module* module_onp, float time = 2, float target_scalep = 2);
	float LerpValue(float percent, float start, float end);
	void SetTargetScale(int target_scalep);
	

private:
	which_animation w_anim=which_animation::none;

	j1Module* module_on = nullptr;
	j1Module* module_off = nullptr;
	float percent = 0;
	float total_time = 0;
	j1Timer timer;
	SDL_Rect screen;
	SDL_Rect WipeRect;
	
	//for the zoom transition
	int start_width;
	int start_height;
	int final_width;
	int final_height;
	int current_width;
	int current_height;
	float current_scale = 1;
	float target_scale;
	float normal_scale = 1;
	float percent2 = 0;


};

#endif //__MODULEFADETOBLACK_H__