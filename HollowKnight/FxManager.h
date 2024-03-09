#pragma once
#include "Singleton.h"
#include "IManager.h"
#include"FxData.h"


class FxManager : public Singleton<FxManager>, public IManager<string, FxData>
{
	int index;
public:
	FxManager();

public:
	void Run(const string& _runningAnimation);
};

