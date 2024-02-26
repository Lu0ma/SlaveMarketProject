#include "Player.h"
//#include "TextureManager.h"
#include "ActionMap.h"
#include "Component.h"
#include "MovementComponent.h"

Player::Player() : Actor("Hero" , data)
{
	data = ShapeData();
}

void Player::Init()
{

	ActionMap("Movement ", { 
		ActionData("Right" , this , &Player::Right , {Event::KeyPressed , Keyboard::D} , {Event::KeyPressed , Keyboard::Right}),
		ActionData("Left" , this , &Player::Left , {Event::KeyPressed , Keyboard::Q} , {Event::KeyPressed , Keyboard::Left} ),
		ActionData("Up" , this , &Player::Up , {Event::KeyPressed , Keyboard::Z} , {Event::KeyPressed , Keyboard::Up})
		}

	);
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
