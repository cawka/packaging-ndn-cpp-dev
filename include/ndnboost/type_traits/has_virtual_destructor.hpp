
//  (C) Copyright John Maddock 2005.  
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.


#ifndef NDNBOOST_TT_HAS_VIRTUAL_DESTRUCTOR_HPP_INCLUDED
#define NDNBOOST_TT_HAS_VIRTUAL_DESTRUCTOR_HPP_INCLUDED

#include <ndnboost/type_traits/intrinsics.hpp>
// should be the last #include
#include <ndnboost/type_traits/detail/bool_trait_def.hpp>

namespace ndnboost {

#ifdef NDNBOOST_HAS_VIRTUAL_DESTRUCTOR
NDNBOOST_TT_AUX_BOOL_TRAIT_DEF1(has_virtual_destructor,T,NDNBOOST_HAS_VIRTUAL_DESTRUCTOR(T))
#else
NDNBOOST_TT_AUX_BOOL_TRAIT_DEF1(has_virtual_destructor,T,false)
#endif

} // namespace ndnboost

#include <ndnboost/type_traits/detail/bool_trait_undef.hpp>

#endif // NDNBOOST_TT_IS_MEMBER_FUNCTION_POINTER_HPP_INCLUDED
