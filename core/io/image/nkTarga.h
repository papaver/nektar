//------------------------------------------------------------------------------
// nkTarga.h
//------------------------------------------------------------------------------

#ifndef _NKTARGA_H_
#define _NKTARGA_H_

/*

Header:
Field Length  name            Description
1     1       thIdLength      Length of the image ID field
2     1       thColorMapType  Whether a color map is included
3     1       thImageType     Compression and color types
4     5       thColorMapSpec  Describes the color map
5     10      thImageSpec     Image dimensions and format

Image and color map data:
Field Length          name           Description
6     thIdLength      tdImageId      Optional field containing identifying info
7     thColorMapSpec  tdColorMapData Look-up table containing color map data
8     thImageSpec     tdImageData    Stored according to the image descriptor

-- Image ID length (field 1)

0 - 255 The number of bytes that the image ID field consists of. The image ID 
field can contain any information, but it is common for it to contain the date 
and time the image was created or a serial number. As of version 2.0 of the TGA 
spec, the date and time the image was created is catered for in the extension 
area.

-- Color map type (field 2)

0 if image file contains no color map
1 if present
2-127 reserved by Truevision
128-255 available for developer use

-- Image type (field 3)

is enumerated in the lower three bits, with the fourth bit as a flag for RLE. 
Some possible values are:

0 no image data is present,
1 uncompressed, color-mapped image,
2 uncompressed, true-color image,
3 uncompressed, black-and-white image,
9 run-length encoded, color-mapped Image,
10 run-length encoded, true-color image and,
11 run-length encoded, black-and-white Image

-- Color map specification (field 4)

First entry index (2 bytes): offset into the color map table
Color map length (2 bytes): number of entries
Color map entry size (1 byte): number of bits per pixel

-- Image specification (field 5)

X-origin (2 bytes): absolute coordinate of lower-left corner for displays where origin is at the lower left
Y-origin (2 bytes): as for X-origin
Image width (2 bytes): width in pixels
Image height (2 bytes): height in pixels
Pixel depth (1 byte): bits per pixel
Image descriptor (1 byte): bits 3-0 give the alpha channel depth, bits 5-4 give direction

*/

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h> 

//------------------------------------------------------------------------------
// typedef
//------------------------------------------------------------------------------

typedef char  char8_t;
typedef short short16_t;
typedef int   int32_t;

//------------------------------------------------------------------------------
// structs
//------------------------------------------------------------------------------

#pragma pack(push)  // push the current alignment to the stack
#pragma pack(1)     // set boundy to one since we are trying to fill the structures with a memory dump


typedef struct _TARGACOLORMAPSPEC
{
  short16_t tcmpFirstEntryIndex;   // offset into the color map table
  short16_t tcmpColorMapLength;    // number of entries
  char8_t   tcmpColorMapEntrySize; // number of bits per pixel

} TargaColorMapSpec;

typedef struct _TARGAIMAGESPEC
{
  short16_t tisXorigin;         // absolute coordinate of lower-left corner for displays where origin is at the lower left
  short16_t tisYorigin;         // as for X-origin
  short16_t tisImageWidth;      // width in pixels
  short16_t tisImageHeight;     // height in pixels
  char8_t   tisPixelDepth;      // bits per pixel
  char8_t   tisImageDescriptor; // bits 3-0 give the alpha channel depth, bits 5-4 give direction

} TargaImageSpec;

typedef struct _TARGAHEADER
{
  char8_t           thIdLength;     // Length of the image ID field
  char8_t           thColorMapType; // Whether a color map is included
  char8_t           thImageType;    // Compression and color types
  TargaColorMapSpec thColorMapSpec; // Describes the color map
  TargaImageSpec    thImageSpec;    // Image dimensions and format

} TargaHeader;

#pragma pack(pop)

//------------------------------------------------------------------------------
// interface definition
//------------------------------------------------------------------------------

FILE* openTarga(const char* path, TargaHeader *header);
bool  readTarga(FILE *targa, TargaHeader *header, char *buffer);

int32_t getTargaMode(TargaHeader *header);
int32_t getTargaImageSize(int32_t mode, TargaHeader *header);

//------------------------------------------------------------------------------
// interface implementation
//------------------------------------------------------------------------------

inline int32_t getTargaMode(TargaHeader *header) 
{  
  // calculate the number of bytes to read for the actual image
  int32_t mode = header->thImageSpec.tisPixelDepth / 8;
  return mode;
}

//------------------------------------------------------------------------------

inline int32_t getTargaImageSize(int32_t mode, TargaHeader *header) 
{  
  // calculate the number of bytes to read for the actual image
  int32_t image_size = header->thImageSpec.tisImageWidth * 
                       header->thImageSpec.tisImageHeight *
                       mode;
  return image_size;
}

#endif // _NKTARGA_H_
