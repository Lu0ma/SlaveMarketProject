#include "Menu.h"

Menu::Menu(const string& _name, Menu* _owner) : IManagable(_name)
{
	isInit = false;
	canvas = new Canvas(_name);
	pointer = nullptr;
	owner = _owner;
}