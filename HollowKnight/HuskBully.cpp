#include "HuskBully.h"
#include "Animation.h"

#define PATH_HUSK_BULLY "Animations/HuskBully.png"

HuskBully::HuskBully(const ShapeData& _data) : Mob(_data)
{
	//===================================
	// TODO => aucune données correcte
	//===================================

	const Vector2f& _sizeIdle = Vector2f(115.0f, 127.0f); // ratio fait de la taille d'une image dans le sheet
	const Vector2f& _sizeAttack = Vector2f(192.0f, 218.0f); // ratio fait de la taille d'une image dans le sheet
	//const Vector2f& _size = Vector2f(512.f, 256.0f); // ratio fait de la taille d'une image dans le sheet
	const ReadDirection& _readDirection = READ_RIGHT;
	const bool _toRepeat = true;
	const int _countIdle = 9;
	const int _countAttack = 6;
	const float _speedIdle = 0.3f;
	const float _speedAttack = 0.3f;

	//animation = new AnimationComponent(this, PATH_HUSK_BULLY, {
	//	/*AnimationData("Idle", Vector2f(2.0f, 22.0f), _sizeIdle, _readDirection, ANIM_DIR_UP, _toRepeat, _countIdle, _speedIdle),
	//	AnimationData("Attack", Vector2f(4.0f, 173.0f), _sizeAttack, _readDirection, ANIM_DIR_DOWN, _toRepeat, _countAttack, _speedAttack),*/
	//	AnimationData("Attack2", Vector2f(4.0f, 173.0f), _sizeAttack, _readDirection, ANIM_DIR_RIGHT, _toRepeat, _countAttack, _speedAttack),
	//	AnimationData("Idle2", Vector2f(2.0f, 22.0f), _sizeIdle, _readDirection, ANIM_DIR_LEFT, _toRepeat, _countIdle, _speedIdle),
	//	}, ANIM_DIR_LEFT);

	//components.push_back(animation);
}
