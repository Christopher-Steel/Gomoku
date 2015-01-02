#pragma once

#include <vector>

#include "ComponentFactory.h"

class									World
{
public:
	World();
	~World();

	const unsigned int					createEmptyEntity();

	void								destroyEntity(const unsigned int id);

	void								addRenderComponent(const unsigned int id, RenderComponent *render);
	void								addTransformComponent(const unsigned int id, TransformComponent *xform);
	void								addTextComponent(const unsigned int id, TextComponent *text);

	void								removeRenderComponent(const unsigned int id);
	void								removeTransformComponent(const unsigned int id);
	void								removeTextComponent(const unsigned int id);

	unsigned int						entityCount;

	std::vector<RenderComponent *>		renderComponents;
	std::vector<TransformComponent *>	transformComponents;
	std::vector<TextComponent *>		textComponents;
private:

	const unsigned int					findEmptySlot();
};