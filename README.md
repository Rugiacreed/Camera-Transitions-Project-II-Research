# Camera-Transitions-Project-II-Research
I'm Roger Pérez Romera student from CITM UPC Terrassa from the Development and Design career. 
This is my link to my github repository from this project: https://github.com/Rugiacreed/Camera-Transitions-Project-II-Research.

# CAMERA TRANSITIONS

A transition is a technique used in audio-visual productions to combine two scenes on after the other. In the film industry this technique is done at the post-production stage but in video games we must have them in mind during all the programming stage.  

Most commonly this is through a normal cut to the next shot. But there are a few differents styles to end a scene and introduce a new one, and with each of them we can produce a different effect at the spectator. 
There are several of them used commonly in films and we we’ll learn how they work forward in this page.

Think I should state that in the following project i will show the most used transitions and the ones most useful for video games from the programming point-of-view. Is it obvious that when we’re in a cinematic or narrative moment in a game the scenes transitions will work exactly the same as a film or any other narrative video. 
But when we’re talking about the player or user around our game we just don’t have characters and narrative elements, we have a amount of menus and differents scenes where the player constantly will be moving and these ones are not the same in a film.


## TYPES OF TRANSITIONS:

Fade, Cross Fade, Wipe and Pan and Zoom, these are some of the most used scene transitions in films but useful too in videogames and graphic interfaces, each one has it own meaning and importance. Each one will be transmit something different to the spectator and will be interesting choose wisely the one that you will use in your game.

### Fade:
This simple transition makes the scene gradually fade turning it slowly in a color or to a text slide. This type of transition is slow and creates tension between scenes, for this reasons its useful for transitions between important scenes like the first scenes of a videogame, main menus or at exiting it.

