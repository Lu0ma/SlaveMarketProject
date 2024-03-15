#include "Game.h"

#include "TimerManager.h"
#include "ProgressBar.h"
#include "Timer.h"

using namespace std;

#define OLVIER_TRISTE "Oops/TRISTE.png"
#define OLVIER_CONTENT "Oops/CONTENT.png"

int main()
{
	locale::global(locale(""));
	srand(static_cast<unsigned>(time(nullptr)));
    Game _game;
    _game.Launch();

   /* #pragma region EasterEgg

   sf::RenderWindow window(sf::VideoMode(1200, 800), "Olivier....", Style::Titlebar);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    ProgressBar* _olivier = new ProgressBar(ShapeData(Vector2f(window.getSize()) / 2.0f, Vector2f(600.0f, 600.0f), OLVIER_TRISTE), OLVIER_CONTENT, PT_CENTER);
    float _factor = -2.0f;
    new Timer([&]() {
        _factor *= -1.0f;
        const int _typeIndex = rand() % PT_COUNT;
        _olivier->SetType((ProgressType)_typeIndex);
        }, seconds(6.0f), true, true);
    new Timer([&]() { _olivier->ChangeValue(_factor);  }, seconds(0.1f), true, true);

    while (window.isOpen()) {

        TimerManager::GetInstance().Update();

        sf::Event event;
        while (window.pollEvent(event))
            if (sf::Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();

        window.clear();
        window.draw(*_olivier->GetDrawable());
        window.draw(*_olivier->GetForeground()->GetDrawable());
        window.display();
    }

    #pragma endregion*/

	return 0;
}
