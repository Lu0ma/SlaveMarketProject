#include "Inventory.h"
#include "Button.h"
#include "Game.h"
#include "TextureManager.h"
#include "HUD.h"

#define PATH_BACKGROUND "UIs/Inventory/Inventory.png"
#define PATH_CELL "UIs/Inventory/Cell.png"
#define PATH_POINTER "UIs/Inventory/Pointer.png"
#define PATH_SEPARATOR "UIs/Inventory/Separator.png"

#define PATH_CORE "UIs/Inventory/Core.png"
#define PATH_GEO "UIs/Inventory/Geo.png"
#define PATH_SKILL_SLOT "UIs/Inventory/Skills/SkillSlot.png"

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

void Inventory::UpdateCount(ShapeWidget* _widget, int& _count, const string& _path,
	const int _max, const int _factor)
{
	_count += _factor;
	_count %= _max; // TODO remove

	UpdateTexture(_widget, ComputePath(_path, _count));
}

void Inventory::UpdateTexture(ShapeWidget* _widget, const string& _path)
{
	if (!_widget) return;

	Shape* _shape = _widget->GetDrawable();
	TextureManager::GetInstance().Load(_shape, _path);
	_widget->GetObject()->SetShape(_shape);
}


void Inventory::Init()
{
	canvas = new Canvas("PlayerInventory");
	canvas->SetVisibilityStatus(false);

	const Vector2f& _windowSize = Game::GetWindowSize();
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
				if (Button* _hoveredButton = HUD::GetInstance().GetHoveredButton(buttons))
				{
					const Vector2f& _position = _hoveredButton->GetDrawable()->getPosition();
					pointer->SetShapePosition(_position);

					if (ItemWidget* _itemWidget = dynamic_cast<ItemWidget*>(_hoveredButton->GetForeground()))
					{
						descriptionTitle->SetString(_itemWidget->GetTitle());
						descriptionText->SetString(_itemWidget->GetText());
					}
				}
			};

			buttons.push_back(_button);
			canvas->AddWidget(_button);
		}
	}
	
	#pragma region Pointer

	pointer = new ShapeWidget(ShapeData(_gridPos, cellSize, PATH_POINTER));
	canvas->AddWidget(pointer);

	#pragma endregion

	#pragma endregion

	#pragma region Equipment

	const float _equipmentSizeX = _gridPos.x - _borderSpacingX - _gapX * 2.0f - cellSize.x / 2.0f;
	const Vector2f& _equipmentSize = Vector2f(_equipmentSizeX, _gridSizeY);

	const float _equipmentPosX = _borderSpacingX + _gapX + _equipmentSizeX / 2.0f;
	const float _equipmentPosY = _gridPos.y - cellSize.y / 2.0f + _gridSizeY / 2.0f;
	const Vector2f& _equipmentPos = Vector2f(_equipmentPosX, _equipmentPosY);

	/*ShapeWidget* _equipment = new ShapeWidget(ShapeData(_equipmentPos, _equipmentSize, ""));
	canvas->AddWidget(_equipment);*/

	// HealthMask
	const Vector2f& _healthMaskPos = Vector2f(150.0f, 180.0f);
	const Vector2f& _healthMaskSize = Vector2f(150.0f, 200.0f);
	const string& _healthMaskPath = ComputePath(PATH_HEALTH_MASK, maskCount);
	maskWidget = new ShapeWidget(ShapeData(_healthMaskPos, _healthMaskSize, _healthMaskPath));
	canvas->AddWidget(maskWidget);

	// Vessel
	const Vector2f& _vesselPos = Vector2f(250.0f, 150.0f);
	const Vector2f& _vesselSize = Vector2f(70.0f, 70.0f);
	const string& _vesselPath = ComputePath(PATH_VESSEL, vesselCount);
	vesselWidget = new ShapeWidget(ShapeData(_vesselPos, _vesselSize, _vesselPath));
	canvas->AddWidget(vesselWidget);

	// Mirror
	const Vector2f& _mirrorPos = Vector2f(330.0f, 180.0f);
	const Vector2f& _mirrorSize = Vector2f(90.0f, 130.0f);
	const string& _mirrorPath = ComputePath(PATH_MIRROR, mirrorLevel);
	mirrorWidget = new ShapeWidget(ShapeData(_mirrorPos, _mirrorSize, _mirrorPath));
	canvas->AddWidget(mirrorWidget);

	// Sword
	const Vector2f& _swordPos = Vector2f(150.0f, 450.0f);
	const Vector2f& _swordSize = Vector2f(70.0f, 300.0f);
	const string& _swordLevel = ComputePath(PATH_SWORD, swordLevel);
	swordWidget = new ShapeWidget(ShapeData(_swordPos, _swordSize, _swordLevel));
	canvas->AddWidget(swordWidget);

	// Core
	const Vector2f& _corePos = Vector2f(300.0f, 350.0f);
	const Vector2f& _coreSize = Vector2f(100.0f, 100.0f);
	coreWidget = new ShapeWidget(ShapeData(_corePos, _coreSize, PATH_CORE));
	canvas->AddWidget(coreWidget);

	// Vengeful
	const Vector2f& _vengefulPos = Vector2f(260.0f, 300.0f);
	const Vector2f& _vengefulSize = Vector2f(45.0f, 40.0f);
	const string& _vengefulPath = ComputePath(PATH_VENGEFUL, isVengefulActive);
	vengefulWidget = new ShapeWidget(ShapeData(_vengefulPos, _vengefulSize, _vengefulPath));
	canvas->AddWidget(vengefulWidget);

	// Slam
	const Vector2f& _slamPos = Vector2f(340.0f, 300.0f);
	const Vector2f& _slamSize = Vector2f(40.0f, 40.0f);
	const string& _slamPath = ComputePath(PATH_SLAM, isSlamActive);
	slamWidget = new ShapeWidget(ShapeData(_slamPos, _slamSize, _slamPath));
	canvas->AddWidget(slamWidget);

	// Shriek
	const Vector2f& _shriekPos = Vector2f(300.0f, 415.0f);
	const Vector2f& _shriekSize = Vector2f(40.0f, 40.0f);
	const string& _shriekPath = ComputePath(PATH_SHRIEK, isShriekActive);
	shriekWidget = new ShapeWidget(ShapeData(_shriekPos, _shriekSize, _shriekPath));
	canvas->AddWidget(shriekWidget);

	// Whirlwind
	const Vector2f& _whirlwindPos = Vector2f(235.0f, 500.0f);
	const Vector2f& _whirlwindSize = Vector2f(80.0f, 80.0f);
	whirlwindWidget = new ShapeWidget(ShapeData(_whirlwindPos, _whirlwindSize, PATH_SKILL_SLOT));
	canvas->AddWidget(whirlwindWidget);

	// Uppercut
	const Vector2f& _uppercutPos = Vector2f(305.0f, 500.0f);
	const Vector2f& _uppercutSize = Vector2f(80.0f, 80.0f);
	uppercutWidget = new ShapeWidget(ShapeData(_uppercutPos, _uppercutSize, PATH_SKILL_SLOT));
	canvas->AddWidget(uppercutWidget);

	// Dash
	const Vector2f& _dashPos = Vector2f(375.0f, 500.0f);
	const Vector2f& _dashSize = Vector2f(80.0f, 80.0f);
	dashWidget = new ShapeWidget(ShapeData(_dashPos, _dashSize, PATH_SKILL_SLOT));
	canvas->AddWidget(dashWidget);

	// Geo
	const Vector2f& _geoPos = Vector2f(230.0f, 590.0f);
	const Vector2f& _geoSize = Vector2f(40.0f, 40.0f);
	ShapeWidget* _geoWidget = new ShapeWidget(ShapeData(_geoPos, _geoSize, PATH_GEO));
	canvas->AddWidget(_geoWidget);

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
	descriptionTitle = new Label(TextData("Shade Cloak", _descriptionTitlePos, FONT, 26));
	canvas->AddWidget(descriptionTitle);

	#pragma endregion

	#pragma region Text

	const float _textSpacingX = _descriptionSizeX * 5.0f / 100.0f;
	const float _textSpacingY = _gridSizeY * 25.0f / 100.0f;
	const float _descriptionTextPosX = _descriptionPos.x - _descriptionSizeX / 2.0f + _textSpacingX;
	const float _descriptionTextPosY = _descriptionTitlePosY + _textSpacingY;
	const Vector2f& _descriptionLabelPos = Vector2f(_descriptionTextPosX, _descriptionTextPosY);
	descriptionText = new Label(TextData("coucou\nc'est moi", _descriptionLabelPos, FONT));
	canvas->AddWidget(descriptionText);

	#pragma endregion

	#pragma endregion

	#pragma region Separators

	const Vector2f& _separatorSize = Vector2f(_gapX - 5.0f, _gridSizeY);

	const float _separatorPosX1 = _gridPos.x - _separatorSize.x * 1.25f;
	const Vector2f& _separatorPos1 = Vector2f(_separatorPosX1, _halfSize.y);
	ShapeWidget* _separator1 = new ShapeWidget(ShapeData(_separatorPos1, _separatorSize, PATH_SEPARATOR));
	canvas->AddWidget(_separator1);

	const float _separatorPosX2 = _descriptionPosX - _descriptionSizeX / 2.0f - _separatorSize.x / 2.0f;
	const Vector2f& _separatorPos2 = Vector2f(_separatorPosX2, _gridSizeY);
	ShapeWidget* _separator2 = new ShapeWidget(ShapeData(_separatorPos2, _separatorSize, PATH_SEPARATOR));
	canvas->AddWidget(_separator2);

	#pragma endregion
}

