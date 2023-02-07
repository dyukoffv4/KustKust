#pragma once

#include "defines.hpp"

namespace KP {
	class Key {
	private:
		char s_data;
		std::string l_data;

		int lk_num;
		int hk_num;

		static Key getNull();
		static Key getRoot();

	public:
		enum State{E, S, L, A};
		enum Dind{l, e, h};

		explicit Key(const char& s_data, int f_num = -1, int s_num = -1);
		explicit Key(const std::string& l_data, int f_num = -1, int s_num = -1);
		explicit Key(const char& s_data, const std::string& l_data, int f_num = -1, int s_num = -1);

		State getState() const;

		bool operator<(const Key& key) const;
		Dind operator[](const int& num) const;

		char sname() const;
		std::string lname() const;

		friend class Terminal;
	};
}