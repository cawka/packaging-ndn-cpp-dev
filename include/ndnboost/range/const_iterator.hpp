// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef NDNBOOST_RANGE_CONST_ITERATOR_HPP
#define NDNBOOST_RANGE_CONST_ITERATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <ndnboost/range/config.hpp>

#ifdef NDNBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <ndnboost/range/detail/const_iterator.hpp>
#else

#include <ndnboost/range/detail/extract_optional_type.hpp>
#include <ndnboost/type_traits/remove_const.hpp>
#include <cstddef>
#include <utility>

namespace ndnboost
{
    //////////////////////////////////////////////////////////////////////////
    // default
    //////////////////////////////////////////////////////////////////////////
    
    namespace range_detail {
        NDNBOOST_RANGE_EXTRACT_OPTIONAL_TYPE( const_iterator )
    }

    template< typename C >
    struct range_const_iterator : range_detail::extract_const_iterator<C>
    {};
    
    //////////////////////////////////////////////////////////////////////////
    // pair
    //////////////////////////////////////////////////////////////////////////

    template< typename Iterator >
    struct range_const_iterator< std::pair<Iterator,Iterator> >
    {
        typedef Iterator type;
    };
    
    //////////////////////////////////////////////////////////////////////////
    // array
    //////////////////////////////////////////////////////////////////////////

    template< typename T, std::size_t sz >
    struct range_const_iterator< T[sz] >
    {
        typedef const T* type;
    };

} // namespace ndnboost

#endif // NDNBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif
