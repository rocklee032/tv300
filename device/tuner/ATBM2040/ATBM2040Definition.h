#ifndef __ATBM2040DEFINITION_H__
#define __ATBM2040DEFINITION_H__
#ifdef __cplusplus
extern "C"
{
#endif

#ifndef BOOL
#define BOOL int
#ifndef TRUE
#define TRUE (1==1)
#define FALSE (!TRUE)
#endif
#endif

//typedef unsigned char       UINT8;
//typedef unsigned short		UINT16;
//typedef unsigned int		UINT32;
typedef signed char         SINT8;
typedef short               SINT16;
typedef int                 SINT32;


#ifndef NULL
#define NULL    ((void *)0)
#endif


#ifdef __cplusplus
}
#endif

#endif /*__ATBM2040DEFINITION_H__*/


