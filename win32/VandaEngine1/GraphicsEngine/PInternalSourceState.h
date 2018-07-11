/// PInternalSourceState.h
///
/// Copyright 1997-2007 by David K. McAllister
/// http://www.ParticleSystems.org
///
/// Defines these classes: PInternalSourceState_t

#ifndef PInternalSourceState_h
#define PInternalSourceState_h

#include "pDomain.h"

namespace PAPI {

    const pVec P010(0.0f, 1.0f, 0.0f);
    const pVec P000(0.0f, 0.0f, 0.0f);
    const pVec P111(1.0f, 1.0f, 1.0f);

    class PInternalSourceState_t
    {
    public:
        pDomain *Up;
        pDomain *Vel;
        pDomain *RotVel;
        pDomain *VertexB;
        pDomain *Size;
        pDomain *Color;
        pDomain *Alpha;
        puint64 Data;
        float Age;
        float AgeSigma;
        float Mass;
        bool vertexB_tracks;

        PInternalSourceState_t() : Up(new PDPoint(P010)), Vel(new PDPoint(P000)), RotVel(new PDPoint(P000)),
            VertexB(new PDPoint(P000)), Size(new PDPoint(P111)), Color(new PDPoint(P111)), Alpha(new PDPoint(P111))
        {
            Data = 0;
            Age = 0.0f;
            AgeSigma = 0.0f;
            Mass = 1.0f;
            vertexB_tracks = true;
        }

        void WipeIt()
        {
            delete Up;
            delete Vel;
            delete RotVel;
            delete VertexB;
            delete Size;
            delete Color;
            delete Alpha;
        }

        ~PInternalSourceState_t() { WipeIt(); }

        // Make copies of the other guy's entries and point me to the copies
        void set(const PInternalSourceState_t &In)
        {
            WipeIt();
            Up = In.Up->copy();
            Vel = In.Vel->copy();
            RotVel = In.RotVel->copy();
            VertexB = In.VertexB->copy();
            Size = In.Size->copy();
            Color = In.Color->copy();
            Alpha = In.Alpha->copy();
            Data = In.Data;
            Age = In.Age;
            AgeSigma = In.AgeSigma;
            Mass = In.Mass;
            vertexB_tracks = In.vertexB_tracks;
        }
    };

};

#endif
