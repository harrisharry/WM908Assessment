#pragma once
#include <iostream>
#include <Memory>
namespace DataStructures {

	//Custom stack class for ints for now.
	template<typename T>
	class Stack {

	private:
		std::unique_ptr<T[]> arrayStack;
		//T* arrayStack; //Default size for now.
		unsigned int topIndex = 0; //Stores how much data we have. 0 means there is nothing in the stack, and there for empty.

		
	public:


		//Constructor.
		Stack(unsigned int size = 10) {
			//Initialise the array and store it in the Unique ptr.
			arrayStack = std::make_unique<T[]>(size);

		}


		bool Empty() {
			if (topIndex == 0) {
				std::cout << "The stack is empty.\n";
				return true;
			}

			return false;
				
		}
		//Class manipulators.
		void Push(T value) {
			if (topIndex >= 12) { //Check if there is overflow in the array.
				std::cout << "The stack array is full, can't add anymore values\n";
				return; //Cant add anymore values.
			}
			arrayStack[topIndex] = value; //Store the value.
			topIndex++; //Increment topIndex to make sure that the next value is added in the correct place.
		}
		//Returns the value at the front of the queue / at the head.
		T Pop() {

			if (Empty()) {
				
				return 0;
			}
			topIndex--; //Move the top value in the stack back.
			/*Return the value at this current position, since the next in queue is topIndex - 1,which has already been done in 
			the line above and that index in the array is now ready to be used for the next Push.*/
			return arrayStack[topIndex];
		}
		int Length() {
			/*Whatever value topIndex is directly corrosponds to the size of the active stack.
			Because 0 means it is empty, and any number greater than 0 means that is the number of elements within the stack currently*/
			return topIndex;
		}
		void DebugStack() {
			//Debug array.
			if (Empty())
				return;

			std::cout << "Value of topIndex is: " << topIndex << std::endl;

			for (int i = topIndex - 1; i >= 0; i-- ) { // topIndex - 1 becuase the index here is currently not actually in use.
				std::cout << "Value at index " << i << " is " << arrayStack[i] << std::endl;

			}
		}
	};

	template<typename T>
	class Queue
	{
	private:
		//T* arrayQueue;
		std::unique_ptr<T[]> arrayQueue;
		unsigned int arraySize = 0;
		unsigned int head = 0;
		unsigned int tail = 0;

		bool Full() {
			return tail == arraySize;
		}
	public:

		Queue(unsigned int size = 10) {
			//arrayQueue = new T[size];
			arrayQueue = std::make_unique<T[]>(size);
			arraySize = size;
		}

		bool Empty() {
			return tail != 0; //If the tail is pointing at 0, then nothing has been enqueued.
		}
		int Size() {
			return tail; //tail value will always indicate the size of the queue.
		}
		void Enqueue(T value) {
			if (Full())
			{
				std::cout << "Queue has reached max size.\n";
				return;
			}
			arrayQueue[tail] = value; //Assign the queue at the tail.
			tail++; //Increment tail so it is pointing at the next available index. 
		}
		T Dequeue() {

			T returned = arrayQueue[head];
			head++;

			return returned;
			
		}

		void DebugQueue() {

			for (int i = head; i < tail; i++) {

				std::cout << "The value at position " << i << " is " << arrayQueue[i] << std::endl;
			}
		}
	};

	template<typename T>
	struct Node {
	public:
		T data; //Storest the data this node contains.
		std::unique_ptr<Node<T>> next = nullptr; //Reference to the next item node in the list. If this is null, this is the last item in the list. For now.
		Node<T>* prev = nullptr; //Referrence to the previous item node in the list. If this is null, this is the first item in the list.

		Node(T dataToStore) {
			data = dataToStore;
		}
	};
	
	//https://www.google.com/search?sca_esv=a1669c2d6fe4ecbb&rlz=1C1HKFL_enGB1235GB1235&sxsrf=AKL5yDhA1WigKU4jEcA4_L25H7Ag6hO4vA:1793288869769&udm=vids&fbs=ACAhTvwdifjn2dKXmjtOfBxVFl_k7xB_bJXhWBZp-REbIUHBWN-snoH3FlZylufB_FE1AR1adZpcKn9ihLVbHvMslHJlW0lte04An72fAl3Q1xEmNc9CZfDbOROifjy1E5_AGkz6XoL21U3hzSsg2DCiQCUmFVajuP5H5ucPJjUhKnSPwMuBareePdKAfQxf1oCbBVVU7R4hTvflYG3vzgwGXciqUb_8lA&q=custom+iterators+explained+c~%2B%2B&sa=X&ved=2ahUKEwiYhr_Qyd-XAxUcU0EAHQzwLOEQtKgLegQIFxAB&biw=1163&bih=605&dpr=1.65#fpstate=ive&vld=cid:46552808,vid:F9eDv-YIOQ0,st:0
	
	template<typename List>
	class ListIterator {


	private:
		using ValueType = typename List::ValueType;
		using PointerType = ValueType*;
		using ReferenceType = ValueType&;


		PointerType current; //Currently pointing to.


	public:

 		ListIterator(PointerType ptr) {
			current = ptr;
		}

