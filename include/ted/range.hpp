/*
               range.hpp

            -- range size --

original (c) 2021 theodoric e. stier
public domain

*/

#ifndef H_1847FC0F_5AF7_46D7_B1F1_71BF191D28F2
#define H_1847FC0F_5AF7_46D7_B1F1_71BF191D28F2

#include <ted/iterator.hpp>

namespace ted
{

template<
	typename Range>
concept range = requires (
	Range ab)
{
	begin(ab);
	end(ab);
};

template<
	range Range>
	auto size(
		const Range &ab)
	noexcept -> decltype(auto)
{
	return distance(
		begin(ab),
		end(ab));
}

template<
	range Range>
	auto insert(
		Range &&ab)
	noexcept -> decltype(auto)
{
	return insert(
		end(same(ab)));
}

template<
	range Range>
	auto insert_front(
		Range &&ab)
	noexcept -> decltype(auto)
{
	return insert(
		begin(same(ab)));
}

template<
	range Range>
	auto extract(
		Range &&ab)
	noexcept -> decltype(auto)
{
	return extract(
		end(same(ab)));
}

template<
	range Range>
	auto extract_back(
		Range &&ab)
	noexcept -> decltype(auto)
{
	return extract(
		begin(same(ab)));
}

}

#endif