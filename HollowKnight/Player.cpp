#include "Player.h"
#include "Component.h"
#include "MovementComponent.h"

Player::Player() : Actor("Hero" , data)
{
	data = ShapeData();
	merchand = new Merchand();
	Init();
}

void Player::Init()
{

	ActionMap("Movement ", { 
		ActionData("Right" , this , &Player::Right , {Event::KeyPressed , Keyboard::D} , {Event::KeyPressed , Keyboard::Right}),
		ActionData("Left" , this , &Player::Left , {Event::KeyPressed , Keyboard::Q} , {Event::KeyPressed , Keyboard::Left} ),
		ActionData("Up" , this , &Player::Up , {Event::KeyPressed , Keyboard::Z} , {Event::KeyPressed , Keyboard::Up})
		}

	);
	new ActionMap("Diplay", { ActionData("Shop", [&]() { merchand->Toggle(); }, InputData({ ActionType::KeyPressed, Keyboard::Tab })) });

}

void Player::Right()
{
	//Component
	GetComponent<MovementComponent>()->SetDestination();
}

void Player::Left()
{
	GetComponent<MovementComponent>()->SetDestination();
}

void Player::Up()
{
	GetComponent<MovementComponent>()->SetDestination();
}
