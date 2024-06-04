 /**
 * @file stdio.h
 *
 * Copyright 2020 Teledyne Webb Research as an unpublished work.
 *
 * The information contained herein is the property of Teledyne Webb Research
 * and is considered proprietary. This information may not be used for
 * any other purpose, copied, transferred or disclosed to third parties,
 * reverse engineered, modified or improved without written consent
 * from Teledyne Webb Research.
 *
 */

#if !defined(STDIO_H)
#define STDIO_H

/* ********************************* Includes ********************************* */

#include <printf.h>
#include <stdarg.h>
#include <libdef.h>
#include <stddef.h>
#include <wchar.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ********************************* Defines ********************************** */

#undef EOF
#define EOF (-1)

#if defined(_LIBC_BUILDING_LIBRARY) || defined(_LIBCPP_BUILDING_LIBRARY) || defined(_LIBCXXABI_BUILDING_LIBRARY)
struct __sbuf
{
	unsigned char* _base;
	int _size;
};

/*
 * struct __sFILE_fake is the start of a struct __sFILE, with only the
 * minimal fields allocated.  In __sinit() we really allocate the 3
 * standard streams, etc., and point away from this fake.
 */
struct __sFILE_fake
{
	unsigned char* _p; /* current position in (some) buffer */
	int _r; /* read space left for getc() */
	int _w; /* write space left for putc() */
	short _flags; /* flags, below; this FILE is free if 0 */
	short _file; /* fileno, if Unix descriptor, else -1 */
	struct __sbuf _bf; /* the buffer (at least 1 byte, if !NULL) */
	int _lbfsize; /* 0 or -_bf._size, for inline putc */

	struct _reent* _data;
};

#if !defined(__FILE_defined)
typedef struct __sFILE_fake FILE;
#define __FILE_defined
#endif

typedef union _G_fpos64_t
{
	char __opaque[16];
	long long __lldata;
	double __align;
} fpos_t;

/* C++ Support functions */

char* fgets(char* __restrict, int, FILE* __restrict);
int fclose(FILE*);
int feof(FILE*);
int ferror(FILE*);
int fflush(FILE*);
int fgetc(FILE*);
int fgetpos(FILE* __restrict, uint32_t* __restrict);
int fprintf(FILE* __restrict, const char* __restrict, ...);
int fputws(const wchar_t* __restrict, FILE* __restrict);
int fscanf(FILE* __restrict, const char* __restrict, ...);
int fseek(FILE*, long, int);
int fsetpos(FILE*, const fpos_t*);
int fwide(FILE*, int);
int fwprintf(FILE* __restrict, const wchar_t* __restrict, ...);
int fwscanf(FILE* __restrict, const wchar_t* __restrict, ...);
int getc(FILE*);
int putc(int, FILE*);
int setvbuf(FILE* __restrict, char* __restrict, int, size_t);
int swprintf(wchar_t* __restrict, size_t, const wchar_t* __restrict, ...);
int swscanf(const wchar_t* __restrict, const wchar_t* __restrict, ...);
int ungetc(int, FILE*);
int vfprintf(FILE* __restrict, const char* __restrict, __isoc_va_list);
int vfscanf(FILE* __restrict, const char* __restrict, __isoc_va_list);
int vfwprintf(FILE* __restrict, const wchar_t* __restrict, __isoc_va_list);
int vfwscanf(FILE* __restrict, const wchar_t* __restrict, __isoc_va_list);
int vswprintf(wchar_t* __restrict, size_t, const wchar_t* __restrict, __isoc_va_list);
int vswscanf(const wchar_t* __restrict, const wchar_t* __restrict, __isoc_va_list);
int vwprintf(const wchar_t* __restrict, __isoc_va_list);
int wprintf(const wchar_t* __restrict, ...);
long ftell(FILE*);
size_t fread(void* __restrict, size_t, size_t, FILE* __restrict);
size_t fwrite(const void* __restrict, size_t, size_t, FILE* __restrict);
void clearerr(FILE*);
void perror(const char*);
void rewind(FILE*);
wchar_t* fgetws(wchar_t* __restrict, int, FILE* __restrict);
wint_t fgetwc(FILE*);
wint_t fputwc(wchar_t, FILE*);
wint_t getwc(FILE*);
wint_t putwchar(wchar_t);
wint_t putwc(wchar_t, FILE*);
wint_t ungetwc(wint_t, FILE*);
int fputs(const char* __restrict, FILE* __restrict);
int fputc(int, FILE*);
void setbuf(FILE* __restrict, char* __restrict);
int vsprintf(char* s, const char* format, va_list arg) __attribute__((format(printf, 2, 0)));

#endif

/* ****************************** Module Globals ****************************** */

/* *************************** Function Prototypes **************************** */

/* Implemented functions */

int getchar(void);

int putchar(int c);

int puts(const char *);

int asprintf(char **, const char *, ...) __attribute__((format(printf, 2, 3)));

int vasprintf(char **, const char *, __isoc_va_list) __attribute__((format(printf, 2, 0)));

int sscanf(const char *buf, const char *format, ...) __attribute__((format(scanf, 2, 3)));

int vsscanf(const char *buf, const char *s, va_list ap);

#ifdef __cplusplus
}
#endif

#endif /* if !defined(STDIO_H) */
