#pragma once
namespace DataStructures {

	//Contaimner for data in a the class Queue.
	class Node {
		int data;
		Node* nextNode;

	};

	//Custom queue class.
	class Queue {

		Node* head, tail;

	};

}