#include <iostream>
#include <string>

using namespace std;

struct lbtNode
{
    int element; //存储符号
    lbtNode *leftChild;
    lbtNode *rightChild;
    lbtNode(int theElement)
    {
        element = theElement;
        leftChild = rightChild = NULL;
    }
};

class linkedBinaryTree
{
public:
    linkedBinaryTree(); //construct
    void output(lbtNode *);
    void outINorder()
    {
        output(root);
    }
    void makeTree(int element, linkedBinaryTree tree1, linkedBinaryTree tree2);
    void inorder_path(lbtNode *, int a[], int); //找到每个字符的路径长度
    lbtNode* getRoot()
    {
        return root;
    }

protected:
    lbtNode *root; //
};

linkedBinaryTree::linkedBinaryTree()
{
    root = NULL;
}

void linkedBinaryTree::makeTree(int element, linkedBinaryTree tree1, linkedBinaryTree tree2)
{
    root = new lbtNode(element);
    // root->element = element;
    root->leftChild = tree1.root;
    root->rightChild = tree2.root;
}

void linkedBinaryTree::output(lbtNode *t)
{
    if (t == NULL)
    {
        return;
    }
    output(t->leftChild);
    cout << t->element << "--";
    output(t->rightChild);
}

void linkedBinaryTree::inorder_path(lbtNode *t, int a[], int path_length)
{
    int path = path_length;
    if (t->element == 0)
    {
        path++;

        inorder_path(t->leftChild, a, path);
        // a[path]++;

        inorder_path(t->rightChild, a, path);
        // a[path]++; 
    }
    else
    {
        a[t->element] = path;
    }
    
}
//
struct huffmanNode
{
    linkedBinaryTree *tree;
    int weight; //权重

    void operator=(huffmanNode theNode)
    {
        tree = theNode.tree;
        weight = theNode.weight;
    }
};

class minHeap
{
public:
    minHeap(int size);                   //构造函数
    void to_initial(huffmanNode *, int); //初始化,空表
    void insert(huffmanNode);            //插入元素
    void pop();                          //删除根元素
    void exist_initail(int theSize);     //已存在的表的
    huffmanNode get_root();              //获根跟元素
    void sort();

protected:
    huffmanNode *heap_root;
    int arrayLength;
    int heapSize;
};

minHeap::minHeap(int size)
{
    heap_root = new huffmanNode[size];
    heapSize = 0;
    arrayLength = size + 1;
}

void minHeap::insert(huffmanNode thenode)
{
    if (heapSize == arrayLength - 1)
    {
        //改变数组的长度
    }

    int currentNode = ++heapSize;
    while (currentNode != 1 && heap_root[currentNode / 2].weight > thenode.weight)
    {
        heap_root[currentNode] = heap_root[currentNode / 2];
        currentNode /= 2;
    }

    heap_root[currentNode] = thenode;
}

huffmanNode minHeap::get_root()
{
    return heap_root[1];
}

void minHeap::to_initial(huffmanNode *hNode, int num)
{
    huffmanNode temp[num + 1];
    for (int i = 1; i <= num; i++)
    {
        insert(hNode[i]);
    }

    // int have_last_child = num / 2;
}

void minHeap::pop()
{
    huffmanNode lastElement = heap_root[heapSize--];
    int currtNode = 1;
    int child = 2; //currentNode的孩子
    while (child <= heapSize)
    {
        //heap[child]是currentNode的最小的孩子
        if (child < heapSize && heap_root[child].weight > heap_root[child + 1].weight)
        {

            child++;
        }

        if (heap_root[child].weight > lastElement.weight)
            break;

        heap_root[currtNode] = heap_root[child];
        currtNode = child;
        child *= 2;
    }
    heap_root[currtNode] = lastElement;
}

// void minHeap::exist_initail(int theSize)
// {
//     huffmanNode *theHeap = new huffmanNode[theSize + 1];
//     for (int i = 0; i < theSize; i++)
//     {
//         cin >> theHeap[i + 1].weight;
//     }

//     delete[] heap_root;
//     heap_root = theHeap;
//     heapSize = theSize;

//     for (int root = heapSize / 2; root >= 1; root--)
//     {
//         int rootElement = heap_root[root].weight;
//         int child = 2 * root;

//         while (child <= heapSize)
//         {
//             //    heapchild应该是兄第中的较小的
//             if (child < heapSize && heap_root[child].weight > heap_root[child + 1].weight)
//             {
//                 child++;
//             }

//             if (rootElement <= heap_root[child].weight)
//             {
//                 break; //可以
//             }
//             //    不可以
//             heap_root[child / 2].weight = heap_root[child].weight;
//             child *= 2; //这个地方之前写成了 child *= child;导致结果一直有错，还好我及时发X现了这个错误
//         }

//         heap_root[child / 2].weight = rootElement;
//     }
// }

//构造霍夫曼树
linkedBinaryTree *huffmanTree(int weight[], int n)
{
    //用权weight[1:n]生成霍夫曼树
    // 创建一组单节点的树
    huffmanNode *hNode = new huffmanNode[n + 1];
    linkedBinaryTree emptyTree;
    int index = 1;
    for (int i = 1; i <= n; i++)
    {
        if (weight[i] == 0)
        {
            continue;
        }

        hNode[index].weight = weight[i];
        hNode[index].tree = new linkedBinaryTree;
        hNode[index++].tree->makeTree(i, emptyTree, emptyTree);
    }

    //ues a array of single node to build minHeap
    minHeap heap(100);
    heap.to_initial(hNode, index - 1);

    //countinue to merge two trees from minHeap

    huffmanNode w, x, y;
    linkedBinaryTree *z;
    for (int i = 1; i < index - 1; i++)
    {
        x = heap.get_root();
        heap.pop();
        y = heap.get_root();
        heap.pop();

        //merge to be a one tree
        z = new linkedBinaryTree;
        z->makeTree(0, *x.tree, *y.tree);
        w.weight = x.weight + y.weight;
        w.tree = z;
        heap.insert(w);
        delete x.tree;
        delete y.tree;
    }

    return heap.get_root().tree;
}

int main()
{
    string test;
    cin >> test;
    int numbers[27] = {}; //用来存储每个字母的个数，1~a,2~b......26~z;
    for (int i = 0, num = test.size(); i < num; i++)
    {
        numbers[test[i] - 97 + 1]++;
    }

    // cout << "  "
    //      << "a "
    //      << "b "
    //      << "c "
    //      << "d "
    //      << "e "
    //      << "f "
    //      << "g "
    //      << "h "
    //      << "i "
    //      << "j "
    //      << "k "
    //      << "l "
    //      << "m "
    //      << "n "
    //      << "o "
    //      << "p "
    //      << "p "
    //      << "r "
    //      << "s "
    //      << "t "
    //      << "u "
    //      << "v "
    //      << "w "
    //      << "x "
    //      << "y "
    //      << "z " << endl;
    // for (int i = 0; i < 27; i++)
    // {
    //     cout << numbers[i] << " ";
    // }
    // cout << endl;

    linkedBinaryTree *result = huffmanTree(numbers, 26);
    // result->outINorder();
    // cout << endl;
    int code[27] = {};
    result->inorder_path(result->getRoot(),code,0);
    // for (int  i = 1; i <27; i++)
    // {
    //     cout<<code[i]<<"  ";
    // }
    
    int result__=0;
    for (int  i = 1; i < 27; i++)
    {
       result__+= code[i]*numbers[i];
    }
    cout<<result__<<endl;
    
    system("pause");
}