#include "Inventory.h"
#include "Button.h"
#include "Game.h"
#include "TextureManager.h"
#include "HUD.h"
#include"Macro.h"

#define PATH_INVENTORY "UIs/Inventory/Inventory.png"
#define PATH_CELL "UIs/Inventory/Cell.png"
#define PATH_INVENTORY_POINTER "UIs/Inventory/Pointer.png"
#define PATH_SEPARATOR "UIs/Inventory/Separator.png"

#define PATH_CORE "UIs/Inventory/Core.png"
#define PATH_GEO "UIs/Inventory/Geo.png"
#define PATH_SKILL_SLOT "UIs/Inventory/Skills/SkillSlot.png"

Inventory::Inventory() : Menu("Inventory", nullptr)
{
	gridSize = Vector2i(4, 5);
	cellSize = Vector2f(80.0f, 80.0f);

	buttons = vector<Button*>();
	stackSize = 5;

	descriptionTitle = nullptr;
	descriptionText = nullptr;

	maskCount = 0;
	maskWidget = nullptr;

	vesselCount = 0;
	vesselWidget = nullptr;

	mirrorLevel = 0;
	mirrorWidget = nullptr;

	coreWidget = nullptr;

	isVengefulActive = false;
	vengefulWidget = nullptr;

	isSlamActive = false;
	slamWidget = nullptr;

	isShriekActive = false;
	shriekWidget = nullptr;

	swordLevel = 0;
	swordWidget = nullptr;

	isWhirlwindUnlocked = false;
	whirlwindWidget = nullptr;

	isUppercutUnlocked = false;
	uppercutWidget = nullptr;

	isDashActive = false;
	dashWidget = nullptr;
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
	Menu::Init();

	windowSize = Game::GetWindowSize();
	halfSize = windowSize / 2.0f;
	gridSizeX = gridSize.x * cellSize.x;
	gridSizeY = gridSize.y * cellSize.y;

	Background();
	Grid();
	Equippements();
	Description();
	Separator();
}


void Inventory::UpdateMaskCount(const int _factor)
{
	if (!maskWidget) return;

	maskCount += _factor;
	maskCount %= 5; // TODO remove

	const string& _path = ComputeHealthMaskPath();
	TextureManager::GetInstance().Load(maskWidget->GetObject(), _path);
}

void Inventory::Background()
{
	ShapeWidget* _background = new ShapeWidget(ShapeData(halfSize, windowSize, PATH_INVENTORY));
	canvas->AddWidget(_background);
}

void Inventory::UpdateVesselCount(const int _factor)
{
	if (!vesselWidget) return;

	vesselCount += _factor;
	vesselCount %= 4; // TODO remove

	const string& _path = ComputeVesselPath();
	TextureManager::GetInstance().Load(vesselWidget->GetObject(), _path);
}

void Inventory::UpdateMirrorLevel(const int _factor)
{
	if (!mirrorWidget) return;

	mirrorLevel += _factor;
	mirrorLevel %= 4; // TODO remove

	const string& _path = ComputeMirrorPath();
	TextureManager::GetInstance().Load(mirrorWidget->GetObject(), _path);
}

void Inventory::UpdateSwordLevel(const int _factor)
{
	if (!swordWidget) return;

	swordLevel += _factor;
	swordLevel %= 5; // TODO remove

	const string& _path = ComputeSwordPath();
	TextureManager::GetInstance().Load(swordWidget->GetObject(), _path);
}

void Inventory::Grid()
{
	const float _borderSpacingX = windowSize.x * 5.0f / 100.0f;
	const float _gapX = windowSize.x * 5.0f / 100.0f;
	const float gridSizeX = gridSize.x * cellSize.x;
	const float gridSizeY = gridSize.y * cellSize.y;
	const Vector2f& _gridSize = Vector2f(gridSizeX - cellSize.x, gridSizeY - cellSize.y);
	const Vector2f& _gridPos = halfSize - _gridSize / 2.0f;

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
					if (ItemWidget* _itemWidget = dynamic_cast<ItemWidget*>(_hoveredButton->GetForeground()))
					{
						ShapeObject* _object = _itemWidget->GetObject();
						pointerLeft->SetShapePosition(_object->GetShapePosition());

						descriptionTitle->SetString(_itemWidget->GetTitle());
						descriptionText->SetString(_itemWidget->GetText());
					}
				}
			};

			buttons.push_back(_button);
			canvas->AddWidget(_button);
		}
	}

	pointerLeft = new ShapeWidget(ShapeData(_gridPos, cellSize, PATH_INVENTORY_POINTER));
	pointerLeft->SetVisible(false);
	pointerRight->SetVisible(false);
	canvas->AddWidget(pointerLeft);
}

