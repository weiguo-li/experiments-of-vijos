#include<iostream>
#include<sstream>
using namespace std;
ostringstream s;

template<class K,class E>
class hashTable
{
    public :
    hashTable(int theDivisor);
    int search(const K& theKey);
    void insert(const pair<const K,E>& thePair);
    void erase(const K& theKey);
    int find(const K& thekey);


    protected:
    pair<const K,const E>** table ;//散列表
    // hash<K> hash;//把类型K映射到一个非整数
    int dSize;//字典的数对的个数
    int divisor;//散列函数除数 

}; 

//构造函数的实现
template<class K,class E>
hashTable<K,E>::hashTable(int theDivisor)
{
    divisor = theDivisor;
    dSize = 0;
    //分配和初始化散列表数组
    table = new pair<const K,const E> * [divisor];
    for (int  i = 0; i < divisor; i++)
    {
        table[i] = NULL;
    }
    
}

template<class K,class E>
int hashTable<K,E>::search(const K& theKey)
{
    int i = theKey% divisor;//起始桶
    int j = i;
    do
    {
        if (table[j] == NULL|| table[j]->first == theKey)
        {
           
            return j;
        }

        j = (j+1)% divisor;
        
    } while (j!= i);
    
    return j;//表满
}

template<class K,class E>
int hashTable<K,E>::find(const K& theKey)
{
    int b = search(theKey);
    if (table[b] == NULL)
    {
        return -1;
        /* code */
    }
    else return b;
    
    // int i = theKey% divisor;//起始桶
    // int j = i;
    // do
    // {
    //     if (table[j] == NULL|| table[j]->first == theKey)
    //     {
    //         if (table[j]==NULL)
    //         {
    //             return -1;//没有找到
    //         }
    //         else
    //             return j;
    //     }

    //     j = (j+1)% divisor;
        
    // } while (j!= i);
    
    // return -1;//表满
}

template<class K,class E>
void hashTable<K,E>::insert(const pair<const K,E>& thePair)
{
    
    int b = search(thePair.first);

    //检查是否有匹配的数对
    if (table[b] == NULL)//没有匹配的数对
    {
        table[b] = new pair<const K,const E>(thePair);
        dSize++;
        s<<b<<endl;
    }
    else
    {
        //检查是否有重复的关键字数对或者表是否满了
        if (table[b]->first == thePair.first)
        {//有重复的关键字数对，修改table[b]->scond
            // table[b]->second = thePair.second;
            s<<"Existed"<<endl;
        }
        else
        {
            //表满了
        
        }
        
        
    }
    
    
}

//输出notFound或者删除所要移动的元素的个数
template<class K,class E>
void hashTable<K,E>::erase(const K& theKey)
{
    int number=0;//用来计数要移动的操作数
    const int b = search(theKey);//thekey关键字的数对逻辑上应该存在的桶的位置
    if (table[b] == NULL)//没有找到
    {
        s<<"Not Found"<<endl;
    }
    else
    {
        // if (table[b]->first == theKey )
        // {   
            delete table[b];//释放内存
            table[b] = NULL;
            dSize--;
        // }

            //从删除位置的下一个开始移动删除后的元素，直到遇到空桶或者回到删除位置
            int front_point = b;//指向移动的目的位置,为NULL
            
            int index_point =b;//执行被移动的元素的位置
           
            index_point  = (index_point+1)%divisor;
            
            while (table[front_point] == NULL && table[index_point] != NULL && index_point != b) //移动元素
            {
                int destnation = table[index_point]->first % divisor; //理论应该在的位置

                if ((destnation <= front_point && front_point < index_point)||\
                (index_point<destnation && destnation<=front_point)||\          
                (front_point<index_point && index_point<destnation))//要移动的三种条件
                {
                    table[front_point] = table[index_point];
                    table[index_point] = NULL;
                    number++;

                    front_point = (front_point + index_point - front_point) % divisor; //指向下一个
                    index_point = (index_point + 1) % divisor;                         //指向下一个
                }
                else //相等的话去看下一个节点，并且front_point不变，始终指向NULL
                {

                    index_point = (index_point + 1) % divisor; //指向下一个
                    /* code */
                }
                
                //不能移动到起始桶之前
                // if (table[index_point]->first % divisor != index_point && (table[index_point]->first % divisor <= front_point\
                //  || (index_point < table[index_point]->first % divisor&&index_point>front_point ) ) ) //不相等就移动
                // {

                //     table[front_point] = table[index_point];
                //     table[index_point] = NULL;
                //     number++;

                //     front_point = (front_point + index_point - front_point) % divisor; //指向下一个
                //     index_point = (index_point + 1) % divisor;                         //指向下一个
                    
                    
                // }
                // else //相等的话去看下一个节点，并且front_point不变，始终指向NULL
                // {

                //     index_point = (index_point + 1) % divisor; //指向下一个
                //     /* code */
                // }
            }

        s<<number<<endl;
        
    }

}


int main()
{
    int D;
    int m;
    cin>>D>>m;
    hashTable<int ,int > test(D);
    while (m>0)
    {
        int option;
        cin>>option;
        int key;
        cin >>key;
        pair<const int ,int> thepair(key,0);
        switch (option)
        {
        case 0:
            test.insert(thepair);
            break;
        
        case 1:
        s<<test.find(key)<<endl;
        break;
            case 2:test.erase(key);
                break;
        }
        m--;
       
        
    }
     cout<<s.str();
    
    cout<<"this is a test "<<endl;
    system("pause");
}