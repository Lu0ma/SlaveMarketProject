#pragma once
#include "Actor.h"
#include<iostream>

using namespace std;

class Fx : public Actor
{

public:
	Fx(const string& _name, const ShapeData& _data);
};