#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stack>
#include <string>
#include <iomanip>
#include <map>

using namespace std;

double do_calc(double right, char oper, double left);

const int SYMNUMS = 7;
const char symbols[SYMNUMS] = {'+','-','*','/','(',')','#'};

//存储优先级关系
const char prio_table[SYMNUMS][SYMNUMS] = 
{
//    +   -   *   /   (   )   #
    {'>','>','<','<','<','>','>'}, // +
    {'>','>','<','<','<','>','>'}, // -
    {'>','>','>','>','<','>','>'}, // *
    {'>','>','>','>','<','>','>'}, // /
    {'<','<','<','<','<','=','x'}, // (
    {'>','>','>','>','x','>','>'}, // )
    {'<','<','<','<','<','x','='}  // #
}; 

int main(int argc, char* argv[])
{
    std::map<char,int> symmap;
    for (int i = 0; i < SYMNUMS; ++i)
    {
        symmap.insert(std::pair<char,int>(symbols[i],i));
    }

    stack<double> NumsStack;    //操作数栈
    stack<char> OperStack;   //操作符栈

    //初始化，清空两个栈，并将‘#’放入操作符栈中
    while(!NumsStack.empty())
    {
        NumsStack.pop();
    }
    while(!OperStack.empty())
    {
        OperStack.pop();
    }
    OperStack.push('#');

    cout << "please input expression : ";
    string express = "";
    getline(cin,express);
    express += "#";

    const char* p = express.c_str();
    while(*p != '#' || OperStack.top() != '#')
    {
        //*p是操作数
        if(isdigit(*p))    
        {
            char number[32] = {0};
            char* _n = number;
            while(isdigit(*p) || *p == '.')
            {
                *(_n++) = *(p++);
            }
            *_n = 0;
            //操作数入栈
            NumsStack.push(atof(number));           
        }
        else
        {
            if(*p == ' ')
            {
                ++p;
                continue;
            }

            //ch是操作符
            if(symmap.find(*p) == symmap.end())
            {
                cerr << "error expression!" << endl;
                return 0;
            }
            char last = symmap.at(OperStack.top());
            char curr = symmap.at(*p);
            switch(prio_table[last][curr])
            {
            case '<':        
                {
                    //栈顶的操作符优先级小于当前操作符
                    OperStack.push(*p);
                    ++p;
                    break;
                }
            case '=':
                {
                    //相等，消去括号
                    if(OperStack.top() != '(')
                    {
                        cerr << "error expression! () not match." << endl;
                        return 0;
                    }
                    OperStack.pop();
                    ++p;
                    break;
                }
            case '>':
                {
                    if(OperStack.size() < 1 || NumsStack.size() < 2)
                    {
                        cerr << "error expression!" << endl;
                        return 0;
                    }

                    //栈顶的操作符优先级大于当前操作符
                    char oper = OperStack.top();
                    OperStack.pop();
                    double left = NumsStack.top();
                    NumsStack.pop();
                    double right = NumsStack.top();
                    NumsStack.pop();
                    //将操作后的结果放入运算数栈中
                    NumsStack.push(do_calc(right,oper,left));
                    break;
                }
            default:
                break;
            }
        }

    }

    if(NumsStack.size() != 1)
    {
        cerr << "error expression!" << endl;
        return 0;
    }

    //NumsStack剩下的元素就是表达式的结果
    cout << "= " <<NumsStack.top() << endl;
    return 0;
}

double do_calc(double right, char oper, double left)
{
    double result = 0;
    switch (oper)
    {
    case '+':
        result = right + left;
        break;
    case '-':
        result = right - left;
        break;
    case '*':
        result = right * left;
        break;
    case '/':
        result = right / left;
        break;
    default:
        break;
    }
    return result;
}