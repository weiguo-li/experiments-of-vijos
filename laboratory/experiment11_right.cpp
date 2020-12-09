#include <iostream>
#include <sstream>
#include <queue>
using namespace std;
ostringstream s; //记录输出的结果
int temp_key;    //存放名词的关键值,名词最小为1，不是0
struct IBSTnode
{
    int key;          //关键字
    int leftSize = 0; //节点左边孩子的个数
    IBSTnode *leftchild;
    IBSTnode *rightchild;
    IBSTnode(int thekey)
    {
        key = thekey;
        rightchild = leftchild = NULL;
    }

    IBSTnode(int thekey, IBSTnode *lt, IBSTnode *rt)
    {
        key = thekey;
        leftchild = lt;
        rightchild = rt;
    }
    IBSTnode(int thekey, IBSTnode *lt, IBSTnode *rt, int theltSize)
    {
        key = thekey;
        leftchild = lt;
        rightchild = rt;
        leftSize = theltSize;
    }
};

class indexBStree //链表描述
{
public:
    indexBStree();
    int insert(int theNode);             //向二叉搜索树种插入一个元素
    int erase(int k);                    //删除一个关键字为k的元素
    int erase_byRank(int b);             //通过名次的大小删除
    int find(int k);                     //查找关键字为k的元素
    int find_byRank(int b);              //通过名词的值查找
    void ascent(IBSTnode *t);            //升序输出所有元素的的值
    void output();                       //输出结果
    int find_key(IBSTnode *t, int rank); //找到名次为rank的节点的key值
    IBSTnode *getroot()
    {
        return root;
    }

protected:
    IBSTnode *root; //根节点
};

indexBStree::indexBStree()
{
    root = NULL;
}

int indexBStree::find(int k)
{
    int yihou_result = 0; //用来记录，每次查找的异或值
    IBSTnode *p = root;   //从根开始找
    while (p != NULL)
    {
        if (p->key > k) //往左子树找
        {
            yihou_result ^= p->key;
            p = p->leftchild;
        }
        else
        {
            if (p->key < k) //往右子树找
            {
                yihou_result ^= p->key;
                p = p->rightchild;
            }
            else
            {
                return yihou_result ^ k;
            }
        }
    }

    return 0;
}

int indexBStree::insert(int theNode)
{
    IBSTnode *p = root;   //用来寻找插入的位置
    IBSTnode *pp = NULL;  //p所指向的节点的父节点，即应该插入节点的父节点
    int yihuo_result = 0; //存放遍历节点的以后异或的结果
    // bool flag = true;无用，对leftSize的一次尝试
    queue<IBSTnode *> que;
    while (p != NULL)
    {
        pp = p;
        if (theNode < p->key)
        {
            yihuo_result ^= p->key;
            p = p->leftchild;
            que.push(pp);
            // if (p != NULL)  多余，也是对leftSzie的一次尝试
            // {    pp->leftSize++;
            // }
        }
        else
        {
            if (theNode > p->key)
            {
                yihuo_result ^= p->key;
                p = p->rightchild;
            }
            else
            {
                return 0; //已存在
            }
        }
    }

    while (!que.empty())
    {
        que.front()->leftSize++;
        que.pop();
    }

    //申请一个新的节点存放插入的节点，并与pp所指向的节点连接
    IBSTnode *newNode = new IBSTnode(theNode);
    if (root != NULL)
    {
        if (theNode < pp->key) //插入到左边
        {
            pp->leftchild = newNode;
        }
        else
        {
            pp->rightchild = newNode;
        }
    }
    else
    {
        root = newNode; //插入到一颗空树
    }

    return yihuo_result;
}

void indexBStree::ascent(IBSTnode *t)
{
    if (t == NULL)
    {
        return;
    }

    ascent(t->leftchild);
    s << t->key << "  " << t->leftSize << " " << endl;

    ascent(t->rightchild);
}

void indexBStree::output()
{
    ascent(root);
}

