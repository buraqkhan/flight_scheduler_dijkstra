#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "List.h"
#include "vector.h"
#include "PriorityQueue.h"
using namespace std;

class Graph
{

private:
	List* array;
	vector<string> alpha; ///array for comparing names
	int S; //size of the List pointer i.e. array

public:
	Graph(const std::string& filename)
	{
		/////filling the graph with flight information

		ifstream input;

		string city; //for storing name of the city in the vector

		string temp;

		string temp2;

		bool check = false; // For checking if the city already exists in the vector
		bool check2 = false;

		input.open(filename);

		if (!input)
		{
			cout << "File not present\n";
			exit(1);
		}///First check to see if file is present


		while (!input.eof())
			//for(int y=0;y<2;y++)
		{
			temp = "";
			city = "";
			temp2 = "";
			check = false;
			check2 = false;

			getline(input, temp, '\n');

			int a;

			for (a = 0; temp[a] != ' '; a++)
				city += temp[a];

			a++;

			for (; temp[a] != ' '; a++)
				temp2 += temp[a];


			if (alpha.Is_Empty())
			{
				alpha.Push_Back(city);
				alpha.Push_Back(temp2);
			}//if


			else if (!alpha.Is_Empty())
			{
				for (int i = 0; i < alpha.Size(); i++)
				{
					if (alpha.getPointer()[i] == city)
					{
						check = true;
						break;
					}

				}//for

				if (!check)
					alpha.Push_Back(city);



				////////////////////////////////
				for (int i = 0; i < alpha.Size(); i++)
				{
					if (alpha.getPointer()[i] == temp2)
					{
						check2 = true;
						break;
					}

				}//for

				if (!check2)
					alpha.Push_Back(temp2);


			}//else if



		//cout << endl;

		}//while

		input.close();





		////////////////////////////////////////////////////////////////////////////////////////////////////////
		//alpha.Display();

		S = alpha.Size(); //equal to size of vector and the number of cities of the cities

		array = new List[alpha.Size()]; //Allocating Lists equal to the number of cities present in the file


		for (int i = 0; i < alpha.Size(); i++)
		{

			array[i].PushBack(alpha[i]);
		}




		FillNodes(filename);

		//alpha.Display(); //For checking
		cout << endl;

	}//func end

	void FillNodes(const std::string& filename)
	{
		ifstream in;
		string temp;
		string temp1 = "";
		string Sour, dest, date, FlyingT, LandingT, air;


		string price;

		int price2 = 0;

		int a = 0;

		in.open(filename);


		while (!in.eof())
			//for(int y=0;y<104;y++)
		{
			getline(in, temp, '\n');

			a = 0;

			//for source
			for (; temp[a] != ' '; a++)
			{
				temp1 += temp[a];
			}//for1
			a++;
			Sour = temp1;
			//cout << Sour<<endl;
			temp1 = "";


			//for dest
			for (; temp[a] != ' '; a++)
			{
				temp1 += temp[a];
			}//for1
			a++;
			dest = temp1;
			//cout << dest << endl;
			temp1 = "";

			//for date
			for (; temp[a] != ' '; a++)
			{
				temp1 += temp[a];
			}//for1
			a++;
			date = temp1;
			//cout << date << endl;
			temp1 = "";

			//for Flying Time
			for (; temp[a] != ' '; a++)
			{
				temp1 += temp[a];
			}//for1
			a++;
			FlyingT = temp1;
			//cout << FlyingT << endl;
			temp1 = "";

			//for Landing Time
			for (; temp[a] != ' '; a++)
			{
				temp1 += temp[a];
			}//for1
			a++;
			LandingT = temp1;
			//cout << LandingT << endl;
			temp1 = "";

			//for Airline
			for (; temp[a] != NULL; a++)
			{
				temp1 += temp[a];
			}//for1
			air = temp1;
			a++;

			int pos = 0;
			for (; pos < air.length(); pos++)
			{
				if (air[pos] == ' ')
					break;
			}

			air.erase(0, pos + 1);
			//cout << air << endl;

			string temp2 = temp1;

			temp1 = "";


			//FOR PRICE SEPARATION
			for (int i = 0; i < temp2.length(); i++)
			{
				if (temp2[i] == ' ')
					break;

				price += temp2[i];
			}

			stringstream o(price);
			o >> price2;
			//cout << price2<<endl;
			price = "";

			///ADDING CITIES TO ADJACENCY LIST
			for (int q = 0; q < S; q++)
			{
				if (Sour == array[q].getHead()->Source)
				{
					array[q].PushBack(Sour, dest, date, price2, air, FlyingT, LandingT);
					break;
				}
			}///for loop 				
		}//while

		in.close();
	}///func end

//===========================================================================================================================================//



	int checkCost(string maincity, string destcity) {
		Node* temp;
		int num = 1500000000;
		for (int i = 0; i < S; i++) {
			if (array[i].head->Source == maincity) {
				temp = array[i].head;
				while (temp != NULL) {
					if (temp->Destination == destcity) {
						if (num > temp->TicketPrice)
							num = temp->TicketPrice;
					}
					temp = temp->next;
				}
			}
		}
		return num;
	}

	int specCheckCost(string maincity, string destcity, string airline) {
		Node* temp;
		int num = 1500000000;
		for (int i = 0; i < S; i++) {
			if (array[i].head->Source == maincity) {
				temp = array[i].head;
				while (temp != NULL) {
					if (temp->Destination == destcity) {
						if (num > temp->TicketPrice&& airline == temp->Airline)
							num = temp->TicketPrice;
					}
					temp = temp->next;
				}
			}
		}
		return num;
	}

	int secondaryCheckCost(string maincity, string destcity, vector<int> min) {
		Node* temp;
		int num = 1500000000;
		for (int i = 0; i < S; i++) {
			if (array[i].head->Source == maincity) {
				temp = array[i].head;
				while (temp != NULL) {
					if (temp->Destination == destcity) {
						for (int j = 0; j < min.Size(); j++) {
							if (num > temp->TicketPrice&& temp->TicketPrice != min[j])
								num = temp->TicketPrice;
						}
					}
					temp = temp->next;
				}
			}
		}
		return num;
	}

	int specSecondaryCheckCost(string maincity, string destcity, vector<int> min, string airline) {
		Node* temp;
		int num = 1500000000;
		for (int i = 0; i < S; i++) {
			if (array[i].head->Source == maincity) {
				temp = array[i].head;
				while (temp != NULL) {
					if (temp->Destination == destcity) {
						for (int j = 0; j < min.Size(); j++) {
							if (num > temp->TicketPrice&& temp->TicketPrice != min[j] && airline == temp->Airline)
								num = temp->TicketPrice;
						}
					}
					temp = temp->next;
				}
			}
		}
		return num;
	}

