#include "InteractableActor.h"
#include "Game.h"
#include "Widget.h"
#include "Label.h"
#include "Macro.h"

#define PATH_INTERACTION "UIs/Discussions/Interaction.png"
#define PATH_DISCUSSION "UIs/Discussions/Dialog.png"
#define FONT "Font.ttf"

InteractableActor::InteractableActor(const string& _name, const ShapeData& _data) : Actor(_name, _data, CT_OVERLAP)
{
	canvas = new Canvas(STRING_ID("Interactable"));
	isOpen = false;

	interactionBG = nullptr;
	interactionText = nullptr;

	discussionBG = nullptr;
	discussionText = nullptr;

	Init();
	Register();
}


void InteractableActor::Register()
{
	ActorManager::GetInstance().AddInteractable(this);
}

void InteractableActor::Verify()
{
	if (!interactionBG || !interactionText) return;

	Player* _player = Game::GetPlayer();
	FloatRect _rectPNJ = shape->getGlobalBounds();

	if (_rectPNJ.intersects(_player->GetBounds()))
	{
		if (!isOpen)
		{
			interactionBG->SetVisible(true);
			interactionText->SetVisible(true);
		}
	}

	else
	{
		CloseDiscussion();
	}
}

void InteractableActor::CloseDiscussion()
{
	isOpen = false;

	interactionBG->SetVisible(false);
	interactionText->SetVisible(false);

	discussionBG->SetVisible(false);
	discussionText->SetVisible(false);
}


void InteractableActor::Init()
{
	const Vector2f& _interactionBGPos = /*Vector2f(690.0f, 230.0f); */ GetShapePosition();
	const RenderWindow& _window = Game::GetWindow();
	const Vector2f& _interactionBGPos2 = _window.mapPixelToCoords(static_cast<Vector2i>(_interactionBGPos));

	interactionBG = new ShapeWidget(ShapeData(_interactionBGPos, Vector2f(200.0f, 124.0f), PATH_INTERACTION), WT_WORLD);
	interactionBG->SetVisible(false);
	canvas->AddWidget(interactionBG);

	interactionText = new Label(TextData("Listen", _interactionBGPos + Vector2f(0.0f, -10.0f), FONT, 32), AT_CENTER, WT_WORLD);
	interactionText->SetVisible(false);
	canvas->AddWidget(interactionText);

	const Vector2f& _halfWindowSize = Game::GetWindowSize() / 2.0f;
	const Vector2f& _discussionPos = Vector2f(_halfWindowSize.x, 80.0f);

	discussionBG = new ShapeWidget(ShapeData(_discussionPos, Vector2f(418.0f, 150.0f), PATH_DISCUSSION), WT_WORLD);
	discussionBG->SetVisible(false);
	canvas->AddWidget(discussionBG);

	discussionText = new ProgressLabel(TextData("", _discussionPos + Vector2f(0.0f, -20.0f), FONT, 16), 0.1f, "Bon jeu à toi dans Hollow Knight !", AT_CENTER, WT_WORLD);
	discussionText->SetVisible(false);
	canvas->AddWidget(discussionText);
}

void InteractableActor::Update(const float _deltaTime)
{
	Actor::Update(_deltaTime);
	Verify();
}

void InteractableActor::OpenDiscussion()
{
	if (isOpen)
	{
		CloseDiscussion();
		return;
	}

	isOpen = true;

	interactionBG->SetVisible(false);
	interactionText->SetVisible(false);

	discussionBG->SetVisible(true);
	discussionText->SetVisible(true);
}