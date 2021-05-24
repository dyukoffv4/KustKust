#include "daa_func.h"

daa_4::daa_vec daa_4::get_suffix(daa_str temp) {

	daa_vec p(temp.size());

	for (int i = 1, j = 0; i < temp.size(); 0) {

		if (temp[i] == temp[j]) p[i++] = ++j;
		else
			if (j == 0) p[i++] = 0;
			else j = p[j - 1];
	}

	return p;
}

daa_4::daa_vec daa_4::get_entry(daa_str& text, daa_str& temp) {

	daa_vec result;
	daa_vec indx = get_suffix(temp + "*" + text);
	int text_s = text.size();
	int temp_s = temp.size();

	for (int i = 0; i < text_s; i++)
		if (indx[temp_s + i + 1] == temp_s)
			result.push_back(i - temp_s + 1);

	return result;
}