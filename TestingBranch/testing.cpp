#include "../UVEP/head.h"
#include "../UVEP/functions.h"
//#include "../UVEP/globals.h"
#include "../UVEP/classes.h"
#include "../UVEP/VUCO.h"
#include "../UVEP/ScreenImaging.h"
#include "../UVEP/RPoint.h"

//#include "cell_class.h" // https://www.learncpp.com/cpp-tutorial/class-code-and-header-files/
#include <utility>
#include <type_traits>


DWORD WINAPI CheckEscape(LPVOID lpParam) {
	while (GetAsyncKeyState(VK_ESCAPE) == 0) {
		//sleep 
		Sleep(10);
	}
	exit(0);

}


// YOUTUBE LINKS
/*
// https://www.youtube.com/watch?v=vqT5j38bWGg&ab_channel=DesignedbyHugo
// https://upload.wikimedia.org/wikipedia/commons/7/75/BMPfileFormat.svg
// https://www.youtube.com/watch?v=PahbNFypubE&t=675s&ab_channel=Bisqwit
// https://www.youtube.com/watch?v=hxOw_p0kLfI&ab_channel=Bisqwit
// https://www.youtube.com/watch?v=EnKZnwbgn-U&list=PL3WoIG-PLjSsg1Gwy5Lv--y5b3MDg47rd&ab_channel=QuantitativeBytes
// https://stackoverflow.com/questions/60231780/display-a-bitmap-in-opengl
// https://stackoverflow.com/questions/2785612/c-what-does-the-colon-after-a-constructor-mean
// https://stackoverflow.com/questions/15999123/const-before-parameter-vs-const-after-function-name-c
*/
// https://softwareengineering.stackexchange.com/questions/329709/python-style-keyword-args-in-c-good-practice-or-bad-idea