	int checkTime(string maincity, string destcity) {
		Node* temp;
		int num = 1500000000;
		for (int i = 0; i < S; i++) {
			if (array[i].head->Source == maincity) {
				temp = array[i].head;
				while (temp != NULL) {
					if (temp->Destination == destcity) {
						if (num > temp->timeofFlight)
							num = temp->timeofFlight;
					}
					temp = temp->next;
				}
			}
		}
		return num;
	}

	int secondaryCheckTime(string maincity, string destcity, vector<int> min) {
		Node* temp;
		int num = 1500000000;
		for (int i = 0; i < S; i++) {
			if (array[i].head->Source == maincity) {
				temp = array[i].head;
				while (temp != NULL) {
					if (temp->Destination == destcity) {
						for (int j = 0; j < min.Size(); j++) {
							if (num > temp->timeofFlight&& temp->timeofFlight != min[j])
								num = temp->timeofFlight;
						}
					}
					temp = temp->next;
				}
			}
		}
		return num;
	}

	void showGraphStructure()
	{
		for (int i = 0; i < S; i++)
		{
			cout << "Source => " << alpha[i] << endl;
			array[i].Display();
			cout << endl;
		}
	}

	int CityToNumber(string place) {
		for (int i = 0; i < S; i++) {
			if (array[i].head->Source == place) {
				return i;
			}
		}
	}

	string NumberToCity(int n) {
		return array[n].head->Source;
	}

	string* cityVertices() {
		string* allCities = new string[S];
		for (int i = 0; i < S; i++) {
			allCities[i] = array[i].head->Source;
		}
		return allCities;
	}

	void CalculateCities(string currentCity, string* allCities, string* parent, int index) {
		vector<string> ConnectedCities;
		vector<string> MainCities;
		ConnectedCities.Push_Back(allCities[index]);
		ConnectedCities.Push_Back(parent[index]);
		int x = 0;
		for (; x < 100;) {
			if (parent[index] == currentCity) {
				break;
			}
			if (allCities[x] == parent[index]) {
				index = x;
				ConnectedCities.Push_Back(parent[index]);
				x = -1;
			}
			x++;
		}
		for (int i = ConnectedCities.Size() - 1; i >= 0; i--) {
			MainCities.Push_Back(ConnectedCities[i]);
		}
		MainCities.Display();
	}

	vector<string> transitCities(string currentCity, string* allCities, string* parent, int index) {
		vector<string> ConnectedCities;
		vector<string> MainCities;
		ConnectedCities.Push_Back(allCities[index]);
		ConnectedCities.Push_Back(parent[index]);
		int x = 0;
		for (; x < 100;) {
			if (parent[index] == currentCity) {
				break;
			}
			if (allCities[x] == parent[index]) {
				index = x;
				ConnectedCities.Push_Back(parent[index]);
				x = -1;
			}
			x++;
		}
		for (int i = ConnectedCities.Size() - 1; i >= 0; i--) {
			MainCities.Push_Back(ConnectedCities[i]);
		}

		return MainCities;
	}



	//===========> Cost Related Functions <===========//
//=================================================================================================================================================//

	//============ Normal Circumstance Dijkstra ============//

	int DijkstraForCost(Graph shortPath, string source, string destination) {
		PriorityQueue<int> costAdder;
		int* cost = new int[S];
		bool* check = new bool[S];
		string* parent = new string[S];
		for (int i = 0; i < S; i++) {
			cost[i] = 1000000000;
			check[i] = false;
		}

		int cityNo = shortPath.CityToNumber(source);
		cost[cityNo] = 0;
		parent[cityNo] = "\0";

		for (int q = 0; q < S; q++) {
			costAdder.insert(0, cost[q], cityVertices()[q]);
		}

		while (!costAdder.isEmpty()) {
			int u = shortPath.CityToNumber(costAdder.retCity());
			string main_city = costAdder.retCity();
			int p = costAdder.deleteMin();
			if (p == 1000000000) {
				break;
			}
			check[u] = true;
			for (int count = 0; count < S; count++) {
				string other_city = shortPath.NumberToCity(count);
				if (check[count] == false && shortPath.checkCost(main_city, other_city) + cost[u] < cost[count]) {
					if (shortPath.checkCost(main_city, other_city) != 0) {
						cost[count] = shortPath.checkCost(main_city, other_city) + cost[u];
						parent[count] = main_city;
						costAdder.insert(0, cost[count], shortPath.cityVertices()[count]);
					}
				}
			}
		}

		int final = shortPath.CityToNumber(destination);

		if (cost[final] == 1000000000 || cost[final] == 0) {
			cout << source << " To " << destination << " no flights available" << endl;
		}
		else {
			cout << source << " To " << destination << " ~ Cost: Rs " << cost[final] << " VIA ";
			CalculateCities(source, cityVertices(), parent, final);
			cout << endl;
		}

		return cost[final];
	}

	int DijkstraForCost(Graph shortPath, string source, string destination, vector<int>min) {
		PriorityQueue<int> costAdder;
		int* cost = new int[S];
		bool* check = new bool[S];
		string* parent = new string[S];
		for (int i = 0; i < S; i++) {
			cost[i] = 1000000000;
			check[i] = false;
		}

		int cityNo = shortPath.CityToNumber(source);
		cost[cityNo] = 0;
		parent[cityNo] = "\0";

		for (int q = 0; q < S; q++) {
			costAdder.insert(0, cost[q], cityVertices()[q]);
		}

		while (!costAdder.isEmpty()) {
			int u = shortPath.CityToNumber(costAdder.retCity());
			string main_city = costAdder.retCity();
			int p = costAdder.deleteMin();
			if (p == 1000000000) {
				break;
			}
			check[u] = true;
			for (int count = 0; count < S; count++) {
				string other_city = shortPath.NumberToCity(count);
				bool repeat = false;
				for (int i = 0; i < min.Size(); i++) {
					if (shortPath.secondaryCheckCost(main_city, other_city, min) + cost[u] == min[i]) {
						repeat = true;
						break;
					}
				}
				if (!repeat)
				{
					if (check[count] == false && shortPath.secondaryCheckCost(main_city, other_city, min) + cost[u] < cost[count]) {
						if (shortPath.checkCost(main_city, other_city) != 0) {
							cost[count] = shortPath.secondaryCheckCost(main_city, other_city, min) + cost[u];
							parent[count] = main_city;
							costAdder.insert(0, cost[count], shortPath.cityVertices()[count]);
						}
					}
				}
			}
		}

		int final = shortPath.CityToNumber(destination);

		if (cost[final] == 1000000000 || cost[final] == 0) {
			cout << "No other flghts to " << destination << " available." << endl;
		}
		else {
			cout << source << " To " << destination << " ~ Cost: Rs " << cost[final] << " VIA ";
			CalculateCities(source, cityVertices(), parent, final);
			cout << endl;
		}
		return cost[final];
	}

