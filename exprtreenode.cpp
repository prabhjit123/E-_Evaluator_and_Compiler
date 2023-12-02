/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"
ExprTreeNode::ExprTreeNode()
{
    evaluated_value = new UnlimitedRational();
    type = ""; 
    left = nullptr;
    right = nullptr;
    id = "";
    val = new UnlimitedRational();
};
ExprTreeNode::ExprTreeNode(string t, UnlimitedInt * v)
{
    type = t;
    UnlimitedInt * one = new UnlimitedInt(1);
    UnlimitedRational * temp = new UnlimitedRational(v,one);
    evaluated_value = temp;
    left = nullptr;
    right = nullptr;
    id = "";
    val = new UnlimitedRational();
};
ExprTreeNode::ExprTreeNode(string t, UnlimitedRational * v)
{
    val = new UnlimitedRational();
    type = t;
    evaluated_value = v;
    left = nullptr;
    right = nullptr;
    id = "";

};

ExprTreeNode::~ExprTreeNode()
{
    delete left;
    delete right;
    delete evaluated_value;
    delete val;
}