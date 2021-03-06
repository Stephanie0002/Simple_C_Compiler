#ifndef _GRAMMARTREE_H
#define _GRAMMARTREE_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include "utils.h"

using namespace std;

struct grammarTree
{
    string name;
    string content;
    int lineno;
    int id;
    struct grammarTree *left; // 1st child
    struct grammarTree *right; // next sibling
	// prep for tailor; classified on Nb_opr
	using Type_t = enum { BinExpr, List, Garbage, NA };
	Type_t type() const {
		if (string("(),;none").find(name) != string::npos) {
			return Garbage;
		}
		else if (name.find("list") != string::npos) {
			return List;
		}
		else {
			for (string &&s : { "AddExp", "MulExp", "RelExp", "EqExp", "LAndExp", "LOrExp" }) {
				if (name == s) {
					return BinExpr;
				}
			}
			return NA;
		}
	}
	bool orphan() { return right == nullptr; }
	int nb_child() {
		int cnt = 0;
		if (auto c = left) {
			while (c) {
				cnt++;
				c = c->right;
			}
		}
		return cnt;
	}
	grammarTree *fold_lchain() {
		grammarTree *rv = this->left;
		// rebuild sibling ptr
		grammarTree *sib = rv;
		while (sib->right) {
			sib = sib->right;
		}
		sib->right = this->right;
		// isolate & delete
		this->left = this->right = nullptr;
		delete this;
		return rv;
	}
	grammarTree *fold_rchain() {
		grammarTree *rv = this->right;
		this->left = this->right = nullptr;
		delete this;
		return rv;
	}
	void tailor(); // to be called from root
	grammarTree *tailor_inner();
	// cascading deletion
	~grammarTree() {
		delete left;
		delete right;
	}
};

grammarTree *createGrammarTree(string name, int num, ...);
grammarTree *addNullNode(string name, int lineno, int col);
void floorTraverse(grammarTree *root);
void nodePrint(grammarTree *root, string out_name, bool verbose);

#endif