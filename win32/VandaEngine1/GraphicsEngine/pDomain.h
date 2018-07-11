/// pDomain.h
///
/// Copyright 1997-2007 by David K. McAllister
/// http://www.ParticleSystems.org
///
/// This file defines the pDomain class and all of the classes that derive from it.

#ifndef pdomain_h
#define pdomain_h

#include "pError.h"
#include "pVec.h"

#include <vector>

namespace PAPI
{
    const float P_PLANAR_EPSILON = 1e-3f; ///< How small the dot product must be to declare that a point is in a plane for Within().

    /// A representation of a region of space.
    ///
    /// A Domain is a representation of a region of space. For example, the Source action uses a domain to describe the volume in which a particle
    /// will be created. A random point within the domain is chosen as the initial position of the particle. The Avoid, Sink and Bounce actions,
    /// for example, use domains to describe a volume in space for particles to steer around, die when they enter, or bounce off, respectively.
    ///
    /// Domains can be used to describe velocities. Picture the velocity vector as having its tail at the origin and its tip being in the domain.
    /// Domains can be used to describe colors in any three-valued color space. They can be used to describe three-valued sizes, such as Length, Width, Height.
    ///
    /// Several types of domains can be specified, such as points, lines, planes, discs, spheres, gaussian blobs, etc. Each subclass of the pDomain
    /// class represents a different kind of domain.
    ///
    /// All domains support two basic operations. The first is Generate, which returns a random point in the domain.
    ///
    /// The second basic operation is Within, which tells whether a given point is within the domain.
    ///
    /// The application programmer never calls the Generate or Within functions. The application will use the pDomain class and its derivatives solely
    /// as a way to communicate the domain to the API. The API's action commands will then perform operations on the domain, such as generating particles within it.
    class pDomain
    {
    public:
        virtual bool Within(const pVec &) const = 0; ///< Returns true if the given point is within the domain.
        virtual pVec Generate() const = 0; ///< Returns a random point in the domain.
        virtual float Size() const = 0; ///< Returns the size of the domain (length, area, or volume).

        virtual pDomain *copy() const = 0; // Returns a pointer to a heap-allocated copy of the derived class

        virtual ~pDomain() {}
    };

    /// A CSG union of multiple domains.
    ///
    /// A point is within this domain if it is within domain A OR B.
    /// Generate returns a point from either domain.
    /// Within returns true if pos is within A or within B.
    ///
    /// All domains have a Size() that is used to apportion probability between the domains in the union. Sizes of domains of the same dimensionality
    /// are commensurate but sizes of differing dimensionality are not.
    /// Thus, to properly distribute probability of Generate() choosing each domain, it is wise to only combine domains that have the same
    /// dimensionality. Note that thin shelled cylinders, cones, and spheres, where InnerRadius==OuterRadius, are considered 2D, not 3D. Thin
    /// shelled discs (circles) are considered 1D.
    class PDUnion : public pDomain
    {
    public:
        std::vector<pDomain *> Doms;
        float TotalSize;

    public:
        PDUnion() /// Use this one to create an empty PDUnion then call .insert() to add each item to it.
        {
            TotalSize = 0.0f;
        }

        PDUnion(const pDomain &A, const pDomain &B)
        {
            TotalSize = A.Size() + B.Size();
            Doms.push_back(A.copy());
            Doms.push_back(B.copy());
        }

        PDUnion(const pDomain &A, const pDomain &B, const pDomain &C)
        {
            TotalSize = A.Size() + B.Size() + C.Size();
            Doms.push_back(A.copy());
            Doms.push_back(B.copy());
            Doms.push_back(C.copy());
        }

        /// Makes a copy of all the subdomains and point to the copies.
        ///
        /// Note that the Generate() function gets a performance boost if you supply DomList with the largest domains first.
        PDUnion(const std::vector<pDomain *> &DomList)
        {
            TotalSize = 0.0f;
            for(std::vector<pDomain *>::const_iterator it = DomList.begin(); it != DomList.end(); it++) {
                Doms.push_back((*it)->copy());
                TotalSize += (*it)->Size();
            }
        }

