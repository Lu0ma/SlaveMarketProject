#include "Label.h"

Label::Label(const TextData& _data, const AligmentText& _aligment) : TextWidget(_data)
{
	SetAlignement(_aligment);
}