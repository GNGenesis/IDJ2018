#ifndef MUSIC_H_
#define MUSIC_H_

//Make 2018/1
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

//Make 2017/1
/*#include "SDL_mixer.h"*/

#include <string>

class Music {
private:
	Mix_Music* music;

public:
	Music();
	Music(std::string file);
	~Music();
	void Open(std::string file);
	void Play(int times = -1);
	void Stop(int msToStop = 1500);
	bool IsOpen();
};

#endif /* MUSIC_H_ */