        // Makes a copy of all the subdomains and point to the copies.
        PDUnion(const PDUnion &P)
        {
            TotalSize = 0.0f;
            for(std::vector<pDomain *>::const_iterator it = P.Doms.begin(); it != P.Doms.end(); it++) {
                Doms.push_back((*it)->copy());
                TotalSize += (*it)->Size();
            }
        }

        ~PDUnion()
        {
            for(std::vector<pDomain *>::const_iterator it = Doms.begin(); it != Doms.end(); it++) {
                delete (*it);
            }
        }

        /// Insert another domain into this PDUnion.
        void insert(const pDomain &A)
        {
            TotalSize += A.Size();
            Doms.push_back(A.copy());
        }

        bool Within(const pVec &pos) const /// Returns true if pos is within any of the domains.
        {
            for(std::vector<pDomain *>::const_iterator it = Doms.begin(); it != Doms.end(); it++)
                if((*it)->Within(pos)) return true;
            return false;
        }

        pVec Generate() const /// Generate a point in any subdomain, chosen by the ratio of their sizes.
        {
            float Choose = pRandf() * TotalSize, PastProb = 0.0f;
            for(std::vector<pDomain *>::const_iterator it = Doms.begin(); it != Doms.end(); it++) {
                PastProb += (*it)->Size();
                if(Choose <= PastProb)
                    return (*it)->Generate();
            }
            throw PErrInternalError("Sizes didn't add up to TotalSize in PDUnion::Generate().");
        }

        float Size() const
        {
            return TotalSize;
        }

        pDomain *copy() const
        {
            PDUnion *P = new PDUnion(*this);
            return P;
        }
    };

    /// A single point.
    ///
    /// Generate always returns this point. Within returns true if the point is exactly equal.
    class PDPoint : public pDomain
    {
    public:
        pVec p;

    public:
        PDPoint(const pVec &p0)
        {
            p = p0;
        }

        ~PDPoint()
        {
            // std::cerr << "del " << typeid(*this).name() << this << std::endl;
        }

        bool Within(const pVec &pos) const /// Always returns false.
        {
            return p == pos;
        }

        pVec Generate() const /// Returns true if the point is exactly equal.
        {
            return p;
        }

        float Size() const
        {
            return 1.0f;
        }

        pDomain *copy() const
        {
            PDPoint *P = new PDPoint(*this);
            return P;
        }
    };

    /// A line segment.
    ///
    /// e0 and e1 are the endpoints of the segment.
    ///
    /// Generate returns a random point on this segment. Within returns true for points within epsilon of the line segment.
    class PDLine : public pDomain
    {
    public:
        pVec p0, vec, vecNrm;
        float len;

    public:
        PDLine(const pVec &e0, const pVec &e1)
        {
            p0 = e0;
            vec = e1 - e0;
            vecNrm = vec;
            vecNrm.normalize();
            len = vec.length();
        }

        ~PDLine()
        {
        }

        bool Within(const pVec &pos) const /// Returns true for points within epsilon of the line segment.
        {
            pVec to = pos - p0;
            float d = dot(vecNrm, to);
            float dif = fabs(d - to.length()) / len; // Has a sqrt(). Kind of slow.
            return dif < 1e-7f; // It's inaccurate, so we need this epsilon.
        }

        pVec Generate() const /// Returns a random point on this segment.
        {
            return p0 + vec * pRandf();
        }

        float Size() const
        {
            return len;
        }

        pDomain *copy() const
        {
            PDLine *P = new PDLine(*this);
            return P;
        }
    };

    // Compute the inverse matrix of the plane basis.
    static inline void NewBasis(const pVec &u, const pVec &v, pVec &s1, pVec &s2)
    {
        pVec w = Cross(u, v);

        float det = 1.0f / (w.z()*u.x()*v.y() - w.z()*u.y()*v.x() - u.z()*w.x()*v.y() - u.x()*v.z()*w.y() + v.z()*w.x()*u.y() + u.z()*v.x()*w.y());

        s1 = pVec((v.y()*w.z() - v.z()*w.y()), (v.z()*w.x() - v.x()*w.z()), (v.x()*w.y() - v.y()*w.x()));
        s1 *= det;
        s2 = pVec((u.y()*w.z() - u.z()*w.y()), (u.z()*w.x() - u.x()*w.z()), (u.x()*w.y() - u.y()*w.x()));
        s2 *= -det;
    }

