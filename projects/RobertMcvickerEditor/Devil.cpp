#include "Devil.h"
#include "app.h"

Devil::Devil()
{
	m_sprite = kage::TextureManager::getSprite("data/demon.png");
	kage::centreOrigin(m_sprite);
	m_tags.add("Devil");

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

Devil::~Devil()
{

}

void Devil::update(float deltaT)
{
	// Do logic here

	
	
	jumpTime -= deltaT;
	shootTime -= deltaT;
	
	if (jumpTime <= 0)
	{
		velocity(0, -6);
		jumpTime = 3;
	}

	auto player = kage::World::findByTag("Player");
	if (player)
	{
		auto hp = kage::Physics::rayCast(position(), player->position());
		if (hp.hit)
		{
			if (kage::Physics::getGameObject(hp.fixture) == player && shootTime <= 0) 
			{
				auto fireball = kage::World::build<Fireball>();
				fireball->position(position());
				auto dir = player->position() - position();
				dir = normalise(dir);
				fireball->velocity(dir * 4);
				shootTime = 1;

			}
		}
	}

}

void Devil::onCollision(GameObject *obj)
{
	//if (obj->m_tags.has("enemy"))
	//{
		//m_dead = true;		// kills itself
		//obj->m_dead = true;	// kills the other object
	//}
}

void Devil::onCollision(b2Fixture *fix)
{
	//if ((int)(fix->GetUserData()) == 1234) // Fake ID value 1234
	//{
	//}
}

#pragma region Optional
//void Devil::onCollisionStop(GameObject* obj)
//{
//}

//void Devil::onCollisionStop(b2Fixture* fix)
//{
//}

//void Devil::render(sf::RenderTarget& rt)
//{
//	// Do custom rendering here. Not normally needed.
//}
#pragma endregion
