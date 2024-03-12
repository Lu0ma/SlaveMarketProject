#pragma once
#include "ShapeWidget.h"

class ScrollBar : public ShapeWidget
{
	int baseIndex;
	int scrollAmount;
	ShapeWidget* bar;
public:
	void SetScrollAmount(const int _scrollAmount) { scrollAmount = _scrollAmount; }

	ShapeWidget* GetBar() { return bar; }
public:
	ScrollBar(const ShapeData& _data, const int _scrollAmount);

public:
	void UpdateScroll(const Event& _event);
	void UpScroll();
	void DownScroll();
	void ComputeClickOnBar(const Vector2f& _position);
	void ComputeByIndex(const float _destination);
};

