#include "game_of_life.h"

bool game_of_life::slucajnaVrijednost()
{
    //generate random value from 0-4, return true if it is 0
    return std::rand() % 4 == 0;
}

bool game_of_life::celijaZauzeta(int i, int j) const
{
	return i >= 0 && i < REDAKA && j >= 0 && j < STUPACA && generacija[i][j];
}

game_of_life::game_of_life()
{
	//seed
	srand(time(nullptr));

	//generate starting configuration
	for (unsigned int i = 0; i < REDAKA; i++) 
    {
		for (unsigned int j = 0; j < STUPACA; j++)
			generacija[i][j] = slucajnaVrijednost();
	}
}

void game_of_life::slijedecaGeneracija()
{
    for (unsigned int i = 0; i < REDAKA; i++) 
    {
        for (unsigned int j = 0; j < STUPACA; j++) 
        {
            //number of neighbour cells
            int neighbors = 0;
            for (int ii = -1; ii <= 1; ii++) 
            {
                for (int jj = -1; jj <= 1; jj++) 
                {
                    if (!(ii == 0 && jj == 0) && celijaZauzeta(i + ii, j + jj))
                        neighbors++;
                    else continue;
                }
            }

            //apply rules of the game
            
            if ((generacija[i][j] && (neighbors == 2 || neighbors == 3)) || (!celijaZauzeta(i, j) && neighbors == 3))
                sljedecaGeneracija[i][j] = true;
            else
                sljedecaGeneracija[i][j] = false;
            /*
            1. a live cell with 2 or 3 live neighbors survives to the next generation
            2. if a cell does not have 2 or 3 live neighbors, it dies
            3. a dead cell with exactly 3 live neighbors becomes alive in the next generation
            */
        }
    }

    //copy the next generation to the current generation
    for (unsigned int i = 0; i < REDAKA; i++) 
    {
        for (unsigned int j = 0; j < STUPACA; j++)
            generacija[i][j] = sljedecaGeneracija[i][j];
    }
}

void game_of_life::iscrtaj() const
{
    for (unsigned int i = 0; i < REDAKA; i++) 
    {
        for (unsigned int j = 0; j < STUPACA; j++) 
        {
            if (generacija[i][j])
                std::cout << "* ";
            else
                std::cout << "- ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void game_of_life::draw(sf::RenderWindow& window) const
{
    for (unsigned int i = 0; i < REDAKA; i++) 
    {
		for (unsigned int j = 0; j < STUPACA; j++)
		{
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(j * cellSize, i * cellSize);
            cell.setFillColor(generacija[i][j] ? aliveCell : deadCell); //boja žive ili mrtve ćelije
            cell.setOutlineColor(outline);
            cell.setOutlineThickness(1.f);
            window.draw(cell);

            //if the cell is alive, spawn a flower
            if (generacija[i][j])
            {
                sf::Color flowerColor = flowerColors[rand() % flowerColors.size()];
                for (int ii = 0; ii < 5; ii++)
                {
                    sf::CircleShape latice;
                    latice.setRadius(cellSize / 5);
                    latice.setFillColor(flowerColor); //give the flower random color
                    latice.setPosition(j * cellSize + cellSize / 2, i * cellSize + cellSize / 2); //center in the cell
                    latice.setRotation((ii + 1) * 72.f);
                    window.draw(latice);
                }

                sf::CircleShape shape;
                shape.setRadius(cellSize / 5);
                shape.setFillColor(sf::Color(255, 255, 0));
                shape.setPosition(j * cellSize + cellSize / 3.4, i * cellSize + cellSize / 3.4); //center in the cell
                window.draw(shape);
            }
		}
    }
}