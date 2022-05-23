//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "Defines.h"
#include "../graphicsEngine/OpenGL.h"
#include <io.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp> 
#include <boost/serialization/string.hpp>
#include <iostream>
#include <sstream>


#define EPSILON 2.5e-8 
#define INFINITE_DISTANCE 1000000
#define ZERO EPSILON
#define Min(a,b)            (((a) < (b)) ? (a) : (b))
#define Max(a,b)            (((a) > (b)) ? (a) : (b))

//Windows Functions
//Delete all files in a directory
inline CVoid RemoveAllFilesInDirectory(CChar* directory)
{
	HANDLE hFind;
	WIN32_FIND_DATA data;
	CChar path[MAX_NAME_SIZE];
	sprintf( path, "%s%s", directory, "*.*" );
	hFind = FindFirstFile( path, &data );
	do
	{
		CChar filePath[MAX_NAME_SIZE];
		sprintf( filePath, "%s%s", directory, data.cFileName );
		//Remove Files
		if( !DeleteFile( filePath) )
		{
			//CChar temp[MAX_NAME_SIZE];
			//sprintf( temp, "\n%s%s", "Error: Couldn't remove the file ", data.cFileName );
			//PrintInfo( temp, COLOR_RED );
		}
	}while (FindNextFile( hFind, &data));

	FindClose(hFind);
}

inline BOOL IsDots(const TCHAR* str) {
	if (_tcscmp(str, ".") && _tcscmp(str, "..")) return FALSE;
	return TRUE;
}

inline BOOL RemoveAllFilesAndFoldersInDirectory(const TCHAR* sPath) {
	HANDLE hFind;  // file handle
	WIN32_FIND_DATA FindFileData;

	TCHAR DirPath[MAX_PATH];
	TCHAR FileName[MAX_PATH];

	_tcscpy(DirPath, sPath);
	_tcscat(DirPath, "\\*");    // searching all files
	_tcscpy(FileName, sPath);
	_tcscat(FileName, "\\");

	hFind = FindFirstFile(DirPath, &FindFileData); // find the first file
	if (hFind == INVALID_HANDLE_VALUE) return FALSE;
	_tcscpy(DirPath, FileName);

	bool bSearch = true;
	while (bSearch) { // until we finds an entry
		if (FindNextFile(hFind, &FindFileData)) {
			if (IsDots(FindFileData.cFileName)) continue;
			_tcscat(FileName, FindFileData.cFileName);
			if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {

				// we have found a directory, recurse
				if (!RemoveAllFilesAndFoldersInDirectory(FileName)) {
					FindClose(hFind);
					return FALSE; // directory couldn't be deleted
				}
				RemoveDirectory(FileName); // remove the empty directory
				_tcscpy(FileName, DirPath);
			}
			else {
				if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
					_chmod(FileName, _S_IWRITE); // change read-only file mode
				if (!DeleteFile(FileName)) {  // delete the file
					FindClose(hFind);
					return FALSE;
				}
				_tcscpy(FileName, DirPath);
			}
		}
		else {
			if (GetLastError() == ERROR_NO_MORE_FILES) // no more files there
				bSearch = false;
			else {
				// some error occured, close the handle and return FALSE
				FindClose(hFind);
				return FALSE;
			}

		}

	}
	FindClose(hFind);  // closing file handle

	return RemoveDirectory(sPath); // remove the empty directory
}

