#pragma once
#include <vector>
#include <unordered_map>

namespace SubScreenName {
	enum SubScreenName { Options, OptionsDisplay };
}

class Game;
class Button;

class Screen {
	bool isShowing = false;
	int selectedButtonIt = 0;

	std::vector<Button*> buttons;
	std::unordered_map<SubScreenName::SubScreenName, Screen*> subScreens;
protected:
	void addButton(Button* buttonToAdd) { buttons.push_back(buttonToAdd); }
	void addSubScreen(SubScreenName::SubScreenName name, Screen* screenToAdd) { subScreens[name] = screenToAdd; }
public:
	virtual void update();
	virtual void draw();

	void setButtonValue(int buttonIt, std::string valueToSet);

	bool showing() { return isShowing; }
	void setShowing(bool s);
	void setShowingSubScreen(SubScreenName::SubScreenName name, bool toSet);
	Screen* getPresentSubScreen();

	Button* selectedButton(); // Return button that is under mouse else return nullptr

	Screen();
	virtual ~Screen();
};