int main() {


	std::cout << "Program Start\n";
	CreateThread(NULL, 0, CheckEscape, NULL, 0, NULL);


	/* #########################################
	const int width = 5632;
	const int height = 2048;

	ScreenRaster temp(width, height);
	Image image(width, height);

	RPoint TopMid(width*0.5, height);
	RPoint BotLeft(0, height*0.5);
	RPoint BotRight(width, height*0.5);

	RPoint BottomLeftMid(width * 0.25, 0);
	RPoint BottomRightMid(width * 0.75, 0);

	RPoly T1;
	RPoly T2;
	RPoly T3;

	T1.points.push_back(TopMid);
	T1.points.push_back(BotLeft);
	T1.points.push_back(BotRight);

	T2.points.push_back( TopMid );
	T2.points.push_back(BottomLeftMid);
	T2.points.push_back(BottomRightMid);

	//IPixel cyan_pix(0,250,250);
	
	IPixel red_pix( 1.0f, 0.0f, 0.0f );

	IPixel green_pix( 0x00FF00 );
	######################################### */


	//red_pix = cyan_pix;

	//RasterizeTriangle_rewrite(&TopMid, &BotLeft, &BotRight, temp, &red_pix);

// TODO: Given a set of points on a convex polygon, order them based on distance to the next point. It does not matter which point starts
		/* ######################################################
				std::cout << "\nDrawing Polygon";
	
				DrawPolygon( &T1, &red_pix, temp );
				//DrawPolygon( &T2, &green_pix, temp );

				//red_pix.b = 1.0f;
				//red_pix.g = 1.0f;
				//temp.RenderPixel(19, 19, &red_pix);

				//temp.SimpleView();
				std::cout << "\nEmplacing in image";
				image.MapRaster( temp );

				std::cout << "\nCreating file...";
				image.Export( "example_image.bmp" );

		###################################################### */


	EnsureDirectory( "AZGAAR" );
	EnsureDirectory( "AZGAAR/PLACE_NAMEBASE_HERE" );
	std::string wanted_file = "AZGAAR/PLACE_NAMEBASE_HERE/namebases.txt";
	std::vector<std::string> all_lines;
	try {
		std::cout << "\nReading from file...";
		all_lines = ReadFromLineByLine( wanted_file );
	}
	catch (std::runtime_error e) {
		std::cerr << e.what();
	}
	catch (...) {
	}
	std::cout << "...File was read" << std::endl;
	// For each item in all_lines

	std::vector<culture_namebase> all_namebases;
	NamebaseParse( all_lines, all_namebases );

	std::vector<std::string> word_list = {
		"John",
		"Steve",
		"Michael",
		"Josh",
		"Joana",
		"Juan",
		"Ezekiel",
		"Mike"
	};
	VUCO( "name make", "Beginning to construct namebase..." );
	culture_namebase Bible_Names;
	Bible_Names.fn_AzgaarNamebaseGeneration( word_list );
	std::cout << "\n Returned word: " << Bible_Names.fn_MakeWordAzgaar(5, 12, "");
	std::cout << "\n Returned word: " << Bible_Names.fn_MakeWordAzgaar( 5, 12, "" );
	std::cout << "\n Returned word: " << Bible_Names.fn_MakeWordAzgaar( 5, 12, "" );
	std::cout << "\n Returned word: " << Bible_Names.fn_MakeWordAzgaar( 5, 12, "" );

	std::cout << '\n' << all_namebases[0].name << std::endl;
	std::cout << "\n Returned word: " << all_namebases[0].fn_MakeWordAzgaar( 5, 12, "" );
	std::cout << "\n Returned word: " << all_namebases[0].fn_MakeWordAzgaar( 5, 12, "" );
	std::cout << "\n Returned word: " << all_namebases[0].fn_MakeWordAzgaar( 5, 12, "" );
	std::cout << "\n Returned word: " << all_namebases[0].fn_MakeWordAzgaar( 5, 12, "" );

	std::cout << '\n' << all_namebases[2].name << std::endl;
	std::cout << "\n Returned word: " << all_namebases[2].fn_MakeWordAzgaar( 5, 12, "" );
	std::cout << "\n Returned word: " << all_namebases[2].fn_MakeWordAzgaar( 5, 12, "" );
	std::cout << "\n Returned word: " << all_namebases[2].fn_MakeWordAzgaar( 5, 12, "" );
	std::cout << "\n Returned word: " << all_namebases[2].fn_MakeWordAzgaar( 5, 12, "" );

	std::cout << '\n' << all_namebases[4].name << std::endl;
	std::cout << "\n Returned word: " << all_namebases[4].fn_MakeWordAzgaar( 5, 12, "" );
	std::cout << "\n Returned word: " << all_namebases[4].fn_MakeWordAzgaar( 5, 12, "" );
	std::cout << "\n Returned word: " << all_namebases[4].fn_MakeWordAzgaar( 5, 12, "" );
	std::cout << "\n Returned word: " << all_namebases[4].fn_MakeWordAzgaar( 5, 12, "" );


	std::cout << '\n' << all_namebases[6].name << std::endl;
	std::cout << "\n Returned word: " << all_namebases[6].fn_MakeWordAzgaar( 5, 12, "" );
	std::cout << "\n Returned word: " << all_namebases[6].fn_MakeWordAzgaar( 5, 12, "" );
	std::cout << "\n Returned word: " << all_namebases[6].fn_MakeWordAzgaar( 5, 12, "" );
	std::cout << "\n Returned word: " << all_namebases[6].fn_MakeWordAzgaar( 5, 12, "" );


	//ScreenRaster holding(10, 10);

	// Option 1:
		// Assign a point (point_A here) order 0
		// Find dist between point_A and point_B
		// update point_B to be next point in poly.points vector
		// repeat find dist
		// continue until all points have their dist to point_A calculated
		// point with shortest dist gets order 1
		// repeat until all points have an order (order will be =  poly.points.size_of() - 1 )

	// Option 2:  https://math.stackexchange.com/questions/978642/how-to-sort-vertices-of-a-polygon-in-counter-clockwise-order
		// Find centroid (average of all points)
		// Find angle of each point with regards to centroid
		// sort according to angle


	// GeoJSON coordinates are longitude and lattitude
	// So the MAX corners: 
				/*
				-180, 90				180,90		



				-180, -90				180, -90
	
				*/
	// AZGAAR maps these depending on world location ( CONFIGURE WORLD -> WORLD COVERAGE)
	// So an exported map may not fill the world, it may just be a small subsection in the middle
	// But it can also go over the max
	// Find the top most and bottom most points, find vertical expansion factor to get to GeoJSON extremes 
	// Find left most and right most points, find horizontal expansion factor to get to GeoJSON extremes
	// Do the finding of the xy-most points while reading in from AZGAAR, then calculate the x and y expansion factors, and then apply the stretch

	// Then, want to add 180 to all horizontal positions
	// Add 90 to all vertical positions
	// So there should be two points (prolly) that have one coordinate value with 0, and NO coordinate value should be negative
	// Doing all this, and if the values were saved as ints, the resulting maxes should be:
				/*
				0,18000							36000,18000





				0,0								36000, 0			
				
				*/
	// Which then needs mapped to 
	// vanilla map is 5623 x 2048
	// Here would be a good place to use the GUI as an option
	//If you still need to change the map size, it's set in map/default.map. The values have to be multiples of 128, and heightmap.bmp, provinces.bmp, rivers.bmp and terrain.bmp all need to have that exact size, while world_normal.bmp and the colormaps need to have half that size.
				/*
				0, 2048								5632,2048



				0,0									5632,0
				
				
				*/




	// TGA CREATION: 128x128
	// ARMORIA SETTINGS: HUGE GALLEY, 1.3 SCALE , SHIELD > SIMPLE > NO 
	// -> Output is PNG file where each is about 128x128 from bottom left
	// Ask user to make several batches and store somewhere, then iterate through all PNG and then convert to TGAs
	// Try and assign TGA's to specific areas (like Batch1 could be for Europe




	std::cout << "\nProgram Finish" << std::endl;
	return 0;
}