inline CBool CopyAllFilesAndFoldersToDstDirectory(CChar* r_szSrcPath, CChar* r_szDesPath, CBool failIfExist = TRUE)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	char l_szTmp[1025] = {0};
	memcpy(l_szTmp,r_szSrcPath,1024);

	char l_szSrcPath[1025] = {0};
	char l_szDesPath[1025] = {0};
	memcpy(l_szSrcPath,r_szSrcPath,1024);
	memcpy(l_szDesPath,r_szDesPath,1024);

	char l_szNewSrcPath[1025] = {0};
	char l_szNewDesPath[1025] = {0};

	strcat(l_szTmp,"*");

	hFind = FindFirstFile(l_szTmp, &FindFileData);
	if(hFind == NULL) return FALSE;

	do
	{
		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if(strcmp(FindFileData.cFileName,"."))
			{
				if(strcmp(FindFileData.cFileName,".."))
				{
					sprintf(l_szNewDesPath,"%s%s\\",l_szDesPath,FindFileData.cFileName);
					sprintf(l_szNewSrcPath,"%s%s\\",l_szSrcPath,FindFileData.cFileName);
					CreateDirectory(l_szNewDesPath,NULL);
					CopyAllFilesAndFoldersToDstDirectory(l_szNewSrcPath,l_szNewDesPath);
				}
			}
		}
		else
		{
			char l_szSrcFile[1025] = {0};
			char l_szDesFile[1025] = {0};
			sprintf(l_szDesFile,"%s%s",l_szDesPath,FindFileData.cFileName);
			sprintf(l_szSrcFile,"%s%s",l_szSrcPath,FindFileData.cFileName);
			BOOL l_bRet = CopyFile(l_szSrcFile, l_szDesFile, failIfExist);
		}
	}
	while(FindNextFile(hFind, &FindFileData));
	FindClose(hFind);
	return CTrue;
}

inline CVoid CreateWindowsDirectory(CChar* directory)
{
	if (!CreateDirectory(directory, NULL))
	{
		if (GetLastError() != 183)
		{
			CChar temp[MAX_NAME_SIZE];
			sprintf(temp, "\n%s%d%s%s", "Error (", GetLastError(), ") occured while creating the directory ", directory);
			PrintInfo(temp, COLOR_RED);
		}
	}
}

inline CVoid CopyAllFilesFromSrcToDstDirectory(CChar* srcDirectory, CChar* dstDirectory)
{
	CreateWindowsDirectory(srcDirectory);
	CreateWindowsDirectory(dstDirectory);

	HANDLE hFind;
	WIN32_FIND_DATA data;
	CChar path[MAX_NAME_SIZE];
	sprintf( path, "%s%s", srcDirectory, "*.*" );
	hFind = FindFirstFile( path, &data );
	if (hFind == NULL) return;

	do
	{
		CChar srcFilePath[MAX_NAME_SIZE];
		sprintf( srcFilePath, "%s%s", srcDirectory, data.cFileName );

		CChar dstFilePath[MAX_NAME_SIZE];
		sprintf( dstFilePath, "%s%s", dstDirectory, data.cFileName );

		if( !CopyFile( srcFilePath, dstFilePath, FALSE) )
		{
			//CChar temp[MAX_NAME_SIZE];
			//sprintf( temp, "\n%s%d%s%s%s%s", "Error (", GetLastError(), ") Couldn't copy the file ", srcFilePath, " to ", dstFilePath );
			//PrintInfo( temp, COLOR_RED );
		}
	}while (FindNextFile( hFind, &data));

	FindClose(hFind);
}

inline void StringToUpper(char* str)
{
    while (*str)
    {
        *str = toupper(*str);
        str++;
    }
}


inline CVoid Cpy( CChar * dest, const CChar * src )
{	
	strcpy( dest, src );	
}

inline CBool ICmp( const CChar * s1, const CChar * s2 )
{	
	if (!s1 || !s2)
		return false;

	if ( _stricmp( s1, s2 )  == 0 )
		return CTrue;
	return CFalse;
}

inline CBool Cmp( const CChar * s1, const CChar * s2 )
{	
	if (!s1 || !s2)
		return false;
	if ( strcmp( s1, s2 )  == 0 )
		return true;
	return false;
}

inline CBool Cmp2( CChar * s1, CChar * s2 )
{	
	if (!s1 || !s2)
		return false;

	if ( strcmp( s1, s2 )  == 0 )
		return true;
	return false;
}

inline	CVoid Cpy( CChar * dest, const CChar * src, const CChar endChar )
{
	CUInt len = (CUInt)strlen( src );
	CUInt i = 0; 

	while ( i < len )
	{
		// need to stop at a certain at a given character passed in. 
		if ( src[i] == endChar )
		{
			dest[i] = '\0';
			break; 
		}

		dest[i] = src[i]; 
		i++;		
	}
}

