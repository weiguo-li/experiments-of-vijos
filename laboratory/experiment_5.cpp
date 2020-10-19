#include<iostream>
#include<sstream>
using namespace std;

ostringstream s;

using namespace std;
struct matrixTerm 
{
    int row;
    int col;
    int value;
    matrixTerm()//默认构造函数
    {
        this->row = 0;
        this ->col = 0;
        this->value =0;
    }
    matrixTerm(int row,int col,int value)//有参构造函数
    {
        this->row = row;
        this ->col = col;
        this->value = value;
    }

    bool  operator==(const matrixTerm& a)
    {
        if (this->value == a.value)
        {
            return true;
        }
        else return false;
        
    }
    void write()
    {
        int row;
        int col;
        int value;
        cin>>row>>col>>value;
        this->row = row-1;
        this->col = col-1;
        this->value = value;

    }

    
    
};

ostream&  operator<<(ostream& o,const matrixTerm& b)
    {
        o<<b.value<<" "<<b.row+1<<" "<<b.col+1;//加1是因为数组索引从0开始，而矩阵从1，保持了一致性
        return cout;
    }

template<class T>
class spareMatrix
{
    public:
        spareMatrix(int row,int col,int initialCapacity);
        spareMatrix(const spareMatrix<T>& list);
        ~spareMatrix()
        {
            delete [] term;
        }

        void transpose(/*spareMatrix<T>& b*/);//matrix's transform
        void add();//maxtrix's add
        void   multiply(/*spareMatrix<T>& a,spareMatrix<T>& b*/);//matrix's multiply
        void select();//mapping the two demmision to one demission
        void re_set();//重置矩阵
        void matrix_set();//设置矩阵的一位映射输入
        void output();//测试输出，可以输出三元组的具体信息
        void fulloutput();//输出稀疏矩阵的所有元素，包括0元素
        int  getcol(){return col;}
        int  getrow(){return row;}
        matrixTerm get(int index);
        //为term
        void insert(int index,const matrixTerm& a);

        

    private:
        int row;//represent the row of the matrix
        int col;//represent the colums of the matrix
        matrixTerm* term;//mon-0 list
        int listSize;
        int arrayLength;

};

template<class T>
spareMatrix<T>::spareMatrix(int row,int col,int initialCapacity)
{
    this->row = row;
    this->col = col;
    this->listSize = 0;
    this->term = new matrixTerm[initialCapacity];
    this->arrayLength= initialCapacity;
    
}

template<class T>
void spareMatrix<T>::output()
{
    for(int i=0;i<listSize;i++)
    cout<<term[i]<<"      ";
    cout<<"listSize="<<listSize<<endl;
    
    
}
template<class T>
void spareMatrix<T>::insert(int index,const matrixTerm& a)
{
    
    if (index<listSize)
    {
        copy_backward(term+index,term+listSize,term+listSize+1);

    }
    
    term[index] = a;
    listSize++;


}

template<class T>
spareMatrix<T>::spareMatrix(const spareMatrix<T>& list)
{
    row = list.row;
    col = list.col;
    listSize = list.listSize;
    term = new matrixTerm[list.arrayLength];
    copy(list.term,list.term+listSize,term);
}

