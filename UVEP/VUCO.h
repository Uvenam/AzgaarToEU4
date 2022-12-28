#pragma once
#include "../UVEP/head.h"

#define DEBUG

template <class ST>
void VUCO(std::string const& where_ele, ST& message)
{
#ifdef DEBUG
	// write message to std::cerr
	std::cout << '\n' << "[ " << where_ele << " ] " << message;
#else
	// write message to log file
#endif
}
template <class ST>
void VUCO(std::string const& where_ele, ST& message, bool act)
{
#ifdef DEBUG
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
void VUCO_WAN( ST& message )
{
#ifdef DEBUG
	// write message to std::cerr

		std::cout << message;


#else
	// write message to log file
#endif
}