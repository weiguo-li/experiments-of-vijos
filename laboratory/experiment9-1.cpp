#include <iostream>
#include <deque>
using namespace std;

struct BTNode //define the binaryTree's node;
{
    int binahao;   //memory the bianhao of the Node;
    BTNode *left;  //point to left children
    BTNode *right; //point to right children
    BTNode()
    {
    }
    BTNode(int BH) //构造函数
    {
        binahao = BH;
        left = right = NULL;
    }
};
class binaryTree
{
public:
    binaryTree(int n);
    BTNode *proOrder(BTNode *t, int BH);        //前序遍历
    int inOrder(BTNode *t);                     //中序遍历
    void postOder(BTNode *t);                   //后续遍历
    void levelOder(BTNode *t);                  //层次遍历
    BTNode *levelOderSearch(BTNode *t, int BH); // 层次遍历查找
    int height(BTNode *t) const;                //求出以t指向的节点为根节点的子树的高度
    int number(BTNode *t);                      //计算以t指向的节点为根节点的子树的元素个数
    void insert(int bNumber);                   //向该树种插入一个节点
    void outputnumber(BTNode **a);              //输出每个节点为根元素的节点的个数
    BTNode *visit(BTNode *t, int BH);
    void levelPOint(BTNode **&a); //遍历存储节点
    int visitfornumber(BTNode *t);
    void output();                 //层次遍历输出
    void outputheight(BTNode **a); //输出每一个节点为根的高度
protected:
    BTNode *root; //
    int treeSize; //record the number of the Node of the binaryTree
};

binaryTree::binaryTree(int n) //construct functiona;
{
    root = new BTNode(1);
    // root->binahao=1;
    // root->left=root->right =NULL;
    treeSize = n;
}

BTNode *binaryTree::visit(BTNode *t, int BH)
{
    if (t->binahao == BH)
    {
        return t;
    }

    else
        return NULL;
}

int binaryTree::visitfornumber(BTNode *t)
{
    static int number = 0;
    number++;
    return number;
}

BTNode *binaryTree::proOrder(BTNode *t, int BH) //前序遍历找编号为BH的节点
{
    BTNode *thePoint = NULL;
    // int i;
    if (t != NULL)
    {
        BTNode *temp = visit(t, BH);
        if (temp != NULL) //找到了编号为BH的节点
        {
            thePoint = temp;
            return temp;
        }
        else
        {

            temp = proOrder(t->left, BH);
            // if (temp->binahao != BH)
            // {
            //     temp = NULL;
            // }

            thePoint = temp;
            if (temp == NULL)
            {

                temp = proOrder(t->right, BH);
                thePoint = temp; //非常关键的一步，想了合唱时间才尝试出来
            }

            // goto a;
        }
    }

    return thePoint;
}

void binaryTree::levelPOint(BTNode **&a)
{
    BTNode *des = root;
    deque<BTNode *> q;
    while (des != NULL)
    {
        // a[des->binahao] = des;
        a[des->binahao] = des;

        if (des->left != NULL)
        {
            q.push_back(des->left);
        }
        if (des->right != NULL)
        {
            q.push_back(des->right);
        }

        if (q.size() == 0)
        {
            break;
        }

        des = q.front();
        q.pop_front();
    }
}

BTNode *binaryTree::levelOderSearch(BTNode *t, int BH)
{
    deque<BTNode *> q;
    BTNode *result = NULL;
    while (t != NULL)
    {

        if (t->binahao == BH)
        {
            result = t;
            break;
        }

        if (t->left != NULL)
        {
            q.push_back(t->left);
        }
        if (t->right != NULL)
        {
            q.push_back(t->right);
        }
        if (q.size() == 0)
        {
            break;
        }

        t = q.front();
        q.pop_front();
    }

    return result;
}
void binaryTree::insert(int bNumber)
{
    BTNode *des = levelOderSearch(root, bNumber); //proOrder(root, bNumber);//找到插入的目标节点的父节点
    int letfB;
    int RightB;
    cin >> letfB >> RightB;
    if (letfB != -1)
    {
        des->left = new BTNode(letfB);
    }
    if (RightB != -1)
    {
        des->right = new BTNode(RightB);
    }
}

int binaryTree::inOrder(BTNode *t) //中序遍历以t指向的节点为根节点的子树的节点数目
{
    static int number = 0;
    if (t != NULL)
    {
        inOrder(t->left); //这个地方仍然有很大的疑问
        number++;
        inOrder(t->right);
    }

    // int NodeNumber = 0; 这个竟然可以用来找到节点的高度
    // if (t!=NULL)
    // {
    //     NodeNumber =inOrder(t->left);//这个地方仍然有很大的疑问
    //     NodeNumber++;
    //     inOrder(t->right);

    // }

    return number;
}
void binaryTree::postOder(BTNode *t)
{
    if (t != NULL)
    {
        postOder(t->left);
        postOder(t->right);
        cout << t->binahao;
    }
}

void binaryTree::levelOder(BTNode *t)
{
    deque<BTNode *> q;
    while (t != NULL)
    {

        cout << t->binahao << " ";

        if (t->left != NULL)
        {
            q.push_back(t->left);
        }
        if (t->right != NULL)
        {
            q.push_back(t->right);
        }
        if (q.size() == 0)
        {
            break;
        }

        t = q.front();
        q.pop_front();
    }
}

void binaryTree::output()
{
    levelOder(root);
}

int binaryTree::height(BTNode *t) const
{
    if (t == NULL)
    {
        return 0;
    }

    int hl = height(t->left);  //左树高
    int hr = height(t->right); //右树高
    if (hl > hr)
    {
        return ++hl;
    }

    else
    {
        return ++hr;
    }
}

void binaryTree::outputheight(BTNode **a)
{
    for (int i = 1; i <= treeSize; i++)
    {
        BTNode *temp = a[i]; // levelOderSearch(root, i); //proOrder(root,i);//前序遍历找到编号为i的节点
        int het = height(temp);
        cout << het << " ";
    }
}

void binaryTree::outputnumber(BTNode **a)
{
    for (int i = 1; i <= treeSize; i++)
    {
        BTNode *temp = a[i]; //levelOderSearch(root, i); //proOrder(root,i);
        int alltemp = inOrder(temp);
        static int allfront = 0;
        cout << alltemp - allfront << " ";
        allfront = alltemp;
    }
}
int binaryTree::number(BTNode *t) //找到以t节点为根的子树的节点个数
{
    int result = inOrder(t);
    return 0;
}
int main()
{
    int n;
    cin >> n;
    binaryTree test(n);
    int i = 1;
    while (i <= n)
    {
        test.insert(i);
        i++;
    }

    BTNode **point = new BTNode *[n];
    test.levelPOint(point);

    test.output();
    cout << endl;

    test.outputnumber(point);
    cout << endl;

    test.outputheight(point);
    cout << endl;
    system("pause");
}