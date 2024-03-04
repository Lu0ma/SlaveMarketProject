#include "Menu.h"

Menu::Menu(const string& _name, Menu* _owner)
{
	isInit = false;
	canvas = new Canvas(_name);
	pointer = nullptr;
	owner = _owner;
}