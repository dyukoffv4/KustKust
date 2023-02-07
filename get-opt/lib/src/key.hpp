#pragma once

#include <exception>
#include <stdexcept>
#include "defines.hpp"

namespace GetOpt {
	class Key {
	private:
		char s_data;
		std::string l_data;

	public:
		enum State{E, S, L, A};

		explicit Key(const std::string& l_data);
		explicit Key(const char& s_data, const std::string& l_data = "");

		State getState() const;

		bool operator<(const Key& key) const;

		char sname() const;
		std::string lname() const;

		static Key getNull();
		static Key getRoot();
	};
}