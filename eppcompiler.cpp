/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"
//Write your code below this line

EPPCompiler::EPPCompiler()
{
    memory_size = 0;
    output_file ="FinalOutput.txt";

}

EPPCompiler::EPPCompiler(string out_file,int mem_limit)
{
    this->memory_size = mem_limit;
    this->output_file = out_file;
    for (int i = 0; i<mem_limit; i++)
    {
        mem_loc.push_back(i);
    }
}

void EPPCompiler::compile(vector <vector <string> > code)
{
    std::ofstream outputFile(output_file);

    int t_size = (int)(code.size());
    int temp = 0;
    for (int i = 0; i < t_size; i++)
    {
        targ.parse(code[i]);
        if (targ.expr_trees[(int)(targ.expr_trees.size())-1]->left->type == "VAR")
        {
            targ.symtable->assign_address(targ.expr_trees[(int)(targ.expr_trees.size())-1]->left->id,mem_loc[0]);
            mem_loc.erase(mem_loc.begin(),mem_loc.begin()+1);
            write_to_file(generate_targ_commands());
        }
        else if (targ.expr_trees[(int)(targ.expr_trees.size())-1]->left->type == "DEL")
        {

            mem_loc.push_back(targ.last_deleted);
            write_to_file(generate_targ_commands());
             //This eventually removes the memory occupied by the element
        }
        else if (targ.expr_trees[(int)(targ.expr_trees.size())-1]->left->type == "RET")
        {
            targ.parse(code[i]);
            write_to_file(generate_targ_commands());
        }
        
    }
}

void add_string(ExprTreeNode * node ,vector <string> &v, SymbolTable * symtable)
{
    
    ExprTreeNode * current = new ExprTreeNode();
    if (node->type == ":=")
    {
        current = node->right;
    }
    else
    {
        current = node;
    }
    string temp = "";
    if (current->left == NULL && current ->right == NULL)
    {
        if (current->type == "VAL")
        {
            temp = "PUSH " + to_string(current->num);
        }
        else if (current->type == "VAR")
        {
            int address_current = symtable->search(current->id);
            if (address_current!=-2)
            {
            temp = "PUSH mem[" + to_string(address_current) + "]";
            }
        }
        v.push_back(temp);
    }
    else
    { 
        add_string(current->right,v,symtable);
        add_string(current->left,v,symtable);
        if (current->type != ":=")
        {
        v.push_back(current->type);
        };
        
    }
}

vector<string> EPPCompiler::generate_targ_commands()
{
    vector <string> v;
    string temp = "";
    ExprTreeNode * current = targ.expr_trees[(int)(targ.expr_trees.size())-1];
    if (current->left->type == "DEL")
    {
        int current_address = targ.symtable->search(current->right->id);
        temp = "DEL = mem[" + to_string(targ.last_deleted) + "]";
        v.push_back(temp); 
    }
    else if (current->left->type == "RET")
    {
        add_string(current, v, targ.symtable);
        temp = "RET = POP";
        v.push_back(temp);
    }
    else if (current->left->type == "VAR")
    {
        add_string(current, v, targ.symtable);
        temp = "mem[" + to_string(targ.symtable->search(current->left->id)) + "] = POP";
        v.push_back(temp);
    }
    return v;
}

void EPPCompiler::write_to_file(vector<string> commands)
{
    std::ofstream outputFile;
    outputFile.open(output_file,ios::app);
    for (int i = 0; i< (int)(commands.size()); i++)
    {
        outputFile << commands[i] << std::endl;
    }
    outputFile.close();
}

EPPCompiler::~EPPCompiler()
{
}
//
//int main()
//{
//    EPPCompiler c("prab.txt",5);
//    vector <string> v1;
//    v1.push_back("x");
//    v1.push_back(":=");
//    v1.push_back("3");
//     vector <string> v2;
//    v2.push_back("y");
//     v2.push_back(":=");
//     v2.push_back("5");
//
////     vector <string> v3;
////     v3.push_back("ret");
////     v3.push_back(":=");
////     v3.push_back("h1");
////     vector <string> v4;
////     v4.push_back("h2");
////     v4.push_back(":=");
////     v4.push_back("(");
////     v4.push_back("2");
////     v4.push_back("/");
////     v4.push_back("(");
////     v4.push_back("3");
////     v4.push_back("+");
////     v4.push_back("4");
////     v4.push_back(")");
////     v4.push_back(")");
//    vector <vector<string> > final;
//    final.push_back(v1);
//     final.push_back(v2);
////     final.push_back(v3);
////     final.push_back(v4);
//    c.compile(final);
// }
