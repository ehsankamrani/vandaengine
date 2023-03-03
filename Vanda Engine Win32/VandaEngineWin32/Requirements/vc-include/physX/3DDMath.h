/*----------------------------------------------------------------------------*\
|
|						    NVIDIA PhysX Technology
|
|							     www.nvidia.com
|
\*----------------------------------------------------------------------------*/


#ifndef __3DDMATH_H__
#define __3DDMATH_H__
/*-------------------------------*\
| Vector, Matrix, and Quaternion classes
|
| Vec3d, Quatd based on code by Robert Stephen Rodgers
| uses 'double' as base type
\*-------------------------------*/
/*-Revision----------------------\
| At: 11/10/99 4:52:08 PM
| Added Mat33d::Orthogonalize() 
| uses GramSchmidt algorithm, based 
| on Maple code `Copyright (c) 1997 by Erich Kaltofen`
|
| In retrospect: I think it doesn't work.
\-------------------------------*/
/*-Revision----------------------\
| At: 11/15/99 8:55:00 PM
| Changed Orthogonalize to 
| Orthonormalize.
\-------------------------------*/
/*-Revision----------------------\
| At: 11/15/99 8:59:32 PM
| Changed all methods which took 
| pointer params to take reference
| params.  Oh dear.
\-------------------------------*/
/*-Revision----------------------\
| At: 4/2/00 5:35:15 PM
| Added assignment to/from
| float array.
|
\-------------------------------*/

#include <math.h>
#include <Smart.h>
#include <stdlib.h>

#define M3D_EPSILON		0.0005f

inline double frandd()//between 0 and 1
	{
	return (double)rand()/((double)RAND_MAX+1);
	}

class Vec3d
	{
	bool epsilonEquals(const double left, const double right, const double epsilon) const;
	public: 
		double x,y,z;

	Vec3d() {}
	Vec3d(const double x, const double y, const double z);
	Vec3d(const Vec3d& v);

	double  GetElem(int i);						//get/set element at index i=0..2
	void SetElem(int i, double elem);
	void Get(double &);

	Vec3d& operator=(const Vec3d& v);
	Vec3d& operator=(const double & v);
	bool operator==(const Vec3d& v) const;

	Vec3d operator*(const double f) const;			// scalar multiple of this vector
	Vec3d& operator*=(const double f);				
	Vec3d operator+(const Vec3d& v) const;		// sum of the two vectors
	Vec3d& operator+=(const Vec3d& v);
	Vec3d operator-(const Vec3d& v) const;		// signed difference of the two vectors
	Vec3d& operator-=(const Vec3d& v);
	void Add(const Vec3d * v);						//this += v;
	bool isZero() const;
	void Zero();
	void Set(const double x, const double y, const double z);
	
	Vec3d Cross(const Vec3d& v) const;	// returns = this Cross v
	void Cross(const Vec3d& left, const Vec3d& right); // this = left Cross right
	double Dot(const Vec3d& v) const;		// Dot = this . v
	double Magnitude() const;				// Magnitude of this vector
	double MagnitudeSq() const;				// Magnitude squared of this vector
	double Angle(const Vec3d& v) const;		// Angle between this & v
	void Normalize();					// makes this vector a unit vector
	};

class Mat33d;

class Quatd
	{
	double deg_to_rad(const double src) const;  // convert degrees to radians
	double rad_to_deg(const double src) const;  // convert radians to degrees
	double dot4(const double v1[4], const double v2[4]) const; // 4-vector Dot product
	bool epsilonEquals(const double leflo, const double right, const double epsilon) const;

public:

	double w,x,y,z;

	// various ways of creating a new clQuaternionernion
	////////////////////////////////////////////////
	Quatd() {}										// default constructor -- contents UNDEFINED
	Quatd(const Quatd& s);					// copy constructor
	Quatd(const Vec3d& v);						// copy constructor, assumes w=0 
	Quatd(const double Angle, Vec3d & axis)				// creates a Quatd from an Angle axis -- note that if Angle > 360 the resulting rotation is Angle mod 360
		{
		fromAngleAxis(Angle, axis);
		}
	// Quatd functions
	////////////////////////////////////////////////
	void Set(const double w,const  double x,const  double y,const  double z);
	void Zero();
	void fromAngleAxis(const double Angle, Vec3d & axis);			// set the Quatd by Angle-axis (see AA constructor)
	void fromMatrix(Mat33d &m);					// set the Quatd from a rotation matrix
	void Normalize();											// convert this Quatd to a unit clQuaternionernion
	void fromclQuaternion(const Quatd& q);				// set the Quatd to another Quatd
	void fromclQuaterniondata(const double clQuaternion_wxyz[4]);	// directly set the Quatd data -- a normalization is performed
	void getAngleAxis(double& Angle, double axis[3]) const;			// fetches the Angle/axis given by the Quatd
	void multiply(const Quatd& q);						// this = this * q		
	void multiply(const Quatd& leflo, const Quatd& right);		// this = leflo * right
	void slerp(const double t, const Quatd& leflo, const Quatd& right); // this = slerp(t, leflo, right)
	bool sameAs(const Quatd& q) const;
	void Rotate(Vec3d & cloVector);						//rotates passed vec by rot expressed by quaternion.  overwrites arg ith the result.
	void InverseRotate(Vec3d & cloVector);				//rotates passed vec by opposite of rot expressed by quaternion.  overwrites arg ith the result.
	double Magnitude();											//this is actually magnitude squared.

	// semantic sugar -- these wrap the above functions
	///////////////////////////////////////////////////
	Quatd& operator*= (const Quatd& r_h_s);
	Quatd& operator+= (const Quatd& r_h_s);
	Quatd& operator-= (const Quatd& r_h_s);
	Quatd  operator+  (const Quatd& r_h_s) const;
	Quatd  operator-  (const Quatd& r_h_s) const;

	Quatd& operator*= (const double Scale);
	Quatd  operator*  (const Quatd& r_h_s) const;
	Vec3d    operator^  (const Quatd& r_h_s) const;//same as normal quat rot, but casts itself into a vector.  (doesn't compute w term)
	Quatd  operator*  (const Vec3d& v) const;//implicitly extends vector by a 0 w element.
	Quatd  operator*  (const double Scale) const;
	bool  operator== (const Quatd& r_h_s) const;
	Quatd& operator=  (const Quatd& r_h_s);
	Quatd& operator=  (const Vec3d& v);		//implicitly extends vector by a 0 w element.
	void Random()
		{
		x = 2.0f*frandd() - 1;
		y = 2.0f*frandd() - 1;
		z = 2.0f*frandd() - 1;
		w = 2.0f*frandd() - 1;
		Normalize();
		}
	};


