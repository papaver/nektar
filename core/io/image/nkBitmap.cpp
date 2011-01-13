//------------------------------------------------------------------------------
// nkBitmap.cpp
//------------------------------------------------------------------------------

#include "nektar/nektar.h"
#include "io/image/nkBitmap.h"

#include "io/nkTextureManager.h"

#include <math.h>

//------------------------------------------------------------------------------
// interface implementation
//------------------------------------------------------------------------------

void print(nkBitmapFileHeader *header);
void print(nkBitmapInfoHeader *header);

u32 doBitmap(const char* path)
{
  nkBitmapFileHeader file_header;
  nkBitmapInfoHeader info_header;

  // attempt to open the file for read
  FILE* file = fopen(path, "rb");
  if (file == NULL)
  {
    nk_error("Failed to open bitmap '%s'.", path);
    return false;
  }

  // get the bitmap file header from the stream
  if (fread(&file_header, sizeof(nkBitmapFileHeader), 1, file) != 1)
  {
    fclose(file);
    nk_error("Failed to read file-header from '%s'\n.", path);
    return false;
  }

  // check if header has valid bitmap type tag
  if (file_header.bf_type != BM)
  {
    switch (file_header.bf_type)
    {
      case BA:
      case CI:
      case CP:
      case IC:
      case PT:
        nk_error("Bitmap types of OS/2 not supported: '%s'.\n", path);
        break;

      default:
        nk_error("Bitmap type unknown: '%s'\n", path);
        break;
    }

    fclose(file);
    return false;
  }

  // get the bitmap info header from the stream
  if (fread(&info_header, sizeof(nkBitmapInfoHeader), 1, file) != 1)
  {
    fclose(file);
    nk_error("Failed to read info header from '%s'\n.", path);
    return false;
  }

  print(&file_header);
  print(&info_header);

  // load color palette
  u32 palette_colors = pow(2, info_header.bi_bits_per_pixel);
  nkRGBQuad *palette = (nkRGBQuad*)nk_malloc(sizeof(nkRGBQuad) * palette_colors);
  if (fread(palette, sizeof(nkRGBQuad), palette_colors, file) != palette_colors)
  {
    fclose(file);
    nk_error("Failed to read color palette from '%s'\n.", path);
    return false;
  }

  // load image
  u32 image_size = info_header.bi_image_size; 
  u8 *image = (u8*)nk_malloc(image_size);
  if (fread(image, image_size, 1, file) != 1)
  {
    fclose(file);
    nk_error("Failed to read image from '%s'\n.", path);
    return false;
  }

  // figure out proper size to load data into
  u32 width  = GetHighestPowerOfTwo(info_header.bi_width);
  u32 height = GetHighestPowerOfTwo(info_header.bi_height);

  typedef struct rgb {
    u8 r,g,b;
  };

  // allocate space for final image
  rgb *final_image = (rgb*)nk_malloc(sizeof(rgb) * width * height);

  // ensure padding to the dword
  u32 line_width = GetHighestMultipleOfPowerOfTwo(info_header.bi_width * info_header.bi_bits_per_pixel, 32);

  u8 one_bit_masks[8]   = { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 };
  u8 four_bit_masks[2]  = { 0xF0, 0x0F };
  u8 eight_bit_masks[1] = { 0xFF };

  u8 *masks[3] = { one_bit_masks, four_bit_masks, eight_bit_masks };

  u8 *bit_masks = masks[info_header.bi_bits_per_pixel / 4];

  u32 bits_per_pixel  = info_header.bi_bits_per_pixel;
  u32 pixels_per_byte = 8 / bits_per_pixel;

  // decode image 
  for (u32 y = 0; y < info_header.bi_height; ++y) 
  {
    for (u32 x = 0; x < info_header.bi_width; ++x)
    {
      // locate bit
      u32 index = (line_width * y) + (x * bits_per_pixel);
      u32 byte  = index / 8;
      u32 bit   = (index % 8) / bits_per_pixel;

      u8  mask  = bit_masks[bit];
      u32 shift = ((pixels_per_byte - 1) - bit) * bits_per_pixel;
      u32 palette_index = (image[byte] & mask) >> shift;

      // swap the blue/green channels
      nkRGBQuad *palette_entry = &palette[palette_index];
      final_image[(y * width) + x].r = palette_entry->red;
      final_image[(y * width) + x].g = palette_entry->blue;
      final_image[(y * width) + x].b = palette_entry->green;
    }
  }

  nkTexture *texture = TEXTURE::LoadBuffer((u8*)final_image, RGB_888, width, height);

  // cleanup  
  nk_free(image);
  nk_free(palette);
  nk_free(final_image);
  fclose(file);

  return texture->m_id;
}

