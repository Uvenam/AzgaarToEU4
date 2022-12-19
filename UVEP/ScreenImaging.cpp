#include "ScreenImaging.h"
/*##########################################################################################################*/
// IPixel class
IPixel::IPixel()
	: r(0), g(0), b(0)
{}
IPixel::IPixel(unsigned char r_ele, unsigned char g_ele, unsigned char b_ele)
	:r(r_ele), g(g_ele), b(b_ele)
{}
IPixel::IPixel( unsigned long hex_ele )
	:
	r( static_cast<unsigned char>( (hex_ele >> 16)	&0xFF) ), 
	g( static_cast<unsigned char>( (hex_ele >> 8)	&0xFF) ), 
	b( static_cast<unsigned char>( (hex_ele)		&0xFF) )
{}
IPixel::IPixel( float r_ele, float g_ele, float b_ele )
	:
	r(static_cast<unsigned char>(r_ele*255.0f)	),
	g(static_cast<unsigned char>(g_ele*255.0f)	),
	b(static_cast<unsigned char>(b_ele*255.0f)	)
{}
IPixel::IPixel( int r_ele, int g_ele, int b_ele )
	:
	r( static_cast<unsigned char>(r_ele) ),
	g( static_cast<unsigned char>(g_ele) ),
	b( static_cast<unsigned char>(b_ele) )
{}
/*
IPixel::IPixel(const RPixel& x)
	:r(static_cast<unsigned char>(x.r * 255.0f)),
	g(static_cast<unsigned char>(x.g * 255.0f)),
	b(static_cast<unsigned char>(x.b * 255.0f))
{}
*/
// conversion from A (assignment):
/*
IPixel& IPixel::operator= (const RPixel& x)
{
	this->r = static_cast<unsigned char>(x.r * 255.0f);
	this->g = static_cast<unsigned char>(x.g * 255.0f);
	this->b = static_cast<unsigned char>(x.b * 255.0f);
	return *this;
}
*/
// conversion to A (type-cast operator)
/*
IPixel::operator RPixel()
{
	return RPixel(
		static_cast<float>(this->r / 255.0f),
		static_cast<float>(this->g / 255.0f),
		static_cast<float>(this->b / 255.0f)
	);
}
*/
 // end IPixel Class
