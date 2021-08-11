// Simple class to contain GLSL shaders/programs

#ifndef GLSL_PROGRAM_H
#define GLSL_PROGRAM_H

#include <GL/glew.h>
#include <stdio.h>

class GLSLProgram
{
public:
    // construct program from strings
	GLSLProgram(const char *vsource, const char *fsource);
    GLSLProgram(const char *vsource, const char *gsource, const char *fsource,
                GLenum gsInput = GL_POINTS, GLenum gsOutput = GL_TRIANGLE_STRIP);
	~GLSLProgram();

	void enable();
	void disable();

	void setUniform1f(const GLchar *name, GLfloat x);
	void setUniform2f(const GLchar *name, GLfloat x, GLfloat y);
    void setUniform3f(const char *name, float x, float y, float z);
    void setUniform4f(const char *name, float x, float y, float z, float w);
	void setUniformfv(const GLchar *name, GLfloat *v, int elementSize, int count=1);
    void setUniformMatrix4fv(const GLchar *name, GLfloat *m, bool transpose);

	void bindTexture(const char *name, GLuint tex, GLenum target, GLint unit);

	inline GLuint getProgId() { return mProg; }
	
private:
    GLuint compileProgram(const char *vsource, const char *gsource, const char *fsource,
                          GLenum gsInput = GL_POINTS, GLenum gsOutput = GL_TRIANGLE_STRIP);
	GLuint mProg;
};

#endif