#pragma once

#include <string>
#include <exception>
#include <stdexcept>


class Key {
private:
	std::string data;
	static Key getNull();
	static Key getRoot();

public:
	explicit Key(const char& data);
	explicit Key(const std::string& data);

	void rename(const std::string& data);

	bool largeEqual(const Key& key) const;
	bool shortEqual(const Key& key) const;
	
	bool operator<(const Key& key) const;

	std::string name() const;

	static Key root_key;
	static Key null_key;
};