#include <iostream>
#include "Graph.h"
using namespace std;

int main() {
	Graph G("Flights.txt");
	G.DisplayVertices();
	
	string src, des, airline, basis;
	int day, month, year, transitHours;
	int choice1, choice2, choice3, choice4, choice5;
	bool flag;

	//Graph G("Flights.txt");
	//G.DisplaySources();
	//G.showGraphStructure();
	cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<< Welcome To AirLine Reservation System >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl << endl << endl;
	cout << "What Would You Like To Do?" << endl;
	cout << "1.Proceed To Book A Flight" << endl;
	cout << "2.Exit" << endl;
	cin >> choice1;

	while ((choice1 != 1) && (choice1 != 2)) {
		cout << "Invalid Input Entered,Please Try Again" << endl << endl;
		cout << "What Would You Like To Do?" << endl;
		cout << "1.Proceed To Book A Flight" << endl;
		cout << "2.Exit" << endl;
		cin >> choice1;
	}

	while (choice1 == 1 || choice1 == 2) {
		if (choice1 == 1) {
			Graph G("Flights.txt");

			cout << "Enter Origin Of Your Journey: ";
			cin >> src;
			cout << "Enter Destination Of Your Journey: ";
			cin >> des;
			cout << "Enter Day Of Travel: ";
			cin >> day;
			cout << "Enter Month Of Travel: ";
			cin >> month;
			cout << "Enter Year Of Travel: ";
			cin >> year;
			cout << endl;
			cout << "Would you Like to Specify Your Airline? " << endl;
			cout << "1.Yes" << endl;
			cout << "2.No" << endl;
			cin >> choice2;
			while ((choice2 != 1) && (choice2 != 2)) {
				cout << "Invalid Input,Try Again: " << endl;
				cout << "Would you Like to Specify Your Airline? " << endl;
				cout << "1.Yes" << endl;
				cout << "2.No" << endl;
				cin >> choice2;
			}
			if (choice2 == 1) {
				cout << endl << "Enter An Airline Of Your Choice: ";
				cin.ignore();
				getline(cin, airline);
			}
			else {
				airline = "$";
			}
			cout << endl;
			cout << "Is Your Flight Direct Or Indirect?" << endl;
			cout << "1.Direct" << endl;
			cout << "2.Indirect" << endl;
			cin >> choice3;
			while ((choice3 != 1) && (choice3 != 2)) {
				cout << "Invalid Input,Try Again: " << endl;
				cout << "Is Your Flight Direct Or Indirect?" << endl;
				cout << "1.Direct" << endl;
				cout << "2.Indirect" << endl;
				cin >> choice3;
			}
			if (choice3 == 1) {
				flag = true;
			}
			else {
				flag = false;
			}
			if (flag == false) {
				cout << endl << "Enter Transit Hours: (Enter 0 For None)" << endl;
				cin >> choice4;
				while (choice4 < 0) {
					cout << "Transit Hours Cannot Be Negative,Please Try Again: ";
					cin >> choice4;
				}
				transitHours = choice4;
			}
			// call function for direct flights
			if (flag == true) {
				cout << "On What Basis Would You Like To Book Your Flight?" << endl;
				cout << "1.Travel Time" << endl;
				cout << "2.Travel Expense" << endl;
				cin >> choice5;

				while (choice5 != 1 && choice5 != 2) {
					cout << "Invalid Input,Try Again: " << endl;
					cout << "On What Basis Would You Like To Book Your Flight?" << endl;
					cout << "1.Travel Time" << endl;
					cout << "2.Travel Cost" << endl;
					cin >> choice5;
				}
				if (choice5 == 1)
					basis = "Time";
				else
					basis = "Cost";

				G.DirectFlights(src, des, day, month, year, airline, basis);
			}
			else {
				cout << "On What Basis Would You Like To Book Your Flight?" << endl;
				cout << "1.Travel Time" << endl;
				cout << "2.Travel Expense" << endl;
				cin >> choice5;

				while (choice5 != 1 && choice5 != 2) {
					cout << "Invalid Input,Try Again: " << endl;
					cout << "On What Basis Would You Like To Book Your Flight?" << endl;
					cout << "1.Travel Time" << endl;
					cout << "2.Travel Cost" << endl;
					cin >> choice5;
				}

				if (airline == "$" && choice5 == 2)
					G.mainDijkstraForCost(G, src, des);

				else if (airline != "$" && choice5 == 2)
					G.specMainDijkstraForCost(G, src, des, airline);

				else if (airline == "$" && choice5 == 1)
					G.mainDijkstraForTime(G, src, des);

				else if (airline != "$" && choice5 == 1) {
					string transitlocation;
					cout << "Enter Your Transit Location: ";
					getline(cin, transitlocation);
					G.mainTransitDijkstra(G, src, des, transitlocation);
				}

				else
					break;
			}
		}
		else
			break;
	}

	cout << endl << endl << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Have A Safe Journey :) >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl << endl;
	system("pause");

	//return 0;
}