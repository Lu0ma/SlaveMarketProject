#include "Item.h"

ItemWidget::ItemWidget(const ShapeData& _data) : ShapeWidget(_data), IManagable(_data.path)
{

}