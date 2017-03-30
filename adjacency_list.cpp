#include"Adjacency_list.h"
#include<cstring>
#include<iostream>

using namespace std;



//The default constructor
table::table(int size)
{
	list_size = size;
	a_list = new vertex[size];

	vertex * current = a_list;
	vertex * last = a_list + size;

	while (current < last)
	{
		(*current).chore = NULL;
		(*current).head = NULL;
		(*current).visited = false;
		++current;
	}
} 



//The destructor
table::~table()
{
	vertex * current = a_list;
	vertex * last = a_list + list_size;
	node * temp;

	while (current < last) //Iterates through array
	{
		if ( current->head ) //If the element contains a LLL
		{
			while (current->head) //Iterate and destroy the LLL
			{
				temp = current->head->next;
				delete current->head;
				current->head = temp;						
			}
		}

		if ( current->chore ) //If the chore name exists, delete it
			delete current->chore;

		++current;
	}

	delete a_list; //Finally, delete the array itself
}			



//Function used as a subroutine by other functions
//This finds the correct index in the array and sends
//it back to the calling function as a pointer to the element
//or a pointer to NULL if the element doesn't exist.
vertex * table::find_vertex(char * name)
{
	vertex * current = a_list; 
	vertex * last = a_list + list_size;

	while (current < last)
	{
		if (!current->chore)
			current = last;

		else if (strcmp (current->chore, name) == 0)
		{
			return current;
		}	

		else	
		++current;
	}

	return NULL;
}



//This is the wrapper function for printing all of the vertices
//in any path originating from the user chosen vertex
int table::display_connections(char * name)
{
	vertex * current = find_vertex(name); //Call find_vertex to store the address of the eleement in current
	int result; //Used to tell the calling function the type of result

	if (!current)
		return -1; //The element was not found in the table

	
	result = display_connections(current->head);
	
	reset_visited(); //Put all of the visited bools back to false
	cout << endl;
	return result;
}



//This recursive call performs a depth-first traversal.
//Any vertex encountered from the chosen one is checked
//to see if the visited flag is marked.  If not, it marks
//the flag and prints the chore contained.
//After going to the terminal node, it goes back up and over, wherever
//it can move horizontally to begin another depth-first traversal.
int table::display_connections(node * current)
{
	if (!current)
	{
		return 0;
	}

	if (current->adjacent->visited == false)
	{
		cout << current->adjacent->chore << ", ";
		current->adjacent->visited =  true;
	}

	display_connections(current->adjacent->head); //Move vertically

	return display_connections(current->next) + 1; //Move horizontally
}



//This is the wrapper function for printing all of the vertices
//that form a path into the chosen vertex
int table::display_prior_connections(char * name)
{
	vertex * destination = find_vertex(name);
	vertex * begin = a_list;
	bool result;

	if (!destination) //The given vertex doesn't exist
		return 0;

	
	result = display_prior_connections(begin, destination); //Call the recursive function
	
	cout << endl;
	reset_visited();
	
	if (result)
		return 1;
	
	return -1; //No connected nodes precede the chose vertex
	
}



//Recursive call moves vertically checking to see if the path of the current vertex/element
//eventually leads to the user chosen vertex.  If so, it sends true to the other recursive function
//for it to print and move to the next element
bool table::display_prior_connections(node * current, vertex * destination)
{
	if (!current)
	{
		return false; //The path doesn't lead to the user chosen vertex
	}

	if (current->adjacent == destination)
	{
		return true; //The path does lead to the vertex
	}

	if (display_prior_connections(current->adjacent->head, destination))
	{
		return true; //This path doesn't, but another path from this vertex does
	}

	return display_prior_connections(current->next, destination); //Traverse until a path is found or no path is found
}



//Second recursive function moves through the array until a NULL entry is found
bool table::display_prior_connections(vertex * current, vertex * destination)
{
	bool result = false;

	if (display_prior_connections(current->head, destination) == true) //A path was found in the first recursive call
	{
		cout << current->chore << ", "; //Print this vertex
		result = true; //Tell the calling function that at least one preceding vertex was found
	}

	if ( (*(current + 1)).chore != NULL) //The end of the array elements with content has been reached
		display_prior_connections(++current, destination);
	
	return result;	

}	



//Resets the visited flags back to false
int table::reset_visited(void)
{
	
	vertex * current = a_list;
	vertex * last = a_list + list_size;

	while (current < last)
	{
		(*current).visited = false;
		++current;
	}

	return 1;
}



//Finds the first empty spot in the array and inserts the new chore
//If the array is full, 0 is returned
int table::insert_vertex(char * name)
{

	vertex * current = a_list;
	vertex * last = a_list + list_size;

	while (current < last)
	{
		if (!current->chore)
		{
			current->chore = new char[ strlen(name) + 1];
			strcpy(current->chore, name);
			return 1;
		}
		++current;
	}

	return 0;
}



//This inserts a new edge to the edge list of an existing vertex
int table::insert_edge(char * chore_from, char * chore_to)
{
	vertex * from = find_vertex(chore_from);
	vertex * to = find_vertex(chore_to);

	if (from && to) //If one or both of the chosen items doesn't exist, this statement will not execute
	{
		node * temp = new node;
		temp->adjacent = to;
		temp->next = from->head;
		from->head = temp;
		return 1;
	}

	return 0;
}
	
			