	// Dijkstra Implementation based on Cost efficiency //
	void mainDijkstraForCost(Graph shortPath, string source, string destination) { // not specifiaction airline / cost
		int num = 0;
		vector<int> min;
		num = DijkstraForCost(shortPath, source, destination);
		min.Push_Back(num);
		int i = 0;
		while (i < 10) {
			if (num != 1000000000) {
				num = DijkstraForCost(shortPath, source, destination, min);
				min.Push_Back(num);
			}
			else {
				break;
			}
			i++;
		}
	}



	//============ Specific Airline Dijkstra ===============//

	int specDijkstraForCost(Graph shortPath, string source, string destination, string airline) {
		PriorityQueue<int> costAdder;
		int* cost = new int[S];
		bool* check = new bool[S];
		string* parent = new string[S];
		for (int i = 0; i < S; i++) {
			cost[i] = 1000000000;
			check[i] = false;
		}

		int cityNo = shortPath.CityToNumber(source);
		cost[cityNo] = 0;
		parent[cityNo] = "\0";

		for (int q = 0; q < S; q++) {
			costAdder.insert(0, cost[q], cityVertices()[q]);
		}

		while (!costAdder.isEmpty()) {
			int u = shortPath.CityToNumber(costAdder.retCity());
			string main_city = costAdder.retCity();
			int p = costAdder.deleteMin();
			if (p == 1000000000) {
				break;
			}
			check[u] = true;
			for (int count = 0; count < S; count++) {
				string other_city = shortPath.NumberToCity(count);
				if (check[count] == false && shortPath.specCheckCost(main_city, other_city, airline) + cost[u] < cost[count]) {
					if (shortPath.specCheckCost(main_city, other_city, airline) != 0) {
						cost[count] = shortPath.specCheckCost(main_city, other_city, airline) + cost[u];
						parent[count] = main_city;
						costAdder.insert(0, cost[count], shortPath.cityVertices()[count]);
					}
				}
			}
		}

		int final = shortPath.CityToNumber(destination);

		if (cost[final] == 1000000000 || cost[final] == 0) {
			cout << source << " To " << destination << " no flights available" << endl;
		}
		else {
			cout << source << " To " << destination << " ~ Cost: Rs " << cost[final] << " VIA ";
			CalculateCities(source, cityVertices(), parent, final);
			cout << endl;
		}

		return cost[final];
	}

	int specDijkstraForCost(Graph shortPath, string source, string destination, vector<int>min, string airline) {
		PriorityQueue<int> costAdder;
		int* cost = new int[S];
		bool* check = new bool[S];
		string* parent = new string[S];
		for (int i = 0; i < S; i++) {
			cost[i] = 1000000000;
			check[i] = false;
		}

		int cityNo = shortPath.CityToNumber(source);
		cost[cityNo] = 0;
		parent[cityNo] = "\0";

		for (int q = 0; q < S; q++) {
			costAdder.insert(0, cost[q], cityVertices()[q]);
		}

		while (!costAdder.isEmpty()) {
			int u = shortPath.CityToNumber(costAdder.retCity());
			string main_city = costAdder.retCity();
			int p = costAdder.deleteMin();
			if (p == 1000000000) {
				break;
			}
			check[u] = true;
			for (int count = 0; count < S; count++) {
				string other_city = shortPath.NumberToCity(count);
				bool repeat = false;
				for (int i = 0; i < min.Size(); i++) {
					if (shortPath.specSecondaryCheckCost(main_city, other_city, min, airline) + cost[u] == min[i]) {
						repeat = true;
						break;
					}
				}
				if (!repeat)
				{
					if (check[count] == false && shortPath.specSecondaryCheckCost(main_city, other_city, min, airline) + cost[u] < cost[count]) {
						if (shortPath.checkCost(main_city, other_city) != 0) {
							cost[count] = shortPath.specSecondaryCheckCost(main_city, other_city, min, airline) + cost[u];
							parent[count] = main_city;
							costAdder.insert(0, cost[count], shortPath.cityVertices()[count]);
						}
					}
				}
			}
		}

		int final = shortPath.CityToNumber(destination);

		if (cost[final] == 1000000000 || cost[final] == 0) {
			cout << "No other flghts to " << destination << " available VIA " << airline << endl;
		}
		else {
			cout << source << " To " << destination << " ~ Cost: Rs " << cost[final] << " VIA ";
			CalculateCities(source, cityVertices(), parent, final);
			cout << endl;
		}
		return cost[final];
	}

	// Called When user enters a specific airline to travel through with cost efficiency //
	void specMainDijkstraForCost(Graph shortPath, string source, string destination, string airline) { // airline specify 
		int num = 0;
		vector<int> min;
		num = specDijkstraForCost(shortPath, source, destination, airline);
		min.Push_Back(num);
		int i = 0;
		while (i < 10) {
			if (num != 1000000000) {
				num = specDijkstraForCost(shortPath, source, destination, min, airline);
				min.Push_Back(num);
			}
			else {
				break;
			}
			i++;
		}
	}

	//=============> Time Based Functions <==============//
//=========================================================================================================================================//

	int DijkstraForTime(Graph shortPath, string source, string destination, vector<int>min) {
		PriorityQueue<int> timeAdder;
		int* time = new int[S];
		bool* check = new bool[S];
		string* parent = new string[S];
		for (int i = 0; i < S; i++) {
			time[i] = 1000000000;
			check[i] = false;
		}

		int cityNo = shortPath.CityToNumber(source);
		time[cityNo] = 0;
		parent[cityNo] = "\0";

		for (int q = 0; q < S; q++) {
			timeAdder.insert(0, time[q], cityVertices()[q]);
		}

		while (!timeAdder.isEmpty()) {
			int u = shortPath.CityToNumber(timeAdder.retCity());
			string main_city = timeAdder.retCity();
			int p = timeAdder.deleteMin();
			if (p == 1000000000) {
				break;
			}
			check[u] = true;
			for (int count = 0; count < S; count++) {
				string other_city = shortPath.NumberToCity(count);

				bool repeat = false;
				for (int i = 0; i < min.Size(); i++) {
					if (shortPath.secondaryCheckTime(main_city, other_city, min) + time[u] == min[i]) {
						repeat = true;
						break;
					}
				}

				if (!repeat)
				{
					if (check[count] == false && shortPath.secondaryCheckTime(main_city, other_city, min) + time[u] < time[count]) {
						if (shortPath.checkTime(main_city, other_city) != 0) {
							time[count] = shortPath.secondaryCheckTime(main_city, other_city, min) + time[u];
							parent[count] = main_city;
							timeAdder.insert(0, time[count], shortPath.cityVertices()[count]);
						}
					}
				}

			}
		}

		int final = shortPath.CityToNumber(destination);

		if (time[final] == 1000000000 || time[final] == 0) {
			cout << "No other flights to " << destination << " available" << endl;
		}
		else {
			cout << source << " To " << destination << " ~ Time: " << time[final] << " hrs VIA ";
			CalculateCities(source, cityVertices(), parent, final);
			cout << endl;
		}
		return time[final];
	}



