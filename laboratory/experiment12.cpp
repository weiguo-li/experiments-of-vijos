#include <iostream>
#include <deque>
#include <sstream>

using namespace std;

ostringstream ss;  //存放结果,连通分支的最小元素升序排列
ostringstream ss2; //存放字典序列的从s开始的bfs
ostringstream ss3; //存放字典序列的从t开始的bfs

struct linkedNode //邻接链表的节点
{
    int vertex;
    linkedNode *next;
    linkedNode()
    {
        vertex = 0;
        next = NULL;
    }
    linkedNode(int theVertex)
    {
        vertex = theVertex;
        next = NULL;
    }
};
class linear //创建线性表类
{
    friend class adjacencyGraph;

public:
    linear();
    void insert(int theNUmber)
    {
        if (first == NULL)
        {
            first = new linkedNode;
            first->vertex = theNUmber;
            return;
        }

        linkedNode *pre = first; //呀插入节点的前驱结点
        linkedNode *point = first->next;
        while (point != NULL && point->vertex < theNUmber)
        {
            pre = point;
            point = point->next;
        }
        linkedNode *newpoint = new linkedNode(theNUmber);
        if (point == NULL) //在尾部直接插入
        {
            pre->next = newpoint;
            newpoint = NULL;
        }
        else
        {
            newpoint->next = pre->next;
            pre->next = newpoint;
            newpoint = NULL;
        }

        // linkedNode* point = first;//找到链表的最后一个节点
        // while (point->next!=NULL)
        // {
        //     point = point->next;
        // }
        // 直接在链表头部后插入

        // point->next = first->next;
        // first->next = point;
        // point = NULL;
    }

    void earse(int theNUmber) //不可能去删除头结点
    {
        linkedNode *point = first->next;   //
        linkedNode *pre = first;           //要删除节点的前驱结点
        while (point->vertex != theNUmber) //找到顶点为目标元素的指针
        {
            pre = point;
            point = point->next;
        }
        pre->next = point->next;
        delete point;
    }
    linear(const linear &theLinear); //复制构造函数
    void output()
    {
        linkedNode *point = first;
        while (point != NULL)
        {
            cout << point->vertex << " ";
            point = point->next;
        }
    }

protected:
    linkedNode *first;
};

linear::linear()
{
    first = NULL;
}
linear::linear(const linear &theLinear)
{
    first = NULL;
    linkedNode *point = theLinear.first;
    while (point != NULL)
    {
        insert(point->vertex);
        point = point->next;
    }
}
//正式开始
class adjacencyGraph // build a no_direction graph
{
public:
    adjacencyGraph(int theNumber);
    void addEdge();                                //添加一条边
    void deleteage();                              //删除一条边
    void test_output();                            //
    int connected();                               //返回连通分支的个数
    void bfs(int v, int reach[], int lable, bool); //广度优先搜索
    void dfs(int v, int reach[], int lable, bool); //深度优先搜索
    int theLength_of_dfs(int s);                   //从顶点s开始的dfs序列长度
    int theLength_of_bfs(int t);                   //从顶点t开始的dfs序列长度
    int the_shortest_path(int s, int t);           //最短路径
protected:
    int number_of_vertex; //顶点的个数
    linear *all;
};

adjacencyGraph::adjacencyGraph(int theNumber)
{
    number_of_vertex = theNumber;
    all = new linear[theNumber + 1];
    for (int i = 1; i <= theNumber; i++)
    {
        all[i].insert(i);
    }

    // all = new linkedNode *[theNumber + 1];
    // for (int i = 1; i <= theNumber; i++) //邻接链表的初始化
    // {
    //     all[i] = new linkedNode;
    //     all[i]->vertex = i;
    // }
}

void adjacencyGraph::addEdge()
{
    int u;
    int v;
    cin >> u >> v;
    all[u].insert(v); //u中添加v
    all[v].insert(u); //v中添加u
}

void adjacencyGraph::deleteage()
{
    int u;
    int v;
    cin >> u >> v;
    all[u].earse(v); //u中删除v
    all[v].earse(u); //v中删除u
}

void adjacencyGraph::test_output()
{
    for (int i = 1; i <= number_of_vertex; i++)
    {
        all[i].output();
        cout << endl;
    }
}

void adjacencyGraph::bfs(int v, int reach[], int lable, bool flag = false)
{
    deque<int> q;
    reach[v] = lable;
    q.push_back(v);
    while (!q.empty())
    {
        // 从队列中删除一个标记过的顶点
        int w = q.front();
        q.pop_front();
        // 标记所有没有到达的邻接与顶点w的顶点
        linkedNode *iw = all[w].first->next; //友元函数的缘故
                                             //可能单顶点的情况
        if (iw == NULL)
        {
            break;
        }
        int u = (iw->vertex);

        while (u != 0)
        {
            if (reach[u] == 0) //u没有到达
            {

                if (flag)
                {
                    ss3 << u << " ";
                }

                q.push_back(u);
                reach[u] = lable;
            }
            iw = iw->next;
            if (iw == NULL)
            {
                break;
            }
            u = (iw->vertex);
        }
        delete iw;
    }
}

