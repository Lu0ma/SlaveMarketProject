#include "CharmsMenu.h"
#include "Game.h"
#include "HUD.h"

#define PATH_CHARMS "UIs/Charms/Charms.png"
#define PATH_SKILL_SLOT "UIs/Charms/SkillSlot.png"
#define PATH_NOTCH_UNUSED "UIs/Charms/Notch_0.png"
#define PATH_NOTCH_USED "UIs/Charms/Notch_1.png"
#define PATH_SELECTED_CHARMS "UIs/Charms/Select_Charms.png"
#define PATH_SEPARATOR "UIs/Inventory/Separator.png"
#define PATH_CHARM_POINTER "UIs/Charms/Pointer.png"
#define CHARMS "UIs/Charms/AllCharms/Charms_"

CharmsMenu::CharmsMenu() : Menu("CharmsMenu", nullptr)
{
	gridSize = Vector2i();
	slotSize = Vector2f();
	notchSize = Vector2f();
	charmsSelectSize = Vector2f();
	cellSize = Vector2f();
	gridPos = Vector2f();
	windowSize = Vector2f();
	halfSize = Vector2f();
	notches = 0;
	charmsCount = 0;
	slotsCharms = vector<Button*>();
	slotsEquippedCharms = vector<Button*>();
	descriptionItem = nullptr;
	titleItem = nullptr;
}


void CharmsMenu::Init()
{
	Menu::Init();
	canvas->SetVisibilityStatus(false);

	gridSize = Vector2i(9, 4);
	slotSize = Vector2f(30.0f, 30.0f);
	notchSize = Vector2f(20.0f, 20.0f);
	charmsSelectSize = Vector2f(30.0f, 30.0f);
	notches = 11;
	charmsCount = 6;
	windowSize = Game::GetWindowSize();
	gridPos = Vector2f(windowSize.x / 12.0f, windowSize.y / 8.0f);
	halfSize = windowSize / 2.0f;

	_items = vector<CharmsItem>();
	Background();
	Separator();
	SelectedCharms();
	SlotCharms();
	Notches();
	NotchesText();
	EquippedText();
	Title();
	Description();
}

void CharmsMenu::Background()
{
	ShapeWidget* _background = new ShapeWidget(ShapeData(halfSize, windowSize, PATH_CHARMS));
	canvas->AddWidget(_background);
}

void CharmsMenu::Separator()
{
	const float _spacingX = gridSize.x * slotSize.x;
	const float _spacingSeparatorY = Game::GetWindowSize().y / 2.0f * 0.95f;
	ShapeWidget* _line = new ShapeWidget(ShapeData(Vector2f(gridPos.x + _spacingX, _spacingSeparatorY), Vector2f(35.0f, 589.0f), PATH_SEPARATOR));
	_line->GetDrawable()->setRotation(90.0f);
	canvas->AddWidget(_line);
}

void CharmsMenu::SelectedCharms()
{
	const float _spacingY = halfSize.y * 0.8f;

	for (int _row = 0; _row < charmsCount; _row++)
	{
		Button* _charm = new Button(ShapeData(Vector2f(gridPos.x + 35.0f + _row * (charmsSelectSize.y + 50.0f), _spacingY - halfSize.y * 0.30f), charmsSelectSize, PATH_SELECTED_CHARMS));
		_charm->GetData().hoveredCallback = [&]()
		{
			if (Button* _hoveredButton = HUD::GetInstance().GetHoveredButton(slotsEquippedCharms))
			{
				const Vector2f& _position = _hoveredButton->GetDrawable()->getPosition();
				pointerLeft->SetShapePosition(_position);
				pointerLeft->GetDrawable()->setScale(1.0f, 1.0f);
				pointerLeft->SetVisible(true);
			}
		};
		_charm->GetData().pressedCallback = [&]()
		{
			if (Button* _pressedButton = HUD::GetInstance().GetPressedButton(slotsEquippedCharms))
			{
				if (CharmWidget* _charm = dynamic_cast<CharmWidget*>(_pressedButton->GetForeground()))
				{
					_pressedButton->SetForeground(nullptr);
					_charm->ResetPosition();
				}
			}
		};
		slotsEquippedCharms.push_back(_charm);
		canvas->AddWidget(_charm);
	}
	
	pointerLeft = new ShapeWidget(ShapeData(Vector2f(gridPos.x + 35.0f, _spacingY - halfSize.y * 0.30f), Vector2f(50.0f, 50.0f), PATH_CHARM_POINTER));
	pointerLeft->SetVisible(false);
	pointerRight->SetVisible(false);
	canvas->AddWidget(pointerLeft);
}

