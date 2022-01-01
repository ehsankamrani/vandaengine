//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include <math.h>
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

inline CVoid Append( CChar* dest, CChar* src)
{
	strcat( dest, src);
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