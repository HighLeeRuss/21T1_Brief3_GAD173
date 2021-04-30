#pragma once
#include "kage/gameobject.h"

class ManaOrb : public kage::GameObject
{
public:
	ManaOrb();
	~ManaOrb();

	void update(float deltaT);
	void onCollision(GameObject *obj);
	void onCollision(b2Fixture *fix);

#pragma region Optional
	//void render(sf::RenderTarget& rt);
	//void onCollisionStop(GameObject* obj);
	//void onCollisionStop(b2Fixture* fix);
#pragma endregion
};
