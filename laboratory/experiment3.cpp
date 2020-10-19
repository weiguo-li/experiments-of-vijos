#include<iostream>
#include<cstring>
#include<sstream>
using namespace std;
ostringstream s;

template<class T>
void changelength(T* &a,int n)//改变数组的长度，T* &非常重要
{
    T* temp =new T[2*n];
    copy(a,a+n,temp);
    delete []a;
    a = temp;
}
//定义一个通讯的结构体
struct Tongxun
{
    string name;//学生的姓名
    string  number;//电话号码；
    int classnumber;//班级号码
    int comdation;//宿舍号
    void wirite_in()
    {
        cin>>name;
        cin>>number;
        cin>>classnumber;
        cin>>comdation;
    }
};

template<class T>
class LinearList//线性表的一个抽象类
{
    public :
    virtual void insert() = 0;
    virtual void deletebyname() = 0;
    virtual int  find()const = 0;
};

template<class T>
class TongxunluList:public LinearList<T>//基类派生出TongxunluList
{
    public :
        TongxunluList(int capacity = 10);
        ~TongxunluList()
        {
            delete []element ;
        }
        void insert();//插入一个学生
        void deletebyname();//通过名字去删除一个学生的信息
        int  find() const;//查找学生
        void  output_yihuo() ;//输出学生宿舍号的异或
        void editbyname();//通过名字去编辑信息
    private:
        T* element;//一个存贮Tongxu类型的元素的数组
        int capacity;//数组的容量
        int listsize;//学生信息的个数

};

//构造函数
template<class T>
TongxunluList<T>::TongxunluList(int initialcp )
{
    element = new T[initialcp];
    capacity = initialcp;
    listsize = 0;
}


template<class T>
void TongxunluList<T>::insert()
{
    
    if(listsize==capacity)//先判断数组满了没有
    {
        changelength(element,listsize);//满了就改变数组的容量，过大一倍
        capacity = 2*capacity;
    }
    Tongxun student;//待插入的学生
    student.wirite_in();
    element[listsize] = student;//把待插入的学生插入
    listsize++;//插入以后，学生的个数加一

}


template<class T>
void TongxunluList<T>::deletebyname()
{
    string going_del;
    cin>>going_del;
    for (int i=0;i<listsize;i++)
    {
        if(element[i].name == going_del)
        {
            copy(element +i+1,element+i+listsize,element+i);
            element[listsize].~T();
            listsize--;
           
        }
            
    }


}


template<class T>
int   TongxunluList<T>::find()const//find track by student nama;
{
    string stuname;
    cin>>stuname;
    for (int i=0;i<listsize;i++)
    {
        if(element[i].name == stuname)
        {
            return  1;// number 1 represent that this is a student called stuname
        }
        
    }
    return 0;//0 represent that counn't find the student whose name is stuname;

}


template<class T>
void  TongxunluList<T>::output_yihuo()
{
    int des_class;
    cin>>des_class;
    int *same_class=new int [listsize];//储存同一个班的宿舍号
    for(int i=0;i<listsize;i++)
    {
        same_class[i]=0;//初始化
    }
    int j=0;
    for(int i=0;i<listsize;i++)//遍历整个数组，找到目标名称
    {
        if(element[i].classnumber == des_class )//如果找到了，就把宿舍号提取出来。
        {
            same_class[j] = element[i].comdation;
            j++;
        }
        
    }
    int result=same_class[0];
        for (int i=0;i<j-1;i++)//把宿舍号异或求出来
        {
            result ^=same_class[i+1];
        }

    s<< result<<endl;

}

template<class T>
void TongxunluList<T>::editbyname()
{
    string des_name;//要删除的名字
    int selection;//定位了名字之后，定位一个选择，本退共有3个选择
    cin>>des_name;
    cin>>selection;
    for(int i=0;i<listsize;i++)
    {
        if(element[i].name == des_name)
        {
            switch (selection)//不同的选择有不同的操作
            {
            case 1://edit the phonenumber
                cin>>element[i].number;
                break;
            case 2://edit the class 
                cin>>element[i].classnumber;
                break;

            case 3://edit the comdation
                cin>>element[i].comdation;
                break;
            default:
                break;
            }

            break;
        }
    }

}
int main()
{
    int frequency;//表示操作的次数
    cin>>frequency;
    TongxunluList<Tongxun> test(2);
    while(frequency)
    {
        int point ;//point represent all kinds of process,including 0,1,2,3,4....
        cin>>point; //get the concrete process,specified from the standard 'cin'
        switch (point)
        {
        case 0:
            test.insert();//不同的数字代表不同的操作，以下皆是如此
            break;
        case 1:
            test.deletebyname();
            break;
        case 2:
            test.editbyname();
            break;
        case 3:
            s<<test.find()<<endl;
            break;
        case 4:
            test.output_yihuo();
            break;

        default:
            break;
        }
        frequency--;
    }
    cout<<s.str();
    
    system("pause");
}