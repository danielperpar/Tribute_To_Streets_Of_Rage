#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#include <list>

class Utilities {
public:
	static void free_list(std::list<int*>& rect_list)
	{
		for (std::list<int*>::iterator it = rect_list.begin(); it != rect_list.end(); it++)
		{
			delete[] *it;
		}

		rect_list.clear();
	}
};


#endif // __UTILITIES_H__
