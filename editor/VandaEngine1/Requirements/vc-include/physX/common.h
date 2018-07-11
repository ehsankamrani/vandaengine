#ifndef COMMON_HEADER_FILE
#define COMMON_HEADER_FILE

#ifndef __PPCGEKKO__
inline void glVertexPointer (GLint size, GLenum type, GLsizei stride, GLuint buffer_size, const GLvoid *pointer)
{
	glVertexPointer(size, type, stride, pointer);
}

inline void glTexCoordPointer (GLint size, GLenum type, GLsizei stride, GLuint buffer_size, const GLvoid *pointer)
{
	glTexCoordPointer(size, type, stride, pointer);
}

inline void glNormalPointer (GLenum type, GLsizei stride, GLuint buffer_size, const GLvoid *pointer)
{
	glNormalPointer(type, stride, pointer);
}

inline void glColorPointer (GLint size, GLenum type, GLsizei stride, GLuint buffer_size, const GLvoid *pointer)
{
	glColorPointer(size, type, stride, pointer);
}
#endif

#endif
