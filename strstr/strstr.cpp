// strstr.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <map>
                 //12345678901234567890
char * g_puzzle = "peteaapuzh"  //y = (offset/dimension)+1   x=(offset % dimension)+1
                  "heresapuza"  
				  "heresapuzr"  
				  "heresapuzr"
				  "heresapuzy"
				  "herpeterzl"
				  "neresapuzl"
				  "hiresapuzl"
				  "hecesapuzl"
				  "herksapuzl";

/*
diagonal (1,10), 
         (1,9)(2,10),
		 (1,8)(2,9)(3,10),
		 (1,7)(2,8)(3,9)(4,10), 
		 (1,6)(2,7)(3,8)(4,9)(5,10),
		 (1,5)(2,6)(3,7)(4,8)(5,9)(6,10)
		 (1,4)(2,5)(3,6)(4,7)(5,8)(6,9)(7,10)
		 (1,3)(2,4)(3,5)(4,4)(5,7)(6,8)(7,9)(8,10)
		 (1,2)(2,3)(3,4)(4,5)(5,6)(6,7)(7,8)(8,9)(9,10)
		 (1,1)(2,2)(3,3)(4,4)(5,5)(6,6)(7,7)(8,8)(9,9)(10,10)
		 (2,1)(3,2)(4,3)(5,4)(6,5)(7,6)(8,7)(9,8)(10,9)
		 (3,1)
		 (4,1)
		 (5,1)
		 (6,1)
		 (7,1)
		 (8,1)(9,2)(10,3)
		 (9,1)(10,2)
		 (10,1)
*/


char * g_puzzle2=   "heresapuzzh"
					"heresapuzza"
					"heresapuzzr"
					"heresapuzzr"
					"heresapuzzy"
					"herpeterzzl"
					"neresapuzzl"
					"hiresapuzzl"
					"hecesapuzzl"
					"herksapuzzl";

class tuple
{
public:

	class tuple	(size_t x, size_t y)
		:  m_x(x), m_y(y)
	{
		return;
	}

	class tuple() : m_x(0), m_y(0)
	{
		return;
	}

	tuple(const tuple &rhs)
	{
		Clone(rhs);
		return;
	}

	tuple & increment(const tuple &rhs)
	{
		m_x += rhs.m_x;
		m_y += rhs.m_y;
		return *this;
	}

	tuple & operator=(const tuple &rhs)
	{
		return Clone(rhs);
	}

	tuple & Clone(const tuple &rhs)
	{
		if (&rhs != this)
		{
			this->m_x = rhs.m_x;
			this->m_y = rhs.m_y;
		}
		return *this;
	}

	size_t m_x;
	size_t m_y;
};


class velocity 
{
public:
	enum direction { notfound, horizontal, vertical, L_diagonal, R_diagonal } ;
	velocity() : m_direction(notfound), m_start(0, 0)
	{
		return;
	}
	velocity(direction d, size_t x, size_t y)
		: m_direction(d), m_start(x, y)
	{
		return;
	}
	tuple m_start;
	direction m_direction;
};

