//---------------------------------------------------------------------------

#ifndef __BOUNDS3D__

#define __BOUNDS3D__

//---------------------------------------------------------------------------



#include "3DDMath.h"



//-------------------------------------------------

class Bounds3d 

	{

	//-------------------------------------------------

	public:

	Bounds3d() { empty = true; }

	~Bounds3d() {}

	

	void clear() { empty = true; }

	

	void include(const Vec3d &v);

	void intersect(const Bounds3d &b2);

	void combine(const Bounds3d &b2);

	void transform(const Mat33d & orientation, const Vec3d & translation);

	

	bool isEmpty() const { return empty; }

	bool intersects(const Bounds3d &b) const;

	bool contain(const Vec3d &v) const;

	inline Vec3d dims() const { return max - min; }	



	inline Vec3d & getMin() { return min; }	//this returns reference, so its not const!

	inline Vec3d & getMax() { return max; }



	inline void set(double minx, double miny, double minz, double maxx, double maxy,double maxz)

		{

		empty = false;

		min.Set(minx, miny, minz);

		max.Set(maxx, maxy, maxz);

		}

	

	private:

	Vec3d min, max;

	bool empty;

	};

#endif