class Mat44d
	{
	public:
	union
		{
		double M44[4][4];						//column major order [x-column][y-row]
		double M16[16];						//[x = 2][y = 1] == [9]
		};
											/*
											 0 4 8 12
											 1 5 9 13 
											 2 6 0 14
											 3 7 1 15
											*/

	Mat44d();							//init to identity
	Mat44d(Quatd & Quatd);			//create from quat
	void ID();								//init to identity

	void FromQuat(Quatd & Quatd);		//sets itself to rotmatrix based on quat passed
	void Set(Mat44d & clopMatrix);		//This = Matrix


	void SetTranslation(Vec3d & clpVector);	//sets 3 elems responsible for translation
	void SetTranslationNegative(Vec3d & cloVector);	//same as above, but sets vars to -clopVector.
	void Copy3x3(Mat44d & cloMatrix);			//copies the 3x3 part of the passed matrix to the 3x3 part of this matrix. (sets a rotation)
	void Copy3x3Transposed(Mat44d & cloMatrix);//same as above, but transposes 3x3 part as it copies.  (sets the inverse of a rotation)

	void TranslateNegative(Vec3d & cloVector);//this = this * TranslationMx(-clopVector);
													//assumes all but 3x3 part is 0, except lower right corner = 1
	void Rotate(Vec3d & cloVector);		//implicitly extends vector to 1x4 mx, and overwrites it with the result. Assumes that no translation happens

	/* not yet implemented:
	void Scale(Vec3d * clopVector);	//same as multiplying with corresp scaling matrix.  overwrites itself with the result
	void Mult(Mat44d * clopMatrix);	//This = This * Matrix
	void Add(Mat44d * clopMatrix);		//overwrites itself with the result
	void Subtract(Mat44d * clopMatrix);//overwrites itself with the result
	Mat44d * Copy(void);				//creates a copy obj, returns ptr to it, caller gets to own it.
	*/										//other possibilities:  Norm, Determinant, Invert.
											//make special cases for mult which assume 0001 for last row.
	Mat44d  operator*  (const Mat44d& r_h_s) const;	//assumes 4th rows are identity.
	Vec3d   operator*  (const Vec3d & r_h_s) const;	//assumes 4th rows are identity.
	};


class Mat33d
	{
	public:
	union
		{
		double M33[3][3];						//column major order [x-column][y-row]
		double M9[9];							//[x = 2][y = 1] == [7]
		};

	Mat33d();							//init to identity
	void ID();								//init to identity
	void FromQuat(Quatd & Quatd);		//sets itself to rotmatrix based on quat passed
	void Orthonormalize();					//Gram-Schmidt orthogonalization to correct numerical drift, plus column normalization
	void GetColumn(int i,Vec3d & col) const;		//get/set column vector at i = 0..2
	void SetColumn(int i,Vec3d & col);

	Mat33d& operator=  (const Mat33d& r_h_s);
	Mat33d  operator+  (const Mat33d& r_h_s) const;
	Mat33d  operator*  (const Mat33d& r_h_s) const;
	Vec3d   operator*  (const Vec3d & r_h_s) const;
	Mat33d  operator*  (      double  r_h_s) const;
	Mat33d  operator%  (const Mat33d& r_h_s) const;	// multiplies by transpose of r_h_s
	Vec3d   operator%  (const Vec3d & r_h_s) const;	// multiplies by transpose of this
	void vecTransMult(const Vec3d & r_h_s, Vec3d & result) const;	// performs dest = rhs^t * this
	};

inline Vec3d ::Vec3d(const double x, const double y, const double z)
{
Set(x,y,z);
}

inline void Vec3d ::Set(const double x, const double y, const double z)
	{
	this->x = x;
	this->y = y;
	this->z = z; 
	}

inline void Vec3d::Get(double &f)
	{
	f = x;
	(&f)[1] = y;
	(&f)[2] = z;
	}

inline double  Vec3d::GetElem(int i)
	{
	switch(i) 
		{
		case 0:
			return x;
		case 1:
			return y;
		default:
			return z;
		};
	}
inline void Vec3d::SetElem(int i, double elem)
	{
	switch(i) 
		{
		case 0:
			x=elem; break;
		case 1:
			y=elem; break;
		default:
			z=elem;
		};
	}

  
