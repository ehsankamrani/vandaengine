/// pVec.h - yet another 3D vector class.
///
/// Copyright 1997-2007 by David K. McAllister
/// Based on code Copyright 1997 by Jonathan P. Leech
/// http://www.ParticleSystems.org
///
/// A simple 3D float vector class for internal use by the particle systems.
///
/// I have experimented with an implementation of this class that uses four floats.
/// This allows the class to be implemented using
/// SSE intrinsics for faster execution on P4 and AMD processors.

#ifndef pvec_h
#define pvec_h

#include <iostream>
#include <cmath>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433f
#endif

#ifdef WIN32
// This is because their stupid compiler thinks it's smart.
#define inline __forceinline
#endif

namespace PAPI
{
    typedef unsigned long long puint64;

    const float P_SQRT2PI = 2.506628274631000502415765284811045253006f;
    const float P_ONEOVERSQRT2PI = (1.f / P_SQRT2PI);

    inline float fsqr(float f) { return f * f; }

#ifdef unix
    inline float pRandf() { return drand48(); }
    inline void pSRandf(int x) { srand48(x); }
#else
    const float P_ONEOVER_RAND_MAX = (1.0f/((float) RAND_MAX));
    inline float pRandf() { return ((float) rand())*P_ONEOVER_RAND_MAX; }
    inline void pSRandf(int x) { srand(x); }
#endif

    inline bool pSameSign(const float &a, const float &b) { return a * b >= 0.0f; }

    /// Return a random number with a normal distribution.
    inline float pNRandf(float sigma = 1.0f)
    {
        float x, y, r2;
        do {
            x = pRandf()*2.0f-1.0f;
            y = pRandf()*2.0f-1.0f;
            r2 = x*x+y*y;
        }
        while(r2 > 1.0f || r2 == 0.0f);

        float m = sqrtf(-2.0f * logf(r2)/r2);

        float px = x*m*sigma;
        // float py = y*m*sigma;

        return px;
    }

    /// A single-precision floating point three-vector.
    ///
    /// This class is used for packaging three floats for the application to pass into the API.
    ///
    /// This is also the class used internally to do vector math.
    class pVec
    {
        float vx, vy, vz;

    public:
        inline pVec(float ax, float ay, float az) : vx(ax), vy(ay), vz(az) {}
        inline pVec(float a) : vx(a), vy(a), vz(a) {}
        inline pVec() {}

        const float& x() const { return vx; }
        const float& y() const { return vy; }
        const float& z() const { return vz; }

        float& x() { return vx; }
        float& y() { return vy; }
        float& z() { return vz; }

        inline float length() const
        {
            return sqrtf(vx*vx+vy*vy+vz*vz);
        }

        inline float length2() const
        {
            return (vx*vx+vy*vy+vz*vz);
        }

        inline float normalize()
        {
            float onel = 1.0f / sqrtf(vx*vx+vy*vy+vz*vz);
            vx *= onel;
            vy *= onel;
            vz *= onel;

            return onel;
        }

        // Dot product
        friend inline float dot(const pVec &a, const pVec &b)
        {
            return b.x()*a.x() + b.y()*a.y() + b.z()*a.z();
        }

        // Scalar multiply
        inline pVec operator*(const float s) const
        {
            return pVec(vx*s, vy*s, vz*s);
        }

        inline pVec operator/(const float s) const
        {
            float invs = 1.0f / s;
            return pVec(vx*invs, vy*invs, vz*invs);
        }

        inline pVec operator+(const pVec& a) const
        {
            return pVec(vx+a.x(), vy+a.y(), vz+a.z());
        }

        inline pVec operator-(const pVec& a) const
        {
            return pVec(vx-a.x(), vy-a.y(), vz-a.z());
        }

        inline bool operator==(const pVec &a) const
        {
            return vx==a.x() && vy==a.y() && vz==a.z();
        }

        inline pVec operator-()
        {
            vx = -vx;
            vy = -vy;
            vz = -vz;
            return *this;
        }

        inline pVec& operator+=(const pVec& a)
        {
            vx += a.x();
            vy += a.y();
            vz += a.z();
            return *this;
        }

        inline pVec& operator-=(const pVec& a)
        {
            vx -= a.x();
            vy -= a.y();
            vz -= a.z();
            return *this;
        }

        inline pVec& operator*=(const float a)
        {
            vx *= a;
            vy *= a;
            vz *= a;
            return *this;
        }

        inline pVec& operator/=(const float a)
        {
            float b = 1.0f / a;
            vx *= b;
            vy *= b;
            vz *= b;
            return *this;
        }

        inline pVec& operator=(const pVec& a)
        {
            vx = a.x();
            vy = a.y();
            vz = a.z();
            return *this;
        }

        // Component-wise absolute value
        friend inline pVec Abs(const pVec &a)
        {
            return pVec(fabs(a.x()), fabs(a.y()), fabs(a.z()));
        }

        // Component-wise multiply
        friend inline pVec CompMult(const pVec &a, const pVec& b)
        {
            return pVec(b.x()*a.x(), b.y()*a.y(), b.z()*a.z());
        }

        friend inline pVec Cross(const pVec& a, const pVec& b)
        {
            return pVec(
                a.y()*b.z()-a.z()*b.y(),
                a.z()*b.x()-a.x()*b.z(),
                a.x()*b.y()-a.y()*b.x());
        }

        friend inline std::ostream& operator<<(std::ostream& os, const pVec& v)
        {
            os << &v << '[' << v.x() << ", " << v.y() << ", " << v.z() << ']';

            return os;
        }
    };

    // To offset [0 .. 1] vectors to [-.5 .. .5]
    static pVec vHalf(0.5, 0.5, 0.5);

    inline pVec pRandVec()
    {
        return pVec(pRandf(), pRandf(), pRandf());
    }

    inline pVec pNRandVec(float sigma)
    {
        float x, y, r2;
        do {
            x = pRandf()*2.0f-1.0f;
            y = pRandf()*2.0f-1.0f;
            r2 = x*x+y*y;
        }
        while(r2 > 1.0f || r2 == 0.0f);

        float m = sqrtf(-2.0f * logf(r2)/r2);

        float px = x*m*sigma;
        float py = y*m*sigma;
        return pVec(px, py, pNRandf(sigma));
    }

};

#endif
