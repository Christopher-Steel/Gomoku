#include "TextSystem.h"

void							TextSystem::update(sf::RenderWindow *window, World &world)
{
	for (unsigned int i = 0; i < world.entityCount; ++i)
	{
		TextComponent			*txt = world.textComponents[i];
		TransformComponent		*xform = world.transformComponents[i];

		if (txt && xform)
		{
			sf::Text			text;

			text.setFont(*txt->font);
			text.setColor(txt->color);
			text.setString(txt->string);
			text.setCharacterSize(txt->size);

			if (txt->highlighted)
			{
				text.scale(1.2f, 1.2f);
				text.setColor(sf::Color(sf::Color(255, 255, 255, 255)));
			}

			if (txt->centered)
			{
				sf::FloatRect	bounds = text.getGlobalBounds();
				sf::Vector2f	position;

				position.x = window->getSize().x / 2.0f;
				position.x -= (bounds.left + bounds.width) / 2.0f;

				text.setPosition(position);
			}

			sf::RenderStates	states;

			states.transform = xform->transform;
			window->draw(text, states);
		}
	}
}