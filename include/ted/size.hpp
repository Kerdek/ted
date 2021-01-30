/*
                size.hpp

            -- range size --

original (c) 2021 theodoric e. stier
public domain

instead of directly using the operator
aliases, we use these special names
when manipulating iterators so that they
can be differently customized for 
different contexts.

*/

#ifndef H_1847FC0F_5AF7_46D7_B1F1_71BF191D28F2
#define H_1847FC0F_5AF7_46D7_B1F1_71BF191D28F2

#include <ted/iterator.hpp>

namespace ted
{

template<
	typename Range>
	auto size(
		Range &self)
	noexcept -> decltype(
		distance(
		begin(self),
		end(self)))
{
	return distance(
		begin(self),
		end(self));
}

}

#endif