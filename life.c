#include <stdio.h>
#include <stdlib.h>

#include "header.h"

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))
#define XD
#define true 1
#define false 0
// thanks :3




int neighbor_count(int state[GRIDSIZE][GRIDSIZE], int x, int y) {
	// i feel like removing that u was just making fun of me :(
	// also just realized this is using clang so i cant actually make
	// inline functions so that's cool
	// ?? just run gcc
	// ok where is min max
	//this is wrong near the edges but
	//well, i guess it works nevermind
	//usually you make the edges loop or something
	int neighbors = 0;
	int left = max(x - 1, 0);
	int top = max(y - 1, 0);
	int right = min(x + 1, GRIDSIZE-1);
	int bottom = min(y + 1, GRIDSIZE-1);
	// 
	//////////#pra  gma omp parallel for reduction(+:neighbors)
	// note: pragma balls broke everything
	for (int i = left; i <= right; i++)
	  for (int j = top; j <= bottom; j++)
	    // nvm wrong thinking in my head
		// i might have fixed it by just not cheating
		neighbors += (state[i][j] && !(i==x && j==y));
  //switch (right-left + (bottom-top)*2){case 0:break; case 1:} 
	return neighbors;
}
//what's the sudo password
//need to think of initializing board or whatever
extern int grp[GRIDSIZE*ZOOM][GRIDSIZE*ZOOM];

typedef int bool;
typedef int Row[GRIDSIZE];
typedef Row Board[GRIDSIZE];

Board states[2] = {0};
Row* oldstate = states[0];
Row* newstate = states[1];

bool running = false;

// we have to initialize it somehow
// (i feel like i should make it so it toggles)
void setpoint(int x, int y) {
	oldstate[x][y] = !oldstate[x][y];
}

// just to make testing easier, obviously there should be better input
// but F--- YOU !
void initializelife() {
	setpoint(1,1);
	setpoint(2,1);
	setpoint(3,1);
}

void click(int x,int y){
	puts("click");
    // you might also want to divide it by 8 because of scale
    setpoint(x/ZOOM,y/ZOOM);
}

void space() {
	puts("space");
    running = !running;
}

void Scale_render(int zoom) {
	int w = (GRIDSIZE);
	int h = (GRIDSIZE);
	int temp[GRIDSIZE][GRIDSIZE];
	for (int y=0; y<h; y++)
		for (int x=0; x<w; x++)
			temp[y][x] = grp[y][x];
	for (int y=0;y<GRIDSIZE*ZOOM;y++) {
		for (int x=0; x<GRIDSIZE*ZOOM; x++) {
			grp[y][x] = temp[y/zoom][x/zoom];
		}
	}
}


void frame() {
    // oh i overthought this didnt i
    // i couldve just had 3 dimensional array with one of them
    // being the state 
    //it is going to take me like 
    // 3 hours to decide whether it's [2][size][size] or [size][size][2]
    // lol
    // FINAL_ANSWER
    // THREE!
    // woah learning in real time !

    // wow this isnt as smooth as it looked in the animation
    
    // im not sure... entirely... hmmmmmm, i 

    //ok who has their indent set differently
    // for me it inserts a tab idk how to even change that

// is twelve doing all the work for you
    // pauses so that you can input things
	// no, um, i just dont really know what theyre doing
  // i'm just fixing the indents lol
	// ok why do you use two tabs... it looks horrible on
	// 4 indent size
// oh i had indent set to 2
// isn't that the default
// AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
/// oh i / well yesput 2
// tabs because/./ i didn't want to reindent that lol
// lol
	if (running) {//you better go catch it
		for (int x = 0; x < GRIDSIZE; ++x) {
 			for (int y = 0; y < GRIDSIZE; y++) {
				// this is seriously undercounting, but why
				int neighbors = neighbor_count(oldstate, x, y);
				//grp[y][x] = (int[]){0xFF0000,0xFFFF00,0x00FF00,0x00FFFF,0x0000FF,0xFF00FF,0x000000,0xFFFFFF}[neighbors];
				// we can simplify this later just let this work rn
				// check for live cells first
				// that was an issue
				// lol that was bad
				//if (neighbors) printf("%d\n", neighbors);
				int news = 0;
				if (oldstate[x][y]) {
					if (neighbors<2 || neighbors>3)
						news = 0;
					else
						news = 1;
				}
				// rules for if current cell is dead
				else {
					news = (neighbors == 3);
					// if (neighbors == 3)
					// 	news = 1;
					// is this actually required?
					// oh ok
					// yes because newstate is just the same array we used last frame so it  has junk data in it
					// else
					// 	newstate[x][y] = 0;
				}
				newstate[x][y] = news;
			}
    	}
		void* temp = oldstate;
		oldstate = newstate;
		newstate = temp;
	}
            // wait i had an idea in my head on how to do this but i actually
            // have no idea how to do it in C uhhhhhhhh maybe i can just be awful
            // oldstate = &newstate;
            // no i didnt think
            // ok im an idiot
    		// 
    		// need to make pointers to the arrays
    		// and then swap those
        // 
        // yeah, although im not 100% sure if that's what i want almost idk,,,
    // wait does this actually work? huh. ok is there a way to access X or something
    // for display. oh i wonder if some of the lag for the text is because of the
    // x session actually lol

	// yyyyyes
	// but like
	// hold on I'll make something uh
    //	static cherry;
    // static sue;
	//static const _Complex unsigned long long ligma; //XD
    //	const square_size = 8; // :<
  for (int x = 0; x < GRIDSIZE; ++x) {
    for (int y = 0; y < GRIDSIZE; y++) {
        // oh cool static - i didnt mean you had to do that literally lol
		// why is this undefined but it worked earlier ????
		// (note: this sucks at high res)
		// yes x and y are swapped here
			grp[y][x] = oldstate[x][y] ? 0xFFFFFF : 0x000000;
// grp[x][y] = rand()%2 ? 0xFFFFFF : 0x000000;
		}
	}
	Scale_render(ZOOM);
}
// oh i see where the indenting settings are now.
// if only x didnt take 3 hours to load....
// gcc life.c -o life -lX11 -Wall -fopenmp