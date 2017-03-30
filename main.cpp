#include<iostream>
#include<cstring>
#include"Adjacency_list.h"

/*
Joshua Sander
CS163
Program 5
11/23/2016

This program allows the user to insert and manage a list of chorse.

It is managed as an ADT graph.

It has one menu that accesses all the necessary functions.

The size of the list of chores was originally set in the header for the data structure.
However, I noticed that the assignment stated that the size should be set by the user,
so I included a line at the beginning that allows the user define the size.
*/

using namespace std;


const int MAX = 100;


int insert_chore(table & my_table);
int insert_connection(table & my_table);
int display_from(table & my_table);
int display_to(table & my_table);

int main()
{
	char choice;
	char chore_name[MAX];
	int my_max;

	cout << endl << "Hello and welcome to your winter planner." << endl;
	cout << endl << "How many chores maximum do you think you will have?" << endl;
	cin >> my_max;
	cin.ignore();
	table my_table(my_max);
	


	do
	{
		cout << endl << "Please choose from the following options: " << endl;	
		cout << "A: Add a chore to the list" << endl;
		cout << "B: Add a connection between chores" << endl;
		cout << "C: Display all chores that need to get done before a chosen chore" << endl;
		cout << "D: Display all chores that happen after a given chore" << endl;
		cout << "E: Exit this program" << endl << endl;

		cin >> choice;
		cin.ignore();
		cout << endl;

		switch(choice)
		{
			case 'a':
			case 'A':
				insert_chore(my_table);
				break;
			case 'b':
			case 'B':
				insert_connection(my_table);
				break;
			case 'c':
			case 'C':
				display_from(my_table);
				break;
			case 'd':
			case 'D':
				display_to(my_table);
				break;
			case 'e':
			case 'E':
				break;
		}
	}while (choice != 'e' && choice != 'E');

	return 0;
}



//Calls the graph's insert vertex function
int insert_chore(table & my_table)
{
	char chore_name[MAX];

	cout << endl << "Which chore would you like to add?" << endl;
	cin.getline(chore_name, MAX, '\n');

	if (my_table.insert_vertex(chore_name) == 0)
	{
		cout << "Your list is full!" << endl;
		return 0;
	}

	cout << "Added successfully!" << endl;
	return 1;
}



//Calls the graphs insert edge function
int insert_connection(table & my_table)
{
	char chore_name1[MAX], chore_name2[MAX];

	cout << endl << "Please enter the chore that needs to be done first: " << endl;
	cin.getline(chore_name1, MAX, '\n');
	cout << endl << "Please enter the chore that needs to be done after: " << endl;
	cin.getline(chore_name2, MAX, '\n');

	if (my_table.insert_edge(chore_name1, chore_name2) == 0)
	{
		cout << endl << "Invalid entries!" << endl;
		return 0;
	}

	cout << endl << "Success!" << endl;
	return 1;
}



//Cals the function to display any paths from the chosen vertex
int display_from(table & my_table)
{
	char chore_name[MAX];
	int result;

	cout << endl << "Please enter the name of the chore and you will see what needs to be done first: " << endl;
	cin.getline(chore_name, MAX, '\n');
	cout << endl << "Your results are: " << endl;

	result = my_table.display_prior_connections(chore_name);

	if (result == 0)
	{
		cout << endl << "This chore is not in your list!" << endl;
		return 0;
	}

	else if (result == -1)
	{
		cout << endl << "Nothing comes before this chore!" << endl;
	}

	return 1;
}



//Calls the function to display any paths leading to the given vertex
int display_to(table & my_table)
{
	char chore_name[MAX];
	int result;

	cout << endl << "Please enter the name of the chore and you will see what happens after: " << endl;
	cin.getline(chore_name, MAX, '\n');
	cout << endl << "Your results are: " << endl;

	result = my_table.display_connections(chore_name);
	if (result < 0)
	{
		cout << endl << "This chore is not in your list!" << endl;
		return 0;
	}

	if (result == 0)
	{
		cout << endl << "Nothing comes after this chore!" << endl;
		return 0;
	}

	return 1;

}
