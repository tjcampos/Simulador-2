#include "kbddecoder.h"

string KbdDecoder::decodeKbdEvent(){
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				return "quits";
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						return "quit";
						break;
					case SDLK_p:
						return "pause";
						break;
					case SDLK_o:
						return "step";
						break;
					case SDLK_f:
						return "fast";
						break;
					case SDLK_q:
						return "leftup";
						break;
					case SDLK_w:
						return "rightup";
						break;
					case SDLK_e:
						return "bothup";
						break;
					case SDLK_a:
						return "leftdown";
						break;
					case SDLK_s:
						return "rightdown";
						break;
					case SDLK_d:
						return "bothdown";
						break;
					default:
						break;
				}
				break;
		}
	}

	return "";
}
