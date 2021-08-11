#ifndef _SG_FONT_H__

#define _SG_FONT_H__



class clText

	{

	public:

	enum FontStyle

		{

		GFONT_NORMAL=0,

		GFONT_BOLD=1,

		GFONT_ITALIC=2,

		GFONT_UNDERLINE=4

		};







	static void createFont(int fid, int size,FontStyle typeflags);

	static void draw(unsigned font, float size, float x,float y,const char * string, float* color = 0, FontStyle typeflags = GFONT_NORMAL);

	static void start();	//call when starting to draw text in a frame

	static void end();		//call after not drawing any text this frame anymore

	static void shutDown();

/*

Font scaling: 

A size of 1 indicates that the font's A character's height is exactly half the viewport.

A size of 2 is half that large.

The string is centered in the x direction if x == 1 (which is off screen for regular positioning), else it is drawn

at x,y (lower left corner of first char) on an (-1,1)(-1,1) cartesian plane.

Same applies to the y direction.



*/

	};



#endif