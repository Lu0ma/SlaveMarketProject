#include "ShopMenu.h"
#include "Merchand.h"
#include "Game.h"
#include "HUD.h"

#define PATH_ITEM "UIs/Inventory/Core.png"
#define PATH_LANTERN "UIs/Inventory/Lantern.png"

#define PATH_SHOP "UIs/Shop/Shop.png"
#define PATH_GEO "UIs/Shop/Geo.png"

ShopMenu::ShopMenu(Menu* _owner, Merchand* _merchand) : Menu("Shop", _owner)
{
	timeBeforeOpenShop = 8.0f;
	buttons = vector<Button*>();
	descriptionTitle = nullptr;
	descriptionText = nullptr;
	timer = nullptr;
	merchand = _merchand;
	purchase = new PurchaseMenu(this);
}


void ShopMenu::Init()
{
	const Vector2f& _windowSize = Game::GetWindowSize();
	const Vector2f& _halfWindowSize = Game::GetWindowSize() / 2.0f;

	#pragma region Background

	const Vector2f& _shopSize = Vector2f(_halfWindowSize.x * 0.8f, _windowSize.y);
	const Vector2f& _shopPos = Vector2f(_halfWindowSize.x + _shopSize.x / 2.0f, _halfWindowSize.y);
	ShapeWidget* _shop = new ShapeWidget(ShapeData(_shopPos, _shopSize, PATH_SHOP));
	canvas->AddWidget(_shop);

	#pragma endregion

	#pragma region Grid

	items = {
		{
			PATH_LANTERN,
			200,
			"Lantern",
			"This is a simple lantern."
		},
		{
			PATH_ITEM,
			300,
			"Gathering Swarm",
			"Do you find yourself leaving a\n"
			"lot of Geo behind as you hurry\n"
			"through the caverns ?\n\n"
			"This charm will make sure that\n"
			"any loose change finds its way\n"
			"back to you."
		},
	};

	const float _widgetPosX = _shopPos.x - _shopSize.x * 0.35f;
	const Vector2f& _widgetSize = Vector2f(60.0f, 60.0f);
	const float _geoPosX = _widgetPosX + _widgetSize.x;
	const Vector2f& _geoSize = Vector2f(30.0f, 30.0f);
	const float _geoTextPosX = _geoPosX + _geoSize.x * 0.8f;
	const float _startPosY = _shopPos.y - _shopSize.y * 0.275f;
	const float _gapY = 10.0f;
	const Vector2f& _buttonSize = Vector2f(_shopSize.x * 0.4f, _widgetSize.y + _widgetSize.y * 0.7f);
	const float _buttonPosX = _widgetPosX + _buttonSize.x * 0.2f;
	int _index = 0;

	for (const SellItem& _item : items)
	{
		const float _posY = _startPosY + _index * _widgetSize.y + _gapY * _index;

		Button* _button = new Button(ShapeData(Vector2f(_buttonPosX, _posY), _buttonSize));
		_button->GetDrawable()->setFillColor(Color::Transparent);
		_button->GetData().hoveredCallback = [&]()
		{
			if (Button* _hoveredButton = HUD::GetInstance().GetHoveredButton(buttons))
			{
				MovePointers(_hoveredButton);

				if (ItemWidget* _itemWidget = dynamic_cast<ItemWidget*>(_hoveredButton->GetForeground()))
				{
					descriptionTitle->SetString(_itemWidget->GetTitle());
					descriptionText->SetString(_itemWidget->GetText());
				}
			}
		};
		_button->GetData().pressedCallback = [&]() {
			if (Button* _hoveredButton = HUD::GetInstance().GetHoveredButton(buttons))
			{
				const SellItem& _item = GetSellItemByButton(_hoveredButton);
				purchase->SetItem(_item);
			}
			SetStatus(false);
			purchase->SetStatus(true);
		};
		buttons.push_back(_button);
		canvas->AddWidget(_button);

		ItemWidget* _widget = new ItemWidget(ShapeData(Vector2f(_widgetPosX, _posY), _widgetSize, _item.path),
											 _item.title, _item.text);
		canvas->AddWidget(_widget);
		_button->SetForeground(_widget);

		ShapeWidget* _geo = new ShapeWidget(ShapeData(Vector2f(_geoPosX, _posY), _geoSize, PATH_GEO));
		canvas->AddWidget(_geo);

		Label* _geoText = new Label(TextData(to_string(_item.price), Vector2f(_geoTextPosX, _posY - 3.5f), FONT), AT_LEFT);
		canvas->AddWidget(_geoText);

		_index++;
	}

	#pragma region Pointer

	Menu::Init();
	MovePointers(buttons.front());

	#pragma endregion

	#pragma endregion

	#pragma region Description

	const Vector2f& _descriptionSize = Vector2f(_shopSize.x / 2.0f, _shopSize.y * 0.6f);
	const Vector2f& _descriptionPos = _shopPos + Vector2f(_descriptionSize.x * 0.3f, 0.0f);
	/*ShapeWidget* _description = new ShapeWidget(ShapeData(_descriptionPos, _descriptionSize, ""));
	canvas->AddWidget(_description);*/

	#pragma region Title

	const float _descriptionTitlePosX = _descriptionPos.x;
	const float _descriptionTitlePosY = _descriptionPos.y - _descriptionPos.y / 2.0f;
	const Vector2f& _descriptionTitlePos = Vector2f(_descriptionTitlePosX, _descriptionTitlePosY);
	descriptionTitle = new Label(TextData("", _descriptionTitlePos, FONT, 22), AT_CENTER);
	canvas->AddWidget(descriptionTitle);

	#pragma endregion

	#pragma region Text

	const float _descriptionTextPosX = _descriptionPos.x - _descriptionSize.x * 0.45f;
	const float _descriptionTextPosY = _descriptionTitlePosY + _descriptionSize.y * 0.15f;
	const Vector2f& _descriptionLabelPos = Vector2f(_descriptionTextPosX, _descriptionTextPosY);
	descriptionText = new Label(TextData("", _descriptionLabelPos, FONT, 13), AT_LEFT);
	canvas->AddWidget(descriptionText);

	#pragma endregion

	#pragma endregion
}

void ShopMenu::SetStatus(const bool _status, const bool _applyToWidgets)
{
	if (!_status)
	{
		timer = nullptr;
		Menu::SetStatus(false);
		purchase->SetStatus(false);
	}

	else
	{
		timer = new Timer([&]() {
			merchand->CloseDiscussion();
			Open();
		}, seconds(timeBeforeOpenShop));
	}
}

void ShopMenu::Open()
{
	Menu::SetStatus(true);
}