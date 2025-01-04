#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <string>

class Tag {
protected:
    std::string name, params, body; // params methods add
    std::vector<Tag> childs;
    Tag* ptr_parent;
    bool atomic;

public:
    Tag(const std::string& name, bool atomic = false);

    Tag* add_child(const std::string& name, bool atomic, int pos = -1);
    Tag* add_child(const std::string& name, int pos = -1);
    Tag* add_child(const Tag& child, int pos = -1);

    void del_child(const std::string& name, int pos = 0);
    void del_child(int pos);

    Tag* get_child(const std::string& name, int pos = 0);
    Tag* get_child(int pos);

    Tag* parent() const;
    
    bool add_name(const std::string& p_name);
    bool set_name(const std::string& p_name);
    const std::string& get_name() const;

    bool add_body(const std::string& p_body);
    bool set_body(const std::string& p_body);
    const std::string& get_body() const;

    std::string string(int level = 0) const;
};

void trim_string(std::string& str);
bool letter(const char& c);
bool passed(const char& c);
bool tag_passed(const std::string& s);

void save(const std::string& filename, const Tag& root, std::string metadata);
void load(const std::string& filename, Tag& root, std::string& metadata);
