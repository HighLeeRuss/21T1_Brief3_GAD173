#pragma once
#include "kage/gameobject.h"

class Devil : public kage::GameObject
{
public:
	Devil();
	~Devil();

	void update(float deltaT);
	void onCollision(GameObject *obj);
	void onCollision(b2Fixture *fix);

	float jumpTime = 3;
	float shootTime = 1;



#pragma region Optional
	//void render(sf::RenderTarget& rt);
	//void onCollisionStop(GameObject* obj);
	//void onCollisionStop(b2Fixture* fix);
#pragma endregion
};
