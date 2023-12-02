/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"
using namespace std;
#include <iostream>
UnlimitedInt::UnlimitedInt()
{
    sign = 0;
    size = 1;
    capacity = size*2;

}
UnlimitedInt::UnlimitedInt(int k)
{
    if (k>0)
    {
        sign = 1;
    }
    else if (k==0)
    {
        sign = 0;
    }
    else if (k<0)
    {
        sign = -1;
    }
    string string_int = std::to_string(k);
    size = string_int.size();
    capacity = size * 2;
    unlimited_int = new int[capacity];
    if (sign == 1)
    {
    for (int i=0; i<size; i++)
    {
        unlimited_int[i]= string_int[i] - '0';
    }
    }
    if (sign == 0)
    {
        unlimited_int[0]=0;
    }
    if (sign<0)
    {
        size = string_int.size() - 1;
        for (int i=1; i<size+1; i++)
        {
            unlimited_int[i-1]= string_int[i] - '0';
        };
    }
}
UnlimitedInt::UnlimitedInt(string k)
{
    bool flag = true;
    char sign_index = k[0];
    if (sign_index== '-') 
    {
        sign = -1;
    }
    else if (sign_index=='0')
    {
        int i = 0;
        while (k[i]=='0' && i < (int)(k.size()))
        {
            i++;
        }
        if (i==(int)(k.size()))
        {
            sign = 0;
        }
        else
        {
            flag = false;
            size = k.size()-i;
            capacity = size * 2;
            unlimited_int = new int[capacity];
            for(int j = 0; j<size; j++)
            {
                unlimited_int[j] = k[i+j] - '0';
            }
            sign = 1;
        }
    }
    else 
    {
        sign = 1;
    };
    if (sign==1 && flag==true)
    {
        size = k.size();
        capacity = size * 2;
        unlimited_int = new int[capacity];
        for (int i=0; i<size; i++)
        {
            unlimited_int[i]= k[i] - '0';
        };
    }
    else if (sign == 0)
    {
        size=1;
        capacity = size * 2;
        unlimited_int = new int[capacity];
        unlimited_int[0]=0;
    }
    else
    {
        size = k.size()-1;
        capacity = size * 2;
        unlimited_int = new int[capacity];
        for (int i=1; i<size+1; i++)
        {
            unlimited_int[i-1]= k[i] - '0';
        };
    }
}
UnlimitedInt::~UnlimitedInt()
{
    delete [] unlimited_int;
}
int compare(UnlimitedInt* i1, UnlimitedInt* i2)
{
    int size_1 = i1->get_size();
    int size_2 = i2->get_size();
    int sign_1 = i1->get_sign();
    int sign_2 = i2->get_sign();
    int * array_1 = i1->get_array();
    int * array_2 = i2->get_array();
    if (sign_1 >= 0 && sign_2 >= 0)
    {
    if (size_1>size_2)
    {
        return 1;
    }
    else if (size_1<size_2)
    {
        return -1;  
    }
    else
    {
        for (int i = 0; i < size_1; i++)
        {
            if (array_1[i]<array_2[i])
            {
                return -1;
            }
            else if (array_1[i]>array_2[i])
            {
                return 1;
            }
        }
    }
    return 0;
    }
    else if (sign_1 <= 0 && sign_2 <= 0)
    {
        if (size_1>size_2)
    {
        return -1;
    }
    else if (size_1<size_2)
    {
        return 1;  
    }
    else
    {
        for (int i = 0; i < size_1; i++)
        {
            if (array_1[i]<array_2[i])
            {
                return 1;
            }
            else if (array_1[i]>array_2[i])
            {
                return -1;
            }
        }
    }
    return 0;
    }
    else if (sign_1 >= 0 && sign_2 < 0)
    {
        return 1;
    }
    else if (sign_1 < 0 && sign_2 >= 0)
    {
        return -1;
    }
    return 0;
};
int UnlimitedInt:: get_size()

