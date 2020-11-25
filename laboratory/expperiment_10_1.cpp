#include <iostream>
#include<sstream>
using namespace std;
ostringstream s;
struct heapNode
{
    int element;
    // heapNode *left;
    // heapNode *right;
    // heapNode()
    // {
    //     left = right = NULL;
    // }
};

class minHeap
{
public:
    minHeap(int size);               //构造函数
    void to_initial(int);            //初始化,空表
    void insert(int number);         //插入元素
    void pop();                      //删除根元素
    void exist_initail(int theSize); //已存在的表的
    int get_root();                  //获根跟元素
    void sort();                     //排序

protected:
    heapNode *heap;
    int arrayLength;
    int heapSize;
};

minHeap::minHeap(int size)
{
    heap = new heapNode[size];
    heapSize = 0;
    arrayLength = size + 1;
}

void minHeap::insert(int number)
{
    if (heapSize == arrayLength - 1)
    {
        //改变数组的长度
    }

    int currentNode = ++heapSize;
    while (currentNode != 1 && heap[currentNode / 2].element > number)
    {
        heap[currentNode] = heap[currentNode / 2];
        currentNode /= 2;
    }

    heap[currentNode].element = number;
}

int minHeap::get_root()
{
    return heap[1].element;
}
void minHeap::to_initial(int num)
{
    heapNode temp[num + 1];
    for (int i = 1; i <= num; i++)
    {
        int tp;
        cin >> tp;
        insert(tp);
    }

    // int have_last_child = num / 2;
}

void minHeap::pop()
{
    int lastElement = heap[heapSize--].element;
    int currtNode = 1;
    int child = 2; //currentNode的孩子
    while (child <= heapSize)
    {
        //heap[child]是currentNode的最小的孩子
        if (child < heapSize && heap[child].element > heap[child + 1].element)
        {

            child++;
        }

        if (heap[child].element > lastElement)
            break;

        heap[currtNode].element = heap[child].element;
        currtNode = child;
        child *= 2;
    }
    heap[currtNode].element = lastElement;
}

void minHeap::exist_initail(int theSize)
{
    heapNode *theHeap = new heapNode[theSize + 1];
    for (int i = 0; i < theSize; i++)
    {
        cin >> theHeap[i + 1].element;
    }

    delete[] heap;
    heap = theHeap;
    heapSize = theSize;

    for (int root = heapSize / 2; root >= 1; root--)
    {
        int rootElement = heap[root].element;
        int child = 2 * root;

        while (child <= heapSize)
        {
            //    heapchild应该是兄第中的较小的
            if (child < heapSize && heap[child].element > heap[child + 1].element)
            {
                child++;
            }

            if (rootElement <= heap[child].element)
            {
                break; //可以
            }
            //    不可以
            heap[child / 2].element = heap[child].element;
            child *= 2; //这个地方之前写成了 child *= child;导致结果一直有错，还好我及时发X现了这个错误
        }

        heap[child / 2].element = rootElement;
    }
}

void minHeap::sort()
{
    int theSize;
    cin >> theSize;
    exist_initail(theSize);
    while (heapSize > 0)
    {
       s<< get_root() << " ";
        pop();
    }
}

int main()
{
    int heapAmount;
    cin >> heapAmount;

    minHeap test(10000);
    test.to_initial(heapAmount);
    s<<test.get_root()<<endl;

    int m;
    cin >> m;
    while (m > 0)
    {
        int op_number;
        cin >> op_number;
        int num;
        // heapNode* heap = new heapNode[10000];
        if (op_number == 1)
        {
            cin >> num;
        }

        switch (op_number)
        {
        case 1:
            test.insert(num);
            s << test.get_root() << endl;
            break;

        case 2:
            test.pop();
            s << test.get_root() << endl;
            break;
        case 3:
            test.sort();
            break;

        default:
            break;
        }

        m--;
    }

    cout<<s.str();
    system("pause");
}
