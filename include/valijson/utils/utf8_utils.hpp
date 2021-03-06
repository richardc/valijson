#ifndef __VALIJSON_UTILS_UTF8_UTILS_HPP
#define __VALIJSON_UTILS_UTF8_UTILS_HPP

/*
  Basic UTF-8 manipulation routines, adapted from code that was released into
  the public domain by Jeff Bezanson.
*/

namespace valijson {
namespace utils {

static const u_int32_t offsetsFromUTF8[6] = {
    0x00000000UL, 0x00003080UL, 0x000E2080UL,
    0x03C82080UL, 0xFA082080UL, 0x82082080UL
};

/* is c the start of a utf8 sequence? */
inline bool isutf(char c) {
    return ((c & 0xC0) != 0x80);
}

/* reads the next utf-8 sequence out of a string, updating an index */
inline u_int32_t u8_nextchar(const char *s, int *i)
{
    u_int32_t ch = 0;
    int sz = 0;

    do {
        ch <<= 6;
        ch += (unsigned char)s[(*i)++];
        sz++;
    } while (s[*i] && !isutf(s[*i]));
    ch -= offsetsFromUTF8[sz-1];

    return ch;
}

/* number of characters */
inline int u8_strlen(const char *s)
{
    int count = 0;
    int i = 0;

    while (s[i] != 0 && u8_nextchar(s, &i) != 0) {
        count++;
    }

    return count;
}

}  // namespace utils
}  // namespace valijson

#endif
