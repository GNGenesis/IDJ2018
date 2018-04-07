#ifndef SPRITE_H_
#define SPRITE_H_

//Make 2018/1
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

//Make 2017/1
/*#include "SDL_image.h"*/

#include <string>

class Sprite {
private:
	SDL_Texture* texture;
	SDL_Rect clipRect;
	int width;
	int height;


public:
	Sprite();
	Sprite(std::string file);
	~Sprite();
	void Open(std::string file);
	void SetClip(int x, int y, int w, int h);
	void Render(int x, int y);
	int GetWidth();
	int GetHeight();
	bool IsOpen();
};

#endif /* SPRITE_H_ */