std::string pfw_puzzle(char * find, char * puzzle, const size_t dimension)
{

	velocity Horizontal(velocity::horizontal, 0, 0);
	velocity Vertical(velocity::horizontal, 0, 0);
	velocity LDiag(velocity::horizontal, 0, dimension);
	velocity RDiag(velocity::horizontal, dimension, 0);

	velocity Found;

	size_t x = 0;
	size_t y = 0;

	size_t len = strlen(find);

	//assert len <= dimension


	//this finds the horizontal pos
	tuple cursor;

	tuple rate(1, 0);
	for (cursor= Horizontal.m_start;
		Found.m_direction == velocity::notfound && cursor.m_y < dimension; cursor.increment(rate))
	{
		;
	}
	

	//this finds the vertical pos

	tuple rate(1, 0);
	for (x = Vertical.m_start.m_x, y = Vertical.m_start.m_y;
		Found.m_direction == velocity::notfound && x < dimension;
		x++)
	{
		;
	}


	//this finds the ldiag pos

	tuple rate(1, 1);
	for (x = LDiag.m_start.m_x, y = LDiag.m_start.m_y;
		Found.m_direction == velocity::notfound && y < dimension;
		x++)
	{

		;
	}




	char * pos = strstr(puzzle, find);
	if (pos)
	{
		direction = horizontal;
		long offset = ( pos - puzzle);

		y = (offset / dimension)+1;
		x = (offset % dimension)+1;

		printf("\nhorizontal x=%d, y=%d", x, y);
	}

	for (x = 0; direction == notfound && x < dimension; x++)
	{
		for (y = 0; direction == notfound && y <= dimension - len; y++)
		{

			long i = 0;
			char * f = find;
			while (find[i] == puzzle[(y*dimension) + (dimension*i) + x])
			{
				i++;
			}
			if (i == len)
			{
				direction = vertical;
				printf("\nvertical x=%d, y=%d", x, y);
			}
		}
	}

	// 1 2 3 4     (1,4) - (1,3),(2,4)-
	// 1 2 3 4
	// 1 2 3 4
	// 1 2 3 4

	

	for (size_t diagcount = dimension * 2 - 1; diagcount && direction == notfound; diagcount--)
	{

		if (x < y)
		{
			
		}
		size_t diaglength = (x < y) dimension - y;

			while (i < diaglength && find[i] && find[i] == puzzle[(y*dimension) + (dimension*i) + (x + i)])
			{
				i++;
			}
			if (i == len)
			{
				direction = L_diagonal;
				printf("\nL_diagonal x=%d, y=%d", x, y);
			}
		}
		if (diaglength == dimension | x ) x++;

	}

	switch (direction)
	{
	case horizontal:
		//start(0,0)
		//(1,0)
		break;
	case vertical:
		//start(0,0)
		//(0,1)
		break;
	case L_diagonal:
		//start(max,0)
		//(1,1)
		break;
	case R_diagonal:
		//start(0,max)
		//(-1,-1)
		break;
	default:
		break;
	}
	return "";
}

const char * pfw_strstr(const char * s, const char * f)
{
	const char * RetVal = 0;
	if (s && f)
	{
		if (*s && *f)
		{
			while (*s && RetVal==0)
			{
				int i = 0;
				while (*(s+i) && *(f+i) && *(s+i)==*(f+i))
				{
					i++;
					if (*(f + i) == 0)
					{
						RetVal = s;
					}
				}
				s++;
			}
		}
	}
	return RetVal;
}


int _tmain(int argc, _TCHAR* argv[])
{

	std::map<std::string, const char*> test_results;

	const char * test_cases[ ][2]= {
		{ "BALL", "ALL" },
		{ "ALL", "BALL" },
		{ "", "" },
		{ "PETERFRANCISWATTERS", "CIS" },
		{ "JOHNSON", "JOHN" },
		{ "JOHNSON", "OHN" },
		{ "JOHNSON", "OH" }, 
		{ "JOHNSON", "O" },
		{ "JOHNSON", "J" },
		{ "JOHNSON", "ON" },
		{ 0, 0 }
	};

	pfw_puzzle("peter", g_puzzle, 10);
	pfw_puzzle("pete", g_puzzle, 10);
	pfw_puzzle("nick", g_puzzle, 10);
	pfw_puzzle("harry", g_puzzle, 10);


	for (int i = 0; test_cases[i][0]; i++)
	{
		std::string key = test_cases[i][0];
		key += ", ";
		key += test_cases[i][1];
		test_results[key] = pfw_strstr(test_cases[i][0], test_cases[i][1]);
	}

	for (std::map<std::string, const char*>::iterator it = test_results.begin(); it != test_results.end(); it++)
	{
		printf("\n%s returned %s", (*it).first.c_str(), ((*it).second) ? ((*it).second) : "<NULL>");
	}

	return 0;
}

