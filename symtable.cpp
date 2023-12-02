/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
using namespace std;
#include <iostream>
SymbolTable::SymbolTable()
{
    size = 0;
    root = nullptr;
}
SymbolTable::~SymbolTable()
{
    size = 0;
    root = nullptr;
}

void SymbolTable::insert(string k, UnlimitedRational* v)
{
    SymEntry * temp = new SymEntry(k, v); 
    if (root == nullptr) 
    {
        root = temp;
        size++; 
    }
    else
    {
        SymEntry * ptr_1 = root; 
        SymEntry * ptr_2 = nullptr; 

        while (ptr_1 != nullptr) 
        {
            ptr_2 = ptr_1; 
            if (ptr_1->key > k)
            {
                ptr_1 = ptr_1->left; 
            }
            else if (ptr_1->key < k)
            {
                ptr_1 = ptr_1->right; 
            }
        }
        if (ptr_2->key > k)
        {
            ptr_2->left = temp; 
            size++;
        }
        else
        {
            ptr_2->right = temp; 
            size++;
        };
    };
};

void swap_nodes(SymEntry* n1, SymEntry* n2)
{
    string temp_key = n1->key;
    UnlimitedRational * temp_val = n1->val;

    n1->key = n2->key;
    n1->val = n2->val;

    n2->key = temp_key;
    n2->val = temp_val;
}
void SymbolTable::remove(string k)
{
    /*
    1. Find the node which is to be deleted by moving a pointer to that node and one to its parent node
    2. If the node is a leaf, simply delete the node.
    3. If it has one child, exchange them and delete the node.
    4. If it has two children, find the successor (in this case the minimum element of the right subtree) and then swap and call delete recursively
    */
    if (root==nullptr)
    {
        return;
    }
    else
    {
        SymEntry * ptr_1 = root;
        SymEntry * ptr_2 = nullptr;
        while (ptr_1->key != k )
        {
            if (ptr_1->key > k)
            {
                ptr_2 = ptr_1;
                ptr_1 = ptr_1->left;
            }
            else if (ptr_1->key < k)
            {
                ptr_2 = ptr_1;
                ptr_1 = ptr_1->right;
            };
        };
        if (ptr_1 == nullptr)
        {
            return;
        }
        else
        {
            //Node is a leaf
            if (ptr_1->left == nullptr && ptr_1->right == nullptr)
            {
                if (ptr_2->left == ptr_1)
                {
                    ptr_2->left = nullptr;
                    size--;
                    delete ptr_1;
                }
                else if (ptr_2->right == ptr_1)
                {
                    ptr_2->right = nullptr;
                    size--;
                    delete ptr_1;
                }
            }
            //Node has only one child
            else if (ptr_1->left != nullptr && ptr_1->right == nullptr)
            {
                if (ptr_2->left == ptr_1)
                {
                    ptr_2->left = ptr_1->left;
                    ptr_1->left = nullptr;
                    size--;
                    delete ptr_1;
                }
                else if (ptr_2->right == ptr_1)
                {
                    ptr_2->right = ptr_1->left;
                    ptr_1->left = nullptr;
                    size--;
                    delete ptr_1;
                }
            }
            else if (ptr_1->left == nullptr && ptr_1->right != nullptr)
            {
                if (ptr_2->left == ptr_1)
                {
                    ptr_2->left = ptr_1->right;
                    ptr_1->right = nullptr;
                    size--;
                    delete ptr_1;
                }
                else if (ptr_2->right == ptr_1)
                {
                    ptr_2->right = ptr_1->right;
                    ptr_1->right = nullptr;
                    size--;
                    delete ptr_1;
                }
            }
            //Node has two children
            else
            {
                ptr_2 = ptr_1; //Moving the ptr_2 to the node to be deleted
                ptr_1 = ptr_1->right; 
                SymEntry * ptr_3 = nullptr;
                while (ptr_1->left != nullptr)
                {
                    ptr_3 = ptr_1;
                    ptr_1 = ptr_1->left;
                } //Moving ptr_1 to the sucessor
                if (ptr_3 == nullptr)
                {                   
                    swap_nodes(ptr_1,ptr_2);
                    ptr_2->right = ptr_1->right;
                    ptr_1->right = nullptr;
                    size--;
                    delete ptr_1;
                }
                else
                {
                swap_nodes(ptr_1,ptr_2); //Swapping with the successor
                ptr_3->left = ptr_1->right;
                ptr_1->right = nullptr;
                size--;
                delete ptr_1;  //Deleting the exchanged node finally
                };
            };
        };
    };
};

SymEntry * SymbolTable::get_root()
{
    return root;
}

UnlimitedRational* SymbolTable::search(string k)
{
    if (root==nullptr)
    {
        return nullptr;
    }
    else if (root->key == k)
    {
        return root->val;
    }
    else
    {
        SymEntry * ptr_1 = root;
        while (ptr_1->key != k )
        {
            if (ptr_1->key > k)
            {
                ptr_1 = ptr_1->left;
            }
            else if (ptr_1->key < k)
            {
                ptr_1 = ptr_1->right;
            };
            if (ptr_1 == nullptr)
            {
                break;
            }
        }
        if (ptr_1 == nullptr)
        {
            return nullptr;
        }
        return ptr_1->val;
    }
    
}

int SymbolTable::get_size()
{
    return size;
}


// int main()
// {
//     SymbolTable * s1 = new SymbolTable();
//     UnlimitedInt * ai1 = new UnlimitedInt(1);
//     UnlimitedInt * ai2 = new UnlimitedInt(3);
//     UnlimitedInt * bi1 = new UnlimitedInt(1);
//     UnlimitedInt * bi2 = new UnlimitedInt(2);
//     UnlimitedRational * u1 = new UnlimitedRational(ai1, ai2);
//     UnlimitedRational * u2 = new UnlimitedRational(bi1, bi2);
//     s1->insert("d", u1);
//     s1->insert("a", u2);
//     s1->insert("m", u1);
//     s1->insert("e", u2);
//     s1->insert("p", u1);
//     s1->insert("n", u2);
//     s1->remove("n");
//     inorderTraversal(s1->get_root());
//     cout << s1->get_size();
// }
