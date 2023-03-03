/*-----------------------------------------------------------
This is a very simple TGA lib. It will only load and save 
uncompressed images in greyscale, RGB or RGBA mode.

If you want a more complete lib I suggest you take 
a look at Paul Groves' TGA loader. Paul's home page is at 

	http://paulyg.virtualave.net


Just a little bit about the TGA file format.

Header - 12 fields

	
id						unsigned char
colour map type			unsigned char
image type				unsigned char

	1	-	colour map image
	2	-	RGB(A) uncompressed
	3	-	greyscale uncompressed
	9	-	greyscale RLE (compressed)
	10	-	RGB(A) RLE (compressed)

colour map first entry	short int
colour map length		short int
map entry size			short int

horizontal origin		short int
vertical origin			short int
width					short int
height					short int
pixel depth				unsigned char

	8	-	greyscale
	24	-	RGB
	32	-	RGBA

image descriptor		unsigned char

From all these fields, we only care about the image type, 
to check if the image is uncompressed and not color indexed, 
the width and height, and the pixel depth.

You may use this library for whatever you want. This library is 
provide as is, meaning that I won't take any responsability for
any damages that you may incur for its usage.

Antonio Ramires Fernandes ajbrf@yahoo.com
-------------------------------------------------------------*/

#define	TGA_ERROR_FILE_OPEN				-5
#define TGA_ERROR_READING_FILE			-4
#define TGA_ERROR_INDEXED_COLOR			-3
#define TGA_ERROR_MEMORY				-2
#define TGA_ERROR_COMPRESSED_FILE		-1
#define TGA_OK							 0


typedef struct {
	int status;
	unsigned char type, pixelDepth;
	short int width, height;
	unsigned char *imageData;
}tgaInfo;

tgaInfo* tgaLoad(char *filename);

int tgaSave(char			*filename, 
			 short int		width, 
			 short int		height, 
			 unsigned char	pixelDepth, 
			 unsigned char	*imageData);

int tgaSaveSeries(char			*filename, 
			 short int		width, 
			 short int		height, 
			 unsigned char	pixelDepth, 
			 unsigned char	*imageData);

void tgaRGBtoGreyscale(tgaInfo *info);

int tgaGrabScreenSeries(char *filename, int x,int y, int w, int h);

void tgaDestroy(tgaInfo *info);
