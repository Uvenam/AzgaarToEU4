#pragma once
#include "../UVEP/head.h"

class RPoint {
	// https://www.tutorialspoint.com/cplusplus/cpp_inheritance.htm
public:
	int x_pos, y_pos;
	RPoint();
	RPoint( int x_value, int y_value );
	friend bool operator == ( RPoint const& lhs, RPoint const& rhs );
};
struct RPointHash {
public:
	size_t operator()( const RPoint p ) const
	{
		return std::hash<uint32_t>()(p.x_pos) ^ std::hash<uint32_t>()(p.y_pos);
	}

};
// RPoly holds a vector of RPoints (found in classes.h as of comment date (8-14-22)
class RPoly {
public:
	std::vector<RPoint> points;
	RPoint xy_center;
	void SortPoints();
	void MergePoly( RPoly& polyB );
	void DeleteDuplicates();		//ISSUE -> RESOLVED https://www.reddit.com/r/cpp_questions/comments/dum03u/having_issues_using_unordered_set_with_struct/
};


std::vector<RPoly> CreateTiledHexagonGrid( int width_ele, int height_ele, int horiz_number, int vertical_number );