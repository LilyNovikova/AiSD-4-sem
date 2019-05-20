#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AISD_cours/FordFulkerson.h"
//#include "../UnitTest1/text.txt"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(example_from_task)
		{
			Web web;
			web.add_edge('s', 'o', 3);
			web.add_edge('s', 'p', 3);
			web.add_edge('o', 'p', 2);
			web.add_edge('o', 'q', 3);
			web.add_edge('p', 'r', 2);
			web.add_edge('q', 'r', 4);
			web.add_edge('q', 't', 2);
			web.add_edge('r', 't', 3);

			web.FordFulkerson();
			Assert::AreEqual(5, web.summ_flow());
		}

		TEST_METHOD(example_wiki)
		{
			Web web;
			web.add_edge('s', 'a', 5);
			web.add_edge('s', 'b', 2);
			web.add_edge('a', 'b', 2);
			web.add_edge('a', 'c', 3);
			web.add_edge('b', 'd', 4);
			web.add_edge('c', 'd', 1);
			web.add_edge('d', 't', 5);
			web.add_edge('c', 't', 2);

			web.FordFulkerson();
			Assert::AreEqual(7, web.summ_flow());
		}

		TEST_METHOD(no_source)
		{
			try
			{
				Web web;
				web.add_edge('o', 'p', 2);
				web.add_edge('o', 'q', 3);
				web.add_edge('p', 'r', 2);
				web.add_edge('q', 'r', 4);
				web.add_edge('q', 't', 2);
				web.add_edge('r', 't', 3);

				web.FordFulkerson();
			}
			catch (runtime_error e)
			{
				Assert::AreEqual(e.what(), "Source not found");
			}
		}

		TEST_METHOD(no_sink)
		{
			try
			{
				Web web;
				web.add_edge('s', 'a', 5);
				web.add_edge('s', 'b', 2);
				web.add_edge('o', 'p', 2);
				web.add_edge('o', 'q', 3);
				web.add_edge('p', 'r', 2);
				web.add_edge('q', 'r', 4);

				web.FordFulkerson();
			}
			catch (runtime_error e)
			{
				Assert::AreEqual(e.what(), "Sink not found");
			}
		}

		TEST_METHOD(no_way)
		{
			Web web;
			web.add_edge('s', 'a', 5);
			web.add_edge('b', 't', 2);
			try
			{
				web.FordFulkerson();
			}
			catch (runtime_error e)
			{
				Assert::AreEqual(e.what(), "Can't find way from source to sink");
			}
		}

		TEST_METHOD(existing_edge)
		{
			Web web;
			web.add_edge('s', 'a', 5);
			try
			{
				web.add_edge('s', 'a', 5);
			}
			catch (invalid_argument e)
			{
				Assert::AreEqual(e.what(), "Trying add an existing edge");
			}
		}

		TEST_METHOD(zero_bandwidth)
		{
			Web web;
			web.add_edge('s', 'a', 5);
			try
			{
				web.add_edge('s', 'b', 0);
			}
			catch (invalid_argument e)
			{
				Assert::AreEqual(e.what(), "Trying to add edge with bandwidth less 1");
			}
		}

		TEST_METHOD(loop_edge)
		{
			Web web;
			web.add_edge('s', 'a', 5);
			try
			{
				web.add_edge('s', 's', 5);
			}
			catch (invalid_argument e)
			{
				Assert::AreEqual(e.what(), "Trying to add loop edge");
			}
		}

	};
}