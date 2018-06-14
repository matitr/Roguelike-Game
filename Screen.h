#pragma once
#include <vector>

class Game;
class Button;

class Screen {
	bool isShowing = false;
	
protected:
	std::vector<Button*> buttons;

public:
	bool showing() { return isShowing; }
	void setShowing(bool s) { isShowing = s; }

	virtual void update(Game* g) = 0;
	virtual void draw();

	Button* buttonUnderMouse();

	Screen();
	virtual ~Screen();
};

