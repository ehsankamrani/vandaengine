/*

*  Simple SGI .rgb (IRIS RGB) image file reader ripped off from

*  texture.c (written by David Blythe).  See the SIGGRAPH '96

*  Advanced OpenGL course notes.

Modified by Adam Moravanszky



*/





/* includes */



/*#if defined WIN32

#include <windows.h> 

#endif



 #include <GL/gl.h> 

 #include <GL/glu.h>  

*/



/* wgl typedefs */



typedef unsigned int GLenum;

typedef unsigned char GLboolean;

typedef unsigned int GLbitfield;

typedef signed char GLbyte;

typedef short GLshort;

typedef int GLint;

typedef int GLsizei;

typedef unsigned char GLubyte;

typedef unsigned short GLushort;

typedef unsigned int GLuint;

typedef float GLfloat;

typedef float GLclampf;

typedef double GLdouble;

typedef double GLclampd;

typedef void GLvoid;



/* Boolean */

#ifndef GL_TRUE

#define GL_TRUE                           1

#endif

#ifndef GL_FALSE

#define GL_FALSE                          0

#endif



/* GLTXimage: Structure containing a texture image */

struct GLTXimage

	{

	GLuint   width;			/* width of image */

	GLuint   height;			/* height of image */

	GLuint   origWidth;

	GLuint   origHeight;

	GLuint   components;			/* number of components in image */

	GLenum   format;

	GLubyte* data;			/* image data */



	inline GLubyte & operator()( unsigned y, unsigned x, unsigned z = 0 )

		{

		return  data[ y * width*components + x*components + z  ]  ;	//returns reference to start of scan line.

		}

	};





/* gltxDelete: Deletes a texture image

* 

* image - properly initialized GLTXimage structure

*/

void gltxDelete(GLTXimage* image);

GLTXimage* gltxReadBMP(char const* sFileName);

bool gltxWriteBMP(const char * sFileName, GLTXimage* image);

