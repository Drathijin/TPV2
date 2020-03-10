#include "Resources.h"
#include "SDL_macros.h"

vector<Resources::FontInfo> Resources::fonts_ {
//
		{ ARIAL16, "resources/fonts/ARIAL.ttf", 16 }, //
		{ ARIAL24, "resources/fonts/ARIAL.ttf", 24 } //
};

vector<Resources::ImageInfo> Resources::images_ {
//
		{ Blank, "resources/images/blank.png" }, //
		{ Bullet, "resources/images/whiterect.png" }, //
		{ TennisBall, "resources/images/tennis_ball.png" }, //
		{ KeyBoardIcon, "resources/images/keyboard.png" }, //
		{ MouseIcon, "resources/images/mouse.png" }, //
		{ AIIcon, "resources/images/ai.png" }, //
		{ SpaceShips, "resources/images/spaceships.png" }, //
		{ Airplanes, "resources/images/airplanes.png" }, //
		{ Heart, "resources/images/heart.png" }, //
		{ Star, "resources/images/star.png" },//
		{ Asteroid, "resources/images/asteroid.png" }, //
		{ Bullet, "resources/images/whiterect.png" } //
};

vector<Resources::TextMsgInfo> Resources::messages_ {
//
		{ HelloWorld, "Hello World", { COLOR(0xaaffffff) }, ARIAL16 }, //
		{ PresAnyKey, "Press Any Key ...", { COLOR(0xaaffbbff) }, ARIAL24 }, //
		{ GameOver, "Game Over", { COLOR(0xffffbbff) }, ARIAL24 } //
};

vector<Resources::MusicInfo> Resources::musics_ {
//
		{ Beat, "resources/sound/beat.wav" }, //
		{ Cheer, "resources/sound/cheer.wav" }, //
		{ Boooo, "resources/sound/boooo.wav" }, //
		{ Imperial_March, "resources/sound/imperial_march.wav"}
};

vector<Resources::SoundInfo> Resources::sounds_ {
//
		{ Explosion, "resources/sound/explosion.wav" }, //
		{ GunShot, "resources/sound/GunShot.wav"}
};

