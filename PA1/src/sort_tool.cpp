// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
//  Modify     [2023/9/12 Ming-Bang Fan]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>
#define ll long long 
// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    for(int j = 1; j <= data.size() - 1; j++){
        int key = data[j];
        int i = j - 1;
        while(i >= 0 && data[i] > key){
            data[i + 1] = data[i];
            i--;
        }
        data[i + 1] = key;
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data, int f){
    QuickSortSubVector(data, 0, data.size() - 1, f);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high, const int flag) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    // flag == 0 -> normal QS
    // flag == 1 -> randomized QS
    if (low < high) {
        int q;
        if(flag == 0){
            q = Partition(data, low, high);
        }
        else{
            q = RandomizedPartition(data, low, high);
        }
        QuickSortSubVector(data, low, q - 1, flag);
        QuickSortSubVector(data, q + 1, high, flag);
    }
}
int SortTool::RandomizedPartition(vector<int>& data, int low, int high) {
    // Function : RQS's Partition the vector 
    // TODO : Please complete the function
    int i = low + rand() % (high - low + 1);
    swap(data[i], data[high]);
    return Partition(data, low, high);
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    int x = data[high];
    int i = low - 1;
    for(int j = low; j <= high - 1; j++){
        if(data[j] <= x){
            i++;
            swap(data[i], data[j]);
        }
    }
    swap(data[i + 1], data[high]);
    return i + 1;
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data) {
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if (low < high) {
        int middle = (low + high) / 2;
        MergeSortSubVector(data, low, middle); 
        MergeSortSubVector(data, middle+1, high); 
        Merge(data, low, middle, high);
    }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int n_l = middle - low + 1;
    int n_r = high - middle;
    vector< int > L( n_l );
    vector< int > R( n_r );

    for(int i = 0; i <= n_l - 1; i++){
        L[i] = data[low + i];
    }
    for(int j = 0; j <= n_r - 1; j++){
        R[j] = data[middle + j + 1];
    }
    int i,j = 0;
    while(i < n_l && j < n_r){
        if(L[i] <= R[j]){
            data[low] = L[i];
            i++;
        }
        else{
            data[low] = R[j];
            j++;
        }
        low++;
    }
    while(i < n_l){
        data[low] = L[i];
        i++;
        low++;
    }
    while(j < n_r){
        data[low] = R[j];
        j++;
        low++;
    }
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int left = 2 * root + 1;
    int right = 2 * root + 2;
    int largest;
    if (left <= heapSize - 1 && data[left] > data[root]) {
        largest = left;
    }
    else {
        largest = root;
    }
    if (right <= heapSize - 1 && data[right] > data[largest]) {
        largest = right;
    }
    if (largest != root) {
        swap(data[root], data[largest]);
        MaxHeapify(data, largest);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for(int i = data.size() / 2 - 1; i >= 0; i--) {
        MaxHeapify(data, i);
    }
}
