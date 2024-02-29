#include "InteractableActor.h"
#include "Game.h"
#include "Widget.h"
#include "Label.h"
#define FONT "Font.ttf"
#define UI_BUTTON "UIs/Charms/bottom_fleur0002.png"

InteractableActor::InteractableActor(const string& _name, const ShapeData& _data, const Vector2f& _sizeDetector) : Actor(_name , _data)
{
	// canvas = new Canvas("ee");
	cursor = new Canvas("Ui");
	canVerify = false;
	textScript = new Canvas("TEXT");
	
}

void InteractableActor::Update(const float _deltaTime)
{
	Actor::Update(_deltaTime);
	Verify();
}

void InteractableActor::Verify()
{
 	Player* _player = Game::GetPlayer();
	FloatRect _rectPNJ = shape->getGlobalBounds();

	// if (!canVerify) return ;
	if (_rectPNJ.intersects(_player->GetDrawable()->getGlobalBounds()))
	{
	 	if (cursor->GetVisibilityStatus()) return;
		cursor->SetVisibilityStatus(true);
	}
	else
	{
		cursor->SetVisibilityStatus(false);
		textScript->SetVisibilityStatus(false);
	}

}

void InteractableActor::Init()
{
 	ShapeWidget* _widget = new ShapeWidget(ShapeData(Vector2f(690.0f , 300.0f), Vector2f(303.0f, 66.0f), UI_BUTTON));
	cursor->AddWidget(_widget);

	const Vector2f& _windowSize = Game::GetWindowSize();
	const float _mainMenuTextPosY = _windowSize.y * 70.0f / 100.0f;
	const float _mainMenuTextPosX = _windowSize.x / 2.0f;
	Label* _text = new Label(TextData("Bienvenue à Shrek City !", Vector2f(_mainMenuTextPosX, _mainMenuTextPosY), FONT, 26));
	textScript->AddWidget(_text);

}

string InteractableActor::Scrolling(const string& _text)
{

	//string ScrollingText(const string& _text)
	//{

	//	for (int _i = 0; _i < _text.size(); _i++)
	//	{
	//		cout << _text[_i]; 
	//		sleep(time);
	//	}
	//}
	return string();
}