    /// A Triangle.
    ///
    /// p0, p1, and p2 are the vertices of the triangle. The triangle can be used to define an arbitrary geometrical model for particles to
    // bounce off, or generate particles on its surface (and explode them), etc.
    ///
    /// Generate returns a random point in the triangle. Within returns true for points within epsilon of the triangle. Currently it is not
    /// possible to sink particles that enter/exit a polygonal model. Suggestions?]
    class PDTriangle : public pDomain
    {
    public:
        pVec p, u, v, uNrm, vNrm, nrm, s1, s2;
        float uLen, vLen, D, area;

    public:
        PDTriangle(const pVec &p0, const pVec &p1, const pVec &p2)
        {
            p = p0;
            u = p1 - p0;
            v = p2 - p0;

            uLen = u.length();
            uNrm = u / uLen;
            vLen = v.length();
            vNrm = v / vLen;

            nrm = Cross(uNrm, vNrm); // This is the non-unit normal.
            nrm.normalize(); // Must normalize it.

            D = -dot(p, nrm);

            NewBasis(u, v, s1, s2); // Compute the inverse matrix of the plane basis.

            // Compute the area
            pVec Hgt = v - uNrm * dot(uNrm, v);
            float h = Hgt.length();
            area = 0.5f * uLen * h;
        }

        ~PDTriangle()
        {
        }

        bool Within(const pVec &pos) const /// Returns true for points within epsilon of the triangle.
        {
            pVec offset = pos - p;
            float d = dot(offset, nrm);

            if(d > P_PLANAR_EPSILON) return false;

            // Dot product with basis vectors of old frame
            // in terms of new frame gives position in uv frame.
            float upos = dot(offset, s1);
            float vpos = dot(offset, s2);

            // Did it cross plane outside triangle?
            return !(upos < 0 || vpos < 0 || (upos + vpos) > 1);
        }

        pVec Generate() const /// Returns a random point in the triangle.
        {
            float r1 = pRandf();
            float r2 = pRandf();
            pVec pos;
            if(r1 + r2 < 1.0f)
                pos = p + u * r1 + v * r2;
            else
                pos = p + u * (1.0f-r1) + v * (1.0f-r2);

            return pos;
        }

        float Size() const
        {
            return area;
        }

        pDomain *copy() const
        {
            PDTriangle *P = new PDTriangle(*this);
            return P;
        }
    };

    /// Rhombus-shaped planar region.
    ///
    /// p0 is a point on the plane. u0 and v0 are (non-parallel) basis vectors in the plane. They don't need to be normal or orthogonal.
    ///
    /// Generate returns a random point in the diamond-shaped patch whose corners are o, o+u, o+u+v, and o+v. Within returns true for points within epsilon of the patch.
    class PDRectangle : public pDomain
    {
    public:
        pVec p, u, v, uNrm, vNrm, nrm, s1, s2;
        float uLen, vLen, D, area;

    public:
        PDRectangle(const pVec &p0, const pVec &u0, const pVec &v0)
        {
            p = p0;
            u = u0;
            v = v0;

            uLen = u.length();
            uNrm = u / uLen;
            vLen = v.length();
            vNrm = v / vLen;

            nrm = Cross(uNrm, vNrm); // This is the non-unit normal.
            nrm.normalize(); // Must normalize it.

            D = -dot(p, nrm);

            NewBasis(u, v, s1, s2); // Compute the inverse matrix of the plane basis.

            // Compute the area
            pVec Hgt = v - uNrm * dot(uNrm, v);
            float h = Hgt.length();
            area = uLen * h;
        }

        ~PDRectangle()
        {
            // std::cerr << "del " << typeid(*this).name() << this << std::endl;
        }

