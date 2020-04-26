#ifndef __MODULEFADETOBLACK_H__
#define __MODULEFADETOBLACK_H__

#include "j1Module.h"
#include "j1Timer.h"
#include "SDL\include\SDL_rect.h"

//this enum will manage all the transitions, using it to indicate which type of transition we're using
enum which_animation {
	none,
	fade_to_black,
	fade_to_white,
	wipe,
	zoom,
	curtain
};

class j1Transitions : public j1Module
{
public:
//main functions
	j1Transitions();
	~j1Transitions();

	bool Start();
	bool PostUpdate();


public:
//this enum indicates the situation of the transition/effect we are in
	enum fade_step
	{
		none,
		entering,
		exiting
	} ongoingstep = fade_step::none;


	bool Transition(which_animation type, j1Module* module_offp, j1Module* module_onp, float time = 2, float target_scalep = 2);
	
	//the following calculates the percentatge of the transition that is done
	float LerpValue(float percent, float start, float end);

	//for the zoom camera transition, it sets the camera scale that we will get at the final of the zoom transition
	void SetTargetScale(int target_scalep);
	

private:
	which_animation w_anim=which_animation::none;

	//desactivate and activate the modules
	j1Module* module_on = nullptr;
	j1Module* module_off = nullptr;

	//used for calculating the percentage of screen doing the effect of the transition
	//we calculate it using the time of the transition and position of our rects that we create during it
	float percentatge = 0;
	float globaltime = 0;
	j1Timer timer;

	//used for the renders and the transitions functions
	SDL_Rect screen;
	SDL_Rect WipeTransRect;
	SDL_Rect CurtainTransRect;
	SDL_Rect CurtainTransRect2;

	
	
	//for the zoom transition
	int original_width;
	int original_height;
	int final_width;
	int final_height;
	int current_width;
	int current_height;
	float current_scale = 1;
	float target_scale;
	float normal_scale = 1;
	float percentatge2 = 0;
	float percent3 = 0;


};

#endif //__MODULEFADETOBLACK_H__