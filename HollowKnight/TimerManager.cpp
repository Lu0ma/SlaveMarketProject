#include "TimerManager.h"

TimerManager::TimerManager()
{
	clock = Clock();
	time = 0.0f;
	lastTime = 0.0f;
	lastFrameTime = 0.0f;
	elapsedTime = 0.0f;
	timeScale = 1.0f;
	deltaTime = 0.0f;
	framesCount = 0;
	maxFrameRate = 60;
	fps = 0;
	current = 0;
	max = 0;
	isPause = false;
}


void TimerManager::UpdateTimers()
{
	for (const auto& _pair : allValues)
	{
		_pair.second->Update(deltaTime);
	}

	GarbageValues();
}


void TimerManager::Update()
{
	lastTime = time;
	time = static_cast<float>(clock.getElapsedTime().asMilliseconds());
	elapsedTime = time - lastTime;
	deltaTime = elapsedTime * timeScale;
	framesCount++;
	if (Render() && renderCallback)
	{
		renderCallback();
	}
	UpdateTimers();
}

void TimerManager::Pause(const float _duration)
{

}
