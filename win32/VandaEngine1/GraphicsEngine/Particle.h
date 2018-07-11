/// Particle.h
///
/// Copyright 1997-2007 by David K. McAllister
/// http://www.ParticleSystems.org
///
/// This file contains the definition of a particle.
/// It is only included by API implementation files, not by applications.

#ifndef Particle_h
#define Particle_h

#include "pVec.h"

namespace PAPI {

// #pragma pack(push,16) /* Must ensure class & union 16-B aligned */

// A single particle
struct Particle_t
{
    pVec pos;
    pVec vel;
    pVec color;	    // Color must be next to alpha so glColor4fv works.
    float alpha;	// This is both cunning and scary.
    float age;
    float tmp0;		// These temporaries are used as padding and for sorting.
    pVec size;
    pVec up;
    pVec rvel;
    pVec posB;
    pVec velB;	    // Used to compute binormal, normal, etc.
    pVec upB;
    float mass;
    puint64 data;		// arbitrary data for user

    inline Particle_t(const pVec &pos, const pVec &posB,
        const pVec &up, const pVec &upB,
        const pVec &vel, const pVec &velB,
        const pVec &rvel, const pVec &rvelB,
        const pVec &size, const pVec &color,
        float alpha, float age, float mass, puint64 data, float tmp0) :
    pos(pos), posB(posB),
        up(up), upB(upB),
        vel(vel), velB(velB),
        rvel(rvel),
        size(size), color(color),
        alpha(alpha), age(age), mass(mass), data(data), tmp0(0)
    {
    }

    inline Particle_t(const Particle_t &rhs) :
    pos(rhs.pos), posB(rhs.posB),
        up(rhs.up), upB(rhs.upB),
        vel(rhs.vel), velB(rhs.velB),
        rvel(rhs.rvel),
        size(rhs.size), color(rhs.color),
        alpha(rhs.alpha), age(rhs.age), mass(rhs.mass), data(rhs.data), tmp0(rhs.tmp0)
    {
    }

    Particle_t() : data(0)
    {
    }

    // For sorting.
    bool operator<(const Particle_t &P) const
    {
        return tmp0 < P.tmp0;
    }
};

// #pragma pack(pop) /* 16-B aligned */

};

#endif
