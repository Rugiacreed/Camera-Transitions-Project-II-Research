#ifndef __MODULEFADETOBLACK_H__
#define __MODULEFADETOBLACK_H__

#include "j1Module.h"
#include "SDL\include\SDL_rect.h"

enum which_fade {
	unknown,
	logo_to_title,
	title_to_scene,
	scene_to_title
};

class j1FadeToBlack : public j1Module
{
public:
	j1FadeToBlack();
	~j1FadeToBlack();

	bool Start();
	bool PostUpdate();


public:
	enum fade_step
	{
		none,
		fade_to_black,
		fade_from_black
	} current_step = fade_step::none;

 
	
	which_fade actual_change = unknown;

	bool FadeToBlack(j1Module* module_offp, j1Module* module_onp, float time = 2);

private:

	j1Module* module_on = nullptr;
	j1Module* module_off = nullptr;
	bool changing_to_scene = false;



	Uint32 start_time = 0;
	Uint32 total_time = 0;
	SDL_Rect screen;
};

#endif //__MODULEFADETOBLACK_H__