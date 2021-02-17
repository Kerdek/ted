/*
                span.hpp

               -- span --

original (c) 2021 theodoric e. stier
public domain

our favorite range.

*/

#ifndef H_8FCD914D_66A0_4425_9AB3_E94964376165
#define H_8FCD914D_66A0_4425_9AB3_E94964376165

#include <ted/assuming.hpp>
#include <ted/operator.hpp>
#include <ted/same.hpp>

namespace ted::span
{

template<
	typename Begin,
	typename End>
	struct span_t
{
	Begin a;
	End b;
};

template<
	typename Span>
	constexpr auto begin(
		Span &&self)
	noexcept -> decltype(auto)
{
	return (same(self).a);
}

template<
	typename Span>
	constexpr auto end(
		Span &&self)
	noexcept -> decltype(auto)
{
	return (same(self).b);
}

}

namespace ted
{

template<
	typename Begin,
	typename End>
	constexpr auto make_span(
		Begin a,
		End b)
	noexcept -> span::span_t<
		Begin,
		End>
{
	assuming(negate(less(b, a)))
	{
		return
		{
			a,
			b
		};
	}
}

}

#endif