/*##########################################################################################################*/
/*##########################################################################################################*/
// ScreenRaster Class
ScreenRaster::		 ScreenRaster(int width_ele, int height_ele)
	:height(height_ele), width(width_ele)
{
	std::vector<IPixel> column;
	IPixel white_space(0.0f, 0.0f, 0.0f);
	for (int x = 0; x < width; x++) {
		grid.push_back(column);
		for (int y = 0; y < height; y++) {
			grid[x].push_back(white_space);
		}
	}
};
/* deprecated
void ScreenRaster::RGB_ScreenRaster(int width_ele, int height_ele)

{
	this->width = width_ele;
	this->height = height_ele;


	std::vector<IPixel> column;
	IPixel white_space(0x00, 0x00, 0x00);
	for (int x = 0; x < width; x++) {
		grid.push_back(column);
		for (int y = 0; y < height; y++) {
			grid[x].push_back(white_space);
		}
	}
};*/
void ScreenRaster::	 RenderPixel(int x_loc, int y_loc, const IPixel* px) {

	grid[x_loc][y_loc].b = px->b;
	grid[x_loc][y_loc].g = px->g;
	grid[x_loc][y_loc].r = px->r;
}
void ScreenRaster::  RenderPixel(const RPoint* pos, const IPixel* px) {

	grid[pos->x_pos][pos->y_pos].b = px->b;
	grid[pos->x_pos][pos->y_pos].g = px->g;
	grid[pos->x_pos][pos->y_pos].r = px->r;
}
void ScreenRaster::	 SimpleView() {
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
IPixel ScreenRaster::GetColor( int x, int y ) {
	return grid[x][y];
}
void ScreenRaster::	 Export( const char* path , int bytes) {	// DOES NOT WORK FOR WHATEVER GODFORSAKEN REASON

	std::ofstream f;
	f.open( path, std::ios::out | std::ios::binary ); // outputting (out) in binary 

	if (!f.is_open()) {
		std::cout << "ERROR! FILE COULD NOT BE OPENED!\n";
		return;
	}


	//std::vector<unsigned char>temporary(bytes);
	//unsigned char* bmpPad = &temporary[0];
	unsigned char* bmpPad{ new unsigned char[bytes] {} };
	const int paddingAmount = ((4 - (width * bytes) % 4) % 4);
	//const int paddingAmount = 0;

	const int fileHeaderSize = 14;
	const int informationHeaderSize = 40;
	const int fileSize = fileHeaderSize + informationHeaderSize + width * height * bytes + paddingAmount * height + (256*4);

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
	// IPixel Data Offset
	fileHeader[10] = (fileHeaderSize + informationHeaderSize + (256 * 4));
	fileHeader[11] = (fileHeaderSize + informationHeaderSize + (256 * 4)) >>8;
	fileHeader[12] = (fileHeaderSize + informationHeaderSize + (256 * 4)) >>16;
	fileHeader[13] = (fileHeaderSize + informationHeaderSize + (256 * 4)) >>24;

	unsigned char informatinHeader[informationHeaderSize];
	int quick_itr = 0;
	// Header Size
	informatinHeader[quick_itr++] = informationHeaderSize;
	informatinHeader[quick_itr++] = 0;
	informatinHeader[quick_itr++] = 0;
	informatinHeader[quick_itr++] = 0;
	// Image Width
	informatinHeader[quick_itr++] = width;
	informatinHeader[quick_itr++] = width >> 8;
	informatinHeader[quick_itr++] = width >> 16;
	informatinHeader[quick_itr++] = width >> 24;
	// Image Height
	informatinHeader[quick_itr++] = height;
	informatinHeader[quick_itr++] = height >> 8;
	informatinHeader[quick_itr++] = height >> 16;
	informatinHeader[quick_itr++] = height >> 24;
	// Planes
	informatinHeader[quick_itr++] = 1;
	informatinHeader[quick_itr++] = 0;
	// Bits per pixel RGB
	informatinHeader[quick_itr++] = 8;
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
	// Total colors (defaults to 2^n)
	informatinHeader[quick_itr++] = 256;
	informatinHeader[quick_itr++] = 256 >> 8;
	informatinHeader[quick_itr++] = 256 >> 16;
	informatinHeader[quick_itr++] = 256 >> 24;
	// Important colors (generally ignored)
	informatinHeader[quick_itr++] = 256;
	informatinHeader[quick_itr++] = 256 >> 8;
	informatinHeader[quick_itr++] = 256 >> 16;
	informatinHeader[quick_itr++] = 256 >> 24; // quick_itr is now 40

	//std::vector<unsigned char> colorTable;	// https://www.codeproject.com/Articles/7124/Image-Bit-depth-conversion-from-32-Bit-to-8-Bit
											// https://stackoverflow.com/questions/70086475/create-bmp-image-on-8-bits-per-pixel
	


	f.write( reinterpret_cast<char*>(fileHeader), fileHeaderSize );
	f.write( reinterpret_cast<char*>(informatinHeader), informationHeaderSize );

	for (int e = 0; e < 256; e++) {
		//ABGR -> BGRA
		uint8_t buf[4]{};
		buf[0] = e;	//(e >> 16) & 0xff;
		buf[1] = e;	//(e >> 8) & 0xff;
		buf[2] = e;	//(e >> 0) & 0xff;
		buf[3] = 0x00;	//(e >> 24) & 0xff;
		f.write( (char*)buf, 4 );
	}
	//f.write(reinterpret_cast<char*>(colorTable),colorTableSize);


	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			unsigned char b_ch = static_cast<unsigned char>(GetColor( x, y ).b);
			//unsigned char g_ch = static_cast<unsigned char>(GetColor( x, y ).g);
			//unsigned char r_ch = static_cast<unsigned char>(GetColor( x, y ).r);


			unsigned char color[] = { b_ch };
			//VUCO( "", "Outputting to .bmp..." );
			f.write( reinterpret_cast<char*>(color), 1 );	
		}
		//VUCO( "", "Outputting line .bmp..." );
		if (paddingAmount>0)
			f.write( reinterpret_cast<char*>(bmpPad), paddingAmount );
		

	}


	f.close();
	VUCO( "", "File created" );
	delete[] bmpPad;
}















