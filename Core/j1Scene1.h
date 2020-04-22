#ifndef __j1SCENE1__
#define __j1SCENE1__

#include "j1Module.h"
#include "j1Timer.h"

struct SDL_Texture;

class j1Scene1 : public j1Module
{
public:

	j1Scene1();

	// Destructor
	virtual ~j1Scene1();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

private:
	SDL_Texture* debug_tex;
};

#endif // __j1SCENE1__