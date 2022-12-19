#include "ScreenImaging.h"
#include "classes.h"

export module screens;

export ScreenRaster CreateHeightmap( std::vector<cell_info> all_cells) {
	ScreenRaster EU4_MAP( 5632, 2048 );
	int height = 0;
	for (int dp_itr = 0; dp_itr < all_cells.size() - 1; dp_itr++) {
		height = all_cells[dp_itr].height;	// -	// Ranges from -3248ft to 22061ft (or 0 to 100 where ~20 is sealevel, but its saved as -3248 to 22061)
	// Lowest is [0,0,0], sea level IS [94,94,94] (so values at 94 and below are "sea"), and [255,255,255] is highest. The heightmap.bmp file should be in Greyscale mode and saved as a 8-bit bitmap image file (.BMP).
		height += 3248;	// place into purely positive range of 0 to 25309
		height /= 99;	// place into purely positive range of 0 to 255.646, truncates
		IPixel color_rgb( height,height,height );

		RPoly temp_poly;
		temp_poly.points = all_cells[dp_itr].verticies;

		//temp_poly2.points = all_cells[dp_itr+1].verticies; // TEMP, ALSO CHANGE size()-1 to size()
		//temp_poly.MergePoly(temp_poly2);
		DrawPolygon( &temp_poly, &color_rgb, EU4_MAP );
	}
	return EU4_MAP;
}