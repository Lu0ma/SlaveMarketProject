#include "Menu.h"
#include "MenuManager.h"

Menu::Menu(const string& _name, Menu* _owner) : IManagable(_name)
{
	Register();

	isInit = false;
	canvas = new Canvas(_name);
	pointer = nullptr;
	owner = _owner;
}


void Menu::Register()
{
	MenuManager::GetInstance().Add(id, this);
}