template<class T>
void spareMatrix<T>::add()
{
    spareMatrix<T> Q(2,3,85000);
    Q.matrix_set();//要与本类相加的matrix
    matrixTerm *p= term;//本类的迭代器
    
    matrixTerm * q= Q.term;//与本类元素相加的iterator
    //P是本类对象
    int Prow = row;
    int Pcol = col;
    int Qrow = Q.row;//Q.getrow();
    int Qcol = Q.getcol();
    if (Qcol!=Pcol|| Qrow!=Prow)//不合法的矩阵直接不运算
    {
        
        s<<-1<<endl;
        //将Q赋给p
        row = Qrow;
        col = Qcol;
        delete [] term;
        term = new matrixTerm[arrayLength];
        copy(Q.term,Q.term+listSize,term);
        listSize =Q.listSize;
        // for(int i =0;i<Q.listSize;i++)
        // term[i] = Q.term[i];

        /* code */
    }
    else
    {
        int index=0;
        
        for (int  i = 0; i < Q.listSize; i++)//将Q的元素插入到p
        {
            
            int Qmapping = (q->row)*(Qcol)+q->col+1;//相加矩阵的映射
            int Pmapping = ((p)->row)*(Qcol)+p->col+1;

            while (Qmapping>Pmapping&&p!=term+listSize)
            {
                p++;
                index++;
                if (p!=term+listSize)
                {
                   Pmapping = (p->row)*(Qcol)+p->col+1;
                }
                
            }


            if (p==term+listSize)
            {
                insert(listSize,*q);
            }
            else if(Qmapping==Pmapping)
            {
                p->value=p->value+q->value;//将计算结果保存在本类
            }
            else
            {
                insert(index,*q);
            }
            
            //p=term;//将p指针指向头结点；
            q++;

      
      }

    
    }

}


