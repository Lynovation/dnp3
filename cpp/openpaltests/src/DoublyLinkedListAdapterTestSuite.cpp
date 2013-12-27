/**
 * Licensed to Green Energy Corp (www.greenenergycorp.com) under one or
 * more contributor license agreements. See the NOTICE file distributed
 * with this work for additional information regarding copyright ownership.
 * Green Energy Corp licenses this file to you under the Apache License,
 * Version 2.0 (the "License"); you may not use this file except in
 * compliance with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * This project was forked on 01/01/2013 by Automatak, LLC and modifications
 * may have been made to this file. Automatak, LLC licenses these modifications
 * to you under the terms of the License.
 */
#include <boost/test/unit_test.hpp>

#include <openpal/DynamicArray.h>
#include <openpal/DoublyLinkedListAdapter.h>


using namespace openpal;

BOOST_AUTO_TEST_SUITE(DoublyLinkListAdapterTestSuite)


BOOST_AUTO_TEST_CASE(CorrectInitialState)
{
	DynamicArray<DoubleListNode<int>, uint16_t> arr(3);
	DoublyLinkedListAdapter<int, uint16_t> list(arr.ToIndexable());
	
	BOOST_REQUIRE(list.IsEmpty());
	BOOST_REQUIRE(!list.IsFull());
	BOOST_REQUIRE_EQUAL(0, list.Size());
}

BOOST_AUTO_TEST_CASE(AddsUntilFull)
{
	DynamicArray<DoubleListNode<int>, uint16_t> arr(3);
	DoublyLinkedListAdapter<int, uint16_t> list(arr.ToIndexable());
	
	auto one = list.Add(1);
	auto two = list.Add(2);
	auto three = list.Add(3);
	
	BOOST_REQUIRE_EQUAL(1, one->value);
	BOOST_REQUIRE_EQUAL(2, two->value);
	BOOST_REQUIRE_EQUAL(3, three->value);
	BOOST_REQUIRE(list.IsFull());

	// adding to a full list returns a nullptr
	BOOST_REQUIRE(nullptr == list.Add(4));	
}

BOOST_AUTO_TEST_CASE(CanRemoveHead)
{
	DynamicArray<DoubleListNode<int>, uint16_t> arr(3);
	DoublyLinkedListAdapter<int, uint16_t> list(arr.ToIndexable());
	
	auto one = list.Add(1);
	auto two = list.Add(2);
	auto three = list.Add(3);
	
	list.Remove(one);

	BOOST_REQUIRE_EQUAL(2, list.Size());

	auto four = list.Add(4); 

	BOOST_REQUIRE_EQUAL(four, one); // these pointers should be the same
}

BOOST_AUTO_TEST_CASE(CanRemoveTail)
{
	DynamicArray<DoubleListNode<int>, uint16_t> arr(3);
	DoublyLinkedListAdapter<int, uint16_t> list(arr.ToIndexable());
	
	auto one = list.Add(1);
	auto two = list.Add(2);
	auto three = list.Add(3);
	
	list.Remove(three);

	BOOST_REQUIRE_EQUAL(2, list.Size());

	auto four = list.Add(4); 

	BOOST_REQUIRE_EQUAL(four, three); // these pointers should be the same
}

BOOST_AUTO_TEST_CASE(CanRemoveMiddle)
{
	DynamicArray<DoubleListNode<int>, uint16_t> arr(3);
	DoublyLinkedListAdapter<int, uint16_t> list(arr.ToIndexable());
	
	auto one = list.Add(1);
	auto two = list.Add(2);
	auto three = list.Add(3);
	
	list.Remove(two);

	BOOST_REQUIRE_EQUAL(2, list.Size());

	auto four = list.Add(4); 

	BOOST_REQUIRE_EQUAL(four, two); // these pointers should be the same
}

BOOST_AUTO_TEST_CASE(CanIterateOverValues)
{
	DynamicArray<DoubleListNode<int>, uint16_t> arr(3);
	DoublyLinkedListAdapter<int, uint16_t> list(arr.ToIndexable());
	
	list.Add(1);
	list.Add(2);
	list.Add(3);
	
	auto iter = list.Iterate();

	for(int i=1; i < 4; ++i)
	{
		BOOST_REQUIRE(iter.HasNext());
		BOOST_REQUIRE_EQUAL(i, iter.Next()->value);
	}

	BOOST_REQUIRE(!iter.HasNext());
}




BOOST_AUTO_TEST_SUITE_END()