inline CBool CmpIn( const CChar * s1, const CChar * s2 )
{	
	if (!s1 || !s2)
		return CFalse;

	if ( strstr( s1, s2 ) != NULL )
		return CTrue;
	return CFalse;
}

inline	CChar * FindStr( const CChar * str, const CChar * c )
{
	return strstr((CChar *)str,(CChar *)c); 
}

inline CChar * GetAfterPath( CChar * name )
{
	CUInt len = (CUInt)strlen( name ); 
	CChar * tName = name + strlen( name ); 
	
	// from the end go backward to find the first forward or backslash
	while ( tName[0] != '/' && tName[0] != '\\' && len > 0 )
	{
		tName--;
		len--; 
	}	

	if ( len != 0 )
        tName ++;

	return tName; 
}

inline CVoid GetWithoutDot( CChar * name )
{
	CUInt len = (CUInt)strlen( name ); 
	CChar* tName = name + len -1;
	
	while ( tName[0] != '.' && len > 0 )
	{
		if( tName[0] == '\\' || tName[0] == '/')
			return;
		tName--;
		len--; 
	}	

	if ( len != 0 )
        tName[0] = 0;
}

inline CChar* GetFileExtension(CChar * name)
{
	CUInt len = (CUInt)strlen(name);
	CChar* tName = name + len - 1;

	while (tName[0] != '.' && len > 0)
	{
		if (tName[0] == '\\' || tName[0] == '/')
			return NULL;
		tName--;
		len--;
	}
	return tName;
}

inline CVoid Append( CChar* dest, CChar* src)
{
	strcat( dest, src);
}

inline CFloat Clampf( CFloat v, CFloat min = 0.0f, CFloat max = 1.0f )
{
	if	(v < min)
		return min;
	else if	(v > max)
		return max;
	else
		return v;
}

inline CInt	EatWhite( const CChar**	data )
{
	const CChar* c = *data;
	CInt32 w = 0;

	while( *c==' ' || *c=='\t' || *c=='\r' || *c=='\n' )
	{
		w++;
		c++;
	}
	*data	=	c;
	return (CInt)w; 
}

inline CInt	GetValueLenth( const CChar*	str )
{
	CInt32 len = 0;
	const CChar* c = str;

	while( c[0] != '\0' && c[0] != ' ' && c[0] != '\t'&& c[0] != '\r' && c[0] != '\n' && c[0] != '@' )
	{
		len++;
		c++;
	}
	return (CInt)len; 
}

inline const CChar*	GetValueString( const CChar** data )
{
	const CChar* d = *data;
	CInt32 w = EatWhite(&d);
	CInt32 len = GetValueLenth(d);
	*data += len + w;
	return (CChar *)d; 
}

inline CFloat GetFloatString( const CChar**	data )
{
	return (CFloat)atof(GetValueString(data));
}

inline CVoid CopyOneFileToDstDirectory(CChar* srcFilePath, CChar* dstDirectory)
{
	CreateWindowsDirectory(srcFilePath);
	CreateWindowsDirectory(dstDirectory);

	CChar* srcFilePathAfterPath = GetAfterPath( srcFilePath );

	CChar dstFilePath[MAX_NAME_SIZE];
	sprintf( dstFilePath, "%s%s", dstDirectory, srcFilePathAfterPath );

	if (Cmp(srcFilePath, dstFilePath))
		return;

	if( !CopyFile( srcFilePath, dstFilePath, FALSE) )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "\n%s%d%s%s%s%s", "Error (", GetLastError(), ") Couldn't copy the file ", srcFilePath, " to ", dstFilePath );
		PrintInfo( temp, COLOR_RED );
	}
}

