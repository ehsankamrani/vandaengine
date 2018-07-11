#include "stdafx.h"
#include "bitmap.h" 

CBitmapTexture::CBitmapTexture()
{
}

CBitmapTexture::~CBitmapTexture()
{
}

CBool CBitmapTexture::CLoad( CChar *filename)
{
	m_bitmapImage = NULL;
	m_bitmapImageWithAlpha = NULL;
	memset( &m_bitmapFileHeader, 0, sizeof( BITMAPFILEHEADER ) );
	memset( &m_bitmapInfoHeader, 0, sizeof( BITMAPINFOHEADER ) );

	FILE *filePtr;			// the file pointer
	CInt	imageIdx = 0;		// image index counter
	// open filename in "read binary" mode
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL)
		return CFalse;
	// read the bitmap file header
	fread(&m_bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
		
	// verify that this is a bitmap by checking for the universal bitmap id
	if (m_bitmapFileHeader.bfType != 0x4D42 )
	{
		fclose(filePtr);
		return CFalse;
	}
	// read the bitmap information header
	fread(&m_bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
	// move file pointer to beginning of bitmap data
	fseek(filePtr, m_bitmapFileHeader.bfOffBits, SEEK_SET);
	// allocate enough memory for the bitmap image data
	m_bitmapImage = new CUChar[m_bitmapInfoHeader.biSizeImage];
	// verify memory allocation
	if (!m_bitmapImage)
	{
		fclose(filePtr);
		return CFalse;
	}

	// read in the bitmap image data
	fread(m_bitmapImage, 1, m_bitmapInfoHeader.biSizeImage, filePtr);
	// make sure bitmap image data was read
	if (m_bitmapImage == NULL)
	{
		fclose(filePtr);
   		return CFalse;
	}

	// close the file and return the bitmap image data
	fclose(filePtr);

	return CTrue;
}

CBool CBitmapTexture::CLoadWithAlpha( CChar* filename )
{
	if( CLoad( filename ) )
	{
		  m_bitmapImageWithAlpha = new CUChar[m_bitmapInfoHeader.biSizeImage * 4 / 3];
		  if( m_bitmapImageWithAlpha == NULL )
			  return CFalse;

    	  for (unsigned CInt src = 0, dst = 0; src < m_bitmapInfoHeader.biSizeImage; src +=3, dst +=4)
          {
              // if the pixel is black, set the alpha to 0. Otherwise, set it to 255.
              if (m_bitmapImage[src] == 0 && m_bitmapImage[src+1] == 0 && m_bitmapImage[src+2] == 0)
                  m_bitmapImageWithAlpha[dst+3] = 0;
              else
                  m_bitmapImageWithAlpha[dst+3] = 0xFF;

              // copy pixel data over
              m_bitmapImageWithAlpha[dst] = m_bitmapImage[src];
              m_bitmapImageWithAlpha[dst+1] = m_bitmapImage[src+1];
              m_bitmapImageWithAlpha[dst+2] = m_bitmapImage[src+2];
          }

		  return CTrue;
	}
	return CFalse;
}

CVoid CBitmapTexture::CUnload()
{
	if( m_bitmapImage != NULL )
	{
		delete [] m_bitmapImage;
		m_bitmapImage = NULL;
	}
	if( m_bitmapImageWithAlpha != NULL )
	{
		delete[] m_bitmapImageWithAlpha;
		m_bitmapImageWithAlpha = NULL;
	}
    memset( &m_bitmapInfoHeader, 0, sizeof( m_bitmapInfoHeader ) );
	memset( &m_bitmapFileHeader, 0, sizeof( m_bitmapFileHeader ) );
}
