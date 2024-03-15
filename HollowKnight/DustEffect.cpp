#include "DustEffect.h"
#include "Macro.h"
#include "Game.h"

DustEffect::DustEffect()
{
	spawnDust = nullptr;
	Init();

}

void DustEffect::Init()
{
	function<void()> _callback = [&]() 
		{
			for (int i = 0; i < Random(10,5); i++)
			{
				new Particule();
			}
		};
	spawnDust = new Timer(_callback, seconds(1.0f), true, true);
}
