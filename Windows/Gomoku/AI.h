/*

vector2u									getMove(Goban &goban)
{
	vector2u								move;
	map<vector2u, int>						results;

	for (every_adjacent_cell)
	{
		vector2u							position;

		position = adjacent_cell.position();

		for (uint i = 0; i != 100; ++i)
		{
			uint								simulationResult;

			results[position] = 0;
	
			if ((simulationResult = simulation(position, goban)) == 0) // WIN
			{
				++results[position];
			}

			else if (simulationResult == 1) // LOSE
			{
				--results[position];
			}
		}
	}

	move = get_best_move(results);

	return (move);
}

uint										simulation(vector2u move, Goban goban)
{
	uint									result;
	vector2u								position;

	position = move;

	while (!gameOver)
	{	
		goban.setPion(position);

		position.x = (rand() % (goban[max].x - goban[min].x)) + goban[min].x;
		position.y = (rand() % (goban[max].y - goban[min].y)) + goban[min].y;		
	}

	result = gameResult;

	return (result);
}







*/