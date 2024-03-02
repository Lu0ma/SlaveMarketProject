#include "Merchand.h"
#include "Game.h"
#include "HUD.h"

#define PATH_ITEM "UIs/Inventory/Core.png"
#define PATH_LANTERN "UIs/Inventory/Lantern.png"

#define PATH_SHOP "UIs/Shop/Shop.png"
#define PATH_POINTER "UIs/Shop/Pointer.png"
#define PATH_GEO "UIs/Shop/Geo.png"
#define FONT "Font.ttf"

Merchand::Merchand(const ShapeData& _data, const vector<string>& _texts)
				  : NPC(STRING_ID("Merchand"), _data, _texts)
{
	timeBeforeOpenShop = 3.0f;
	canvas = new Canvas("Shop");
	buttons = vector<Button*>();
	pointer = nullptr;
	descriptionTitle = nullptr;
	descriptionText = nullptr;
}


void Merchand::CloseDiscussion()
{
	InteractableActor::CloseDiscussion();
	CloseShop();
}


void Merchand::Init()
{
	NPC::Init();

	canvas->SetVisibilityStatus(false);

	const Vector2f& _windowSize = Game::GetWindowSize();
	const Vector2f& _halfWindowSize = Game::GetWindowSize() / 2.0f;

	#pragma region Background

	const Vector2f& _shopSize = Vector2f(_halfWindowSize.x * 0.8f, _windowSize.y);
	const Vector2f& _shopPos = Vector2f(_halfWindowSize.x + _shopSize.x / 2.0f, _halfWindowSize.y);
	ShapeWidget* _shop = new ShapeWidget(ShapeData(_shopPos, _shopSize, PATH_SHOP));
	canvas->AddWidget(_shop);

	#pragma endregion

	#pragma region Grid

	struct SellItem
	{
		string widgetPath;
		int price;
		string title;
		string text;
	};

	const vector<SellItem>& _items = {
		{
			PATH_ITEM,
			300,
			"Swarm",
			"Do you find yourself leaving a\n"
			"lot of Geo behind as you hurry\n"
			"through the caverns ?\n\n"
			"This charm will make sure that\n"
			"any loose change finds its way\n"
			"back to you."
		},

		{
			PATH_LANTERN,
			200,
			"Lantern",
			"This is a simple lantern."
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
	int _index = 0;

	for (const SellItem& _item : _items)
	{
		const float _posY = _startPosY + _index * _widgetSize.y + _gapY * _index;

		Button* _button = new Button(ShapeData(Vector2f(_widgetPosX + _buttonSize.x * 0.2f, _posY), _buttonSize));
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

		ItemWidget* _widget = new ItemWidget(ShapeData(Vector2f(_widgetPosX, _posY), _widgetSize, _item.widgetPath),
											 _item.title, _item.text);
		canvas->AddWidget(_widget);
		_button->SetForeground(_widget);

		ShapeWidget* _geo = new ShapeWidget(ShapeData(Vector2f(_geoPosX, _posY), _geoSize, PATH_GEO));
		canvas->AddWidget(_geo);

		Label* _geoText = new Label(TextData(to_string(_item.price), Vector2f(_geoTextPosX, _posY - 8.5f), FONT));
		canvas->AddWidget(_geoText);

		_index++;
	}

	#pragma region Pointer

	pointer = new ShapeWidget(ShapeData(Vector2f(_widgetPosX, _startPosY), _buttonSize, PATH_POINTER));
	canvas->AddWidget(pointer);

	#pragma endregion

	#pragma endregion

	#pragma region Description

	const Vector2f& _descriptionPos = Vector2f(_shopPos.x + _shopSize.x * 0.15f, _shopPos.y);
	const Vector2f& _descriptionSize = Vector2f(_shopSize.x / 2.0f, _shopSize.y * 0.6f);
	/*ShapeWidget* _description = new ShapeWidget(ShapeData(_descriptionPos, _descriptionSize, ""));
	canvas->AddWidget(_description);*/

	#pragma region Title

	const float _descriptionTitlePosX = _descriptionPos.x - _descriptionSize.x * 0.15f;
	const float _descriptionTitlePosY = _descriptionPos.y - _descriptionPos.y / 2.0f;
	const Vector2f& _descriptionTitlePos = Vector2f(_descriptionTitlePosX, _descriptionTitlePosY);
	descriptionTitle = new Label(TextData("Shade Cloak", _descriptionTitlePos, FONT, 22));
	canvas->AddWidget(descriptionTitle);

	#pragma endregion

	#pragma region Text

	const float _descriptionTextPosX = _descriptionTitlePosX - _descriptionSize.x * 0.3f;
	const float _descriptionTextPosY = _descriptionTitlePosY + _descriptionSize.y * 0.15f;
	const Vector2f& _descriptionLabelPos = Vector2f(_descriptionTextPosX, _descriptionTextPosY);
	descriptionText = new Label(TextData("coucou\nc'est moi", _descriptionLabelPos, FONT, 13));
	canvas->AddWidget(descriptionText);

	#pragma endregion

	#pragma endregion
}

void Merchand::OpenDiscussion()
{
	InteractableActor::OpenDiscussion();

	if (!timer)
	{
		timer = new Timer([&]() {
			Toggle();
			InteractableActor::CloseDiscussion();
			SetIsOpen(true);
		}, seconds(timeBeforeOpenShop));
	}
}

//void Merchand::BuyItem()
//{
//
//}