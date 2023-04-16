#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* insertNode(ListNode* head, ListNode* newNode) {
        if (head == nullptr) {
            newNode->next = nullptr;
            head = newNode;
        } else {
            ListNode* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            newNode->next = nullptr;
            temp->next = newNode;
        }
        return head;
    }

    ListNode* buildLists(vector<int>& a) {
        int len = a.size();
        ListNode* ans = new ListNode();
        ans->val = a[0];
        ans->next = nullptr;
        int flag = 1;
        while (flag < len) {
            ListNode* newNode = new ListNode();
            newNode->val = a[flag];
            newNode->next = nullptr;
            ans = insertNode(ans, newNode);
            flag++;
        }
        return ans;
    }

    void printNode(ListNode* node) {
        while (node != nullptr) {
            cout << node->val << endl;
            node = node->next;
        }
    }

    bool isNeedReverse(ListNode* head, int k) {
        int count = 1;
        if (head == nullptr) return false;
        while (count < k) {
            if (head->next == nullptr) return false;
            else head = head->next;
            count++;
        }
        return true;
    }
    vector<ListNode*> reverseK(ListNode* head, int k) {
        vector<ListNode*> ans = {head, head};
        if (k == 1) return ans;
        else if (k == 2) {
            ListNode *cur = head->next;
            if (cur->next == nullptr) head->next = nullptr;
            else head->next = cur->next;
            cur->next = head;
            ans = {cur, head};
            return ans;
        } else {
            ListNode *left = head, *cur = head;
            int step = 0, stateCount = 0;
            while (step <= k-2) {
                // update states--Node(head), Node(left), Node(cur)
                head = cur;
                left = head;
                cur = head->next;
                stateCount = step;
                while (stateCount > 0) {
                    left = left->next;
                    cur = cur->next;
                    stateCount--;
                }

                // reverse operation
                left->next = cur->next;
                cur->next = head;
                step++;
            }
            // Get Node(head)
            head = cur;
            // Get Node(tail)
            ListNode *tail = head->next;
            int countTail = k - 2;
            while(countTail--) tail = tail->next;
            ans = {head, tail};
        }

        return ans;
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        if (k == 1) return head;

        vector<ListNode*> headAndTail = reverseK(head, k);
        ListNode *ans = headAndTail[0], *tail = headAndTail[1];

        while (isNeedReverse(tail->next, k)) {
            // cout << "-------------------" << endl;
            // printNode(tail);
            headAndTail = reverseK(tail->next, k);
            tail->next = headAndTail[0];
            tail = headAndTail[1];
        }

        return ans;
    }
};

// Line 92: Char 32: runtime error: member access within null pointer of type 'ListNode' (solution.cpp)
// SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior prog_joined.cpp:101:32


int main() {
    Solution *s = new Solution();
    vector<int> a = {1, 2, 3, 4};
    ListNode* lista = s->buildLists(a);
    cout << "is : " << s->isNeedReverse(lista, 2) << endl;
    // vector<ListNode*> ans1 = s->reverseK(lista, 2);
    // s->printNode(ans1[0]);

    ListNode* ans = s->reverseKGroup(lista, 2);
    s->printNode(ans);
    return 0;
}