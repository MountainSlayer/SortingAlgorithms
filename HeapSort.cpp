//Purpose: Reviewing heap data structure and heapsort
#include <iostream>
using namespace std;

#define MAX 100

//Disadvantage of using an array data structure for a binary tree is that space
//is wasted if the tree is sparse. It's wasteful when dealing with different
//tree topologies and it's more difficult to move subtrees around
class Heap{
    int items[MAX + 1];
    int n;
    int get_parent(int);
    int get_left_child(int);
    int get_right_child(int);
    void bubble_up(int);
    void bubble_down(int);
    void make_heap(int [], int);
    public:
        Heap();
        void insert(int);
        int extract_min();
        void heapsort(int [], int);
        void print();
};

Heap::Heap(){
    for(int i = 0; i <= MAX; i ++){
        items[i] = 0;
    }
    items[0] = -1;
    this->n = 0;
}

int Heap::get_parent(int k){
    return (int)(k / 2);
}

int Heap::get_left_child(int k){
    return 2*k;
}

int Heap::get_right_child(int k){
    return 2*k + 1;
}

void Heap::bubble_up(int pos){
    int k = this->items[pos];
    if(k != -1){ //if have not hit root yet
        int parent_ind = get_parent(pos);
        int parent = this->items[parent_ind];
        if(k < parent){
            //swap k with parent
            this->items[parent_ind] = k;
            this->items[pos] = parent;
            bubble_up(parent_ind);
        }
    }
}

//Heap is always a complete tree (and also a balanced tree)
//so worst case of insert is logn (the height of the tree)
void Heap::insert(int k){
    this->n ++;
    this->items[this->n] = k; //add new item to rightmost leaf of heap
    bubble_up(this->n);
}

void Heap::bubble_down(int pos){
    int k = this->items[pos];
    int min_child_pos;
    int left_pos = get_left_child(pos);
    int right_pos = get_right_child(pos);
    if(left_pos <= this->n || right_pos <= this->n){
        if(left_pos <= this->n && right_pos <= this->n){
            int left_val = this->items[left_pos];
            int right_val = this->items[right_pos];
            if(left_val < right_val){
                min_child_pos = left_pos;
            }
            else{
                min_child_pos = right_pos;
            }
        }
        else if(left_pos <= this->n){
            min_child_pos = left_pos;
        }
        else if(right_pos <= this->n){
            min_child_pos = right_pos;
        }
        if(k > this->items[min_child_pos]){
            this->items[pos] = this->items[min_child_pos];
            this->items[min_child_pos] = k;
            bubble_down(min_child_pos);
        }
    }
}

int Heap::extract_min(){
    int min = -1;
    if(this->n > 0){
        min = this->items[1];
        int rightmost = this->items[this->n];
        this->items[1] = rightmost;
        this->n --;
        bubble_down(1);
    }
    return min;
}

void Heap::make_heap(int array[], int length){
    for(int i = 0; i < length; i ++){
        insert(array[i]);
    }
}

//heapsort is O(nlogn) worst case time complexity
//heapsort is just repeatedly calling extract_min
void Heap::heapsort(int array[], int length){
    make_heap(array, length);
    for(int i = 0; i < length; i ++){
        array[i] = extract_min();
    }
}

void Heap::print(){
    for(int i = 0; i <= this->n; i ++){
        cout << this->items[i] << endl;
    }
}

int main(){
    Heap *h = new Heap();
    int array[] = {5, 4, 1, 2, 7, 9, 1};
    int length = 7;
    h->heapsort(array, length);
    for(int i = 0; i < length; i ++){
        cout << array[i] << " ";
    }
    delete h;
    return 0;
}
