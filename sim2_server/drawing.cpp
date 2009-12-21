#include "drawing.h"

Drawing::Drawing(int realWidth, int realHeigth, int scrWidth, int scrHeigth, char *fontFile, unsigned int fSize, int cw, int ch){
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		cout << "Failed to initialize SDL: " << SDL_GetError();
		exit(1);
	}
	atexit(SDL_Quit);
	// Initilize the screen
	scr = SDL_SetVideoMode(scrWidth, scrHeigth, 32,SDL_HWSURFACE | SDL_DOUBLEBUF);
	if (scr == NULL) {
		cout << "Unable to set video mode: " << SDL_GetError();
		exit(1);
	}
	//load font data
	FILE *file;
	currFont = new char [fSize];
	file = fopen(fontFile, "r");
	fread(currFont, fSize, 1, file);
	fclose(file);
	gfxPrimitivesSetFont(currFont, cw, ch);
	//calcula relacao entre area da tela e mundo real
	xScale = (float) scrWidth/realWidth;
	yScale = (float) scrHeigth/realHeigth;
	scale = xScale;
}

void Drawing::clearScr(){
	SDL_FillRect(scr, NULL, 0);
}

void Drawing::updateScr(){
	SDL_Flip(scr);
}

void Drawing::drawCircle(const Point2d &center, int size, Uint32 color) {
	filledCircleColor(scr, (Sint16) (center.x *xScale), (Sint16) (center.y *yScale), (Sint16) (size *scale), color);
}

void Drawing::drawPolygon(Point2d vertices[], int nvertices, Uint32 color){
	Sint16 *x = new Sint16 [nvertices];
	Sint16 *y = new Sint16 [nvertices];

	for (int i = 0; i < nvertices; i++){
		x[i] = (Sint16) (vertices[i].x * xScale);
		y[i] = (Sint16) (vertices[i].y * yScale);
	}

	filledPolygonColor(scr, x, y, nvertices, color);
}

void Drawing::drawLine(const Point2d &ini, Point2d &fim, Uint32 color){
	lineColor(scr, (Sint16) (ini.x *xScale), (Sint16) (ini.y *yScale), (Sint16) (fim.x *xScale), (Sint16) (fim.y *yScale), color);
}

void Drawing::drawText(string text,Point2d pos, Uint32 color){
	stringColor(scr, pos.x, pos.y, text.c_str(), color);
}

Drawing::~Drawing(){
	//TODO pau loco
	//delete[] currFont;
}
