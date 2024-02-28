#include "HUD.h"
#include "InputManager.h"
#include "Widget.h"
#include "Button.h"

void HUD::Interact(const Vector2f& _worldPosition, const Event::EventType& _type)
{
	for (Button* _button : buttons)
	{
		if (!_button->IsVisible()) continue;

		if (_button->GetDrawable()->getGlobalBounds().contains(_worldPosition))
		{
			if (_type == Event::EventType::MouseButtonPressed)
			{
				_button->OnPressed();
			}

			_button->OnHovered();
		}

		else
		{
			_button->OnUnhovered();
		}

		if (_type == Event::EventType::MouseButtonReleased)
		{
			_button->OnReleased();
		}

		_button->OnHeld();
	}
}

Button* HUD::GetHoveredButton(const vector<Button*>& _buttons)
{
	const Vector2f& _worldPosition = InputManager::GetInstance().GetWorldPosition();

	for (Button* _button : _buttons)
	{
		if (_button->IsVisible() && _button->GetDrawable()->getGlobalBounds().contains(_worldPosition))
		{
			return _button;
		}
	}

	return nullptr;
}

Button* HUD::GetPressedButton(const vector<Button*>& _buttons)
{
	const Vector2f& _worldPosition = InputManager::GetInstance().GetWorldPosition();

	for (Button* _button : _buttons)
	{
		if (_button->IsVisible() && _button->GetDrawable()->getGlobalBounds().contains(_worldPosition))
		{
			return _button;
		}
	}

	return nullptr;
}
