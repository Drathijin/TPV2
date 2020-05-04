#pragma once

#include <SDL.h>
#include <string>
#include <vector>

using namespace std;

class Resources {
public:

	enum TextureId : std::size_t {
		// images
		Asteroid,
		Blank,
		Bullet,
		TennisBall,
		KeyBoardIcon,
		MouseIcon,
		AIIcon,
		SpaceShips,
		Airplanes,
		Star,
		Heart,
		

		// text
		HelloWorld,
		PressAnyKey,
		GameOverLose,
		GameOverWin
	};

	enum AudioId : std::size_t {
		// music
		Beat,
		Cheer,
		Boooo,
		Imperial_March,

		// sound effects
		Explosion,
		GunShot
	};
	enum FontId : std::size_t {
		ARIAL16, ARIAL24,
	};

	struct FontInfo {
		FontId id;
		string fileName;
		int size;
	};

	struct ImageInfo {
		TextureId id;
		string fileName;
	};

	struct TextMsgInfo {
		TextureId id;
		string msg;
		SDL_Color color;
		FontId fontId;
	};

	struct MusicInfo {
		AudioId id;
		string fileName;
	};

	struct SoundInfo {
		AudioId id;
		string fileName;

	};

	static vector<FontInfo> fonts_; // initialized in .cpp
	static vector<ImageInfo> images_; // initialized in .cpp
	static vector<TextMsgInfo> messages_; // initialized in .cpp
	static vector<MusicInfo> musics_; // initialized in .cpp
	static vector<SoundInfo> sounds_; // initialized in .cpp

};
