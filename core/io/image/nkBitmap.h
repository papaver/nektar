//------------------------------------------------------------------------------
// nkBitmap.h
//------------------------------------------------------------------------------

#ifndef _NKBITMAP_H_
#define _NKBITMAP_H_

/*
Note that biBitCount actually specifies the color resolution of the bitmap. The 
possible values are: 1 (black/white); 4 (16 colors); 8 (256 colors); 24 (16.7 
million colors). The biBitCount data element also decides if there is a color 
table in the file and how it looks like. In 1-bit mode the color table has to 
contain 2 entries (usually white and black). If a bit in the image data is 
clear, it points to the first palette entry. If the bit is set, it points to the 
second. In 4-bit mode the color table must contain 16 colors. Every byte in the 
image data represents two pixels. The byte is split into the higher 4 bits and 
the lower 4 bits and each value of them points to a palette entry. There are 
also standard colors for 16 colors mode (16 out of Windows 20 reserved colors 
(without the entries 8, 9, 246, 247)). Note that you do not need to use this 
standard colors if the bitmap is to be displayed on a screen which support 256 
colors or more, however (nearly) every 4-bit image uses this standard colors. 
In 8-bit mode every byte represents a pixel. The value points to an entry in the 
color table which contains 256 entries (for details see Palettes in Windows. In 
24-bit mode three bytes represent one pixel. The first byte represents the red 
part, the second the green and the third the blue part. There is no need for a 
palette because every pixel contains a literal RGB-value, so the palette is 
omitted.

Note that the term palette does not refer to a RGBQUAD array, which is called 
color table instead. Also note that, in a color table (RGBQUAD), the 
specification for a color starts with the blue byte. In a palette a color always 
starts with the red byte. There is no simple way to map the whole color table 
into a LOGPALETTE structure, which you will need to display the bitmap. You will 
have to write a function that copies byte after byte.

The pixel data:
It depens on the BITMAPINFOHEADER structure how the pixel data is to be 
interpreted. It is important to know that the rows of a DIB are stored upside 
down. That means that the uppest row which appears on the screen actually is 
the lowest row stored in the bitmap. You do not need to turn around the rows 
manually. The API functions which also display the bitmap will do that for you 
automatically. Another important thing is that the number of bytes in one row 
must always be adjusted to fit into the border of a multiple of four. You 
simply append zero bytes until the number of bytes in a row reaches a multiple 
of four, an example:

6 bytes that represent a row in the bitmap: A0 37 F2 8B 31 C4 
                          must be saved as: A0 37 F2 8B 31 C4 00 00 

to reach the multiple of four which is the next higher after six (eight). If 
you keep these few rules in mind while working with .bmp files it should be 
easy for you, to master it.

Copyright 1998 Stefan Hetzl.
*/

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------

#include <stdio.h>
#include "nektar/nektar.h"

//------------------------------------------------------------------------------
// defines 
//------------------------------------------------------------------------------

#define BM 19778  // 0x424D   // Windows 3.1x, 95, NT, 2000, ...
#define BA 0x4241   // OS/2 Bitmap Array
#define CI 0x4349   // OS/2 Color Icon
#define CP 0x4350   // OS/2 Color Pointer
#define IC 0x4943   // OS/2 Icon
#define PT 0x5054   // OS/2 Pointer

//------------------------------------------------------------------------------
// typedef
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// enums
//------------------------------------------------------------------------------

typedef enum _BITMAPCOMPRESSIONMETHOD 
{
  BI_RGB = 0,     // no compression
  BI_RLE8,        // run length encoding 8-bits/pixel
  BI_RLE4,        // run length encoding 4-bits/pixel
  BI_BITFIELDS,   // bitfields 16/32-bit/pixel
  BI_JPEG,        // for printer drivers, not supported on screen
  BI_PNG,         // for printer drivers, not supported on screen

} nkBitmapCompressionMethod;

//------------------------------------------------------------------------------
// structs
//------------------------------------------------------------------------------

#pragma pack(push)  // push the current alignment to the stack
#pragma pack(1)     // tightly pack the data since memory dump

typedef struct _BITMAPFILEHEADER
{
  u16 bf_type;         // usually 'BM' (19778), this defines the file as bitmap
  u32 bf_file_size;    // size of the file in bytes
  u16 bf_reserved1;    // value depends on creation application
  u16 bf_reserved2;    // value depends on creation application
  u32 bf_bmp_offset;   // offset from the start of the file to the bitmap data

} nkBitmapFileHeader;

typedef struct _BITMAPINFOHEADER
{
  u32 bi_header_size;      // size of the BITMAPINFOHEADER structure, in bytes (40)
  i32 bi_width;            // width of the image in pixels
  i32 bi_height;           // height of the image in pixels
  u16 bi_planes;           // number of planes of the target device, must be set to 1
  u16 bi_bits_per_pixel;   // number of bits per pixel (color depth) 1,4,8,16,24,32
  u32 bi_compression;      // type of compression used
  u32 bi_image_size;       // size of the image data, in bytes, w/o compression 0 valid
  i32 bi_horizontal_res;   // horizontal image resolution, pixels per meter 
  i32 bi_vertical_res;     // vertical image resolution, pixels per meter
  u32 bi_colors;           // # of colors used in the bitmap, default 0 means 2^n
  u32 bi_colors_important; // # of colors that are 'important' for the bitmap, default 0 means all colors important

} nkBitmapInfoHeader;

typedef struct _RGBQUAD
{
  u8 green;         // green part of the color
  u8 blue;          // blue part of the color
  u8 red;           // red part of the color
  u8 reserved;      // always set to 0

} nkRGBQuad;

typedef struct _BITMAPINFO 
{
  nkBitmapInfoHeader bmiHeader;
  nkRGBQuad          bmiColors[1];

} nkBitmapInfo;

#pragma pack(pop)

//------------------------------------------------------------------------------
// interface definition
//------------------------------------------------------------------------------

FILE* openBitmap(const char* path, nkBitmapFileHeader *file_header, nkBitmapInfoHeader *info_header);
bool  readBitmap(FILE *bitmap, nkBitmapInfoHeader *header, i8 *buffer);

u32 getBitmapImageSize(nkBitmapInfoHeader *info_header);

u32 doBitmap(const char* path);

//------------------------------------------------------------------------------
// interface implementation
//------------------------------------------------------------------------------

inline u32 getBitmapImageSize(nkBitmapInfoHeader *info_header) 
{
  // calculate the number of bytes to read for the actual image
  i32 image_size = info_header->bi_image_size;
  if (image_size == 0)
  {
    // ensure padding to the word
    image_size = info_header->bi_width * 
                 -info_header->bi_height * 
                 ((info_header->bi_bits_per_pixel + 7) / 8);
  }

  return (image_size);
}

#endif // _NKBITMAP_H_
