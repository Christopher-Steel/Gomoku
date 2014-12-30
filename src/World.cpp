#include "World.h"

World::World() :
entityCount(0)
{
}

World::~World()
{
	for (unsigned int i = 0; i != entityCount; ++i)
	{
		this->removeAnimationComponent(i);
		this->removeChildrenComponent(i);
		this->removeCollisionComponent(i);
		this->removeEmitterComponent(i);
		this->removeParentComponent(i);
		this->removeMovementComponent(i);
		this->removeParticleComponent(i);
		this->removeRenderComponent(i);
		this->removeProjectileComponent(i);
		this->removeScrollComponent(i);
		this->removeSpinComponent(i);
		this->removeTextComponent(i);
		this->removeTransformComponent(i);
		this->removeWeaponComponent(i);
		this->removeInfoComponent(i);
		this->removeGrowComponent(i);
		this->removeTimerComponent(i);
	}
}

const unsigned int						World::createParticleEffect(const unsigned int maxParticleCount,
	const bool respawn,
	const sf::Texture * const texture,
	const sf::Vector2f &position,
	const sf::Vector2f &scale)
{
	unsigned int						emitterId;
	std::set<unsigned int>				particleId;

	emitterId = this->createEmptyEntity();
	this->addEmitterComponent(emitterId, ComponentFactory::createEmitterComponent(respawn));
	this->addTransformComponent(emitterId, ComponentFactory::createTransformComponent(sf::Vector2f(), position));

	for (unsigned int i = 0; i != maxParticleCount; ++i)
	{
		unsigned int					id;

		id = this->createEmptyEntity();
		this->addRenderComponent(id, ComponentFactory::createRenderComponent(texture, RenderComponent::Plane::PARTICLE));
		this->addTransformComponent(id, ComponentFactory::createTransformComponent(sf::Vector2f(texture->getSize()), position, scale));
		this->addMovementComponent(id, ComponentFactory::createMovementComponent(50.0f, sf::Vector2f(1.0f, 0.0f)));
		this->addParticleComponent(id, ComponentFactory::createParticleComponent(sf::Time::Zero, emitterId));
		this->addParentComponent(id, ComponentFactory::createParentComponent(emitterId, 0.75f));

		particleId.insert(id);
	}

	this->addChildrenComponent(emitterId, ComponentFactory::createChildrenComponent(particleId, 0.75f));
	this->emitterComponents[emitterId]->particleId = particleId;

	return (emitterId);
}

const unsigned int						World::createEmptyEntity()
{
	unsigned int						id;

	if ((id = this->findEmptySlot()) == entityCount)
	{

		renderComponents.push_back(NULL);
		animationComponents.push_back(NULL);
		transformComponents.push_back(NULL);
		movementComponents.push_back(NULL);
		spinComponents.push_back(NULL);
		emitterComponents.push_back(NULL);
		particleComponents.push_back(NULL);
		textComponents.push_back(NULL);
		collisionComponents.push_back(NULL);
		scrollComponents.push_back(NULL);
		projectileComponents.push_back(NULL);
		weaponComponents.push_back(NULL);
		parentComponents.push_back(NULL);
		childrenComponents.push_back(NULL);
		growComponents.push_back(NULL);
		timerComponents.push_back(NULL);

		return (entityCount++);
	}

	return (id);
}

const unsigned int						World::findEmptySlot()
{
	for (unsigned int i = 0; i < entityCount; ++i)
	{
		if (!renderComponents[i] &&  !transformComponents[i] && !textComponents[i] && !parentComponents[i] && !childrenComponents[i] && !growComponents[i] && !timerComponents[i])
			return (i);
	}

	return (entityCount);
}

void									World::destroyEntity(const unsigned int id)
{
	ParentComponent						*parent = parentComponents[id];
	ChildrenComponent					*children = childrenComponents[id];

	if (parent)
	{
		ChildrenComponent				*parentChildren = childrenComponents[parent->id];

		parentChildren->id.erase(id);
	}

	if (children)
	{
		for (std::set<unsigned int>::iterator it = children->id.begin(); it != children->id.end(); ++it)
			this->destroyEntity(*it);
	}

	this->removeRenderComponent(id);
	this->removeChildrenComponent(id);
	this->removeParentComponent(id);
	this->removeTextComponent(id);
	this->removeTransformComponent(id);
	this->removeTimerComponent(id);

	if (id == entityCount - 1)
	{
		renderComponents.pop_back();
		childrenComponents.pop_back();
		parentComponents.pop_back();
		textComponents.pop_back();
		transformComponents.pop_back();
		timerComponents.pop_back();
		--entityCount;
	}
}

void									World::addRenderComponent(const unsigned int id, RenderComponent *render)
{
	renderComponents[id] = render;
}

void									World::addTransformComponent(const unsigned int id, TransformComponent *xform)
{
	transformComponents[id] = xform;
}

void									World::addTextComponent(const unsigned int id, TextComponent *text)
{
	textComponents[id] = text;
}

void									World::addParentComponent(const unsigned int id, ParentComponent *parent)
{
	parentComponents[id] = parent;
}

void									World::addChildrenComponent(const unsigned int id, ChildrenComponent *children)
{
	childrenComponents[id] = children;
}

void									World::addTimerComponent(const unsigned int id, TimerComponent *timer)
{
	timerComponents[id] = timer;
}

void									World::removeRenderComponent(const unsigned int id)
{
	if (renderComponents[id])
	{
		delete (renderComponents[id]);
		renderComponents[id] = NULL;
	}
}

void									World::removeTransformComponent(const unsigned int id)
{
	if (transformComponents[id])
	{
		delete (transformComponents[id]);
		transformComponents[id] = NULL;
	}
}

void									World::removeTextComponent(const unsigned int id)
{
	if (textComponents[id])
	{
		delete (textComponents[id]);
		textComponents[id] = NULL;
	}
}

void									World::removeParentComponent(const unsigned int id)
{
	if (parentComponents[id])
	{
		delete (parentComponents[id]);
		parentComponents[id] = NULL;
	}
}

void									World::removeChildrenComponent(const unsigned int id)
{
	if (childrenComponents[id])
	{
		delete (childrenComponents[id]);
		childrenComponents[id] = NULL;
	}
}

void									World::removeTimerComponent(const unsigned int id)
{
	if (timerComponents[id])
	{
		delete (timerComponents[id]);
		timerComponents[id] = NULL;
	}
}