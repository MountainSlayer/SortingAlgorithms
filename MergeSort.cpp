//Purpose: Reviewing mergesort implementation
//Time complexity: O(nlogn) (doing linear work - merge function runs in O(n) each, over logn levels)
#include <iostream>
using namespace std;

#define INVALID_VALUE -99999

class Node{
    public:
        int key;
        Node *next;
        Node(int);
};

Node::Node(int key){
    this->key = key;
    this->next = NULL;
}

class Queue{
    public:
        Queue();
        ~Queue();
        bool empty();
        void enqueue(int);
        int dequeue();
        int peek();
        void print();
        Node *head;
};

Queue::Queue(){
    this->head = NULL;
}

Queue::~Queue(){
    if(!empty()){
        while(this->head != NULL){
            Node *temp = this->head;
            this->head = this->head->next;
            delete temp;
        }
    }
}

bool Queue::empty(){
    bool is_empty = false;
    if(this->head == NULL){
        is_empty = true;
    }
    return is_empty;
}

void Queue::enqueue(int key){
    if(this->head == NULL){
        Node *new_node = new Node(key);
        this->head = new_node;
    }
    else{
        Node *curr = this->head;
        while(curr->next != NULL){
            curr = curr->next;
        }
        Node *new_node = new Node(key);
        curr->next = new_node;
    }
}

int Queue::dequeue(){
    int key = INVALID_VALUE;
    if(!empty()){
        Node *temp = this->head;
        key = temp->key;
        this->head = this->head->next;
        delete temp;
        temp = NULL;
    }
    return key;
}

int Queue::peek(){
    int key = INVALID_VALUE;
    if(!empty()){
        key = this->head->key;
    }
    return key;
}

void Queue::print(){
    if(!empty()){
        Node *curr = this->head;
        while(curr != NULL){
            cout << curr->key << endl;
            curr = curr->next;
        }
    }
}

void merge(int s[], int low, int middle, int high){

    Queue *buffer1 = new Queue();
    Queue *buffer2 = new Queue();

    for(int i = low; i <= middle; i ++){
        buffer1->enqueue(s[i]);
    }
    for(int i = middle + 1; i < high; i ++){
        buffer2->enqueue(s[i]);
    }

    int i = low;
    while(!(buffer1->empty() || buffer2->empty())){
        if(buffer1->peek() <= buffer2->peek()){
            s[i ++] = buffer1->dequeue();
        }
        else{
            s[i ++] = buffer2->dequeue();
        }
    }

    while(!buffer1->empty()){
        s[i ++] = buffer1->dequeue();
    }
    while(!buffer2->empty()){
        s[i ++] = buffer2->dequeue();
    }

    delete buffer2;
    delete buffer1;
}

void mergesort(int s[], int low, int high){

    int middle;

    if(low < high){
        middle = (low + high)/2;
        mergesort(s, low, middle);
        mergesort(s, middle + 1, high);
        merge(s, low, middle, high);
    }
}

int main(){
    int length = 6;
    int s[] = {4, 8, 2, 10, 1, 1};
    mergesort(s, 0, length);
    for(int i = 0; i < length; i ++){
        cout << s[i] << " ";
    }
    return 0;
}
