#include <filesystem>
#include <iostream>
#include <set>

#include <keyparser/binds.hpp>
#include <keyparser/parser.hpp>

#include "xml/tag.hpp"

namespace fs = std::filesystem;

namespace root {
    Tag xml("wallpapers");
    Tag tag("wallpaper");
    std::string img_save_path = "/home/vladimir/.local/share/backgrounds";
    std::string xml_save_path = "/home/vladimir/.local/share/gnome-background-properties";
    std::string xml_meta_data = "<?xml version=\"1.0\"?>\n<!DOCTYPE wallpapers SYSTEM \"gnome-wp-list.dtd\">";
    std::set<std::string> imgs_to_copy;

    void at_key_0(const keyparser::Args& data) {
        fs::path path = fs::path(img_save_path + '/' + data[0]).lexically_normal();
        if (path.parent_path() != img_save_path) throw std::invalid_argument("Wrong wallpapers name!");
        img_save_path = path.string() + '/';
        xml_save_path = fs::path(xml_save_path + '/' + data[0] + ".xml").lexically_normal().string();
        
        tag.add_child("name");
        tag.add_child("filename");
        tag.add_child("options")->set_body("zoom");
        tag.add_child("shade_type")->set_body("solid");
        tag.add_child("pcolor")->set_body("#FFFFFF");
        tag.add_child("scolor")->set_body("#FFFFFF");
    }

    void at_key_2(const keyparser::Args& data) {
        tag.get_child("options")->set_body(data[0]);
    }

    void at_key_3(const keyparser::Args& data) {
        tag.get_child("shade-type")->set_body(data[0]);
    }

    void at_key_4(const keyparser::Args& data) {
        tag.get_child("pcolor")->set_body(data[0]);
        tag.get_child("scolor")->set_body(data[1]);
    }

    void at_finish() {
        if (fs::exists(xml_save_path) || fs::exists(img_save_path)) {
            std::cout << "Background with this name already exists. Overwrite them (Y/N)?\n";
            char check = std::cin.get();
            if (check != 'Y' && check != 'y') return;
            if (fs::exists(img_save_path)) fs::remove_all(img_save_path);
        }
        save(xml_save_path, xml, xml_meta_data);
        fs::create_directory(img_save_path);
        for (auto& i : imgs_to_copy) fs::copy_file(i, img_save_path/fs::path(i).filename());
    }
}

namespace wallpaper {
    Tag tag("wallpaper");
    bool save_l, save_d;

    void at_key_0(const keyparser::Args& data) {
        fs::path filename_path = fs::path(data[1]).lexically_normal();
        if (!fs::exists(filename_path)) throw std::invalid_argument("Wrong image filename!");
        root::imgs_to_copy.insert(filename_path.string());

        save_d = save_l = false;
        tag = root::tag;

        tag.get_child("name")->set_body(data[0]);
        tag.get_child("filename")->set_body(root::img_save_path + filename_path.filename().string());

        if (data.size() == 3) {
            filename_path = fs::path(data[2]).lexically_normal();
            if (!fs::exists(filename_path)) throw std::invalid_argument("Wrong image filename!");
            root::imgs_to_copy.insert(filename_path.string());
            tag.add_child("filename-dark", 2)->set_body(root::img_save_path + filename_path.filename().string());
        }
    }

    void at_key_2(const keyparser::Args& data) {
        tag.get_child("options")->set_body(data[0]);
    }

    void at_key_3(const keyparser::Args& data) {
        tag.get_child("shade-type")->set_body(data[0]);
    }

    void at_key_4(const keyparser::Args& data) {
        tag.get_child("pcolor")->set_body(data[0]);
        tag.get_child("scolor")->set_body(data[1]);
    }

    void at_key_5(const keyparser::Args& data) {
        switch (data[0][0]) {
        case 'l':
            save_l = true;
            break;
        case 'd':
            save_d = true;
            break;
        case 'a':
            save_d = save_l = true;
            break;
        }
    }

    void at_finish() {
        root::xml.add_child(tag);
        if (!tag.get_child("filename-dark")) return;
        if (save_l) {
            Tag* child_tag = root::xml.add_child(tag);
            child_tag->get_child("name")->add_body("_light");
            child_tag->del_child("filename-dark");
        }
        if (save_d) {
            Tag* child_tag = root::xml.add_child(tag);
            child_tag->get_child("name")->add_body("_dark");
            child_tag->get_child("filename")->set_body(child_tag->get_child("filename-dark")->get_body());
            child_tag->del_child("filename-dark");
        }
    }
}

int main(int argc, char *argv[]) {
    keyparser::Key key_1('w', "wallpaper");
    keyparser::Key key_2('o', "options");
    keyparser::Key key_3('s', "shade-type");
    keyparser::Key key_4('c', "color");
    keyparser::Key key_5("save-each");

    // Parser setting up \start
    keyparser::Parser parser(1), *parser_2 = parser.addKey(key_1, 2, 3);
    parser.addKey(key_2, 1);
    parser.addKey(key_3, 1);
    parser.addKey(key_4, 2);
    parser_2->addKey(key_2, 1);
    parser_2->addKey(key_3, 1);
    parser_2->addKey(key_4, 2);
    parser_2->addKey(key_5, 1);
    // Parser setting up \end

    // Binds setting up \start
    keyparser::Binds binds_2(wallpaper::at_key_0);
    binds_2.bind(key_2, wallpaper::at_key_2);
    binds_2.bind(key_3, wallpaper::at_key_3);
    binds_2.bind(key_4, wallpaper::at_key_4);
    binds_2.bind(key_5, wallpaper::at_key_5);
    binds_2.after_all(wallpaper::at_finish);

    keyparser::Binds binds(root::at_key_0);
    binds.bind(key_1, binds_2);
    binds.bind(key_2, root::at_key_2);
    binds.bind(key_3, root::at_key_3);
    binds.bind(key_4, root::at_key_4);
    binds.after_all(root::at_finish);
    // Binds setting up \end

    binds.execute(parser.parse(argc, argv));
    return 0;
}
