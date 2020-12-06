#include <iostream>
#include <list>

class Tree {

public:
	Tree* left;
	Tree* right;
	Tree* parent;
	char data;
	int weight;

	Tree(char _d, Tree* _p) : data(_d), weight(0), left(nullptr), right(nullptr), parent(_p) {}
	~Tree() { if (left) delete left; if (right) delete right; }

	void operator++ (int) { weight++; if (parent) (*parent)++; }
};

class TreeList {

private:
	std::list<Tree*> list;
	 
public:
	~TreeList() {

		delete *list.begin();
	}

	void add(char symb) {

		bool new_symb = false;

		for (std::list<Tree*>::iterator i = list.begin(); i != list.end(); i++)
			if ((*i)->data == symb) {

				(*(*i))++;
				new_symb = true;
			}

		if (!new_symb) {

			Tree* esc = *list.end();
			esc->right = new Tree(symb, esc);
			(*esc->right)++;
			esc->left = new Tree(0, esc);
			list.push_back(esc->right);
			list.push_back(esc->left);
		}
	}

	void rebuild() {

		Tree* prev;
		Tree* mass;

		for (std::list<Tree*>::iterator i = list.end(); i != list.begin(); --i) {

			if (prev) {

				if (prev->weight > (*i)->weight) {

					mass = prev;
				}
			}

			prev = *i;
		}
	}
};

int main() {

	return 0;
}