		ListIterator  operator ++() {
			if (current->next == nullptr){
				this->current = nullptr; //Source of infinite loop bug. Need to change this.current to be null, and then return this. Before was returning a nullptr copy version. Resulting in iterator in the loop to never be null.
				return *this;
			}
				
			
			this->current = current->next.get();
			return *this;
			
		}

		ListIterator  operator ++(int) {

			ListIterator iterator = *this; //Create a copy before any changes have been made to return.
			++(*this); //Make the changes.
			return iterator; //Return the copy.


		}
		ListIterator operator--() {
			if (current->prev) //Check if null
				return *this;
			this->current = current->prev;

			return *this;
		}
		ListIterator operator--(int){
			ListIterator iterator = *this; //Create a copy before any changes have been made to return.
			--(*this);
			return iterator;
		}
		PointerType operator->() {
			return this->current;
		}
		bool operator==(const ListIterator& other) const {
			return this->current == other.current;
		}
		bool operator!=(const ListIterator& other) const {
			return !(this->current == other.current);
		}
		ReferenceType operator*() {
			return *current;
		}
	};

	template<typename T>
	class List {
		
	private:
		std::unique_ptr<Node<T>> head; //First element in the list. if head == nill, list is empty.
		Node<T>* tail = nullptr;
		int size = 0; //How many elements have been added.
		

	public:
		using ValueType = Node<T>;
		using Iterator = ListIterator<List<T>>;
		List() {
		}
		//An iterator that point at the beginning of the list.
		Iterator Begin() {
			return Iterator(head.get());
		}
		//An iterator that points to the end of the list
		Iterator End() {
			return Iterator(nullptr); //Iterator where it points to null, meaning there is no current anymore.
		}
		//O(n) because at worst case, it will need to treverse all n elements.
		Node<T>* Search(T keyValue) {
			Node<T>* currentNode = head.get(); //Set this to the head, the first element in the list.
			while (currentNode != nullptr && currentNode->data != keyValue) //While the node isnt null, and the value of that node is not what we are looking for.
			{
				//Move to the next node pointed to by the current node, and assign it to itself. This way it moves up along the list.
				currentNode = currentNode->next.get();
			}
			//Once the while true breaks, it will mean that the keyValue requested has been found. So we returnb that node.
			return currentNode;
		}
		bool Empty() {
			return head == nullptr;
		}
		//O(1), because it doesn't matter how many elements we have, it will always be appended at the head.
		void Add(T value) {

			////Next and prev are already null because of the constructor.
			
			if (Empty()) { //Checks if the list is empty.
				head = std::make_unique<Node<T>>(Node<T>(value));
				
				tail = head.get(); //The last element is also the first element, as now the list has one singular element.
			}
			else { //If the list is not empty.


				tail->next = std::make_unique<Node<T>>(Node<T>(value)); //Get the last element in the list, and assign its "next" variable to the new node.
				Node<T>* temp = tail; //Get a pointer to the now previous node to the one we have created.
				tail = tail->next.get(); //The new tail has now moved, tail-> is already pointing to the newly created node, so set tail to point to that now new node
				tail->prev = temp; //Now set the new node's previous pointer to be that of the temp value(Stored before hand so we could do this.)
				std::cout << tail->prev->data;
			}
			
			size++; //Increment size at the end of the function, as we have now increased the total size of this list.
		}
		bool Remove(T valueToRemove) {

			if (Empty())
			{
				std::cout << "List is empty when trying to remove an element\n";
				return false;
			}
			Node<T>* found = Search(valueToRemove);
			if (found == head.get()) { //If the node found is the head, we need to reassign the new head.
				
				if (found->next == nullptr) { //If this is the only element in list just release the data.
					head.release();
				}
				else {
					head = std::move(found->next); //Move control of the foundNode->next pointer to the header, as the header should always be in control of the very first Node.
					head.get()->prev = nullptr; //Set the pointer of the newly made head Node to be null, because it is now the first element.
				}
			}
			else if (found == tail) { //If the node found is the tail, we need to move the tail to be the previous node.
				tail = found->prev; //Set the tail to be the previous node.
				tail->next = nullptr;
			}
			else { //Need to remove the node, and attach the previous node to the next node of the node that is found.
			
				Node<T>* prev = found->prev; //Record what the prev pointer is pointing to the previous Node.
				Node<T>* next = found->next.get(); //Record what the next pointer is pointing to the next Node.



				prev->next = std::move(found->next); //Move ownership of found->next to prev->next, as this now needs to point to the next node instead of the node we are deleting pointing to the next one.
				next->prev = prev; //Get the next node, and set the node it is pointing to it previously to be now the old node was previously pointing to.
			}

			size--;
			return true;
		}
		int Size() {
			return size;
		}
		Node<T>* Last() {
			return tail;
		}
		Node<T>* First(){
			return head.get();
		}
		void DebugList() {

			//Iterate through the list.

			Node<T>* current = head.get();
			std::cout << "Number of elements in the list is " << size << std::endl;
			for (int i = 0; i < size; i++) {

				std::cout << "The element at position " << i << " is " << current->data << std::endl;
				current = current->next.get(); //Reassign current to the node that is stored in the next pointer of the current node.
			}

		}
	};
}