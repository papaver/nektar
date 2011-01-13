//------------------------------------------------------------------------------
// nkTarga.cpp
//------------------------------------------------------------------------------

#include "nektar/nektar.h"
#include "io/image/nkTarga.h"

//------------------------------------------------------------------------------
// interface implementation
//------------------------------------------------------------------------------

FILE* openTarga(const char* path, TargaHeader *header)
{
  // attempt to open the file for read
  FILE *file = fopen(path, "rb");
  if (file == NULL)
  {
    nk_error("Failed to open targa '%s'.", path);
    return NULL;
  }

  // get the targa file header from the stream
  if (fread(header, sizeof(TargaHeader), 1, file) != 1)
  {
    fclose(file);
    nk_error("Failed to read header from file '%s'\n.", path);
    return NULL;
  }

  // minumum support currently...
  char8_t type = header->thImageType;
  if ((type != 2) && (type != 3))
  {
    fclose(file);
    nk_error("Unsupported targa type '%s'\n.", path);
    return NULL;
  }

  return file;
}

//------------------------------------------------------------------------------

bool readTarga(FILE *targa, TargaHeader *header, char *buffer)
{
  int32_t mode       = getTargaMode(header);
  int32_t image_size = getTargaImageSize(mode, header);

  // read in the image from the file
  if (fread(buffer, image_size, 1, targa) != 1)
  {
    nk_error("Failed to read image from file.");
    return false;
  }

  // swap bits if required
  if (mode >= 3) 
  {
    for (int i = 0; i < image_size; i += mode)
    {
      buffer[i]   ^= buffer[i+2];
      buffer[i+2] ^= buffer[i];
      buffer[i]   ^= buffer[i+2];
    }
  }

  return true;
}

