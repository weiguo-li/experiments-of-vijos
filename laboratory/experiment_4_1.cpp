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
        void sort();
        void  meld(const linkedList<T>& dexList);
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
template<class T>
void linkedList<T>::sort()
{
    
    node<T>* desNode = firstNode->next;//dai cha ru de jie dian 
    
    if (desNode->element < firstNode->element)
    {
        firstNode->next=desNode->next;
        desNode->next = firstNode;
        firstNode=desNode;
        
    }
    

    node<T>* searchNode = firstNode->next;//zhao dao dai cha ru de jiedian
    node<T>*  presearchNode = firstNode;//dai cha ru jie dian de qian qv jie dian
    node<T>*  predesNode = firstNode->next;//dai chu ru jie dian de qian qv jie dian
    desNode = predesNode->next;
    while (desNode!=NULL)
    {
       
        if (desNode->element<firstNode->element)
        {
            predesNode->next=desNode->next;
            desNode->next=firstNode;
            firstNode=desNode;
            
            searchNode = firstNode->next;
            presearchNode = firstNode;
            desNode=predesNode;
            // predesNode = firstNode;
        }
        else 
        {
            for(;desNode->element>searchNode->element;searchNode=searchNode->next)
            {
                presearchNode=presearchNode->next;
            }

            if (searchNode!=desNode)
            {

                presearchNode->next = desNode;
                predesNode->next = desNode->next;
                desNode->next = searchNode;

            }
            else
            {
                predesNode=predesNode->next;
                desNode = desNode->next;
            }
            

            
        }
        //predesNode=predesNode->next;
        desNode=predesNode->next;
        presearchNode=firstNode;
        searchNode=presearchNode->next;

    }
}
// template<class T>
// void linkedList<T>::sort()
// {
    
//     linkedList<T>::iterator desNode = firstNode->next;//dai cha ru de jie dian 
    
//     if (*desNode < firstNode->element)
//     {
//         firstNode->next=desNode->next;
//         desNode->next = firstNode;
//         firstNode=desNode->next;
        
//     }

//     linkedList<T>::iterator searchNode = firstNode->next;//zhao dao dai cha ru de jiedian
//     linkedList<T>::iterator presearchNode = firstNode;//dai cha ru jie dian de qian qv jie dian
//     linkedList<T>::iterator predesNode = firstNode;//dai chu ru jie dian de qian qv jie dian
//     while (desNode!=NULL)
//     {
//         predesNode++;
//         desNode++;
//         if (desNode==NULL)
//         {
//             break;
//         }
        
//         if (*desNode<firstNode->element)
//         {
//             firstNode->next=desNode->next;
//             desNode->next = firstNode;
//             firstNode=desNode->next;

//             searchNode = firstNode->next;
//             presearchNode = firstNode;
//             predesNode = firstNode;
//         }
//         else 
//         {
//             for(;*desNode>*searchNode;searchNode++)
//             {
//                 presearchNode++;
//             }

//             if (searchNode!=desNode)
//             {
//                 presearchNode->next = desNode;
//                 predesNode->next = desNode->next;

//                 desNode->next = searchNode;
//             }

//             desNode = predesNode->next;
//         }

//     }
// }
template<class T>
void linkedList<T>::meld(const linkedList<T>& dexList)
{
    node<T>* p=dexList.firstNode;
    int i=0;
    for ( i =0;i<dexList.listSize;i++)
    {
        insert(listSize,p->element);
        p=p->next;
    }
    
    
}


int main()
{
    linkedList<int> test(10);
    linkedList<int> test2(10);
    linkedList<int> test3(10);
    int N;
    int Q;
    cin>>N>>Q;
    for(int i=0;i<N;i++)
    {
        int theElement;
        cin>>theElement;
        test.insert(i,theElement);

    }

    for(int i=0;i<Q;i++)
    {
        int theElement;
        cin>>theElement;
        test2.insert(i,theElement);

    }
    
    test3.meld(test);
    test3.meld(test2);
    if (N>0)
    {
        test.sort();
    }
    if (Q>0)
    {
        test2.sort();
    }

    if (Q+N>0)
    {
       test3.sort();
    }
    
    
   
    
    test.outputyh();
    test2.outputyh();
    test3.outputyh();
    cout<<s.str();
    
}