inline CBool DirectoryExists(LPCTSTR szPath)
{
	DWORD dwAttrib = GetFileAttributes(szPath);

	return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
		(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

struct CColor3f
{
	CFloat r,g,b;

	CColor3f()
	{
		r = g = b = 1;
	}

	CColor3f( CFloat rr, CFloat gg, CFloat bb )
	{
		r = rr; g = gg; b = bb;
	}

	CVoid Clamp( CFloat min = 0.0f, CFloat max = 1.0f )
	{
		r	=	Clampf( r, min, max ); 
		g	=	Clampf( g, min, max ); 
		b	=	Clampf( b, min, max ); 
	}
};

struct    CColor4f
{
	CFloat r,g,b,a;

	CColor4f()
	{
		r = g = b = a = 1;
	}

	CColor4f( CFloat rr, CFloat gg, CFloat bb, CFloat aa )
	{
		r = rr; g = gg; b = bb; a = aa;
	}

	CColor4f( CColor3f * c )
	{
		r = c->r; g = c->g; b = c->b; a = 1.0f; 
	}

	CColor4f( CColor3f c )
	{
		r = c.r; g = c.g; b = c.b; a = 1.0f; 
	}

	CVoid Clamp( CFloat min = 0.0f, CFloat max = 1.0f )
	{
		r =	Clampf( r, min, max ); 
		g =	Clampf( g, min, max ); 
		b =	Clampf( b, min, max ); 
		a =	Clampf( a, min, max ); 
	}
};

struct CQuat
{
	CFloat x,y,z,w; 
	
	CQuat()
	{
		x = y = z = 0; w = 1.0f; 
	}

	CQuat( CFloat X, CFloat Y, CFloat Z, CFloat W )
	{
		x = X, y = Y, z = Z, w = W; 
	}  

	//Update orient 2 q1 * q2 
	inline CQuat& operator *= ( const CQuat& q2 )
	{
	   CFloat A, B, C, D, E, F, G, H;
	   A = (w + x) * (q2.w + q2.x);
	   B = (z - y) * (q2.y - q2.z);
	   C = (w - x) * (q2.y + q2.z);
	   D = (y + z) * (q2.w - q2.x);
	   E = (x + z) * (q2.x + q2.y);
	   F = (x - z) * (q2.x - q2.y);
	   G = (w + y) * (q2.w - q2.z);
	   H = (w - y) * (q2.w + q2.z);

	   x =  A - (  E + F + G + H ) * .5f;
	   y =  C + (  E - F + G - H ) * .5f;
	   z =  D + (  E - F - G + H ) * .5f;
	   w =  B + ( -E - F + G + H ) * .5f;
	   return *this;
	}

	inline CFloat Length()
	{
		return (CFloat)sqrt( x*x + y*y + z*z + w*w);
	}
	inline CVoid Normalize()
	{
		CFloat Len = Length();

		if ( Len > 1e-06f )
		{
			CFloat ILen = (1.0f)/Len;
			x *= ILen;
			y *= ILen;
			z *= ILen;
			w *= ILen;
		}
		else
		{
			x = 0;
			y = 0;
			z = 0;
			w = 0;
		}    
	}
};

struct CVec2f
{
	CFloat x,y; 

	CVec2f()
	{
		x = y = 0; 
	}

	CVec2f( CFloat xx, CFloat yy )
	{
		x = xx; y = yy; 
	}

	inline CBool operator ==( CVec2f v)
	{
		if ( x != v.x )
			return CFalse; 
		if ( y != v.y )
			return CFalse; 
		return CTrue; 
	}

	inline CBool operator !=( CVec2f v )
	{
		if ( x != v.x )
			return CTrue; 
		if ( y != v.y )
			return CTrue; 
		return CFalse; 
	}
};

struct CVec3f
{
	CFloat x,y,z; 

	CVec3f()
	{
		x = y = z = 0; 
	}

	CVec3f( CFloat xx, CFloat yy, CFloat zz )
	{
		x = xx; y = yy; z = zz; 
	}

	inline CVec3f operator +(const CVec3f& v) const 
		{ 	return (CVec3f(x + v.x, y + v.y, z + v.z)); }
	inline CVec3f operator +(const CVec2f& v) const
		{	return (CVec3f(x + v.x, y + v.y, z)); }
	inline CVec3f operator -(const CVec3f& v) const
		{	return (CVec3f(x - v.x, y - v.y, z - v.z)); }
	inline CVec3f operator -(const CVec2f& v) const
		{	return (CVec3f(x - v.x, y - v.y, z)); }
	inline CVec3f operator *(CFloat t) const
		{	return (CVec3f(x * t, y * t, z * t));}
	inline CVec3f & operator +=(const CVec3f& v)
		{	x += v.x; y += v.y;	z += v.z;	return (*this); }
	inline CVec3f & operator =(const CVec3f& v)
	{	x = v.x; y = v.y;	z = v.z;	return (*this); }

	inline CFloat operator *(const CVec3f& v) const
		{	return (x * v.x + y * v.y + z * v.z); }
	inline CVec3f& operator /=( CFloat t)
	{
		CFloat v = 1.0F / t;
		x *= v; y *= v;  z *= v;
		return (*this);
	}

	inline CVec3f& Normalize(CVoid) 
		{ 	return (*this /= sqrtf(x * x + y * y + z * z)); 	}

	inline CFloat Size(CVoid) 
		{ 	return ( sqrtf(x * x + y * y + z * z)); 	}

	inline CBool operator ==( CVec3f v)
	{
		if ( x != v.x )
			return CFalse;
		if ( y != v.y )
			return CFalse;
		if ( z != v.z )
			return CFalse;
		return CTrue;
	}

	inline CBool operator !=( CVec3f v )
	{
		if ( x != v.x )
			return CTrue;
		if ( y != v.y )
			return CTrue; 
		if ( z != v.z )
			return CTrue; 
		return CFalse; 
	}

	inline CFloat DotProduct( const CVec3f * v1, const CVec3f * v2 )
	{
		return ( v1->x * v2->x + v1->y * v2->y + v1->z * v2->z ); 
	}

	inline CVec3f CrossProduct( const CVec3f * v1, const CVec3f * v2 )
	{
		CVec3f v3;  
			
		v3.x = v1->y*v2->z - v1->z*v2->y;
		v3.y = v1->z*v2->x - v1->x*v2->z;
		v3.z = v1->x*v2->y - v1->y*v2->x;
		
		return v3; 
	}

private:
	friend class boost::serialization::access;

	template <typename Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & x;
		ar & y;
		ar & z;
	}

};

struct CQuat; 
struct CVec4f
{
	CFloat x,y,z,w; 

	CVec4f ( CVec3f v, CFloat ww )
	{
		x = v.x; y = v.y; z = v.z; w = ww;
	}

	CVec4f()
	{
		x = y = z = w = 0; 
	}

	CVec4f( CFloat xx, CFloat yy, CFloat zz, CFloat ww )
	{
		x = xx; y = yy; z = zz; w = ww;
	}

	inline CVec4f operator +(const CVec4f& v) const 
		{ 	return CVec4f( CVec3f(x + v.x, y + v.y, z + v.z), w + v.w); }
	inline CVec4f operator -(const CVec4f& v) const
		{	return CVec4f( CVec3f(x - v.x, y - v.y, z - v.z), w - v.w); }
	inline CVec4f operator *(CFloat t) const
		{	return CVec4f( CVec3f(x * t, y * t, z * t), w*t);}
	inline CVec4f& operator /=( CFloat t)
	{
		CFloat v = 1.0F / t;
		x *= v; y *= v;  z *= v; w *= v;
		return (*this);
	}

	inline CVec4f& Normalize(CVoid) 
		{ 	return (*this /= sqrtf(x * x + y * y + z * z ) ); 	}

	inline CVoid Set( CInt i, CFloat f )
	{
		switch( i )
		{
		case 0: x = f; 	break;
		case 1: y = f;  break; 
		case 2:	z = f; 	break; 
		case 3:	w = f; 	break; 
		};
	}

	inline CFloat Get( CInt i )
	{
		switch( i )
		{
		case 0:	return x; 			
		case 1: return y; 
		case 2: return z; 			
		case 3: return w; 			
		};
		return 0; 
	}

	CVoid Set( CQuat *); 

private:
	friend class boost::serialization::access;

	template <typename Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & x;
		ar & y;
		ar & z;
		ar & w;

	}
};

