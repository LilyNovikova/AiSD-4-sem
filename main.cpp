#include "FordFulkerson.h"

int main()
{
	Web web;
	/*web.add_edge('s', 'a', 5);
	web.add_edge('s', 'b', 2);
	web.add_edge('a', 'b', 2);
	web.add_edge('a', 'c', 3);
	web.add_edge('b', 'd', 4);
	web.add_edge('c', 'd', 1);
	web.add_edge('d', 't', 5);
	web.add_edge('c', 't', 2);
	*/

	try
	{
	/*web.add_edge('s', 'o', 3);
	web.add_edge('s', 'p', 3);
	web.add_edge('o', 'p', 2);
	web.add_edge('o', 'q', 3);
	web.add_edge('p', 'r', 2);
	web.add_edge('q', 'r', 4);
	web.add_edge('q', 't', 2);
	web.add_edge('r', 't', 3);*/
	web.from_file();
	web.FordFulkerson();
	cout<<web.summ_flow();
	if (web.summ_flow() == 5) cout << "ok";
	else cout << "((";
	}
	catch (runtime_error e)
	{
		cout << e.what();
	}
	catch (invalid_argument e)
	{
		cout << e.what();
	}

	/*web.show_edges();
	web.show_in_width();

	web.EdmondsKarp();

	cout << endl << endl;
	web.show_in_width();
	web.show_edges();

	cout << endl << ":: " << web.summ_flow() << endl;*/
	
/*	Web web;
	

	
	
	*/
	
	//Assert::AreEqual(5, web.summ_flow());

	system("pause");
	return 0;

}