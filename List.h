#pragma once
#include "Node.h"



class List
{
private:
	Node* tail;
	int size = 0;
public:
	Node* head;
	List()
	{
		head = NULL;
		tail = NULL;
		size = 0;

	}///end
	int iota(string A)
	{
		int x;
		stringstream y(A);
		y >> x;

		return x;

	}///func end



	void PushBack(string sour, string dest, string date, int price, string air, string FlyT, string LandT) {

		size++;
		float ft = 0.0;
		float lt = 0.0;

		Node* temp = new Node();
		int x;
		string T;

		int k = 0;
		// FOR DAY,MONTH AND YEAR INTO INTEGERS
		for (k = 0; k < date.length(); k++) {
			if (date[k] == '/')
				break;
			T += date[k];
		}
		k++;
		x = iota(T);
		temp->day = x;
		T = "";

		for (k; k < date.length(); k++) {
			if (date[k] == '/')
				break;
			T += date[k];
		}
		k++;
		x = iota(T);
		temp->month = x;
		T = "";

		for (k; k < date.length(); k++) {
			if (date[k] == '/')
				break;
			T += date[k];
		}
		k++;
		x = iota(T);
		temp->year = x;

		T = "";

		//////////////////////FOR FLY TIME STORAGE INTO HOURS AND MINUTES//////////////////////
		for (int i = 0; i < FlyT.length(); i++)
		{
			if (FlyT[i] == ':')
				break;

			T += FlyT[i];
		}
		x = iota(T);
		temp->FlyTimeH = x;
		ft += x;

		T = FlyT;

		for (x = 0; x < FlyT.length(); x++)
		{
			if (FlyT[x] == ':')
				break;
		}
		T.erase(0, x+1);
		x = iota(T);
		temp->FlyTimeM = x;
		if (x == 0)
			ft += 0;
		else
			ft += (60 / x);
		///////////////////////////////////////////////////////////////////////////////////////
		T = "";

		//////////////////////FOR LAND TIME STORAGE INTO HOURS AND MINUTES//////////////////////
		for (int i = 0; i < LandT.length(); i++)
		{
			if (LandT[i] == ':')
				break;

			T += LandT[i];
		}
		x = iota(T);
		temp->LandTimeH = x;
		lt += x;

		T = LandT;

		for (x = 0; x < LandT.length(); x++)
		{
			if (LandT[x] == ':')
				break;
		}
		T.erase(0, x+1);
		x = iota(T);
		temp->LandTimeM = x;
		if (x == 0)
			lt += 0;
		else
			lt += (60 / x);

		if (lt > ft) {
			temp->timeofFlight = lt - ft;
		}
		else {// ft>lt
			int counter = 0;
			int tft = ft;
			bool check = true;

			for (tft; check == true; tft++) {
				if (tft % 24 == 0)
					tft = 0;
				if (tft == int(lt))
					check = false;
				counter++;
			}
			temp->timeofFlight = counter - 1;

		}
		///////////////////////////////////////////////////////////////////////////////////////

		
		temp->Source = sour;
		temp->Destination = dest;
		temp->DOT = date;
		temp->TicketPrice = price;
		temp->Airline = air;

		temp->next = NULL;


		if (head == NULL) {

			head = temp;
			tail = temp;
			//head->data = n;
			temp->previous = NULL;
		}
		else {
			temp->previous = tail;
			tail->next = temp;
			tail = temp;
		}

	}///func end

	////////////////////FOR STORING THE SOURCE////////////////////////////////////
	void PushBack(string sour)
	{

		size++;

		Node* temp = new Node();

		temp->Source = sour;
		temp->next = NULL;

		if (head == NULL) {

			head = temp;
			tail = temp;
			//head->data = n;
			temp->previous = NULL;
		}

		else {
			temp->previous = tail;
			tail->next = temp;
			tail = temp;

		}

	}///func end














	Node*& getHead()
	{
		return head;

	}


	void PushFront(string sour, string dest, string date, int price, string air, string FlyT, string LandT) {

		size++;

		Node* temp = new Node();
		int x;
		string T;


		//////////////////////FOR FLY TIME STORAGE INTO HOURS AND MINUTES//////////////////////
		for (int i = 0; i < FlyT.length(); i++)
		{
			if (FlyT[i] == ':')
				break;

			T += FlyT[i];
		}
		x = iota(T);
		temp->FlyTimeH = x;

		T = FlyT;

		for (x = 0; x < FlyT.length(); x++)
		{
			if (FlyT[x] == ':')
				break;
		}
		T.erase(0, x);
		x = iota(T);
		temp->FlyTimeM = x;
		///////////////////////////////////////////////////////////////////////////////////////
		T = "";

		//////////////////////FOR LAND TIME STORAGE INTO HOURS AND MINUTES//////////////////////
		for (int i = 0; i < LandT.length(); i++)
		{
			if (LandT[i] == ':')
				break;

			T += LandT[i];
		}
		x = iota(T);
		temp->LandTimeH = x;

		T = LandT;

		for (x = 0; x < LandT.length(); x++)
		{
			if (LandT[x] == ':')
				break;
		}
		T.erase(0, x);
		x = iota(T);
		temp->LandTimeM = x;
		///////////////////////////////////////////////////////////////////////////////////////


		temp->Source = sour;
		temp->Destination = dest;
		temp->DOT = date;
		temp->TicketPrice = price;
		temp->Airline = air;

		temp->next = NULL;

		if (head == NULL) {

			head = temp;
			tail = temp;
			//head->data = n;
			temp->previous = NULL;
		}

		else {
			temp->next = head;
			tail->previous = NULL;
			head = temp;

		}

	}///func end


