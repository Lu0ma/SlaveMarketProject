#include "InteractableActor.h"
#include "Game.h"
#include "Widget.h"

#define PATH_HEALTH_MASK "UIs/Inventory/HealthMasks/HealthMask_"
InteractableActor::InteractableActor(const string& _name, const ShapeData& _data, const Vector2f& _sizeDetector) : Actor(_name , _data)
{
	sensorArea = new CircleShape(100.0f);
	sensorArea->setPosition(this->GetShapePosition());
	detector = sensorArea->getGlobalBounds();
	canvas = new Canvas("Ui");
}


void InteractableActor::Test()
{
ShapeWidget* _widget = new ShapeWidget(ShapeData(Vector2f(500.0f , 300.f), Vector2f(1000.0f, 1000.0f), PATH_HEALTH_MASK));
	canvas->AddWidget(_widget);
	canvas->SetVisibilityStatus(false);
}

void InteractableActor::Update(const float _deltaTime)
{
	Actor::Update(_deltaTime);
	Player* _player = Game::GetPlayer();



	if (detector.intersects(_player->GetDrawable()->getGlobalBounds()))
	{
		//	cout << "Appuyer sur E pour parler" << endl;
		canvas->SetVisibilityStatus(true);
	}
}

//void InteractableActor::Speak()
//{
//
//}