//  (C) Copyright Daniel Frey and Robert Ramey 2009.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.
 
#ifndef NDNBOOST_TT_IS_VIRTUAL_BASE_OF_HPP_INCLUDED
#define NDNBOOST_TT_IS_VIRTUAL_BASE_OF_HPP_INCLUDED

#include <ndnboost/type_traits/is_base_of.hpp>
#include <ndnboost/type_traits/is_same.hpp>
#include <ndnboost/mpl/and.hpp>
#include <ndnboost/mpl/not.hpp>

// should be the last #include
#include <ndnboost/type_traits/detail/bool_trait_def.hpp>

namespace ndnboost {
namespace detail {


#ifdef NDNBOOST_MSVC
#pragma warning( push )
#pragma warning( disable : 4584 4250)
#elif defined(__GNUC__) && (__GNUC__ >= 4)
#pragma GCC system_header
#endif

template<typename Base, typename Derived, typename tag>
struct is_virtual_base_of_impl
{
    NDNBOOST_STATIC_CONSTANT(bool, value = false);
};

template<typename Base, typename Derived>
struct is_virtual_base_of_impl<Base, Derived, mpl::true_>
{
#ifdef __BORLANDC__
    struct boost_type_traits_internal_struct_X : public virtual Derived, public virtual Base 
    {
       boost_type_traits_internal_struct_X();
       boost_type_traits_internal_struct_X(const boost_type_traits_internal_struct_X&);
       boost_type_traits_internal_struct_X& operator=(const boost_type_traits_internal_struct_X&);
       ~boost_type_traits_internal_struct_X()throw();
    };
    struct boost_type_traits_internal_struct_Y : public virtual Derived 
    {
       boost_type_traits_internal_struct_Y();
       boost_type_traits_internal_struct_Y(const boost_type_traits_internal_struct_Y&);
       boost_type_traits_internal_struct_Y& operator=(const boost_type_traits_internal_struct_Y&);
       ~boost_type_traits_internal_struct_Y()throw();
    };
#else
    struct boost_type_traits_internal_struct_X : public Derived, virtual Base 
    {
       boost_type_traits_internal_struct_X();
       boost_type_traits_internal_struct_X(const boost_type_traits_internal_struct_X&);
       boost_type_traits_internal_struct_X& operator=(const boost_type_traits_internal_struct_X&);
       ~boost_type_traits_internal_struct_X()throw();
    };
    struct boost_type_traits_internal_struct_Y : public Derived 
    {
       boost_type_traits_internal_struct_Y();
       boost_type_traits_internal_struct_Y(const boost_type_traits_internal_struct_Y&);
       boost_type_traits_internal_struct_Y& operator=(const boost_type_traits_internal_struct_Y&);
       ~boost_type_traits_internal_struct_Y()throw();
    };
#endif
    NDNBOOST_STATIC_CONSTANT(bool, value = (sizeof(boost_type_traits_internal_struct_X)==sizeof(boost_type_traits_internal_struct_Y)));
};

template<typename Base, typename Derived>
struct is_virtual_base_of_impl2
{
   typedef typename mpl::and_<is_base_of<Base, Derived>, mpl::not_<is_same<Base, Derived> > >::type tag_type;
   typedef is_virtual_base_of_impl<Base, Derived, tag_type> imp;
   NDNBOOST_STATIC_CONSTANT(bool, value = imp::value);
};

#ifdef NDNBOOST_MSVC
#pragma warning( pop )
#endif

} // namespace detail

NDNBOOST_TT_AUX_BOOL_TRAIT_DEF2(
      is_virtual_base_of
       , Base
       , Derived
       , (::ndnboost::detail::is_virtual_base_of_impl2<Base,Derived>::value) 
)

#ifndef NDNBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
NDNBOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC2_2(typename Base,typename Derived,is_virtual_base_of,Base&,Derived,false)
NDNBOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC2_2(typename Base,typename Derived,is_virtual_base_of,Base,Derived&,false)
NDNBOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC2_2(typename Base,typename Derived,is_virtual_base_of,Base&,Derived&,false)
#endif

} // namespace ndnboost

#include <ndnboost/type_traits/detail/bool_trait_undef.hpp>

#endif
