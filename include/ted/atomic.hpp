/*
                atomic.h

         -- atomic operations --

original (c) 2021 theodoric e. stier
public domain

*/

#ifndef H_B1B36C5A_F4DE_46A0_8458_97B7475C9851
#define H_B1B36C5A_F4DE_46A0_8458_97B7475C9851

#include <ted/memory_order.hpp>
#include <ted/pointer.hpp>
#include <ted/operator.hpp>
#include <ted/lift.hpp>

#include <atomic>

namespace ted
{

template<
	typename Scalar,
	typename Operation,
	typename ...Args>
auto atomic_result(
	std::atomic<
		Scalar> &x,
	Operation &&f,
	Args &&...y)
noexcept -> decltype(auto)
{
	using ted::invoke;
	return invoke(
		same(f),
		ted::address_of(x),
		same(y)...);
}

template<
	typename Atomic>
struct fenced
{
	Atomic x;
	memory_order o;
};

template<
	typename Atomic,
	typename Operation,
	typename ...Args>
auto atomic_result(
	fenced<
		Atomic> x,
	Operation &&f,
	Args &&...y)
noexcept -> decltype(auto)
{
	return atomic_result(
		x.x,
		same(f),
		same(y)...,
		x.o);
}

template<
	typename Atomic>
constexpr
auto fence(
	fenced<
		Atomic> x,
	memory_order o)
noexcept -> fenced<
	fenced<
		Atomic>>
{
	return { x, o };
}

template<
	typename Scalar>
constexpr
auto fence(
	std::atomic<
		Scalar> &x,
	memory_order o)
noexcept -> fenced<
	std::atomic<
		Scalar> &>
{
	return { x, o };
}

template<
	typename Atomic>
constexpr
auto relaxed(
	Atomic &&x)
noexcept -> decltype(auto)
{
	return fence(
		x,
		memory_order::relaxed);
}

template<
	typename Atomic>
constexpr
auto acquire(
	Atomic &&x)
noexcept -> decltype(auto)
{
	return fence(
		x,
		memory_order::acquire);
}

template<
	typename Atomic>
constexpr
auto release(
	Atomic &&x)
noexcept -> decltype(auto)
{
	return fence(
		x,
		memory_order::release);
}

template<
	typename Atomic>
constexpr
auto acq_rel(
	Atomic &&x)
noexcept -> decltype(auto)
{
	return fence(
		x,
		memory_order::acq_rel);
}

template<
	typename Atomic>
constexpr
auto seq_cst(
	Atomic &&x)
noexcept -> decltype(auto)
{
	return fence(
		x,
		memory_order::seq_cst);
}

template<
	typename Atomic>
auto load(
	fenced<
		Atomic> x)
noexcept -> decltype(auto)
{
	return ted::atomic_result(
		x,
		lift(atomic_load_explicit));
}

template<
	typename Atomic,
	typename Value>
auto store(
	fenced<
		Atomic> x,
	Value &&y)
noexcept -> decltype(auto)
{
	return ted::atomic_result(
		x,
		lift(atomic_store_explicit),
		same(y));
}

template<
	typename Atomic,
	typename Value>
auto exchange(
	fenced<
		Atomic> x,
	Value &&y)
noexcept -> decltype(auto)
{
	return ted::atomic_result(
		x,
		lift(atomic_exchange_explicit),
		same(y));
}

template<
	typename Atomic,
	typename Expected,
	typename Desired>
auto compare_exchange_strong(
	fenced<
		Atomic> x,
	Expected &&y,
	Desired &&z)
noexcept -> decltype(auto)
{
	return ted::atomic_result(
		x,
		lift(atomic_compare_exchange_strong_explicit),
		ted::address_of(y),
		same(z));
}

template<
	typename Atomic,
	typename Expected,
	typename Desired>
auto compare_exchange_weak(
	fenced<
		Atomic> x,
	Expected &&y,
	Desired &&z)
noexcept -> decltype(auto)
{
	return ted::atomic_result(
		x,
		lift(atomic_compare_exchange_weak_explicit),
		ted::address_of(y),
		same(z));
}

template<
	typename Atomic,
	typename Value>
auto fetch_add(
	fenced<
		Atomic> x,
	Value &&y)
noexcept -> decltype(auto)
{
	return ted::atomic_result(
		x,
		lift(atomic_fetch_add_explicit),
		same(y));
};

template<
	typename Atomic,
	typename Value>
auto fetch_sub(
	fenced<
		Atomic> x,
	Value &&y)
noexcept -> decltype(auto)
{
	return ted::atomic_result(
		x,
		lift(atomic_fetch_sub_explicit),
		same(y));
}

template<
	typename Atomic,
	typename Value>
auto fetch_and(
	fenced<
		Atomic> x,
	Value &&y)
noexcept -> decltype(auto)
{
	return ted::atomic_result(
		x,
		lift(atomic_fetch_and_explicit),
		same(y));
}

template<
	typename Atomic,
	typename Value>
auto fetch_or(
	fenced<
		Atomic> x,
	Value &&y)
noexcept -> decltype(auto)
{
	return ted::atomic_result(
		x,
		lift(atomic_fetch_or_explicit),
		same(y));
}

template<
	typename Atomic,
	typename Value>
auto fetch_xor(
	fenced<
		Atomic> x,
	Value &&y)
noexcept -> decltype(auto)
{
	return ted::atomic_result(
		x,
		lift(atomic_fetch_xor_explicit),
		same(y));
}

}

#endif