void Inventory::Equippements()
{
	// HealthMask
	const Vector2f& _healthMaskPos = Vector2f(150.0f, 180.0f);
	const Vector2f& _healthMaskSize = Vector2f(150.0f, 200.0f);
	maskWidget = new ShapeWidget(ShapeData(_healthMaskPos, _healthMaskSize, ComputeHealthMaskPath()));
	canvas->AddWidget(maskWidget);

	// Vessel
	const Vector2f& _vesselPos = Vector2f(250.0f, 150.0f);
	const Vector2f& _vesselSize = Vector2f(70.0f, 70.0f);
	vesselWidget = new ShapeWidget(ShapeData(_vesselPos, _vesselSize, ComputeVesselPath()));
	canvas->AddWidget(vesselWidget);

	// Mirror
	const Vector2f& _mirrorPos = Vector2f(330.0f, 180.0f);
	const Vector2f& _mirrorSize = Vector2f(90.0f, 130.0f);
	mirrorWidget = new ShapeWidget(ShapeData(_mirrorPos, _mirrorSize, ComputeMirrorPath()));
	canvas->AddWidget(mirrorWidget);

	// Sword
	const Vector2f& _swordPos = Vector2f(150.0f, 450.0f);
	const Vector2f& _swordSize = Vector2f(70.0f, 300.0f);
	swordWidget = new ShapeWidget(ShapeData(_swordPos, _swordSize, ComputeSwordPath()));
	canvas->AddWidget(swordWidget);

	// Core
	const Vector2f& _corePos = Vector2f(300.0f, 350.0f);
	const Vector2f& _coreSize = Vector2f(100.0f, 100.0f);
	coreWidget = new ShapeWidget(ShapeData(_corePos, _coreSize, PATH_CORE));
	canvas->AddWidget(coreWidget);

	// Vengeful
	const Vector2f& _vengefulPos = Vector2f(260.0f, 300.0f);
	const Vector2f& _vengefulSize = Vector2f(45.0f, 40.0f);
	vengefulWidget = new ShapeWidget(ShapeData(_vengefulPos, _vengefulSize, ComputeVengefulPath()));
	canvas->AddWidget(vengefulWidget);

	// Slam
	const Vector2f& _slamPos = Vector2f(340.0f, 300.0f);
	const Vector2f& _slamSize = Vector2f(40.0f, 40.0f);
	slamWidget = new ShapeWidget(ShapeData(_slamPos, _slamSize, ComputeSlamPath()));
	canvas->AddWidget(slamWidget);

	// Shriek
	const Vector2f& _shriekPos = Vector2f(300.0f, 415.0f);
	const Vector2f& _shriekSize = Vector2f(40.0f, 40.0f);
	shriekWidget = new ShapeWidget(ShapeData(_shriekPos, _shriekSize, ComputeShriekPath()));
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
}

void Inventory::Description()
{
#pragma region Description

	const float _borderSpacingX = windowSize.x * 2.0f / 100.0f;
	const float _gapX = windowSize.x * 5.0f / 100.0f;
	const Vector2f& _gridSize = Vector2f(gridSizeX - cellSize.x, gridSizeY - cellSize.y);
	const Vector2f& _gridPos = halfSize - _gridSize / 2.0f;

	const float _equipmentSizeX = _gridPos.x - _borderSpacingX - _gapX * 2.0f - cellSize.x / 2.0f;
	const Vector2f& _equipmentSize = Vector2f(_equipmentSizeX, gridSizeY);

	const float _equipmentPosX = _borderSpacingX + _gapX + _equipmentSizeX / 2.0f;
	const float _equipmentPosY = _gridPos.y - cellSize.y / 2.0f + gridSizeY / 2.0f;
	const Vector2f& _equipmentPos = Vector2f(_equipmentPosX, _equipmentPosY);

	const float _endGridPosX = _gridPos.x + gridSizeX - cellSize.x / 2.0f;

	const float _descriptionSizeX = windowSize.x - _borderSpacingX - _endGridPosX - _gapX * 2.0f;
	const Vector2f& _descriptionSize = Vector2f(_descriptionSizeX, gridSizeY);
	const float _descriptionPosX = _endGridPosX + _gapX + _descriptionSizeX / 2.0f;
	const float _descriptionPosY = _gridPos.y - cellSize.y / 2.0f + gridSizeY / 2.0f;
	const Vector2f& _descriptionPos = Vector2f(_descriptionPosX, _descriptionPosY);
	//ShapeWidget* _description = new ShapeWidget(ShapeData(_descriptionPos, _descriptionSize, ""));
	//canvas->AddWidget(_description);

#pragma region Title

	const float _descriptionTitlePosX = _descriptionPos.x;
	const float _descriptionTitlePosY = _descriptionPos.y - gridSizeY / 2.0f;
	const Vector2f& _descriptionTitlePos = Vector2f(_descriptionTitlePosX, _descriptionTitlePosY);
	descriptionTitle = new Label(TextData("Shade Cloak", _descriptionTitlePos, FONT, 26));
	canvas->AddWidget(descriptionTitle);

#pragma endregion

#pragma region Text

	const float _textSpacingX = _descriptionSizeX * 5.0f / 100.0f;
	const float _textSpacingY = gridSizeY * 25.0f / 100.0f;
	const float _descriptionTextPosX = _descriptionPos.x - _descriptionSizeX / 2.0f + _textSpacingX;
	const float _descriptionTextPosY = _descriptionTitlePosY + _textSpacingY;
	const Vector2f& _descriptionLabelPos = Vector2f(_descriptionTextPosX, _descriptionTextPosY);
	descriptionText = new Label(TextData("coucou\nc'est moi", _descriptionLabelPos, FONT), AT_LEFT);
	canvas->AddWidget(descriptionText);

#pragma endregion
}

