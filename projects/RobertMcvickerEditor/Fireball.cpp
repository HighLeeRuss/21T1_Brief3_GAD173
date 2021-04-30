#include "Fireball.h"
#include "app.h"

Fireball::Fireball()
{
	m_sprite = kage::TextureManager::getSprite("data/fireball.png");
	kage::centreOrigin(m_sprite);
	m_tags.add("Fireball");

	// Make a Box2D body
	m_body = kage::Physics::BodyBuilder()
				.pos(0, 0)
				.userData(this)	// This lets the body know which GameObject owns it
				.build();

	m_body->SetGravityScale(0);

	// Make a fixture (collision shape) for the body
	kage::Physics::CircleBuilder()
		.radius(0.4f)
		.mass(1)
		.sensor(true)
		.build(m_body); // We need to tell the builder which body to attach to
}

Fireball::~Fireball()
{

}

void Fireball::update(float deltaT)
{
	// Do logic here
}

void Fireball::onCollision(GameObject* obj)
{
	if (obj->m_tags.has("Devil"))
	{
		//m_dead = true;		// kills itself
		//obj->m_dead = true;	// kills the other object
	}
	else if (obj->m_tags.has("Fireball"))
	{
	}
	else
	{
		m_dead = true;
		obj->m_dead = true;
	}
}

void Fireball::onCollision(b2Fixture *fix)
{
	//if ((int)(fix->GetUserData()) == 1234) // Fake ID value 1234
	//{
	//}
}

#pragma region Optional
//void Fireball::onCollisionStop(GameObject* obj)
//{
//}

//void Fireball::onCollisionStop(b2Fixture* fix)
//{
//}

//void Fireball::render(sf::RenderTarget& rt)
//{
//	// Do custom rendering here. Not normally needed.
//}
#pragma endregion
