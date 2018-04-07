#ifndef SPRITE_H_
#define SPRITE_H_

#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

#include "Component.h"

#include <string>

class Sprite : public Component {
private:
	SDL_Texture* texture;
	SDL_Rect clipRect;
	bool on;
	int width;
	int height;

public:
	Sprite(GameObject& associated);
	Sprite(GameObject& associated, std::string file);
	~Sprite();
	void Open(std::string file);
	void SetClip(int x, int y, int w, int h);
	void Toggle();
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	int GetWidth();
	int GetHeight();
	bool IsOpen();
	bool IsOn();

};

#endif /* SPRITE_H_ */
