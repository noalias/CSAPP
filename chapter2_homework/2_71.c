#include <stdio.h>

/* Declaration of data type where 4 bytes are packed
 * into an unsigned */
typedef unsigned packed_t;

/* Extract byte from word. Return as signed integer */
int xbyte(packed_t word, int bytenum);

int main(void)
{
    packed_t word = 0xf2345678;
    int bytenum = 3; /* bytenum 的取值为：0,1,2,3 */

    printf("%x-->%d", xbyte(word, bytenum), xbyte(word, bytenum));

    return 0;
}

int xbyte(packed_t word, int bytenum)
{
    word << ((3 - bytenum) << 3);
    return (int) word >> (3 << 3);
}
