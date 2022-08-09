#include "classes.h"
// https://www.youtube.com/watch?v=ayfCxgVStdQ&ab_channel=JacobSorber
	void progressBar::update(int newProgress)
	{
		currentProgress += newProgress;
		if (currentProgress > items)
		{

			return;
		}
		amountOfFiller = pBarLength * ((double)currentProgress / items); // two int division returns int, MUST have one as a double to "upgrade" to double result

		std::cout << std::fixed << std::setprecision(0) << "\r" // bring cursor to start of line
			<< task << " "
			<< firstPartOfBar
			<< currentProgress << "/" << items << lastPartOfBar;
		std::cout << firstPartOfBar
			<< std::fixed << std::setprecision(1) << 100 * (double)currentProgress / items << "% ";

		for (int a = 0; a < amountOfFiller; a++)
		{ //Print out current progress
			std::cout << barFiller;
		}

		for (int b = 0; b < pBarLength - amountOfFiller; b++)
		{
			std::cout << barEmpty;
		}
		std::cout << lastPartOfBar;
		std::cout << std::flush;


	}
	void progressBar::updatePercent(double newPercent)
	{
		int increaseBy = newPercent * (items / 100);
		if ((increaseBy + currentProgress) > items)
		{
			return;
		}
		update(increaseBy);
	}
	void progressBar::reuse(int items1)
	{
		this->amountOfFiller = 0;

		this->currentProgress = 0;

		this->items = items1;

	}
	progressBar::progressBar(std::string task_ele, int elements)
	{
		task = task_ele;
		items = elements;
	}
	progressBar::progressBar(int elements)
	{
		items = elements;
	}
	progressBar::progressBar() {};



	void cell_info::add_coord(short x_coord, short y_coord) {
		this->verticies.push_back(std::make_tuple(x_coord, y_coord));
	}