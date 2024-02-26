#pragma once
#include "ShapeWidget.h"
#include "Canvas.h"

enum ProgressType
{
	PT_CENTER,
	PT_LEFT,
	PT_TOP,
	PT_RIGHT,
	PT_BOTTOM
};

class ProgressBar : public ShapeWidget
{
	ProgressType type;
	ShapeWidget* foreground;
	float currentValue;
	float maxValue;

public:
	virtual void SetShapePosition(const Vector2f& _position) override
	{
		ShapeWidget::SetShapePosition(_position);
		foreground->SetShapePosition(_position - Vector2f(GetDrawable()->getGlobalBounds().getSize().x / 2.0f, 0.0f));
	}
	void SetValue(const float _newValue)
	{
		currentValue = _newValue > maxValue ? maxValue : _newValue < 0 ? 0 : _newValue;
		Update();
	}
	void ChangeValue(const float _byAmount)
	{
		const float _newValue = currentValue + _byAmount;
		currentValue = _newValue > maxValue ? maxValue : _newValue < 0 ? 0 : _newValue;
		Update();
	}
	void ResetValue()
	{
		currentValue = maxValue;
		Update();
	}
	void ChangeMaxValue(const float _factor)
	{
		maxValue += _factor;
		Update();
	}
	float GetCurrentValue() const
	{
		return currentValue;
	}
	float GetMaxValue() const
	{
		return maxValue;
	}

public:
	ProgressBar(const ShapeData& _data, Canvas* _canvas, const string& _path,
				const ProgressType& _type, const float _maxValue = 100.0f);
	~ProgressBar();

private:
	void Update();
	void UpdateOriginAndPosition(const Vector2f& _size);
	IntRect MakeRect(const float _percent);
};