#include "Resources.h"
#include "SDL_macros.h"

vector<Resources::FontInfo> Resources::fonts_ {
//
		{ ARIAL16, "resources/fonts/ARIAL.ttf", 16 }, //
		{ ARIAL24, "resources/fonts/ARIAL.ttf", 24 } //
};

vector<Resources::ImageInfo> Resources::images_ {
//
		{ Asteroid, "resources/images/asteroid.png" }, //
		{ Bullet, "resources/images/whiterect.png" }, //
		{ SpaceShips, "resources/images/spaceships.png" }, //
		{ Airplanes, "resources/images/airplanes.png" }, //
};

vector<Resources::TextMsgInfo> Resources::messages_ {
//
		{ PressAnyKey, "Press Any Key to Start", { COLOR(0xaaffbbff) }, ARIAL24 }, //
		{ GameOverLose, "Game Over, you lose", { COLOR(0xffbbbbff) }, ARIAL24 },
		{ GameOverWin, "Game Over, you win", { COLOR(0xbbffbbff) }, ARIAL24 }
};

vector<Resources::MusicInfo> Resources::musics_ {
//
};

vector<Resources::SoundInfo> Resources::sounds_ {
//
		{ Explosion, "resources/sound/explosion.wav" }, //
		{ GunShot, "resources/sound/GunShot.wav"}
};

