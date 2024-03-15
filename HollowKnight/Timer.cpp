#include "Timer.h"
#include "TimerManager.h"
#include "Macro.h"

Timer::Timer(const function<void()>& _callback, const Time& _time,
	const bool _startRunning, const bool _isLoop) : IManagable(GetUniqueID())
{
	Register();

	callback = _callback;
	currentDuration = 0.0f;
	duration = static_cast<float>(_time.asMilliseconds());
	isRunning = _startRunning;
	isLoop = _isLoop;
}


void Timer::Register()
{
	TimerManager::GetInstance().Add(id, this);
}


void Timer::Update(const float _deltaTime)
{
	if (!isRunning) return;

	currentDuration += _deltaTime;
	if (currentDuration >= duration)
	{
		if (callback)
		{
			callback();
		}

		if (!isLoop)
		{
			Stop();
		}

		Reset();
	}

}

void Timer::Start()
{
	Reset();
	Resume();
}

void Timer::Resume()
{
	isRunning = true;
	Reset();
}

void Timer::Pause()
{
	isRunning = false;
}

void Timer::Reset()
{
	currentDuration = 0.0f;
}

void Timer::Stop()
{
	TimerManager::GetInstance().Remove(id);
}