        bool Within(const pVec &pos) const /// Returns true for points within epsilon of the patch.
        {
            pVec offset = pos - p;
            float d = dot(offset, nrm);

            if(d > P_PLANAR_EPSILON) return false;

            // Dot product with basis vectors of old frame
            // in terms of new frame gives position in uv frame.
            float upos = dot(offset, s1);
            float vpos = dot(offset, s2);

            // Did it cross plane outside triangle?
            return !(upos < 0 || upos > 1 || vpos < 0 || vpos > 1);
        }

        pVec Generate() const /// Returns a random point in the diamond-shaped patch whose corners are o, o+u, o+u+v, and o+v.
        {
            pVec pos = p + u * pRandf() + v * pRandf();
            return pos;
        }

        float Size() const
        {
            return area;
        }

        pDomain *copy() const
        {
            PDRectangle *P = new PDRectangle(*this);
            return P;
        }
    };

    /// Arbitrarily-oriented disc
    ///
    /// The point Center is the center of a disc in the plane with normal Normal. The disc has an OuterRadius. If InnerRadius is greater than 0,
    /// the domain is a flat washer, rather than a disc. The normal will get normalized, so it need not already be unit length.
    ///
    /// Generate returns a point inside the disc shell. Within returns true for points within epsilon of the disc.
    class PDDisc : public pDomain
    {
    public:
        pVec p, nrm, u, v;
        float radIn, radOut, radInSqr, radOutSqr, dif, D, area;

    public:
        PDDisc(const pVec &Center, const pVec Normal, const float OuterRadius, const float InnerRadius = 0.0f)
        {
            p = Center;
            nrm = Normal;
            nrm.normalize();

            if(InnerRadius < 0) throw PErrInvalidValue("Can't have negative radius.");
            if(OuterRadius < 0) throw PErrInvalidValue("Can't have negative radius.");

            if(OuterRadius > InnerRadius) {
                radOut = OuterRadius; radIn = InnerRadius;
            } else {
                radOut = InnerRadius; radIn = OuterRadius;
            }

            radInSqr = fsqr(radIn);
            radOutSqr = fsqr(radOut);
            dif = radOut - radIn;

            // Find a vector orthogonal to n.
            pVec basis(1.0f, 0.0f, 0.0f);
            if (fabsf(dot(basis, nrm)) > 0.999f)
                basis = pVec(0.0f, 1.0f, 0.0f);

            // Project away N component, normalize and cross to get
            // second orthonormal vector.
            u = basis - nrm * dot(basis, nrm);
            u.normalize();
            v = Cross(nrm, u);
            D = -dot(p, nrm);

            if(dif == 0.0f)
                area = 2.0f * M_PI * radOut; // Length of circle
            else
                area = M_PI * radOutSqr - M_PI * radInSqr; // Area or disc minus hole
        }

        ~PDDisc()
        {
        }

        bool Within(const pVec &pos) const /// Returns true for points within epsilon of the disc.
        {
            pVec offset = pos - p;
            float d = dot(offset, nrm);

            if(d > P_PLANAR_EPSILON) return false;

            float len = offset.length2();
            return len >= radInSqr && len <= radOutSqr;
        }

        pVec Generate() const /// Returns a point inside the disc shell.
        {
            // Might be faster to generate a point in a square and reject if outside the circle
            float theta = pRandf() * 2.0f * float(M_PI); // Angle around normal
            // Distance from center
            float r = radIn + pRandf() * dif;

            float x = r * cosf(theta); // Weighting of each frame vector
            float y = r * sinf(theta);

            pVec pos = p + u * x + v * y;
            return pos;
        }

        float Size() const
        {
            return 1.0f; // A plane is infinite, so what sensible thing can I return?
        }

        pDomain *copy() const
        {
            PDDisc *P = new PDDisc(*this);
            return P;
        }
    };

