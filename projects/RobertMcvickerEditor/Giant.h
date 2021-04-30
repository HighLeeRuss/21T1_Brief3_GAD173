#pragma once
#include "kage/gameobject.h"
#include "Player.h"

class Giant : public kage::GameObject
{
public:
	Giant();
	~Giant();

	void update(float deltaT);
	void onCollision(GameObject *obj);
	void onCollision(b2Fixture *fix);

	float m_direction = -1;
	float m_speed = 2;
	bool beside;

#pragma region Optional
	//void render(sf::RenderTarget& rt);
	//void onCollisionStop(GameObject* obj);
	//void onCollisionStop(b2Fixture* fix);
#pragma endregion
};