void CharmsMenu::SlotCharms()
{
	const float _spacingY = halfSize.y * 0.8f;
	const Vector2f& _gapSlot = Vector2f(35.0f, 35.0f);

	

	_items = {
		{
			"UIs/Charms/SkillSlot.png",
			"Gathering Swarm",
			"Do you find yourself leaving a\n"
			"lot of Geo behind as you hurry\n"
			"through the caverns ?\n\n"
			"This charm will make sure that\n"
			"any loose change finds its way\n"
			"back to you."
		},

		{
			"UIs/Charms/SkillSlot.png",
			"Lantern",
			"This is a simple lantern."
		},
	};

	for (int _row = 0, _count = 0, _index = 0; _row < gridSize.y; _row++)
	{
		for (int _column = 0; _column < gridSize.x; _column++, _count++, _index++)
		{
			const float _posX = gridPos.x + _column * slotSize.x + (_row % 2 != 0 ? _gapSlot.x / 2.0f + 2 * slotSize.x / 3.0f : 0.0f) + _gapSlot.x * _column;
			const float _posY = _spacingY + gridPos.y + _row * slotSize.y + _gapSlot.y * _row;

			Button* _slot = new Button(ShapeData(Vector2f(_posX, _posY), slotSize, PATH_SKILL_SLOT));
			_count %= 2;
			_slot->GetData().hoveredCallback = [&]()
			{
				if (Button* _hoveredButton = HUD::GetInstance().GetHoveredButton(slotsCharms))
				{
					const Vector2f& _position = _hoveredButton->GetDrawable()->getPosition();
					pointerLeft->SetShapePosition(_position);
					pointerLeft->GetDrawable()->setScale(1.5f, 1.5f);

					if (ItemWidget* _itemWidget = dynamic_cast<ItemWidget*>(_hoveredButton->GetForeground()))
					{
						titleItem->SetString(_itemWidget->GetTitle());
						descriptionItem->SetString(_itemWidget->GetText());
					}
				}
			};
			_slot->GetData().pressedCallback = [&]()
			{
				if (Button* _pressedButton = HUD::GetInstance().GetPressedButton(slotsCharms))
				{
					if (ItemWidget* _itemWidget = dynamic_cast<ItemWidget*>(_pressedButton->GetForeground()))
					{
						if (Button* _equippedCharms = GetFirstAvailableEquippedSlot())
						{
							_pressedButton->SetForeground(nullptr);
							_equippedCharms->SetForeground(_itemWidget);
							_itemWidget->SetShapePosition(_equippedCharms->GetShapePosition());
						}
					}
				}
			};
			slotsCharms.push_back(_slot);
			canvas->AddWidget(_slot);

			CharmWidget* _widget = new CharmWidget(ShapeData(Vector2f(_posX, _posY), slotSize * 2.0f, CHARMS + to_string(_index) + ".png"), _items[_count].title, _items[_count].text, _slot);
			_slot->SetForeground(_widget);
			canvas->AddWidget(_widget);
		}
	}
}

void CharmsMenu::Notches()
{
	const float _gapNotchX = 5.0f;
	const float _spacingNotchY = halfSize.y * 0.85f;
	for (int _row = 0; _row < notches; _row++)
	{
		const float _posX = gridPos.x + _row * slotSize.x + _gapNotchX * _row;
		const float _posY = _spacingNotchY;
		ShapeWidget* _notch = new ShapeWidget(ShapeData(Vector2f(_posX, _posY), notchSize, PATH_NOTCH_UNUSED));
		canvas->AddWidget(_notch);
	}
}

void CharmsMenu::NotchesText()
{
	const float _spacingNotchTextY = halfSize.y * 0.7f;
	const Vector2f& _posText = Vector2f(gridPos.x - 10.0f, _spacingNotchTextY);
	TextWidget* _text = new TextWidget(TextData("Notches", _posText, FONT));
	canvas->AddWidget(_text);
}

void CharmsMenu::EquippedText()
{
	const float _spacingY = halfSize.y * 0.8f;

	const float _spacingNotchTextY = halfSize.y * 0.7f;
	const Vector2f& _posText = Vector2f(gridPos.x - 10.0f, _spacingNotchTextY);
	TextWidget* _equippedText = new TextWidget(TextData("Equipped", Vector2f(_posText.x, _spacingY + slotSize.y - halfSize.y * 0.60f), FONT));

	canvas->AddWidget(_equippedText);
}

void CharmsMenu::Title()
{
	titleItem = new Label(TextData("No charms equipped", Vector2f(windowSize.x / 1.5f, halfSize.y * 1.001f), FONT, 26));
	canvas->AddWidget(titleItem);
}

void CharmsMenu::Description()
{
	descriptionItem = new Label(TextData("Select a charms below \nto equip it and activate \nits effects.", Vector2f(windowSize.x / 1.5f, halfSize.y * 1.15f), FONT));
	canvas->AddWidget(descriptionItem);
}