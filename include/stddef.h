#ifndef STDDEF_H_
#define STDDEF_H_

#include <_types/_ptrdiff_t.h>
#include <_types/_size_t.h>
#include <stdint.h>
#include <libdef.h>

#if !defined(strong_alias)
# define strong_alias(name, aliasname) _strong_alias(name, aliasname)
# define _strong_alias(name, aliasname) \
extern __typeof (name) aliasname __attribute__ ((alias (#name)));
#endif

#pragma mark - NULL -

#ifdef __cplusplus
/*! Expands to 0L (for C++). Implementation-defined null pointer constant  */
#define NULL 0L
#else

/*! Expands to ((void*)0) (not C++). Implementation-defined null pointer constant  */
#define NULL ((void*)0)
#endif

#pragma mark - offsetof -

#if __GNUC__ > 3

/*! byte offset from the beginning of a struct type to specified member  */
#define offsetof(type, member) __builtin_offsetof(type, member)
#else

/*! byte offset from the beginning of a struct type to specified member  */
#define offsetof(type, member) ((size_t)((char*)&(((type*)0)->member) - (char*)0))
#endif

#pragma mark - max_align_t -

#if !defined(_UNUSED)
#define _UNUSED(x)       ((void)x)
#endif

#if !defined(ARRAY_SIZE)
#define ARRAY_SIZE(x)       (sizeof x / sizeof x[0])
#endif

#if(defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L) || \
	(defined(__cplusplus) && __cplusplus >= 201103L)

/*! A type with alignment requirement as great as any other scalar type  */
typedef long double max_align_t;
#endif

#pragma pack(1)

#define XBSS        __attribute__((section(".xbss")))
#define XDATA       __attribute__((section(".xdata")))

typedef union
{
    uint16_t u16;
    int16_t i16;
    uint8_t u8[2] ;
    int8_t i8[2] ;
    struct
    {
        uint8_t ul8;
        uint8_t uh8;
    };
    struct
    {
        int8_t il8;
        int8_t ih8;
    };
} x16_parts_t;

typedef union
{
    uint32_t u32;
    int32_t i32;
    float f32;
    uint8_t u8[4] ;
    int8_t i8[4] ;
    struct
    {
        x16_parts_t l16;
        x16_parts_t h16;
    };
} x32_parts_t;

#pragma pack()

#endif // STDDEF_H_
