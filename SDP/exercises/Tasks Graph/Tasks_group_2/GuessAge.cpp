/*
Приятелите на Интегралчо твърдят, че той е добър само
и единствено в решаването на интеграли. Той обаче иска да им
докаже противното и решава да ги впечатли с изпитание в което ще
познае годините на всички свои N приятели.
N-те приятели дават на Интегралчо M части от информация, която
да му помогне. Всяка част от информация съдържа 4 цели числа - t,
u, v и c, както следват:
- Ако t = 1, u приятеля е по-голям от v приятеля с поне c години
- Ако t = 2, u приятеля е НЕ е по-голям от v приятеля с поне c
години
Интегралчо също така знае, че всички години са цели
числа(странно, не задължително всичките положителни), както и че
годините на приятел N1 са 0.
*/

#include <iostream>
#include <climits>

#define SIZE 6
#define MAX INT_MAX
#define min(x, y) ((x) < (y) ? (x) : (y))

int graphMap[SIZE][SIZE] = {
    // vertex "to" :
    // A    B    C    D    E    F     // vertex "from" :
    {MAX, MAX, 6, 2, MAX, MAX},    // A
    {MAX, MAX, MAX, -7, MAX, MAX}, // B
    {MAX, 1, MAX, MAX, MAX, MAX},  // C
    {MAX, MAX, 11, MAX, MAX, MAX}, // D
    {15, MAX, 10, MAX, MAX, -3},   // E
    {MAX, 5, MAX, MAX, MAX, MAX}   // F
};

void print_paths(int v_begin, int dist_vector[])
{
    std::cout << "from A to " << v_begin << std::endl;
    for (int i = 0; i < SIZE; i++)
    {
        if (v_begin == i)
            continue;
        std::cout << 'A' << i;
        if (dist_vector[i] == MAX)
            std::cout << "no such path!\n";
        else
            std::cout << "weight " << dist_vector[i];
    }
}

bool find_negative_cycle(int dist_vector[])
{
    for (int i = 0; i < SIZE; i++)
        for (int j = i; j < SIZE; j++)
        {
            if (graphMap[j][i] == MAX || dist_vector[j] == MAX)
                continue;
            if (dist_vector[i] > dist_vector[j] + graphMap[j][i])
                return true;
        }
        return false;
}

void ford_shortest_paths(int v_begin)
{
    int dist_vector[SIZE];
    for(int i = 0; i < SIZE; ++i)
       dist_vector[i] = graphMap[v_begin][i];
    
    //for each vertex between i and j
    for(size_t k = 0; k < SIZE; k++)
    {
        for ( size_t i = 0; i < SIZE; i++ )
		{
			for ( size_t j = 0; j < SIZE; j++ )
			{
				if ( i == j ) continue;

				if ( graphMap[ j ][ i ] == MAX || dist_vector[ j ] == MAX ) continue;
				
				if ( dist_vector[ i ] > dist_vector[ j ] + graphMap[ j ][ i ] )
					dist_vector[ i ] = dist_vector[ j ] + graphMap[ j ][ i ];
			}
		}
	}

	if ( find_negative_cycle( dist_vector ) )
		printf( "\nthe given graph contains a negative loop!\n" );
	else
		print_paths( v_begin, dist_vector );
}

int main() {

	// run the algorithm from 'B' 
	int v_begin = 1;
	ford_shortest_paths(v_begin);
	
	// run the algorithm from 'E'
	v_begin = 4; // 'E'
	ford_shortest_paths(v_begin);
	
	// change the graph a bit, and run the algorithm again 
	printf("\nmodifying the graph to create a negative loop...\n");
	// for better understanding see the graph's visual representation
	graphMap['D' - 'A']['C' - 'A'] = -11; 
	ford_shortest_paths(v_begin);
	
	return 0;
}
