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

namespace ted
{

template<
	typename Self>
	auto is_truthy(
		Self &&self)
	-> decltype(auto)
{
	return equal(
		same(self),
		true);
}

template<
	typename Self>
	auto is_falsy(
		Self &&self)
	-> decltype(auto)
{
	return equal(
		same(self),
		false);
}

}

#endif