void adjacencyGraph::dfs(int v, int reach[], int lable, bool flag = false) //flag用于判断是否要把每次找的的结果存入ss2
{
    reach[v] = lable;
    linkedNode *iv = all[v].first->next; //邻接与该顶点的第一个元素（字段顺序）
    if (iv == NULL)
    {
        return;
    }

    int u = iv->vertex;
    while (u != 0)
    {
        if (reach[u] == 0)
        {
            if (flag)
            {

                ss2 << u << " ";
            }

            dfs(u, reach, lable, flag);
        }
        iv = iv->next;
        if (iv == NULL)
        {
            break;
        }

        u = iv->vertex;
    }
    delete iv;
}

int adjacencyGraph::connected()
{
    int n = number_of_vertex;
    int *reach = new int[n + 1]; //默认reach[i]= 0;
    for (int i = 0; i <= n; i++) //初始化构建都为未到达的
    {
        reach[i] = 0;
    }

    int lable = 0; //最后一个构件的编号
    for (int i = 1; i <= n; i++)
    {
        if (reach[i] == 0) //顶点i未到达
        {
            ss << i << " ";
            lable++;
            bfs(i, reach, lable);
        }
    }

    return lable;
}

int adjacencyGraph::theLength_of_dfs(int s)
{
    int *reach = new int[number_of_vertex + 1];
    for (int i = 0; i <= number_of_vertex; i++) //初始化
    {
        reach[i] = 0;
    }

    dfs(s, reach, 1, true);
    int number = 0;
    for (int i = 1; i <= number_of_vertex; i++)
    {
        if (reach[i] != 0)
        {
            number++;
            //    ss2<<i<<" ";
        }
    }

    return number;
}
int adjacencyGraph::theLength_of_bfs(int t)
{
    int *reach = new int[number_of_vertex + 1];
    for (int i = 0; i <= number_of_vertex; i++) //初始化
    {
        reach[i] = 0;
    }

    bfs(t, reach, 1, true);
    int number = 0;
    for (int i = 1; i <= number_of_vertex; i++)
    {
        if (reach[i] != 0)
        {
            number++;
            //    ss2<<i<<" ";
        }
    }
    return number;
}

int adjacencyGraph::the_shortest_path(int s, int t)
{
    int lable = 1;
    // int *path = new int[number_of_vertex + 1];
    // path[1] = s;//
    int length = 0; //路径的长度

    int *reach = new int[number_of_vertex + 1];
    for (int i = 0; i <= number_of_vertex; i++) //初始化为0，表示未被访问
    {
        reach[i] = 0;
    }

    deque<int> q;
    reach[s] = lable;
    q.push_back(s);
    int index = q.back(); //判断每一层的遍历
    while (!q.empty())
    {
        // 从队列中删除一个标记过的顶点
        int w = q.front();
        int flag = w;
        if (w == index)
        {
            length++;
            
        }

        q.pop_front();
        // 标记所有没有到达的邻接与顶点w的顶点
        linkedNode *iw = all[w].first->next; //友元函数的缘故
        if (iw == NULL)
        {
            break;
        }

        int u = (iw->vertex);

        while (u != 0)
        {
            if (reach[u] == 0) //u没有到达
            {
                if (u == t) //是否等于终点
                {
                    if (flag!=index)//之前忘了加这个条件，要很仔细才能想察觉
                    {
                       length++;//
                    }
                   
                   
                    return length;
                }

                q.push_back(u);
                reach[u] = lable;
            }
            iw = iw->next;
            if (iw == NULL)
            {
                break;
            }
            u = (iw->vertex);
        }

        if (flag == index)
        {
            index = q.back();
        }

        // delete iw;
    }

    return -1; //不存在路径
}

int main()
{
    int n, m, s, t; //n 代表图中点的个数，m代表接下来共有m个操作，s代表起始点，t代表终点。
    cin >> n >> m >> s >> t;
    ss2 << s << " ";
    ss3 << t << " ";

    adjacencyGraph test(n);
    while (m > 0)
    {
        int select;
        cin >> select;
        switch (select)
        {
        case 0:
            test.addEdge(); //增加一条边

            break;

        case 1:
            test.deleteage(); //删除一条边

            break;
        default:
            break;
        }

        m--;
    }

    cout << test.connected() << endl;
    cout << ss.str() << endl;
    cout << test.theLength_of_dfs(s) << endl;
    cout << ss2.str() << endl;
    cout << test.theLength_of_bfs(t) << endl;
    cout << ss3.str() << endl;
    cout << test.the_shortest_path(s, t);
    system("pause");
}