inline CVec4f Lerp(CVec4f start, CVec4f end, float percent)
{
	if( percent < 0.0f )
		percent = 0.0f;
	else if( percent > 1.0f )
		percent = 1.0f;
    return( start + (end - start)* percent);
}

inline CFloat Lerp(CFloat start, CFloat end, float percent)
{
	if (percent < 0.0f)
		percent = 0.0f;
	else if (percent > 1.0f)
		percent = 1.0f;
	return(start + (end - start)* percent);
}

inline CVec4f Nlerp(CVec4f start, CVec4f end, float percent)
{
	if( percent < 0.0f )
		percent = 0.0f;
	else if( percent > 1.0f )
		percent = 1.0f;
	return(start + (end - start)* percent).Normalize();
}

class CPlane
{
public:

	CVec3f Normal;
	CVec3f Position;
	DWORD axesAlignment;
	
	CPlane(void)
	{
		Normal = CVec3f( 0.0f, 0.0f, 0.0f );
		Position = CVec3f( 0.0f, 0.0f, 0.0f );		
	}

	CPlane(CVec3f &norm,CVec3f &pos, DWORD axes)
	{
		Normal = CVec3f(norm.x,norm.y,norm.z);
		Position = CVec3f(pos.x,pos.y,pos.z);
		axesAlignment = axes;
	}

