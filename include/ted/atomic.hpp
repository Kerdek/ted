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
delegate to `atomic_result` to continue
unwrapping the `AtomicObject`.

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

/**

Get the result 

*/
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

constexpr auto atomic_load = lift(
	atomic_load_explicit);

template<
	typename AtomicObject>
	auto load(
		AtomicObject &&object)
	noexcept -> decltype(
		ted::atomic_result(
			same(object),
			atomic_load))
{
	return ted::atomic_result(
		same(object),
		atomic_load);
}

constexpr auto atomic_store = lift(
	atomic_store_explicit);

template<
	typename AtomicObject,
	typename Value>
	auto store(
		AtomicObject &&object,
		Value &&value)
	noexcept -> decltype(
		ted::atomic_result(
			same(object),
			atomic_store,
			same(value)))
{
	return ted::atomic_result(
		same(object),
		atomic_store,
		same(value));
}

constexpr auto atomic_exchange = lift(
	atomic_exchange_explicit);

template<
	typename AtomicObject,
	typename Value>
	auto exchange(
		AtomicObject &&object,
		Value &&value)
	noexcept -> decltype(
		ted::atomic_result(
			same(object),
			atomic_exchange,
			same(value)))
{
	return ted::atomic_result(
		same(object),
		atomic_exchange,
		same(value));
}

constexpr auto atomic_compare_exchange_strong = lift(
	atomic_compare_exchange_strong_explicit);

template<
	typename AtomicObject,
	typename Expected,
	typename Desired>
	auto compare_exchange_strong(
		AtomicObject &&object,
		Expected &&expected,
		Desired &&desired)
	noexcept -> decltype(
		ted::atomic_result(
			same(object),
			atomic_compare_exchange_strong,
			same(expected),
			same(desired)))
{
	return ted::atomic_result(
		same(object),
		atomic_compare_exchange_strong,
		same(expected),
		same(desired));
}

constexpr auto atomic_compare_exchange_weak = lift(
	atomic_compare_exchange_weak_explicit);

template<
	typename AtomicObject,
	typename Expected,
	typename Desired>
	auto compare_exchange_weak(
		AtomicObject &&object,
		Expected &&expected,
		Desired &&desired)
	noexcept -> decltype(
		ted::atomic_result(
			same(object),
			atomic_compare_exchange_weak,
			same(expected),
			same(desired)))
{
	return ted::atomic_result(
		same(object),
		atomic_compare_exchange_weak,
		same(expected),
		same(desired));
}

constexpr auto atomic_fetch_add = lift(
	atomic_fetch_add_explicit);

template<
	typename AtomicObject,
	typename Amount>
	auto fetch_add(
		AtomicObject &&object,
		Amount &&amount)
	noexcept -> decltype(
		ted::atomic_result(
			same(object),
			atomic_fetch_add,
			same(amount)))
{
	return ted::atomic_result(
		same(object),
		atomic_fetch_add,
		same(amount));
};

constexpr auto atomic_fetch_sub = lift(
	atomic_fetch_sub_explicit);

template<
	typename AtomicObject,
	typename Amount>
	auto fetch_sub(
		AtomicObject &&object,
		Amount &&amount)
	noexcept -> decltype(
		ted::atomic_result(
			same(object),
			atomic_fetch_sub,
			same(amount)))
{
	return ted::atomic_result(
		same(object),
		atomic_fetch_sub,
		same(amount));
}

constexpr auto atomic_fetch_and = lift(
	atomic_fetch_and_explicit);

template<
	typename AtomicObject,
	typename Amount>
	auto fetch_and(
		AtomicObject &&object,
		Amount &&amount)
	noexcept -> decltype(
		ted::atomic_result(
			same(object),
			atomic_fetch_and,
			same(amount))
	)
{
	return ted::atomic_result(
		same(object),
		atomic_fetch_and,
		same(amount));
}

constexpr auto atomic_fetch_or = lift(
	atomic_fetch_or_explicit);

template<
	typename AtomicObject,
	typename Amount>
	auto fetch_or(
		AtomicObject &&object,
		Amount &&amount)
	noexcept -> decltype(
		ted::atomic_result(
			same(object),
			atomic_fetch_or,
			same(amount))
	)
{
	return ted::atomic_result(
		same(object),
		atomic_fetch_or,
		same(amount));
}

constexpr auto atomic_fetch_xor = lift(
	atomic_fetch_xor_explicit);

template<
	typename AtomicObject,
	typename Amount>
	auto fetch_xor(
		AtomicObject &&object,
		Amount &&amount)
	noexcept -> decltype(
		ted::atomic_result(
			same(object),
			atomic_fetch_xor,
			same(amount)))
{
	return ted::atomic_result(
		same(object),
		atomic_fetch_xor,
		same(amount));
}

}

#endif