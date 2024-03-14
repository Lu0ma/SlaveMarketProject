#pragma once
#include "IManagable.h"
#include <SFML/Graphics.hpp>
#include <functional>

using namespace std;
using namespace sf;

class Timer : public IManagable<int>
{
	function<void()> callback;
	float currentDuration;
	float duration;
	bool isRunning;
	bool isLoop;

	bool isPause;
public:
	void AddDuration(const float _duration)
	{
		duration += _duration;
	}
	float GetCurrentDuration() const
	{
		return currentDuration;
	}
	bool IsRunning() const
	{
		return isRunning;
	}

public:
	//template <class Class, typename... Args>
	//Timer(Class* _owner, void (Class::* _callback)(Args...), const Time& _time,
	//	const bool _startRunning = true, const bool _isLoop = false, const Args&... _args)
	//	: IManagable(GetUniqueID())
	//{
	//	Register();
	//	callback = [_owner, _callback, _args...]()
	//	{
	//		(_owner->*_callback)(_args...);
	//	};
	//	currentDuration = 0.0f;
	//	duration = static_cast<float>(_time.asMilliseconds());
	//	isRunning = _startRunning;
	//	isLoop = _isLoop;
	//	//const function<void()>& _callbackWithArgs = bind(_callback, _owner, _args...);
	//}

	Timer(const function<void()>& _callback, const Time& _time,
		const bool _startRunning = true, const bool _isLoop = false);

private:
	virtual void Register() override;

public:
	void Update(const float _deltaTime);
	void Start();
	void Resume();
	void Pause();
	void Reset();
	void Stop();
};