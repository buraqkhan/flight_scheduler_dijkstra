#include <iostream>
using namespace std;

template<class U>
class PriorityQueue
{
private:
    struct Node{
        U priority;
        U info;
        string value;
        Node* next;
    };
    Node* front;
public:
    PriorityQueue(){
        front=NULL;
    }

    void insert(U item, U prio, string val){
        Node* temp = new Node;
        Node* curr;
        temp->priority=prio;
        temp->info=prio;
        temp->value=val;
        if(this->front==NULL || this->front->priority > prio){
            temp->next=front;
            front=temp;
        }
        else{
            curr=front;
            while(curr->next!=NULL && curr->next->priority <= prio){
                curr=curr->next;
            }
            temp->next=curr->next;
            curr->next=temp;
        }
    }
    
    U deleteMin(){
        U value=0;
        Node *temp;
        if(front==NULL){
            cout<<"Queue empty";
        }
        else{
            temp=front;
            value=temp->info;
            front=front->next;
        }
        return value;
    }
    
    string retCity(){
        Node* temp;
        temp=front;
        return temp->value;
    }
    
    bool isEmpty(){
        if(front==NULL){
            return true;
        }
        return false;
    }

    void Display(){
        Node *curr;
        curr=front;
        if(front==NULL){
            cout<<"Queue is empty";
        }
        else{
            while(curr!=NULL){
                cout<<"Queue: ";
                cout<<curr->priority<<" "<<curr->value<<" ";
                curr=curr->next;
            }
        }
    }
};

