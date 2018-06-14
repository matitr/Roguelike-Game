#pragma once
#include "Screen.h"
#include "SDL.h"

class Button;
struct SDL_Point;

class EndScreen : public Screen {
	SDL_Texture* gameResultTxt = nullptr;
	SDL_Rect dstRectGameResult;
	SDL_Point gameResultTxtCenter;

	SDL_Texture* pointsTxt = nullptr;
	SDL_Rect dstRectPoints;
	SDL_Point pointsTxtCenter;

public:
	void update(Game* g) override;
	void draw() override;

	void setStats(bool win, int points);

	EndScreen(int windowResX, int windowResY);
	~EndScreen();
};

