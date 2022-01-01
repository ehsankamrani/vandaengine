//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "targa.h"

CTargaTexture::CTargaTexture()
{
	m_sizeX = 0;
	m_sizeY = 0;
	m_bpp = 0;
	m_dest = NULL;
}

CTargaTexture::~CTargaTexture()
{
}

CUChar * CTargaTexture::GetPointer()
{
	return m_dest;
}	

CInt CTargaTexture::GetBpp()
{
	return m_bpp;		
}

CInt CTargaTexture::GetSizeY()
{
	return m_sizeY;
}

CInt CTargaTexture::GetSizeX()
{
	return m_sizeX;
}

CInt CTargaTexture::Release()
{
	if( m_dest != NULL )
	{
		free( m_dest );
		m_dest = NULL;
		return -1;
	}
	return 0;
}

CInt CTargaTexture::ReadFile( const CChar *str )
{
	CUChar l, r, g, b, a;
    CUChar *tmp;
    
    if( m_dest != NULL )
    {
    	return -1;    	
    }
	FILE *file;
	file = fopen( str, "rb" );
	
    if( file == NULL )
        return 0;
        
    // Read the header
    
	m_tgaHeader.idlength = fgetc( file );	
	m_tgaHeader.colourmaptype = fgetc( file );
	m_tgaHeader.datatypecode = fgetc( file );
	m_tgaHeader.colourmaporigin = fgetc( file );
	m_tgaHeader.colourmaporigin += fgetc( file ) <<8 ;
	m_tgaHeader.colourmaplength = fgetc( file );
	m_tgaHeader.colourmaplength += fgetc( file ) << 8; 
	m_tgaHeader.colourmapdepth = fgetc( file );
	m_tgaHeader.x_origin = fgetc( file ); 
	m_tgaHeader.x_origin += fgetc( file ) << 8; 
	m_tgaHeader.y_origin = fgetc( file );
	m_tgaHeader.y_origin += fgetc( file ) << 8;
	m_tgaHeader.sizeX = fgetc( file );
	m_tgaHeader.sizeX += fgetc( file ) << 8;
	m_tgaHeader.sizeY = fgetc( file );
	m_tgaHeader.sizeY += fgetc( file ) << 8;
	m_tgaHeader.bpp = fgetc( file );
	m_tgaHeader.imagedescriptor = fgetc( file );
	
	// Return if the format is unsupported		
	
    if( m_tgaHeader.datatypecode != TGA_TYPE_COLOR
            && m_tgaHeader.datatypecode != TGA_TYPE_GRAY
            && m_tgaHeader.datatypecode != TGA_TYPE_COLOR_RLE )
        return 0;

	
    if( m_tgaHeader.bpp!=8 && m_tgaHeader.bpp!=24 && m_tgaHeader.bpp!=32 )
        return 0;
	
    if( m_tgaHeader.bpp==8 )
        m_dest = (CUChar*)malloc( m_tgaHeader.sizeX * m_tgaHeader.sizeY );
    if( m_tgaHeader.bpp==32 || m_tgaHeader.bpp==24)
        m_dest = (CUChar*)malloc( m_tgaHeader.sizeX * m_tgaHeader.sizeY * 4 );


    if( m_tgaHeader.datatypecode == TGA_TYPE_COLOR || m_tgaHeader.datatypecode == TGA_TYPE_GRAY )
    {
        for(CInt y = 0; y < m_tgaHeader.sizeY; y++)
            for(CInt x = 0; x < m_tgaHeader.sizeX; x++)
            {
                if( m_tgaHeader.bpp == 8 )
                {
                    r = fgetc( file );
                    m_dest[ x + y * m_tgaHeader.sizeX ] = r;
                }
                if( m_tgaHeader.bpp == 24 || m_tgaHeader.bpp == 32 )
                {
                    b = fgetc(file);
                    g = fgetc(file);
                    r = fgetc(file);
					if( m_tgaHeader.bpp == 24 )
                        a = 255;
                    else
                        a = fgetc(file);
					
                    m_dest[ (x + y * m_tgaHeader.sizeX)* 4 ] = r;
                    m_dest[ (x + y * m_tgaHeader.sizeX) * 4 + 1 ]=g;
                    m_dest[ ( x + y * m_tgaHeader.sizeX ) * 4 + 2 ] = b;
                    m_dest[ ( x + y * m_tgaHeader.sizeX ) * 4 + 3 ] = a;
                }
            }
    }
    if( m_tgaHeader.datatypecode == TGA_TYPE_COLOR_RLE )
    {
        CInt x = 0;
        while( x < m_tgaHeader.sizeX * m_tgaHeader.sizeY )
        {
            l = fgetc(file);
            if( l & 0x80 )
            {
                l = l & 0x7F;
                b = fgetc(file);
                g = fgetc(file);
                r = fgetc(file);
                if( m_tgaHeader.bpp == 24 )
                   a = 255;
	            else
                   a = fgetc(file);


                for( CInt i = 0; i < l + 1; i++ )
                {
                    m_dest[ x * 4 ] = r;
                    m_dest[ x * 4 + 1 ] = g;
                    m_dest[ x * 4 + 2 ] = b;
                    m_dest[ x * 4 + 3 ] = a;
                    x++;
                }
            }
            else
            {
                l = l & 0x7F;
                for( CInt i = 0; i < l + 1; i++ )
                {
                    b = fgetc( file );
                    g = fgetc( file );
                    r = fgetc( file );
                    
                    if(m_tgaHeader.bpp == 24 )
                        a = 255;
                    else
                        a = fgetc( file );


                    m_dest[ x * 4 ] = r ;
                    m_dest[x * 4 + 1 ] = g;
                    m_dest[ x * 4 + 2 ] = b;
                    m_dest[ x * 4 + 3 ] = a;
                    x++;
                }
            }
        }
    }


    m_sizeX = m_tgaHeader.sizeX;
    m_sizeY = m_tgaHeader.sizeY;
    m_bpp = m_tgaHeader.bpp;
    if( m_bpp == 24 )
		m_bpp = 32;
    fclose( file );

    if( ( m_tgaHeader.imagedescriptor & 0x0020) == 0 )  //we flip the file
    {
        tmp = m_dest;

        if( m_tgaHeader.bpp == 8) 
            m_dest = (CUChar*)malloc( m_tgaHeader.sizeX * m_tgaHeader.sizeY );
        if( m_tgaHeader.bpp == 32 || m_tgaHeader.bpp == 24 )
            m_dest = ( CUChar* )malloc( m_tgaHeader.sizeX * m_tgaHeader.sizeY * 4 );


        for( CInt y = 0; y < m_tgaHeader.sizeY; y++ )
        {
            for( CInt x = 0; x< m_tgaHeader.sizeX; x++)
            {
                if( m_bpp == 8 )
                {
                    r = tmp[ x + ( m_tgaHeader.sizeY - y - 1 ) * m_tgaHeader.sizeX ];
                    m_dest[ x + y * m_tgaHeader.sizeX] = r;
                }
                if( m_bpp == 32 )
                {
                    r = tmp[ ( x + ( m_tgaHeader.sizeY - y - 1 ) * m_tgaHeader.sizeX) * 4 ];
                    g = tmp[ ( x + ( m_tgaHeader.sizeY - y - 1 ) * m_tgaHeader.sizeX) * 4 + 1 ];
                    b = tmp[ ( x + ( m_tgaHeader.sizeY - y - 1 ) * m_tgaHeader.sizeX) * 4 + 2 ];
                    a = tmp[ ( x + ( m_tgaHeader.sizeY - y -1 ) * m_tgaHeader.sizeX) * 4 + 3 ];
                    m_dest[ ( x + y * m_tgaHeader.sizeX) * 4 ] = r;
                    m_dest[ ( x + y * m_tgaHeader.sizeX) * 4 + 1] = g;
                    m_dest[ ( x + y * m_tgaHeader.sizeX) * 4 + 2 ]= b;
                    m_dest[ ( x + y * m_tgaHeader.sizeX) * 4 + 3 ]= a;


                }
            }
        }
        free(tmp);
    }
    return -1;
}


