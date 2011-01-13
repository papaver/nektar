//------------------------------------------------------------------------------
// nkShaderBase.cpp
//------------------------------------------------------------------------------

#include "render/shader/nkShaderBase.h"
#include "nektar/nektar.h"
#include "utils/nk_iphone.h"

//------------------------------------------------------------------------------
// interface implementation
//------------------------------------------------------------------------------

nkShaderBase::~nkShaderBase()
{
  GLuint program = getProgram();
  if (program)
  {
    glDeleteProgram(program);
    setProgram(0);
  }
}

//------------------------------------------------------------------------------

bool nkShaderBase::loadProgram(const GLchar *name)
{
  GLuint vertex_shader;
  GLuint fragment_shader;

  const u32 path_size   = 512;
  const u32 source_size = 4096;
  char shader_path[path_size];
  char shader_source[source_size];

  // create shader program
  GLuint program = glCreateProgram();
  setProgram(program);

  // load vertex shader
  nkiPhone::getFilePath(name, "vsh", shader_path, path_size);
  nkiPhone::readAsciiFile(shader_path, shader_source, source_size);
  compileShader(&vertex_shader, GL_VERTEX_SHADER, shader_source);
  glAttachShader(program, vertex_shader);

  // load fragment shader
  nkiPhone::getFilePath(name, "fsh", shader_path, path_size);
  nkiPhone::readAsciiFile(shader_path, shader_source, source_size);
  compileShader(&fragment_shader, GL_FRAGMENT_SHADER, shader_source);
  glAttachShader(program, fragment_shader);

  // bind attribute locations, this needs to be done prior to linking
  onBindAttributeLocations(program);
    
  // link program
  linkProgram(program);

  // get uniform locations
  onSaveUniformLocations(program);

  // release vertex/fragment shaders
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
	
  return true;
}

//------------------------------------------------------------------------------

bool nkShaderBase::compileShader(GLuint *shader, GLuint type, const GLchar *source)
{
  // make sure your source is kosher!
  NK_ASSERT(source);

  // compile shader
  *shader = glCreateShader(type);
  glShaderSource(*shader, 1, &source, NULL);
  glCompileShader(*shader);
  
  // log shader compile step
  logShaderInfo(*shader);
    
  // [moiz] should this just be an assert? is it a valid assumption
  //  that all the shaders being used should compiler properly?
  // make sure the shader compiled
  GLint status;
  glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
  return (!!status);
}

//------------------------------------------------------------------------------

bool nkShaderBase::linkProgram(GLuint program)
{
  // link shaders into a program
  glLinkProgram(program);

  // log program link step
  logProgramInfo(program);
    
  // [moiz] should this just be an assert? is it a valid assumption
  //  that all the shaders being used should compiler properly?
  // make sure the program linked
  GLint status;
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  return (!!status);
}


//------------------------------------------------------------------------------

bool nkShaderBase::validateProgram()
{
  GLuint program = getProgram();

  // validate program
  glValidateProgram(program);

  // log validation
  logProgramInfo(program);

  // check program status
  GLint status;
  glGetProgramiv(program, GL_VALIDATE_STATUS, &status);
  return (!!status);
}

//------------------------------------------------------------------------------

#if (BUILD < BUILD_FINAL)

void nkShaderBase::logProgramInfo(GLuint program) 
{
  GLint log_length;
  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
  if (log_length > 0)
  {
    // [moiz] add a skipable gameplay assert here
    GLchar *log = (GLchar*)nk_malloc(log_length);
    glGetProgramInfoLog(program, log_length, &log_length, log);
    nk_error(log);
    nk_free(log);
  }
}

#endif 

//------------------------------------------------------------------------------

#if (BUILD < BUILD_FINAL)

void nkShaderBase::logShaderInfo(GLuint shader) 
{
  GLint log_length;
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
  if (log_length > 0)
  {
    // [moiz] add a skipable gameplay assert here
    GLchar *log = (GLchar *)nk_malloc(log_length);
    glGetShaderInfoLog(shader, log_length, &log_length, log);
    nk_error(log);
    nk_free(log);
  }
}

#endif 

