#include "grid.hpp"
#include "raylib.h"
#define Da 1.0
#define Db 0.5
#define f 0.018
#define k 0.051


void Grid::draw()
{
	for (int row = 0;row < rows;row++) {
		for (int column = 0;column < columns;column++) {
			/*float B = cells[row][column].B;
			unsigned char c = (B > 0.3f) ? 255 : 0;

			Color color = { c, c, c, 255 };
			//Color color = cells[row][column].A ? Color{ 0,255,0,255 } : Color{ 55,55,55,255 };
			DrawRectangle(column * cellSize, row * cellSize, cellSize - 1, cellSize - 1, color);*/
			// Calculate grayscale color based on concentrations
			int color = clamp(255 - 255 * (cells[row][column].A - cells[row][column].B), 0, 255);
			Color cellColor = { color, color, color, 255 };

			// Draw rectangle representing each cell
			DrawRectangle(row * cellSize, column * cellSize, cellSize, cellSize, cellColor);
		}
	}
}

void Grid::update()
{
	for (int row = 0;row < rows;row++) {
		for (int column = 0;column < columns;column++) {
			auto a = cells[row][column].A;
			auto b = cells[row][column].B;
			temp[row][column].A = clamp(a + (Da * laplac(row, column, 'a')) - a * b * b + f * (1 - a),0,1);
			temp[row][column].B = clamp(b + (Db * laplac(row, column, 'b')) + a * b * b - b * (k + f),0,1);
		}
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cells[i][j] = temp[i][j];
			//temp[i][j] = { 1.0, 0.0 };
		}
	}

}

float Grid::laplac(int x, int y, char c)
{
	int l = (x == 0) ? rows - 1 : x - 1;
	int r = (x == rows - 1) ? 0 : x + 1;
	int up= (y == 0) ? columns - 1 : y - 1;
	int down= (y == columns - 1) ? 0 : y + 1;

	float sum = 0.0f;

	switch (c) {
	case 'a':
		sum-= cells[x][y].A;
		sum += 0.2 * (cells[x][up].A + cells[x][down].A + cells[l][y].A + cells[r][y].A);
		sum += 0.05 * (cells[l][up].A + cells[l][down].A + cells[r][up].A + cells[r][down].A);
		return sum;
	case 'b':
		sum -= cells[x][y].B;
		sum += 0.2 * (cells[x][up].B + cells[x][down].B + cells[l][y].B + cells[r][y].B);
		sum += 0.05 * (cells[l][up].B + cells[l][down].B + cells[r][up].B + cells[r][down].B);
		return sum;
	}
}

void Grid::mouseactions() {
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		int x = GetMouseX() / cellSize;
		int y = GetMouseY() / cellSize;
		int size = 3;
		cells[x][y]= { 1.0f, 1.0f };
		/*for (int i = -size; i <= size; i++) {
			for (int j = -size; j <= size; j++) {
				int nx = y + i;
				int ny = x + j;

				if (nx >= 0 && nx < rows && ny >= 0 && ny < columns) {
					cells[nx][ny] = { 1.0f, 1.0f };
				}
			}
		}*/
	}
}

float Grid::clamp(float value, double low, double high)
{
	return value > high ? high : (value < low ? low : value);
	return 0.0f;
}
