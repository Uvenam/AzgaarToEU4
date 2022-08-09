#pragma once
#include "head.h"
#include "VUCO.h"
// RPixel inherits all public members/methods of RPoint
class RPixel {
public:
	float r, g, b; // 1 single byte of info, 0 to 255


	RPixel()
		: r(0), g(0), b(0)
	{};
	RPixel(float r_ele, float g_ele, float b_ele)
		:r(r_ele), g(g_ele), b(b_ele)
	{};
	~RPixel()
	{};
};
class RPoint {
	// https://www.tutorialspoint.com/cplusplus/cpp_inheritance.htm
public:
	int x_pos, y_pos;
	RPoint()
		: x_pos(0), y_pos(0)
	{};
	RPoint(int x_value, int y_value)
		: x_pos(x_value), y_pos(y_value)
	{};

};
class RPoly {
public:
	std::vector<RPoint> points;
	void SortPoints() {

		// https://stackoverflow.com/questions/19713092/how-to-order-vertices-in-a-non-convex-polygon-how-to-find-one-of-many-solutions


		// make centroid
		RPoint centroid;
		// find # of elements in vector
		int psize = points.size();
		// sum all point x and y
		for (int pt_itr = 0; pt_itr < psize; pt_itr++) {
			centroid.x_pos += points[pt_itr].x_pos;
			centroid.y_pos += points[pt_itr].y_pos;
		}
		// get average of x and y, and place into centroid
		centroid.x_pos = centroid.x_pos / psize;
		centroid.y_pos = centroid.y_pos / psize;

		// Get an angle for each point and tie it to each point
		double ang;
		std::vector <std::tuple<double, RPoint>>  proper_order;
		for (int pt_itr = 0; pt_itr < psize; pt_itr++) {
			proper_order.push_back(
				std::make_tuple(
					std::atan2(points[pt_itr].y_pos - centroid.y_pos, points[pt_itr].x_pos - centroid.x_pos),
					points[pt_itr]
				)
			);
		}
		// Sort based on angle
		std::sort(proper_order.begin(), proper_order.end(),
			[](const std::tuple<double, RPoint>& pA, const std::tuple<double, RPoint>& pB)
			-> bool { return std::get<0>(pA) > std::get<0>(pB); }
		);
		// Replace RPoly.points vector with properly ordered vector
		for (int pt_itr = 0; pt_itr < psize; pt_itr++) {
			points[pt_itr] = std::get<1>(proper_order[pt_itr]);
		}




	}
};
class ScreenRaster {
public:
	int height = 0;
	int width = 0;

	std::vector<std::vector<RPixel>> grid;
	ScreenRaster(int width_ele, int height_ele)
		:height(height_ele), width(width_ele)
	{
		std::vector<RPixel> column;
		RPixel white_space(0.0f, 0.0f, 0.0f);
		for (int x = 0; x < width; x++) {
			grid.push_back(column);



			for (int y = 0; y < height; y++) {
				grid[x].push_back(white_space);



			}
		}
	};

	void RenderPixel(int x_loc, int y_loc, const RPixel* px) {

		grid[x_loc][y_loc].b = px->b;
		grid[x_loc][y_loc].g = px->g;
		grid[x_loc][y_loc].r = px->r;
	}

	void RenderPixel(const RPoint* pos, const RPixel* px) {

		grid[pos->x_pos][pos->y_pos].b = px->b;
		grid[pos->x_pos][pos->y_pos].g = px->g;
		grid[pos->x_pos][pos->y_pos].r = px->r;
	}

