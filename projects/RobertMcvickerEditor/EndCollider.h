#pragma once
#include "kage/gameobject.h"

class EndCollider : public kage::GameObject
{
public:
	EndCollider();
	~EndCollider();

	void update(float deltaT);
	void onCollision(GameObject *obj);
	void onCollision(b2Fixture *fix);

	bool isFinished = false;

#pragma region Optional
	//void render(sf::RenderTarget& rt);
	//void onCollisionStop(GameObject* obj);
	//void onCollisionStop(b2Fixture* fix);
#pragma endregion
};
