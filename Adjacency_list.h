#ifndef ADJACENTSCHMACENT
#define ADJACENTSCHMACENT

/*
This is the data structure that handles the graph ADT.
It is implemented with an array of linear linked lists.
Each element in the array is a vertex, each LLL contains the edges connected to each vertex.
There is also a visited flag to be used by some of the functions.

INPUT: Vertices (new chores) to add, edges (connections between chores) to add
INPUT: Names (char *) to search for and display functions with.

OUTPUT: Vertices (chores)
*/

struct vertex
{
	char * chore;
	struct node * head;
	bool visited;
};




struct node
{
	vertex * adjacent;
	node * next;
};


class table
{
	public:
		table(int size);
		~table();

		//Accessor functions
		vertex * find_vertex(char * name);		
		int display_connections(char * name);	
		int display_prior_connections(char * name);

		//Mutator functions
		int reset_visited(void);
		int insert_vertex(char * name);
		int insert_edge(char * chore_from, char * chore_to);


	private:
		//Recersive Accessor
		int display_connections(node * current);
		bool display_prior_connections(node * current, vertex * destination);
		bool display_prior_connections(vertex * current, vertex * destination);

		int list_size;
		vertex * a_list;

};


#endif
