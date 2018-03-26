#include <iostream>
#include <stack>

using namespace std;

stack<int> OPND;    //操作数
stack<char> OPTR;   //操作符
int priority[7][7] = {1,1,-1,-1,-1,1,1,1,1,-1,-1,-1,1,1,1,1,1,1,-1,1,1,1,1,1,1,-1,1,1,-1,-1,-1,-1,-1,0,-2,1,1,1,1,-2,1,1,-1,-1,-1,-1,-1,-2,0};    //存储优先级关系


void Initial();    //初始化
void GetExpressionValue();          //计算表达式的值
int GetPriority(char a, char b);    //得到a,b优先级
int Operate(int a, char theta, int b);    //计算a theta b的值

int main()
{
    int sum = 0;
    Initial();                   //初始化
    GetExpressionValue();        //计算表达式的值
    cout << OPND.top() << endl;
    return 0;
}

void Initial()
{
    //初始化，清空两个栈，并将‘#’放入操作符栈中
    while(!OPND.empty())
    {
        OPND.pop();
    }
    while(!OPTR.empty())
    {
        OPTR.pop();
    }
    OPTR.push('#');
}

void GetExpressionValue()
{
    int data[12] = {0};    //操作数
    int d = 0;
    char ch;
    char theta;
    int a = 0;
    int b = 0;
    int i = 0;
    int j = 0;
    cin >> ch;
    while(ch != '#' || OPTR.top() != '#')    //两个都=‘#’，求值结束
    {
        if(isdigit(ch))    //ch是操作数
        {
            i = 0;
            d = 0;
            while(isdigit(ch))      //将字符型的操作数转换为整型
            {
                data[i++] = ch - '0';
                cin>>ch;
            }
            for(j = 0; j < i; j++)
            {
                d = d + data[j]*pow(10.0, j);
            }
            OPND.push(d);           //操作数入栈
        }
        else               //ch是操作符
        {
            switch(GetPriority(OPTR.top(), ch))
            {
            case -1:        //栈顶的操作符优先级小于当前操作符
                {
                    OPTR.push(ch);
                    cin>>ch;
                    break;
                }
            case 0:         //相等，消去括号
                {
                    OPTR.pop();
                    cin>>ch;
                    break;
                }
            case 1:         //栈顶的操作符优先级大于当前操作符
                {
                    theta = OPTR.top();
                    OPTR.pop();
                    a = OPND.top();
                    OPND.pop();
                    b = OPND.top();
                    OPND.pop();
                    OPND.push(Operate(b,theta,a));    //将操作后的结果放入运算数栈中
                    break;
                }
            default:
                break;
            }
        }
    }
}

int GetPriority(char a, char b)
{
    int i = -1;
    int j = -1;
    switch(a)
    {
        case '#':
            i++;
        case ')':
            i++;
        case '(':
            i++;
        case '/':
            i++;
        case '*':
            i++;
        case '-':
            i++;
        case '+':
            i++;
        default:
            break;
    }

    switch(b)
    {
        case '#':
            j++;
        case ')':
            j++;
        case '(':
            j++;
        case '/':
            j++;
        case '*':
            j++;
        case '-':
            j++;
        case '+':
            j++;
        default:
            break;
    }

    if(i >= 0 && j >= 0)
    {
        return priority[i][j];
    }
    else
    {
        return -2;
    }
}

int Operate(int a, char theta, int b)
{
    int res = 0;
    switch (theta)
    {
    case '+':
        res = a + b;
        break;
    case '-':
        res = a - b;
        break;
    case '*':
        res = a * b;
        break;
    case '/':
        res = a / b;
        break;
    default:
        break;
    }
    return res;
}