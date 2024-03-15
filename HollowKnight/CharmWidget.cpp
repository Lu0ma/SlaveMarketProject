#include "CharmWidget.h"

CharmWidget::CharmWidget(const ShapeData& _data, const string& _title, const string& _text,
						 Button* _owner) : ItemWidget(_data, _title, _text)
{
	owner = _owner;
}

void CharmWidget::ResetPosition()
{
	owner->SetForeground(this);
	SetShapePosition(owner->GetShapePosition());
}