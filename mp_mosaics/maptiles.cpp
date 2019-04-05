/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
		int row = theSource.getRows();
		int column = theSource.getColumns();
		std::vector<Point<3>> points;
		std::map<Point<3>, TileImage*> map;
		MosaicCanvas* canvas = new MosaicCanvas(row, column);

		for (size_t i = 0; i < theTiles.size(); i++) {
			Point<3> avgColor = convertToXYZ(theTiles[i].getAverageColor());
			map[avgColor] = &theTiles[i];
			points.push_back(avgColor);
		}

		KDTree<3> tiles(points);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				Point<3> sourcePoint = convertToXYZ(theSource.getRegionColor(i, j));
				Point<3> tile = tiles.findNearestNeighbor(sourcePoint);
				canvas->setTile(i, j, map[tile]);
			}
		}

    return canvas;
}
