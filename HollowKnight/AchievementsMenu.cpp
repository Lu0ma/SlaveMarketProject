#include "AchievementsMenu.h"
#include "Game.h"

#define PATH_ACHIEVEMENTS "UIs/Menus/Achievements/Achievement_"

AchievementsMenu::AchievementsMenu(Menu* _owner) : Menu("Achievements", _owner)
{

}


void AchievementsMenu::Init()
{
	const Vector2f& _windowSize = Game::GetWindowSize();
	const float _halfWindowX = _windowSize.x / 2.0f;

	#pragma region Background

	ShapeWidget* _background = new ShapeWidget(ShapeData(_windowSize / 2.0f, _windowSize, PATH_BACKGROUND));
	canvas->AddWidget(_background);

	#pragma endregion

	#pragma region Title

	const float _titlePosY = _windowSize.y * 0.1f;
	Label* _title = new Label(TextData("Achievements", Vector2f(_halfWindowX, _titlePosY), FONT, 36));
	canvas->AddWidget(_title);

	const float _titleBarPosY = _titlePosY + 75.0f;
	const Vector2f& _titleBarSize = Vector2f(_windowSize.x * 0.4f, 50.0f);
	const float _halfTitleBarSizeX = _titleBarSize.x * 0.45f;
	ShapeWidget* _titleBar = new ShapeWidget(ShapeData(Vector2f(_halfWindowX, _titleBarPosY), _titleBarSize, PATH_TITLE_ICON));
	canvas->AddWidget(_titleBar);

	#pragma endregion

	#pragma region Grid

	struct AchievementData
	{
		string title;
		string description;
	};

	const vector<AchievementData>& _allData = {
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
		/*{
			"MASKED_PATH"
			"MASKED.png",
			"Acquire all Mask Shards"
		},
		{
			"CHARMED_PATH"
			"CHARMED.png",
			"Acquire your first Charm"
		},
		{
			"SOULFUL_PATH"
			"SOULFUL.png",
			"Acquire 3 Vessel Fragments"
		},
		{
			"WORLDFUL_PATH"
			"WORLDFUL.png",
			"Acquire all Vessel Fragments",
		},
		{
          	"FALSEHOOD_PATH"
			"FALSEHOOD.png",
			"Defeat the False Knight"
		},*/
	};

	const float _firstAchievementPosY = _windowSize.y * 0.3f;
	const float _iconPosX = _windowSize.x * 0.25f;
	const Vector2f& _iconSize = Vector2f(50.0f, 50.0f);
	const float _achievementPosX = _iconPosX + 70.0f;
	const float _gapY = _iconSize.y * 0.25f;

	const int _dataCount = (int)_allData.size();
	for (int _index = 0; _index < _dataCount; _index++)
	{
		const AchievementData& _data = _allData[_index];
		const float _achievementPosY = _firstAchievementPosY + _iconSize.y * _index + _gapY * _index;

		const string& _path = PATH_ACHIEVEMENTS + to_string(_index + 1) + ".png";
		ShapeWidget* _icon = new ShapeWidget(ShapeData(Vector2f(_iconPosX, _achievementPosY), _iconSize, _path));
		canvas->AddWidget(_icon);

		Label* _achievementTitle = new Label(TextData(_data.title, Vector2f(_achievementPosX, _achievementPosY - 10.0f), FONT, 20), AT_LEFT);
		canvas->AddWidget(_achievementTitle);

		Label* _achievementDescrition = new Label(TextData(_data.description, Vector2f(_achievementPosX, _achievementPosY + 10.0f), FONT, 14), AT_LEFT);
		canvas->AddWidget(_achievementDescrition);
	}

	#pragma endregion 

	#pragma region Back

	const Vector2f& _buttonSize = Vector2f(200.0f, 50.0f);
	const float _buttonPosY = _windowSize.y * 0.9f;
	const Vector2f& _buttonPos = Vector2f(_halfWindowX, _buttonPosY);

	backButton = new Button(ShapeData(_buttonPos, _buttonSize, ""));
	backButton->GetData().pressedCallback = [&]() {
		owner->SetStatus(true);
		canvas->SetVisibilityStatus(false);
	};
	backButton->GetDrawable()->setFillColor(Color::Transparent);
	canvas->AddWidget(backButton);

	Label* _buttonText = new Label(TextData("BACK", Vector2f(_halfWindowX, _buttonPos.y), FONT, 20));
	backButton->SetForeground(_buttonText);
	canvas->AddWidget(_buttonText);

	Menu::Init();
	MovePointers(backButton);

	#pragma endregion
}