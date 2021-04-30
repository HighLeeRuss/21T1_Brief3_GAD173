#include "Player.h"
#include "app.h"

Player::Player()
{
	m_sprite = kage::TextureManager::getSprite("data/gabe.png");
	m_sprite->setOrigin(32, 36);
	m_tags.add("Player");
	
	m_anim.setSprite(m_sprite);
	m_anim.setGridSize(6, 2);
	m_anim.setFrameSize(64, 64);
	m_anim.addSequence("run", 0, 5, 0.5, true);
	m_anim.addSequence("idle", 6, 11, 0.5, true);
	m_anim.addSequence("jump", 3, 4, 0.5, false);
	
	m_anim.play("idle", true);

	

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

Player::~Player()
{

}

void Player::update(float deltaT)
{
	// Do logic here

	m_anim.update(deltaT);


	bool onGround = kage::Physics::getTouching(m_body, 1);
	auto vel = velocity();
	vel.x = 0;
	if (vel.x == 0, vel.y == 0)
	{
		m_anim.play("idle", false);
	}

	if (kage::Input::isKeyDown(sf::Keyboard::Left))
	{
		m_sprite->setScale(-1, 1);
		vel.x = -6;
		if(fabs(vel.y) < 0.01)
		{
			m_anim.play("run", false);
		}
	}

	if (kage::Input::isKeyDown(sf::Keyboard::Right))
	{
		m_sprite->setScale(1, 1);
		vel.x = 6;
		if (fabs(vel.y) < 0.01)
		{
			m_anim.play("run", false);
		}
	}

	if (kage::Input::isKeyPressed(sf::Keyboard::Space))
	{
		if (onGround && !doubleJump)
		{
			vel.y = -8;
			m_anim.play("jump", true);	
		}
		if (onGround && doubleJump || counter < 1)
		{
			vel.y = -8;
			m_anim.play("jump", true);
			counter++;
		}
		if (onGround && doubleJump && counter > 0)
		{
			counter = 0;
		}
		
		
	}

	velocity(vel);

	//auto rabbit = kage::World::findByTag("Rabbit");
	//kf::Vector2 diff = rabbit->position() - position();
	//diff = diff * kf::Vector2(1, 1.777);
	//float zoom = length(diff) / 12;

	kage::World::setView(App::getWindow(), position(), 1);
	
}

void Player::onCollision(GameObject *obj)
{
	if (obj->m_tags.has("ManaOrb"))
	{
		//m_dead = true;
		doubleJump = true;
		counter = 0;
		obj->m_dead = true;
			// kills the other object
	}
}

void Player::onCollision(b2Fixture *fix)
{
	//if ((int)(fix->GetUserData()) == 1234) // Fake ID value 1234
	//{
	//}
}

#pragma region Optional
//void Player::onCollisionStop(GameObject* obj)
//{
//}

//void Player::onCollisionStop(b2Fixture* fix)
//{
//}

//void Player::render(sf::RenderTarget& rt)
//{
//	// Do custom rendering here. Not normally needed.
//}
#pragma endregion
