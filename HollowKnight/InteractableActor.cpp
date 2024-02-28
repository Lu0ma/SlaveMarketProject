#include "InteractableActor.h"
#include "Game.h"
#include "Widget.h"

#define PATH_HEALTH_MASK "UIs/Inventory/HealthMasks/HealthMask_"

Canvas* InteractableActor::canvas;
FloatRect InteractableActor::detector;

InteractableActor::InteractableActor(const string& _name, const ShapeData& _data, const Vector2f& _sizeDetector) : Actor(_name , _data)
{
	sensorArea = new CircleShape(10.0f);
	sensorArea->setPosition(this->GetShapePosition());
	detector = sensorArea->getGlobalBounds();
	canvas = new Canvas("Ui");
	ShapeWidget* _widget = new ShapeWidget(ShapeData(this->GetShapePosition(), Vector2f(100.0f, 100.0f), PATH_HEALTH_MASK));
	canvas->AddWidget(_widget);
}

void InteractableActor::Update(const float _deltaTime)
{
	Actor::Update(_deltaTime);
	Player* _player = Game::GetPlayer();
	if (detector.intersects(_player->GetDrawable()->getGlobalBounds()))
	{
		// cout << "Appuyer sur E pour parler" << endl;
		if (canvas->GetVisibilityStatus()) return;
		canvas->SetVisibilityStatus(true);
	}
	else
	{
		canvas->SetVisibilityStatus(false);

	}
	// Verify();
}

void InteractableActor::Verify()
{
	if (canvas->GetVisibilityStatus())
	{
		cout << "OUI" << endl; // Afficher le texte du personnage , ou la boutique 
		//canvas->SetVisibilityStatus(false);
	}
}
