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

		//


		////////////
		//  List  //
		////////////

		//push_back
		TEST_METHOD(list_push_back_with_empty_list)
		{
			int item = 2;
			List<int> list = List<int>();
			list.push_back(item);
			Assert::AreEqual(item, list.at(list.get_size()));
		}
		TEST_METHOD(list_push_back)
		{
			int item = 2,
				new_item = 3;
			List<int> list = List<int>();
			list.push_back(item);
			list.push_back(new_item);
			Assert::AreEqual(new_item, list.at(list.get_size()));
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
	};
}