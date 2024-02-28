#include "InteractableActor.h"
#include "Game.h"



InteractableActor::InteractableActor(const string& _name, const ShapeData& _data, const Vector2f& _sizeDetector) : Actor(_name , _data)
{
	sensorArea = new CircleShape(100.0f , 100.0f);
	sensorArea->setPosition(this->GetShapePosition());
	detector = sensorArea->getGlobalBounds();
}





void InteractableActor::Update(const float _deltaTime)
{
	Actor::Update(_deltaTime);
	Player* _player = Game::GetPlayer();
	if (detector.intersects(_player->GetShape()->getGlobalBounds()))
	{
		cout << "Appuyer sur E pour parler" << endl;
	}
} 




void InteractableActor::Speak()
{
	
}
