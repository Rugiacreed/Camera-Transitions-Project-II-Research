#ifndef __j1SCENE2__
#define __j1SCENE2__

#include "j1Module.h"
#include "j1Timer.h"

struct SDL_Texture;

class j1Scene2 : public j1Module
{
public:

	j1Scene2();

	// Destructor
	virtual ~j1Scene2();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

private:
	SDL_Texture* debug_tex;
};

#endif // __j1SCENE2__