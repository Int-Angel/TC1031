/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *list = new ListNode();
        ListNode *current = list;
        
        while(l1 && l2){
            if(l1->val <= l2->val){
                ListNode *temp = l1;
                current->next = temp;
                current = temp;
                l1 = l1->next;
            }else{
                ListNode *temp = l2;
                current->next = temp;
                current = temp;
                l2 = l2->next;
            }
        }
        
        while(l1){
            ListNode *temp = l1;
            current->next = temp;
            current = temp;
            l1 = l1->next;
        }
        
        while(l2){
            ListNode *temp = l2;
            current->next = temp;
            current = temp;
            l2 = l2->next;
        }
        
        return list->next;
    }
};