// end ScreenRaster Class
/*##########################################################################################################*/
/*##########################################################################################################*/
// Image Class
Image::		  Image(int width, int height)
	:m_width(width), m_height(height), m_colors(std::vector<IPixel>(width* height))
{};
IPixel Image::GetColor(int x, int y) const	// 1) const following ) only works for member functions, 2. the const following the ) means the implicit "this" pointer is const (i.e. this function WILL NOT BE ABLE TO CHANGE ANYTHING THAT IS NOT MUTABLE
{
	return m_colors[y * m_width + x];
};
void Image::  SetColor(const IPixel& color, int x, int y) {
	m_colors[y * m_width + x] = color;
	//m_colors[y * m_width + x].g = color.g;
	//m_colors[y * m_width + x].b = color.b;
}
void Image::  Export(const char* path) {
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
	// IPixel Data Offset
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
	// Total colors (IPixel pallete not used)
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
			unsigned char b_ch = static_cast<unsigned char>(GetColor(x, y).b);
			unsigned char g_ch = static_cast<unsigned char>(GetColor(x, y).g);
			unsigned char r_ch = static_cast<unsigned char>(GetColor(x, y).r);


			unsigned char color[] = { b_ch , g_ch, r_ch };
			f.write(reinterpret_cast<char*>(color), 3);
		}

		f.write(reinterpret_cast<char*>(bmpPad), paddingAmount);


	}


	f.close();
	VUCO("","File created");
}
void Image::  MapRaster(ScreenRaster& screen) {



	for (int x = 0; x < screen.width; x++) {
		for (int y = 0; y < screen.height; y++) {
			// image.SetColor(IPixel(x, y, 0), x, y);
			// ALSO: WHENEVER DOING CASTS, DO static_cast<type> TO GET THE VALUE CONVERTED TO A NEW TYPE AND THUS NEW INFORMATION AND WILL BE READ ACCORDING TO NEW TYPE. reinterpret_cast<type> WILL READ THE SAME INFORMATION ACCORDING TO THE NEW TYPE
			this->SetColor(screen.grid[x][y], x, y);

		}
	}

}
// End Image Class
/*##########################################################################################################*/
// Relevant functions

