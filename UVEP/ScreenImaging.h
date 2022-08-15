#pragma once
#include "../UVEP/head.h"
#include "../UVEP/VUCO.h"
#include "../UVEP/RPoint.h" // VITAL
// IPixel holds RGB values as unsigned char
class IPixel {
public:
	unsigned char r, g, b; // 1 single byte of info, 0 to 255

	IPixel();
	IPixel(unsigned char r_ele, unsigned char g_ele, unsigned char b_ele);
	IPixel( unsigned long hex_ele );
	IPixel( float r_ele, float g_ele, float b_ele );
	IPixel( int r_ele, int g_ele, int b_ele );
	// https://stackoverflow.com/questions/28705030/c-header-implementation-file-and-overloaded-operators
	// https://cplusplus.com/doc/tutorial/typecasting/
	// conversion from A (constructor):


	//IPixel(const RPixel& x);
	// conversion from A (assignment):
	//IPixel& operator= (const RPixel& x);
	// conversion to A (type-cast operator)
	//operator RPixel();
};

// Holds IPixels in XY grid
class ScreenRaster {
public:
	// Y Dimension
	int height = 0;
	// X Dimension
	int width = 0;
	// screen.grid [X] [Y]
	std::vector<std::vector<IPixel>> grid;
	// Initializes blackscreen with given dimensions
	ScreenRaster(int width_ele, int height_ele);

	void RGB_ScreenRaster(int width_ele, int height_ele);

	void RenderPixel(int x_loc, int y_loc, const IPixel* px);

	void RenderPixel(const RPoint* pos, const IPixel* px);

	void SimpleView();

};
class Image {
public:
	int m_width;
	int m_height;
	std::vector<IPixel> m_colors;

	Image(int width, int height);
	IPixel GetColor(int x, int y) const;
	void SetColor(const IPixel& color, int x, int y);
	void Export(const char* path);
	void MapRaster(ScreenRaster& screen);
};

std::pair<float, float> MakeSlope
(const RPoint* point_A, const RPoint* point_B, const int number_of_steps);
void DrawScanLine
(int y, std::pair<float, float>& left, std::pair<float, float>& right,
	ScreenRaster& screen, const IPixel* px);
void RasterizeTriangle_rewrite
(const RPoint* p0, const RPoint* p1, const RPoint* p2,
	ScreenRaster& screen, const IPixel* px_color);
// Go through list of verticies and rasterize them on screen
void DrawPolygon(RPoly* poly, const IPixel* color, ScreenRaster& screen);
/*
void DrawPolygon(
	std::array<int, 2>p0,
	std::array<int, 2>p1,
	std::array<int, 2>p2)
{
	using SlopeData = std::pair<float , float>;
	RasterizeTriangle(
		&p0, &p1, &p2,
		// GetXY: Retrieve std::tuple<int,int> or std::array<int,2> from a point
		[&](const auto& p) { return p; },
		// Slope generator
		[&](const auto* from, const auto* to, int num_steps)
		{
			// rretrive X coord for begin and end
			int begin = (*from)[0], end = (*to)[0];
			// Number of steps = number of scanlines
			float inv_step = 1.f / num_steps;
			return SlopeData{ begin,			// begin here
				(end - begin) * inv_step };		// Stepsize
		}
		// Scanline funct
			[&](int y, SlopeData& left, SlopeData& right)
		{
			int x = left.first, endx = right.first;
			for (; x < endx; ++x) {
				Plot(x, y);		// Render each pixel
			}
			// after scnaline is drawn, update X coord on both sides
			left.first += left.second;
			right.first += right.second;
		}
		);
}
*/
