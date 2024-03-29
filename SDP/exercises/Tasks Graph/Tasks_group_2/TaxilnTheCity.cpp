/*След като Интегралчо се е доказал в познаването на
години на всички свои N приятели(в частност в намирането на
най-къс път в насочен тегловен граф). Той е поканен на гости на
всеки един от приятелите му и за да не се бави с градски транспорт,
той пътува с такси. Той сам насочва таксиметровия шофьор, за да
минимизира парите необходими да обиколи града и да посети
всички N приятели. Преди да се качи в таксито Интегралчо си е
пуснал алгоритъм, който да му сметне колко минималната цена за
таксито, така че да обиколи всичките си приятели. Какъв е
алгоритъма който е използвал, ако знаете че цената на таксито е
0.95лв на километър пробег?*/

/*******************************************************************************
* This file is part of the "Data structures and algorithms" course. FMI 2018/19 
*******************************************************************************/

/**
* @file   floyd-warshall_spp.cpp
* @author Ivan Filipov
* @date   01.2019
* @brief  Finding the shortest path from each vertex to all others, using Floyd-Warshall's algorithm.
*
* @see https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm
* @note Written in plain C.
*
* Difference from Dijkstra - edges can also have negative weights, solves all-to-all (SPP).
*/

#include <stdio.h> // printf(), putchar()
#include <climits>
/// graph matrix size
#define SIZE 6 
/// "no path" constant, should be maximum INT_MAX / 2
#define MAX INT_MAX
/// helper marco for finding minimum of two numbers
#define min(x, y) ((x) < (y)) ? (x) : (y)

/// the graph is represented as weighing matrix
int graph[SIZE][SIZE] = {
	// vertex "to" :
	// A    B    C    D     E      F     // vertex "from" :
	{ MAX,	7 ,  6  ,  2  ,   9 ,  1  }, // A
	{ 7	 , MAX,  6  ,  1  ,  11 ,  3  }, // B
	{ 6  ,	6 , MAX ,  7  ,   2 ,  9  }, // C
	{ 2  , 1  ,  7  , MAX ,   5 , 10  }, // D
	{ 9  , 11 ,  2  ,  5  , MAX ,  1  }, // E
	{ 1  ,  3 ,  9  , 10  ,   1 , MAX }  // F
};

/// simply outputs info about all found paths
void print_paths() {

	printf("\nall paths with their weights:\n");
	for (size_t i = 0; i < SIZE; i++) {
		printf("from %c ", 'A' + i);

		for (size_t j = 0; j < SIZE; j++)
			if (graph[i][j] != MAX)
				printf("[ to %c : %d ]", 'A' + j, graph[i][j]);

		putchar('\n');
	}
}

/**
* @brief Runs Floyd-Warshall'salgorithm in the given graph.
*
* @note Outputs the path's weights into the same weighting matrix
* @note Time complexity : O(n^3)
*/
void floyd_shortest_paths() {

	for (size_t k = 0; k < SIZE; k++)           // for each vertex
		for (size_t i = 0; i < SIZE; i++)       // between i
			for (size_t j = 0; j < SIZE; j++) { // and j
												// don't optimize path from vertex to itself
				if (i == j) continue;
				// if there is no edge from i to k or from k to j skip this step
				if (graph[i][k] == MAX || graph[k][j] == MAX) continue;
				// remember the old value, debug purpose only
				int old = graph[i][j];
				// try to optimize the path
				graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
				// debug only
				if (old != graph[i][j]) {
					printf("optimizing path from %c to %c through %c (%d->%d)\n", 
						'A' + i, 'A' + j, 'A' + k, old, graph[i][j]);
				}
			}
}

int main()
{

	// run the algorithm
	floyd_shortest_paths();

	// print the info about all paths
	print_paths();

	return 0;
}