#include "AchievementsMenu.h"
#include "Game.h"

#define PATH_ACHIEVEMENTS "UIs/Menus/Achievements/Achievement_"
#define PATH_SCROLL "UIs/Menus/Achievements/ScrollBar/Scroll.png"

AchievementsMenu::AchievementsMenu(Menu* _owner) : Menu("Achivements", _owner)
{
	handle = nullptr;
	canvas = nullptr;
	allData = vector<AchievementData>();
	boxOfView = nullptr;
}

void AchievementsMenu::Init()
{

	canvas = new Canvas("Achievements", FloatRect(0, 0, 1, 1));
	const Vector2f& _windowSize = Game::GetWindowSize();
	const float _halfWindowX = _windowSize.x / 2.0f;

	boxOfView = new ShapeWidget(ShapeData(Vector2f(_windowSize.x / 2.0f - 50.0f, _windowSize.y / 2.0f + 20.0f), Vector2f(600.0f, 375.0f), ""));
	boxOfView->GetDrawable()->setFillColor(Color::Transparent);


#pragma region Background

	ShapeWidget* _background = new ShapeWidget(ShapeData(_windowSize / 2.0f, _windowSize, PATH_BACKGROUND));
	canvas->AddWidget(_background);

#pragma endregion

#pragma region Title

	const float _tilePosY = _windowSize.y * 0.15f;
	Label* _title = new Label(TextData("ACHIEVEMENTS", Vector2f(_halfWindowX, _tilePosY), FONT, 32));
	canvas->AddWidget(_title);

	const float _tileIconPosY = _tilePosY + 50.0f;
	ShapeWidget* _titleIcon = new ShapeWidget(ShapeData(Vector2f(_halfWindowX, _tileIconPosY), Vector2f(765.0f, 78.0f), PATH_TITLE_ICON));
	_titleIcon->GetDrawable()->setScale(0.6f, 0.6f);
	canvas->AddWidget(_titleIcon);

#pragma endregion

#pragma region Grid

	allData = {
		{
			"PROTECTED",
			"Acquire 4 Mask Shards"
		},
		{
			"MASKED",
			"Acquire all Mask Shards"
		},
		{
			"CHARMED",
			"Acquire your first Charm"
		},
		{
			"ENCHANTED",
			"Acquire half of Hallownest's Charms"
		},
		{
			"BLESSED",
			"Acquire all Charms and received Salubra's blessing"
		},
		{
			"SOULFUL",
			"Acquire 3 Vessel Fragments"
		},
		{
			"CHARMED",
			"Acquire your first Charm"
		},
		{
			"ENCHANTED",
			"Acquire half of Hallownest's Charms"
		},
		{
			"BLESSED",
			"Acquire all Charms and received Salubra's blessing"
		},
		{
			"SOULFUL",
			"Acquire 3 Vessel Fragments"
		},
	};

	const float _firstAchievementPosY = _windowSize.y * 0.3f;
	const float _iconPosX = _windowSize.x * 0.25f;
	const Vector2f& _iconSize = Vector2f(50.0f, 50.0f);
	const float _achievementPosX = _iconPosX + 70.0f;
	const float _gapY = _iconSize.y * 0.25f;

	const int _dataCount = (int)allData.size();
	for (int _index = 0, _offset = 0; _index < _dataCount; _index++, _offset++)
	{
		_offset %= 6; //TODO remove si on met plusieurs achivements
		const AchievementData& _data = allData[_offset];
		const float _achievementPosY = _firstAchievementPosY + _iconSize.y * _index + _gapY * _index;

		const string& _path = PATH_ACHIEVEMENTS + to_string(_offset + 1) + ".png";
		ShapeWidget* _icon = new ShapeWidget(ShapeData(Vector2f(_iconPosX, _achievementPosY), _iconSize, _path));
		canvas->AddWidget(_icon);

		Label* _achievementTitle = new Label(TextData(_data.title, Vector2f(_achievementPosX, _achievementPosY - 10.0f), FONT, 20), AT_LEFT);
		canvas->AddWidget(_achievementTitle);

		Label* _achievementDescrition = new Label(TextData(_data.description, Vector2f(_achievementPosX, _achievementPosY + 10.0f), FONT, 14), AT_LEFT);
		canvas->AddWidget(_achievementDescrition);

		Achievement* _achievement = new Achievement(_icon, { _achievementTitle, _achievementDescrition });
		achievements.insert(achievements.begin(), _achievement);
	}
	int _index = 0;
	for (Achievement* _achievement : achievements)
	{
		if (_index <= 3)
		{
			achievements[_index]->widget->SetVisible(false);
			achievements[_index]->labels[0]->SetVisible(false);
			achievements[_index]->labels[1]->SetVisible(false);
		}
		_index++;
	}
#pragma endregion 

#pragma region Back

	const Vector2f& _buttonSize = Vector2f(200.0f, 50.0f);
	const float _buttonPosY = _windowSize.y * 0.9f;
	const Vector2f& _buttonPos = Vector2f(_halfWindowX, _buttonPosY);

	Button* _backButton = new Button(ShapeData(_buttonPos, _buttonSize, ""));
	_backButton->GetData().pressedCallback = [&]() {
		owner->SetStatus(true);
		canvas->SetVisibilityStatus(false);
		};
	_backButton->GetDrawable()->setFillColor(Color::Transparent);
	canvas->AddWidget(_backButton);

	Label* _buttonText = new Label(TextData("BACK", Vector2f(_halfWindowX, _buttonPos.y), FONT, 20));
	_backButton->SetForeground(_buttonText);
	canvas->AddWidget(_buttonText);

	pointer = new ShapeWidget(ShapeData(Vector2f(_halfWindowX, _buttonPos.y), Vector2f(_buttonSize.x, _buttonSize.y), PATH_POINTER));
	canvas->AddWidget(pointer);

#pragma endregion

#pragma region ScrollBar

	const Vector2f& _barSize = Vector2f(61, 400.0f);
	const float _windowOneThirdX = _windowSize.x / 1.35f;
	const Vector2f& _scrollSize = Vector2f(30.0f, 60.0f);

	handle = new ScrollBar(ShapeData(Vector2f(_windowOneThirdX, 225.0f), _scrollSize, PATH_SCROLL), 4, [&](bool _scrolltype) {ComputeScroll(allData, _scrolltype); });
	canvas->AddWidget(handle->GetBar());
	canvas->AddWidget(handle);
	canvas->AddWidget(handle->GetButtonUp());
	canvas->AddWidget(handle->GetButtonDown());
#pragma endregion
	canvas->AddWidget(boxOfView);
}

