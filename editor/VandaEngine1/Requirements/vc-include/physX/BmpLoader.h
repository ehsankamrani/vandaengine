#ifndef BMP_LOADER_H
#define BMP_LOADER_H

class BmpLoader
{
public:

	BmpLoader(void);
	~BmpLoader(void);

	// returns number of triangles that were loaded.  Data is persists until the class is destructed.
	bool loadBmp(const char *filename); 

	int	           mWidth;
	int	           mHeight;
	unsigned char *mRGB;
};

#endif
