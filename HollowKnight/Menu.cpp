#include "Menu.h"
#include "MenuManager.h"

#define SOUND_SELECT "Ui/ui_change_selection"
Menu::Menu(const string& _name, Menu* _owner) : IManagable(_name)
{
	Register();

	isInit = false;
	canvas = new Canvas(_name);
	pointerLeft = nullptr;
	pointerRight = nullptr;
	backButton = nullptr;
	owner = _owner;
	sound = new SoundData(SOUND_SELECT, 100, false);
}


void Menu::Register()
{
	MenuManager::GetInstance().Add(id, this);
}

void Menu::MovePointers(Button* _button)
{
	TextWidget* _text = dynamic_cast<Label*>(_button->GetForeground());
	if (!_text) return;
	TextObject* _object = _text->GetObject();

	const Vector2f& _position = _object->GetShapePosition();
	const Vector2f& _size = _object->GetShapeSize();
	MovePointers(_position, _size);
}

void Menu::MovePointers(const Vector2f& _position, const Vector2f& _size)
{
	const float _halfSizeX = _size.x / 2.0f;
	const float _offsetX = _halfSizeX + 30.0f;
	const float _offsetY = _size.y * 0.5f;
	pointerLeft->SetShapePosition(_position + Vector2f(-_offsetX, _offsetY));
	pointerRight->SetShapePosition(_position + Vector2f(_offsetX, _offsetY));
	// new SoundData(SOUND_SELECT, 100, false);
	sound->play();
}

void Menu::Init()
{
	const Vector2f& _pointerSize = Vector2f(20.0f, 20.0f);
	pointerLeft = new ShapeWidget(ShapeData(Vector2f(), _pointerSize, PATH_POINTER));
	canvas->AddWidget(pointerLeft);

	pointerRight = new ShapeWidget(ShapeData(Vector2f(), _pointerSize, PATH_POINTER));
	pointerRight->GetDrawable()->setScale(-1.0f, 1.0f);
	canvas->AddWidget(pointerRight);
}