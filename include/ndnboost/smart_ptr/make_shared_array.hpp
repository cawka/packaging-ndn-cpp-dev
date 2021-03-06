/*
 * Copyright (c) 2012 Glen Joseph Fernandes
 * glenfe at live dot com
 *
 * Distributed under the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt
 * or copy at http://boost.org/LICENSE_1_0.txt)
 */
#ifndef NDNBOOST_SMART_PTR_MAKE_SHARED_ARRAY_HPP
#define NDNBOOST_SMART_PTR_MAKE_SHARED_ARRAY_HPP

#include <ndnboost/smart_ptr/shared_ptr.hpp>
#include <ndnboost/smart_ptr/detail/array_deleter.hpp>
#include <ndnboost/smart_ptr/detail/array_traits.hpp>
#include <ndnboost/smart_ptr/detail/make_array_helper.hpp>
#include <ndnboost/smart_ptr/detail/sp_if_array.hpp>
#if !defined(NDNBOOST_NO_CXX11_HDR_INITIALIZER_LIST)
#include <initializer_list>
#endif

namespace ndnboost {
    template<typename T>
    inline typename ndnboost::detail::sp_if_array<T>::type
    make_shared(std::size_t size) {
        typedef typename ndnboost::detail::array_inner<T>::type T1;
        typedef typename ndnboost::detail::array_base<T1>::type T2;
        T1* p1 = 0;
        T2* p2 = 0;
        std::size_t n1 = size * ndnboost::detail::array_total<T1>::size;
        ndnboost::detail::make_array_helper<T2[]> a1(n1, &p2);
        ndnboost::detail::array_deleter<T2[]> d1(n1);
        ndnboost::shared_ptr<T> s1(p1, d1, a1);
        typedef ndnboost::detail::array_deleter<T2[]>* D2;
        p1 = reinterpret_cast<T1*>(p2);
        D2 d2 = static_cast<D2>(s1._internal_get_untyped_deleter());
        d2->init(p2);
        return ndnboost::shared_ptr<T>(s1, p1);
    }
#if !defined(NDNBOOST_NO_CXX11_VARIADIC_TEMPLATES) && !defined(NDNBOOST_NO_CXX11_RVALUE_REFERENCES)
    template<typename T, typename... Args>
    inline typename ndnboost::detail::sp_if_array<T>::type
    make_shared(std::size_t size, Args&&... args) {
        typedef typename ndnboost::detail::array_inner<T>::type T1;
        typedef typename ndnboost::detail::array_base<T1>::type T2;
        T1* p1 = 0;
        T2* p2 = 0;
        std::size_t n1 = size * ndnboost::detail::array_total<T1>::size;
        ndnboost::detail::make_array_helper<T2[]> a1(n1, &p2);
        ndnboost::detail::array_deleter<T2[]> d1(n1);
        ndnboost::shared_ptr<T> s1(p1, d1, a1);
        typedef ndnboost::detail::array_deleter<T2[]>* D2;
        p1 = reinterpret_cast<T1*>(p2);
        D2 d2 = static_cast<D2>(s1._internal_get_untyped_deleter());
        d2->init(p2, ndnboost::detail::sp_forward<Args>(args)...);
        return ndnboost::shared_ptr<T>(s1, p1);
    }
    template<typename T, typename... Args>
    inline typename ndnboost::detail::sp_if_size_array<T>::type
    make_shared(Args&&... args) {
        typedef typename ndnboost::detail::array_inner<T>::type T1;
        typedef typename ndnboost::detail::array_base<T1>::type T2;
        enum {
            N = ndnboost::detail::array_total<T>::size
        };
        T1* p1 = 0;
        T2* p2 = 0;
        ndnboost::detail::make_array_helper<T2[N]> a1(&p2);
        ndnboost::detail::array_deleter<T2[N]> d1;
        ndnboost::shared_ptr<T> s1(p1, d1, a1);
        typedef ndnboost::detail::array_deleter<T2[N]>* D2;
        p1 = reinterpret_cast<T1*>(p2);
        D2 d2 = static_cast<D2>(s1._internal_get_untyped_deleter());
        d2->init(p2, ndnboost::detail::sp_forward<Args>(args)...);
        return ndnboost::shared_ptr<T>(s1, p1);
    }
#endif
#if !defined(NDNBOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX)
    template<typename T>
    inline typename ndnboost::detail::sp_if_size_array<T>::type
    make_shared(const T& list) {
        typedef typename ndnboost::detail::array_inner<T>::type T1;
        typedef typename ndnboost::detail::array_base<T1>::type T2;
        typedef const T2 T3;
        enum {
            N = ndnboost::detail::array_total<T>::size
        };
        T1* p1 = 0;
        T2* p2 = 0;
        T3* p3 = 0;
        ndnboost::detail::make_array_helper<T2[N]> a1(&p2);
        ndnboost::detail::array_deleter<T2[N]> d1;
        ndnboost::shared_ptr<T> s1(p1, d1, a1);
        typedef ndnboost::detail::array_deleter<T2[N]>* D2;
        p3 = reinterpret_cast<T3*>(list);
        p1 = reinterpret_cast<T1*>(p2);
        D2 d2 = static_cast<D2>(s1._internal_get_untyped_deleter());
        d2->init_list(p2, p3);
        return ndnboost::shared_ptr<T>(s1, p1);
    }
    template<typename T>
    inline typename ndnboost::detail::sp_if_array<T>::type
    make_shared(std::size_t size,
        const typename ndnboost::detail::array_inner<T>::type& list) {
        typedef typename ndnboost::detail::array_inner<T>::type T1;
        typedef typename ndnboost::detail::array_base<T1>::type T2;
        typedef const T2 T3;
        enum {
            M = ndnboost::detail::array_total<T1>::size
        };
        T1* p1 = 0;
        T2* p2 = 0;
        T3* p3 = 0;
        std::size_t n1 = M * size;
        ndnboost::detail::make_array_helper<T2[]> a1(n1, &p2);
        ndnboost::detail::array_deleter<T2[]> d1(n1);
        ndnboost::shared_ptr<T> s1(p1, d1, a1);
        typedef ndnboost::detail::array_deleter<T2[]>* D2;
        p3 = reinterpret_cast<T3*>(list);
        p1 = reinterpret_cast<T1*>(p2);
        D2 d2 = static_cast<D2>(s1._internal_get_untyped_deleter());
        d2->template init_list<M>(p2, p3);
        return ndnboost::shared_ptr<T>(s1, p1);
    }
    template<typename T>
    inline typename ndnboost::detail::sp_if_size_array<T>::type
    make_shared(const typename ndnboost::detail::array_inner<T>::type& list) {
        typedef typename ndnboost::detail::array_inner<T>::type T1;
        typedef typename ndnboost::detail::array_base<T1>::type T2;
        typedef const T2 T3;
        enum {
            M = ndnboost::detail::array_total<T1>::size,
            N = ndnboost::detail::array_total<T>::size
        };
        T1* p1 = 0;
        T2* p2 = 0;
        T3* p3 = 0;
        ndnboost::detail::make_array_helper<T2[N]> a1(&p2);
        ndnboost::detail::array_deleter<T2[N]> d1;
        ndnboost::shared_ptr<T> s1(p1, d1, a1);
        typedef ndnboost::detail::array_deleter<T2[N]>* D2;
        p3 = reinterpret_cast<T3*>(list);
        p1 = reinterpret_cast<T1*>(p2);
        D2 d2 = static_cast<D2>(s1._internal_get_untyped_deleter());
        d2->template init_list<M>(p2, p3);
        return ndnboost::shared_ptr<T>(s1, p1);
    }
#if !defined(NDNBOOST_NO_CXX11_HDR_INITIALIZER_LIST)
    template<typename T>
    inline typename ndnboost::detail::sp_if_array<T>::type
    make_shared(std::initializer_list<typename ndnboost::detail::array_inner<T>::type> list) {
        typedef typename ndnboost::detail::array_inner<T>::type T1;
        typedef typename ndnboost::detail::array_base<T1>::type T2;
        typedef const T2 T3;
        T1* p1 = 0;
        T2* p2 = 0;
        T3* p3 = 0;
        std::size_t n1 = list.size() * ndnboost::detail::array_total<T1>::size;
        ndnboost::detail::make_array_helper<T2[]> a1(n1, &p2);
        ndnboost::detail::array_deleter<T2[]> d1(n1);
        ndnboost::shared_ptr<T> s1(p1, d1, a1);
        typedef ndnboost::detail::array_deleter<T2[]>* D2;
        p3 = reinterpret_cast<T3*>(list.begin());
        p1 = reinterpret_cast<T1*>(p2);
        D2 d2 = static_cast<D2>(s1._internal_get_untyped_deleter());
        d2->init_list(p2, p3);
        return ndnboost::shared_ptr<T>(s1, p1);
    }
#endif
#if !defined(NDNBOOST_NO_CXX11_RVALUE_REFERENCES)
    template<typename T>
    inline typename ndnboost::detail::sp_if_array<T>::type
    make_shared(std::size_t size,
        typename ndnboost::detail::array_base<T>::type&& value) {
        typedef typename ndnboost::detail::array_inner<T>::type T1;
        typedef typename ndnboost::detail::array_base<T1>::type T2;
        T1* p1 = 0;
        T2* p2 = 0;
        std::size_t n1 = size * ndnboost::detail::array_total<T1>::size;
        ndnboost::detail::make_array_helper<T2[]> a1(n1, &p2);
        ndnboost::detail::array_deleter<T2[]> d1(n1);
        ndnboost::shared_ptr<T> s1(p1, d1, a1);
        typedef ndnboost::detail::array_deleter<T2[]>* D2;
        p1 = reinterpret_cast<T1*>(p2);
        D2 d2 = static_cast<D2>(s1._internal_get_untyped_deleter());
        d2->init(p2, ndnboost::detail::sp_forward<T2>(value));
        return ndnboost::shared_ptr<T>(s1, p1);
    }
    template<typename T>
    inline typename ndnboost::detail::sp_if_size_array<T>::type
    make_shared(typename ndnboost::detail::array_base<T>::type&& value) {
        typedef typename ndnboost::detail::array_inner<T>::type T1;
        typedef typename ndnboost::detail::array_base<T1>::type T2;
        enum {
            N = ndnboost::detail::array_total<T>::size
        };
        T1* p1 = 0;
        T2* p2 = 0;
        ndnboost::detail::make_array_helper<T2[N]> a1(&p2);
        ndnboost::detail::array_deleter<T2[N]> d1;
        ndnboost::shared_ptr<T> s1(p1, d1, a1);
        typedef ndnboost::detail::array_deleter<T2[N]>* D2;
        p1 = reinterpret_cast<T1*>(p2);
        D2 d2 = static_cast<D2>(s1._internal_get_untyped_deleter());
        d2->init(p2, ndnboost::detail::sp_forward<T2>(value));
        return ndnboost::shared_ptr<T>(s1, p1);
    }
#endif
#endif
    template<typename T>
    inline typename ndnboost::detail::sp_if_array<T>::type
    make_shared_noinit(std::size_t size) {
        typedef typename ndnboost::detail::array_inner<T>::type T1;
        typedef typename ndnboost::detail::array_base<T1>::type T2;
        T1* p1 = 0;
        T2* p2 = 0;
        std::size_t n1 = size * ndnboost::detail::array_total<T1>::size;
        ndnboost::detail::make_array_helper<T2[]> a1(n1, &p2);
        ndnboost::detail::array_deleter<T2[]> d1(n1);
        ndnboost::shared_ptr<T> s1(p1, d1, a1);
        typedef ndnboost::detail::array_deleter<T2[]>* D2;
        p1 = reinterpret_cast<T1*>(p2);
        D2 d2 = static_cast<D2>(s1._internal_get_untyped_deleter());
        d2->noinit(p2);
        return ndnboost::shared_ptr<T>(s1, p1);
    }
    template<typename T>
    inline typename ndnboost::detail::sp_if_size_array<T>::type
    make_shared_noinit() {
        typedef typename ndnboost::detail::array_inner<T>::type T1;
        typedef typename ndnboost::detail::array_base<T1>::type T2;
        enum {
            N = ndnboost::detail::array_total<T>::size
        };
        T1* p1 = 0;
        T2* p2 = 0;
        ndnboost::detail::make_array_helper<T2[N]> a1(&p2);
        ndnboost::detail::array_deleter<T2[N]> d1;
        ndnboost::shared_ptr<T> s1(p1, d1, a1);
        typedef ndnboost::detail::array_deleter<T2[N]>* D2;
        p1 = reinterpret_cast<T1*>(p2);
        D2 d2 = static_cast<D2>(s1._internal_get_untyped_deleter());
        d2->noinit(p2);
        return ndnboost::shared_ptr<T>(s1, p1);
    }
}

#endif