	void PopBack() {

		size--;

		tail = tail->previous;
		delete tail->next;
		tail->next = NULL;



		/*	size--;

		Node* i = head;
		for (; i->next != tail; i = i->next) {};
		Node* temp = tail;

		i->next = NULL;
		tail = i;

		delete temp;*/



	}

	int getSize()
	{
		return size;
	}


	void PopFront() {
		size--;

		head = head->next;
		delete head->previous;
		head->previous = NULL;

	}


	int Remove(int n)
	{
		/*Node* temp = new Node();
		bool check = false;
		for (Node*i = head;i->next!=NULL;i = i->next)
		{
			check = false;

			if (i->data == n)
			{
				check = true;
				temp->next = i;
				i->previous->next = i->next;
				i->next->previous = i->previous;
				temp= i;

			}
		}*/

		Node* i = head;
		i->previous = NULL;
		int index = 0;
		while (i && i->data != n)
		{
			i = i->next;
			index++;
		}

		if (i)
		{
			if (i->previous)
			{
				i->previous->next = i->next;
				delete i;
			}
			else
			{
				head = i->next;
				delete i;
			}
			return index;

		}


		return 0;
	}//func end






	void RemoveDup() {
		Node* temp = new Node();
		Node* a;
		Node* b;
		for (a = head; a != NULL; a = a->next) {
			b = a;
			while (b->next != NULL)
			{
				if (a->data == b->next->data) {

					temp->next = b->next;
					b->next = b->next->next;
					delete temp;

				}////if end
				else
				{
					b = b->next;
				}   //else end 
			}///while
		}//for end
	}



	void MergeBack(List b) {


		this->tail->next = b.head;
		b.head->previous = tail;
		tail = b.tail;



	}////func end



	bool Insert(int n, int ind) {

		////////////////FINDING INDEX////////////////////
		if (ind <= 0)
			return false;

		int index = 1;
		Node* i = head;

		while (i && index < ind)
		{
			i = i->next;
			index++;
		}

		if (index > 1 && i == NULL)
		{
			return false;
		}
		////////////////////////////////////////////////

		Node* temp = new Node;
		temp->data = n;

		if (index == 1)
		{
			temp->next = head;
			head = temp;
		}

		else
		{
			temp->next = i->next;
			temp->previous = i;
			i->next = temp;
			temp->next->previous = temp;
		}
		return true;
	}///func end

	bool Replace(int n, int ind)
	{
		////////////////FINDING INDEX////////////////////
		if (ind <= 0)
			return false;

		int index = 1;
		Node* i = head;

		while (i && index < ind)
		{
			i = i->next;
			index++;
		}

		if (index > 1 && i == NULL)
		{
			return false;
		}
		////////////////////////////////////////////////

		i->next->data = n;


	}/////func end



	bool duplicate()
	{
		Node* a;
		Node* b;
		for (a = head; a != NULL; a = a->next) {
			b = a;
			while (b->next != NULL)
			{
				if (a->data == b->next->data) {

					return true;

				}////if end
				else
				{
					b = b->next;
				}   //else end 
			}///while
		}//for end


		return false;


	}///func end



	bool isEmpty() {
		if (size == 0)
			return true;

		return false;
	}


	void ClearList() {

		Node* i = head;
		Node* j = NULL;

		while (i != NULL)
		{
			j = i->next;
			delete i;
			i = j;
		}

	}///func end




	void sort()
	{


		Node* k = head;

		int temp;

		//cout << size;

		for (int i = 0; i < size - 1; i++)
		{

			for (int j = 0; j < size - i - 1; j++, k = k->next)
			{
				//cout << "yes";
				if (k->data > k->next->data)
				{
					temp = k->data;
					k->data = k->next->data;
					k->next->data = temp;
				}
			}
			k = head;

		}

	}///func end




	void Display() {

		Node* i;
		for (i = head->next; i != NULL; i = i->next)
		{
			cout << i->Source << ">>" << i->Destination << " " << i->DOT << " " << i->FlyTimeH << ":" << i->FlyTimeM << " " << i->LandTimeH << ":" << i->LandTimeM << "  FlightTime>>"<<i->timeofFlight<<" " << i->Airline <<" Price: "<< i->TicketPrice << endl;
		}
		cout << endl;

	}

	~List() {

		for (Node* i = head; i->next != NULL;)
		{

			Node* temp = i;
			i = i->next;
			delete temp;
			//exit(1);
		}

	}

	////////////////Haroon part


};
