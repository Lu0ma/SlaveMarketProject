#include "InteractableActor.h"
#include "Game.h"
#include "Widget.h"
#include "Label.h"

#define FONT "Font.ttf"
#define UI_BUTTON "UIs/Charms/bottom_fleur0002.png"

InteractableActor::InteractableActor(const string& _name, const ShapeData& _data) : Actor(_name, _data)
{
	canvas = new Canvas(STRING_ID("Interactable"));
	cursor = nullptr;
	textScript = nullptr;
	isPlay = true;
	Register();
}


void InteractableActor::Register()
{
	ActorManager::GetInstance().AddInteractable(this);
}

void InteractableActor::Init()
{
	cursor = new ShapeWidget(ShapeData(Vector2f(690.0f, 300.0f), Vector2f(303.0f, 66.0f), UI_BUTTON));
	canvas->AddWidget(cursor);

	const Vector2f& _windowSize = Game::GetWindowSize();
	const float _mainMenuTextPosY = _windowSize.y * 70.0f / 100.0f;
	const float _mainMenuTextPosX = _windowSize.x / 2.0f;
	textScript = new Label(TextData("Bienvenue � Shrek City !", Vector2f(_mainMenuTextPosX, _mainMenuTextPosY), FONT, 26));
	canvas->AddWidget(textScript);
}

void InteractableActor::Update(const float _deltaTime)
{
	Actor::Update(_deltaTime);
	Verify();
}

void InteractableActor::Verify()
{
	if(!NeedToVerify()) return;
 	Player* _player = Game::GetPlayer();
	FloatRect _rectPNJ = shape->getGlobalBounds();
	
	if (_rectPNJ.intersects(_player->GetDrawable()->getGlobalBounds()))
	{
		cursor->SetVisible(true);
		if (isPlay)
		{
			textScript->SetVisible(true);
		}
	}
	else
	{
		cursor->SetVisible(false);
		textScript->SetVisible(false);
		isPlay = false;
	}
}