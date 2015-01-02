#pragma once

#include "Components.h"

class							ComponentFactory
{
public:
	static RenderComponent		*createRenderComponent(const sf::Texture * const tex,
		const unsigned int plane = 0,
		const sf::Color &color = sf::Color::White);

	static TransformComponent	*createTransformComponent(const sf::Vector2f &size,
		const sf::Vector2f &pos,
		const sf::Vector2f &sca = sf::Vector2f(1.0f, 1.0f),
		const float rot = 0.0f);

	static TextComponent		*createTextComponent(const std::string &string,
		const sf::Font * const font,
		bool centered = false,
		bool hightlighted = false,
		const unsigned int size = 30,
		const sf::Color &color = sf::Color::White);
private:
	ComponentFactory();
};