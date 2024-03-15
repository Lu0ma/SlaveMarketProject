#include "Particule.h"
#include "Game.h"

#define PATH_PARTICULE "Levels/FX/Particule.png"

Particule::Particule() : Actor(STRING_ID("Particule"), ShapeData(Game::GetPlayer()->GetShapePosition() + GetRandomDirection(), Vector2f(5.0f, 5.0f), PATH_PARTICULE), CT_NONE)
{
	bool _isSpawning = true;
	
	color = new Color(255, 255, 255, 0);


	//FadeIn
	timerIn = new Timer([&]() {
		if (color->a >= 255)
		{
			
			timerIn->Stop();
			timerOut->Start();
		}
		else
		{
			color->a++;
			GetDrawable()->setFillColor(*color);
		}
	}, milliseconds((Int32)1.0f), true, true);

	//FadeOut
	timerOut = new Timer([&]() {
		if (color->a <= 0)
		{
			timerOut->Stop();
			Destroy();
		}
		else
		{
			color->a--;
			GetDrawable()->setFillColor(*color);
		}
	}, milliseconds((Int32)1.0f), false, true);
}

Vector2f Particule::GetRandomDirection()
{
	const float _randomX = Random(Game::GetPlayer()->GetShapeSize().x * 2.0f, Game::GetPlayer()->GetShapeSize().x / 2.0f);
	const float _randomY = Random(Game::GetPlayer()->GetShapeSize().y * 2.0f, Game::GetPlayer()->GetShapeSize().y / 2.0f);

	const float _random = Random((float)360, (float)0);
	const float _valueX = cos(_random);
	const float _valueY = sin(_random);

	return Vector2f(_valueX * _randomX, _valueY * _randomY);
}
