/*
                atomic.h

         -- atomic operations --

original (c) 2021 theodoric e. stier
public domain

we put the atomic operations into
a reasonably customizable form. 
friendly with 'ref_obj'.
these atomic operations automatically
unwrap the reference.

*/

#ifndef H_E3B5CD65_B490_4785_8EA1_50AB09F1CEB6
#define H_E3B5CD65_B490_4785_8EA1_50AB09F1CEB6

#include <ted/ref.hpp>
#include <ted/lift.hpp>
#include <ted/memory_order.hpp>
#include <ted/pointer.hpp>

namespace ted
{

/**

`atomic_invoke` on the `args` and return
the result.

This function template controls the
iterative instantiation of
`atomic_invoke`. An atomic initiator or
composed atomic operation should
delegate to this function template
to continue unwrapping the
`AtomicObject`.

*/
template<
	typename ...Args>
	auto atomic_result(
		Args &&...args)
	noexcept -> decltype(auto)
{
	return atomic_invoke(
		same(args)...);
}

template<
	typename Object,
	typename AtomicOp,
	typename ...Args>
	auto atomic_invoke(
		std::atomic<Object> &object,
		AtomicOp &&op,
		Args &&...args)
	noexcept -> decltype(auto)
{
	return invoke(
		same(op),
		ted::address_of(object),
		same(args)...);
}

template<
	typename AtomicObject>
	auto load(
		AtomicObject &&object)
	noexcept -> decltype(auto)
{
	return ted::atomic_result(
		same(object),
		lift(atomic_load_explicit));
}

template<
	typename AtomicObject,
	typename Value>
	auto store(
		AtomicObject &&object,
		Value &&value)
	noexcept -> decltype(auto)
{
	return ted::atomic_result(
		same(object),
		lift(atomic_store_explicit),
		same(value));
}

template<
	typename AtomicObject,
	typename Value>
	auto exchange(
		AtomicObject &&object,
		Value &&value)
	noexcept -> decltype(auto)
{
	return ted::atomic_result(
		same(object),
		lift(atomic_exchange_explicit),
		same(value));
}

template<
	typename AtomicObject,
	typename Expected,
	typename Desired>
	auto compare_exchange_strong(
		AtomicObject &&object,
		Expected &&expected,
		Desired &&desired)
	noexcept -> decltype(auto)
{
	return ted::atomic_result(
		same(object),
		lift(atomic_compare_exchange_strong_explicit),
		same(expected),
		same(desired));
}

template<
	typename AtomicObject,
	typename Expected,
	typename Desired>
	auto compare_exchange_weak(
		AtomicObject &&object,
		Expected &&expected,
		Desired &&desired)
	noexcept -> decltype(auto)
{
	return ted::atomic_result(
		same(object),
		lift(atomic_compare_exchange_weak_explicit),
		same(expected),
		same(desired));
}

template<
	typename AtomicObject,
	typename Amount>
	auto fetch_add(
		AtomicObject &&object,
		Amount &&amount)
	noexcept -> decltype(auto)
{
	return ted::atomic_result(
		same(object),
		lift(atomic_fetch_add_explicit),
		same(amount));
};

template<
	typename AtomicObject,
	typename Amount>
	auto fetch_sub(
		AtomicObject &&object,
		Amount &&amount)
	noexcept -> decltype(auto)
{
	return ted::atomic_result(
		same(object),
		lift(atomic_fetch_sub_explicit),
		same(amount));
}

template<
	typename AtomicObject,
	typename Amount>
	auto fetch_and(
		AtomicObject &&object,
		Amount &&amount)
	noexcept -> decltype(auto)
{
	return ted::atomic_result(
		same(object),
		lift(atomic_fetch_and_explicit),
		same(amount));
}

template<
	typename AtomicObject,
	typename Amount>
	auto fetch_or(
		AtomicObject &&object,
		Amount &&amount)
	noexcept -> decltype(auto)
{
	return ted::atomic_result(
		same(object),
		lift(atomic_fetch_or_explicit),
		same(amount));
}

template<
	typename AtomicObject,
	typename Amount>
	auto fetch_xor(
		AtomicObject &&object,
		Amount &&amount)
	noexcept -> decltype(auto)
{
	return ted::atomic_result(
		same(object),
		lift(atomic_fetch_xor_explicit),
		same(amount));
}

}

#endif