    /// Arbitrarily-oriented plane.
    ///
    /// The point p0 is a point on the plane. Normal is the normal vector of the plane. If you have a plane in a,b,c,d form remember that
    /// n = [a,b,c] and you can compute a suitable point p0 as p0 = -n*d. The normal will get normalized, so it need not already be unit length.
    ///
    /// Generate returns the point p0. Within returns true if the point is in the positive half-space of the plane (in the plane or on the side that Normal points to).
    class PDPlane : public pDomain
    {
    public:
        pVec p, nrm;
        float D;

    public:
        PDPlane(const pVec &p0, const pVec &Normal)
        {
            p = p0;
            nrm = Normal;
            nrm.normalize(); // Must normalize it.
            D = -dot(p, nrm);
        }

        ~PDPlane()
        {
        }

        // Distance from plane = n * p + d
        // Inside is the positive half-space.
        bool Within(const pVec &pos) const /// Returns true if the point is in the positive half-space of the plane (in the plane or on the side that Normal points to).
        {
            return dot(nrm, pos) >= -D;
        }

        // How do I sensibly make a point on an infinite plane?
        pVec Generate() const /// Returns the point p0.
        {
            return p;
        }

        float Size() const
        {
            return 1.0f; // A plane is infinite, so what sensible thing can I return?
        }

        pDomain *copy() const
        {
            PDPlane *P = new PDPlane(*this);
            return P;
        }
    };

    /// Axis-aligned box
    ///
    /// e0 and e1 are opposite corners of an axis-aligned box. It doesn't matter which of each coordinate is min and which is max.
    ///
    /// Generate returns a random point in this box. Within returns true if the point is in the box.
    ///
    /// It is only possible to bounce particles off the outside of the box, not the inside. Likewise, particles can only Avoid
    /// the box from the outside. To use the Avoid action inside a box, define the box as six planes.
    class PDBox : public pDomain
    {
    public:
        // p0 is the min corner. p1 is the max corner.
        pVec p0, p1, dif;
        float vol;

    public:
        PDBox(const pVec &e0, const pVec &e1)
        {
            p0 = e0;
            p1 = e1;
            if(e1.x() < e0.x()) { p0.x() = e1.x(); p1.x() = e0.x(); }
            if(e1.y() < e0.y()) { p0.y() = e1.y(); p1.y() = e0.y(); }
            if(e1.z() < e0.z()) { p0.z() = e1.z(); p1.z() = e0.z(); }

            dif = p1 - p0;
            vol = dot(dif, pVec(1,1,1));
        }

        ~PDBox()
        {
        }

        bool Within(const pVec &pos) const /// Returns true if the point is in the box.
        {
            return !((pos.x() < p0.x()) || (pos.x() > p1.x()) ||
                (pos.y() < p0.y()) || (pos.y() > p1.y()) ||
                (pos.z() < p0.z()) || (pos.z() > p1.z()));
        }

        pVec Generate() const /// Returns a random point in this box.
        {
            // Scale and translate [0,1] random to fit box
            return p0 + CompMult(pRandVec(), dif);
        }

        float Size() const
        {
            return vol;
        }

        pDomain *copy() const
        {
            PDBox *P = new PDBox(*this);
            return P;
        }
    };

    /// Cylinder
    ///
    /// e0 and e1 are the endpoints of the axis of the right cylinder. OuterRadius is the outer radius, and InnerRadius is the inner
    /// radius for a cylindrical shell. InnerRadius = 0 for a solid cylinder with no empty space in the middle.
    ///
    /// Generate returns a random point in the cylindrical shell. Within returns true if the point is within the cylindrical shell.
    class PDCylinder : public pDomain
    {
    public:
        pVec apex, axis, u, v; // Apex is one end. Axis is vector from one end to the other.
        float radOut, radIn, radOutSqr, radInSqr, radDif, axisLenInvSqr, vol;
        bool ThinShell;

