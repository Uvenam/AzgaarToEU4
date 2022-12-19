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
	std::vector<uint32_t> palette;
	std::vector<std::vector<IPixel>> grid;
	// Initializes blackscreen with given dimensions
	ScreenRaster(int width_ele, int height_ele);

	//void RGB_ScreenRaster(int width_ele, int height_ele); //deprecated

	void RenderPixel(int x_loc, int y_loc, const IPixel* px);

	void RenderPixel(const RPoint* pos, const IPixel* px);

	void SimpleView();
		
	void Export (const char* path, int bytes);	// FRUSTRATINGLY DOES NOT WORK


	IPixel GetColor( int x, int y );

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



class BMPImage
{
	template<typename T>
	void readint( std::ifstream& f, T& val )
	{   //endian-independant read
		//static_assert(sizeof(T) <= 4); //requires c++17
		uint8_t buf[4];
		f.read( (char*)buf, sizeof( val ) );
		val = 0;
		for (int i = sizeof( val ) - 1; i >= 0; i--)
			val += (buf[i] << (8 * i));
	}

	template<typename T>
	void writeint( std::ofstream& f, T val )
	{   //endian-independant write
		//static_assert(sizeof(T) <= 4); //requires c++17
		uint8_t buf[4];
		for (int i = sizeof( val ) - 1; i >= 0; i--)
			buf[i] = (val >> 8 * i) & 0xff;
		f.write( (char*)buf, sizeof( val ) );
	}

	//based on BITMAPFILEHEADER, struct size will be off
	struct cfileheader
	{
		char type[2];
		uint32_t size;
		uint32_t reserved;
		uint32_t offset;
	};

	//based on BITMAPINFOHEADER, struct size will be off
	struct cinfoheader
	{
		uint32_t struct_size;
		uint32_t width;
		uint32_t height;
		uint16_t planes;
		uint16_t bitcount;
		uint32_t compression;
		uint32_t image_size;
		uint32_t xpermeter;
		uint32_t ypermeter;
		uint32_t colors_used;
		uint32_t colors_important;
	};

	BMPImage( const BMPImage& ) {} //lets make these inaccessible
	BMPImage& operator = ( BMPImage const& ) {}
public:
	BMPImage();
	bool readfile( const char* filename );
	bool writefile( const char* filename );
	bool isopen;
	int  width, height;
	int  width_in_bytes;
	int  bitcount;
	cfileheader fileheader;
	cinfoheader info;
	std::vector<uint32_t> palette;
	std::vector<uint8_t> image;
	uint32_t getpixel( int x, int y )
	{
		switch (bitcount)
		{
		case 1:
		{
			const int rowindex = (height - y - 1) * width_in_bytes;
			const uint8_t bit = (image[rowindex + x / 8] >> (7 - (x % 8))) & 1;
			return palette[bit];
		}
		case 4:
		{
			const int start = (height - y - 1) * width_in_bytes;
			uint8_t pal = image[start + x / 2];
			if (!(x % 2)) pal >>= 4;
			return palette[pal & 0xf];
		}
		case 8:
		{
			//find the index of pixel at x/y
			//the pixel should have a value between 0 to 256
			//get the color from palette
			const int i = (height - y - 1) * width_in_bytes + x;
			const uint8_t pal = image[i];
			return palette[pal];
		}
		case 24:
		{
			const int i = (height - y - 1) * width_in_bytes + x * 3;
			return image[i + 2] + (image[i + 1] << 8) + (image[i + 0] << 16);
		}
		case 32:
		{
			const int i = (height - y - 1) * width_in_bytes + x * 4;
			return image[i + 2] + (image[i + 1] << 8) + (image[i + 0] << 16);
		}
		}
		return 0;
	}
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

ScreenRaster CalculateNormal(ScreenRaster heightmap);

