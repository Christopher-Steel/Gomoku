#include "TransformSystem.h"

void							TransformSystem::update(World &world, const sf::Vector2u &screenSize)
{
	for (unsigned int i = 0; i < world.entityCount; ++i)
	{
		if (world.transformComponents[i])
		{
			computeTransform(i, world);
		}
	}
}

// void							TransformSystem::applyScroll(const unsigned int id, World &world, const sf::Time &elapsed)
// {
// 	TransformComponent			*xform = world.transformComponents[id];
// 	ScrollComponent				*scroll = world.scrollComponents[id];

// 	if (scroll)
// 		xform->position += scroll->direction * scroll->speed * elapsed.asSeconds();
// }

// bool							TransformSystem::applyMovement(const unsigned int id, World &world, const sf::Time &elapsed, const sf::Vector2u &screenSize)
// {
// 	TransformComponent			*xform = world.transformComponents[id];
// 	MovementComponent			*mov = world.movementComponents[id];

// 	if (mov)
// 	{
// 		sf::Vector2f			movement;
// 		float					length;

// 		movement = mov->direction;
// 		length = sqrt(movement.x * movement.x + movement.y * movement.y);
// 		if (length != 0.0f)
// 			movement /= length;
// 		movement *= mov->velocity * elapsed.asSeconds();
// 		xform->position += movement;
// 		//if (xform->position.x <= -500.0f || xform->position.x >= screenSize.x + 500.0f)
// 		//{
// 		//	world.destroyEntity(id);
// 		//	return (false);
// 		//}

// 		updateChildren(id, world, movement);
// 	}
// 	return (true);
// }

// void							TransformSystem::applySpin(const unsigned int id, World &world, const sf::Time &elapsed)
// {
// 	TransformComponent			*xform = world.transformComponents[id];
// 	SpinComponent				*spin = world.spinComponents[id];

// 	if (spin)
// 	{
// 		float					spinValue = spin->direction * spin->speed * elapsed.asSeconds();

// 		xform->rotation += spinValue;

// 		updateChildren(id, world, spinValue);
// 	}
// }

// void							TransformSystem::applyGrow(const unsigned int id, World &world, const sf::Time &elapsed)
// {
// 	TransformComponent			*xform = world.transformComponents[id];
// 	GrowComponent				*grow = world.growComponents[id];

// 	if (grow)
// 	{
// 		sf::Vector2f			growValue = grow->direction * grow->speed * elapsed.asSeconds();

// 		xform->size += growValue;
// 		if (grow->limit.x != 0.0f && xform->size.x > grow->limit.x)
// 			xform->size.x = grow->limit.x;
// 		if (grow->limit.y != 0.0f && xform->size.y > grow->limit.y)
// 			xform->size.y = grow->limit.y;
// 	}
// }

// void							TransformSystem::updateChildren(const unsigned int id, World &world, const sf::Vector2f &movement)
// {
// 	ChildrenComponent			*children = world.childrenComponents[id];

// 	if (children)
// 	{
// 		for (std::set<unsigned int>::iterator it = children->id.begin(); it != children->id.end(); ++it)
// 		{
// 			TransformComponent	*xform = world.transformComponents[*children->id.find(*it)];

// 			if (xform)
// 			{
// 				xform->position += movement * children->degree;
// 				updateChildren(*children->id.find(*it), world, movement);
// 			}
// 		}
// 	}
// }

// void							TransformSystem::updateChildren(const unsigned int id, World &world, const float spinValue)
// {
// 	ChildrenComponent			*children = world.childrenComponents[id];

// 	if (children)
// 	{
// 		for (std::set<unsigned int>::iterator it = children->id.begin(); it != children->id.end(); ++it)
// 		{
// 			TransformComponent	*xform = world.transformComponents[*children->id.find(*it)];

// 			if (xform)
// 			{
// 				xform->rotation += spinValue * children->degree;
// 				updateChildren(*children->id.find(*it), world, spinValue);
// 			}
// 		}
// 	}
// }

void							TransformSystem::computeTransform(const unsigned int id, World &world)
{
	TransformComponent			*xform = world.transformComponents[id];

	xform->transform = sf::Transform::Identity;
	xform->transform.translate(xform->position);
	xform->transform.scale(xform->scale);
	xform->transform.rotate(xform->rotation, sf::Vector2f(xform->size.x / 2, xform->size.y / 2));
}