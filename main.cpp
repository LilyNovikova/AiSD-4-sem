#include "Dijkstra.h"

int main()
{
	Dijkstra road_map;
	/*road_map.add_link((char*)"a", (char*)"b", 1);
	road_map.add_link((char*)"a", (char*)"c", 4);


	road_map.add_link((char*)"b", (char*)"c", 2);
	road_map.add_link((char*)"b", (char*)"d", 6);
	road_map.add_link((char*)"c", (char*)"d", 3);
	road_map.add_link((char*)"d", (char*)"e", 4);
	road_map.add_link((char*)"c", (char*)"e", 8);

	road_map.add_link((char*)"f", (char*)"a", '9');*/
	try
	{
		road_map.from_file((char*)"1.txt");
	}
	catch (invalid_argument e)
	{
		cout << e.what();
	}
	catch (runtime_error e)
	{
		cout << e.what();
	}
/*	road_map.find_ways_from_departure((char*)"a");

	road_map.show_result();
	cout << endl << "Distance from start to 'd' = " << road_map.get_distance((char*)"f") << endl;*/
	cout << road_map.count_distance((char*)"a", (char*)"z")<<endl;

	system("pause");
	return 0;
}
