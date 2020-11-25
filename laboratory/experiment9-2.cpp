#include <iostream>
#include <deque>
using namespace std;

void divide(deque<int> &a, deque<int> &b, int num)
{
    static int index = 0; //前序遍历的数组的位置
    deque<int> left, right;
    // int* leftpoint;
    // int* rightpoint;
    static deque<int> result; //存放后续遍历的结果
    if (!b.empty() && index < num)
    {
        int i = 0; //找到中序遍历的数组的与前序遍历数组对应的节点
        for (i = 0; i < num; i++)
        {

            if (b.at(i) == a[index])
            {
                break;
                // index++;
            }
        }
        // leftpoint = new int[i];
        // rightpoint = new int [num-i-1];

        int j = 0;
        while (j < num) //将中序遍历的数组分成三类
        {
            if (j < i)
            {
                // leftpoint[j] = b[i];

                left.push_back(b.at(j));
                j++;
            }
            else if (j > i)
            {
                // rightpoint[j-i-1] = b[j];
                right.push_back(b.at(j));
                j++;
            }
            else
            {
                result.push_back(b.at(j));
                j++;
            }
        }
        index++;
        if (left.size() == 1)
        {
            cout << left.at(0) << " ";
            index++;
            // cout<<result.back()<<" ";
            // result.pop_back();
        }
        else
        {
            divide(a, left, left.size());
        }

        if (right.size() == 1)
        {
            cout << right.at(0) << " ";
            cout << result.back() << " ";
            result.pop_back();
            index++;
        }
        else
        {
            divide(a, right, right.size());
            cout << result.back() << " "; //非常重要的一步
            result.pop_back();
        }
        // divide(a, right, right.size());
    }
}

int main()
{
    int n;
    cin >> n;
    //
    deque<int> a1;
    deque<int> b1;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        a1.push_back(a);
    }

    for (int i = 0; i < n; i++)
    {
        int b;
        cin >> b;
        b1.push_back(b);
    }

    divide(a1, b1, n);
    cout << "this is a test" << endl;
    system("pause");
}