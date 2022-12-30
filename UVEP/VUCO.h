#pragma once
#include "../UVEP/head.h"



template <class ST>
void VUCO(std::string where_ele, ST message)
{
#ifdef _DEBUG
	// write message to std::cerr
	std::cout << '\n' << "[ " << where_ele << " ] " << message;
#else
	// write message to log file
#endif
}
template <class ST>
void VUCO(std::string where_ele, ST message, bool act)
{
#ifdef _DEBUG
	// write message to std::cerr
	if (act == TRUE)
	{
		std::cout << '\n' << "[ " << where_ele << " ] " << message;
	}

#else
	// write message to log file
#endif
}
template <class ST>
void VUCO_WAN( ST message )
{
#ifdef _DEBUG
	// write message to std::cerr

		std::cout << message;


#else
	// write message to log file
#endif
}