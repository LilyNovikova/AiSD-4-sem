#include "stdafx.h"
#include "CppUnitTest.h"
#include"../Lab4_4_1/Dijkstra.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DijkstraTest
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(from_a_to_d)
		{
			Dijkstra roads;
			try
			{
				roads.add_link((char*)"a", (char*)"b", 1);
				roads.add_link((char*)"a", (char*)"c", 4);


				roads.add_link((char*)"b", (char*)"c", 2);
				roads.add_link((char*)"b", (char*)"d", 6);
				roads.add_link((char*)"c", (char*)"d", 3);
				roads.add_link((char*)"d", (char*)"e", 4);
				roads.add_link((char*)"c", (char*)"e", 8);

				roads.add_link((char*)"f", (char*)"a", '9');
				//roads.from_file("1.txt");
				Assert::AreEqual(6, roads.count_distance((char*)"a", (char*)"d"));
			}
			catch (runtime_error e)
			{
				Assert::IsFalse(true);
				//Assert::AreEqual(e.what(), "File not found");
			}
			catch (invalid_argument e)
			{
				Assert::IsFalse(true);
			}

		}

		TEST_METHOD(from_a_to_f)
		{
			Dijkstra roads;
			try
			{
				roads.add_link((char*)"a", (char*)"b", 1);
				roads.add_link((char*)"a", (char*)"c", 4);


				roads.add_link((char*)"b", (char*)"c", 2);
				roads.add_link((char*)"b", (char*)"d", 6);
				roads.add_link((char*)"c", (char*)"d", 3);
				roads.add_link((char*)"d", (char*)"e", 4);
				roads.add_link((char*)"c", (char*)"e", 8);

				roads.add_link((char*)"f", (char*)"a", '9');
				//roads.from_file("1.txt");
				Assert::AreEqual(-1, roads.count_distance((char*)"a", (char*)"f"));
			}
			catch (runtime_error e)
			{
				Assert::IsFalse(true);
				//Assert::AreEqual(e.what(), "File not found");
			}
			catch (invalid_argument e)
			{
				Assert::IsFalse(true);
			}

		}

		TEST_METHOD(from_a_to_a)
		{
			Dijkstra roads;
			try
			{
				roads.add_link((char*)"a", (char*)"b", 1);
				roads.add_link((char*)"a", (char*)"c", 4);


				roads.add_link((char*)"b", (char*)"c", 2);
				roads.add_link((char*)"b", (char*)"d", 6);
				roads.add_link((char*)"c", (char*)"d", 3);
				roads.add_link((char*)"d", (char*)"e", 4);
				roads.add_link((char*)"c", (char*)"e", 8);

				roads.add_link((char*)"f", (char*)"a", '9');
				//roads.from_file("1.txt");
				Assert::AreEqual(0, roads.count_distance((char*)"a", (char*)"a"));
			}
			catch (runtime_error e)
			{
				Assert::IsFalse(true);
				//Assert::AreEqual(e.what(), "File not found");
			}
			catch (invalid_argument e)
			{
				Assert::IsFalse(true);
			}

		}

		TEST_METHOD(from_a_to_nonexisting)
		{
			Dijkstra roads;
			try
			{
				roads.add_link((char*)"a", (char*)"b", 1);
				roads.add_link((char*)"a", (char*)"c", 4);


				roads.add_link((char*)"b", (char*)"c", 2);
				roads.add_link((char*)"b", (char*)"d", 6);
				roads.add_link((char*)"c", (char*)"d", 3);
				roads.add_link((char*)"d", (char*)"e", 4);
				roads.add_link((char*)"c", (char*)"e", 8);

				roads.add_link((char*)"f", (char*)"a", '9');
				//roads.from_file("1.txt");
				Assert::AreEqual(0, roads.count_distance((char*)"a", (char*)"z"));
			}
			catch (runtime_error e)
			{
				Assert::IsFalse(true);
				//Assert::AreEqual(e.what(), "File not found");
			}
			catch (invalid_argument e)
			{
				Assert::AreEqual(e.what(), "No node with this name");
			}

		}

		TEST_METHOD(from_nonexisting_to_a)
		{
			Dijkstra roads;
			try
			{
				roads.add_link((char*)"a", (char*)"b", 1);
				roads.add_link((char*)"a", (char*)"c", 4);


				roads.add_link((char*)"b", (char*)"c", 2);
				roads.add_link((char*)"b", (char*)"d", 6);
				roads.add_link((char*)"c", (char*)"d", 3);
				roads.add_link((char*)"d", (char*)"e", 4);
				roads.add_link((char*)"c", (char*)"e", 8);

				roads.add_link((char*)"f", (char*)"a", '9');
				//roads.from_file("1.txt");
				Assert::AreEqual(0, roads.count_distance((char*)"z", (char*)"a"));
			}
			catch (runtime_error e)
			{
				Assert::IsFalse(true);
				//Assert::AreEqual(e.what(), "File not found");
			}
			catch (invalid_argument e)
			{
				Assert::AreEqual(e.what(), "No node with this name");
			}

		}

		TEST_METHOD(empty)
		{
			Dijkstra roads;
			try
			{
				//roads.from_file("1.txt");
				Assert::AreEqual(0, roads.count_distance((char*)"z", (char*)"a"));
			}
			catch (runtime_error e)
			{
				Assert::AreEqual(e.what(), "The list is empty");
				
				//Assert::AreEqual(e.what(), "File not found");
			}
			catch (invalid_argument e)
			{
				Assert::IsFalse(true);
			}

		}

	};
}