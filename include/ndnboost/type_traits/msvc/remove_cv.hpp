// Copyright (C) 2004 Peder Holt
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef NDNBOOST_TYPE_TRAITS_MSVC_REMOVE_CV_HOLT_2004_0901
#define NDNBOOST_TYPE_TRAITS_MSVC_REMOVE_CV_HOLT_2004_0901

#include <ndnboost/type_traits/msvc/typeof.hpp>
#include <ndnboost/type_traits/is_volatile.hpp>
#include <ndnboost/type_traits/is_const.hpp>
#include <ndnboost/type_traits/is_pointer.hpp>
#include <ndnboost/type_traits/is_array.hpp>

namespace ndnboost {
    namespace detail {
        template<bool IsPointer,bool IsArray,bool IsConst,bool IsVolatile>
        struct remove_cv_impl_typeof {
            template<typename T,typename ID>
            struct inner {
                typedef T type;
            };
            template<typename T>
            struct transform_type {
                typedef T type;
            };
        };
        template<> //Volatile
        struct remove_cv_impl_typeof<false,false,false,true> {
            template<typename T,typename ID>
            struct inner {
                template<typename U>
                static msvc_register_type<U,ID> test(U volatile&(*)());
                static msvc_register_type<T,ID> test(...);
                NDNBOOST_STATIC_CONSTANT(unsigned,register_test=sizeof(test( (T(*)())(NULL) ) ));
                typedef typename msvc_extract_type<ID>::id2type::type type;
            };
            template<typename T>
            struct transform_type {
                typedef T& type;
            };
        };
        template<> //Const
        struct remove_cv_impl_typeof<false,false,true,false> {
            template<typename T,typename ID>
            struct inner {
                template<typename U>
                static msvc_register_type<U,ID> test(U const&(*)());
                static msvc_register_type<T,ID> test(...);
                NDNBOOST_STATIC_CONSTANT(unsigned,register_test=sizeof(test( (T(*)())(NULL) ) ));
                typedef typename msvc_extract_type<ID>::id2type::type type;
            };
            template<typename T>
            struct transform_type {
                typedef T& type;
            };
        };
        template<> //CV
        struct remove_cv_impl_typeof<false,false,true,true> {
            template<typename T,typename ID>
            struct inner {
                template<typename U>
                static msvc_register_type<U,ID> test(U const volatile&(*)());
                static msvc_register_type<T,ID> test(...);
                NDNBOOST_STATIC_CONSTANT(unsigned,register_test=sizeof(test( (T(*)())(NULL) ) ));
                typedef typename msvc_extract_type<ID>::id2type::type type;
            };
            template<typename T>
            struct transform_type {
                typedef T& type;
            };
        };
        template<> //Volatile Pointer
        struct remove_cv_impl_typeof<true,false,false,true> {
            template<typename T,typename ID>
            struct inner {
                template<typename U>
                static msvc_register_type<U,ID> test(void(*)(U volatile[]));
                static msvc_register_type<T,ID> test(...);
                NDNBOOST_STATIC_CONSTANT(unsigned,register_test=sizeof(test( (void(*)(T))(NULL) ) ));
                typedef typename msvc_extract_type<ID>::id2type::type type;
            };
            template<typename T>
            struct transform_type {
                typedef T type[];
            };
        };
        template<> //Const Pointer
        struct remove_cv_impl_typeof<true,false,true,false> {
            template<typename T,typename ID>
            struct inner {
                template<typename U>
                static msvc_register_type<U,ID> test(void(*)(U const[]));
                static msvc_register_type<T,ID> test(...);
                NDNBOOST_STATIC_CONSTANT(unsigned,register_test=sizeof(test( (void(*)(T))(NULL) ) ));
                typedef typename msvc_extract_type<ID>::id2type::type type;
            };
            template<typename T>
            struct transform_type {
                typedef T type[];
            };
        };
        template<> //CV Pointer
        struct remove_cv_impl_typeof<true,false,true,true> {
            template<typename T,typename ID>
            struct inner {
                template<typename U>
                static msvc_register_type<U,ID> test(void(*)(U const volatile[]));
                static msvc_register_type<T,ID> test(...);
                NDNBOOST_STATIC_CONSTANT(unsigned,register_test=sizeof(test( (void(*)(T))(NULL) ) ));
                typedef typename msvc_extract_type<ID>::id2type::type type;
            };
            template<typename T>
            struct transform_type {
                typedef T type[];
            };
        };        
        template<> //Volatile Array
        struct remove_cv_impl_typeof<false,true,false,true> {
            template<typename T,typename ID>
            struct inner {
                NDNBOOST_STATIC_CONSTANT(unsigned,value=(sizeof(T)/sizeof((*((T*)NULL))[0])));

                template<typename U>
                static msvc_register_type<U[value],ID> test(void(*)(U volatile[]));
                static msvc_register_type<T,ID> test(...);
                NDNBOOST_STATIC_CONSTANT(unsigned,register_test=sizeof(test( (void(*)(T))(NULL) ) ));
                typedef typename msvc_extract_type<ID>::id2type::type type;
            };
            template<typename T>
            struct transform_type {
                typedef T type;
            };
        };
        template<> //Const Array
        struct remove_cv_impl_typeof<false,true,true,false> {
            template<typename T,typename ID>
            struct inner {
                NDNBOOST_STATIC_CONSTANT(unsigned,value=(sizeof(T)/sizeof((*((T*)NULL))[0])));

                template<typename U>
                static msvc_register_type<U[value],ID> test(void(*)(U const[]));
                static msvc_register_type<T,ID> test(...);
                NDNBOOST_STATIC_CONSTANT(unsigned,register_test=sizeof(test( (void(*)(T))(NULL) ) ));
                typedef typename msvc_extract_type<ID>::id2type::type type;
            };
            template<typename T>
            struct transform_type {
                typedef T type;
            };
        };

        template<> //CV Array
        struct remove_cv_impl_typeof<false,true,true,true> {
            template<typename T,typename ID>
            struct inner {
                NDNBOOST_STATIC_CONSTANT(unsigned,value=(sizeof(T)/sizeof((*((T*)NULL))[0])));

                template<typename U>
                static msvc_register_type<U[value],ID> test(void(*)(U const volatile[]));
                static msvc_register_type<T,ID> test(...);
                NDNBOOST_STATIC_CONSTANT(unsigned,register_test=sizeof(test( (void(*)(T))(NULL) ) ));
                typedef typename msvc_extract_type<ID>::id2type::type type;
            };
            template<typename T>
            struct transform_type {
                typedef T type;
            };
        };

    } //namespace detail

    template<typename T>
    struct remove_cv {
        typedef ndnboost::detail::remove_cv_impl_typeof<
            ndnboost::is_pointer<T>::value,
            ndnboost::is_array<T>::value,
            ndnboost::is_const<T>::value,
            ndnboost::is_volatile<T>::value
        > remove_cv_type;
        typedef typename 
            remove_cv_type::template inner<
                typename remove_cv_type::template transform_type<T>::type,
                remove_cv<T>
            >::type
        type;
        NDNBOOST_MPL_AUX_LAMBDA_SUPPORT(1,remove_cv,T)
    };
}//namespace ndnboost

#endif //NDNBOOST_TYPE_TRAITS_MSVC_REMOVE_CV_HOLT_2004_0901