	int DijkstraForTime(Graph shortPath, string source, string destination) {
		PriorityQueue<int> timeAdder;
		int* time = new int[S];
		bool* check = new bool[S];
		string* parent = new string[S];
		for (int i = 0; i < S; i++) {
			time[i] = 1000000000;
			check[i] = false;
		}

		int cityNo = shortPath.CityToNumber(source);
		time[cityNo] = 0;
		parent[cityNo] = "\0";

		for (int q = 0; q < S; q++) {
			timeAdder.insert(0, time[q], cityVertices()[q]);
		}

		while (!timeAdder.isEmpty()) {
			int u = shortPath.CityToNumber(timeAdder.retCity());
			string main_city = timeAdder.retCity();
			int p = timeAdder.deleteMin();
			if (p == 1000000000) {
				break;
			}
			check[u] = true;
			for (int count = 0; count < S; count++) {
				string other_city = shortPath.NumberToCity(count);
				if (check[count] == false && shortPath.checkTime(main_city, other_city) + time[u] < time[count]) {
					if (shortPath.checkTime(main_city, other_city) != 0) {
						time[count] = shortPath.checkTime(main_city, other_city) + time[u];
						parent[count] = main_city;
						timeAdder.insert(0, time[count], shortPath.cityVertices()[count]);
					}
				}
			}
		}

		int final = shortPath.CityToNumber(destination);

		if (time[final] == 1000000000 || time[final] == 0) {
			cout << source << " To " << destination << " no flights available" << endl;
		}
		else {
			cout << source << " To " << destination << " ~ Time: " << time[final] << " hrs VIA ";
			CalculateCities(source, cityVertices(), parent, final);
			cout << endl;
		}

		return time[final];
	}

	void mainDijkstraForTime(Graph shortPath, string source, string destination) { // not with airline
		int num = 0;
		vector<int> min;
		num = DijkstraForTime(shortPath, source, destination);
		min.Push_Back(num);
		int i = 0;
		while (i < 10) {
			if (num != 1000000000) {
				num = DijkstraForTime(shortPath, source, destination, min);
				min.Push_Back(num);
			}
			else {
				break;
			}
			i++;
		}
	}


	//============= Transit-Based Functionality ============//
//=====================================================================================================================================//

	int transitDijkstra(Graph shortPath, string source, string destination, string transloc) { 
		PriorityQueue<int> costAdder;
		int* cost = new int[S];
		bool* check = new bool[S];
		string* parent = new string[S];
		for (int i = 0; i < S; i++) {
			cost[i] = 1000000000;
			check[i] = false;
		}

		int cityNo = shortPath.CityToNumber(source);
		cost[cityNo] = 0;
		parent[cityNo] = "\0";

		for (int q = 0; q < S; q++) {
			costAdder.insert(0, cost[q], cityVertices()[q]);
		}

		while (!costAdder.isEmpty()) {
			int u = shortPath.CityToNumber(costAdder.retCity());
			string main_city = costAdder.retCity();
			int p = costAdder.deleteMin();
			if (p == 1000000000) {
				break;
			}
			check[u] = true;
			for (int count = 0; count < S; count++) {
				string other_city = shortPath.NumberToCity(count);
				if (check[count] == false && shortPath.checkCost(main_city, other_city) + cost[u] < cost[count]) {
					if (shortPath.checkCost(main_city, other_city) != 0) {
						cost[count] = shortPath.checkCost(main_city, other_city) + cost[u];
						parent[count] = main_city;
						costAdder.insert(0, cost[count], shortPath.cityVertices()[count]);
					}
				}
			}
		}

		int final = shortPath.CityToNumber(destination);

		bool yes = false;

		vector<string> transit = transitCities(source, cityVertices(), parent, final);
		for (int i = 0; i < transit.Size(); i++) {
			if (transit[i] == transloc) {
				cout << source << " To " << destination << " ~ Cost: Rs " << cost[final] << " with location " << transloc << " VIA ";
				CalculateCities(source, cityVertices(), parent, final);
				cout << endl;
				break;
			}
		}
		if (cost[final] == 1000000000 || cost[final] == 0) {
			cout << "No flight with location " << transloc << " available." << endl;
			return 1000000000;
		}
		return cost[final];
	}

	int transitDijkstra(Graph shortPath, string source, string destination, vector<int>min, string transloc) {
		PriorityQueue<int> costAdder;
		int* cost = new int[S];
		bool* check = new bool[S];
		string* parent = new string[S];
		for (int i = 0; i < S; i++) {
			cost[i] = 1000000000;
			check[i] = false;
		}

		int cityNo = shortPath.CityToNumber(source);
		cost[cityNo] = 0;
		parent[cityNo] = "\0";

		for (int q = 0; q < S; q++) {
			costAdder.insert(0, cost[q], cityVertices()[q]);
		}

		while (!costAdder.isEmpty()) {
			int u = shortPath.CityToNumber(costAdder.retCity());
			string main_city = costAdder.retCity();
			int p = costAdder.deleteMin();
			if (p == 1000000000) {
				break;
			}
			check[u] = true;
			for (int count = 0; count < S; count++) {
				string other_city = shortPath.NumberToCity(count);
				bool repeat = false;
				for (int i = 0; i < min.Size(); i++) {
					if (shortPath.secondaryCheckCost(main_city, other_city, min) + cost[u] == min[i]) {
						repeat = true;
						break;
					}
				}
				if (!repeat)
				{
					if (check[count] == false && shortPath.secondaryCheckCost(main_city, other_city, min) + cost[u] < cost[count]) {
						if (shortPath.checkCost(main_city, other_city) != 0) {
							cost[count] = shortPath.secondaryCheckCost(main_city, other_city, min) + cost[u];
							parent[count] = main_city;
							costAdder.insert(0, cost[count], shortPath.cityVertices()[count]);
						}
					}
				}
			}
		}

		int final = shortPath.CityToNumber(destination);

		bool yes = false;

		vector<string> transit = transitCities(source, cityVertices(), parent, final);
		for (int i = 0; i < transit.Size(); i++) {
			if (transit[i] == transloc){
				cout << source << " To " << destination << " ~ Cost: Rs " << cost[final] << " with location " << transloc << " VIA ";
				CalculateCities(source, cityVertices(), parent, final);
				cout << endl;
				break;
			}
		}
		if (cost[final] == 1000000000 || cost[final] == 0) {
			cout << "No other flight with location " << transloc << " available." << endl;
		}

		return cost[final];
	}
	
