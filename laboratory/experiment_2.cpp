using namespace std;
#include<iostream> 
template<class T>
class Sort
{
    public:
        Sort (T * pt,int size)
        {
            p = pt;
            this->size = size;
        }

        void rank();//名次词排序
        void select();//选择排序
        bool bubble();//冒泡一次
        void bubblesort();//冒泡排序
        void insert_sort();//插入排序
        void output();//输出结果；
        //void insert();
    private:
        T *p ;
        int size;

};

// template<class T>
// void Sort<T>::rank()
// {
    
// }

template<class T>
void Sort<T>::select()
{
    bool swaped = false;
    for(int j=0;!swaped&&j<size-1;j++)
    {
        int temp = 0;//用来存放最大的索引
       // T middle = p[0];
        for(int i=1;i<size-j;i++)
        {
            
            if(p[i]>p[temp])//如果后面的元素大，temp就存放大的元素的索引。
            {
                temp = i;
                swaped =true;//暂时有序
            } 
            else
            {
                swaped = false;//无序
            }
            
        }
        swap(p[temp],p[size-j-1]);


        // if (p[size-1-j]!=p[temp])
        // {
        //    swaped = false;
        //    swap(p[temp],p[size-1-j]);
        // }
        // else swaped = true;
            
        
    }
}



//仅仅冒泡一次
template<class T>
bool Sort<T>::bubble()
{
    bool swaped = false ;
    for(int j=0;j<size-1;j++)
    {
        if(p[j]>p[j+1])
        {
            swap(p[j],p[j+1]);
            swaped = true;//说明无序
        }
       
    }
    return swaped;
}

//冒泡排序
template<class T>
void Sort<T>::bubblesort()
{
    for(int  i=0;bubble() && i<size;i++)
    {

    }
}


template<class T>
void Sort<T>::rank()
{
    int *index = new int[size];
    for(int i=0;i<size;i++)
    {
       index[i]=0;
    }

    for(int i=1;i<size;i++)
    {
        for (int j=0;j<i;j++)
        {
            if(p[j]<=p[i])
                index[i]++;
            else index[j]++;
        }
    }

    for(int i=0;i<size;i++)
        cout<<index[i]<<" ";
    cout<<endl;

    delete [] index;

}

template<class T>
void Sort<T>::insert_sort()
{
    for (int  i = 1; i < size; i++)//i代表要插入元素的索引
    {
        T temp = p[i];
        int  j;
        for (j = i-1; j>=0&&temp<p[j]; j--)//要插入的元素与前面的元素进行比较，如果小的话，就将后面的元素
        //往后移动，
        {
           p[j+1] = p[j];
        }
        p[j+1]=temp;//j+1就表示插入元素的正确位置
        
    }
    
}
template<class T>
void Sort<T>::output()
{
    for(int i=0;i<size;i++)
    {
        cout<<p[i]<<" ";
    }
}

int main()
{
    int size;
    cin>>size;
    int * ptr = new int[size];
    for(int i=0;i<size;i++)
    {
        cin>>ptr[i];
    }

   
    Sort<int> a(ptr,size);
   a.select();
    //a.bubblesort();
    //a.rank();
    //a.insert_sort();
    a.output();
    // for(int i=0;i<size;i++)
    // {
    //     cout<<ptr[i]<<" ";
    // }

    system("pause");
} 

