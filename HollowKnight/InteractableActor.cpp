#include "InteractableActor.h"
#include "Game.h"
#include "Widget.h"
#include "Label.h"

#define PATH_INTERACTION "UIs/Discussions/Interaction.png"
#define PATH_DISCUSSION "UIs/Discussions/Dialog.png"
#define FONT "Font.ttf"

InteractableActor::InteractableActor(const string& _name, const ShapeData& _data) : Actor(_name, _data, CT_NONE)
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
	const Vector2f& _interactionBGPos = Vector2f(690.0f, 230.0f);
	interactionBG = new ShapeWidget(ShapeData(_interactionBGPos, Vector2f(200.0f, 124.0f), PATH_INTERACTION));
	canvas->AddWidget(interactionBG);

	interactionText = new Label(TextData("LISTEN", _interactionBGPos + Vector2f(0.0f, -10.0f), FONT, 32));
	canvas->AddWidget(interactionText);

	const Vector2f& _halfWindowSize = Game::GetWindowSize() / 2.0f;
	const Vector2f& _discussionPos = Vector2f(_halfWindowSize.x, 80.0f);

	discussionBG = new ShapeWidget(ShapeData(_discussionPos, Vector2f(418.0f, 150.0f), PATH_DISCUSSION));
	discussionBG->SetVisible(false);
	canvas->AddWidget(discussionBG);

	discussionText = new ProgressLabel(TextData("Your words, are they repeating ?", _discussionPos + Vector2f(0.0f, -20.0f), FONT, 16), 0.1f);
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