//------------------------------------------------------------------------------

void print(nkBitmapFileHeader *header)
{
  nk_print("BitmapFileHeader:\n");
  nk_print("  type: %c%c\n",     (header->bf_type & 0x00FF), (header->bf_type >> 8));
  nk_print("  file size: %d\n",  header->bf_file_size);
  nk_print("  reserved1: %d\n",  header->bf_reserved1);
  nk_print("  reserved1: %d\n",  header->bf_reserved2);
  nk_print("  bmp offset: %d\n", header->bf_bmp_offset);
} 

void print(nkBitmapInfoHeader *header)
{
  const u32 compression_count = 6;
  static const char *s_compression2str[compression_count] = {
    "RGB", "RLE8", "RLE4", "BITFIELDS", "JPEG", "PNG" 
  };

  nk_print("BitmapInfoHeader:\n");
  nk_print("  header size: %d\n",      header->bi_header_size);
  nk_print("  width: %d\n",            header->bi_width);
  nk_print("  height: %d\n",           header->bi_height);
  nk_print("  planes: %d\n",           header->bi_planes);
  nk_print("  bits per pixel: %d\n",   header->bi_bits_per_pixel);
  nk_print("  compression: %s\n",      s_compression2str[header->bi_compression]);
  nk_print("  image size: %d\n",       header->bi_image_size);
  nk_print("  horizonal res: %d\n",    header->bi_horizontal_res);
  nk_print("  veritcal res: %d\n",     header->bi_vertical_res);
  nk_print("  colors: %d\n",           header->bi_colors);
  nk_print("  colors important: %d\n", header->bi_colors_important);
}

//------------------------------------------------------------------------------
// old interface implementation
//------------------------------------------------------------------------------

FILE* openBitmap(const char* path, nkBitmapFileHeader *file_header, nkBitmapInfoHeader *info_header)
{
  // attempt to open the file for read
  FILE* file = fopen(path, "rb");
  if (file == NULL)
  {
    nk_error("Failed to open bitmap '%s'.", path);
    return NULL;
  }

  // get the bitmap file header from the stream
  if (fread(file_header, sizeof(nkBitmapFileHeader), 1, file) != 1)
  {
    fclose(file);
    nk_error("Failed to read header from file '%s'\n.", path);
    return NULL;
  }

  // check if header has valid bitmap type tag
  if (file_header->bf_type != BM)
  {
    switch (file_header->bf_type)
    {
      case BA:
      case CI:
      case CP:
      case IC:
      case PT:
        nk_error("Bitmap types of OS/2 not supported: '%s'.\n", path);
        break;

      default:
        nk_error("Bitmap type unknown: '%s'\n", path);
        break;
    }

    fclose(file);
    return NULL;
  }

  // get the bitmap info header from the stream
  if (fread(info_header, sizeof(nkBitmapInfoHeader), 1, file) != 1)
  {
    fclose(file);
    nk_error("Failed to read info header from '%s'\n.", path);
    return NULL;
  }

  return file;
}

//------------------------------------------------------------------------------

bool readBitmap(FILE *bitmap, nkBitmapInfoHeader *header, i8 *buffer)
{
  // calculate the number of bytes to read for the actual image
  u32 image_size = getBitmapImageSize(header);
     
  // read in the image from the file
  if (fread(buffer, image_size, 1, bitmap) != 1)
  {
    nk_error("Failed to read image info from file.");
    return false;
  }

  // moiz:: dammit!!! wtf is this shit??
  //  why is it in BGR format!!! 
  for (int i = 0; i < image_size; i += 3)
  {
    buffer[i]   ^= buffer[i+2];
    buffer[i+2] ^= buffer[i];
    buffer[i]   ^= buffer[i+2];
  }

  return true;
}