{
    return size;
}
int * UnlimitedInt:: get_array()
{
    return unlimited_int;
}
int UnlimitedInt:: get_sign()
{
    return sign;
}
UnlimitedInt * UnlimitedInt::add(UnlimitedInt* i1, UnlimitedInt* i2)
{
    int size_1 = i1->get_size();
    int size_2 = i2->get_size();
    int sign_1 = i1->get_sign();
    int sign_2 = i2->get_sign();
    int * array_1 = i1->get_array();
    int * array_2 = i2->get_array();
    int carry = 0;
    if (sign_1>=0 && sign_2>=0)
    {
    if (size_1>size_2)
    {
        UnlimitedInt * answer_ui;
        answer_ui = new UnlimitedInt();
        answer_ui->sign = 1;
        int * answer = new int[size_1+1];
        for (int i = 0; i <= size_1; i++) 
        {
          answer[i] =  0; 
        }

        //remember to set size, signs of the answer in final
        for (int i = 0; i < size_2; i++)
        {
            int sum_result = array_1[size_1-i-1] + array_2[size_2-i-1] + carry;
            answer[size_1-i] = sum_result % 10;
            if (sum_result-(sum_result%10) != 0)
            {
                carry = 1;
            }
            else
            {
                carry = 0;
            };
        }
        for (int i = 0; i<size_1-size_2; i++)
        {
            int sum = array_1[size_1-size_2-1-i] + carry;
            answer[size_1-size_2-i] = sum%10;
            if (sum-(sum%10) != 0)
            {
                carry = 1;
            } 
            else
            {
                carry = 0;
            };
        }
        if (carry == 1)
        {
            answer[0] = 1;
        }
        else
        {
            if (answer[0]==0)
            {
                int * final_answer = new int[size_1];
                for(int i = 1; i<size_1+1; i++)
                {
                    final_answer[i-1] = answer[i];
                };
                answer_ui->unlimited_int = final_answer;
                answer_ui->size = size_1;
                return answer_ui; 
            }
        }
    answer_ui->unlimited_int = answer;
    answer_ui->size = size_1+1;
    return answer_ui; 
    }
    else if (size_2>size_1)
    {
        
        return add(i2,i1);
    }
    else if (size_1==size_2)
    {
        UnlimitedInt * answer_ui = new UnlimitedInt();
        answer_ui->unlimited_int = new int[size_1+1];
        answer_ui->sign = 1;
        int * answer = answer_ui->unlimited_int;
        for (int i = 0; i < size_2; i++)
        {
            int sum_result = array_1[size_1-i-1] + array_2[size_2-i-1] + carry;
            answer[size_1-i] = sum_result % 10;
            if (sum_result-(sum_result%10) != 0)
            {
                carry = 1;
            }
            else
            {
                carry = 0;
            };
        }
        if (carry == 1)
        {
            answer[0]=1;
            answer_ui->unlimited_int = answer;
            answer_ui->size = size_1+1;
            return answer_ui; 
        }
        int * final_answer = new int[size_1];
        for(int i = 1; i<size_1+1; i++)
            {
                final_answer[i-1] = answer[i];
            };
            answer_ui->unlimited_int = final_answer;
            answer_ui->size = size_1;
            return answer_ui; 
    }    
    }
    else if (sign_1>= 0 && sign_2 <= 0)
    {
        UnlimitedInt * changed_i2 = i2;
        changed_i2->sign = 1; 
        return sub(i1,changed_i2);
    }
    else if (sign_1<= 0 && sign_2 >= 0)
    {
        UnlimitedInt * changed_i1 = i1;
        changed_i1->sign = 1; 
        return sub(i2,changed_i1);
    }
    else
    {
        UnlimitedInt * changed_i1 = i1;
        UnlimitedInt * changed_i2 = i2;
        changed_i1->sign = 1; 
        changed_i2->sign = 1; 
        UnlimitedInt * final = add(changed_i1,changed_i2);
        final->sign = -1;
        return final;

    }
    return i1;
}
UnlimitedInt * UnlimitedInt::sub(UnlimitedInt* i1, UnlimitedInt* i2)
{
    int size_1 = i1->get_size();
    int size_2 = i2->get_size();
    int sign_1 = i1->get_sign();
    int sign_2 = i2->get_sign();
    int * array_1 = i1->get_array();
    int * array_2 = i2->get_array();
    int carry = 0;
    if (sign_1 >= 0 && sign_2 >=0)
    {   
        if (size_1 > size_2)
            {
                UnlimitedInt * answer_ui = new UnlimitedInt();
                int * answer = new int[size_1];
                answer_ui->sign = 1;
                for (int i =0; i<size_2; i++)
                {
                    if (array_1[size_1-i-1]-carry >= array_2[size_2-i-1])
                    {
                        int diff = array_1[size_1-i-1] - carry - array_2[size_2-i-1]; 
                        answer[size_1-i-1] = diff;          
                        carry = 0;
                    }
                    else if (array_1[size_1-i-1]-carry < array_2[size_2-i-1])
                    {
                        int diff = array_1[size_1-i-1] - carry +10 - array_2[size_2-i-1]; 
                        answer[size_1-i-1] = diff;
                        carry = 1;
                }
                } //till the second number's all numbers we are done
            if (carry == 0)
            {
                for (int i = 0; i<size_1-size_2; i++)
                {
                    int diff = array_1[size_1-size_2-i-1];
                    answer[size_1-size_2-i-1] = diff;
                }; // had carry been zero, then we just propagate through with copying remians
            }
            else if (carry == 1)
            {
                for (int i = 0; i<size_1-size_2; i++) //for to propagate
                {
                    if (array_1[size_1-size_2-i-1] >= 1)
                    {
                        int diff = array_1[size_1-size_2-i-1]-carry; //no borrowing required
                        answer[size_1-size_2-i-1] = diff;
                        carry = 0;      
                    }
                    else if (array_1[size_1-size_2-i-1] == 0) 
                    {
                        int diff = array_1[size_1-size_2-i-1]+10-carry ; //Borrowing required, just zero was there with carry 1;
                        answer[size_1-size_2-i-1] = diff;
                        carry = 1;
                    }
                };  
            }
            if (answer[0]==0) //size reduced
            {
                int i = 0;
                int count = 0;
                while (answer[i]==0)
                {
                    count++;
                    i++;
                }
                int * final_answer = new int[size_1 - count];
                int index = i;
                while (i<size_1)
                {
                final_answer[i-index] = answer[i];
                i++;
                }
                delete [] answer;
                answer_ui->unlimited_int = final_answer;
                answer_ui->size = size_1-count;
                return answer_ui;
            }
            else
            {
            answer_ui->size = size_1;
            answer_ui->unlimited_int = answer;
            answer_ui->sign = 1;
            return answer_ui;
            };
        }
        else if (size_2 > size_1)
            {
                UnlimitedInt * answer_ui = new UnlimitedInt();
                answer_ui = sub(i2,i1);
                answer_ui->sign = -1;
                return answer_ui;
            }
        else if (size_2 == size_1)
            {
                if (compare(i1,i2) == 1)
                {
                    UnlimitedInt * answer_ui = new UnlimitedInt();
                    int * answer = new int[size_1];
                    for (int i = 0 ; i <size_1; i++)
                    {
                        if (array_1[size_1-i-1]-carry >= array_2[size_2-i-1])
                        {
                            int diff = array_1[size_1-i-1] - carry - array_2[size_2-i-1]; 
                            answer[size_1-i-1] = diff;          
                            carry = 0;
                        }
                        else if (array_1[size_1-i-1]-carry < array_2[size_2-i-1])
                        {
                            int diff = array_1[size_1-i-1] - carry +10 - array_2[size_2-i-1]; 
                            answer[size_1-i-1] = diff;
                            carry = 1;
                        }    
                    }
                    int i = 0;
                    int count = 0;
                    while (answer[i]==0)
                    {
                        count++;
                        i++;
                    }
                    int * final_answer = new int[size_1-count];
                    int index = i;
                    while (i<size_1)
                    {
                        final_answer[i-index] = answer[i];
                        i++;
                    }
                    answer_ui->size = size_1-count;
                    answer_ui->unlimited_int = final_answer;
                    answer_ui->sign = 1;
                    return answer_ui;
                }
                else if (compare(i1,i2)==0)
                {
                    UnlimitedInt * answer_ui = new UnlimitedInt(0);
                    return answer_ui;
                }
                else
                {
                    UnlimitedInt * answer_ui = new UnlimitedInt();
                    answer_ui = sub(i2,i1);
                    answer_ui->sign = -1;
                    return answer_ui;
                }
            }
    }
    else if (sign_1 <= 0  && sign_2 <= 0)
    {

        UnlimitedInt * changed_i1 = i1;
        UnlimitedInt * changed_i2 = i2;
        changed_i1->sign = 1;
        changed_i2->sign = 1;
        return sub(changed_i2, changed_i1);
    }
    else if (sign_1 >= 0 && sign_2 <=0 )
    {
        UnlimitedInt * changed_i2 = i2;
        changed_i2->sign = 1;
        return add(i1,changed_i2);
    }
    else if (sign_1 <= 0 && sign_2 >=0)
    {
        if (compare(i1,i2)==0)
        {
            UnlimitedInt * answer_ui = new UnlimitedInt(0);
            return answer_ui;
        }
        UnlimitedInt * changed_i1 = i1;
        changed_i1->sign = 1;
        UnlimitedInt * temp = add(changed_i1,i2);
        temp->sign = -1;
        return temp;
    };
    return i1;
}
UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1, UnlimitedInt* i2)
{
    if (i1->sign == 0 || i2->sign == 0)
    {
        UnlimitedInt* temp_1 = new UnlimitedInt(0);
        return temp_1;
    }
    else
    {
        if (i1->get_size() <=i2->get_size())
        {
            int* array_1 = i1->get_array();
            int* array_2 = i2->get_array();
            int size_1 = i1->get_size();
            int size_2 = i2->get_size();
            UnlimitedInt* answer = new UnlimitedInt(0);

            for (int i = 0; i < size_1; i++)
            {
                string s_temp = "";
                int carry = 0;

                for (int j = 0; j < size_2; j++)
                {
                    int temp = array_1[size_1 - 1 - i] * array_2[size_2 - 1 - j] + carry;
                    s_temp = std::to_string(temp % 10) + s_temp;
                    carry = temp / 10;
                }

                if (carry > 0)
                {
                    s_temp = std::to_string(carry) + s_temp;
                }

                for (int k = 0; k < i; k++)
                {
                    s_temp += "0";
                }
                UnlimitedInt * finally = new UnlimitedInt(s_temp);
                answer = answer->add(finally, answer);
            }
            if (i1->sign<0 && i1->sign<0)
            {
                return answer;
            }
            else if (i1->sign< 0 || i2->sign <0)
            {
                answer->sign = -1;
            }
            return answer;
        }
        else
        {
            return i1->mul(i2,i1);
        }
    }
}

