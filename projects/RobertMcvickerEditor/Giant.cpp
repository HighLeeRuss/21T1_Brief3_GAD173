#include "Giant.h"
#include "app.h"

Giant::Giant()
{
	
	kage::World::findByTag("Player");
	m_sprite = kage::TextureManager::getSprite("data/frost.png");
	kage::centreOrigin(m_sprite);
	m_tags.add("Giant");

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
	kage::Physics::CircleBuilder()
		.radius(0.1)
		.pos(0, 0.4)
		.mass(0.01)
		.sensor(true)
		.userData(1)
		.build(m_body);
}

Giant::~Giant()
{

}



	


void Giant::update(float deltaT)
{
	// Do logic here
	
	bool onGround = kage::Physics::getTouching(m_body, 1);
	auto vel = velocity();
	vel.x = m_direction * m_speed;
	

	auto nextTo = kage::Physics::testPoint(position() + kf::Vector2(m_direction *.5 , 0));
	auto ground1 = kage::Physics::testPoint(position() + kf::Vector2(m_direction * 0.5, 1));
	auto ground2 = kage::Physics::testPoint(position() + kf::Vector2(m_direction * 1.5, 1));
	auto above = kage::Physics::testPoint(position() + kf::Vector2(m_direction * .5, -1));

	//main AI

	if (onGround)
	{
		if (nextTo) // something beside
		{
			m_direction *= -1;	
		}
		else //nothing beside us
		{
			if (!ground1)
			{
				if (ground2)
				{
					vel.y = -4;
				}
				else
				{
					m_direction *= -1;
				}
			}
		}
		if (m_direction == -1)
		{
			m_sprite->setScale(1, 1);
		}
		else if (m_direction == 1)
		{
			m_sprite->setScale(-1, 1);
		}
		

		
	}

	
	velocity(vel);
}

void Giant::onCollision(GameObject *obj)
{
	if (obj->m_tags.has("Player"))
	{
	//m_dead = true;		// kills itself
	obj->m_dead = true;	// kills the other object
	}
}

void Giant::onCollision(b2Fixture *fix)
{
	//if ((int)(fix->GetUserData()) == 1234) // Fake ID value 1234
	//{
	//}
}

#pragma region Optional
//void Giant::onCollisionStop(GameObject* obj)
//{
//}

//void Giant::onCollisionStop(b2Fixture* fix)
//{
//}

//void Giant::render(sf::RenderTarget& rt)
//{
//	// Do custom rendering here. Not normally needed.
//}
#pragma endregion