inline Vec3d ::Vec3d(const Vec3d& v)
{
	x = v.x;
	y = v.y;
	z = v.z; 
}


  
inline Vec3d & Vec3d ::operator=(const Vec3d& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

inline Vec3d& Vec3d::operator=(const double & v)
	{
	x = v;
	y = (&v)[1];
	z = (&v)[2];
	return *this;
	}

  
inline bool Vec3d ::operator==(const Vec3d& v) const
{
	return 
			epsilonEquals(x, v.x, (double) M3D_EPSILON) &&
			epsilonEquals(y, v.y, (double) M3D_EPSILON) &&
			epsilonEquals(z, v.z, (double) M3D_EPSILON);
}


  
inline bool Vec3d ::epsilonEquals(const double left, const double right, const double epsilon) const
{
	const double diff = (double)fabs(left - right);
	if(diff < epsilon) return true;
	return false;
}



  
inline Vec3d  Vec3d ::operator*(const double f) const 
{ 
	Vec3d t(x * f, y * f, z * f); 
	return t; 
}




  
inline Vec3d & Vec3d ::operator*=(const double f)
{
	x *= f; y *= f;  z *= f; 
	return *this;
}




  
inline Vec3d  Vec3d ::operator+(const Vec3d& v) const 
{ 
	Vec3d t(x + v.x,
			y + v.y,
			z + v.z);  
	return t;
}



  
inline void  Vec3d ::Add(const Vec3d * v) 
{ 
	x += v->x; 
	y += v->y; 
	z += v->z; 
}



  
inline Vec3d  Vec3d ::operator-(const Vec3d& v) const 
{ 
	Vec3d t(x - v.x,y - v.y,z - v.z);  
	return t;
}



  
inline Vec3d &  Vec3d ::operator-=(const Vec3d& v) 
	{ 
	x -= v.x; 
	y -= v.y; 
	z -= v.z; 
	return *this; 
	}

inline Vec3d  & Vec3d ::operator+=(const Vec3d& v) 
	{ 
	x += v.x; 
	y += v.y; 
	z += v.z; 
	return *this; 
	}



inline bool Vec3d ::isZero() const
	{
	return 
		epsilonEquals(x, 0, (double) M3D_EPSILON) &&
		epsilonEquals(y, 0, (double) M3D_EPSILON) &&
		epsilonEquals(z, 0, (double) M3D_EPSILON);
	}

inline void Vec3d ::Zero()
	{
	x = y = z = 0.0f;
	}




inline Vec3d  Vec3d ::Cross(const Vec3d& v) const
	{
	Vec3d t(
		(y * v.z) - (z * v.y),
		(z * v.x) - (x * v.z),
		(x * v.y) - (y * v.x)
		);
	return t;
	}




inline void Vec3d ::Cross(const Vec3d& left, const Vec3d& right)
	{
	assert(&left != this && &right != this);//can't do this in place!
	x = (left.y * right.z) - (left.z * right.y);
	y = (left.z * right.x) - (left.x * right.z);
	z = (left.x * right.y) - (left.y * right.x);
	}




inline double Vec3d ::Dot(const Vec3d& v) const
	{
	return x*v.x + y*v.y + z*v.z; 
	}





inline double Vec3d ::Magnitude() const
	{
	return (double)sqrt(Dot(*this));
	}

inline double Vec3d ::MagnitudeSq() const
	{
	return Dot(*this);
	}



inline double Vec3d ::Angle(const Vec3d& v) const
	{
	const double divis = Magnitude() * v.Magnitude();
	return (double)acos( Dot(v) / divis); 
	}



  
inline void Vec3d ::Normalize()
{
	double m = Magnitude(); 
	if (m)
		{
		const double il = (double) 1.0 / m;
		x *= il;
		y *= il;
		z *= il;
		}
}

inline void Quatd ::Set(const double w, const double x, const double y, const double z)
	{
	this->w = w;
	this->x = x;
	this->y = y;
	this->z = z; 
	}

inline Quatd::Quatd(const Quatd& s)
{
	w = s.w;
	x = s.x;
	y = s.y;
	z = s.z;
}

inline Quatd::Quatd(const Vec3d& v)
{
	w = 0.0f;
	x = v.x;
	y = v.y;
	z = v.z;
}

inline void Quatd::Zero()
	{
	w = 1.0f;
	x = y = z = 0.0f;
	}

inline void Quatd::fromclQuaterniondata(const double q[4])
{
	w = q[0];
	x = q[1];
	y = q[2];
	z = q[3];
	Normalize();
}




inline void Quatd::fromclQuaternion(const Quatd& q)
{
	w = q.w;
	x = q.x;
	y = q.y;
	z = q.z;
}




inline double Quatd::deg_to_rad(const double src) const 
{
	return (double)0.01745329251994329547 * src;
}




inline double Quatd::rad_to_deg(const double src) const
{
	return (double)57.29577951308232286465 * src;
}



inline void Quatd::Normalize()
	{
	// a clQuaternionernion can be converted to a unit clQuaternionernion by 
	// dividing each sub element by the Quatd's Magnitude 
	// (unit clQuaternions satisfy w^2 + x^2 + y^2 + z^2 = 1) 

/*	const double wsqd = w * w;
	const double xsqd = x * x;
	const double ysqd = y * y;
	const double zsqd = z * z;

   wsqd + xsqd + ysqd + zsqd 
*/	const double mag = (double) sqrt(Magnitude());
	if (mag)
		{
		const double i_magnitude = (double) 1.0 / mag;
		
		w = w * i_magnitude;
		x = x * i_magnitude;
		y = y * i_magnitude;
		z = z * i_magnitude;
		}
	}




inline void Quatd::multiply(const Quatd& q)
	{
	double T[4]; //working clQuaternionernion
	T[0] =w*q.w - q.x*x - y*q.y - q.z*z;
	T[1] =w*q.x + q.w*x + y*q.z - q.y*z;
	T[2] =w*q.y + q.w*y + z*q.x - q.z*x;
	z =w*q.z + q.w*z + x*q.y - q.x*y;

	w = T[0];
	x = T[1];
	y = T[2];
	}

inline double Quatd::Magnitude()
	{
	return x*x + y*y + z*z + w*w;
	}


inline void Quatd::multiply(const Quatd& leflo, const Quatd& right)
	{
	w =leflo.w*right.w - leflo.x*right.x - leflo.y*right.y - leflo.z*right.z;
	x =leflo.w*right.x + right.w*leflo.x + leflo.y*right.z - right.y*leflo.z;
	y =leflo.w*right.y + right.w*leflo.y + leflo.z*right.x - right.z*leflo.x;
	z =leflo.w*right.z + right.w*leflo.z + leflo.x*right.y - right.x*leflo.y;
	}

inline void Quatd::Rotate(Vec3d & cloVector)	//rotates passed vec by rot expressed by quaternion.  overwrites arg ith the result.
	{
	double msq = 1.0f/Magnitude();
	Quatd MyInverse;
	MyInverse.w = w*msq;
	MyInverse.x = -x*msq;
	MyInverse.y = -y*msq;
	MyInverse.z = -z*msq;

	cloVector = (*this * cloVector) ^ MyInverse;
	
	}

inline void Quatd::InverseRotate(Vec3d & cloVector)	
	//rotates passed vec by rot opposite to that expressed by quaternion.  overwrites arg ith the result.
	{
	double msq = 1.0f/Magnitude();
	Quatd MyInverse;
	MyInverse.w = w*msq;
	MyInverse.x = -x*msq;
	MyInverse.y = -y*msq;
	MyInverse.z = -z*msq;

	cloVector = (MyInverse * cloVector) ^ (*this);
	}


inline Quatd Quatd::operator*(const Vec3d & Vec) const
	{
	Quatd a;
	a.w =this->w*0.0f - this->x*Vec.x - this->y*Vec.y - this->z*Vec.z;
	a.x =this->w*Vec.x + 0.0f*this->x + this->y*Vec.z - Vec.y*this->z;
	a.y =this->w*Vec.y + 0.0f*this->y + this->z*Vec.x - Vec.z*this->x;
	a.z =this->w*Vec.z + 0.0f*this->z + this->x*Vec.y - Vec.x*this->y;
	return a;
	}

inline void Quatd::getAngleAxis(double& Angle, double axis[3]) const
{
/*	Angle = (double) acos((double)w) * 2.0f;
	const double i_sin_over = 1.0f / (double)sin((double)Angle/2.0f);
	axis[0] = x * i_sin_over;
	axis[1] = y * i_sin_over;
	axis[2] = z * i_sin_over;
	Angle = (double) rad_to_deg(Angle);
*/



	//return axis and angle of rotation of quaternion
    Angle = (double)acos(w) * 2.0f;
    double sa = (double)sqrt(1.0f - w*w);
	if (sa)
		{
		axis[0]=x/sa; axis[1]=y/sa; axis[2]=z/sa;
		Angle = (double) rad_to_deg(Angle);
		}
	else
		axis[0]=axis[1]=axis[2]=0.0f;
	}




inline void Quatd::fromAngleAxis(const double Angle, Vec3d & axis)
{
	x = axis.x;
	y = axis.y;
	z = axis.z;

	// required: Normalize the axis

	const double i_length = (double) 1.0f / (double) sqrt( x*x + y*y + z*z );
	
	x = x * i_length;
	y = y * i_length;
	z = z * i_length;

	// now make a clQuaternionernion out of it
	double Half = deg_to_rad((double)Angle / 2.0f);

	w = (double) cos(Half);//this used to be w/o deg to rad.
	const double sin_theta_over_two = (double) sin( Half );
	x = x * sin_theta_over_two;
	y = y * sin_theta_over_two;
	z = z * sin_theta_over_two;
}

inline void Quatd::fromMatrix(Mat33d &m)
    {
    double tr, s;
    tr = m.M33[0][0] + m.M33[1][1] + m.M33[2][2];
    if(tr >= 0)
		{
		s = (double)sqrt(tr +1);
		w = 0.5f * s;
		s = 0.5f / s;
		x = (m.M33[1][2] - m.M33[2][1]) * s;
		y = (m.M33[2][0] - m.M33[0][2]) * s;
		z = (m.M33[0][1] - m.M33[1][0]) * s;
		}
    else
		{
		int i = 0; 
		if (m.M33[1][1] > m.M33[0][0])
			i = 1; 
		if(m.M33[2][2] > m.M33[i][i])
			i=2; 
		switch (i)
			{
			case 0:
				s   = (double)sqrt((m.M33[0][0] - (m.M33[1][1] + m.M33[2][2])) + 1);
				x = 0.5f * s;
				s   = 0.5f / s;
				y = (m.M33[1][0] + m.M33[0][1]) * s; 
				z = (m.M33[0][2] + m.M33[2][0]) * s;
				w = (m.M33[1][2] - m.M33[2][1]) * s;
				break;
			case 1:
				s   = (double)sqrt((m.M33[1][1] - (m.M33[2][2] + m.M33[0][0])) + 1);
				y = 0.5f * s;
				s   = 0.5f / s;
				z = (m.M33[2][1] + m.M33[1][2]) * s;
				x = (m.M33[1][0] + m.M33[0][1]) * s;
				w = (m.M33[2][0] - m.M33[0][2]) * s;
				break;
			case 2:
				s   = (double)sqrt((m.M33[2][2] - (m.M33[0][0] + m.M33[1][1])) + 1);
				z = 0.5f * s;
				s   = 0.5f / s;
				x = (m.M33[0][2] + m.M33[2][0]) * s;
				y = (m.M33[2][1] + m.M33[1][2]) * s;
				w = (m.M33[0][1] - m.M33[1][0]) * s;
			}
		}
	}



inline void Quatd::slerp(const double t, const Quatd& leflo, const Quatd& right)
{
	// the slerp of a pair of unit clQuaternionerions is the weighted
	// interpolation between them, where the interpolation weight is
	// given by t = [0, 1.0]
	//
	// the trick to slerping is that we find the Angle between the two
	// clQuaternions by treating them as a pair of four vectors and getting the
	// cosine [as the Dot product].  
	//
	// then the slerp between two clQuaternionernions A and B is:
	//
	//       A * (upper_weight) + B * (lower_weight) 
	//		
	//	where the weights are the sines of the t-weighted Angle
	//	divided by the sine of the Angle. 
	//
	// the resulting clQuaternionernion is also a unit clQuaternionernion.


	// find the Angle between the two clQuaternions by treating 
	// them as 4-length vectors -- V1.V2 = cos(theta) 
	const double cosine = dot4(&leflo.w, &right.w); 
	const double Angle = (double)acos((double)cosine); // Angle is in radians.. 

	double lower_weight;
	double upper_weight;

	// set up our weights
	if(epsilonEquals(Angle, 0.0f, M3D_EPSILON))
	{
		// numerically unstable when Angle is close to 0, lerp instead
		lower_weight = t;
		upper_weight = 1.0f - t;
	}
	else
	{
		// this will also fall apart if w approaches k*pi/2 for k = [1, 2, ...]
		const double i_sin_angle = 1.0f / (double)sin(Angle);
		lower_weight = (double)sin(Angle - Angle*t) * i_sin_angle;
		upper_weight = (double)sin(Angle * t) * i_sin_angle;
	}

	w = (leflo.w * (lower_weight)) + (right.w * (upper_weight));
	x = (leflo.x * (lower_weight)) + (right.x * (upper_weight));
	y = (leflo.y * (lower_weight)) + (right.y * (upper_weight));
	z = (leflo.z * (lower_weight)) + (right.z * (upper_weight));
}




inline double Quatd::dot4(const double v1[4], const double v2[4]) const
{
	return 
		  (v1[0] * v2[0]) 
		+ (v1[1] * v2[1]) 
		+ (v1[2] * v2[2]) 
		+ (v1[3] * v2[3]);
}



inline bool Quatd::epsilonEquals(const double leflo, const double right, const double epsilon) const
{
	const double diff = (double)fabs(leflo - right);
	if(diff < epsilon) return true;
	return false;
}




inline Quatd& Quatd::operator*=(const Quatd& r_h_s)
	{
	multiply(r_h_s);
	return *this;
	}

inline Quatd& Quatd::operator*= (const double S)
	{
	x*=S;
	y*=S;
	z*=S;
	w*=S;
	return *this;
	}

inline Quatd& Quatd::operator+= (const Quatd& r_h_s)
	{
	x+=r_h_s.x;
	y+=r_h_s.y;
	z+=r_h_s.z;
	w+=r_h_s.w;
	return *this;
	}
inline Quatd& Quatd::operator-= (const Quatd& r_h_s)
	{
	x-=r_h_s.x;
	y-=r_h_s.y;
	z-=r_h_s.z;
	w-=r_h_s.w;
	return *this;
	}

inline Quatd Quatd::operator+(const Quatd& r_h_s) const
	{
	Quatd a;
	a.x=this->x+r_h_s.x;
	a.y=this->y+r_h_s.y;
	a.z=this->z+r_h_s.z;
	a.w=this->w+r_h_s.w;
	return a;
	}
inline Quatd Quatd::operator-(const Quatd& r_h_s) const
	{
	Quatd a;
	a.x=this->x-r_h_s.x;
	a.y=this->y-r_h_s.y;
	a.z=this->z-r_h_s.z;
	a.w=this->w-r_h_s.w;
	return a;
	}

inline Quatd Quatd::operator*(const double S) const
	{
	Quatd a;
	a.x=this->x*S;
	a.y=this->y*S;
	a.z=this->z*S;
	a.w=this->w*S;
	return a;
	}


inline Quatd Quatd::operator*(const Quatd& r_h_s) const
	{
	Quatd a;
	a.multiply(*this, r_h_s);
	return a;
	}

inline Vec3d Quatd::operator^(const Quatd& right) const
	{
	Vec3d a;
	a.x =this->w*right.x + right.w*this->x + this->y*right.z - right.y*this->z;
	a.y =this->w*right.y + right.w*this->y + this->z*right.x - right.z*this->x;
	a.z =this->w*right.z + right.w*this->z + this->x*right.y - right.x*this->y;
	return a;
	}



inline bool Quatd::operator==(const Quatd& r_h_s) const
	{
	return sameAs(r_h_s);
	}




inline Quatd& Quatd::operator=(const Quatd& r_h_s)
	{
	fromclQuaternion(r_h_s);
	return *this;
	}

inline Quatd& Quatd::operator=(const Vec3d& v)
	{
	w = 0.0f;
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
	}



inline bool Quatd::sameAs(const Quatd& r_h_s) const
{
	return	(w == r_h_s.w) && 
			(x == r_h_s.x) && 
			(y == r_h_s.y) && 
			(z == r_h_s.z);
}



//---------------------------------------------------------------
//---------------------------------------------------------------

inline Mat44d::Mat44d()							//init to identity
	{
	ID();
	}
inline void Mat44d::ID()								//init to identity
	{
	M44[0][0] = M44[1][1] = M44[2][2] = M44[3][3] = 1.0f;



				M44[1][0] = M44[2][0] = M44[3][0] = 
	M44[0][1] =				M44[2][1] = M44[3][1] = 
	M44[0][2] = M44[1][2] =				M44[3][2] = 
	M44[0][3] = M44[1][3] = M44[2][3] = 

	0.0f;
	}

inline Mat44d::Mat44d(Quatd & q)			//create from quat
	{
	FromQuat(q);
	}

inline void Mat44d::FromQuat(Quatd & q)		//sets itself to rotmatrix based on quat passed
	{
	const double w = q.w;
	const double x = q.x;
	const double y = q.y;
	const double z = q.z;

	M16[  0 ] = 1.0f - y*y*2.0f - z*z*2.0f;
	M16[  1 ] = x*y*2.0f + w*z*2.0f;	
	M16[  2 ] = x*z*2.0f - w*y*2.0f;	
	M16[  3 ] = 0.0f;	

	M16[  4 ] = x*y*2.0f - w*z*2.0f;	
	M16[  5 ] = 1.0f - x*x*2.0f - z*z*2.0f;	
	M16[  6 ] = y*z*2.0f + w*x*2.0f;	
	M16[  7 ] = 0.0f;	
	
	M16[  8 ] = x*z*2.0f + w*y*2.0f;	
	M16[  9 ] = y*z*2.0f - w*x*2.0f;	
	M16[ 10 ] = 1.0f - x*x*2.0f - y*y*2.0f;	
	M16[ 11 ] = 0.0f;	
	
	M16[ 12 ] = 0.0f;	
	M16[ 13 ] = 0.0f;	
	M16[ 14 ] = 0.0f;	
	M16[ 15 ] = 1.0f;	
	}

inline void Mat44d::Set(Mat44d & cloMatrix)		//This = Matrix
	{
	for (int n=0; n<16; n++)
		M16[n] = cloMatrix.M16[n];
	}

inline void Mat44d::SetTranslation(Vec3d & v)
	{
	M16[ 12 ] = v.x;
	M16[ 13 ] = v.y;	
	M16[ 14 ] = v.z;	
	}

inline void Mat44d::SetTranslationNegative(Vec3d & v)	//same as above, but sets vars to -clopVector.
	{
	M16[ 12 ] = -v.x;
	M16[ 13 ] = -v.y;	
	M16[ 14 ] = -v.z;	
	}

inline void Mat44d::TranslateNegative(Vec3d & v)//this = this * TranslationMx(-clopVector);
	{																//assumes all but 3x3 part is 0, except lower right corner = 1
	M44[3][0] = -M44[0][0] * v.x	-M44[1][0] * v.y		-M44[2][0] * v.z;
	M44[3][1] = -M44[0][1] * v.x	-M44[1][1] * v.y		-M44[2][1] * v.z;
	M44[3][2] = -M44[0][2] * v.x	-M44[1][2] * v.y		-M44[2][2] * v.z;

	}

inline void Mat44d::Copy3x3(Mat44d & m)	//copies the 3x3 part of the passed matrix to the 3x3 part of this matrix.
	{
	M16[  0 ] =m.M16[0];
	M16[  1 ] =m.M16[1];
	M16[  2 ] =m.M16[2];

	M16[  4 ] =m.M16[4];
	M16[  5 ] =m.M16[5];
	M16[  6 ] =m.M16[6];
	
	M16[  8 ] =m.M16[8];
	M16[  9 ] =m.M16[9];
	M16[ 10 ] =m.M16[10];
	}

inline void Mat44d::Copy3x3Transposed(Mat44d & m)	//same as above, but transposes 3x3 part as it copies.  (sets the inverse of a rotation)
	{
	M16[  0 ] =m.M16[0];
	M16[  1 ] =m.M16[4];
	M16[  2 ] =m.M16[8];

	M16[  4 ] =m.M16[1];
	M16[  5 ] =m.M16[5];
	M16[  6 ] =m.M16[9];
	
	M16[  8 ] =m.M16[2];
	M16[  9 ] =m.M16[6];
	M16[ 10 ] =m.M16[10];
	}

inline void Mat44d::Rotate(Vec3d & v)		//implicitly extends vector to 1x4 mx, and overwrites it with the result.
	{
	v.x = M44[0][0] * v.x	+M44[1][0] * v.y		+M44[2][0] * v.z;
	v.y = M44[0][1] * v.x	+M44[1][1] * v.y		+M44[2][1] * v.z;
	v.z = M44[0][2] * v.x	+M44[1][2] * v.y		+M44[2][2] * v.z;


	}

inline Mat44d  Mat44d::operator*  (const Mat44d& r) const
	{
	Mat44d a;	//temp result of multiplication

	a.M44[0][0] = M44[0][0] * r.M44[0][0] + M44[1][0] * r.M44[0][1] + M44[2][0] * r.M44[0][2];
	a.M44[0][1] = M44[0][1] * r.M44[0][0] + M44[1][1] * r.M44[0][1] + M44[2][1] * r.M44[0][2]; 
	a.M44[0][2] = M44[0][2] * r.M44[0][0] + M44[1][2] * r.M44[0][1] + M44[2][2] * r.M44[0][2]; 

	a.M44[1][0] = M44[0][0] * r.M44[1][0] + M44[1][0] * r.M44[1][1] + M44[2][0] * r.M44[1][2]; 
	a.M44[1][1] = M44[0][1] * r.M44[1][0] + M44[1][1] * r.M44[1][1] + M44[2][1] * r.M44[1][2]; 
	a.M44[1][2] = M44[0][2] * r.M44[1][0] + M44[1][2] * r.M44[1][1] + M44[2][2] * r.M44[1][2]; 

	a.M44[2][0] = M44[0][0] * r.M44[2][0] + M44[1][0] * r.M44[2][1] + M44[2][0] * r.M44[2][2]; 
	a.M44[2][1] = M44[0][1] * r.M44[2][0] + M44[1][1] * r.M44[2][1] + M44[2][1] * r.M44[2][2]; 
	a.M44[2][2] = M44[0][2] * r.M44[2][0] + M44[1][2] * r.M44[2][1] + M44[2][2] * r.M44[2][2]; 

	a.M44[3][0] = M44[0][0] * r.M44[3][0] + M44[1][0] * r.M44[3][1] + M44[2][0] * r.M44[3][2] + M44[3][0];
	a.M44[3][1] = M44[0][1] * r.M44[3][0] + M44[1][1] * r.M44[3][1] + M44[2][1] * r.M44[3][2] + M44[3][1];
	a.M44[3][2] = M44[0][2] * r.M44[3][0] + M44[1][2] * r.M44[3][1] + M44[2][2] * r.M44[3][2] + M44[3][2];
	return a;
	}

inline Vec3d   Mat44d::operator*  (const Vec3d & r) const
	{
	Vec3d a;	//temp result of multiplication
	//a.multiply(*this, r_h_s):

	a.x = M44[0][0] * r.x + M44[1][0] * r.y + M44[2][0] * r.z + M44[3][0];
	a.y = M44[0][1] * r.x + M44[1][1] * r.y + M44[2][1] * r.z + M44[3][1]; 
	a.z = M44[0][2] * r.x + M44[1][2] * r.y + M44[2][2] * r.z + M44[3][2]; 

	return a;
	}


//---------------------------------------------------------------
//---------------------------------------------------------------

inline Mat33d::Mat33d()							//init to identity
	{
	ID();
	}

inline void Mat33d::ID()								//init to identity
	{
	M33[0][0] = M33[1][1] = M33[2][2] = 1.0f;

				M33[1][0] = M33[2][0] = 
	M33[0][1] =				M33[2][1] = 
	M33[0][2] = M33[1][2] =				

	0.0f;
	}

inline Mat33d& Mat33d::operator=  (const Mat33d& r_h_s)
	{
	for (int n=0; n<9; n++)	//copy that to this matrix
	M9[n] = r_h_s.M9[n];
	return *this;
	}
inline Mat33d  Mat33d::operator*  (const Mat33d& r) const
	{
	Mat33d a;	//temp result of multiplication
	//a.multiply(*this, r_h_s):

	//cols of a:
	a.M33[0][0] = M33[0][0] * r.M33[0][0] + M33[1][0] * r.M33[0][1] + M33[2][0] * r.M33[0][2];
	a.M33[0][1] = M33[0][1] * r.M33[0][0] + M33[1][1] * r.M33[0][1] + M33[2][1] * r.M33[0][2]; 
	a.M33[0][2] = M33[0][2] * r.M33[0][0] + M33[1][2] * r.M33[0][1] + M33[2][2] * r.M33[0][2]; 

	a.M33[1][0] = M33[0][0] * r.M33[1][0] + M33[1][0] * r.M33[1][1] + M33[2][0] * r.M33[1][2]; 
	a.M33[1][1] = M33[0][1] * r.M33[1][0] + M33[1][1] * r.M33[1][1] + M33[2][1] * r.M33[1][2]; 
	a.M33[1][2] = M33[0][2] * r.M33[1][0] + M33[1][2] * r.M33[1][1] + M33[2][2] * r.M33[1][2]; 

	a.M33[2][0] = M33[0][0] * r.M33[2][0] + M33[1][0] * r.M33[2][1] + M33[2][0] * r.M33[2][2]; 
	a.M33[2][1] = M33[0][1] * r.M33[2][0] + M33[1][1] * r.M33[2][1] + M33[2][1] * r.M33[2][2]; 
	a.M33[2][2] = M33[0][2] * r.M33[2][0] + M33[1][2] * r.M33[2][1] + M33[2][2] * r.M33[2][2]; 

	return a;
	}
inline Mat33d  Mat33d::operator%  (const Mat33d& r) const
	{//mulitplies by transpose of r_h_s
	Mat33d a;	//temp result of multiplication

	//cols of a:
	a.M33[0][0] = M33[0][0] * r.M33[0][0] + M33[1][0] * r.M33[1][0] + M33[2][0] * r.M33[2][0];
	a.M33[0][1] = M33[0][1] * r.M33[0][0] + M33[1][1] * r.M33[1][0] + M33[2][1] * r.M33[2][0]; 
	a.M33[0][2] = M33[0][2] * r.M33[0][0] + M33[1][2] * r.M33[1][0] + M33[2][2] * r.M33[2][0]; 

	a.M33[1][0] = M33[0][0] * r.M33[0][1] + M33[1][0] * r.M33[1][1] + M33[2][0] * r.M33[2][1]; 
	a.M33[1][1] = M33[0][1] * r.M33[0][1] + M33[1][1] * r.M33[1][1] + M33[2][1] * r.M33[2][1]; 
	a.M33[1][2] = M33[0][2] * r.M33[0][1] + M33[1][2] * r.M33[1][1] + M33[2][2] * r.M33[2][1]; 

	a.M33[2][0] = M33[0][0] * r.M33[0][2] + M33[1][0] * r.M33[1][2] + M33[2][0] * r.M33[2][2]; 
	a.M33[2][1] = M33[0][1] * r.M33[0][2] + M33[1][1] * r.M33[1][2] + M33[2][1] * r.M33[2][2]; 
	a.M33[2][2] = M33[0][2] * r.M33[0][2] + M33[1][2] * r.M33[1][2] + M33[2][2] * r.M33[2][2]; 

	return a;
	}

inline Vec3d   Mat33d::operator*  (const Vec3d & r) const
	{
	Vec3d a;	//temp result of multiplication
	//a.multiply(*this, r_h_s):

	a.x = M33[0][0] * r.x + M33[1][0] * r.y + M33[2][0] * r.z;
	a.y = M33[0][1] * r.x + M33[1][1] * r.y + M33[2][1] * r.z; 
	a.z = M33[0][2] * r.x + M33[1][2] * r.y + M33[2][2] * r.z; 

	return a;
	}

inline Mat33d  Mat33d::operator+  (const Mat33d& r) const
	{
	Mat33d a;	//temp result of multiplication
	for (unsigned i=0; i<9; i++)
		a.M9[i] = M9[i] + r.M9[i];
	return a;
	}

inline Mat33d  Mat33d::operator*  (double  r) const
	{
	Mat33d a;	//temp result of multiplication
	for (unsigned i=0; i<9; i++)
		a.M9[i] = M9[i] * r;
	return a;
	}

inline void Mat33d::vecTransMult(const Vec3d & r, Vec3d & result) const	// performs dest = rhs^t * this
	{
	result.x = M33[0][0] * r.x + M33[0][1] * r.y + M33[0][2] * r.z;
	result.y = M33[1][0] * r.x + M33[1][1] * r.y + M33[1][2] * r.z; 
	result.z = M33[2][0] * r.x + M33[2][1] * r.y + M33[2][2] * r.z; 
	}


inline Vec3d   Mat33d::operator%  (const Vec3d & r) const
	{
	Vec3d a;	//temp result of multiplication
	//a.multiply(*this, r_h_s):

	a.x = M33[0][0] * r.x + M33[0][1] * r.y + M33[0][2] * r.z;
	a.y = M33[1][0] * r.x + M33[1][1] * r.y + M33[1][2] * r.z; 
	a.z = M33[2][0] * r.x + M33[2][1] * r.y + M33[2][2] * r.z; 

	return a;
	}

inline void Mat33d::FromQuat(Quatd & q)		//sets itself to rotmatrix based on quat passed
	{
	const double w = q.w;
	const double x = q.x;
	const double y = q.y;
	const double z = q.z;

	M9[  0 ] = 1.0f - y*y*2.0f - z*z*2.0f;
	M9[  1 ] = x*y*2.0f + w*z*2.0f;	
	M9[  2 ] = x*z*2.0f - w*y*2.0f;	

	M9[  3 ] = x*y*2.0f - w*z*2.0f;	
	M9[  4 ] = 1.0f - x*x*2.0f - z*z*2.0f;	
	M9[  5 ] = y*z*2.0f + w*x*2.0f;	
	
	M9[  6 ] = x*z*2.0f + w*y*2.0f;	
	M9[  7 ] = y*z*2.0f - w*x*2.0f;	
	M9[  8 ] = 1.0f - x*x*2.0f - y*y*2.0f;	
	
	}

inline void Mat33d::GetColumn(int i,Vec3d & col) const
	{
	col.x = M33[i][0];
	col.y = M33[i][1];
	col.z = M33[i][2];
	}
inline void  Mat33d::SetColumn(int i,Vec3d & col)
	{
	M33[i][0] = col.x;
	M33[i][1] = col.y;
	M33[i][2] = col.z;
	}

inline void Mat33d::Orthonormalize()  //uses GramSchmidt algorithm to orthogonalize, based on Maple code `Copyright (c) 1997 by Erich Kaltofen`
									// then normalize
	{
	Vec3d w,t1,t2,t3;
	double norm_sq;

    const double m=3;			//m := linalg[rowdim](A);
    const double n=3;			//n := linalg[coldim](A);
	int i, j, k = 0;				//k := 0;


    Mat33d v = *this;				//v := linalg[col](A, 1 .. n); -- 3 column vectors indexable
    Vec3d norm_u_sq;
																//# orthogonalize v[i]
    for (i=0; i<n; i++)//for i to n do
		{
        v.GetColumn(i,w);		//i-th column
        for (j=0; j<k; j++)									//# pull w along projection of v[i] with u[j]
			{
			this->GetColumn(j,t1);
			this->GetColumn(j,t2);
			v.GetColumn(i,t3);
			Vec3d temp = (t2 * (1.0f/norm_u_sq.GetElem(j)));
			Vec3d temp2 = temp  * t3.Dot( t1 );
			w -= temp;	
			}
																//        # compute norm of orthogonalized v[i]
      norm_sq = w.Dot(w);

		if (norm_sq != 0.0f) 
			{													//           # linearly independent new orthogonal vector 
																//       # add to list of u and norm_u_sq
			this->SetColumn(i,w);									//u = [op(u), evalm(w)];
            norm_u_sq.SetElem(i,norm_sq);						//norm_u_sq = [op(norm_u_sq), norm_sq];
            k ++;
			}
		}
	

	Vec3d temp;													//may want to do this in-place -- dunno if optimizer does this for me
	for (i=0; i<3; i++)
		{
		GetColumn(i,temp);
		temp.Normalize();
		SetColumn(i,temp);
		}

	}

#endif //__3DDMATH_H__
//NVIDIACOPYRIGHTBEGIN
///////////////////////////////////////////////////////////////////////////
// Copyright © 2010 NVIDIA Corporation.
// All rights reserved. www.nvidia.com
///////////////////////////////////////////////////////////////////////////
//NVIDIACOPYRIGHTEND