	void DrawNormal()
	{
		glUseProgram(0);
		glMatrixMode( GL_MODELVIEW );
		glPushAttrib( GL_ENABLE_BIT | GL_CURRENT_BIT | GL_LINE_BIT );
		glDisable(GL_LIGHTING);
		glDisable( GL_TEXTURE_2D );
		glColor3f(1.0f,0.0f,0.0f);
		glBegin(GL_LINES);
		glVertex3f(Position.x,Position.z,Position.y);
		glVertex3f(Normal.x*2+Position.x,Normal.z*2+Position.z,Normal.y*2+Position.y);
		glEnd();
		glPopAttrib();
	}

	void Draw()
	{
		glDisable(GL_DEPTH_TEST);

		glUseProgram(0);
		glMatrixMode( GL_MODELVIEW );
		glPushAttrib( GL_ENABLE_BIT | GL_CURRENT_BIT | GL_LINE_BIT );
		glDisable(GL_LIGHTING);
		glDisable( GL_TEXTURE_2D );
		glDisable( GL_CULL_FACE );
		glLineWidth(1.0);
		float size = 1.0f;
		// xy plane default
		float x = Position.x;
		float y = Position.z;
		float z = Position.y;
		CVec3f color;
		glPushMatrix();
			if(axesAlignment == XYTRANS)
			{
				x = Position.x;
				y = Position.z;
				z = Position.y;	
				color.y = 0.7f; color.x = color.z = 0.1f;
			}
			else if(axesAlignment == ZXTRANS)
			{
				glRotatef(90.0f,1.0f,0.0f,0.0f);
				x = Position.x;
				y = Position.y;
				z = -Position.z;	
				color.z = 0.8f; color.y = color.x = 0.1f;

			}
			else if(axesAlignment == YZTRANS)
			{
				glRotatef(-90.0f,0.0f,0.0f,1.0f);
				x = -Position.z;
				y = Position.x;
				z = Position.y;
				color.x = 0.7; color.y = color.z = 0.1f;

			}
			
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColor4f(color.x,color.y,color.z,0.2f);
			glBegin(GL_QUADS);				
				glVertex3f(x-size,y,z-size);
				glVertex3f(x-size,y,z+size);				
				glVertex3f(x+size,y,z+size);
				glVertex3f(x+size,y,z-size);				
			glEnd();
			glDisable(GL_BLEND);
			
			glColor3f(1.0f,1.0f,0.0f);
			glBegin(GL_LINES);				
				glVertex3f(x-size,y,z-size);
				glVertex3f(x-size,y,z+size);
				glVertex3f(x+size,y,z-size);
				glVertex3f(x+size,y,z+size);
				glVertex3f(x-size,y,z-size);
				glVertex3f(x+size,y,z-size);
				glVertex3f(x-size,y,z+size);
				glVertex3f(x+size,y,z+size);				
			glEnd();
		
		glPopMatrix();

		glPopAttrib();	

		glEnable(GL_DEPTH_TEST);

	}
};

