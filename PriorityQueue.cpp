#include "PriorityQueue.hpp"
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;


typedef PriorityQueue::DataType DataType;
 // Constructor initializes heap_ to an array of size "capacity + 1", so that
  // there are at most "capacity" elements in the heap.
PriorityQueue::PriorityQueue(unsigned int capacity){
	size_ = 0;
	capacity_ = capacity;
	heap_ = new DataType[capacity_+1];
}

PriorityQueue::~PriorityQueue(){
	delete [] heap_;
	heap_ = NULL;
}

// insert
bool PriorityQueue::enqueue(DataType val){
	if(full()) return 0;
	
	heap_[size_+1] = val;
	size_++;
	
	if(size_==1) return 1;

	int index=size_;
	while(index > 1){
		if(heap_[(int)floor(index/2)] < heap_[index]){
			swap(heap_[(int)floor(index/2)], heap_[index]); 
		}
		index = floor(index/2);
	}
	return 1;
}

bool PriorityQueue::dequeue(){
	if(empty()) return 0;
	
	if(size_ == 1){ 
		size_--;
		return 1;
	}

	heap_[0] = heap_[size_];
	size_--;

	int index=1, temp =0;
		while(index < size_){
			
		if(heap_[index*2] > heap_[index*2+1])
			temp = index*2;
		else
			temp = index*2 + 1;
		
		if(heap_[temp] > heap_[index])
			swap(heap_[temp], heap_[index]);
		index = temp;
	}
	return 1;
}

DataType PriorityQueue::max() const{
	return heap_[1];
}

bool PriorityQueue::empty() const{
	return (size_ == 0);
}

bool PriorityQueue::full() const{
	return (size_ == capacity_);
}

unsigned int PriorityQueue::size() const{
	return size_;
}

void PriorityQueue::print() const{
	for(int i=1; i<=size_; i++){
		cout << heap_[i] << " ";
	}
}