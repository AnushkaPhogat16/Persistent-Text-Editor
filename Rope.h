#ifndef ROPE_H

#define ROPE_H
#include <string>
using namespace std;

// structure for a node in persistent rope
struct RopeNode{
    RopeNode* left; //pointer to lchild (null for leaf nodes)
    RopeNode* right; 
    string str;  //Stores actual string (only in leaf nodes)
    int weight; //Length of left subtree (or length of str if leaf node)
    int totalWeight; //total length of rope rooted at this node
    
    //constructor for leaf node
    RopeNode(const string& s);

    //constructor for internal node
    RopeNode(RopeNode* l, RopeNode* r);    

};

//build a rope from a string (creates a leaf node)
RopeNode* buildRope(const string &s);

//update a node's wt fields based on children
void update(RopeNode* node);

//concatenation
RopeNode* concat(RopeNode* left, RopeNode* right);

//split rope at given index
void split(RopeNode* root, int index, RopeNode*& left, RopeNode*& right);

//insert string s at pos-> return new rope version
RopeNode* insert(RopeNode* root, int pos, const string& s);

//delete len characters starting from pos-> return new rope version
RopeNode* deleteRange(RopeNode* root, int pos, int len);

//convert the rope into a standard string(in-order traversal)
string toString(RopeNode* root);

//Free memory
void deleteRope(RopeNode* root);


#endif 