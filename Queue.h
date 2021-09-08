#pragma once

#include "Node.h"

class Queue
{

private:
	Node* rear;
	int size;
public:
	Node* front;
	Queue()
	{
		front = NULL;
		rear = NULL;
		size = 0;
	}

	void enqueue(int data)
	{
		Node* new_node = new Node;
		new_node->data = data;
		new_node->next = NULL;
		if (rear)
			rear->next = new_node;
		else
			front = new_node;
		rear = new_node;
		size++;
	}
	int dequeue()
	{
		if (rear == NULL)
		{
			cout << "No Element Exists in the Queue to return" << endl;
			exit(0);
		}
		Node* temp = front;
		int data = front->data;
		front = front->next;
		if (front == NULL)
			rear = NULL;
		delete temp;
		size--;
		return data;
	}



	void clear()
	{
		if (front != NULL)
		{
			Node* temp = front->next;
			while (temp)
			{
				delete front;
				front = temp;
				temp = temp->next;
			}
		}
		rear = NULL;
		front = NULL;
		size = 0;
	}
	void Print()
	{
		cout << "Queue: ";
		for (Node* a = front; a != NULL; a = a->next)
		{
			cout << a->data;
		}
		cout << endl;
	}

	bool isEmpty()
	{
		if (size == 0)
			return true;
		return false;
	}




	~Queue()
	{
		if (front != NULL)
		{
			Node* temp = front->next;
			while (temp)
			{
				delete front;
				front = temp;
				temp = temp->next;
			}
		}
	}



};