    public:
        PDCylinder(const pVec &e0, const pVec &e1, const float OuterRadius, const float InnerRadius = 0.0f)
        {
            apex = e0;
            axis = e1 - e0;

            if(InnerRadius < 0) throw PErrInvalidValue("Can't have negative radius.");
            if(OuterRadius < 0) throw PErrInvalidValue("Can't have negative radius.");

            if(OuterRadius < InnerRadius) {
                radOut = InnerRadius; radIn = OuterRadius;
            } else {
                radOut = OuterRadius; radIn = InnerRadius;
            }

            radOutSqr = fsqr(radOut);
            radInSqr = fsqr(radIn);

            ThinShell = (radIn == radOut);
            radDif = radOut - radIn;

            // Given an arbitrary nonzero vector n, make two orthonormal
            // vectors u and v forming a frame [u,v,n.normalize()].
            pVec n = axis;
            float axisLenSqr = axis.length2();
            float len = sqrtf(axisLenSqr);
            axisLenInvSqr = axisLenSqr ? (1.0f / axisLenSqr) : 0.0f;
            n *= sqrtf(axisLenInvSqr);

            // Find a vector orthogonal to n.
            pVec basis(1.0f, 0.0f, 0.0f);
            if (fabsf(dot(basis, n)) > 0.999f)
                basis = pVec(0.0f, 1.0f, 0.0f);

            // Project away N component, normalize and cross to get
            // second orthonormal vector.
            u = basis - n * dot(basis, n);
            u.normalize();
            v = Cross(n, u);

            float EndCapArea = M_PI * radOutSqr - M_PI * radInSqr;
            if(ThinShell)
                vol = len * 2.0f * M_PI * radOut; // Surface area of cylinder
            else
                vol = EndCapArea * len; // Volume of cylindrical shell
        }

        ~PDCylinder()
        {
        }

        bool Within(const pVec &pos) const /// Returns true if the point is within the cylindrical shell.
        {
            // This is painful and slow. Might be better to do quick accept/reject tests.
            // Axis is vector from base to tip of the cylinder.
            // x is vector from base to pos.
            //         x . axis
            // dist = ---------- = projected distance of x along the axis
            //        axis. axis   ranging from 0 (base) to 1 (tip)
            //
            // rad = x - dist * axis = projected vector of x along the base

            pVec x = pos - apex;

            // Check axial distance
            float dist = dot(axis, x) * axisLenInvSqr;
            if(dist < 0.0f || dist > 1.0f)
                return false;

            // Check radial distance
            pVec xrad = x - axis * dist; // Radial component of x
            float rSqr = xrad.length2();

            return (rSqr >= radInSqr && rSqr <= radOutSqr);
        }

        pVec Generate() const /// Returns a random point in the cylindrical shell.
        {
            float dist = pRandf(); // Distance between base and tip
            float theta = pRandf() * 2.0f * float(M_PI); // Angle around axis
            // Distance from axis
            float r = radIn + pRandf() * radDif;

            // Another way to do this is to choose a random point in a square and keep it if it's in the circle.
            float x = r * cosf(theta);
            float y = r * sinf(theta);

            pVec pos = apex + axis * dist + u * x + v * y;
            return pos;
        }

        float Size() const/// Returns the thick cylindrical shell volume or the thin cylindrical shell area if OuterRadius==InnerRadius.
        {
            return vol;
        }

        pDomain *copy() const
        {
            PDCylinder *P = new PDCylinder(*this);
            return P;
        }
    };

    ///  Cone
    ///
    /// e0 is the apex of the cone and e1 is the endpoint of the axis at the cone's base. OuterRadius is the radius of the base of the cone.
    /// InnerRadius is the radius of the base of a cone to subtract from the first cone to create a conical shell. This is similar to the 
    /// cylindrical shell, which can be thought of as a large cylinder with a smaller cylinder subtracted from the middle. Both cones share the
    /// same apex and axis, which implies that the thickness of the conical shell tapers to 0 at the apex. InnerRadius = 0 for a solid cone with
    /// no empty space in the middle.
    ///
    /// Generate returns a random point in the conical shell. Within returns true if the point is within the conical shell.
    class PDCone : public pDomain
    {
    public:
        pVec apex, axis, u, v; // Apex is one end. Axis is vector from one end to the other.
        float radOut, radIn, radOutSqr, radInSqr, radDif, axisLenInvSqr, vol;
        bool ThinShell;

