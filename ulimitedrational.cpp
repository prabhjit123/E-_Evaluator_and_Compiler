/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"
using namespace std;
#include <iostream>

UnlimitedRational::UnlimitedRational()
{
    p = new UnlimitedInt(0);
    q = new UnlimitedInt(0);
}

UnlimitedRational::UnlimitedRational(UnlimitedInt * num, UnlimitedInt * den)
{
    p = num;
    q = den;
}

UnlimitedRational::~UnlimitedRational()
{
    delete p;
    delete q;
}

UnlimitedInt * UnlimitedRational::get_p()
{
    return p;
}

UnlimitedInt * UnlimitedRational::get_q()
{
    return q;
}

string UnlimitedRational::get_p_str()
{
    return p->to_string();
}

string UnlimitedRational::get_q_str()
{
    return q->to_string();
}
UnlimitedInt* gcd(UnlimitedInt * n1, UnlimitedInt *n2)
{
    if (n1->get_sign() == 0)
    {
        return n2;
    }
    else
    {
        UnlimitedInt * temp_1 = new UnlimitedInt(-1);
        if (n1->get_sign()==-1)
        {
            n1 = n1->mul(n1,temp_1);
        }
        if (n2->get_sign()==-1)
        {
            n2 = n2->mul(n2,temp_1);
        }
    }
    return gcd(n2->mod(n2,n1), n1);
}

UnlimitedRational* reduce(UnlimitedRational * n)
{
    UnlimitedInt * p = new UnlimitedInt(n->get_p_str());
    UnlimitedInt * q = new UnlimitedInt(n->get_q_str());
    while (gcd(p,q)->to_string()!="1")
    {
        UnlimitedInt * gcd_temp = new UnlimitedInt(gcd(p,q)->to_string());
        p = p->div(p,gcd_temp);
        q = q->div(q,gcd_temp);
        delete gcd_temp;
    }
    UnlimitedRational * n1 = new UnlimitedRational(p,q);
    return n1;
}
UnlimitedRational* UnlimitedRational::add(UnlimitedRational* i1, UnlimitedRational* i2)
{
    UnlimitedInt * a = new UnlimitedInt(i1->get_p_str());
    UnlimitedInt * b = new UnlimitedInt(i1->get_q_str());
    UnlimitedInt * c = new UnlimitedInt(i2->get_p_str());
    UnlimitedInt * d = new UnlimitedInt(i2->get_q_str());
    /*
    a   c     a*d + c*b
    - + -  =  ---------
    b   d        b*d
    */
    if(b->get_sign()==0 || d->get_sign()==0)
    {
        UnlimitedRational * answer = new UnlimitedRational();
        return answer;
    }
    UnlimitedInt * num = a->add(d->mul(a,d), c->mul(c,b));
    UnlimitedInt * den = b->mul(b,d);
    UnlimitedRational * answer = new UnlimitedRational(num,den);
    answer = reduce(answer);
    return answer;
}

UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* i1, UnlimitedRational* i2)
{
    UnlimitedInt * a = i1->get_p();
    UnlimitedInt * b = i1->get_q();
    UnlimitedInt * c = i2->get_p();
    UnlimitedInt * d = i2->get_q();
    /*
    a   c     a*d - c*b
    - - -  =  ---------
    b   d        b*d
    */
    if(b->get_sign()==0 || d->get_sign()==0)
    {
        UnlimitedRational * answer = new UnlimitedRational();
        return answer;
    }
    UnlimitedInt * num = a->sub(d->mul(a,d), c->mul(c,b));
    UnlimitedInt * den = b->mul(b,d);
    UnlimitedRational * answer = new UnlimitedRational(num,den);
    answer = reduce(answer);
    return answer;
}

UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* i1, UnlimitedRational* i2)
{
    UnlimitedInt * a = i1->get_p();
    UnlimitedInt * b = i1->get_q();
    UnlimitedInt * c = i2->get_p();
    UnlimitedInt * d = i2->get_q();
    /*
    a   c    a*c
    - * -  = ---
    b   d    b*d
    */
    if(b->get_sign()==0 || d->get_sign()==0)
    {
        UnlimitedRational * answer = new UnlimitedRational();
        return answer;
    }
    UnlimitedInt * num = a->mul(a,c);
    UnlimitedInt * den = b->mul(b,d);
    UnlimitedRational * answer = new UnlimitedRational(num,den);
    answer = reduce(answer);
    return answer;
}


UnlimitedRational* UnlimitedRational::div(UnlimitedRational* i1, UnlimitedRational* i2)
{
    UnlimitedInt * a = i1->get_p();
    UnlimitedInt * b = i1->get_q();
    UnlimitedInt * c = i2->get_p();
    UnlimitedInt * d = i2->get_q();
    /*
    a   c    a*d
    - / -  = ---
    b   d    b*c
    */
    if(b->get_sign()==0 || c->get_sign()==0 || d->get_sign()==0)
    {
        UnlimitedRational * answer = new UnlimitedRational();
        return answer;
    }
    UnlimitedInt * num = a->mul(a,d);
    UnlimitedInt * den = b->mul(b,c);
    UnlimitedRational * answer = new UnlimitedRational(num,den);
    answer = reduce(answer);
    return answer;
}
string UnlimitedRational::get_frac_str()
{
    return p->to_string() + "/" + q->to_string();
}

// int main()
// {
//     UnlimitedInt *ap = new UnlimitedInt(1);
//     UnlimitedInt *aq = new UnlimitedInt(2);
//     UnlimitedRational *a = new UnlimitedRational(ap, aq);
//     UnlimitedInt *bp = new UnlimitedInt(-1);
//     UnlimitedInt *bq = new UnlimitedInt(2);
//     UnlimitedRational *b = new UnlimitedRational(bp, bq);
//     UnlimitedRational * c = a->add(a,b);
//     // b = reduce(b);
//     cout << c->get_frac_str() << "\n";
// }

// //*** check sub with 1
