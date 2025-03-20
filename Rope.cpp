#include "Rope.h"
#include <cassert>
#include <iostream>
using namespace std;

//const for leaf node
RopeNode:: RopeNode(const string& s) : left(nullptr), right(nullptr), str(s){
    weight = s.size();
    totalWeight = s.size();
}

//const for internal node
RopeNode:: RopeNode(RopeNode* l, RopeNode* r): left(l), right(r), str(""){
    weight = (l ? l->totalWeight : 0);
    totalWeight = weight + (r ? r->totalWeight : 0);
}

RopeNode* buildRope(const string &s){
    return new RopeNode(s);
}

void update(RopeNode* node){
    if(!node) return; //prevents null pointer access

    //handling leaf nodes
    if(!node->left && !node->right){
        node->weight = node->str.size();
        node->totalWeight = node->str.size();
    }else{
        //handling internal nodes
        node->weight = node->left ? node->left->totalWeight : 0;
        node->totalWeight = node->weight + (node->right ? node->right->totalWeight : 0);
    }
}

RopeNode* concat(RopeNode* left, RopeNode* right){
    if(!left) return right;
    if(!right) return left;

    RopeNode* node = new RopeNode(left, right);
    update(node);
    return node;
}

void split(RopeNode* root, int index, RopeNode*& left, RopeNode*& right){
    if(!root){
        left = right = nullptr;
        return;
    }

    //Leaf node: split the string
    if(!root->left && !root->right){
        if(index >= (int)root->str.size()){
            left = new RopeNode(root->str);
            right = nullptr;
        }else if(index <= 0){
            right = new RopeNode(root->str);
            left = nullptr;
        }else{
            //0 < index < length
            string lStr = root->str.substr(0, index);
            string rStr = root->str.substr(index);

            left = new RopeNode(lStr);
            right = new RopeNode(rStr);
        }
        return;
    }

    //Internal node: decide whether to split l or r
    if(index < root->weight){
        //split happens in l subtree
        RopeNode* l;
        RopeNode* r;

        split(root->left, index, l, r);
        left = l;
        RopeNode* newRight = concat(r, root->right);
        right = newRight;
    }else if(index == root->weight){
        left = root->left;
        right = root->right;
    }else{
        //split happens in r subtree
        //index > root->weight
        RopeNode* l;
        RopeNode* r;
        split(root->right, index - root->weight, l, r);
        RopeNode* newLeft = concat(root->left, l);
        left = newLeft;
        right = r;
    }
}

RopeNode* insert(RopeNode* root, int pos, const string& s){
    RopeNode* left;
    RopeNode* right;
    split(root, pos, left, right);
    RopeNode* middle = buildRope(s);
    return concat(concat(left, middle), right);
}

RopeNode* deleteRange(RopeNode* root, int pos, int len){
    RopeNode* left;
    RopeNode* mid;
    RopeNode* right;

    split(root, pos, left, mid);
    split(mid, len, mid, right);

    return concat(left, right);
}

string toString(RopeNode* root){
    if(!root) return "";
    if(!root->left && !root->right) return root->str;
    return toString(root->left) + toString(root->right);
}

void deleteRope(RopeNode* root) {
    if (!root) return;
    deleteRope(root->left);
    deleteRope(root->right);
    delete root;
}
