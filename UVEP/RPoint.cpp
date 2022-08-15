#include "../UVEP/RPoint.h"

// RPoint class
/*#########################################################################################################*/
RPoint::RPoint()
	: x_pos( 0 ), y_pos( 0 )
{}
RPoint::RPoint( int x_value, int y_value )
	: x_pos( x_value ), y_pos( y_value )
{}
bool operator==( RPoint const& lhs, RPoint const& rhs )
{

	if (lhs.x_pos == rhs.x_pos) {
		if (lhs.y_pos == rhs.y_pos) {
			return true;
		}
	}
	return false;

}
/*#########################################################################################################*/

// RPoly class
void RPoly::SortPoints() {

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

	this->xy_center = centroid;
	// Get an angle for each point and tie it to each point
	double ang;
	std::vector <std::tuple<double, RPoint>>  proper_order;
	for (int pt_itr = 0; pt_itr < psize; pt_itr++) {
		proper_order.push_back(
			std::make_tuple(
				std::atan2( points[pt_itr].y_pos - centroid.y_pos, points[pt_itr].x_pos - centroid.x_pos ),
				points[pt_itr]
			)
		);
	}
	// Sort based on angle
	std::sort( proper_order.begin(), proper_order.end(),
		[]( const std::tuple<double, RPoint>& pA, const std::tuple<double, RPoint>& pB )
		-> bool { return std::get<0>( pA ) > std::get<0>( pB ); }
	);
	// Replace RPoly.points vector with properly ordered vector
	for (int pt_itr = 0; pt_itr < psize; pt_itr++) {
		points[pt_itr] = std::get<1>( proper_order[pt_itr] );
	}




}
void RPoly::MergePoly( RPoly& polyB )
{
	// add new
	int bpsize = polyB.points.size();
	for (int dm_itr = 0; dm_itr < bpsize; dm_itr++) {
		this->points.push_back( polyB.points[dm_itr] );
	}
	DeleteDuplicates();
	SortPoints();
}

void RPoly::DeleteDuplicates() {	// ISSUE -> RESOLVED https://www.reddit.com/r/cpp_questions/comments/dum03u/having_issues_using_unordered_set_with_struct/

	// How to get unique ID for every RPoint? 

	std::unordered_set<RPoint, RPointHash> unique_points;
	std::vector<RPoint> unique_points_vec;
	// Place every point into unique set
	int psize = points.size();
	for (int d_itr = 0; d_itr < psize; d_itr++) {
		unique_points.emplace( points[d_itr] );
	}
	// Place each item from unique_points and into points
	for (auto S_itr : unique_points) {
		unique_points_vec.push_back( S_itr );
	}
	this->points.swap( unique_points_vec );



}

// end RPoly class
/*##########################################################################################################*/

// Relevant Functions


std::vector<RPoly> CreateTiledHexagonGrid( int width_ele, int height_ele, int horiz_number, int vertical_number )
{
	std::vector<RPoly> poly_grid;


	// NOTE! Can't just do a tiled hexagon grid as an underlay/overlay. Have to consider that there are coastal ocean cells
	// Could merge coastal cells and then create a hexagon grid up until it gets close to a coastal cell, then link up the one hexagon to have its verticies match the coastal cell neighbor

	//https://www.redblobgames.com/grids/hexagons/implementation.html










	return poly_grid;
}
