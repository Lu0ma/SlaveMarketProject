#include "Inventory.h"
#include "Button.h"
#include "Game.h"
#include "TextureManager.h"
#include "HUD.h"

#define PATH_BACKGROUND "UIs/Inventory.png"
#define PATH_CELL "UIs/Cell.png"
#define PATH_POINTER "UIs/Pointer.png"
#define PATH_SEPARATOR "UIs/Separator.png"
#define FONT "Font.ttf"

Inventory::Inventory()
{
	canvas = nullptr;
	gridSize = Vector2i(4, 5);
	cellSize = Vector2f(80.0f, 80.0f);
	buttons = vector<Button*>();
	stackSize = 5;
}


Button* Inventory::GetFirstAvailableButton() const
{
	for (Button* _button : buttons)
	{
		if (!_button->GetForeground())
		{
			return _button;
		}
	}

	return nullptr;
}

Item* Inventory::FindItemData(const string& _path)
{
	for (Item* _item : GetAllValues())
	{
		if (_item->GetPath() == _path && _item->GetCount() < stackSize)
		{
			return _item;
		}
	}

	return nullptr;
}


void Inventory::Init()
{
	canvas = new Canvas("PlayerInventory", FloatRect(0, 0, 1, 1));
	canvas->SetVisibilityStatus(false);

	const Vector2f& _windowSize = Game::GetInstance().GetWindowSize();
	const Vector2f& _halfSize = _windowSize / 2.0f;
	const float _borderSpacingX = _windowSize.x * 5.0f / 100.0f;
	const float _gapX = _windowSize.x * 5.0f / 100.0f;

	#pragma region Background

	ShapeWidget* _background = new ShapeWidget(ShapeData(_halfSize, _windowSize, PATH_BACKGROUND));
	canvas->AddWidget(_background);
	
	#pragma endregion

	#pragma region Grid

	const float _gridSizeX = gridSize.x * cellSize.x;
	const float _gridSizeY = gridSize.y * cellSize.y;
	const Vector2f& _gridSize = Vector2f(_gridSizeX - cellSize.x, _gridSizeY - cellSize.y);
	const Vector2f& _gridPos = _halfSize - _gridSize / 2.0f;

	for (int _rowIndex = 0; _rowIndex < gridSize.y; _rowIndex++)
	{
		for (int _columnIndex = 0; _columnIndex < gridSize.x; _columnIndex++)
		{
			const float _posX = _gridPos.x + _columnIndex * cellSize.x;
			const float _posY = _gridPos.y + _rowIndex * cellSize.y;
			const Vector2f& _buttonPos = Vector2f(_posX, _posY);

			Button* _button = new Button(ShapeData(_buttonPos, cellSize, PATH_CELL));
			_button->GetDrawable()->setFillColor(Color::Transparent);

			_button->GetData().hoveredCallback = [&]()
			{ 
				// afficher le pointer au dessus du boutton
				Button* _hoveredButton = dynamic_cast<Button*>(HUD::GetInstance().GetHoveredButton(buttons));
				const Vector2f& _position = _hoveredButton->GetDrawable()->getPosition();
				pointer->SetShapePosition(_position);

				//_button->ToggleVisibilityWidget();
			};

			buttons.push_back(_button);
			canvas->AddWidget(_button);
		}
	}
	
	pointer = new ShapeWidget(ShapeData(_gridPos, cellSize, PATH_POINTER));
	canvas->AddWidget(pointer);

	#pragma endregion

	#pragma region Equipment

	const float _equipmentSizeX = _gridPos.x - _borderSpacingX - _gapX * 2.0f - cellSize.x / 2.0f;
	const Vector2f& _equipmentSize = Vector2f(_equipmentSizeX, _gridSizeY);

	const float _equipmentPosX = _borderSpacingX + _gapX + _equipmentSizeX / 2.0f;
	const float _equipmentPosY = _gridPos.y - cellSize.y / 2.0f + _gridSizeY / 2.0f;
	const Vector2f& _equipmentPos = Vector2f(_equipmentPosX, _equipmentPosY);

	/*ShapeWidget* _equipment = new ShapeWidget(ShapeData(_equipmentPos, _equipmentSize, ""));
	canvas->AddWidget(_equipment);*/

	const Vector2f& _healthMaskPos = Vector2f(_equipmentPosX, _equipmentPosY);
	const Vector2f& _healthMaskSize = Vector2f(125.0f, 200.0f);
	maskWidget = new ShapeWidget(ShapeData(_healthMaskPos, _healthMaskSize, ComputeHealthMaskPath()));
	canvas->AddWidget(maskWidget);

	#pragma endregion

	#pragma region Description

	const float _endGridPosX = _gridPos.x + _gridSizeX - cellSize.x / 2.0f;

	const float _descriptionSizeX = _windowSize.x - _borderSpacingX - _endGridPosX - _gapX * 2.0f;
	const Vector2f& _descriptionSize = Vector2f(_descriptionSizeX, _gridSizeY);
	const float _descriptionPosX = _endGridPosX + _gapX + _descriptionSizeX / 2.0f;
	const float _descriptionPosY = _gridPos.y - cellSize.y / 2.0f + _gridSizeY / 2.0f;
	const Vector2f& _descriptionPos = Vector2f(_descriptionPosX, _descriptionPosY);
	/*ShapeWidget* _description = new ShapeWidget(ShapeData(_descriptionPos, _descriptionSize, ""));
	canvas->AddWidget(_description);*/

	#pragma region Title

	const float _descriptionTitlePosX = _descriptionPos.x - _descriptionSizeX * 20.0f / 100.0f;
	const float _descriptionTitlePosY = _descriptionPos.y - _gridSizeY / 2.0f;
	const Vector2f& _descriptionTitlePos = Vector2f(_descriptionTitlePosX, _descriptionTitlePosY);
	Label* _descriptionTitle = new Label(TextData("Shade Cloak", _descriptionTitlePos, FONT, 26));
	canvas->AddWidget(_descriptionTitle);

	#pragma endregion

	#pragma region Text

	const float _textSpacingX = _descriptionSizeX * 5.0f / 100.0f;
	const float _textSpacingY = _gridSizeY * 25.0f / 100.0f;
	const float _descriptionTextPosX = _descriptionPos.x - _descriptionSizeX / 2.0f + _textSpacingX;
	const float _descriptionTextPosY = _descriptionTitlePosY + _textSpacingY;
	const Vector2f& _descriptionLabelPos = Vector2f(_descriptionTextPosX, _descriptionTextPosY);
	Label* _descriptionText = new Label(TextData("coucou\nc'est moi", _descriptionLabelPos, FONT));
	canvas->AddWidget(_descriptionText);

	#pragma endregion

	#pragma endregion

	#pragma region Separators

	const Vector2f& _separatorSize = Vector2f(_gapX - 5.0f, _gridSizeY);

	const float _separatorPosX1 = _gridPos.x - _separatorSize.x * 1.25f;
	const Vector2f& _separatorPos1 = Vector2f(_separatorPosX1, _halfSize.y);
	ShapeWidget* _separator1 = new ShapeWidget(ShapeData(_separatorPos1, _separatorSize, PATH_SEPARATOR));
	canvas->AddWidget(_separator1);

	const float _separatorPosX2 = _descriptionPosX - _descriptionSizeX / 2.0f - _separatorSize.x / 2.0f;
	const Vector2f& _separatorPos2 = Vector2f(_separatorPosX2, _halfSize.y);
	ShapeWidget* _separator2 = new ShapeWidget(ShapeData(_separatorPos2, _separatorSize, PATH_SEPARATOR));
	canvas->AddWidget(_separator2);

	#pragma endregion
}


