/*
              iterator.hpp

      -- iterator manipulators --

original (c) 2021 theodoric e. stier
public domain

instead of directly using the operator
aliases, we use these special names
when manipulating iterators so that they
can be differently customized for 
different contexts.

*/

#ifndef H_8F9F2391_A5FE_4676_8C99_160E438FEC85
#define H_8F9F2391_A5FE_4676_8C99_160E438FEC85

#include <ted/address.hpp>
#include <ted/is_truthy.hpp>
#include <ted/operator.hpp>

#include <ted/assuming.hpp>
#include <ted/same.hpp>

namespace ted::iterator
{

template<
	typename Begin,
	typename Caret>
	auto distance(
		Begin &&begin,
		Caret &&caret)
	noexcept -> decltype(
		minus(
			same(caret), 
			same(begin)))
{
	const auto ordered = negate(
		less(
			caret,
			begin));

	assuming(ordered)
	{
		return minus(
			same(caret),
			same(begin));
	}
}

template<
	typename Caret>
	auto peek(
		Caret &&caret)
	noexcept -> decltype(
		obj(
			same(caret)))
{
	const auto non_null = is_truthy(
		caret);

	assuming(non_null)
	{
		return obj(
			same(caret));
	}
}

template<
	typename Caret>
	auto advance(
		Caret &&caret)
	noexcept -> decltype(
		increment(
			same(caret)))
{
	return increment(
		same(caret));
}

}

#include <ted/nosame.hpp>
#include <ted/noassuming.hpp>

#endif