int indexBStree::erase(int k)
{
    int yihuo_result = 0; //存放结果的异或值
    IBSTnode *p = root;   //代表从跟开始寻找要擅长的的元素
    IBSTnode *pp = NULL;  //pp是指向p的父节点的指针、
    while (p != NULL && p->key != k)
    {
        yihuo_result ^= p->key;

        pp = p;
        if (k < p->key) //向左边的孩子找
        {
            p = p->leftchild;
        }
        else
        {
            p = p->rightchild;
        }
    }

    if (p == NULL)
    {
        return 0; //未找到
    }
    else //修改LeftSzie的值
    {
        // if(p->leftchild!=NULL&&p->rightchild!=NULL) //要删除的节点有两个孩子
        // {
        //这一次去去遍历直到根节点的leftSize
        IBSTnode *p1 = root; //代表从跟开始寻找要擅长的的元素
        // IBSTnode *pp1 = NULL; //pp是指向p的父节点的指针、
        while (p1 != NULL && p1->key != k)
        {

            // pp1 = p1;
            if (k < p1->key) //向左边的孩子找
            {
                p1->leftSize--;

                p1 = p1->leftchild;
            }
            else //向右边孩子找
            {
                p1 = p1->rightchild;
            }
        }
        if (p->leftchild != NULL && p->rightchild != NULL) //要删除的节点有两个孩子
        {
            //这一次从要删除节点的右子树开是遍历leftSize直到最左边的叶子结点
            IBSTnode *s = p->rightchild; //
            // IBSTnode *ps = p;            //s 的父节点
            while (s->leftchild != NULL)
            {
                s->leftSize--;
                // /ps = s;
                s = s->leftchild;
            }
        }

        // }
        else if (p->leftchild != NULL && p->rightchild == NULL) //要删除的节点只有一个孩子，并且该孩子是左孩子，如果是右孩子，则不用更新left Size的值
        {
            p->leftSize--;
        }
        //		else if()
        //		{
        //
        //		}

        // if (p != NULL)
        // {
        //     p->leftSize--;
        // }
    }

    //p有两个孩子的情况
    if (p->leftchild != NULL && p->rightchild != NULL)
    {
        //在p的右子树中寻找最大的元素
        IBSTnode *s = p->rightchild; //
        IBSTnode *ps = p;            //s 的父节点
        while (s->leftchild != NULL)
        {
            ps = s;
            s = s->leftchild;
        }

        // 将右边最小的元素移动到p;
        IBSTnode *q = new IBSTnode(s->key, p->leftchild, p->rightchild, p->leftSize);

        if (pp == NULL) //删除的元素是根元素
        {
            root = q;
        }

        else if (pp->leftchild == p) //删除的是pp的左孩子
        {
            pp->leftchild = q;
        }
        else
        {
            pp->rightchild = q;
        }

        //转换成一个孩子节点的关键
        if (ps == p) //pp去指向要删除节点的父节点
        {
            pp = q;
        }
        else
        {
            pp = ps;
        }

        delete p;
        p = s; //p指向新的要删除的节点
    }

    //p最多只有给1个孩子
    IBSTnode *c; //存放指向孩子的指针

    if (p->leftchild != NULL)
    {
        c = p->leftchild;
    }
    else
    {
        c = p->rightchild;
    }

    //删除p
    if (p == root)
    {
        root = c;
    }
    else
    {
        //p是pp的左孩子还是右孩子
        if (p == pp->leftchild)
        {
            pp->leftchild = c;
        }
        else
        {
            pp->rightchild = c;
        }
    }

    delete p;

    return yihuo_result ^ k; //最初忘记异或了k
}

int indexBStree::find_key(IBSTnode *t, int rank)
{
    int result;
    IBSTnode *p = t;
    if (p->leftSize >= rank) //往左走
    {
        p = p->leftchild;
        while (p->leftSize >= rank)
        {
            p = p->leftchild; //接着往左走
        }

        if (p->leftSize + 1 == rank) //
        {
            result = p->key;
            return result;
        }
        else
        {
            int fic_rank = rank - p->leftSize - 1;
            return find_key(p->rightchild, fic_rank);
        }
    }
    else
    {
        if (p->leftSize + 1 == rank)
        {
            result = p->key;
            return result;
        }
        else
        {
            int fic_rank = rank - p->leftSize - 1;
            return find_key(p->rightchild, fic_rank);
        }
    }
    // return 0;
    // return  result;
}
int indexBStree::find_byRank(int b)
{
    // 先找到到名次所对应的key值
    // 再调用按照关键字查找的函数find()
    int kkey = find_key(root, b); //找到名词为b的元素的关键字
    return find(kkey);
}

int indexBStree::erase_byRank(int b)
{
    int kkey = find_key(root, b); //找到名词为b的元素的关键字
    return erase(kkey);
}

int main()
{
    indexBStree test;
    //     test.insert(12);
    //     test.insert(7);
    //     test.insert(1);
    //     test.insert(9);
    //     test.insert(15);
    //     test.insert(13);
    //     test.insert(18);
    //     // test.insert(67);
    //     test.output();
    //     cout << s.str() << endl;
    //     cout << "---------------" << endl;
    //     test.erase(12);
    //    test.output();
    //    cout<<s.str()<<endl;

    int op_number;
    std::cin >> op_number;
    while (op_number > 0)
    {
        int a, b;
        std::cin >> a >> b;
        switch (a)
        {
        case 0:
            s << test.insert(b) << endl; //向搜索树种插入插入b

            break;

        case 1:
            s << test.find(b) << endl; //向搜索树种查找b

            break;

        case 2:
            s << test.erase(b) << endl; //搜索树中删除 b

            break;

        case 3:
            s << test.find_byRank(b) << endl; //查找搜索树中名次为 b 的元素

            break;
        case 4:
            s << test.erase_byRank(b) << endl; //删除搜索树中名次为 b 的元素

            break;

        default:
            break;
        }
        op_number--;
    }
    cout << s.str();
    std::system("pause");
}