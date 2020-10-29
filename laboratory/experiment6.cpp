#include<iostream>
#include<sstream>
#include<iomanip>
using namespace std;
ostringstream s;

template<class T>
class stack
{
    public:
        virtual ~stack(){
		};
        virtual bool empty() const =0;
        virtual int size() const =0;
        virtual T& top() = 0;
        virtual void pop() = 0;

        virtual void push(const T& theElement)=0;

};


template<class T>
class arrayStack:public stack<T>
{   
    public :
    	
        arrayStack(int initailCapacity=10);
        ~arrayStack(){delete [] stack;}
        bool empty()const
        {
            return stackTop ==-1;
        }
        int size() const
        {
            return stackTop+1;
        }

        T& top()
        {
            if (stackTop == -1)
            {
                cout<<"栈为空，不能访问栈顶元素"<<endl;
                /* code */
            }

            return stack[stackTop];
            
        }

    void pop()
    {
        if (stackTop ==-1 )
        {
             cout<<"栈为空，不能删除栈顶元素"<<endl;
            /* code */
        }
        stack[stackTop].~T();
        stackTop--;

        
    }

    void push(const T& theElement);
    
    void output()
	{
		for(int i=0;i<=stackTop;i++)
		cout<<stack[i]<<" ";
	 } 
    
//    template<class T>
//    	friend ostream& operator<<(const ostream& out,const arrayStack<T>& list);
    
    
    private :
        int stackTop;
        int arrayLength;
        T* stack;
};

template<class T>
arrayStack<T>::arrayStack(int initialCapacity)
{
    if (initialCapacity<1)
    {
        cout<<"初始容量不合法"<<endl;

    }

    arrayLength = initialCapacity ;
    stack = new T[arrayLength];
    stackTop = -1;

};

template<class T>
void arrayStack<T>::push(const T& theElement)
{
    if(stackTop == arrayLength)
    {

    }

    stack[++stackTop] = theElement;

}






double compute()//计算表达式的值
{
    string expression ;//存储表达式
    cin>>expression;
    arrayStack<double> ope_number(200);//存储操作数
    arrayStack<char> opr_symble(200);//存储操作符
    int size = expression.size();
    for (int  i = 0; i <=size; i++)
    {  
        if(i == expression.size() )
        {
        a:    double up = ope_number.top();
            ope_number.pop();
            double down = ope_number.top();
            ope_number.pop();
            double temp;
            if (opr_symble.top() == '+')
            {
                temp = down + up;
            }
            else if (opr_symble.top() == '-')
            {
                temp =down-up;
            }
            else if (opr_symble.top() == '*')
            {
                temp = down * up;
            }
            else if (opr_symble.top() == '/')
            {
                temp = down / up;
            }
             
            ope_number.push(temp);
            opr_symble.pop();
            if(!opr_symble.empty())
            {
                goto a;

            }

            break;
        }



        if (expression.at(i) =='(' || expression.at(i)=='+' || expression.at(i) == '-'    \
         || expression.at(i) == '*'|| expression.at(i) == '/'||expression.at(i) == ')')
        {
            
            if (opr_symble.empty()||opr_symble.top() == '(')
            {
                opr_symble.push(expression.at(i));
            }
            else
            {
                
                
            b:   if ((expression.at(i) == '*'&&(opr_symble.top()=='+'||opr_symble.top()=='-'))|| \
               (expression.at(i) == '/'&&(opr_symble.top()=='+'||opr_symble.top()=='-'))||expression.at(i)=='(')//压入站的运算符优先级比上一个高
               {
                   opr_symble.push(expression.at(i));
               }
               else
               {

               
                   double up = ope_number.top();
                   ope_number.pop();
                   double down = ope_number.top();
                   ope_number.pop();
                   double temp;
                   if (opr_symble.top() == '+')
                   {
                       temp = down + up;
                   }
                   else if (opr_symble.top() == '-')
                   {
               
                       temp = down -up;
                   }
                   else if (opr_symble.top() == '*')
                   {
                       temp = down * up;
                   }
                   else if (opr_symble.top() == '/')
                   {
                       temp = down / up;
                   }

                   ope_number.push(temp);
                   opr_symble.pop();//弹出操作符
                   if(!opr_symble.empty()&&opr_symble.top()!='(')
                             goto b;

                   opr_symble.push(expression.at(i));
                }
                 if (expression.at(i)==')')
                {
                    opr_symble.pop();
                    opr_symble.pop();
                }  
            }
            
        }
        else 
		{
			
            ope_number.push(double(expression.at(i)-48));
            
        }  
    }

   return ope_number.top();
    
}



int main()
{
    int row ;
    cin>>row;
    while (row>0)
    {
        s<<setiosflags(ios::fixed)<<setprecision(2)<<compute()<<endl;
       row--;

    }
    cout<<s.str();
    
    //  system("pause");
}