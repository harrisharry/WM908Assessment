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
			//Initialise array ints with nullptr.
			arrayStack = std::make_unique<T[]>(size);
			//arrayStack = new T[size];
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
		T* arrayQueue;
		unsigned int arraySize = 0;
		unsigned int head = 0;
		unsigned int tail = 0;

		bool Full() {
			return tail == arraySize;
		}
	public:

		Queue(unsigned int size = 10) {
			arrayQueue = new T[size];
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
	class List {
		
		

	};
}