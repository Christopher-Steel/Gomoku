#include "World.h"

World::World() :
entityCount(0)
{
}

World::~World()
{
	for (unsigned int i = 0; i != entityCount; ++i)
	{
		this->removeRenderComponent(i);
		this->removeTextComponent(i);
		this->removeTransformComponent(i);
	}
}

const unsigned int						World::createEmptyEntity()
{
	unsigned int						id;

	if ((id = this->findEmptySlot()) == entityCount)
	{

		renderComponents.push_back(NULL);
		transformComponents.push_back(NULL);
		textComponents.push_back(NULL);

		return (entityCount++);
	}

	return (id);
}

const unsigned int						World::findEmptySlot()
{
	for (unsigned int i = 0; i < entityCount; ++i)
	{
		if (!renderComponents[i] &&  !transformComponents[i] && !textComponents[i])
			return (i);
	}

	return (entityCount);
}

void									World::destroyEntity(const unsigned int id)
{
	// ParentComponent						*parent = parentComponents[id];
	// ChildrenComponent					*children = childrenComponents[id];

	// if (parent)
	// {
	// 	ChildrenComponent				*parentChildren = childrenComponents[parent->id];

	// 	parentChildren->id.erase(id);
	// }

	// if (children)
	// {
	// 	for (std::set<unsigned int>::iterator it = children->id.begin(); it != children->id.end(); ++it)
	// 		this->destroyEntity(*it);
	// }

	this->removeRenderComponent(id);
	this->removeTextComponent(id);
	this->removeTransformComponent(id);

	// if (id == entityCount - 1)
	// {
	// 	renderComponents.pop_back();
	// 	textComponents.pop_back();
	// 	transformComponents.pop_back();
	// 	--entityCount;
	// }
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
