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

		void setDiapozon(int f, int s);

	public:
		enum State{E, S, L, A};

		explicit Key(const char& s_data, int num = -1, int hnum = -1);
		explicit Key(const std::string& l_data, int num = -1, int hnum = -1);
		explicit Key(const char& s_data, const std::string& l_data, int num = -1, int hnum = -1);

		State getState() const;

		bool operator<(const Key& key) const;
		bool operator[](const int& num) const;

		char sname() const;
		std::string lname() const;

		friend class Terminal;
	};
}