void Inventory::UpdateMaskCount(const int _factor)
{
	UpdateCount(maskWidget, maskCount, PATH_HEALTH_MASK, 5, _factor);
}

void Inventory::UpdateVesselCount(const int _factor)
{
	UpdateCount(vesselWidget, vesselCount, PATH_VESSEL, 4, _factor);
}

void Inventory::UpdateMirrorLevel(const int _factor)
{
	UpdateCount(mirrorWidget, mirrorLevel, PATH_MIRROR, 4, _factor);
}

void Inventory::UpdateSwordLevel(const int _factor)
{
	UpdateCount(swordWidget, swordLevel, PATH_SWORD, 5, _factor);
}

void Inventory::SetVengefulStatus(const bool _status)
{
	isVengefulActive = !isVengefulActive; //TODO remove
	//isSlamActive = _status;
	UpdateTexture(vengefulWidget, ComputePath(PATH_VENGEFUL, isVengefulActive));
}

void Inventory::SetSlamStatus(const bool _status)
{
	isSlamActive = !isSlamActive; //TODO remove
	//isSlamActive = _status;
	UpdateTexture(slamWidget, ComputePath(PATH_SLAM, isSlamActive));
}

void Inventory::SetShriekStatus(const bool _status)
{
	isShriekActive = !isShriekActive; //TODO remove
	//isSlamActive = _status;
	UpdateTexture(shriekWidget, ComputePath(PATH_SHRIEK, isShriekActive));
}


void Inventory::AddItem(const int _count, const ItemData& _data)
{
	if (_count <= 0) return;

	if (Item* _item = FindItemData(_data.path))
	{
		_item->UpdateCount(1);
		AddItem(_count - 1, _data);
		return;
	}

	CreateItemData(_data);
	AddItem(_count - 1, _data);
}

void Inventory::CreateItemData(const ItemData& _data)
{
	Button* _button = GetFirstAvailableButton();
	if (!_button) return;

	const ShapeData& _objectData = ShapeData(_button->GetObject()->GetShapePosition(),
											 _button->GetObject()->GetShapeSize() * 70.0f / 100.0f,
											 _data.path);
	ItemWidget* _widget = new ItemWidget(_objectData, _data.title, _data.text);
	Item* _item = new Item(_widget, FONT);
	Add(_item->GetID(), _item);

	canvas->AddWidget(_widget);
	canvas->AddWidget(_item->GetCountText());
	_button->SetForeground(_widget);
}