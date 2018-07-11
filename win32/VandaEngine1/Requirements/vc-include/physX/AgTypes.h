/*----------------------------------------------------------------------
    This Software and Related Documentation are Proprietary to NVIDIA
    Corporation

    Copyright 2010 NVIDIA Corporation
    Unpublished -
    All Rights Reserved Under the Copyright Laws of the United States.

    Restricted Rights Legend:  Use, Duplication, or Disclosure by
    the Government is Subject to Restrictions as Set Forth in
    Paragraph (c)(1)(ii) of the Rights in Technical Data and
    Computer Software Clause at DFARS 252.227-7013.  NVIDIA
    Corporation
-----------------------------------------------------------------------*/

#ifndef AGTYPES_H
#define AGTYPES_H 1

#if 0
#define AG_USE_INLINES 0

/* OOC Wonder whether we ever need separate DECL and IMPL macros. */

#if AG_USE_INLINES
#define AgINLINE_DECL extern inline
#define AgINLINE_IMPL extern inline
#else
#define AgINLINE_DECL
#define AgINLINE_IMPL
#endif
#endif /* 0 */

#ifndef __cplusplus
typedef enum { false = 0, true = 1 } bool;
#endif

typedef void   *AgHostPtr;
typedef float   AgReal;

typedef unsigned int AgU32;
typedef int AgI32;

typedef unsigned short AgU16;
typedef short AgI16;

/* Remember that char, signed char, and unsigned char
   are always distinct, I'm not sure that I want to break
   anyone's code by redefining AgI8 to signed char */
typedef unsigned char AgU8;
typedef char AgI8;
typedef char AgChar;


/* These defines are deprecated for host software */
#ifdef WIN32
typedef unsigned __int64 AgU64;         /* Unsigned 64-bit quantity     */
typedef unsigned __int64 uint64;        /* Unsigned 64-bit quantity     */
#else
typedef unsigned long long AgU64;       /* Unsigned 64-bit quantity     */
typedef unsigned long long uint64;      /* Unsigned 64-bit quantity     */
#endif
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

#ifdef WIN32
typedef __int64 AgI64;            /* Signed   64-bit quantity     */
typedef __int64 sint64;           /* Signed   64-bit quantity     */
#else
typedef long long AgI64;          /* Signed   64-bit quantity     */
typedef long long sint64;         /* Signed   64-bit quantity     */
#endif
typedef signed int sint32;
typedef signed short sint16;
typedef signed char sint8;

typedef struct
{
	AgI16 x;
	AgI16 y;
	AgI16 z;

} AgI16Vector3;


#if 0
/*! Type conversion function without float <-> int casting */
AgINLINE_IMPL AgU32 AgRealToWord(AgReal fl)
{
    return * (AgU32 *) &fl;
}

/*! Type conversion function without float <-> int casting */
AgINLINE_IMPL AgReal AgWordToReal(AgU32 w)
{
    return * (AgReal *) &w;
}
#endif /*0*/

#endif
