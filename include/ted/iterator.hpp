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

#include <ted/assuming.hpp>
#include <ted/null.hpp>
#include <ted/operator.hpp>
#include <ted/pointer.hpp>
#include <ted/same.hpp>

namespace ted
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
		follow(
			same(caret)))
{
	const auto non_null = is_nonnull(
		caret);

	assuming(non_null)
	{
		return follow(
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

#endif