//===========================================================================================
//	CRay defined by 2 points (can we call it a segment?)
//
//	The 2 points p0 and p1 are expressed in non-opengl cartesian co-ordinates.
//	where the Z axis in vertical. In opengl the screen and the Y axis is vertical.
//===========================================================================================

class CRay
{

public:
	CVec3f p0;
	CVec3f p1;

	CRay(void)
	{
		p0 = CVec3f( 0.0f, 0.0f, 0.0f );
		p1 = CVec3f( 0.0f, 0.0f, 0.0f );
	}

	CRay(CVec3f P0,CVec3f P1)
	{
		p0 = CVec3f( 0.0f, 0.0f, 0.0f );
		p1 = CVec3f( 0.0f, 0.0f, 0.0f );

		p0.x = P0.x;
		p0.y = P0.y;
		p0.z = P0.z;
		p1.x = P1.x;
		p1.y = P1.y;
		p1.z = P1.z;
		
	}

	CRay(int x2D, int y2D)
	{
		p0 = CVec3f( 0.0f, 0.0f, 0.0f );
		p1 = CVec3f( 0.0f, 0.0f, 0.0f );
		Generate3DRay(x2D, y2D);		
	}

	void Generate3DRay(int x2D, int y2D)
	{
		p0 = CVec3f( 0.0f, 0.0f, 0.0f );
		p1 = CVec3f( 0.0f, 0.0f, 0.0f );
	
		int x =x2D;
		int y =y2D;	
		GLint viewport[4];	
		GLdouble modelview[16];
		GLdouble projection[16];
		GLdouble winX, winY; 
		GLdouble winZ0 = 0.0f; GLdouble winZ1 = 1.0f;
		GLdouble posX0, posY0, posZ0;
		GLdouble posX1, posY1, posZ1;

		glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
		glGetDoublev(GL_PROJECTION_MATRIX, projection);

		glGetIntegerv(GL_VIEWPORT, viewport);		

		winX = (GLdouble)x;
		winY = (GLdouble)viewport[3] - (GLdouble)y;

		glReadBuffer( GL_BACK );

		gluUnProject( winX, winY, winZ0, modelview, projection, viewport, &posX0, &posY0, &posZ0);
		gluUnProject( winX, winY, winZ1, modelview, projection, viewport, &posX1, &posY1, &posZ1);
		// flip opengl co-ordinates to flight simulator co-ordinates
		p0.x = (float)posX0;
		p0.y = (float)posZ0;
		p0.z = (float)posY0;
		//
		p1.x = (float)posX1;
		p1.y = (float)posZ1;
		p1.z = (float)posY1;

	}

	int Intersects(CPlane p, CVec3f& I)
	{
		CVec3f intersectPoint;

		CVec3f u = p1 - p0;
		CVec3f w = p0 - p.Position;
		
		CVec3f tempVec;
		float D = tempVec.DotProduct( &p.Normal, &u );
		CVec3f normalTempVec = CVec3f( -p.Normal.x, -p.Normal.y, -p.Normal.z );
		float N = tempVec.DotProduct( &normalTempVec, &w);

		if (fabs(D) < ZERO)			// segment is parallel to plane
		{          
			if (N == 0)                     // segment lies in plane
				return 2;
			else
				return 0;                   // no intersection
		}

		float s = N / D;
		if (s < 0 || s > 1)
			return 0;                       // no intersection

		intersectPoint = p0 + u*s;         // compute segment intersect point

		I.x  = intersectPoint.x;
		I.y  = intersectPoint.y;
		I.z  = intersectPoint.z;
		
		return 1;
	}

};
