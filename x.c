#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>


#include "header.h"
// probably have to manually link it
// i think can use a makefile maybe

Display* D;
Window win;
XImage* image;

#define WIDTH GRIDSIZE
#define HEIGHT GRIDSIZE
void click(int x,int y);
void redraw() {
	XPutImage(D, win, DefaultGC(D, 0), image, 0,0, 0,0, WIDTH*ZOOM,HEIGHT*ZOOM);
}

int grp[HEIGHT*ZOOM][WIDTH*ZOOM];

static bool processEvent(void) {
	while (1) {
		static union {
			XEvent event;
			XMotionEvent motion;
			XKeyEvent key;
			XButtonEvent button;
			XClientMessageEvent clientMessage;
		} ev;
		Bool t = XCheckWindowEvent(D, win, ~0L, &ev.event);
		if (!t)
			return true;
		switch (ev.event.type) {
		case Expose:
			redraw();
			break;
		case ButtonPress:;
			click(ev.button.x,ev.button.y);
		case KeyPress:;
			KeySym key = XLookupKeysym(&ev.key, 0);
			if (!key) break;
			if (key==XK_space) {
				space();

			} 

		}
	}
}

void frame(void);

int main(int argc, char** argv) {
	D = XOpenDisplay(NULL);
	Visual* visual = DefaultVisual(D, 0);
	if (visual->class!=TrueColor) {
		fprintf(stderr, "Cannot handle non true color visual ...\n");
		XCloseDisplay(D);
		exit(1);
	}
	// Create window
	win = XCreateSimpleWindow(D, RootWindow(D, 0), 0, 0, WIDTH*ZOOM, HEIGHT*ZOOM, 1, 0, 0);
	XSelectInput(D, win, ButtonPressMask|ExposureMask|KeyPressMask);
	XMapWindow(D, win);
	
	image = XCreateImage(D, visual, 24, ZPixmap, 0, (char*)grp, WIDTH*ZOOM,HEIGHT*ZOOM, 32, 0);

	initializelife();
	frame();
	redraw();
	while (processEvent()) {
		frame();
		redraw();
	}
}
	