	// Dijkstra Implementation based on Cost efficiency //
	void mainTransitDijkstra(Graph shortPath, string source, string destination, string transloc) { // ask for transit location
		int num = 0;
		vector<int> min;
		num = transitDijkstra(shortPath, source, destination, transloc);
		min.Push_Back(num);
		int i = 0;
		while (i < 10) {
			if (num != 1000000000) {
				num = transitDijkstra(shortPath, source, destination, min, transloc);
				min.Push_Back(num);
			}
			else {
				break;
			}
			i++;
		}
	}

	//========================================================================================================================================//

	//===================================== DIRECT FLIGHT ========================================//
	void DirectFlights2(string src, string des, int day, int month, int year, string airline, string basis) {

		//cout << endl << endl << "Direct Flights 2 Called" << endl << endl;

		// if airline is not mentioned
		
		string src1, des1, airline1;
		int d, m, y, fth, ftm, lth, ltm;
		int tof = 1000000;
		int tpr = 1000000;

		// if airline is mentioned
		if (airline == "$") {

			if (basis == "Time") {

				bool check1 = false;
				bool check2 = false;
				for (int i = 0; i < S; i++) {
					Node* temp = array[i].getHead()->next;
					while (temp != NULL) {
						if (temp->Source == src && temp->Destination == des && temp->day == day && temp->month == month && temp->year == year) {
							//cout << "ONCE";
							if (check2 == false) {
								cout << endl << "Here Are The Potential Flights You Could Catch: " << endl;
								check2 = true;
							}
							if (temp->timeofFlight < tof) {
								src1 = temp->Source;
								des1 = temp->Destination;
								airline1 = temp->Airline;
								d = temp->day;
								m = temp->month;
								y = temp->year;
								fth = temp->FlyTimeH;
								ftm = temp->FlyTimeM;
								lth = temp->LandTimeH;
								ltm = temp->LandTimeM;
								tof = temp->timeofFlight;
								tpr = temp->TicketPrice;
							}
							if (temp->timeofFlight == tof && d != temp->day) {
								//cout << "AAA";
								cout << "Origin: " << temp->Source << endl;
								cout << "Destination: " << temp->Destination << endl;
								cout << "Flight Schedule: " << temp->day << "/" << temp->month << "/" << temp->year << endl;
								cout << "Flight Hours: " << temp->FlyTimeH << ":" << temp->FlyTimeM << "-" << temp->LandTimeH << ":" << temp->LandTimeM << endl;
								cout << "Airline: " << temp->Airline << endl;
								cout << "Flight Duration: " << temp->timeofFlight << " hour/s" << endl;
								cout << "Expense: " << temp->TicketPrice << "$" << endl << endl;
							}
							check1 = true;
						}
						temp = temp->next;
					}
				}

				if (check1 == true) {
					//cout << "BBB";
					cout << "Origin: " << src1 << endl;
					cout << "Destination: " << des1 << endl;
					cout << "Flight Schedule: " << d << "/" << m << "/" << y << endl;
					cout << "Flight Hours: " << fth << ":" << ftm << "-" << lth << ":" << ltm << endl;
					cout << "Airline: " << airline1 << endl;
					cout << "Flight Duration: " << tof << " hour/s" << endl;
					cout << "Expense: " << tpr << "$" << endl << endl;
				}

				if (check1 != true) {
					cout << endl << "No Flights Available On The Given Date: " << endl << endl;

					int dayprev, dayaft, monthprev, monthaft;
					check1 = check2 = false;
					if (day == 1 || day == 31) {
						if (day == 1) {
							dayaft = 2;
							dayprev = 31;
							if (month == 1) {
								monthprev = 12;
								monthaft = 2;
							}
							else if (month == 12) {
								monthprev = 11;
								monthaft = 1;
							}
							else {
								monthprev = month - 1;
								monthaft = month + 1;
							}
						}
						else if (day == 31) {
							dayaft = 1;
							dayprev = 30;
							if (month == 1) {
								monthprev = 12;
								monthaft = 2;
							}
							else if (month == 12) {
								monthprev = 11;
								monthaft = 1;
							}
							else {
								monthprev = month - 1;
								monthaft = month + 1;
							}
						}
					}
					else {
						dayprev = day - 1;
						dayaft = day + 1;
						monthprev = month;
						monthaft = month;
					}

					for (int i = 0; i < S; i++) {
						Node* temp = array[i].getHead()->next;
						while (temp != NULL) {
							if (temp->Source == src && temp->Destination == des && ((temp->day == dayprev && temp->month == monthprev && temp->year == year) || (temp->day == dayaft && temp->month == monthaft && temp->year == year))) {
								cout << endl << "AGYAA" << endl;
								if (check2 == false) {
									cout << endl << "Available Flights Near The Mentioned Date: " << endl;
									check2 = true;
								}
								if (temp->timeofFlight < tof) {
									src1 = temp->Source;
									des1 = temp->Destination;
									airline1 = temp->Airline;
									d = temp->day;
									m = temp->month;
									y = temp->year;
									fth = temp->FlyTimeH;
									ftm = temp->FlyTimeM;
									lth = temp->LandTimeH;
									ltm = temp->LandTimeM;
									tof = temp->timeofFlight;
									tpr = temp->TicketPrice;
								}
								if (temp->timeofFlight == tof && d != temp->day) {
									//cout << "AAA";
									cout << "Origin: " << temp->Source << endl;
									cout << "Destination: " << temp->Destination << endl;
									cout << "Flight Schedule: " << temp->day << "/" << temp->month << "/" << temp->year << endl;
									cout << "Flight Hours: " << temp->FlyTimeH << ":" << temp->FlyTimeM << "-" << temp->LandTimeH << ":" << temp->LandTimeM << endl;
									cout << "Airline: " << temp->Airline << endl;
									cout << "Flight Duration: " << temp->timeofFlight << " hour/s" << endl;
									cout << "Expense: " << temp->TicketPrice << "$" << endl << endl;
								}
								check1 = true;
							}
							temp = temp->next;
						}
					}
					if (check1 == true) {
						//cout << "BBB";
						cout << "Origin: " << src1 << endl;
						cout << "Destination: " << des1 << endl;
						cout << "Flight Schedule: " << d << "/" << m << "/" << y << endl;
						cout << "Flight Hours: " << fth << ":" << ftm << "-" << lth << ":" << ltm << endl;
						cout << "Airline: " << airline1 << endl;
						cout << "Flight Duration: " << tof << " hour/s" << endl;
						cout << "Expense: " << tpr << "$" << endl << endl;
					}

					if (check1 == false)
						cout << "No Flights Available Before Or After The Mentioned Date Either" << endl;
				}
			}

			//////////////////////////////////^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^/////////////////////////////////////////////////////////////////
			//////////////////////////////////^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^/////////////////////////////////////////////////////////////////
			//////////////////////////////////^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^/////////////////////////////////////////////////////////////////
			//////////////////////////////////^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^/////////////////////////////////////////////////////////////////
			//////////////////////////////////^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^/////////////////////////////////////////////////////////////////

			if (basis == "Cost") {

				bool check1 = false;
				bool check2 = false;
				for (int i = 0; i < S; i++) {
					Node* temp = array[i].getHead()->next;
					while (temp != NULL) {
						if (temp->Source == src && temp->Destination == des && temp->day == day && temp->month == month && temp->year == year) {
							//cout << "ONCE";
							if (check2 == false) {
								cout << endl << "Here Are The Potential Flights You Could Catch: " << endl;
								check2 = true;
							}
							if (temp->TicketPrice < tpr) {
								src1 = temp->Source;
								des1 = temp->Destination;
								airline1 = temp->Airline;
								d = temp->day;
								m = temp->month;
								y = temp->year;
								fth = temp->FlyTimeH;
								ftm = temp->FlyTimeM;
								lth = temp->LandTimeH;
								ltm = temp->LandTimeM;
								tof = temp->timeofFlight;
								tpr = temp->TicketPrice;
							}
							if (temp->TicketPrice == tpr && d != temp->day) {
								//cout << "AAA";
								cout << "Origin: " << temp->Source << endl;
								cout << "Destination: " << temp->Destination << endl;
								cout << "Flight Schedule: " << temp->day << "/" << temp->month << "/" << temp->year << endl;
								cout << "Flight Hours: " << temp->FlyTimeH << ":" << temp->FlyTimeM << "-" << temp->LandTimeH << ":" << temp->LandTimeM << endl;
								cout << "Airline: " << temp->Airline << endl;
								cout << "Flight Duration: " << temp->timeofFlight << " hour/s" << endl;
								cout << "Expense: " << temp->TicketPrice << "$" << endl << endl;
							}
							check1 = true;
						}
						temp = temp->next;
					}
				}

				if (check1 == true) {
					//cout << "BBB";
					cout << "Origin: " << src1 << endl;
					cout << "Destination: " << des1 << endl;
					cout << "Flight Schedule: " << d << "/" << m << "/" << y << endl;
					cout << "Flight Hours: " << fth << ":" << ftm << "-" << lth << ":" << ltm << endl;
					cout << "Airline: " << airline1 << endl;
					cout << "Flight Duration: " << tof << " hour/s" << endl;
					cout << "Expense: " << tpr << "$" << endl << endl;
				}

				if (check1 != true) {
					cout << "No Flights Available On The Given Date: " << endl << endl;

					int dayprev, dayaft, monthprev, monthaft;
					check1 = check2 = false;
					if (day == 1 || day == 31) {
						if (day == 1) {
							dayaft = 2;
							dayprev = 31;
							if (month == 1) {
								monthprev = 12;
								monthaft = 2;
							}
							else if (month == 12) {
								monthprev = 11;
								monthaft = 1;
							}
							else {
								monthprev = month - 1;
								monthaft = month + 1;
							}
						}
						else if (day == 31) {
							dayaft = 1;
							dayprev = 30;
							if (month == 1) {
								monthprev = 12;
								monthaft = 2;
							}
							else if (month == 12) {
								monthprev = 11;
								monthaft = 1;
							}
							else {
								monthprev = month - 1;
								monthaft = month + 1;
							}
						}
					}
					else {
						dayprev = day - 1;
						dayaft = day + 1;
						monthprev = month;
						monthaft = month;
					}

					for (int i = 0; i < S; i++) {
						Node* temp = array[i].getHead()->next;
						while (temp != NULL) {
							if (temp->Source == src && temp->Destination == des && ((temp->day == dayprev && temp->month == monthprev && temp->year == year) || (temp->day == dayaft && temp->month == monthaft && temp->year == year))) {
								//cout << endl << "AGYAA" << endl;
								if (check2 == false) {
									cout << endl << "Available Flights Near The Mentioned Date: " << endl;
									check2 = true;
								}
								if (temp->TicketPrice < tpr) {
									src1 = temp->Source;
									des1 = temp->Destination;
									airline1 = temp->Airline;
									d = temp->day;
									m = temp->month;
									y = temp->year;
									fth = temp->FlyTimeH;
									ftm = temp->FlyTimeM;
									lth = temp->LandTimeH;
									ltm = temp->LandTimeM;
									tof = temp->timeofFlight;
									tpr = temp->TicketPrice;
								}
								if (temp->TicketPrice == tpr && d != temp->day) {
									//cout << "AAA";
									cout << "Origin: " << temp->Source << endl;
									cout << "Destination: " << temp->Destination << endl;
									cout << "Flight Schedule: " << temp->day << "/" << temp->month << "/" << temp->year << endl;
									cout << "Flight Hours: " << temp->FlyTimeH << ":" << temp->FlyTimeM << "-" << temp->LandTimeH << ":" << temp->LandTimeM << endl;
									cout << "Airline: " << temp->Airline << endl;
									cout << "Flight Duration: " << temp->timeofFlight << " hour/s" << endl;
									cout << "Expense: " << temp->TicketPrice << "$" << endl << endl;
								}
								check1 = true;
							}
							temp = temp->next;
						}
					}
					if (check1 == true) {
						//cout << "BBB";
						cout << "Origin: " << src1 << endl;
						cout << "Destination: " << des1 << endl;
						cout << "Flight Schedule: " << d << "/" << m << "/" << y << endl;
						cout << "Flight Hours: " << fth << ":" << ftm << "-" << lth << ":" << ltm << endl;
						cout << "Airline: " << airline1 << endl;
						cout << "Flight Duration: " << tof << " hour/s" << endl;
						cout << "Expense: " << tpr << "$" << endl << endl;
					}

					if (check1 == false)
						cout << "No Flights Available Before Or After The Mentioned Date Either" << endl;
				}
			}
		}


	}


