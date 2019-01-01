#include "WallsGenerator.h"
#include "LevelGenerator.h"
#include "Room.h"


void WallsGenerator::generateSymetrical(LevelGenerator* levelGen, Room* room, FieldType fieldType) {
	int maxCulumnsInColumn = (room->y2 - room->y1) / (MIN_COLUMN_SPACE + MIN_COLUMN_SIZE) - 1;
	int maxCulumnsInRow = (room->x2 - room->x1) / (MIN_COLUMN_SPACE + MIN_COLUMN_SIZE) - 1;

	if (maxCulumnsInColumn < 1 || maxCulumnsInRow < 1)
		return;

	int numberOfRows = rand() % maxCulumnsInColumn + 1;

	if (numberOfRows % 2 && maxCulumnsInRow <= 1)
		numberOfRows--;
	if (numberOfRows < 1)
		return;

	std::vector<std::vector<int>> columnXPosition;
	columnXPosition.resize(numberOfRows / 2 + numberOfRows % 2); // Set number of rows

	std::vector<int> rowPositionY(numberOfRows / 2 + numberOfRows % 2);
	std::vector<PointInt> columnSize(numberOfRows / 2 + numberOfRows % 2);

	// Set number of columns in each row
	for (int row = 0; row < numberOfRows / 2; row++) {
		columnXPosition[row].resize(rand() % maxCulumnsInRow + 1);

		// Set width of columns in row
		int rowAdditionalSpace = room->x2 - room->x1 - 1 - (columnXPosition[row].size() * (MIN_COLUMN_SPACE + MIN_COLUMN_SIZE) + MIN_COLUMN_SPACE) - 2;
		int rowAdditionalSpaceBetweenCol = rowAdditionalSpace / (columnXPosition[row].size() + 1);
		int randSpace = 0;
		if (rowAdditionalSpaceBetweenCol > 0)
			randSpace = rand() % rowAdditionalSpaceBetweenCol;
		columnSize[row].x = MIN_COLUMN_SIZE + randSpace;
	}

	// Set number of columns in the middle row
	if (numberOfRows % 2) {
		int randNumber = rand() % maxCulumnsInRow + 1;

		if (randNumber == 1 && maxCulumnsInRow >= 2)
			randNumber = 2;
		else if (randNumber % 2)
			randNumber--;

		int row = numberOfRows / 2;
		columnXPosition[row].resize(randNumber);
		// Set width of columns in row
		int rowAdditionalSpace = room->x2 - room->x1 - 1 - (columnXPosition[row].size() * (MIN_COLUMN_SPACE + MIN_COLUMN_SIZE) + MIN_COLUMN_SPACE) - 2;
		int rowAdditionalSpaceBetweenCol = rowAdditionalSpace / (columnXPosition[row].size() + 1);
		int randSpace = 0;
		if (rowAdditionalSpaceBetweenCol > 0)
			randSpace = rand() % rowAdditionalSpaceBetweenCol;
		columnSize[row].x = MIN_COLUMN_SIZE + randSpace;
	}

	// Set height of columns in row
	for (auto it = columnSize.begin(); it != columnSize.end(); it++)
		(*it).y = MIN_COLUMN_SIZE;

	int columnAdditionalSpace = room->y2 - room->y1 - 1 - (numberOfRows * (MIN_COLUMN_SPACE + MIN_COLUMN_SIZE) + MIN_COLUMN_SPACE) - 2;
	int itAdditionalSpace = 0;
	while (itAdditionalSpace < columnAdditionalSpace) {
		if (rand() % 100 < 50) {
			int randNumber = rand() % columnXPosition.size();
			if (columnSize[randNumber].x / (float)columnSize[randNumber].y < COLUMN_MAX_WIDTH_TO_HEIGHT
				&& columnSize[randNumber].y / (float)columnSize[randNumber].x < COLUMN_MAX_HEIGHT_TO_WIDTH) { // Check max w/h && h/w ratio
				columnSize[randNumber].y++;
				if (randNumber == (columnXPosition.size() - 1))
					itAdditionalSpace++;
				else
					itAdditionalSpace += 2;
			}
			itAdditionalSpace += 2;
		}
		else
			itAdditionalSpace += 2;
	}

	// Set positions x in each row
	for (int row = 0; row < columnXPosition.size(); row++) {
		int totalColumnSizeX = columnSize[row].x * columnXPosition[row].size();

		int allSpaceBetweenCol = (room->x2 - room->x1 - 1 - totalColumnSizeX);
		int minSpaceBetweenColumns = (room->x2 - room->x1 - 1 - totalColumnSizeX) / (columnXPosition[row].size() + 1);
		for (int i = MIN_COLUMN_SPACE * (columnSize[row].x + 1); i < allSpaceBetweenCol; i += 2) { // Split space randomly
			if (rand() % columnXPosition[row].size() == 0)
				columnXPosition[row][rand() % columnXPosition[row].size() / 2]++;
		}

		columnXPosition[row][0] += MIN_COLUMN_SPACE + 1;
		for (int i = 1; i < columnXPosition[row].size(); i++)
			columnXPosition[row][i] += columnXPosition[row][i - 1] + columnSize[row].x + MIN_COLUMN_SPACE;

		int roomWidth = (room->x2 - room->x1 + 1);
		for (int i = columnXPosition[row].size() - 1; i > (columnXPosition[row].size() - 1) / 2; i--) // Miror left side to right side
			columnXPosition[row][i] = roomWidth - columnXPosition[row][(columnXPosition[row].size() - 1) - i] - columnSize[row].x;

		if (columnXPosition[row].size() % 2) { // Set x position to middle column in this row
			columnXPosition[row][columnXPosition[row].size() / 2] = (room->x2 - room->x1 + 1) / 2 - (columnSize[row].x) / 2;
			if ((columnSize[row].x) % 2 && (room->x2 - room->x1 + 1) % 2 == 0)
				columnXPosition[row][columnXPosition[row].size() / 2]--;
		}
	}

	// Set positions y
	int totalColumnSizeY = 0;
	for (int i = 0; i < columnSize.size(); i++)
		totalColumnSizeY += 2 * columnSize[i].y;

	if (numberOfRows % 2)
		totalColumnSizeY -= columnSize[columnSize.size() - 1].y;

	int minSpaceBetweenColumns = (room->y2 - room->y1 - 1 - totalColumnSizeY) / (numberOfRows + 1);
	int allSpaceBetweenCol = (room->y2 - room->y1 - 1 - totalColumnSizeY);
	for (int i = minSpaceBetweenColumns * (numberOfRows + 1); i < allSpaceBetweenCol; i += 2)
		rowPositionY[rand() % rowPositionY.size()]++;

	rowPositionY[0] += minSpaceBetweenColumns + 1;
	for (int i = 1; i < rowPositionY.size(); i++)
		rowPositionY[i] += rowPositionY[i - 1] + columnSize[i - 1].y + minSpaceBetweenColumns;

	if (numberOfRows % 2) { // Set y positions to middle row
		if ((room->y2 - room->y1 + 1) % 2 != columnSize[columnSize.size() - 1].y % 2)
			columnSize[columnSize.size() - 1].y++;

		rowPositionY[rowPositionY.size() - 1] = (room->y2 - room->y1 + 1) / 2 - (columnSize[rowPositionY.size() - 1].y) / 2;
	}

	// Set mapFields to wall where there is a column
	for (int row = 0; row < columnXPosition.size(); row++) {
		int y = rowPositionY[row];
		if (columnXPosition[row].size() % 2 && ((room->x2 - room->x1 + 1) % 2 != columnSize[row].x % 2)) { // Middle column + 1 width
			for (int col = 0; col < columnXPosition[row].size(); col++) {
				for (int yIt = 0; yIt < columnSize[row].y; yIt++) {
					if (col == columnXPosition[row].size() / 2) {
						for (int xIt = 0; xIt < columnSize[row].x + 1; xIt++) {
							levelGen->setMapFieldType(room->x1 + columnXPosition[row][col] + xIt, room->y1 + y + yIt, FieldType::Wall);
							if (!(row == rowPositionY.size() - 1 && numberOfRows % 2))
								levelGen->setMapFieldType(room->x1 + columnXPosition[row][col] + xIt, room->y2 - (y + yIt), FieldType::Wall);
						}
					}
					else {
						for (int xIt = 0; xIt < columnSize[row].x; xIt++) {
							levelGen->setMapFieldType(room->x1 + columnXPosition[row][col] + xIt, room->y1 + y + yIt, FieldType::Wall);
							if (!(row == rowPositionY.size() - 1 && numberOfRows % 2))
								levelGen->setMapFieldType(room->x1 + columnXPosition[row][col] + xIt, room->y2 - (y + yIt), FieldType::Wall);
						}
					}
				}
			}
		}
		else {
			for (int col = 0; col < columnXPosition[row].size(); col++) {
				for (int yIt = 0; yIt < columnSize[row].y; yIt++) {
					for (int xIt = 0; xIt < columnSize[row].x; xIt++) {
						levelGen->setMapFieldType(room->x1 + columnXPosition[row][col] + xIt, room->y1 + y + yIt, FieldType::Wall);
						if (!(row == rowPositionY.size() - 1 && numberOfRows % 2))
							levelGen->setMapFieldType(room->x1 + columnXPosition[row][col] + xIt, room->y2 - (y + yIt), FieldType::Wall);
					}
				}
			}
		}
	}
}

