#include "ComponentFactory.h"

RenderComponent					*ComponentFactory::createRenderComponent(const sf::Texture * const tex,
	const unsigned int plane,
	const sf::Color &color)
{
	RenderComponent				*render = new RenderComponent();

	render->texture = tex;
	render->vertices = sf::VertexArray(sf::Quads, 4);
	render->color = color;
	render->plane = plane;

	return (render);
}

TransformComponent				*ComponentFactory::createTransformComponent(const sf::Vector2f &size,
	const sf::Vector2f &pos,
	const sf::Vector2f &sca,
	const float rot)
{
	TransformComponent			*xform = new TransformComponent();


	xform->size = size;
	xform->position = pos;
	xform->scale = sca;
	xform->rotation = rot;
	xform->origin = sf::Vector2f();

	return (xform);
}

TextComponent					*ComponentFactory::createTextComponent(const std::string &string,
	const sf::Font * const font,
	bool centered,
	bool highlighted,
	const unsigned int size,
	const sf::Color &color)
{
	TextComponent				*txt = new TextComponent();

	txt->string = string;
	txt->font = font;
	txt->centered = centered;
	txt->highlighted = highlighted;
	txt->size = size;
	txt->color = color;

	return (txt);
}