    public:
        PDCone(const pVec &e0, const pVec &e1, const float OuterRadius, const float InnerRadius = 0.0f)
        {
            apex = e0;
            axis = e1 - e0;

            if(InnerRadius < 0) throw PErrInvalidValue("Can't have negative radius.");
            if(OuterRadius < 0) throw PErrInvalidValue("Can't have negative radius.");

            if(OuterRadius < InnerRadius) {
                radOut = InnerRadius; radIn = OuterRadius;
            } else {
                radOut = OuterRadius; radIn = InnerRadius;
            }

            radOutSqr = fsqr(radOut);
            radInSqr = fsqr(radIn);

            ThinShell = (radIn == radOut);
            radDif = radOut - radIn;

            // Given an arbitrary nonzero vector n, make two orthonormal
            // vectors u and v forming a frame [u,v,n.normalize()].
            pVec n = axis;
            float axisLenSqr = axis.length2();
            float len = sqrtf(axisLenSqr);
            axisLenInvSqr = axisLenSqr ? 1.0f / axisLenSqr : 0.0f;
            n *= sqrtf(axisLenInvSqr);

            // Find a vector orthogonal to n.
            pVec basis(1.0f, 0.0f, 0.0f);
            if (fabsf(dot(basis, n)) > 0.999f)
                basis = pVec(0.0f, 1.0f, 0.0f);

            // Project away N component, normalize and cross to get
            // second orthonormal vector.
            u = basis - n * dot(basis, n);
            u.normalize();
            v = Cross(n, u);

            if(ThinShell)
                vol = sqrtf(axisLenSqr + radOutSqr) * M_PI * radOut; // Surface area of cone (not counting endcap)
            else {
                float OuterVol = 0.33333333f * M_PI * radOutSqr * len; 
                float InnerVol = 0.33333333f * M_PI * radInSqr * len;
                vol = OuterVol - InnerVol; // Volume of conical shell
            }
        }

        ~PDCone()
        {
        }

        bool Within(const pVec &pos) const /// Returns true if the point is within the conical shell.
        {
            // This is painful and slow. Might be better to do quick
            // accept/reject tests.
            // Let axis = vector from base to tip of the cone
            // x = vector from base to test point
            //         x . axis
            // dist = ---------- = projected distance of x along the axis
            //        axis. axis   ranging from 0 (base) to 1 (tip)
            //
            // rad = x - dist * axis = projected vector of x along the base

            pVec x = pos - apex;

            // Check axial distance
            // axisLenInvSqr stores 1 / dot(axis, axis)
            float dist = dot(axis, x) * axisLenInvSqr;
            if(dist < 0.0f || dist > 1.0f)
                return false;

            // Check radial distance; scale radius along axis for cones
            pVec xrad = x - axis * dist; // Radial component of x
            float rSqr = xrad.length2();

            return (rSqr >= fsqr(dist * radIn) && rSqr <= fsqr(dist * radOut));
        }

        pVec Generate() const /// Returns a random point in the conical shell.
        {
            float dist = pRandf(); // Distance between base and tip
            float theta = pRandf() * 2.0f * float(M_PI); // Angle around axis
            // Distance from axis
            float r = radIn + pRandf() * radDif;

            // Another way to do this is to choose a random point in a square and keep it if it's in the circle.
            float x = r * cosf(theta);
            float y = r * sinf(theta);

            // Scale radius along axis for cones
            x *= dist;
            y *= dist;

            pVec pos = apex + axis * dist + u * x + v * y;
            return pos;
        }

        float Size() const /// Returns the thick conical shell volume or the thin conical shell area if OuterRadius==InnerRadius.
        {
            return vol;
        }

        pDomain *copy() const
        {
            PDCone *P = new PDCone(*this);
            return P;
        }
    };

    /// Sphere
    ///
    /// The point Center is the center of the sphere. OuterRadius is the outer radius of the spherical shell and InnerRadius is the inner radius.
    ///
    /// Generate returns a random point in the thick shell at a distance between OuterRadius and InnerRadius from point Center. If InnerRadius
    /// is 0, then it is the whole sphere. Within returns true if the point lies within the thick shell at a distance between InnerRadius to OuterRadius from point Center.
    class PDSphere : public pDomain
    {
    public:
        pVec ctr;
        float radOut, radIn, radOutSqr, radInSqr, radDif, vol;
        bool ThinShell;