void Inventory::UpdateMaskCount(const int _factor)
{
	if (!maskWidget) return;

	maskCount += _factor;

	maskCount %= 5;

	const string& _path = ComputeHealthMaskPath();
	Shape* _shape = maskWidget->GetDrawable();
	TextureManager::GetInstance().Load(_shape, _path);
	maskWidget->GetObject()->SetShape(_shape);
}


void Inventory::AddItem(const int _count, const string _path)
{
	if (_count <= 0) return;

	if (Item* _item = FindItemData(_path))
	{
		_item->UpdateCount(1);
		AddItem(_count - 1, _path);
		return;
	}

	CreateItemData(_path);
	AddItem(_count - 1, _path);
}

void Inventory::CreateItemData(const string& _path)
{
	Button* _button = GetFirstAvailableButton();
	if (!_button) return;

	const ShapeData& _objectData = ShapeData(_button->GetObject()->GetShapePosition(),
											 _button->GetObject()->GetShapeSize() * 60.0f / 100.0f,
											 _path);
	ItemWidget* _widget = new ItemWidget(_objectData);
	Item* _item = new Item(_widget, FONT);
	Add(_item->GetID(), _item);

	canvas->AddWidget(_widget);
	canvas->AddWidget(_item->GetCountText());
	_button->SetForeground(_widget);
}