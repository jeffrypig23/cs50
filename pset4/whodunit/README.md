# Questions

## What's `stdint.h`?

Stdint.h is a library which enables programmers to write more portable code by providing a set of typedefs that specify exact-width integer types.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

Like how a byte is 8 bits, uint8_t and uint32_t defines how many bits make up a byte in terms of a specific data structure

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

8, 32, 32, 16

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

BM, or the fiels signiture

## What's the difference between `bfSize` and `biSize`?

bf size is akin to that of the file size, and bi size is what is required of the structure in terms of bytes

## What does it mean if `biHeight` is negative?

Then "biCompression must be either BI_RGB or BI_BITFIELDS"

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

The file might be being used by another process

## Why is the third argument to `fread` always `1` in our code?

Becasue the size of the element is always 1

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

It sets the file position of the stream to the given offset, kinda like a skipping ahead in a track

## What is `SEEK_CUR`?

Its a pointer to the files new locaion

## Whodunit?

It was professor plum with the candlestick in the library!
