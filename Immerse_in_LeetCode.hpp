// Immerse_in_LeetCode.h : 此文件包含部分结构体定义。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
using namespace std;
struct ListNode {
    int val;    
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

//Definition for a binary tree node.
struct TreeNode {
    int val;  
    TreeNode *left;
    TreeNode *right;  
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// range-based loop
void PrintVecofVec(vector<vector<int> >& res) {
  for (auto& rowV : res) {
	cout << "[ ";
    for (auto& el : rowV) {
      cout << el << " ";
    }
    cout << "] ";
  }
  cout << endl;
}