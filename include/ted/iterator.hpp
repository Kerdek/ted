/*
              iterator.hpp

       -- iterator operations --

original (c) 2021 theodoric e. stier
public domain

instead of directly using the operator
aliases, we use these special names
when manipulating iterators so that they
can be differently customized for 
different contexts.

automatically unwraps reference
wrappers with 'obj'.

*/

#ifndef H_8F9F2391_A5FE_4676_8C99_160E438FEC85
#define H_8F9F2391_A5FE_4676_8C99_160E438FEC85

#include <ted/assuming.hpp>
#include <ted/null.hpp>

namespace ted
{

template<
	typename Lhs,
	typename Rhs>
	auto distance(
		Lhs &&a,
		Rhs &&b)
	noexcept -> decltype(auto)
{
	assuming(less_equal(a, b))
	{
		return minus(
			same(b),
			same(a));
	}
}

template<
	typename Iterator>
	auto peek(
		Iterator &&it)
	noexcept -> decltype(auto)
{
	assuming(is_nonnull(it))
	{
		return follow(
			same(it));
	}
}

template<
	typename Iterator>
	auto advance(
		Iterator &&it)
	noexcept -> decltype(auto)
{
	increment(
		same(it));
}

/*
Stream extraction adapter for iterators.
*/
template<
	typename Iterator>
	auto extract(
		Iterator &&it)
	noexcept -> decltype(
		ted::peek(
			increment(
				same(it))))
{
	return ted::peek(
		increment(
			same(it)));
}

/*
Stream extraction adapter for iterators.
*/
template<
	typename Iterator>
	auto extract_reverse(
		Iterator &&it)
	noexcept -> decltype(
		ted::peek(
			decrement(
				same(it))))
{
	return ted::peek(
		decrement(
			same(it)));
}

/*
Stream insertion adapter for iterators.
*/
template<
	typename Iterator,
	typename Object>
	auto insert(
		Iterator &&it,
		Object &&object)
	noexcept -> decltype(
		ted::peek(
			increment(
				same(it))))
{
	return assign(
		ted::peek(
			increment(
				same(it))),
		same(object));
}

/*
Stream insertion adapter for iterators.
*/
template<
	typename Iterator,
	typename Object>
	auto insert_reverse(
		Iterator &&it,
		Object &&object)
	noexcept -> decltype(
		ted::peek(
			decrement(
				same(it))))
{
	return assign(
		ted::peek(
			decrement(
				same(it))),
		same(object));
}

}

#endif