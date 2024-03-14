#include "Belfly.h"
#include "MovementComponent.h"

Belfly::Belfly(const ShapeData& _data) : Mob(_data)
{

}

void Belfly::Init()
{
	const Vector2f& _sizeIdle = Vector2f(115.0f, 165.0f); // ratio fait de la taille d'une image dans le sheet
	const Vector2f& _sizeAttack = Vector2f(195.0f, 200.0f); // ratio fait de la taille d'une image dans le sheet
	//const Vector2f& _size = Vector2f(512.f, 256.0f); // ratio fait de la taille d'une image dans le sheet
	const ReadDirection& _readDirection = READ_RIGHT;
	const bool _toRepeat = true;
	const int _countIdle = 10;
	const int _countAttack = 12;
	const float _speedIdle = 0.3f;
	const float _speedAttack = 0.3f;

	animation->InitAnimations({
		AnimationData("Idle", Vector2f(0.0f, 0.0f), _sizeIdle, _readDirection, _toRepeat, _countIdle, _speedIdle),
		AnimationData("DeathAttack", Vector2f(0.0f, 175.0f), _sizeAttack, _readDirection, _toRepeat, _countAttack, _speedAttack),
	});
}