	void SimpleView() {
		float ra;
		float ba;
		float ga;
		float summ;
		char C;


		for (int y = height - 1; y >= 0; y--) {
			std::cout << '\n';
			for (int x = 0; x < width; x++) {
				ba = grid[x][y].b;
				ga = grid[x][y].g;
				ra = grid[x][y].r;

				summ = ra + ba + ga;
				switch (static_cast<int>(summ)) {
				case 0:
					C = '.';
					break;
				case 1:
					C = 'u';
					break;
				case 2:
					C = 'U';
					break;
				case 3:
					C = 'W';
					break;
				default:
					C = 'o';
					break;
				}

				std::cout << " " << C << " ";


			}
		}


	}

};
class Image {
public:
	Image(int width, int height)
		:m_width(width), m_height(height), m_colors(std::vector<RPixel>(width* height))
	{};
	~Image()
	{};
	RPixel GetColor(int x, int y) const	// 1) const following ) only works for member functions, 2. the const following the ) means the implicit "this" pointer is const (i.e. this function WILL NOT BE ABLE TO CHANGE ANYTHING THAT IS NOT MUTABLE
	{
		return m_colors[y * m_width + x];
	};
	void SetColor(const RPixel& color, int x, int y) {
		m_colors[y * m_width + x].r = color.r;
		m_colors[y * m_width + x].g = color.g;
		m_colors[y * m_width + x].b = color.b;
	}
	void Export(const char* path) {
		std::ofstream f;
		f.open(path, std::ios::out | std::ios::binary); // outputting (out) in binary 

		if (!f.is_open()) {
			std::cout << "ERROR! FILE COULD NOT BE OPENED!\n";
			return;
		}


		unsigned char bmpPad[3] = { 0,0,0 };
		const int paddingAmount = ((4 - (m_width * 3) % 4) % 4);

		const int fileHeaderSize = 14;
		const int informationHeaderSize = 40;
		const int fileSize = fileHeaderSize + informationHeaderSize + m_width * m_height * 3 + paddingAmount * m_height;

		unsigned char fileHeader[fileHeaderSize];



		// File type
		fileHeader[0] = 'B';
		fileHeader[1] = 'M';
		// File Size ( >> is bit shift here )
		fileHeader[2] = fileSize;
		fileHeader[3] = fileSize >> 8;
		fileHeader[4] = fileSize >> 16;
		fileHeader[5] = fileSize >> 24;
		// Reserved 1 (Not Used)
		fileHeader[6] = 0;
		fileHeader[7] = 0;
		// Reserved 2 (Not Used)
		fileHeader[8] = 0;
		fileHeader[9] = 0;
		// RPixel Data Offset
		fileHeader[10] = fileHeaderSize + informationHeaderSize;
		fileHeader[11] = 0;
		fileHeader[12] = 0;
		fileHeader[13] = 0;

		unsigned char informatinHeader[informationHeaderSize];
		int quick_itr = 0;
		// Header Size
		informatinHeader[quick_itr++] = informationHeaderSize;
		informatinHeader[quick_itr++] = 0;
		informatinHeader[quick_itr++] = 0;
		informatinHeader[quick_itr++] = 0;
		// Image Width
		informatinHeader[quick_itr++] = m_width;
		informatinHeader[quick_itr++] = m_width >> 8;
		informatinHeader[quick_itr++] = m_width >> 16;
		informatinHeader[quick_itr++] = m_width >> 24;
		// Image Height
		informatinHeader[quick_itr++] = m_height;
		informatinHeader[quick_itr++] = m_height >> 8;
		informatinHeader[quick_itr++] = m_height >> 16;
		informatinHeader[quick_itr++] = m_height >> 24;
		// Planes
		informatinHeader[quick_itr++] = 1;
		informatinHeader[quick_itr++] = 0;
		// Bits per pixel RGB
		informatinHeader[quick_itr++] = 24;
		informatinHeader[quick_itr++] = 0;
		// Compression (none)
		informatinHeader[quick_itr++] = 0;
		informatinHeader[quick_itr++] = 0;
		informatinHeader[quick_itr++] = 0;
		informatinHeader[quick_itr++] = 0;
		// Image size (no compression)
		informatinHeader[quick_itr++] = 0;
		informatinHeader[quick_itr++] = 0;
		informatinHeader[quick_itr++] = 0;
		informatinHeader[quick_itr++] = 0;
		// X Pixels per meter (not specified)
		informatinHeader[quick_itr++] = 0;
		informatinHeader[quick_itr++] = 0;
		informatinHeader[quick_itr++] = 0;
		informatinHeader[quick_itr++] = 0;
		// Y Pixels per meter (not specified)
		informatinHeader[quick_itr++] = 0;
		informatinHeader[quick_itr++] = 0;
		informatinHeader[quick_itr++] = 0;
		informatinHeader[quick_itr++] = 0;
		// Total colors (RPixel pallete not used)
		informatinHeader[quick_itr++] = 0;
		informatinHeader[quick_itr++] = 0;
		informatinHeader[quick_itr++] = 0;
		informatinHeader[quick_itr++] = 0;
		// Important colors (generally ignored)
		informatinHeader[quick_itr++] = 0;
		informatinHeader[quick_itr++] = 0;
		informatinHeader[quick_itr++] = 0;
		informatinHeader[quick_itr++] = 0; // quick_itr is now 40

		f.write(reinterpret_cast<char*>(fileHeader), fileHeaderSize);
		f.write(reinterpret_cast<char*>(informatinHeader), informationHeaderSize);

		for (int y = 0; y < m_height; y++) {
			for (int x = 0; x < m_width; x++) {
				unsigned char b_ch = static_cast<unsigned char>(GetColor(x, y).b * 255.0f);
				unsigned char g_ch = static_cast<unsigned char>(GetColor(x, y).g * 255.0f);
				unsigned char r_ch = static_cast<unsigned char>(GetColor(x, y).r * 255.0f);


				unsigned char color[] = { b_ch , g_ch, r_ch };
				f.write(reinterpret_cast<char*>(color), 3);
			}

			f.write(reinterpret_cast<char*>(bmpPad), paddingAmount);


		}


		f.close();
		std::cout << "File created\n";
	}


	void MapRaster(ScreenRaster& screen) {



		for (int x = 0; x < screen.width; x++) {
			for (int y = 0; y < screen.height; y++) {
				// image.SetColor(RPixel(x, y, 0), x, y);
				// ALSO: WHENEVER DOING CASTS, DO static_cast<type> TO GET THE VALUE CONVERTED TO A NEW TYPE AND THUS NEW INFORMATION AND WILL BE READ ACCORDING TO NEW TYPE. reinterpret_cast<type> WILL READ THE SAME INFORMATION ACCORDING TO THE NEW TYPE
				this->SetColor(screen.grid[x][y], x, y);

			}
		}

	}



