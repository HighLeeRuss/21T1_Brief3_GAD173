#pragma once
#include "kage/gameobject.h"
#include "kage/anim.h"


class Player : public kage::GameObject
{
	

public:
	Player();
	~Player();

	void update(float deltaT);
	void onCollision(GameObject *obj);
	void onCollision(b2Fixture *fix);

	int counter = 1;
	bool doubleJump = false;

	kage::Anim m_anim;

#pragma region Optional
	//void render(sf::RenderTarget& rt);
	//void onCollisionStop(GameObject* obj);
	//void onCollisionStop(b2Fixture* fix);
#pragma endregion
};
