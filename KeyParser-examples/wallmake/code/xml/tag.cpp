#include "tag.hpp"
#include <iostream>

void trim_string(std::string& str) {
    for (int i = 0; i < str.size(); i++) {
        if (str[i] != '\n' && str[i] != '\t' && str[i] != ' ') {
            str.erase(0, i);
            break;
        }
    }
    for (int i = str.size() - 1; i >= 0; i--) {
        if (str[i] != '\n' && str[i] != '\t' && str[i] != ' ') {
            str.erase(i + 1);
            break;
        }
    }
}

bool letter(const char& c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

bool passed(const char& c) {
    return (c >= '0' && c <= '9') || letter(c) || c == '_' || c == '-' || c == '.';
}

bool tag_passed(const std::string& s) {
    if (!letter(s.front())) return false;
    for (auto &i : s) if (!passed(i)) return false;
    return true;
}

void save(const std::string& filename, const Tag& root, std::string metadata) {
    std::ofstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Failed to save file: " + filename + "\n");
    trim_string(metadata);
    file << metadata << '\n' << root.string();
    file.close();
}

void load(const std::string& filename, Tag& root, std::string& metadata) {
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Failed to load file: " + filename + "\n");
    // Load code
    file.close();
}

// Tag

Tag::Tag(const std::string& name, bool atomic) {
    if (name.empty()) throw std::invalid_argument("Empty tag name!");
    if (!tag_passed(name)) throw std::invalid_argument("Specific symbol found in tag name!");
    this->atomic = atomic;
    this->name = name;
    ptr_parent = nullptr;
}

Tag* Tag::add_child(const std::string& name, bool atomic, int pos) {
    return add_child(Tag(name, atomic), pos);
}

Tag* Tag::add_child(const std::string& name, int pos) {
    return add_child(Tag(name), pos);
}

Tag* Tag::add_child(const Tag& child, int pos) {
    if (this->atomic) return nullptr;
    if (pos < 0) pos += childs.size() + 1;
    if (pos < 0 || pos > childs.size()) return nullptr;
    childs.insert(childs.begin() + pos, child)->ptr_parent = this;
    return &childs[pos];
}

void Tag::del_child(const std::string& name, int pos) {
    if (pos < 0) pos += childs.size();
    if (pos < 0 || pos >= childs.size()) return;
    for (auto i = childs.begin() + pos; i != childs.end(); i++) {
        if (i->name == name) {
            childs.erase(i);
            break;
        }
    }
}

void Tag::del_child(int pos) {
    if (pos < 0) pos += childs.size();
    if (pos < 0 || pos >= childs.size()) return;
    childs.erase(childs.begin() + pos);
}

Tag* Tag::get_child(const std::string& name, int pos) {
    if (pos < 0) pos += childs.size();
    if (pos < 0 || pos >= childs.size()) return nullptr;
    for (int i = pos; i < childs.size(); i++) if (childs[i].name == name) return &childs[i];
    return nullptr;
}

Tag* Tag::get_child(int pos) {
    if (pos < 0) pos += childs.size();
    if (pos < 0 || pos >= childs.size()) return nullptr;
    return &childs[pos];
}

Tag* Tag::parent() const {
    return ptr_parent;
}

bool Tag::add_name(const std::string& p_name) {
    if (!tag_passed(name)) return false;
    name += p_name;
    return true;
}

bool Tag::set_name(const std::string& p_name) {
    if (name.empty()) return false;
    if (!tag_passed(name)) return false;
    name = p_name;
    return true;
}

const std::string& Tag::get_name() const {
    return name;
}

bool Tag::add_body(const std::string& p_body) {
    if (!atomic) {
        body += p_body;
        trim_string(body);
        return true;
    }
    return false;
}

bool Tag::set_body(const std::string& p_body) {
    if (!atomic) {
        body = p_body;
        trim_string(body);
        return true;
    }
    return false;
}

const std::string& Tag::get_body() const {
    return body;
}

std::string Tag::string(int level) const {
    if (atomic) return std::string(level, '\t') + "<" + name + (params.empty() ? "" : " " + params) + "/>";

    std::string offset(level, '\t'), b_offset(level + 1, '\t');
    std::string result = offset + "<" + name + (params.empty() ? "" : " " + params) + ">";

    if (!body.empty()) {
        std::size_t sind = 0, eind = body.find('\n');
        // Raw write opportunity check
        if (eind == std::string::npos && childs.empty()) return result + body + "</" + name + ">";

        result += '\n';
        while (eind != std::string::npos) {
            result += b_offset + body.substr(sind, eind - sind + 1);
            sind = eind + 1;
            eind = body.find('\n', sind);
        }
        result += b_offset + body.substr(sind) + '\n';
    }
    else {
        // Raw write opportunity check
        if (childs.empty()) return result + "</" + name + ">";
        result += '\n';
    }
    
    for (auto& i : childs) result += i.string(level + 1) + '\n';
    return result + offset + "</" + name + ">";
}