UnlimitedInt * find_i_(UnlimitedInt * i1, UnlimitedInt * i2)
{
    UnlimitedInt * i = new UnlimitedInt(0);
    UnlimitedInt * i_final = new UnlimitedInt(10);
    UnlimitedInt * i_1 = new UnlimitedInt(1);
    while (compare(i,i_final)<0)
    {
        if (compare(i->mul(i,i1),i2)<=0 && compare(i1->mul(i->add(i,i_1),i1),i2)>0) 
        {
            break;
        };
        i = i->add(i,i_1);
    }
    return i;
};
UnlimitedInt * UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2) // i1/i2
{
    UnlimitedInt * temp_1 = new UnlimitedInt(i1->to_string());
    UnlimitedInt * temp_2 = new UnlimitedInt(i2->to_string());
    temp_1->sign = 1;
    temp_2->sign = 1;
    string s1 = temp_1->to_string();
    string s2 = temp_2->to_string();
    string s3 = "";
    string quotient = "";
    int * array_1 = i1->get_array();
    int s1_size = i1->get_size();
    int s2_size = i2->get_size();
    if (compare(temp_1,temp_2) == -1)
    {
        if (i1->sign == -1 && i2->sign == -1)
        {
            temp_1 = new UnlimitedInt(0);
            delete temp_2;
            return temp_1;
        }
        else if (i1->sign == -1 || i2->sign == -1)
        {
            
            temp_1 = new UnlimitedInt(-1);
            delete temp_2;
            return temp_1;
        }
        else
        {
            temp_1 = new UnlimitedInt(0);
            delete temp_2;
            return temp_1;
        }
    }
    else if (compare(i1,i2) == 0)
    {
        temp_1 = new UnlimitedInt(1);
        delete temp_2;
        return temp_1;
    }
   int count = 0;
   string temp = "";
   for (int i = 0; i<s2_size; i++)
   {
        temp += std::to_string(array_1[i]);
   }
   UnlimitedInt * temp_ui = new UnlimitedInt(temp);
   
   if (compare(temp_2, temp_ui)<=0) 
   {
        count = s2_size; 
        UnlimitedInt * answer = sub(temp_ui,temp_2->mul(temp_2,find_i_(temp_2,temp_ui))); 
        s3 = answer->to_string() + std::to_string(array_1[count]);
        quotient += find_i_(temp_2,temp_ui)->to_string(); 
   }
   else
   {
        count = s2_size + 1;
        temp = temp + std::to_string(array_1[s2_size]);
        temp_ui = new UnlimitedInt(temp);
        s3 = sub(temp_ui,temp_2->mul(temp_2,find_i_(temp_2,temp_ui)))->to_string() + std::to_string(array_1[count]); 
        quotient += find_i_(temp_2,temp_ui)->to_string(); 
   };
   UnlimitedInt * s3_ui = new UnlimitedInt(s3);
   while (count!=s1_size)
   {
        if (compare(temp_2,s3_ui)<=0 && count!=s1_size-1) 
        {
            quotient += find_i_(temp_2,s3_ui)->to_string();
            s3 = sub(s3_ui,temp_2->mul(temp_2,find_i_(temp_2,s3_ui)))->to_string() + std::to_string(array_1[count+1]);
            s3_ui = new UnlimitedInt(s3);
            count++;
        }
        else if (compare(temp_2,s3_ui)<=0 && count==s1_size-1) 
        {
            quotient += find_i_(temp_2,s3_ui)->to_string();
            s3 = sub(s3_ui,temp_2->mul(temp_2,find_i_(temp_2,s3_ui)))->to_string();
            s3_ui = new UnlimitedInt(s3);
            count++;
        }
        else if (compare(temp_2,s3_ui)>0 && count!=s1_size-1)
        {
            quotient += find_i_(temp_2,s3_ui)->to_string();
            s3 = sub(s3_ui,temp_2->mul(temp_2,find_i_(temp_2,s3_ui)))->to_string() + std::to_string(array_1[count+1]);
            s3_ui = new UnlimitedInt(s3);
            count++;
            
        }
        else
        {
            quotient += find_i_(temp_2,s3_ui)->to_string();
            s3 = sub(s3_ui,temp_2->mul(temp_2,find_i_(temp_2,s3_ui)))->to_string();
            s3_ui = new UnlimitedInt(s3);
            count++;
            
        }
   }
   if (i1->sign == -1 && i2->sign==-1)
   {
    UnlimitedInt * answer_ui = new UnlimitedInt(quotient);
    return answer_ui;
   }
   else if (i1->sign == -1 || i2->sign==-1)
   {
    UnlimitedInt * answer_ui = new UnlimitedInt(quotient);
    if (temp_1->mul(answer_ui,temp_2)->to_string()!=temp_1->to_string())
    {
        UnlimitedInt * temp_1_1 = new UnlimitedInt(1);
        answer_ui = add(answer_ui, temp_1_1);
        answer_ui->sign = -1;
        return answer_ui;
    }
    answer_ui->sign = -1;
    return answer_ui;
   }
   else
   {
    UnlimitedInt * answer_ui = new UnlimitedInt(quotient);
    return answer_ui;
   }
}
UnlimitedInt * UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2)
{
    if (i1->sign==0)
    {
        UnlimitedInt * temp = new UnlimitedInt(0);
        return temp;
    }
    return sub(i1, i1->mul(i2, i2->div(i1, i2)));
}
string UnlimitedInt::to_string()
{
    string temp ="";
    for (int i = 0; i<size; i++)
    {
        temp+=std::to_string(unlimited_int[i]);
    }
    if (sign==1)
    {
        return temp;
    }
    else if (sign==0)
    {
        return "0";
    }
    else
    {
        temp = "-" + temp;
        return temp;
    }
}

// int main()
// {
//     UnlimitedInt * integer_1 = new UnlimitedInt("12");
//     UnlimitedInt * integer_2 = new UnlimitedInt("3");
//     UnlimitedInt * integer_3 = integer_1->div(integer_1,integer_2);
//     for (int i =0; i<integer_3->get_size(); i++)
//     {
//         cout << (integer_3->get_array())[i];
//     }
//     cout << endl << integer_3->get_sign();
// }
