//------------------------------------------------------------------------------
// nkRenderUtils.cpp
//------------------------------------------------------------------------------

#include "nektar/nektar.h"
#include "render/nkRenderUtils.h"
#include "io/image/nkBitmap.h"
#include "io/image/nkTarga.h"

//------------------------------------------------------------------------------
// interface implementation
//------------------------------------------------------------------------------

GLuint loadDefaultTexture()
{
   // texture object handle
   GLuint textureId;
   
   // 2x2 Image, 3 bytes per pixel (R, G, B)
   GLubyte pixels[4 * 3] =
   {  
      255,   0,   0, // Red
        0, 255,   0, // Green
        0,   0, 255, // Blue
      255, 255,   0  // Yellow
   };

   // use tightly packed data
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   // generate a texture object
   glGenTextures(1, &textureId);

   // bind the texture object
   glBindTexture(GL_TEXTURE_2D, textureId);

   // load the texture
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

   // set the filtering mode
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   return textureId;
}

//------------------------------------------------------------------------------

GLuint loadTargaTexture(const char *path) 
{
  // setup targa header
  TargaHeader header;

  // open the targa file
  FILE *targa = openTarga(path, &header);
  if (!targa) 
  {
    return -1;
  }

  // allocate space for the image
  i32 mode       = getTargaMode(&header);
  i32 image_size = getTargaImageSize(mode, &header);
  char *buffer   = (char*)nk_malloc(image_size);
  if (buffer == NULL)
  {
    fclose(targa);
    nk_error("Failed to allocate memory for the targa image '%s'.", path);
    return -1;
  }

  // read in the image
  if (!readTarga(targa, &header, buffer))
  {
    fclose(targa);
    return -1;
  }

  int width  = header.thImageSpec.tisImageWidth;
  int height = header.thImageSpec.tisImageHeight;
  
  // texture object handle
  GLuint texture_id;
  
  // Use tightly packed data
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  
  // Generate a texture object
  glGenTextures(1, &texture_id);
  
  // Bind the texture object
  glBindTexture(GL_TEXTURE_2D, texture_id);
  
  // Load the texture
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
  
  // Set the filtering mode
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
  
  // free the bits
  nk_free(buffer);

  // close file
  fclose(targa);

  return texture_id;
}

//------------------------------------------------------------------------------

GLuint loadBitmapTexture(const char *path) 
{
  // setup bitmap headers
  nkBitmapFileHeader file_header; 
  nkBitmapInfoHeader info_header;
  openBitmap(path, &file_header, &info_header);

  // open the targa file
  FILE *bitmap = openBitmap(path, &file_header, &info_header);
  if (!bitmap) 
  {
    return -1;
  }

  // allocate space for the image
  i32 image_size = getBitmapImageSize(&info_header);
  char *buffer   = (char*)nk_malloc(image_size);
  if (buffer == NULL)
  {
    fclose(bitmap);
    nk_error("Failed to allocate memory for the bitmap image '%s'.", path);
    return -1;
  }

  // read in the image
  if (!readBitmap(bitmap, &info_header, buffer))
  {
    fclose(bitmap);
    return -1;
  }

  int width  = info_header.bi_width;
  int height = info_header.bi_height;
  
  // texture object handle
  GLuint texture_id;
  
  // Use tightly packed data
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  
  // Generate a texture object
  glGenTextures(1, &texture_id);
  
  // Bind the texture object
  glBindTexture(GL_TEXTURE_2D, texture_id);
  
  // Load the texture
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
  
  // Set the filtering mode
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
  
  // free the bits
  nk_free(buffer);

  // close file
  fclose(bitmap);

  return texture_id;
}