void Inventory::Separator()
{
	const float _borderSpacingX = windowSize.x * 5.0f / 100.0f;
	const float _gapX = windowSize.x * 5.0f / 100.0f;
	const Vector2f& _gridSize = Vector2f(gridSizeX - cellSize.x, gridSizeY - cellSize.y);
	const Vector2f& _gridPos = halfSize - _gridSize / 2.0f;

	const float _equipmentSizeX = _gridPos.x - _borderSpacingX - _gapX * 2.0f - cellSize.x / 2.0f;
	const Vector2f& _equipmentSize = Vector2f(_equipmentSizeX, gridSizeY);

	const float _equipmentPosX = _borderSpacingX + _gapX + _equipmentSizeX / 2.0f;
	const float _equipmentPosY = _gridPos.y - cellSize.y / 2.0f + gridSizeY / 2.0f;
	const Vector2f& _equipmentPos = Vector2f(_equipmentPosX, _equipmentPosY);

	const float _endGridPosX = _gridPos.x + gridSizeX - cellSize.x / 2.0f;

	const float _descriptionSizeX = windowSize.x - _borderSpacingX - _endGridPosX - _gapX * 2.0f;
	const Vector2f& _descriptionSize = Vector2f(_descriptionSizeX, gridSizeY);
	const float _descriptionPosX = _endGridPosX + _gapX + _descriptionSizeX / 2.0f;
	const float _descriptionPosY = _gridPos.y - cellSize.y / 2.0f + gridSizeY / 2.0f;
	const Vector2f& _descriptionPos = Vector2f(_descriptionPosX, _descriptionPosY);

	const Vector2f& _separatorSize = Vector2f(_gapX - 5.0f, gridSizeY);

	const float _separatorPosX1 = _gridPos.x - _separatorSize.x * 1.25f;
	const Vector2f& _separatorPos1 = Vector2f(_separatorPosX1, halfSize.y);
	ShapeWidget* _separator1 = new ShapeWidget(ShapeData(_separatorPos1, _separatorSize, PATH_SEPARATOR));
	canvas->AddWidget(_separator1);

	const float _separatorPosX2 = _descriptionPosX - _descriptionSizeX / 2.0f - _separatorSize.x / 2.0f;
	const Vector2f& _separatorPos2 = Vector2f(_separatorPosX2, halfSize.y);
	ShapeWidget* _separator2 = new ShapeWidget(ShapeData(_separatorPos2, _separatorSize, PATH_SEPARATOR));
	canvas->AddWidget(_separator2);
}

void Inventory::SetVengefulStatus(const bool _status)
{
	isVengefulActive = !isVengefulActive; //TODO remove
	//isSlamActive = _status;

	const string& _path = ComputeVengefulPath();
	TextureManager::GetInstance().Load(vengefulWidget->GetObject(), _path);
}

void Inventory::SetSlamStatus(const bool _status)
{
	isSlamActive = !isSlamActive; //TODO remove
	//isSlamActive = _status;

	const string& _path = ComputeSlamPath();
	TextureManager::GetInstance().Load(slamWidget->GetObject(), _path);
}

void Inventory::SetShriekStatus(const bool _status)
{
	isShriekActive = !isShriekActive; //TODO remove
	//isSlamActive = _status;

	const string& _path = ComputeShriekPath();
	TextureManager::GetInstance().Load(shriekWidget->GetObject(), _path);
}

void Inventory::AddItem(const int _count, const ItemData& _data)
{
	if (_count <= 0) return;

	if (_data.type == IT_HEALTH)
	{
		UpdateMaskCount(_count);
	}

	else if (_data.type == IT_VESSEL)
	{
		UpdateVesselCount(_count);
	}
	
	else if (_data.type == IT_ITEM)
	{
		if (Item* _item = FindItemData(_data.path))
		{
			pointerLeft->SetVisible(true);
			_item->UpdateCount(1);
			AddItem(_count - 1, _data);
			return;
		}

		CreateItemData(_data);
		AddItem(_count - 1, _data);
	}
	else if (_data.type == IT_GEOS)
	{
		int _winningGains = Random<int>(100, 1);
		Game::GetPlayer()->GetStats()->UpdateGeos(_winningGains);
	}
}

void Inventory::CreateItemData(const ItemData& _data)
{
	Button* _button = GetFirstAvailableButton();
	if (!_button) return;

	ShapeObject* _object = _button->GetObject();
	pointerLeft->SetShapePosition(_object->GetShapePosition());
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