#pragma once
#include "Singleton.h"
#include "IManager.h"
#include "Menu.h"

class MenuManager : public Singleton<MenuManager>, public IManager<string, Menu>
{
public:
	template <typename T>
	T* GetMenu()
	{
		for (Menu* _currentMenu : GetAllValues())
		{
			if (T* _menu = dynamic_cast<T*>(_currentMenu))
			{
				return _menu;
			}
		}

		return nullptr;
	}
};