template<class T>
void   spareMatrix<T>::multiply()
{

    spareMatrix<T> Q(2,3,85000);//设置一个乘数矩阵
 
    Q.matrix_set();//要与本类相加的matrix
    if (col!= Q.getrow())//被加的矩阵列数与加的矩阵的行数不相等就做不了乘法
    {
        s<<-1<<endl;
        //把Q赋值给p
        delete term;

        listSize = Q.listSize;
        term = new matrixTerm[arrayLength];
        copy(Q.term,Q.term+listSize,term);
       
        row = Q.row;
        col = Q.col;

    }
    else
    {
        spareMatrix<T> curr(row,Q.getcol(),85000);//将乘的矩阵放在curr中
        int m = 0;//被乘矩阵的每的行数
        int s=0;//用来找到被乘矩阵的三元组

        while (m<row)
        {
           
            matrixTerm * tempcun = new matrixTerm[Q.col];//暂存mei一行的数
    
            int q = 0;//用来迭代相乘矩阵三元组的biaogan
    
            while(q<Q.listSize)
            {
                
                  while (term[s].row<m)
                   {
                       s++;
                   }
                   
                   if(term[s].row>m)
                   {
                       break;
                   }

                   
                    
                
        
                if (term[s].col==Q.term[q].row)
                {

                    tempcun[Q.term[q].col].value = tempcun[Q.term[q].col].value + term[s].value*Q.term[q].value ;
                    tempcun[Q.term[q].col].col = Q.term[q].col;
                    

                    q++;
                    // if (q==Q.listSize)
                    // {
                    //     s++;
                    // }
                   
                    
                    
                }
                else if (term[s].col!=Q.term[q].row )
                {
                    if (term[s].col>Q.term[q].row)
                    {
                        q++;
                    }
                    else
                    {
                        s++;
                    }
            
                }

            }

            //  int index=0;
            for(int i= 0;i<Q.col;i++)
            {
               
                if (tempcun[i].value!=0)
                {
                    tempcun[i].row = m;
                    curr.insert(curr.listSize,tempcun[i]);
                    // index = 1;

                }
                // if (index)
                // {
                //     while (term[s].row==m)
                //     {
                //         s++;
                //     }
                    
                // }
                
           
            }
            delete [] tempcun;

            m++;

        }   

            //将结果赋值给P
        delete term;
        listSize = curr.listSize;
        term =new matrixTerm[arrayLength];
        copy(curr.term,curr.term+listSize,term);
        row = curr.row;
        col = curr.col;



   
    }



  
//     spareMatrix<T> Q(2,3,85000);//设置一个乘数矩阵
  
    // Q.matrix_set();//要与本类相加的matrix
    // spareMatrix<T> curr(row,Q.getcol(),85000);//将乘的矩阵放在curr中

//     if (col!= Q.getrow())//被加的矩阵列数与加的矩阵的行数不相等就做不了乘法
//     {
//         s<<-1<<endl;
//         //把Q赋值给p
//         delete term;

//         listSize = Q.listSize;
//         term = new matrixTerm[arrayLength];
//         copy(Q.term,Q.term+listSize,term);
       
//         row = Q.row;
//         col = Q.col;

//     }
//     else
//     {
        
//         //以下四个整数均代表偏移量
//         int row_banner= 0;//指定每一行的开始
//         int row_finish=0;//指定每一行的结束
//         int col_banner= 0;//指定每一列的开始
//         int col_finish=0;//指定每一列的结束

//         matrixTerm*  Pp=term;//Pp指向被乘的矩阵的第一个元素
//         matrixTerm*  Qq=Q.term;
//         matrixTerm*  rowsearch=term;//用来搜索被乘矩阵的行
//         matrixTerm*  colsearch= Q.term;//用来搜索相乘矩阵的列
        
//         while (rowsearch!=term+listSize)
//         {
//             rowsearch++;
//             colsearch= Q.term;
            
//              //找到被乘矩阵的每一行
//             while (rowsearch!=term+listSize)
//             {
           
//                 if (rowsearch->row==(Pp+row_banner)->row)
//                 {
//                     row_finish++;
//                     rowsearch++;
//                 }
//                  else
//                 {
//                     break;
//                 }
            
//             }
//             //

//             while(colsearch!=Q.term+listSize)
//             {
//                 ////找到被乘矩阵的每一列
//                 colsearch++;
//                 while (colsearch!=Q.term+listSize)//找到被乘矩阵的每一行
//                 {
           
//                     if (colsearch->col==(Qq+col_banner)->col)
//                     {
//                         col_finish++;
//                         colsearch++;
//                     }
//                     else
//                     {
//                         break;
//                     }
            
//                 }


//                 int itrt_rowbegin=row_banner;//循环的时候要用到的行循环次数
//                 int itrt_rowend=row_finish;//循环的时候要用到的行循环次数
//                 matrixTerm temp;
//                 temp.row =(Pp+row_finish)->row ;
//                 temp.col =(Qq+col_finish)->col ;
//                 for ( itrt_rowbegin=row_banner ; itrt_rowbegin  <= itrt_rowend; itrt_rowbegin ++)
//                 {
//                     int itrt_colbegin=col_banner;//循环的时候要用到的列循环次数
//                     int itrt_colend=col_finish;//循环的时候要用到的列循环次数
                   
                   
//                    for (itrt_colbegin = col_banner; itrt_colbegin  <=itrt_colend; itrt_colbegin++)
//                    {
//                        if ((Pp+itrt_rowbegin)->col == (Qq+itrt_colbegin)->row)
//                        {
//                            temp.value =temp.value+ (Pp+itrt_rowbegin)->value*(Qq+itrt_colbegin)->value;
//                            break;
//                        }

                       
//                     }
                   
//                 }

//                 if (temp.value!=0)
//                 {
//                     curr.insert(curr.listSize,temp);
//                 }

//                 col_banner = col_finish= col_finish+1;
                
                
                
//             }

//             col_banner=0;
//             col_finish=0;
//             colsearch = Q.term;
//             colsearch ++;
//             row_banner = row_finish = row_finish+1;
            
//         }
//         //将结果赋值给P
//     delete term;
//     listSize = curr.listSize;
//     term =new matrixTerm[arrayLength];
//     copy(curr.term,curr.term+listSize,term);
//     row = curr.row;
//     col = curr.col;


// }

    
}

  




