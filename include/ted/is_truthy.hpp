/*
              is_truthy.hpp

		    -- truthiness --

original (c) 2021 theodoric e. stier
public domain

Truthiness checks should customize.
Don't just contextually convert things
to 'bool'.

Customizations of 'is_truthy'
must return a type which is contextually
convertible to bool.

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
	-> decltype(
		static_cast<bool>(
			same(self)))
{
	return static_cast<bool>(
		same(self));
}

}

#include <ted/nosame.hpp>

#endif