	void DisplaySources() {
		for (int i = 0; i < S; i++) {
			Node* temp = array[i].getHead();
			while (temp != NULL) {
				cout << i << " " << temp->Source << " " << temp->Destination << endl;
				break;
			}
		}
	}

	void IndirectFlights(string src, string des, string airline, int thours) {

		for (int i = 0; i < S; i++) {
			if (array[i].getHead()->Source == src) {
				Node* temp1 = array[i].getHead()->next;
				while (temp1 != NULL) {
					if (temp1->Airline == airline) {
						for (int j = 0; j < S; j++) {
							if (temp1->Destination == array[j].getHead()->Source) {
								Node* temp2 = array[j].getHead()->next;
								while (temp2 != NULL) {
									if (temp2->Airline == airline && temp2->Destination == des && temp1->Source == src && temp1->Destination == temp2->Source) {
										cout << endl << "Available Flights: " << endl;
										cout << "Source: " << temp1->Source << endl;
										cout << "Transit Location: " << temp2->Source << endl;
										cout << "Destination: " << temp2->Destination << endl;
										cout << "Expense= (" << temp1->TicketPrice << "$ + " << temp2->TicketPrice << "$)= " << temp1->TicketPrice + temp2->TicketPrice << endl;
										cout << "Total Travel Time: " << temp1->timeofFlight + temp2->timeofFlight + thours << " Hours" << endl;
										return;
									}
									temp2 = temp2->next;
								}
							}
						}
					}
					temp1 = temp1->next;
				}
			}
		}

	}

