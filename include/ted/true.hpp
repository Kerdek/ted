/*
                true.hpp

		    -- truthiness --

original (c) 2021 theodoric e. stier
public domain

truthiness checks should customize.
don't just contextually convert things
to 'bool'!

*/

#ifndef H_B05A95C9_4F53_4789_B523_4CEDDD640ECE
#define H_B05A95C9_4F53_4789_B523_4CEDDD640ECE

#include <ted/same.hpp>
#include <ted/operator.hpp>

namespace ted
{

template<
	typename Object>
	auto is_truthy(
		Object &&object)
	-> decltype(
		equal(
			same(object),
			true))
{
	return equal(
		same(object),
		true);
}

template<
	typename Object>
	auto is_falsy(
		Object &&object)
	-> decltype(
		equal(
			same(object),
			false))
{
	return equal(
		same(object),
		false);
}

}

#endif