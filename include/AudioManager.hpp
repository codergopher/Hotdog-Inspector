#include <SDL2/SDL_mixer.h>
#include <string>
#include <map>
class AudioManager
{
public:
	AudioManager();
	void Play(const char* p_clip);
private:
	std::map<const char*, Mix_Chunk*> clips;
};