bool WallsGenerator::canPlaceWall(LevelGenerator* mapGen, RectInt wallRect) {
	for (int y = wallRect.y - MIN_WALL_RECT_SPACE; y < wallRect.y + MIN_WALL_RECT_SPACE + wallRect.h; y++) {
		for (int x = wallRect.x - MIN_WALL_RECT_SPACE; x < wallRect.x + MIN_WALL_RECT_SPACE + wallRect.w; x++) {
			if (mapGen->getMapFieldType(x, y) == FieldType::Door || mapGen->getMapFieldType(x, y) == FieldType::Wall
				|| mapGen->getMapFieldType(x, y) == FieldType::Abyss)
				return false;
		}
	}

	return true;
}

void WallsGenerator::placeWall(LevelGenerator* mapGen, RectInt wallRect, FieldType fieldType) {
	for (int y = wallRect.y; y < wallRect.y + wallRect.h; y++) {
		for (int x = wallRect.x; x < wallRect.x + wallRect.w; x++) { 
			mapGen->setMapFieldType(x, y, fieldType);
		}
	}
}

void WallsGenerator::generateConnectedToWall(LevelGenerator* levelGen, Room* room, FieldType fieldType) {
	int height = rand() % int(((room->y2 - room->y1) / 2) * 0.3) + 2;
	int maxWidth = int(((room->x2 - room->x1) / 2) * 0.3);

	int width = rand() % maxWidth + 2;
	if ((room->x2 - room->x1) % 2 == width % 2)
		width++;

	RectInt rectWallTop = { room->x1 + (room->x2 - room->x1) / 2 - width / 2 + (width + 1) % 2, room->y1 + 1, width, height }; // Wall middle top
	if (canPlaceWall(levelGen, rectWallTop))
		placeWall(levelGen, rectWallTop, fieldType);

	width = rand() % maxWidth + 2;
	if ((room->x2 - room->x1) % 2 == width % 2)
		width++;
	
	RectInt rectWallBottom = { room->x1 + (room->x2 - room->x1) / 2 - width / 2 + (width + 1) % 2, room->y2 - height - 1, width, height }; // Wall middle bottom
	if (canPlaceWall(levelGen, rectWallBottom))
		placeWall(levelGen, rectWallBottom, fieldType);
}

WallsGenerator::WallsGenerator() {

}


WallsGenerator::~WallsGenerator() {

}
