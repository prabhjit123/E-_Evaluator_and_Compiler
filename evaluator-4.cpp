
/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"
#include<iostream>
Evaluator::Evaluator()
{
    expr_trees = vector <ExprTreeNode*>();
    symtable = new SymbolTable();
}
Evaluator::~Evaluator()
{
    delete symtable;
}
bool isinteger(string k)
{
    if (k[0]>=48 && k[0]<=57)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool simple_case(vector <string> expression)
{
    int i = 1;
    int count = 0;
    while(i<(int)(expression.size())-1)
    {
        if (expression[i]=="(")
        {
            count++;
        }
        else
        {
            count--;
        }
        i++;
        if (count == 0 && i!=(int)(expression.size())-1)
        {    
            break;
        }
    }
    if (i == (int)(expression.size())-1)
    {
        return true;
    }
    else
    {
        return false;
    }
};

string choose(string k)
{
    if (k=="+")
    {
        return "ADD";
    }
    else if (k=="-")
    {
        return "SUB";
    }
    else if (k=="*")
    {
        return "MUL";
    }
    else if (k=="/")
    {
        return "DIV";
    }
    return "MOD";
}

ExprTreeNode * parse_custom(vector<string> subtree)
{
    ExprTreeNode * root = new ExprTreeNode();
    ExprTreeNode * left_ptr = new ExprTreeNode();
    ExprTreeNode * right_ptr = new ExprTreeNode();
    /*
    This section contains the code to reduce the subtree expression to just vector of brackets
    */
    vector<string> brackets = vector<string>();
    for (int i=0; i<(int)(subtree.size()); i++)
    {
        if (subtree[i]=="(" || subtree[i]==")")
        {
        brackets.push_back(subtree[i]);
        };
    }
    //All cases in the base case
    if ((int)(brackets.size())==2)
    {
        if (subtree[2]=="+")
    {
        root->type = "ADD";
        if (isinteger(subtree[1])==1)
        {
            left_ptr->type = "VAL"; 
            UnlimitedInt * one = new UnlimitedInt(1);
            UnlimitedInt * val = new UnlimitedInt(subtree[1]);
            UnlimitedRational * temp = new UnlimitedRational(val,one);
            left_ptr->val = temp;
            left_ptr->evaluated_value = temp;
        }
        else
        {
            left_ptr->type = "VAR";
            left_ptr->id = subtree[1];
        };
        if (isinteger(subtree[3])==1)
        {
            right_ptr->type = "VAL";
            UnlimitedInt * one = new UnlimitedInt(1);
            UnlimitedInt * val = new UnlimitedInt(subtree[3]);
            UnlimitedRational * temp = new UnlimitedRational(val,one);
            right_ptr->val = temp;
            right_ptr->evaluated_value = temp;
        }
        else
        {
            right_ptr->type = "VAR";
            right_ptr->id = subtree[3];
        };
    }
        else if (subtree[2]=="-")
    {
        root->type = "SUB";
        if (isinteger(subtree[1])==1)
        {
            left_ptr->type = "VAL";
            UnlimitedInt * one = new UnlimitedInt(1);
            UnlimitedInt * val = new UnlimitedInt(subtree[1]);
            UnlimitedRational * temp = new UnlimitedRational(val,one);
            left_ptr->val = temp;
            left_ptr->evaluated_value = temp;
        }
        else
        { 
            left_ptr->type = "VAR";
            left_ptr->id = subtree[1];
        };
        if (isinteger(subtree[3])==1)
        {
            right_ptr->type = "VAL";
            UnlimitedInt * one = new UnlimitedInt(1);
            UnlimitedInt * val = new UnlimitedInt(subtree[3]);
            UnlimitedRational * temp = new UnlimitedRational(val,one);
            right_ptr->val = temp;
            right_ptr->evaluated_value = temp;
        }
        else
        {
            right_ptr->type = "VAR";
            right_ptr->id = subtree[3]; //()
        };
    }
        else if (subtree[2]=="*")
    {
        root->type = "MUL";
        if (isinteger(subtree[1])==1)
        {
            left_ptr->type = "VAL";
            UnlimitedInt * one = new UnlimitedInt(1);
            UnlimitedInt * val = new UnlimitedInt(subtree[1]);
            UnlimitedRational * temp = new UnlimitedRational(val,one);
            left_ptr->val = temp;
            left_ptr->evaluated_value = temp;
        } 
        else
        {
            left_ptr->type = "VAR";
            left_ptr->id = subtree[1];
        }; 
        if (isinteger(subtree[3])==1)
        {
            right_ptr->type = "VAL";
            UnlimitedInt * one = new UnlimitedInt(1);
            UnlimitedInt * val = new UnlimitedInt(subtree[3]);
            UnlimitedRational * temp = new UnlimitedRational(val,one);
            right_ptr->val = temp;
            right_ptr->evaluated_value = temp;
        }
        else
        {
            right_ptr->type = "VAR";
            right_ptr->id = subtree[3];
        };
    }
        else if (subtree[2]=="/")
    {
        root->type = "DIV";
        if (isinteger(subtree[1])==1)
        {
            left_ptr->type = "VAL";
            UnlimitedInt * one = new UnlimitedInt(1);
            UnlimitedInt * val = new UnlimitedInt(subtree[1]);
            UnlimitedRational * temp = new UnlimitedRational(val,one);
            left_ptr->val = temp;
            left_ptr->evaluated_value = temp;
        }
        else
        {
            left_ptr->type = "VAR";
            left_ptr->id = subtree[1];
        };
        if (isinteger(subtree[3])==1)
        {
            right_ptr->type = "VAL";
            UnlimitedInt * one = new UnlimitedInt(1);
            UnlimitedInt * val = new UnlimitedInt(subtree[3]);
            UnlimitedRational * temp = new UnlimitedRational(val,one);
            right_ptr->val = temp;
            right_ptr->evaluated_value = temp;
        }
        else
        {
            right_ptr->type = "VAR";
            right_ptr->id = subtree[3];
        };
    }
        root->left = left_ptr;
        root->right = right_ptr;
        return root;
    }
    else 
    {
        bool flag = simple_case(brackets);
        if (flag==true)
        {
            if (subtree[1] == "(" && subtree[subtree.size()-2] == ")")
            {
                vector <string> finally;
                for (int i = 1; i<(int)(subtree.size())-1; i++)
                {
                    finally.push_back(subtree[i]);
                };
                return parse_custom(finally);
            }
            else if (subtree[1] == "(" && subtree[subtree.size()-2] != ")")
            {
                vector <string> finally;
                int count = 0;
                for (int i = 1; i<(int)(subtree.size())-2; i++)
                {
                    if (subtree[i]=="(")
                    {
                        count++;
                    }
                    else if (subtree[i]==")")
                    {
                        count--;
                    }
                    finally.push_back(subtree[i]);
                    if (count == 0)
                    {
                        count = i;
                        break;
                    }
                };
                root->type = choose(subtree[count+1]);
                left_ptr =  parse_custom(finally);
                if(isinteger(subtree[count+2])==1)
                {
                    right_ptr->type = "VAL";
                    UnlimitedInt * one = new UnlimitedInt(1);
                    UnlimitedInt * val = new UnlimitedInt(subtree[count+2]);
                    UnlimitedRational * temp = new UnlimitedRational(val,one);
                    right_ptr->val = temp;
                    right_ptr->evaluated_value = temp;
                }
                else
                {
                    right_ptr->type = "VAR";
                    right_ptr->id = subtree[count+2];
                }
            }
            else if (subtree[1] != "(" && subtree[subtree.size()-2] == ")")
            {
                vector <string> finally;
                int count = 0;
                for (int i = 3; i<(int)(subtree.size())-1; i++)
                {
                    if (subtree[i]=="(")
                    {
                        count++;
                    }
                    else if (subtree[i]==")")
                    {
                        count--;
                    }
                    finally.push_back(subtree[i]);
                    if (count == 0)
                    {
                        break;
                    }
                };
                root->type = choose(subtree[2]);
                right_ptr =  parse_custom(finally);
                if(isinteger(subtree[1])==1)
                {
                    left_ptr->type = "VAL";
                    UnlimitedInt * one = new UnlimitedInt(1);
                    UnlimitedInt * val = new UnlimitedInt(subtree[1]);
                    UnlimitedRational * temp = new UnlimitedRational(val,one);
                    left_ptr->evaluated_value = temp;
                    left_ptr->val = temp;
                }
                else
                {
                    left_ptr->type = "VAR";
                    left_ptr->id = subtree[1];
                }
            } 
        }
        else
        {
            vector <string> left_subtree;
            vector <string> right_subtree;
            int count = 0;
            int i = 2;
            count++;
            left_subtree.push_back("(");
            while (count!=0)
            {
                
                if (subtree[i]=="(")
                {
                    count++;
                }
                else if (subtree[i]==")")
                {
                    count--;
                }
                left_subtree.push_back(subtree[i]);
                i++;
            }
            for(int j = i+1; j<(int)(subtree.size())-1; j++)
            {
                right_subtree.push_back(subtree[j]);
            }
            root->type = choose(subtree[i]);
            left_ptr = parse_custom(left_subtree);
            right_ptr = parse_custom(right_subtree);
        }
    }
    root->left = left_ptr;
    root->right = right_ptr;
    return root;
}

void Evaluator::parse(vector<string> code)
{
    ExprTreeNode * root = new ExprTreeNode();
    ExprTreeNode * left_ptr = new ExprTreeNode();
    ExprTreeNode * right_ptr = new ExprTreeNode();
    root->type = ":=";
    left_ptr->type = "VAR";
    left_ptr->id = code[0];
    vector<string> right_subtree = vector<string>();
    for (int i=2; i<(int)(code.size()); i++)
    {
        right_subtree.push_back(code[i]);
    }
    if (right_subtree.size()==1)
    {
        if (isinteger(right_subtree[0])==1)
        {
            right_ptr->type = "VAL";
            UnlimitedInt * one = new UnlimitedInt(1);
            UnlimitedInt * val = new UnlimitedInt(right_subtree[0]);
            UnlimitedRational * temp = new UnlimitedRational(val,one);
            right_ptr->val = temp;
            right_ptr->evaluated_value = temp;
        }  
        else
        {
            right_ptr->type = "VAR";
            right_ptr->id = right_subtree[0];
        }  
    }
    else
    {
    right_ptr = parse_custom(right_subtree);
    };
    root->left = left_ptr;
    root->right = right_ptr;
    expr_trees.push_back(root);
}


UnlimitedRational * operation(UnlimitedRational * i1, UnlimitedRational * i2, string k)
{
    if (k=="ADD")
    {
        return i1->add(i1,i2);
    }
    else if (k=="SUB")
    {
        return i1->sub(i1,i2);
    }
    else if (k=="MUL")
    {
        return i1->mul(i1,i2);
    }
    else if (k=="DIV")
    {
        return i1->div(i1,i2);
    }
    return nullptr;
}


UnlimitedRational * evaluate_value(ExprTreeNode * root, SymbolTable * s1)
{
    if (root==nullptr)
    {
      return nullptr;
    }
    else if (root->left == nullptr && root->right == nullptr)
    {
        if (root->type == "VAR")
        {
            return s1->search(root->id);
        }
        else if (root->type == "VAL")
        {
            return root->val;
        }
    }
    else
        {
            root->evaluated_value = operation(evaluate_value(root->left,s1), evaluate_value(root->right,s1),root->type);
            return root->evaluated_value;
        };  
    
    return nullptr;
};
void Evaluator::eval()
{   
    int i = (int)(expr_trees.size())-1;
    expr_trees[i]->evaluated_value = evaluate_value(expr_trees[i]->right,symtable);
    symtable->insert(expr_trees[i]->left->id, expr_trees[i]->evaluated_value);     
};


// int main()
// {
//     Evaluator * evaluator = new Evaluator();
//     vector <string> s1_v;
//     vector <string> s2_v;
//     s1_v.push_back("ap1");
//     s1_v.push_back(":=");
//     s1_v.push_back("4");
       
//     //ap1:=4

//     s2_v.push_back("ap2");
//     s2_v.push_back(":=");
//     s2_v.push_back("(");
//     s2_v.push_back("ap1");
//     s2_v.push_back("-");
//     s2_v.push_back("("); 
//     s2_v.push_back("4");
//     s2_v.push_back("/");
//     s2_v.push_back("3");
//     s2_v.push_back(")");
//     s2_v.push_back(")");

//     //ap2:=(ap1-(4/3))

//     evaluator->parse(s1_v);
//     inorderTraversal(evaluator->expr_trees[0]);
//     evaluator->eval();
//     cout << evaluator->expr_trees[0]->evaluated_value->get_frac_str() + " ";
//     evaluator->parse(s2_v);
//     cout << endl;
//     inorderTraversal(evaluator->expr_trees[1]);
//     evaluator->eval();
//     cout << endl;
//     cout << evaluator->expr_trees[1]->right->evaluated_value->get_frac_str() + " ";
//     // cout << "Final answer -> ";
//     // cout << evaluator->expr_trees[1]->evaluated_value->get_frac_str() + " ";
//     // cout << evaluator->expr_trees[1]->right->evaluated_value->get_frac_str()<< "<-DIV's evaluated value";
//     // delete evaluator;
// }