	int m_width;
	int m_height;
	std::vector<RPixel> m_colors;

};

std::pair<float, float> MakeSlope
(const RPoint* point_A, const RPoint* point_B, const int number_of_steps) 
{
	int begin_x = point_A->x_pos;
	int end_x = point_B->x_pos;

	float inv_step = 1.f / number_of_steps;
	return std::pair<float, float>{begin_x, (end_x - begin_x)* inv_step};

}
void DrawScanLine
		(int y, std::pair<float,float>& left,std::pair<float, float>& right,
		ScreenRaster& screen,const RPixel* px) 
{
	int x = left.first, endx = right.first;
	for (; x < endx; ++x) {
		//Render_Pixel(x, y);		// Render each pixel
		screen.RenderPixel(x, y, px);
	}
	// after scnaline is drawn, update X coord on both sides
	left.first += left.second;
	right.first += right.second;
}
void RasterizeTriangle_rewrite
		(const RPoint* p0, const RPoint* p1, const RPoint* p2, 
		ScreenRaster& screen, const RPixel* px_color)
{
	int x0 = p0->x_pos;
	int y0 = p0->y_pos;

	int x1 = p1->x_pos;
	int y1 = p1->y_pos;

	int x2 = p2->x_pos;
	int y2 = p2->y_pos;

	// Order sort points by Y coord, putting topmost point first
	// When the Y coordinates are equal, order by X coordinates
	// Using 3-input sorting network
	if (std::tie(y1, x1) < std::tie(y0, x0)) { std::swap(x0, x1); std::swap(y0, y1); std::swap(p0, p1); }
	if (std::tie(y2, x2) < std::tie(y0, x0)) { std::swap(x0, x2); std::swap(y0, y2); std::swap(p0, p2); }
	if (std::tie(y2, x2) < std::tie(y1, x1)) { std::swap(x1, x2); std::swap(y1, y2); std::swap(p1, p2); }

	// Early return if there is nothing to draw (triangle has no area)
	if (y0 == y2) return;

	// Determine whether the short side is on left or right
	bool shortside = (y1 - y0) * (x2 - x0) < (x1 - x0) * (y2 - y0);

	// Make two slopes. p0-p1 short and p0-p2 long
	// One of these is left, one of these is right
	// At y = y1, the p0-p1 slope will be replaced with p1-p2 slope
	std::pair<float, float> sides[2];

	// At this point, y2-y0 cannot be zero.
	sides[!shortside] = MakeSlope(p0, p2, y2 - y0); // slope for long side

	for (int y = y0, endy = y0; ; ++y) {
		if (y >= endy) {
			// if y of p2 is reached, the triangle is complete.
			if (y >= y2) break;
			// Recalculate sloep for shrot side. The number of lines cannot be zero.
			// sides[shortside] = std::apply(MakeSlope, (y < y1) ? std::tuple(p0, p1, (endy = y1) - y0)
			//	: std::tuple(p1, p2, (endy = y2) - y1));
			if (y < y1) {
				sides[shortside] = MakeSlope(p0, p1, (endy = y1) - y0);
			}
			else {
				sides[shortside] = MakeSlope(p1, p2, (endy = y2) - y1);
			}

		}
		// On single scanline, go from left X coord to right X coord
		DrawScanLine(y, sides[0], sides[1], screen, px_color);

	}




}

void DrawPolygon( RPoly* poly, const RPixel* color, ScreenRaster& screen)
{
	int polysize = poly->points.size();
	if (polysize == 0) {
		VUCO(1, "DrawPolygon", "ERROR! DRAWPOLYGON CALLED WHEN POLYSIZE ZERO");
		return;
	}
	int pt_track = 0;

	// INPUT POLYGON SORT HERE


	// Start at first point, treat as "anchor"
	const RPoint* anchor = &(poly->points[pt_track++]);
	// Draw triangle using next two points, point A and point B
	RPoint* temp_A;
	RPoint* temp_B;


	temp_A = &(poly->points[pt_track++]);
	temp_B = &(poly->points[pt_track++]);


	//std::vector<RPixel> color3;
	//color3.push_back(RPixel(1.0f,0.0f,1.0f));
	//color3.push_back(RPixel(0.0f, 1.0f, 1.0f));
	//color3.push_back(RPixel(1.0f, 1.0f, 0.0f));



	RasterizeTriangle_rewrite(anchor, temp_A, temp_B, screen, color);
	// Update point A to be point B, and point B to be value in next poly.points array
	for (; pt_track < polysize; pt_track++) {
		temp_A = temp_B;
		temp_B = &(poly->points[pt_track]);
		//&color3[pt_track-2]
		RasterizeTriangle_rewrite(anchor, temp_A, temp_B, screen, color);


	}

}
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
