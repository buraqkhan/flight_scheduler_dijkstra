#pragma once


#include <iostream>
#include <sstream>
using namespace std;


struct Node
{
	int data;
	Node* next;
	Node* previous;
	bool visited;

	////TRAVEL INFORMATION

	string Source;

	string Destination;

	string DOT; // date of travel
	int day;
	int month;
	int year;

	int timeofFlight;

	int TransitM;

	int FlyTimeH; //flying time hours
	int FlyTimeM; //minutes

	int LandTimeH; //Landing time
	int LandTimeM;  //minutes

	int TicketPrice;

	string Airline;



	//////////////////////////////

	Node()
	{
		//Normal 
		data = 0;
		next = NULL; 
		previous = NULL;
		visited = false;


		//Flight info
		Source = "";
		Destination = "";
		DOT = "";

		timeofFlight = 0;

		day = 0;
		month = 0;
		year = 0;

		FlyTimeH = 0;
		FlyTimeM = 0;

		LandTimeH = 0;
		LandTimeM = 0;

		TicketPrice = 0;

		Airline = "";


		//New
	

	}//constructor


};
