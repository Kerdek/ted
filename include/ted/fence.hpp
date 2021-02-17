#ifndef H_B1B36C5A_F4DE_46A0_8458_97B7475C9851
#define H_B1B36C5A_F4DE_46A0_8458_97B7475C9851

#include <ted/atomic.hpp>

namespace ted
{

/**

Atomic objects which carry memory
ordering information.

*/
template<
	memory_order Order,
	typename AtomicObject>
	struct fenced_t
{
	AtomicObject object;
};

/**

The atomic operation, but with
`Order` as the final argument.

*/
template<
	memory_order Order,
	typename AtomicObject,
	typename ...Args>
	auto atomic_invoke(
		fenced_t<Order, AtomicObject> &object,
		Args &&...args)
	noexcept -> decltype(auto)
{
	return ted::atomic_result(
		obj(object.object),
		same(args)...,
		Order);
}

/**

Get a `fenced_t` for the specified
memory order containing an atomic object
or reference wrapper.

*/
template<
	memory_order Order,
	typename AtomicObject>
	auto fence(
		AtomicObject &&object)
	noexcept -> fenced_t<
        Order,
        AtomicObject &&>
{
	return { same(object) };
}

/**

Convenience wrapper for
`ted::fence<memory_order::relaxed>`.

*/
template<
	typename AtomicObject>
	auto relaxed(
		AtomicObject &&object)
	noexcept -> decltype(auto)
{
	return ted::fence<
		memory_order::relaxed>(
		same(object));
}

/**

Convenience wrapper for
`ted::fence<memory_order::relaxed>`.

*/
template<
	typename AtomicObject>
	auto acquire(
		AtomicObject &&object)
	noexcept -> decltype(auto)
{
	return ted::fence<
		memory_order::acquire>(
		same(object));
}

/**

Convenience wrapper for
`ted::fence<memory_order::release>`.

*/
template<
	typename AtomicObject>
	auto release(
		AtomicObject &&object)
	noexcept -> decltype(auto)
{
	return ted::fence<
		memory_order::release>(
		same(object));
}

/**

Convenience wrapper for
`ted::fence<memory_order::acq_rel>`.

*/
template<
	typename AtomicObject>
	auto acq_rel(
		AtomicObject &&object)
	noexcept -> decltype(auto)
{
	return ted::fence<
		memory_order::acq_rel>(
		same(object));
}

/**

Convenience wrapper for
`ted::fence<memory_order::seq_cst>`.

*/
template<
	typename AtomicObject>
	auto seq_cst(
		AtomicObject &&object)
	noexcept -> decltype(auto)
{
	return ted::fence<
		memory_order::seq_cst>(
		same(object));
}

}

#endif