std::pair<float, float> MakeSlope (const RPoint* point_A, const RPoint* point_B, const int number_of_steps)
{
	int begin_x = point_A->x_pos;
	int end_x = point_B->x_pos;

	float inv_step = 1.f / number_of_steps;
	return std::pair<float, float>{begin_x, (end_x - begin_x)* inv_step};

}
void					DrawScanLine (int y, std::pair<float, float>& left, std::pair<float, float>& right,ScreenRaster& screen, const IPixel* px)
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
void					RasterizeTriangle_rewrite(const RPoint* p0, const RPoint* p1, const RPoint* p2,ScreenRaster& screen, const IPixel* px_color)
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
void					DrawPolygon(RPoly* poly, const IPixel* color, ScreenRaster& screen)
{
	int polysize = poly->points.size();
	if (polysize == 0) {
		VUCO("DrawPolygon", "ERROR! DRAWPOLYGON CALLED WHEN POLYSIZE ZERO",1);
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


	//std::vector<IPixel> color3;
	//color3.push_back(IPixel(1.0f,0.0f,1.0f));
	//color3.push_back(IPixel(0.0f, 1.0f, 1.0f));
	//color3.push_back(IPixel(1.0f, 1.0f, 0.0f));



	RasterizeTriangle_rewrite(anchor, temp_A, temp_B, screen, color);
	// Update point A to be point B, and point B to be value in next poly.points array
	for (; pt_track < polysize; pt_track++) {
		temp_A = temp_B;
		temp_B = &(poly->points[pt_track]);
		//&color3[pt_track-2]
		RasterizeTriangle_rewrite(anchor, temp_A, temp_B, screen, color);


	}

}
ScreenRaster			CalculateNormal( ScreenRaster heightmap )
{
	int xt = heightmap.width;
	int yt = heightmap.height;
	ScreenRaster normal( xt, yt );
	// horizontal_kernel
	int Gx[3][3] =
	{
		{ -1,	0,	1	},
		{ -2,	0,	2	},
		{ -1,	0,	1	}
	};
	// vertical_kernel
	int Gy[3][3] =
	{
		{	1,	2,	1	},
		{	0,	0,	0	},
		{  -1, -2, -1	}
	};

	int value_x = 0;
	int value_y = 0;
	// only need to use one channel since r=g=b
	for (int X = 1; X < xt-1; X++) {
		for (int Y = 1; Y < yt - 1; Y++) {
			// find x value
			value_x =
			  heightmap.grid[X-1][Y-1].b *	Gx[0][0] + heightmap.grid[X][Y-1].b * Gx[0][1] + heightmap.grid[X+1][Y-1].b   *	Gx[0][2]
			+ heightmap.grid[X - 1][Y].b *	Gx[1][0] + heightmap.grid[X][Y].b   * Gx[1][1] + heightmap.grid[X + 1][Y].b *	Gx[1][2]
			+ heightmap.grid[X - 1][Y+1].b *Gx[2][0] + heightmap.grid[X][Y+1].b * Gx[2][1] + heightmap.grid[X + 1][Y+1].b * Gx[2][2];
			// find y value
			value_y =
			  heightmap.grid[X - 1][Y - 1].b * Gy[0][0] + heightmap.grid[X][Y - 1].b * Gy[0][1] + heightmap.grid[X + 1][Y - 1].b * Gy[0][2]
			+ heightmap.grid[X - 1][Y].b *	   Gy[1][0] + heightmap.grid[X][Y].b *     Gy[1][1] + heightmap.grid[X + 1][Y].b *     Gy[1][2]
			+ heightmap.grid[X - 1][Y + 1].b * Gy[2][0] + heightmap.grid[X][Y + 1].b * Gy[2][1] + heightmap.grid[X + 1][Y + 1].b * Gy[2][2];
			// constrain x and y to -128 to 128. Since max is 1020 and resting area of no change is 126, divide by 8 
		
			value_x /= 8;
			value_y /= 8;

			

			static_cast<signed char>(value_x);
			static_cast<signed char>(value_y);

			//render pixel
			normal.grid[X][Y] = IPixel( 127+value_x, 127+value_y, 255 );

			//value_x = 0;
			//value_y = 0;
		}
	}



	return normal;
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

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++




BMPImage::BMPImage() :
	isopen{ false }, fileheader{}, info{},
	bitcount{}, width{}, height{}, width_in_bytes{}
{
}

bool BMPImage::readfile( const char* filename )
{
	std::ifstream fin( filename, std::ios::binary );
	if (!fin) { std::cout << "open failed " << filename << '\n'; return false; }

	fin.read( fileheader.type, 2 );
	if (strncmp( fileheader.type, "BM", 2 ) != 0) return false;
	readint( fin, fileheader.size );
	readint( fin, fileheader.reserved );
	readint( fin, fileheader.offset );

	readint( fin, info.struct_size );
	readint( fin, info.width );
	readint( fin, info.height );
	readint( fin, info.planes );
	readint( fin, info.bitcount );
	readint( fin, info.compression );
	readint( fin, info.image_size );
	readint( fin, info.xpermeter );
	readint( fin, info.ypermeter );
	readint( fin, info.colors_used );
	readint( fin, info.colors_important );

	width = info.width;
	height = info.height;
	bitcount = info.bitcount;

	if (info.struct_size != 40)
	{
		printf( "wrong structure size %d\n", info.struct_size );
		return false;
	}

	std::vector<uint16_t> bitcheck{ 1,4,8,24,32 };
	if (std::find( bitcheck.begin(), bitcheck.end(), bitcount ) == bitcheck.end())
	{
		printf( "cannot handle this bitcount %d\n", bitcount );
		return false;
	}

	int palette_size = (bitcount > 8) ? 0 : (1 << bitcount);
	palette.resize( palette_size );
	for (auto& e : palette)
	{
		//BGRA -> ABGR
		uint8_t buf[4]{};
		fin.read( (char*)buf, 4 );
		e = buf[2] | (buf[1] << 8) | (buf[0] << 16) | (buf[3] << 24);
	}

	if (fin.tellg() != fileheader.offset)
	{
		printf( "error reading image\n" ); return false;
	}

	width_in_bytes = ((width * info.bitcount + 31) / 32) * 4;
	image.resize( width_in_bytes * height );
	fin.read( (char*)image.data(), image.size() );
	isopen = true;
	return true;
}
bool BMPImage::writefile( const char* filename )
{
	if (!isopen) return false;
	std::ofstream fout( filename, std::ios::binary );
	if (!fout) { std::cout << "open failed " << filename << '\n'; return false; }

	fout.write( (char*)fileheader.type, 2 );
	writeint( fout, fileheader.size );
	writeint( fout, fileheader.reserved );
	writeint( fout, fileheader.offset );
	writeint( fout, info.struct_size );
	writeint( fout, info.width );
	writeint( fout, info.height );
	writeint( fout, info.planes );
	writeint( fout, info.bitcount );
	writeint( fout, info.compression );
	writeint( fout, info.image_size );
	writeint( fout, info.xpermeter );
	writeint( fout, info.ypermeter );
	writeint( fout, info.colors_used );
	writeint( fout, info.colors_important );

	for (auto& e : palette)
	{
		//ABGR -> BGRA
		uint8_t buf[4]{};
		buf[0] = (e >> 16) & 0xff;
		buf[1] = (e >> 8) & 0xff;
		buf[2] = (e >> 0) & 0xff;
		buf[3] = (e >> 24) & 0xff;
		fout.write( (char*)buf, 4 );
	}

	fout.write( (char*)image.data(), image.size() );

	return true;
}