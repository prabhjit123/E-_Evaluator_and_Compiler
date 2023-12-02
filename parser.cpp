/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"
//Write your code below this line
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
        if (subtree[2]=="+")        // (2+4)
    {
        root->type = "ADD";
        if (isinteger(subtree[1])==1)
        {
            left_ptr->type = "VAL"; 
            left_ptr->num = stoi(subtree[1]);
        }
        else
        {
            left_ptr->type = "VAR";
            left_ptr->id = subtree[1];
        };
        if (isinteger(subtree[3])==1)
        {
            right_ptr->type = "VAL";
            right_ptr->num = stoi(subtree[3]);
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
            left_ptr->num = stoi(subtree[1]);
        }
        else
        { 
            left_ptr->type = "VAR";
            left_ptr->id = subtree[1];
        };
        if (isinteger(subtree[3])==1)
        {
            right_ptr->type = "VAL";
            right_ptr->num = stoi(subtree[3]);
        }
        else
        {
            right_ptr->type = "VAR";
            right_ptr->id = subtree[3];
        };
    }
        else if (subtree[2]=="*")
    {
        root->type = "MUL";
        if (isinteger(subtree[1])==1)
        {
            left_ptr->type = "VAL";
            left_ptr->num = stoi(subtree[1]);
        } 
        else
        {
            left_ptr->type = "VAR";
            left_ptr->id = subtree[1];
        }; 
        if (isinteger(subtree[3])==1)
        {
            right_ptr->type = "VAL";
            right_ptr->num = stoi(subtree[3]);
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
            left_ptr->num = stoi(subtree[1]);
        }
        else
        {
            left_ptr->type = "VAR";
            left_ptr->id = subtree[1];
        };
        if (isinteger(subtree[3])==1)
        {
            right_ptr->type = "VAL";
            right_ptr->num = stoi(subtree[3]);
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
                    right_ptr->num = stoi(subtree[count+2]);
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
                    left_ptr->num = stoi(subtree[1]);
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

Parser::Parser()
{
    symtable = new SymbolTable();
}

void Parser::parse(vector<string> expression)
{
    ExprTreeNode * root = new ExprTreeNode();
    ExprTreeNode * left_ptr = new ExprTreeNode();
    ExprTreeNode * right_ptr = new ExprTreeNode();
    root->type = ":=";
    if (expression[0] == "del")
    {
        left_ptr->type = "DEL";
    }
    else if (expression[0] == "ret")
    {
        left_ptr->type = "RET";
    }
    else
    {
        left_ptr->type = "VAR";
        left_ptr->id = expression[0];
    }
    vector<string> right_subtree = vector<string>();
    for (int i=2; i<(int)(expression.size()); i++)
    {
        right_subtree.push_back(expression[i]);
    }
    if (right_subtree.size()==1)
    {
        if (isinteger(right_subtree[0])==1)
        {
            right_ptr->type = "VAL";
            right_ptr->num = stoi(right_subtree[0]);
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
    if (root->left->type == "VAR")
    {
        if (symtable->search(root->left->id)==-2)
        {
            symtable->insert(root->left->id);
        }
    }
    else if (root->left->type == "DEL")
    {
        if (symtable->search(root->right->id)!=-2)
        {
        this->last_deleted = symtable->search(root->right->id);
        }
        symtable->remove(root->right->id);
    }
}

void DESTROY(ExprTreeNode * cur) {
    if(cur != NULL) {
            DESTROY(cur->left);
            DESTROY(cur->right);
    }
}

Parser::~Parser()
{
    delete symtable;
    for (int i = 0; i < (int)(expr_trees.size()); i++)
    {
        delete expr_trees[i];
    }
}



// int main()
// {
//     Parser * parsing = new Parser();
//     vector <string> v1;
//     v1.push_back("h0");
//     v1.push_back(":=");
//     v1.push_back("23");
//     vector <string> v2;
//     v2.push_back("h1");
//     v2.push_back(":=");
//     v2.push_back("23");
//     vector <string> v3;
//     v3.push_back("del");
//     v3.push_back(":=");
//     v3.push_back("h1");
//     vector <string> v4;
//     v4.push_back("h2");
//     v4.push_back(":=");
//     v4.push_back("(");
//     v4.push_back("2");
//     v4.push_back("/");
//     v4.push_back("(");
//     v4.push_back("3");
//     v4.push_back("+");
//     v4.push_back("4");
//     v4.push_back(")");
//     v4.push_back(")");
//     parsing->parse(v1);
//     parsing->parse(v2);
//     parsing->parse(v3);
//     parsing->parse(v4);
//     inorderTraversalHelper_((parsing->expr_trees)[0]);
//     cout << parsing->symtable->get_root()->left;

// }