void AchievementsMenu::ComputeScroll(const vector<AchievementData>& _data, const bool _scrollType)
{
	const int _dataSize = (int)_data.size();
	for (int _index = 0; _index < _dataSize; _index++)
	{
		const int _baseIndex = handle->GetBaseIndex();

		if (_scrollType)
		{
			achievements[_index]->widget->GetDrawable()->setPosition(
				achievements[_index]->widget->GetDrawable()->getPosition().x,
				achievements[_index]->widget->GetDrawable()->getPosition().y + 62.5f);

			for (int _offset = 0; _offset < 2; _offset++)
			{
				achievements[_index]->labels[_offset]->GetDrawable()->setPosition(
					achievements[_index]->labels[_offset]->GetDrawable()->getPosition().x,
					achievements[_index]->labels[_offset]->GetDrawable()->getPosition().y + 62.5f);
			}

		}
		else
		{
			achievements[_index]->widget->GetDrawable()->setPosition(
				achievements[_index]->widget->GetDrawable()->getPosition().x,
				achievements[_index]->widget->GetDrawable()->getPosition().y - 62.5f);

			for (int _offset = 0; _offset < 2; _offset++)
			{
				achievements[_index]->labels[_offset]->GetDrawable()->setPosition(
					achievements[_index]->labels[_offset]->GetDrawable()->getPosition().x,
					achievements[_index]->labels[_offset]->GetDrawable()->getPosition().y - 62.5f);
			}
		}
	}

	for (int _index = 0; _index < _dataSize; _index++)
	{
		if (!boxOfView->GetDrawable()->getGlobalBounds().contains(achievements[_index]->widget->GetDrawable()->getPosition()))
		{
			achievements[_index]->SetVisible(false);
			for (int _offset = 0; _offset < 2; _offset++)
			{
				achievements[_index]->labels[_offset]->SetVisible(false);
			}
		}
		else
		{
			achievements[_index]->SetVisible(true);
			for (int _offset = 0; _offset < 2; _offset++)
			{
				achievements[_index]->labels[_offset]->SetVisible(true);

			}
		}
	}
}
