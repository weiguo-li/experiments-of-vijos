#include <iostream>
#include <deque>
using namespace std;
struct BTNode
{
    int ele;
    BTNode *left;
    BTNode *right;
};

BTNode *divide(int *a, int *b, int num)
{
    if (num == 0)
    {
        return NULL;
    }
    BTNode *node = new BTNode;
    node->ele = *a;
    int index = 0;
    // int* left;
    // int* right;
    // static int* result =new int[num]

    for (index; index < num; index++)
    {
        if (b[index] == *a)
        {
            break;
        }
    }

    node->left = divide(a + 1, b, index);
    node->right = divide(a + index + 1, b + index + 1, num - index - 1);
    cout << node->ele << " ";
    return node;
}

int main()
{
    int n;
    cin >> n;
    int *pre = new int[n];
    int *inorder = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> pre[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> inorder[i];
    }

    divide(pre, inorder, n);
    cout << endl;
}