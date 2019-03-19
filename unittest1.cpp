#include "stdafx.h"
#include "CppUnitTest.h"
//list class
#include "../Lab4_1/List.h"
//node class
#include "../Lab4_1/Node.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
		//exceptions
	public:

		////////////
		//  Node  //
		////////////

		//constructor
		TEST_METHOD(node_constructor_with_char)
		{
			char item = 'a';
			Node<char> node = Node<char>(item);
			Assert::AreEqual(item, node.get_item());
		}

		TEST_METHOD(node_constructor_with_int)
		{
			int item = 2;
			Node<int> node = Node<int>(item);
			Assert::AreEqual(item, node.get_item());
		}


		////////////
		//  List  //
		////////////

		//at
		TEST_METHOD(list_at)
		{
			List<int> list = List<int>();
			list.push_back(0);
			list.push_back(1);
			Assert::AreEqual(1, list.at(1));
		}

		//push_back
		TEST_METHOD(list_push_back_with_empty_list)
		{
			List<int> list = List<int>();
			list.push_back(2);
			Assert::AreEqual(2, list.at(list.get_size() - 1));
		}
		
		TEST_METHOD(list_push_back)
		{
			List<int> list = List<int>();
			list.push_back(1);
			list.push_back(2);
			Assert::AreEqual(2, list.at(list.get_size() - 1));
		}

		//push_front
		TEST_METHOD(list_push_front_with_empty_list)
		{
			int item = 2;
			List<int> list = List<int>();
			list.push_front(item);
			Assert::AreEqual(item, list.at(0));
		}

		TEST_METHOD(list_push_front)
		{
			int item = 2,
				new_item = 3;
			List<int> list = List<int>();
			list.push_front(item);
			list.push_front(new_item);
			Assert::AreEqual(new_item, list.at(0));
		}

		//pop_back
		TEST_METHOD(list_pop_back)
		{
			List<int> list = List<int>();
			list.push_back(1);
			list.push_back(2);
			list.push_back(3);
			list.push_back(4);
			list.pop_back();
			list.push_back(5);
			Assert::AreEqual(5, list.at(3));
		}
		
		TEST_METHOD(list_pop_back_with_empty_list)
		{
			List<int> list = List<int>();
			list.push_back(1);
			list.push_back(2);
			list.push_back(3);
			list.push_back(4);
			try
			{
				list.pop_back();
			}
			catch (std::out_of_range e)
			{
				Assert::AreEqual("You tried to delete an item from empty list", e.what());
			}
		}

		//pop_front
		TEST_METHOD(list_pop_front)
		{
			List<int> list = List<int>();
			list.push_back(1);
			list.push_back(2);
			list.push_back(3);
			list.push_back(4);
			list.pop_front();
			list.push_front(5);
			Assert::AreEqual(5, list.at(0));
		}

		TEST_METHOD(list_pop_front_with_empty_list)
		{
			List<int> list;
			try
			{
				list.pop_front();
			}
			catch (std::out_of_range e)
			{
				Assert::AreEqual("You tried to delete an item from empty list", e.what());
			}
		}
		
		//insert
		TEST_METHOD(list_insert_front)
		{
			List<int> list = List<int>();
			list.push_back(1);
			list.push_back(2);
			list.push_back(3);
			list.push_back(4);
			list.insert(10, 0);
			Assert::AreEqual(10, list.at(0));
		}

		TEST_METHOD(list_insert_back)
		{
			List<int> list = List<int>();
			list.push_back(1);
			list.push_back(2);
			list.push_back(3);
			list.push_back(4);
			list.insert(10, 3);
			Assert::AreEqual(10, list.at(3));
		}

		TEST_METHOD(list_insert)
		{
			List<int> list = List<int>();
			list.push_back(1);
			list.push_back(2);
			list.push_back(3);
			list.push_back(4);
			list.insert(10, 2);
			Assert::AreEqual(10, list.at(2));
		}

		TEST_METHOD(list_insert_out_of_range)
		{
			List<int> list = List<int>();
			list.push_back(1);
			list.push_back(2);
			list.push_back(3);
			list.push_back(4);
			try
			{
				list.insert(10, 10);
			}
			catch (std::out_of_range e)
			{
				Assert::AreEqual("Index is greater than list size", e.what());
			}
		}

		TEST_METHOD(list_insert_with_empty_list)
		{
			List<int> list = List<int>();
			list.insert(10, 0);
			Assert::AreEqual(10, list.at(0));
		}

		TEST_METHOD(list_insert_with_empty_list_and_not_zero_index)
		{
			List<int> list = List<int>();
			list.insert(10, 3);
			Assert::AreEqual(10, list.at(0));
		}

		//remove
		TEST_METHOD(list_remove)
		{
			List<int> list = List<int>();
			list.push_back(1);
			list.push_back(2);
			list.push_back(3);
			list.push_back(4);
			list.remove(2);
			list.insert(10, 2);
			Assert::AreEqual(10, list.at(2));
		}

		TEST_METHOD(list_remove_front)
		{
			List<int> list = List<int>();
			list.push_back(1);
			list.push_back(2);
			list.push_back(3);
			list.push_back(4);
			list.insert(10, 0);
			Assert::AreEqual(10, list.at(0));
		}

		TEST_METHOD(list_remove_back)
		{
			List<int> list = List<int>();
			list.push_back(1);
			list.push_back(2);
			list.push_back(3);
			list.push_back(4);
			list.insert(10, 3);
			Assert::AreEqual(10, list.at(3));
		}

		TEST_METHOD(list_remove_out_of_range)
		{
			List<int> list = List<int>();
			list.push_back(1);
			list.push_back(2);
			list.push_back(3);
			list.push_back(4);
			try
			{
				list.remove(10);
			}
			catch (std::out_of_range e)
			{
				Assert::AreEqual("Index is greater than list size", e.what());
			}
		}

		TEST_METHOD(list_remove_out_of_range_with_empty_list)
		{
			List<int> list = List<int>();
			try
			{
				list.remove(0);
			}
			catch (std::out_of_range e)
			{
				Assert::AreEqual("You tried to remove an item from empty list", e.what());
			}
		}

		//get_size
		TEST_METHOD(list_get_size)
		{
			List<int> list;
			list.push_back(1);
			list.push_back(2);
			list.push_back(3);
			list.push_back(4);
			Assert::IsTrue(list.get_size() == 4);
		}

		TEST_METHOD(list_get_size_with_empty_list)
		{
			List<int> list;
			Assert::IsTrue(list.get_size() == 0);
		}

		//clear
		TEST_METHOD(list_clear)
		{
			List<int> list;
			list.push_back(1);
			list.push_back(2);
			list.push_back(3);
			list.push_back(4);
			list.clear();
			Assert::IsTrue(list.is_empty());
		}

		TEST_METHOD(list_clear_with_empty_list)
		{
			List<int> list;
			list.clear();
			Assert::IsTrue(list.is_empty());
		}

		//set
		TEST_METHOD(list_set)
		{
			List<int> list;
			list.push_back(1);
			list.push_back(2);
			list.push_back(3);
			list.push_back(4);
			list.set(10, 2);
			Assert::AreEqual(10, list.at(2));
		}

		TEST_METHOD(list_set_out_of_range)
		{
			List<int> list;
			list.push_back(1);
			list.push_back(2);
			list.push_back(3);
			list.push_back(4);
			try
			{
				list.set(10, 10);
			}
			catch (std::out_of_range e)
			{
				Assert::AreEqual("Index is greater than list size", e.what());
			}
		}

		TEST_METHOD(list_set_out_of_range_with_empty_list)
		{
			List<int> list;
			try
			{
				list.set(10, 0);
			}
			catch (std::out_of_range e)
			{
				Assert::AreEqual("Index is greater than list size", e.what());
			}
		}
		
		//is_empty
		TEST_METHOD(list_is_empty)
		{
			List<int> list;
			Assert::IsTrue(list.is_empty());
		}
	};
}