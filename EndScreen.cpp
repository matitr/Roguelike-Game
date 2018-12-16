#include "SDL.h"
#include "SDL_TTF.h"
#include "EndScreen.h"
#include "Button.h"
#include "DataBase.h"
#include "Game.h"




void EndScreen::draw() {
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
	SDL_RenderClear(Game::renderer);
	Screen::draw();
	SDL_RenderCopy(Game::renderer, gameResultTxt, NULL, &dstRectGameResult);
	SDL_RenderCopy(Game::renderer, pointsTxt, NULL, &dstRectPoints);
}

void EndScreen::setStats(bool win, int points) {
	if (gameResultTxt)
		SDL_DestroyTexture(gameResultTxt);
	if (pointsTxt)
		SDL_DestroyTexture(pointsTxt);

	char charArrayText[100] = "";
	if (win)
		strcpy_s(charArrayText, "You won!");
	else
		strcpy_s(charArrayText, "Game over");

	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(DataBase::fonts[FontPurpose::GameEndResult], charArrayText, DataBase::colors[TextColor::MenuButtonText]);
	gameResultTxt = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage);
	SDL_FreeSurface(surfaceMessage);
	SDL_QueryTexture(gameResultTxt, NULL, NULL, &dstRectGameResult.w, &dstRectGameResult.h);
	dstRectGameResult.x = gameResultTxtCenter.x - dstRectGameResult.w / 2;
	dstRectGameResult.y = gameResultTxtCenter.y - dstRectGameResult.h / 2;

	sprintf_s(charArrayText, "Points: %i", points);
	surfaceMessage = TTF_RenderText_Blended(DataBase::fonts[FontPurpose::MenuButtonsText], charArrayText, DataBase::colors[TextColor::MenuButtonText]);
	pointsTxt = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage);
	SDL_FreeSurface(surfaceMessage);
	SDL_QueryTexture(pointsTxt, NULL, NULL, &dstRectPoints.w, &dstRectPoints.h);
	dstRectPoints.x = pointsTxtCenter.x - dstRectPoints.w / 2;
	dstRectPoints.y = pointsTxtCenter.y - dstRectPoints.h / 2;
}

EndScreen::EndScreen(int windowResX, int windowResY) : dstRectGameResult{ windowResX / 2,int(windowResY * 0.2), 0, 0 }, dstRectPoints{ windowResX / 2,int(windowResY * 0.4), 0, 0 } {
	SDL_Rect r = {
		windowResX / 2,
		int(windowResY * 0.7),
		int(windowResX * 0.2),
		int(windowResY * 0.05),
	};

	gameResultTxtCenter.x = dstRectGameResult.x;
	gameResultTxtCenter.y = dstRectGameResult.y;
	pointsTxtCenter.x = dstRectPoints.x;
	pointsTxtCenter.y = dstRectPoints.y;

	addButton(new Button(r, "New game", [](Screen* parentScreen, ScreensManager* sM, Game* game) { sM->newGame(game); }));
	r.y = int(windowResY * 0.8);
	addButton(new Button(r, "Exit", [](Screen* parentScreen, ScreensManager* sM, Game* game) { sM->quitGame(game); }));

}


EndScreen::~EndScreen() {
	SDL_DestroyTexture(gameResultTxt);
	SDL_DestroyTexture(pointsTxt);
}
