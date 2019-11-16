#ifndef __ECC_H_
#define __ECC_H_
#include <gmp.h>

#define WSIZE 8 // 64-bit

#if WSIZE == 8
    #define P256_MAX_WORD_LEN 4
    #define P256_MAX_BUF_LEN 5
    #define P256_MAX_DOUBLE_BUF_LEN 9

    typedef unsigned long long lint; // surely 64-bit integer (for both 32/64-bit)
    typedef unsigned __int128 llint; // 128-bit extension (for most versions of GCC)
#endif
#if WSIZE == 4
    #define P256_MAX_WORD_LEN 8
    #define P256_MAX_BUF_LEN 9
    #define P256_MAX_DOUBLE_BUF_LEN 17

    typedef unsigned int lint; // surely 32-bit integer (for both 32/64-bit)
    typedef unsigned long long llint; // 64-bit extension (for most versions of GCC)
#endif

typedef struct _p256_int {
    lint data[P256_MAX_BUF_LEN];
    int           len;
} p256_int;

typedef struct _p256_double_int{
    lint data[P256_MAX_DOUBLE_BUF_LEN];
    int   len;
} p256_double_int;

typedef struct _p256_AF_pt {
    int at_infinity;
    p256_int x;
    p256_int y;
} p256_AF_pt;

void mpz_to_p256int(p256_int *out, mpz_t in);
void p256int_to_mpz(mpz_t out, p256_int *in);

void p256int_add(p256_int *out, p256_int *a, p256_int *b);
void p256int_sub(p256_int *out, p256_int *a, p256_int *b);
void p256int_mul(p256_int *out, p256_int *a, p256_int *b);  // 64-bit version only
int  p256int_inv(p256_int *out, p256_int *a);               // return -1 for 0^(-1)
void p256int_cpy(p256_int *dst, p256_int *src);
int p256int_cmp(p256_int *a, p256_int *b);                  // 1:a>b, 0:a==b, -1:a<b

int p256_AF_add(p256_AF_pt *R, p256_AF_pt *P, p256_AF_pt *Q);
int p256_AF_dlb(p256_AF_pt *R, p256_AF_pt *P);
void p256_AF_cpy(p256_AF_pt *R, p256_AF_pt *P);
int p256_AF_cmp(p256_AF_pt *P, p256_AF_pt *Q);              // 0: P == Q , otherwise: P != Q

// p256_prime = 2^256 - 2^224 + 2^192 + 2^96 - 1
#if WSIZE == 8
    static p256_int p256_prime  = {{0xffffffffffffffffLL, 0x00000000ffffffffLL, 0x0000000000000000LL, 0xffffffff00000001LL, 0LL}, P256_MAX_WORD_LEN};
    static p256_int p256_coef_a = {{0xfffffffffffffffcLL, 0x00000000ffffffffLL, 0x0000000000000000LL, 0xffffffff00000001LL, 0LL}, P256_MAX_WORD_LEN};
    static p256_int p256_coef_b = {{0x3bce3c3e27d2604bLL, 0x651d06b0cc53b0f6LL, 0xb3ebbd55769886bcLL, 0x5ac635d8aa3a93e7LL, 0LL}, P256_MAX_WORD_LEN};
#endif
#if WSIZE == 4
    static p256_int p256_prime  = {{0xffffffff,0xffffffff,0xffffffff,0x00000000,0x00000000,0x00000000,0x00000001,0xffffffff,0}, P256_MAX_WORD_LEN};
    static p256_int p256_coef_a = {{0xfffffffc,0xffffffff,0xffffffff,0x00000000,0x00000000,0x00000000,0x00000001,0xffffffff,0},	P256_MAX_WORD_LEN};
    static p256_int p256_coef_b = {{0x27d2604b,0x3bce3c3e,0xcc53b0f6,0x651d06b0,0x769886bc,0xb3ebbd55,0xaa3a93e7,0x5ac635d8,0},	P256_MAX_WORD_LEN};
#endif

#endif