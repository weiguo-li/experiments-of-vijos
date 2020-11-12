#include<iostream>
#include<sstream>
using namespace std;
ostringstream s;
template<class K>
struct hashNode
{
    K key;
    hashNode* next;
    hashNode(const K& theKey)
    {
        key = theKey;
        next = NULL;
    }
};

template<class K>
class hashTable
{
    public :
    hashTable(int theDivisor);
    ~hashTable()
    {

    }
    void insert(const K &theKey) ;
    void   search(const K& theKey);
    void erase(const K& thekey);
    
    protected :
    hashNode<K> **table;
    int divisor; //哈希函数的被除数
    
};

template<class K>
hashTable<K>::hashTable(int theDivisor)
{
    divisor = theDivisor;
    table  = new hashNode<K>* [divisor];
    for (int i = 0; i < divisor; i++)
    {
        table[i] = NULL;
    }    
   
}

template<class K>
void hashTable<K>::insert(const K& theKey)
{
    int des = theKey%divisor;//找到桶的位置
    if (table[des] == NULL)
    {
        table[des] = new hashNode<K>(theKey);
        table[des]->next = NULL;
    }
    else
    {
        hashNode<K>*front = table[des];
        hashNode<K>* tofind = table[des];//指向该桶的第一个节点
        while (tofind!=NULL&&tofind->key!=theKey)//查找到应该插入的位置
        {
            front = tofind;
            tofind = tofind->next;
        }

        if (tofind== NULL)
        {
            front->next = new hashNode<K>(theKey);//插入尾结点
 
        }
        else
        {
            s<<"Existed"<<endl;
        }
        
        
         
    }
     
}

template<class K>
void  hashTable<K>::search(const K& theKey)
{
    int des = theKey%divisor;//找到桶的位置
    if (table[des] == NULL)
    {
        s<<"Not Found"<<endl;
    }
    
    else 
    {
        int number = 0;
        hashNode<K>* tofind = table[des];//指向该桶的第一个节点
        while (tofind!=NULL&&tofind->key!=theKey)//查找到位置
        {
            tofind = tofind->next;
            number++;
        }

        if (tofind == NULL)
        {
            s<<"Not Found"<<endl;
        }
        else
        {
            // number = number-1;
            while (tofind != NULL ) //遍历所有位置
            {
                tofind = tofind->next;
                number++;
            }
            s<<number<<endl;
        }
       
    }
    
    

}

template<class K>
void hashTable<K>::erase(const K& theKey)
{
    int des = theKey%divisor;//目标桶
    if (table[des] == NULL)
    {
        s<<"Delete Failed"<<endl;
    }
    else 
    {
        int number = 0;
        hashNode<K>* tofind = table[des];//指向该桶的第一个节点
        while (tofind!=NULL&&tofind->key!=theKey)//查找到位置
        {
            tofind = tofind->next;
            number++;
        }

        if (tofind == NULL)
        {
            s<<"Delete Failed"<<endl;

        }
        else
        {
            hashNode<K>* temp = tofind;
            while (tofind != NULL ) //遍历所有位置
            {
                tofind = tofind->next;
                number++;
            }
            s<<number-1<<endl;


            if (temp==table[des])//删除的是头结点
            {
                table[des] = temp->next;
                delete temp;
               
            }
            else
            {
                hashNode<K> *front = table[des];
                while (front->next != temp) //找到要删除节点的前驱节点
                {
                    front = front->next;
                }

                front->next = temp->next;
                delete temp;
                
            }
            
            

           
            
        }
    }

}


int main()
{
    int D;
    int m;
    cin>>D>>m;
    hashTable<int> test(D);
    while (m>0)
    {
        int option;
        cin>>option;
        int key;
        cin >>key;
        switch (option)
        {
        case 0:
            test.insert(key);
            break;

        case 1:
            test.search(key);
            break;
        case 2:
            test.erase(key);
            break;
        }
        m--;
       
        
    }
    cout << s.str();
    cout<<"this is a test "<<endl;
    system("pause");

}