	void DirectFlights(string src, string des, int day, int month, int year, string airline, string basis) {

		//cout << endl << endl << "Direct Flights 1 Called" << endl << endl;

		string src1, des1, airline1;
		int d, m, y, fth, ftm, lth, ltm;
		int tof = 1000000;
		int tpr = 1000000;

		// if airline is mentioned
		if (airline != "$") {

			if (basis == "Time") {

				bool check1 = false;
				bool check2 = false;
				for (int i = 0; i < S; i++) {
					Node* temp = array[i].getHead()->next;
					while (temp != NULL) {
						if (temp->Source == src && temp->Destination == des && temp->day == day && temp->month == month && temp->year == year && temp->Airline == airline) {
							//cout << "ONCE";
							if (check2 == false) {
								cout << endl << "Here Are The Potential Flights You Could Catch: " << endl;
								check2 = true;
							}
							if (temp->timeofFlight < tof) {
								src1 = temp->Source;
								des1 = temp->Destination;
								airline1 = temp->Airline;
								d = temp->day;
								m = temp->month;
								y = temp->year;
								fth = temp->FlyTimeH;
								ftm = temp->FlyTimeM;
								lth = temp->LandTimeH;
								ltm = temp->LandTimeM;
								tof = temp->timeofFlight;
								tpr = temp->TicketPrice;
							}
							if (temp->timeofFlight == tof && d != temp->day) {
								//cout << "AAA";
								cout << "Origin: " << temp->Source << endl;
								cout << "Destination: " << temp->Destination << endl;
								cout << "Flight Schedule: " << temp->day << "/" << temp->month << "/" << temp->year << endl;
								cout << "Flight Hours: " << temp->FlyTimeH << ":" << temp->FlyTimeM << "-" << temp->LandTimeH << ":" << temp->LandTimeM << endl;
								cout << "Airline: " << temp->Airline << endl;
								cout << "Flight Duration: " << temp->timeofFlight << " hour/s" << endl;
								cout << "Expense: " << temp->TicketPrice << "$" << endl << endl;
							}
							check1 = true;
						}
						temp = temp->next;
					}
				}

				if (check1 == true) {
					//cout << "BBB";
					cout << "Origin: " << src1 << endl;
					cout << "Destination: " << des1 << endl;
					cout << "Flight Schedule: " << d << "/" << m << "/" << y << endl;
					cout << "Flight Hours: " << fth << ":" << ftm << "-" << lth << ":" << ltm << endl;
					cout << "Airline: " << airline1 << endl;
					cout << "Flight Duration: " << tof << " hour/s" << endl;
					cout << "Expense: " << tpr << "$" << endl << endl;
				}

				if (check1 != true) {
					cout << endl << "No Flights Available On The Given Date: " << endl << endl;

					int dayprev, dayaft, monthprev, monthaft;
					check1 = check2 = false;
					if (day == 1 || day == 31) {
						if (day == 1) {
							dayaft = 2;
							dayprev = 31;
							if (month == 1) {
								monthprev = 12;
								monthaft = 2;
							}
							else if (month == 12) {
								monthprev = 11;
								monthaft = 1;
							}
							else {
								monthprev = month - 1;
								monthaft = month + 1;
							}
						}
						else if (day == 31) {
							dayaft = 1;
							dayprev = 30;
							if (month == 1) {
								monthprev = 12;
								monthaft = 2;
							}
							else if (month == 12) {
								monthprev = 11;
								monthaft = 1;
							}
							else {
								monthprev = month - 1;
								monthaft = month + 1;
							}
						}
					}
					else {
						dayprev = day - 1;
						dayaft = day + 1;
						monthprev = month;
						monthaft = month;
					}

					for (int i = 0; i < S; i++) {
						Node* temp = array[i].getHead()->next;
						while (temp != NULL) {
							if (temp->Source == src && temp->Destination == des && ((temp->day == dayprev && temp->month == monthprev && temp->year == year && temp->Airline == airline) || (temp->day == dayaft && temp->month == monthaft && temp->year == year && temp->Airline == airline))) {
								cout << endl << "AGYAA" << endl;
								if (check2 == false) {
									cout << endl << "Available Flights Near The Mentioned Date: " << endl;
									check2 = true;
								}
								if (temp->timeofFlight < tof) {
									src1 = temp->Source;
									des1 = temp->Destination;
									airline1 = temp->Airline;
									d = temp->day;
									m = temp->month;
									y = temp->year;
									fth = temp->FlyTimeH;
									ftm = temp->FlyTimeM;
									lth = temp->LandTimeH;
									ltm = temp->LandTimeM;
									tof = temp->timeofFlight;
									tpr = temp->TicketPrice;
								}
								if (temp->timeofFlight == tof && d != temp->day) {
									//cout << "AAA";
									cout << "Origin: " << temp->Source << endl;
									cout << "Destination: " << temp->Destination << endl;
									cout << "Flight Schedule: " << temp->day << "/" << temp->month << "/" << temp->year << endl;
									cout << "Flight Hours: " << temp->FlyTimeH << ":" << temp->FlyTimeM << "-" << temp->LandTimeH << ":" << temp->LandTimeM << endl;
									cout << "Airline: " << temp->Airline << endl;
									cout << "Flight Duration: " << temp->timeofFlight << " hour/s" << endl;
									cout << "Expense: " << temp->TicketPrice << "$" << endl << endl;
								}
								check1 = true;
							}
							temp = temp->next;
						}
					}
					if (check1 == true) {
						//cout << "BBB";
						cout << "Origin: " << src1 << endl;
						cout << "Destination: " << des1 << endl;
						cout << "Flight Schedule: " << d << "/" << m << "/" << y << endl;
						cout << "Flight Hours: " << fth << ":" << ftm << "-" << lth << ":" << ltm << endl;
						cout << "Airline: " << airline1 << endl;
						cout << "Flight Duration: " << tof << " hour/s" << endl;
						cout << "Expense: " << tpr << "$" << endl << endl;
					}

					if (check1 == false)
						cout << "No Flights Available Before Or After The Mentioned Date Either" << endl;
				}
			}

			//////////////////////////////////^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^/////////////////////////////////////////////////////////////////
			//////////////////////////////////^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^/////////////////////////////////////////////////////////////////
			//////////////////////////////////^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^/////////////////////////////////////////////////////////////////
			//////////////////////////////////^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^/////////////////////////////////////////////////////////////////
			//////////////////////////////////^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^/////////////////////////////////////////////////////////////////

			if (basis == "Cost") {

				bool check1 = false;
				bool check2 = false;
				for (int i = 0; i < S; i++) {
					Node* temp = array[i].getHead()->next;
					while (temp != NULL) {
						if (temp->Source == src && temp->Destination == des && temp->day == day && temp->month == month && temp->year == year && temp->Airline == airline) {
							//cout << "ONCE";
							if (check2 == false) {
								cout << endl << "Here Are The Potential Flights You Could Catch: " << endl;
								check2 = true;
							}
							if (temp->TicketPrice < tpr) {
								src1 = temp->Source;
								des1 = temp->Destination;
								airline1 = temp->Airline;
								d = temp->day;
								m = temp->month;
								y = temp->year;
								fth = temp->FlyTimeH;
								ftm = temp->FlyTimeM;
								lth = temp->LandTimeH;
								ltm = temp->LandTimeM;
								tof = temp->timeofFlight;
								tpr = temp->TicketPrice;
							}
							if (temp->TicketPrice == tpr && d != temp->day) {
								//cout << "AAA";
								cout << "Origin: " << temp->Source << endl;
								cout << "Destination: " << temp->Destination << endl;
								cout << "Flight Schedule: " << temp->day << "/" << temp->month << "/" << temp->year << endl;
								cout << "Flight Hours: " << temp->FlyTimeH << ":" << temp->FlyTimeM << "-" << temp->LandTimeH << ":" << temp->LandTimeM << endl;
								cout << "Airline: " << temp->Airline << endl;
								cout << "Flight Duration: " << temp->timeofFlight << " hour/s" << endl;
								cout << "Expense: " << temp->TicketPrice << "$" << endl << endl;
							}
							check1 = true;
						}
						temp = temp->next;
					}
				}

				if (check1 == true) {
					//cout << "BBB";
					cout << "Origin: " << src1 << endl;
					cout << "Destination: " << des1 << endl;
					cout << "Flight Schedule: " << d << "/" << m << "/" << y << endl;
					cout << "Flight Hours: " << fth << ":" << ftm << "-" << lth << ":" << ltm << endl;
					cout << "Airline: " << airline1 << endl;
					cout << "Flight Duration: " << tof << " hour/s" << endl;
					cout << "Expense: " << tpr << "$" << endl << endl;
				}

				if (check1 != true) {
					cout << "No Flights Available On The Given Date: " << endl << endl;

					int dayprev, dayaft, monthprev, monthaft;
					check1 = check2 = false;
					if (day == 1 || day == 31) {
						if (day == 1) {
							dayaft = 2;
							dayprev = 31;
							if (month == 1) {
								monthprev = 12;
								monthaft = 2;
							}
							else if (month == 12) {
								monthprev = 11;
								monthaft = 1;
							}
							else {
								monthprev = month - 1;
								monthaft = month + 1;
							}
						}
						else if (day == 31) {
							dayaft = 1;
							dayprev = 30;
							if (month == 1) {
								monthprev = 12;
								monthaft = 2;
							}
							else if (month == 12) {
								monthprev = 11;
								monthaft = 1;
							}
							else {
								monthprev = month - 1;
								monthaft = month + 1;
							}
						}
					}
					else {
						dayprev = day - 1;
						dayaft = day + 1;
						monthprev = month;
						monthaft = month;
					}

					for (int i = 0; i < S; i++) {
						Node* temp = array[i].getHead()->next;
						while (temp != NULL) {
							if (temp->Source == src && temp->Destination == des && ((temp->day == dayprev && temp->month == monthprev && temp->year == year && temp->Airline == airline) || (temp->day == dayaft && temp->month == monthaft && temp->year == year && temp->Airline == airline))) {
								//cout << endl << "AGYAA" << endl;
								if (check2 == false) {
									cout << endl << "Available Flights Near The Mentioned Date: " << endl;
									check2 = true;
								}
								if (temp->TicketPrice < tpr) {
									src1 = temp->Source;
									des1 = temp->Destination;
									airline1 = temp->Airline;
									d = temp->day;
									m = temp->month;
									y = temp->year;
									fth = temp->FlyTimeH;
									ftm = temp->FlyTimeM;
									lth = temp->LandTimeH;
									ltm = temp->LandTimeM;
									tof = temp->timeofFlight;
									tpr = temp->TicketPrice;
								}
								if (temp->TicketPrice == tpr && d != temp->day) {
									//cout << "AAA";
									cout << "Origin: " << temp->Source << endl;
									cout << "Destination: " << temp->Destination << endl;
									cout << "Flight Schedule: " << temp->day << "/" << temp->month << "/" << temp->year << endl;
									cout << "Flight Hours: " << temp->FlyTimeH << ":" << temp->FlyTimeM << "-" << temp->LandTimeH << ":" << temp->LandTimeM << endl;
									cout << "Airline: " << temp->Airline << endl;
									cout << "Flight Duration: " << temp->timeofFlight << " hour/s" << endl;
									cout << "Expense: " << temp->TicketPrice << "$" << endl << endl;
								}
								check1 = true;
							}
							temp = temp->next;
						}
					}
					if (check1 == true) {
						//cout << "BBB";
						cout << "Origin: " << src1 << endl;
						cout << "Destination: " << des1 << endl;
						cout << "Flight Schedule: " << d << "/" << m << "/" << y << endl;
						cout << "Flight Hours: " << fth << ":" << ftm << "-" << lth << ":" << ltm << endl;
						cout << "Airline: " << airline1 << endl;
						cout << "Flight Duration: " << tof << " hour/s" << endl;
						cout << "Expense: " << tpr << "$" << endl << endl;
					}

					if (check1 == false)
						cout << "No Flights Available Before Or After The Mentioned Date Either" << endl;
				}
			}
		}
		else {
			//cout << "dfsdfsdfsd";
			DirectFlights2(src, des, day, month, year, airline, basis);
		}

	}



	////////////////////////////////////////////////////////////////////////////////////////////////


	void DisplayVertices() {
		for (int i = 0; i < S; i++) {
			cout << array[i].head->Source << endl;
		}
	}

	void DisplayList() {
		Node* curr;
		for (int i = 0; i < S; i++) {
			curr = array[i].head;
			while (curr != NULL) {
				cout << curr->Destination << " ";
				curr = curr->next;
			}
			cout << endl;
		}
	}

	void display() {
		string* v = cityVertices();
		for (int i = 0; i < S; i++) {
			cout << v[i] << endl;

		}
	}

	~Graph()
	{
		if (array != NULL)
		{
		}
	}

};

