#pragma once
#include "IManager.h"
#include "IManagable.h"
#include "Action.h"

struct ActionMap : public IManager<string, Action>, public IManagable<string>
{
	bool isActive;
	vector<Action*> actions;

public:
	ActionMap(const string& _name, const vector<ActionData>& _actionsData = vector<ActionData>(),
			  const bool _isActive = true);

private:
	virtual void Register() override;

public:
	void Update(const Event& _event);
};