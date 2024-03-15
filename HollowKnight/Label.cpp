#include "Label.h"

Label::Label(const TextData& _data, const AligmentText& _aligment, const WidgetType& _type) 
			: TextWidget(_data, _type)
{
	SetAlignement(_aligment);
}