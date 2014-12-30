#include "TimerSystem.h"

void							TimerSystem::update(World &world, const sf::Time &elapsed)
{
	for (unsigned int i = 0; i < world.entityCount; ++i)
	{
		TimerComponent			*timer = world.timerComponents[i];

		if (timer)
		{
			timer->countdown -= elapsed;
			if (timer->countdown <= sf::Time::Zero)
			{
				InfoComponent	*info = world.infoComponents[i];

				if (info)
					info->dead = true;
			}
		}
	}
}