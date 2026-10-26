#pragma once
#include <iostream>
namespace DataStructures {

	//Custom stack class for ints for now.
	class StackInt {

	private:
	
		int arrayStack[12]; //Default size for now.
		unsigned int topIndex = 0; //Stores how much data we have. 0 means there is nothing in the stack, and there for empty.

		
	public:


		//Constructor.
		StackInt() {
			//Initialise array ints with nullptr.
			for (int i = 0; i < 12; i++) {
				arrayStack[i] = 0;
			}
		}


		bool Empty() {
			if (topIndex == 0) {
				std::cout << "The stack is empty.\n";
				return true;
			}

			return false;
				
		}
		//Class manipulators.
		void Push(int value) {
			if (topIndex >= 12) { //Check if there is overflow in the array.
				std::cout << "The stack array is full, can't add anymore values\n";
				return; //Cant add anymore values.
			}
			arrayStack[topIndex] = value; //Store the value.
			topIndex++; //Increment topIndex to make sure that the next value is added in the correct place.
		}
		//Returns the value at the front of the queue / at the head.
		int Pop() {

			int dataValIndex = topIndex; //Get the index of the data we are at before we change values and return.
			topIndex--; //Move the top value in the stack back.

			return arrayStack[dataValIndex]; //Return the value from the original topIndex in the array.
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


}