#pragma once
#include <vector>

struct Cell {
	float A;
	float B;
};

class Grid {
public:
	Grid(int width, int height, int cellSize)
		: rows(height / cellSize), columns(width / cellSize), cellSize(cellSize),
		cells(rows, std::vector<Cell>(columns, { 1.0f,0.0f })),
		temp(rows, std::vector<Cell>(columns, { 1.0f,0.0f })) {
	};
	void draw();
	void update();
	float laplac(int x, int y, char c);
	void mouseactions();
	float clamp(float value, double low, double high);

private:
	int rows;
	int columns;
	int cellSize;
	std::vector<std::vector<Cell>> cells;
	std::vector<std::vector<Cell>> temp;
};
