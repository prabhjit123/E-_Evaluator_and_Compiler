/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "entry.h"
using namespace std;

SymEntry::SymEntry()
{
    key = "";
    left = nullptr;
    right = nullptr;
}
SymEntry::SymEntry(string k, UnlimitedRational * v)
{
    key = k;
    val = v;
    left = nullptr;
    right = nullptr;
}
SymEntry::~SymEntry()
{
    delete left;
    delete right;
}
