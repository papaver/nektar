//------------------------------------------------------------------------------
// nk_iphone.cpp
//------------------------------------------------------------------------------

#include <stdio.h>
#include <CoreFoundation/CoreFoundation.h>

#include "utils/nk_iphone.h"

//------------------------------------------------------------------------------
// interface implementation
//------------------------------------------------------------------------------

bool nkiPhone::getFilePath(const char *name, const char *type, char *path, u32 size)
{
  // grab main bundle
  CFBundleRef mainBundle;
  mainBundle = CFBundleGetMainBundle();
  if (!mainBundle)
  {
    return false;
  }

  // convert to cf strings
  CFStringRef fileName;
  CFStringRef fileType;
  fileName = CFStringCreateWithCString(NULL, name, kCFStringEncodingASCII);
  fileType = CFStringCreateWithCString(NULL, type, kCFStringEncodingASCII);

  // get url of resource 
  CFURLRef resourceURL;
  resourceURL = CFBundleCopyResourceURL(mainBundle, fileName, fileType, NULL);
  if (!resourceURL)
  {
    return false;
  }

  // get path to file
  CFURLGetFileSystemRepresentation(resourceURL, true, (UInt8*)path, size);

  // release resources
  CFRelease(resourceURL);
  CFRelease(fileType);
  CFRelease(fileName);

  // should we not be releasing the main bundle here?
  // it causes the system to crash when trying to access
  // the bundle after a couple of releases
  //CFRelease(mainBundle);

  return true;
}

//------------------------------------------------------------------------------

bool nkiPhone::readAsciiFile(const char *path, char *contents, u32 size)
{
  FILE *file;
  i64   file_size;

  // open the file
  file = fopen(path, "r");
  if (!path) 
  {
    return false;
  }

  // get file size
  fseek(file, 0, SEEK_END);
  file_size = ftell(file);
  rewind(file);
  
  NK_ASSERT(file_size <= size);

  // copy the file into the buffer:
  i32 result = fread(contents, 1, file_size, file);
  if (result != file_size) 
  {
    fclose (file);
    return false;
  }

  // terminate the data
  contents[result] = '\0';

  // close file
  fclose (file);

  return true;
}
