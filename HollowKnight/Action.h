#pragma once
#include "IManagable.h"
#include "Macro.h"

typedef Event::EventType ActionType;

struct InputData
{
	ActionType type;
	int key;
};

struct ActionData
{
	string name;
	vector<InputData> keys;
	function<void()> callback;

	ActionData()
	{
		name = "Unknown";
		keys = vector<InputData>();
		callback = function<void()>();
	}

	template <class Class, typename RType = void, typename... Args>
	ActionData(const string& _name, Class* _owner, RType(Class::* _callback)(Args...),
			   const InputData& _primaryKey, const InputData& _secondaryKey = InputData(), Args... _args)
	{
		name = _name;
		callback = [_owner, _callback, _args...]() {
			return (_owner->*_callback)(_args...);
		};
		//callback = bind(_callback, _owner, _args);
		keys.push_back(_primaryKey);
		keys.push_back(_secondaryKey);
	}
	ActionData(const string& _name, const function<void()>& _callback,
		const InputData& _primaryKey, const InputData& _secondaryKey = InputData())
	{
		name = _name;
		callback = _callback;
		keys.push_back(_primaryKey);
		keys.push_back(_secondaryKey);
	}

	bool operator !() const
	{
		return name == "Unknown";
	}
};

struct Action : public IManagable<string>
{
	ActionData data;
	string actionMap;

	Action(const ActionData& _data, const string& _actionMap) : IManagable(_data.name)
	{
		if (!_data)
		{
			toRemove = true;
		}

		else
		{
			data = _data;
			actionMap = _actionMap;
		}

		Register();
	}

private:
	virtual void Register() override;

public:
	void Execute();
};