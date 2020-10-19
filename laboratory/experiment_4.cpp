#include<iostream>
#include<sstream>
using namespace std;

ostringstream s;

template<class T>
struct node
{
    T element;
    node<T>* next;
    node(T theElement,node<T>* p)
    {
        element = theElement;
        next  = p;

    }
};

template<class T>
class linkedList//链表类
{
    // public:
    //         // typedefs required by C++ for a forward iterator
    //         typedef forward_iterator_tag iterator_category;
    //         typedef T value_type;
    //         typedef ptrdiff_t difference_type;
    //         typedef T* pointer;
    //         typedef T& reference;
        
        public :
        //构造，析构，拷贝函数
        linkedList(int initialcapacity);
        linkedList(const linkedList<T>& theList);
       // ~linkedList();
        void insert (/*int theIndex,const T& theElement*/);//指定位置插入元素
        void insert (int theIndex,const T& theElement);
        void delete_();//删除指定元素
        void find();//搜索链表是否有指定元素
        void reverse();//原地逆置链表
        void output(ostream& out) const;//输出链表
        void outputyh()const;
    class iterator//迭代器类；
    {
    public :
    //构造函数
    iterator(node<T>* theNode = NULL)
    {
    pp = theNode;
    }
    //jie yin yong
    T& operator*()const{return pp->element;}
    T* operator->()const{return &pp->element;}
    //iterator plus caozuo
    iterator& operator++()//qian jia 
    {
        pp=pp->next;
        return *this;
    }
    
    iterator operator++(int)//hou jia
    {
        iterator old=*this;
        pp = pp->next;
        return old;
    }

    //equal test
    bool operator!=(const iterator right) const
    {
        return pp!=right.pp;
    }
    bool operator==(const iterator right) const
    {
        return pp == right.pp;
    }

    protected:
        node<T>* pp;

    };


    iterator begin(){return iterator(firstNode);}
    iterator end(){return iterator(NULL);}
        
    protected:
        node<T>* firstNode;
        int listSize;
};


template<class T>
linkedList<T>::linkedList(int initialcapacity)
{
    if(initialcapacity<1)
    {
        ostringstream s;
        s<<"initial capacity = "<<initialcapacity<<"must >0";
    }
    firstNode=NULL;
    listSize = 0;
}


template<class T>
void linkedList<T>::insert (/*int theIndex,const T& theElement*/)
{
    int theIndex;
    cin>>theIndex;
    int theElement;
    cin>>theElement;
    
    if(theIndex == 0)
    {
        firstNode = new node<T>(theElement,firstNode);
    }
    else
    {
        node<T>* p=firstNode;
        for(int i=0;i<theIndex-1;i++)//找到带插入位置的前驱节点
        {
            p=p->next;
        }
        p->next =new node<T>(theElement,p->next);
    }
    listSize++;
}

template<class T>
void linkedList<T>::insert (int theIndex,const T& theElement)
{
    
    
    if(theIndex == 0)
    {
        firstNode = new node<T>(theElement,firstNode);
    }
    else
    {
        node<T>* p=firstNode;
        for(int i=0;i<theIndex-1;i++)//找到带插入位置的前驱节点
        {
            p=p->next;
        }
        p->next =new node<T>(theElement,p->next);
    }
    listSize++;
}


template<class T>
void linkedList<T>::output(ostream& out) const
{
    for (node<T>* currentNode = firstNode; currentNode!=NULL;currentNode = currentNode->next)
    {
        out<<currentNode->element<<" ";
    }
    out<<endl;
}

template<class T>
void linkedList<T>::delete_()
{
    T element;
    cin>>element;
    if(firstNode->element==element)
    {
        node<T>* temp = firstNode;
        firstNode = firstNode->next;
        delete temp;
        listSize--;
    }
    else
    {
        node<T>* currentNode=firstNode;
        node<T>* precurrentNode=firstNode;
        //先找到到待删除的节点；
        for( currentNode=firstNode;currentNode->element!=element&&currentNode->next!=NULL;currentNode=currentNode->next)
        {

        }
        if (currentNode->element!=element)//not found 
        {
            s<<"-1\n";
        }
        else
        {
            while (precurrentNode->next != currentNode)
            {
                 precurrentNode=precurrentNode->next;//找到待删除的前驱节点
            
            }
            
            precurrentNode->next=precurrentNode->next->next;
            delete currentNode;
            listSize--;

        }
    }
}

template<class T>
void linkedList<T>::reverse()
{

    node<T>* pnext = firstNode->next;
    firstNode->next=NULL;
    node<T>* p;
    while (pnext!=NULL)
    {
        //zhe ji hang de shun xv shi fen zhongyao
        p = pnext;
        pnext=pnext->next;
        p->next=firstNode;
        
        firstNode = p;
    }
    
    
    // int zho =listSize/2;
    // node<T>* frontNode=firstNode;
    // node<T>* backNode = NULL;
    // node<T>* preBackNopde= NULL;
    // for(backNode = firstNode;backNode->next!=NULL;backNode=backNode->next)
    // {
       
    // }
   
    // preBackNopde = backNode;
    
    // for( int i=0;i<zho;i++)
    // {
    //     T temp;
    //     temp = frontNode->element;
    //     frontNode->element = preBackNopde->element;
    //     preBackNopde->element = temp;
    //     //这两条语句的顺序至关重要，我在这个地方调试了很长时间；
    //     backNode= frontNode;
    //     frontNode=frontNode->next;
        
    //     for (int j=0;j<listSize-2*i-2;j++)
    //     {
    //         backNode=backNode->next;
    //     }
    //     preBackNopde = backNode;
    // }

}

template<class T>
void linkedList<T>::find()
{
     T theElement;
     cin>>theElement;
    
    int index=0;
    node<T>* currentNode = firstNode;
    while (currentNode!=NULL&&currentNode->element!=theElement)
    {
        index++;
        currentNode=currentNode->next;
        
    }

    if (currentNode==NULL)
    {
        s<<"-1\n";
    }
    else
    {
        s<<index<<endl;
    }
    
    
}



template<class T>
void linkedList<T>::outputyh()const
{
    
    linkedList<T>::iterator pointer(firstNode);
    T sum=0;
    int index=0;
    for(;pointer!=NULL;pointer++)
    {
        sum += index^(*pointer);
        index++;

    }
    s<<sum<<endl;
}





int main()
{
    linkedList<int> test(10);
    int N;
    int Q;
    cin>>N>>Q;
    for(int i=0;i<N;i++)
    {
        int theElement;
        cin>>theElement;
        test.insert(i,theElement);

    }
    //test.output(cout);
    //test.delete_();
    //test.output(cout);
    //test.find();
    //cout<<s.str();
    
    while (Q!=0)
    {
        int number;
        cin>>number;
       switch (number)
        {
            case 1:
            test.insert();
                break;
            case 2:test.delete_();
                break;
            case 3:test.reverse();
                break;
            case 4:test.find();
                break;
            case 5:test.outputyh();
                break;
            default:
                 break;
        }

        Q--;
    }

    cout<<s.str();
    
    

//     test.insert(0,12);
//     test.insert(1,14);
//     test.insert(0,1);
//     test.output(cout);
//     test.outputyh();
//     // test.reverse();
//     // test.output(cout);
//    // test.find(14);

    system("pause");
}