template<class T>
void spareMatrix<T>::transpose()
{

    matrixTerm* p=term;
    int i = listSize;
    while (i>0)
    {
        int temp = p->row;//交换行和列
        p->row = p->col;
        p->col = temp;

        p++;
        i--;
        /* code */
    }


    int temp = row;//交换行和列
        row = col;
        col = temp;

    //快速排序   
    int mapping  = (p->col)*col+p->col+1;//映射关系
    


    //排序按照映射关系小的依次递增,使用冒泡排序
    //int mapping  = (p->col)*col+p->col+1;//映射关系
     //p=term.begin();放在这个位置是错误的做法
    // for (int  t = 0; t<listSize-1 ; t++)
    // {
    //      p=term;
    //      matrixTerm* first = p;
    //      matrixTerm* next = ++p;
    //     for (int  j = 1; j <listSize-t ; j++)
    //         {
               
                
        
    //             if ( (first->row)*col+first->col+1 > (next->row)*col+next->col+1) 
    //             {
    //                 //matrixTerm* tempor = new matrixTerm(*first);

    //                 matrixTerm tempor = *first;
    //                 *first= *next;
    //                 *next=tempor;
    //             }
    //             first++;
    //             next++;
                
        
    //         }
       
    // }
    
    

    
}


template<class T>
void spareMatrix<T>::re_set()//重置矩阵
{
    int row;
    int col;
    cin>>row>>col;
    this->row = row;
    this->col = col;
    int zc;
    if (listSize!=0)
    {
        delete [] term;
        term = new matrixTerm[arrayLength];
        listSize = 0;
    }
    

    for (int  i = 0; i < row; i++)
    {
        for(int j=0;j<col;j++)
        {
            cin>>zc;
            if(zc!= 0)
            {   
                matrixTerm temp(i,j,zc);//i是矩阵的行数减一，j是矩阵的列数减一
                insert(listSize,temp);
            }
        }
    }


}


template<class T>
void spareMatrix<T>::matrix_set()//用来设置行映射的一位矩阵表示（x,y) value
{
    int row;
    int col;
    cin>>row>>col;
    int t;
    cin>>t;
    this->row = row;
    this->col = col;
    for (int  i = 0; i < t; i++)
    {
        matrixTerm temp;
        temp.write();
        insert(i,temp);
    }
}


template<class T>
void spareMatrix<T>::fulloutput()//只能对term中mapping的值按照从小到大的顺序排列的，才能全部输出
{
    //int all= row*col;
    matrixTerm* p=term;
    s<<row<<" "<<col<<endl;
    for (int i = 0; i < row; i++)
    {
        

        for (int j = 0; j < col; j++)
        {
            int mapping = (p->row)*col+p->col+1;//找到映射关系
            // int vrow = mapping/col+1;//找到对应的整除数(行数)
            // int vcol = mapping%col;//找到对应的余数(列数)
            int matrix_mapping = i*col+j+1;//矩阵的行主次序位置
            if (mapping != matrix_mapping)
            {
                s<<0<<" ";
                
            }
            else
            {
                s<<p->value<<" ";
                if (p !=NULL)
                {
                    p++;
                }
            }
            
        }

        s<<endl;
        
        
    }
    




    //cout<<row<<" "<<col<<endl;//先按标准输出
    

}

int main()
{
    spareMatrix<int> P(10, 5,85000);

    // P.re_set();
    // P.add();
    // P.output();
    // cout<<"-------------------------\n";
    // P.fulloutput();
    // // P.multiply();
    // // cout<<"------------------------"<<endl;
    // // P.output();
    // P.fulloutput();
  
    
    int w;
    cin>>w;

    while (w>0)
    {
        int direc;
        cin>>direc;
        if (direc == 1)
        {
            P.re_set();
           
        }
        else if(direc == 2)
        {
            P.multiply();
          

        }
        else  if(direc == 3)
        {
            P.add();
           
        }
        else if(direc == 4)
        {
            P.fulloutput();
        }
        else if(direc == 5)
        {
          
            P.transpose();
     
        }

        w--;
        
    }
    
    cout<<s.str();

    system("pause");
    

    
}


