// Immerse_in_LeetCode.h : 此文件包含部分结构体定义。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
struct ListNode {
    int val;    
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
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