#include "EndCollider.h"
#include "app.h"

EndCollider::EndCollider()
{
	m_sprite = kage::TextureManager::getSprite("data/empty.png");
	kage::centreOrigin(m_sprite);
	m_tags.add("EndCollider");

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

EndCollider::~EndCollider()
{

}

void EndCollider::update(float deltaT)
{
	// Do logic here
	//if (isFinished)
	//{
	//	//isFinsihed = false;
	//	App::setState(GameState::e_editor);
	//	isFinished = false;
	//	return;
	//}
}

void EndCollider::onCollision(GameObject *obj)
{
	if (obj->m_tags.has("Player"))
	{
		//isFinished = true;
		//App::setState(GameState::e_editor);
		//return;



		//m_dead = true;		// kills itself
		obj->m_dead = true;	// kills the other object
	}
}

void EndCollider::onCollision(b2Fixture *fix)
{
	//if ((int)(fix->GetUserData()) == 1234) // Fake ID value 1234
	//{
	//}
}

#pragma region Optional
//void EndCollider::onCollisionStop(GameObject* obj)
//{
//}

//void EndCollider::onCollisionStop(b2Fixture* fix)
//{
//}

//void EndCollider::render(sf::RenderTarget& rt)
//{
//	// Do custom rendering here. Not normally needed.
//}
#pragma endregion
