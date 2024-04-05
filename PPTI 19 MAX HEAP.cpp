#include<stdio.h>
#include<limits.h> //INT_MAX INT_MIN

int parent(int pos){
	return (pos - 1) / 2;
}

int leftChild(int pos){
	return (pos * 2) + 1;
}

int rightChild(int pos) {
	return (pos * 2) + 2;
}

int heap[100] = {INT_MIN};
int size;

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}


void insertHeap(int value){
	heap[size] = value;
	int pos = size;
	size++;
	
	while(heap[parent(pos)] < heap[pos]){
		printf("Swapping %d with %d\n", 
				heap[parent(pos)], 
				heap[pos]);
		swap(&heap[pos], &heap[parent(pos)]);
		pos = parent(pos);
	}
	printf("Successfully inserting %d\n\n", value);
}

void printArray(){
	for(int i = 0; i<size; i++){
		printf("%d ", heap[i]);
	}
	printf("\n");
}

void heapify(int pos){
	
	int leftValue;
	if(leftChild(pos) > size){
		leftValue = INT_MIN;
	} else {
		leftValue = heap[leftChild(pos)];
	}
	
	int rightValue;
	if(rightChild(pos) > size) {
		rightValue = INT_MIN;
	} else {
		rightValue = heap[rightChild(pos)];
	}
	
	if(heap[pos] < rightValue || heap[pos] < leftValue) {
		printf("Swapping....\n");
		
		if (leftValue > rightValue) {
			swap(&heap[pos], &heap[leftChild(pos)]);
			heapify(leftChild(pos));
		} else {
			swap(&heap[pos], &heap[rightChild(pos)]);
			heapify(rightChild(pos));
		}
	}
}

int extractMin(){
	if (size == 0) {
		printf("Heap is Empty! :D");
		return 0;
	}
	int minValue = heap[0];
	
	heap[0] = heap[size-1];
	size--;
	
	heapify(0);
	
	return minValue;
}

int main(){
	insertHeap(10);
	insertHeap(7);
	insertHeap(1);
	insertHeap(5);
	insertHeap(16);
	insertHeap(2);
	insertHeap(14);
	printArray();
	
	while(true) {
		printf("Extracting ........ %d\n", extractMin());
		if(size == 0) {
			break;
		}
	}
	return 0;
}


