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

#include <ted/address.hpp>

#include <atomic>
#include <type_traits>

#include <ted/same.hpp>

namespace ted
{

namespace memory_order
{

enum type
{
	relaxed = std::memory_order_relaxed,
	acquire = std::memory_order_acquire,
	release = std::memory_order_release,
	acq_rel = std::memory_order_acq_rel,
	seq_cst = std::memory_order_seq_cst
};

}

template<
	typename Self>
	auto atomic_obj(
		Self &&self)
	noexcept -> auto *
{
	return ted::address(
		self);
}

template<
	typename Atomic>
	auto load(
		Atomic &&self,
		memory_order::type order =
			memory_order::seq_cst)
	noexcept -> decltype(auto)
{
	return obj(
		atomic_load_explicit(
			atomic_obj(
				same(self)),
			order));
}

template<
	typename Atomic,
	typename Value>
	auto store(
		Atomic &&self,
		Value new_val,
		memory_order::type order =
			memory_order::seq_cst)
	noexcept -> decltype(auto)
{
	return obj(
		atomic_store_explicit(
			atomic_obj(
				same(self)),
			new_val,
			order));
}

template<
	typename Atomic,
	typename Value>
	auto exchange(
		Atomic &&self,
		Value new_val,
		memory_order::type order =
			memory_order::seq_cst)
	noexcept -> decltype(auto)
{
	return obj(
		atomic_exchange_explicit(
			atomic_obj(
				same(self)),
			new_val,
			order));
}

template<
	typename Atomic,
	typename Value>
	auto compare_exchange_strong(
		Atomic &&self,
		Value &expected,
		Value desired,
		memory_order::type failure =
			memory_order::seq_cst,
		memory_order::type success =
			memory_order::seq_cst)
	noexcept -> decltype(auto)
{
	return obj(
		atomic_compare_exchange_strong_explicit(
			atomic_obj(
				same(self)),
			addressof(expected),
			desired,
			success,
			failure));
}

template<
	typename Atomic,
	typename Value>
	auto compare_exchange_weak(
		Atomic &&self,
		Value &expected,
		Value desired,
		memory_order::type failure =
			memory_order::seq_cst,
		memory_order::type success =
			memory_order::seq_cst)
	noexcept -> decltype(auto)
{
	return obj(
		atomic_compare_exchange_weak_explicit(
			atomic_obj(
				same(self)),
			addressof(expected),
			desired,
			success,
			failure));
}

template<
	typename Atomic,
	typename Value>
	auto fetch_add(
		Atomic &&self,
		Value amount,
		memory_order::type order =
			memory_order::seq_cst)
	noexcept -> decltype(auto)
{
	return obj(
		atomic_fetch_add_explicit(
			atomic_obj(
				same(self)),
			amount,
			order));
};

template<
	typename Atomic,
	typename Value>
	auto fetch_sub(
		Atomic &&self,
		Value amount,
		memory_order::type order =
			memory_order::seq_cst)
	noexcept -> decltype(auto)
{
	return obj(
		atomic_fetch_sub_explicit(
			atomic_obj(
				same(self)),
			amount,
			order));
}

template<
	typename Atomic,
	typename Value>
	auto fetch_and(
		Atomic &&self,
		Value amount,
		memory_order::type order =
			memory_order::seq_cst)
	noexcept -> decltype(auto)
{
	return obj(
		atomic_fetch_and_explicit(
			atomic_obj(
				same(self)),
			amount,
			order));
}

template<
	typename Atomic,
	typename Value>
	auto fetch_or(
		Atomic &&self,
		Value amount,
		memory_order::type order =
			memory_order::seq_cst)
	noexcept -> decltype(auto)
{
	return obj(
		atomic_fetch_or_explicit(
			atomic_obj(
				same(self)),
			amount,
			order));
}

template<
	typename Atomic,
	typename Value>
	auto fetch_xor(
		Atomic &&self,
		Value amount,
		memory_order::type order =
			memory_order::seq_cst)
	noexcept -> decltype(auto)
{
	return obj(
		atomic_fetch_xor_explicit(
			atomic_obj(
				same(self)),
			amount,
			order));
}

}

#include <ted/nosame.hpp>

#endif