![Fade to black stages](http://write.flossmanuals.net/video-editing-using-kdenlive/introduction-to-video-effects/static/usingusing_effetcs_9.png)

![Fade to black example](http://www.davetech.co.uk/pages/screentransitions//gifs/fade.gif)

### Cross Fade:
This works similar as the last one but the first scene does not fade to a color or text slide, this one starts fading out at the same time the next scene starts fading in so we combine the fade of the two scenes at the same time. This works faster than a simple fade so i could be useful for pace the change between scenes.

![Cross fade example](http://2.bp.blogspot.com/-Xn96T7zDMGI/TvtQL6S4faI/AAAAAAAAABY/j_bGFSypMgs/s320/IC368459.png)

![Cross fade or dissolve](http://www.davetech.co.uk/pages/screentransitions//gifs/blur.gif)

### Wipe:
To make this one clear, it works as cleaning a coating of dust in a image. The dust would be the first scene and the next scene is the image you are cleaning. So at the same time you clean the image and you’re removing the dust(first scene) you can see part of the image(next scene). This gives freedom to the editor because it can be done in a lot of differents ways. It uses to be slow(although you can modify it velocity) so gives some time to the public to think about what have happened in the last scene while you are introducing a new one. The freedom that it gives allows the user to give to it an emotional charge to it depending how you do the wipe.
In these case we could use too a object or element to make the wipe, following the metaphor of cleaning the image these element would be the cloth we’re using to clean the dust and it will give a natural sensation to the scene.

![Wipe example](http://speedvr.co.uk/wp-content/uploads/2015/12/VR-linear-transitions-300x169.jpg)

![Wipe](http://www.davetech.co.uk/pages/screentransitions//gifs/blob_remake.gif)

### Pan and Zoom:
This transition is just how its named, it's a simple zoom to some direction to focus in new zone or element in the screen creating an entrance to a new scene. I’ve seen this used in a lot of maps to introduce a location and then what happens there but it can be done too for small elements and characters and this could give a lot more of drama to the scene but that could be considered more as a change of shot or point-of-view.

![Pan and zoom example](https://i.ytimg.com/vi/4z21NEC5uZQ/hqdefault.jpg)

![Pan and zoom](https://thumbs.gfycat.com/FlashyMintyIrishterrier-size_restricted.gif)

The power of transmition that this transition have is heavier than the others, but its more difficult to use because is not that easy to load the next scene at the same time you do the movement of the camera, so normally you combine the zoom with another transition or in big games the loading screen.

## The power of camera transitions.

Moving from one moment to another and how you choose to do it will have an incredibly effect to the audience. And doing it right will help in crafting the intended experience for that audience. 

This is the main reason from the point-of-view of a filmaker. If we’re a designer of a videogame we know that during all time our game is running in a determined capability, and when we make loads for an scene these capability will determine if the game freezes or runs slower, these transitions will make us easy to load a scene or level without the player knowing our game is doing so. So hiding these moments will increment the positively thinkning of the player who is in front of the screen. In most of the games where change to a level or scene takes a lot of time are used the loading scenes, these are done between transitions indicating the player that the level or scene is loading.

So starting thinking in our code, our objective will be do the change of scene and and the load of the scene while the middle of the transition, if we do it before the player will see that time the game holds loading everything and then will do the transition so its useless for our objective and if we do it later the transition same. 

## REFERENCES:

- https://pt.slideshare.net/ShelbyBrown1/camera-transitions-and-edits/5
- https://www.youtube.com/watch?v=fKgvno6k-og
- https://en.wikipedia.org/wiki/Film_transition
- https://news.avclub.com/edgar-wright-s-scott-pilgrim-is-a-master-class-in-scene-1798253073
- http://www.davetech.co.uk/screentransitions

## CODE

For the code i decided to do it the most simple as possible, keeping it at the same time with high efficiency. For that i’ve used 1 main module for the process of creation of the transitions in my project. Then there are two scenes named Scene1 and Scene2 that will call the function transition and the transition module that will create the transitions at the same times it acts as a manager of them.

### Transition.h

In this module we will create two main elements, first of all we create an enum that controls which type of transition are we doing, for this project I’ve added 5 differents transitions. Two of them are a fade to black and a fade to white, these are the most basic ones to do but I did them to let understand the structure of the code with a simple example of a transition, the next three are more complicated ones but they will give you more ways to play with the scenes.

![EnumWhichtransition](https://github.com/Rugiacreed/Camera-Transitions-Project-II-Research/blob/master/Web%20Images/TransitionsH.PNG?raw=true)

Then, following the enum named which_animation we must create a class daughter of j1Module, this will be named j1Transitions and will contain the following elements: a constructor and destructor of the class, the main functions Start and PostUpdate. Then we will have three specific functions added to be able to do all the effects and transitions, the most important is the bool Transition where we call it we initiate the transition with the variables that we have in the function.  

Inside this class we have another enum, this will determine in which ongoing step are we during the transition, these are entering(before the scene change) and exiting(after the change scene), the change of scene is done when we finish the entering step but is included in it.


![ClassTransitions1](https://github.com/Rugiacreed/Camera-Transitions-Project-II-Research/blob/master/Web%20Images/functionstransitions.PNG?raw=true)

![ClassTransitions2](https://github.com/Rugiacreed/Camera-Transitions-Project-II-Research/blob/master/Web%20Images/variablestransitions.PNG?raw=true)

### Transition.cpp

Here we will create all the effects for the camera transition and to draw them to the screen, the most relevant part of this code is the two switch i have used to manage the creation of transitions in the postUpdate. The first one just switches between the two steps of the transition, it depends of the time we determine to change between the two steps and when the exiting step is done the next step is none(we don’t do nothing!!!).

The next switch is where we have all the transitions processes, each one have different functionalities and they are done depending of the input the player give. So this switch basically will do the blit of the different rects we have for the differents transitions.

![TransitionsCPP](https://github.com/Rugiacreed/Camera-Transitions-Project-II-Research/blob/master/Web%20Images/TransitionsCPP.PNG?raw=true)

### Scene1 and Scene2

This two scenes work as any other in our last projects, just make sure to call the function transitions when the chosen input, called this function you will have to give which transition are we doing, the module you want to disable(the scene we have) and the module we’re enabling(the scene we are entering) and the time it will take.

![Scene1](https://github.com/Rugiacreed/Camera-Transitions-Project-II-Research/blob/master/Web%20Images/Scene1.PNG?raw=true)

## TODOS

We will create a new transition, this already exists in the solution, but now is your turn to do it.
The new transition will be a wipe that acts like a curtain, and we will do this in six steps.

### TODO 1

The first step is just create a new type of transition. For that you will need to uncomment the curtain type of transition and create a new case in the enum in the Transitions.cpp.


### TODO 2

This is easy. The second Todo just requires create two new rects that we will use in the next transition. Do it in the j1Transitions class.


### TODO 3

To create the two rects required, we need to give them their values. Each rect will cover half of the screen. They will start from the two laterals of the screen.


### TODO 4

This Todo is more complicated, you already have two variables that will help you, uncomment them. You must create inside the case and in the step “entering”  the way the rects will be drawn. See some hints in the image below TODO 5.

### TODO 5

For the fifth Todo you just have to draw the two rects created before, you can use functions:
- SDL_SetRenderDrawColor
- SDL_RenderFillRect


### TODO 6

This last Todo is a gift. Create and input to call the Transition function in Scene01. Remember to give all the needed variables!


