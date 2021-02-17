/*
                null.hpp

		     -- nullness --

original (c) 2021 theodoric e. stier
public domain

null checks should customize.
don't just contextually convert things
to 'bool'!

*/

#ifndef H_8F87FB07_7303_4BC3_BA0B_042BB0C726BE
#define H_8F87FB07_7303_4BC3_BA0B_042BB0C726BE

#include <ted/operator.hpp>

namespace ted
{

template<
	typename Self>
	auto is_null(
		Self &&self)
	-> decltype(
		equal(
			same(self),
			nullptr))
{
	return equal(
			same(self),
			nullptr);
}

template<
	typename Self>
	auto is_nonnull(
		Self &&self)
	-> decltype(
		unequal(
			same(self),
			nullptr))
{
	return unequal(
			same(self),
			nullptr);
}

}

#endif