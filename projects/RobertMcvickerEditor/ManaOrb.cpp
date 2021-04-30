#include "ManaOrb.h"
#include "app.h"

ManaOrb::ManaOrb()
{
	m_sprite = kage::TextureManager::getSprite("data/droplet2.png");
	kage::centreOrigin(m_sprite);
	m_sprite->setScale(0.5, 0.5);
	m_tags.add("ManaOrb");

	// Make a Box2D body
	m_body = kage::Physics::BodyBuilder()
				.pos(0, 0)
				.userData(this)	// This lets the body know which GameObject owns it
				.build();

	// Make a fixture (collision shape) for the body
	kage::Physics::CircleBuilder()
		.radius(0.4f)
		.mass(1)
		.build(m_body); // We need to tell the builder which body to attach to
}

ManaOrb::~ManaOrb()
{

}

void ManaOrb::update(float deltaT)
{
	// Do logic here
}

void ManaOrb::onCollision(GameObject *obj)
{
	//if (obj->m_tags.has("enemy"))
	//{
		//m_dead = true;		// kills itself
		//obj->m_dead = true;	// kills the other object
	//}
}

void ManaOrb::onCollision(b2Fixture *fix)
{
	//if ((int)(fix->GetUserData()) == 1234) // Fake ID value 1234
	//{
	//}
}

#pragma region Optional
//void ManaOrb::onCollisionStop(GameObject* obj)
//{
//}

//void ManaOrb::onCollisionStop(b2Fixture* fix)
//{
//}

//void ManaOrb::render(sf::RenderTarget& rt)
//{
//	// Do custom rendering here. Not normally needed.
//}
#pragma endregion