    public:
        PDSphere(const pVec &Center, const float OuterRadius, const float InnerRadius = 0.0f)
        {
            ctr = Center;

            if(InnerRadius < 0) throw PErrInvalidValue("Can't have negative radius.");
            if(OuterRadius < 0) throw PErrInvalidValue("Can't have negative radius.");

            if(OuterRadius < InnerRadius) {
                radOut = InnerRadius; radIn = OuterRadius;
            } else {
                radOut = OuterRadius; radIn = InnerRadius;
            }

            radOutSqr = fsqr(radOut);
            radInSqr = fsqr(radIn);

            ThinShell = (radIn == radOut);
            radDif = radOut - radIn;

            if(ThinShell)
                vol = 4.0f * M_PI * radOutSqr; // Surface area of sphere
            else {
                float OuterVol = 1.33333333f * M_PI * radOutSqr * radOut; 
                float InnerVol = 1.33333333f * M_PI * radInSqr * radIn;
                vol = OuterVol - InnerVol; // Volume of spherical shell
            }
        }

        ~PDSphere()
        {
        }

        bool Within(const pVec &pos) const /// Returns true if the point lies within the thick shell.
        {
            pVec rvec(pos - ctr);
            float rSqr = rvec.length2();
            return rSqr <= radOutSqr && rSqr >= radInSqr;
        }

        pVec Generate() const /// Returns a random point in the thick spherical shell.
        {
            pVec pos;

            do {
                pos = pRandVec() - vHalf; // Point on [-0.5,0.5] box
            } while (pos.length2() > fsqr(0.5)); // Make sure it's also on r=0.5 sphere.
            pos.normalize(); // Now it's on r=1 spherical shell

            // Scale unit sphere pos by [0..r] and translate
            if(ThinShell) // I can't remember why I make this distinction. Is it for precision or speed? Speed doesn't seem likely.
                pos = ctr + pos * radOut;
            else
                pos = ctr + pos * (radIn + pRandf() * radDif);

            return pos;
        }

        float Size() const /// Returns the thick spherical shell volume or the thin spherical shell area if OuterRadius==InnerRadius.
        {
            return vol;
        }

        pDomain *copy() const
        {
            PDSphere *P = new PDSphere(*this);
            return P;
        }
    };

    /// Gaussian blob
    ///
    /// The point Center is the center of a normal probability density of standard deviation StandardDev. The density is radially symmetrical.
    /// The blob domain allows for some very natural-looking effects because there is no sharp, artificial-looking boundary at the edge of the domain.
    ///
    /// Generate returns a point with normal probability density. Within has a probability of returning true equal to the probability density at the specified point.
    class PDBlob : public pDomain
    {
    public:
        pVec ctr;
        float stdev, Scale1, Scale2;

    public:
        PDBlob(const pVec &Center, const float StandardDev)
        {
            ctr = Center;
            stdev = StandardDev;
            float oneOverSigma = 1.0f/(stdev+0.000000000001f);
            Scale1 = -0.5f*fsqr(oneOverSigma);
            Scale2 = P_ONEOVERSQRT2PI * oneOverSigma;
        }

        ~PDBlob()
        {
        }

        bool Within(const pVec &pos) const /// Has a probability of returning true equal to the probability density at the specified point.
        {
            pVec x = pos - ctr;
            float Gx = expf(x.length2() * Scale1) * Scale2;
            return (pRandf() < Gx);
        }

        pVec Generate() const /// Returns a point with normal probability density.
        {
            return ctr + pNRandVec(stdev);
        }

        float Size() const /// Returns the probability density integral, which is 1.0.
        {
            return 1.0f;
        }

        pDomain *copy() const
        {
            PDBlob *P = new PDBlob(*this);
            return P;
        }
    };

};

#endif
