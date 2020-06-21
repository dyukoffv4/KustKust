#pragma once

#include <cstring>
#include <iostream>

class Heap
{

public:

	void ItoS(char* num_str);				//  Function pull to "num_str" next number with new launch from "1". Function takes only a string to be filled.
	int ItoS(int num, char* num_str);		//  Function pull to "num_str" number that is in "num". Function takes only a string to be filled. Function return "0" if had done perfect.

	int ItS_num = 0;
};