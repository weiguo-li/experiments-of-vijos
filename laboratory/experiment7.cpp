#include<iostream>
using namespace std;
template<class T>
class arrayQueue
{
    public :
    arrayQueue(int initialCapacity)//构造函数
    {
        arrayLength = initialCapacity;
        queueFront = queueBack = 0;//代表是一个空的队列
        element = new T[arrayLength];
    }
    void push(const T& theElement);//向队列插入一个元素
    void pop();//队列删除队列的第一个元素
    void output();//输出队列的元素
    int getszie()
    {
        return (queueBack+arrayLength - queueFront)%arrayLength;

    }
    T front();//返回队列的头元素


    private :
        int queueFront;//逆时针指向首元素的下一个位置
        int queueBack;//指向尾部元素的位置
        int arrayLength;//循环数组的长度
        T* element;//队列的数组指针
};

template <class T>
void arrayQueue<T>::push(const T& theElemnt)
{
    if ((queueBack+1)%arrayLength == queueFront)//数组满了
    {
        T* newQueue = new T[2*arrayLength];
        int start = (queueFront+1)%arrayLength;
        if(start<2)//没有形成环
        {
            copy(element+start,element+queueBack+1,newQueue);

        }
        else
        {//队列形成环
            copy(element+start,element+arrayLength,newQueue);
            copy(element,element+queueBack+1,newQueue +(arrayLength-start));
        }
        
        //设置新队列的首元素位置和尾元素位置
        queueFront = 2*arrayLength -1;
        queueBack = arrayLength-2;
        arrayLength *= 2;
        delete []element;
        element  = newQueue;
    }

    queueBack = (queueBack+1)%arrayLength;
    element[queueBack] = theElemnt; 
    
}

template<class T>
void arrayQueue<T>::pop()
{//删除队列首元素
    if(queueFront == queueBack )//队列为空
        return ;
    
    queueFront = (queueFront+1)%arrayLength;
    element[queueFront].~T();
}

template<class T>
T arrayQueue<T>::front()
{
    int start = (queueFront+1)%arrayLength;
    return element[start];
}

template<class  T>
void arrayQueue<T>::output()
{ 
    int start = (queueFront+1)%arrayLength;
    while (start != queueBack+1)
    {
        cout<<element[start]<<" ";
        start = (start+1)%arrayLength;
    }
    cout<<endl;
    
}


int main()
{
    int number;
    cin>>number;
    arrayQueue<int> test(1);
    for (int  i = 1 ; i <= number ; i++)
    {
        test.push(i);
    }

    while (test.getszie()>=2)
    {
        test.pop();
        int temp = test.front();
        test.pop();
        test.push(temp);  
    }

   
    cout<<test.front();
    
    system("pause");
}