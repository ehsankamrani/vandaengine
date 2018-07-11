/// ActionsAPI.cpp
///
/// Copyright 1997-2007 by David K. McAllister
/// http://www.ParticleSystems.org
///
/// This file implements the action API calls by creating action class instances,
/// which are either executed or added to an action list.
#include "stdafx.h"
#include "pAPI.h"
#include "PInternalState.h"

namespace PAPI {

void PContextActions_t::Avoid(const float magnitude, const float epsilon, const float look_ahead, const pDomain &dom)
{
    PAAvoid *A = new PAAvoid;

    A->position = dom.copy();
    A->magnitude = magnitude;
    A->epsilon = epsilon;
    A->look_ahead = look_ahead;

    A->SetKillsParticles(false);
    A->SetDoNotSegment(false);

    PS->SendAction(A);
}

void PContextActions_t::Bounce(const float friction, const float resilience, const float cutoff, const pDomain &dom)
{
    PABounce *A = new PABounce;

    A->position = dom.copy();
    A->oneMinusFriction = 1.0f - friction;
    A->resilience = resilience;
    A->cutoffSqr = fsqr(cutoff);

    A->SetKillsParticles(false);
    A->SetDoNotSegment(false);

    PS->SendAction(A);
}

void PContextActions_t::Callback(P_PARTICLE_CALLBACK callback, puint64 data)
{
    PACallback *A = new PACallback;
    A->callback = callback;
    A->Data = data;

    A->SetKillsParticles(false);
    A->SetDoNotSegment(false);

    PS->SendAction(A);
}

void PContextActions_t::CopyVertexB(const bool copy_pos, const bool copy_vel)
{
    PACopyVertexB *A = new PACopyVertexB;

    A->copy_pos = copy_pos;
    A->copy_vel = copy_vel;

    A->SetKillsParticles(false);
    A->SetDoNotSegment(false);

    PS->SendAction(A);
}

void PContextActions_t::Damping(const pVec &damping,
                                const float vlow, const float vhigh)
{
    PADamping *A = new PADamping;

    A->damping = damping;
    A->vlowSqr = fsqr(vlow);
    A->vhighSqr = fsqr(vhigh);

    A->SetKillsParticles(false);
    A->SetDoNotSegment(false);

    PS->SendAction(A);
}

void PContextActions_t::RotDamping(const pVec &damping,
                                   const float vlow, const float vhigh)
{
    PARotDamping *A = new PARotDamping;

    A->damping = damping;
    A->vlowSqr = fsqr(vlow);
    A->vhighSqr = fsqr(vhigh);

    A->SetKillsParticles(false);
    A->SetDoNotSegment(false);

    PS->SendAction(A);
}

void PContextActions_t::Explosion(const pVec &center, const float radius,
                                  const float magnitude, const float stdev, const float epsilon)
{
    PAExplosion *A = new PAExplosion;

    A->center = center;
    A->radius = radius;
    A->magnitude = magnitude;
    A->stdev = stdev;
    A->epsilon = epsilon;

    if(A->epsilon < 0.0f)
        A->epsilon = P_EPS;

    A->SetKillsParticles(false);
    A->SetDoNotSegment(false);

    PS->SendAction(A);
}

void PContextActions_t::Follow(const float magnitude, const float epsilon, const float max_radius)
{
    PAFollow *A = new PAFollow;

    A->magnitude = magnitude;
    A->epsilon = epsilon;
    A->max_radius = max_radius;

    A->SetKillsParticles(false);
    A->SetDoNotSegment(true);

    PS->SendAction(A);
}

void PContextActions_t::Gravitate(const float magnitude, const float epsilon, const float max_radius)
{
    PAGravitate *A = new PAGravitate;

    A->magnitude = magnitude;
    A->epsilon = epsilon;
    A->max_radius = max_radius;

    A->SetKillsParticles(false);
    A->SetDoNotSegment(true);

    PS->SendAction(A);
}

void PContextActions_t::Gravity(const pVec &dir)
{
    PAGravity *A = new PAGravity;

    A->direction = dir;

    A->SetKillsParticles(false);
    A->SetDoNotSegment(false);

    PS->SendAction(A);
}

void PContextActions_t::Jet(const pDomain &dom, const pDomain &accel)
{
    PAJet *A = new PAJet;

    A->dom = dom.copy();
    A->acc = accel.copy();

    A->SetKillsParticles(false);
    A->SetDoNotSegment(false);

    PS->SendAction(A);
}

void PContextActions_t::KillOld(const float age_limit, const bool kill_less_than)
{
    PAKillOld *A = new PAKillOld;

    A->age_limit = age_limit;
    A->kill_less_than = kill_less_than;

    A->SetKillsParticles(true);
    A->SetDoNotSegment(false);

    PS->SendAction(A);
}

void PContextActions_t::MatchVelocity(const float magnitude, const float epsilon, const float max_radius)
{
    PAMatchVelocity *A = new PAMatchVelocity;

    A->magnitude = magnitude;
    A->epsilon = epsilon;
    A->max_radius = max_radius;

    A->SetKillsParticles(false);
    A->SetDoNotSegment(true);

    PS->SendAction(A);
}

void PContextActions_t::MatchRotVelocity(const float magnitude, const float epsilon, const float max_radius)
{
    PAMatchRotVelocity *A = new PAMatchRotVelocity;

    A->magnitude = magnitude;
    A->epsilon = epsilon;
    A->max_radius = max_radius;

    A->SetKillsParticles(false);
    A->SetDoNotSegment(true);

    PS->SendAction(A);
}

void PContextActions_t::Move(const bool move_velocity, const bool move_rotational_velocity)
{
    PAMove *A = new PAMove;

    A->move_velocity = move_velocity;
    A->move_rotational_velocity = move_rotational_velocity;

    A->SetKillsParticles(false);
    A->SetDoNotSegment(false);

    PS->SendAction(A);
}

void PContextActions_t::OrbitLine(const pVec &p, const pVec &axis,
                                  const float magnitude, const float epsilon, const float max_radius)
{
    PAOrbitLine *A = new PAOrbitLine;

    A->p = p;
    A->axis = axis;
    A->axis.normalize();
    A->magnitude = magnitude;
    A->epsilon = epsilon;
    A->max_radius = max_radius;

    A->SetKillsParticles(false);
    A->SetDoNotSegment(false);

    PS->SendAction(A);
}

void PContextActions_t::OrbitPoint(const pVec &center, const float magnitude, const float epsilon, const float max_radius)
{
    PAOrbitPoint *A = new PAOrbitPoint;

    A->center = center;
    A->magnitude = magnitude;
    A->epsilon = epsilon;
    A->max_radius = max_radius;

    A->SetKillsParticles(false);
    A->SetDoNotSegment(false);

    PS->SendAction(A);
}

void PContextActions_t::RandomAccel(const pDomain &dom)
{
    PARandomAccel *A = new PARandomAccel;

    A->gen_acc = dom.copy();
    A->SetKillsParticles(false);
    A->SetDoNotSegment(false);

    PS->SendAction(A);
}

void PContextActions_t::RandomDisplace(const pDomain &dom)
{
    PARandomDisplace *A = new PARandomDisplace;

    A->gen_disp = dom.copy();
    A->SetKillsParticles(false);
    A->SetDoNotSegment(false);

    PS->SendAction(A);
}

void PContextActions_t::RandomVelocity(const pDomain &dom)
{
    PARandomVelocity *A = new PARandomVelocity;

    A->gen_vel = dom.copy();
    A->SetKillsParticles(false);
    A->SetDoNotSegment(false);

    PS->SendAction(A);
}

void PContextActions_t::RandomRotVelocity(const pDomain &dom)
{
    PARandomRotVelocity *A = new PARandomRotVelocity;

    A->gen_vel = dom.copy();
    A->SetKillsParticles(false);
    A->SetDoNotSegment(false);

    PS->SendAction(A);
}

void PContextActions_t::Restore(const float time_left, const bool vel, const bool rvel)
{
    PARestore *A = new PARestore;

    A->time_left = time_left;
    A->restore_velocity = vel;
    A->restore_rvelocity = rvel;

    A->SetKillsParticles(false);
    A->SetDoNotSegment(false);

    PS->SendAction(A);
}

void PContextActions_t::Sink(const bool kill_inside, const pDomain &dom)
{
    PASink *A = new PASink;

    A->position = dom.copy();
    A->kill_inside = kill_inside;

    A->SetKillsParticles(true);
    A->SetDoNotSegment(false);

    PS->SendAction(A);
}

void PContextActions_t::SinkVelocity(const bool kill_inside, const pDomain &dom)
{
    PASinkVelocity *A = new PASinkVelocity;

    A->velocity = dom.copy();
    A->kill_inside = kill_inside;

    A->SetKillsParticles(true);
    A->SetDoNotSegment(false);

    PS->SendAction(A);
}

void PContextActions_t::Sort(const pVec &eye, const pVec &look, const bool front_to_back, const bool clamp_negative)
{
    PASort *A = new PASort;

    A->Eye = eye;
    A->Look= look;
    A->front_to_back = front_to_back;
    A->clamp_negative = clamp_negative;

    A->SetKillsParticles(false);
    A->SetDoNotSegment(true); // WARNING: Particles aren't a function of other particles, but since it can screw up the working set thing, I'm setting it true.

    PS->SendAction(A);
}

void PContextActions_t::Source(const float particle_rate, const pDomain &dom)
{
    PASource *A = new PASource;

    A->position = dom.copy();
    A->particle_rate = particle_rate;
    A->SrcSt.set(PS->SrcSt);

    A->SetKillsParticles(false);
    A->SetDoNotSegment(true); // WARNING: Particles aren't a function of other particles, but does affect the working sets optimizations

    PS->SendAction(A);
}

void PContextActions_t::SpeedLimit(const float min_speed, const float max_speed)
{
    PASpeedLimit *A = new PASpeedLimit;

    A->min_speed = min_speed;
    A->max_speed = max_speed;

    A->SetKillsParticles(false);
    A->SetDoNotSegment(false);

    PS->SendAction(A);
}

void PContextActions_t::TargetColor(const pVec &color, const float alpha, const float scale)
{
    PATargetColor *A = new PATargetColor;

    A->color = color;
    A->alpha = alpha;
    A->scale = scale;

    A->SetKillsParticles(false);
    A->SetDoNotSegment(false);

    PS->SendAction(A);
}

void PContextActions_t::TargetSize(const pVec &size, const pVec &scale)
{
    PATargetSize *A = new PATargetSize;

    A->size = size;
    A->scale = scale;

    A->SetKillsParticles(false);
    A->SetDoNotSegment(false);

    PS->SendAction(A);
}

void PContextActions_t::TargetVelocity(const pVec &vel, const float scale)
{
    PATargetVelocity *A = new PATargetVelocity;

    A->velocity = vel;
    A->scale = scale;

    A->SetKillsParticles(false);
    A->SetDoNotSegment(false);

    PS->SendAction(A);
}

void PContextActions_t::TargetRotVelocity(const pVec &vel, const float scale)
{
    PATargetRotVelocity *A = new PATargetRotVelocity;

    A->velocity = vel;
    A->scale = scale;

    A->SetKillsParticles(false);
    A->SetDoNotSegment(false);

    PS->SendAction(A);
}

// If in immediate mode, quickly add a vertex.
// If building an action list, call Source().
void PContextActions_t::Vertex(const pVec &pos, const puint64 data)
{
    if(PS->in_new_list) {
        Source(1, PDPoint(pos));
        return;
    }

    // Immediate mode. Quickly add the vertex.
    Particle_t P;

    P.pos = pos;
    P.posB = PS->SrcSt.vertexB_tracks ? pos : PS->SrcSt.VertexB->Generate();
    P.size = PS->SrcSt.Size->Generate();
    P.up = PS->SrcSt.Up->Generate();
    P.vel = PS->SrcSt.Vel->Generate();
    P.rvel = PS->SrcSt.RotVel->Generate();
    P.color = PS->SrcSt.Color->Generate();
    P.alpha = PS->SrcSt.Alpha->Generate().x();
    P.age = PS->SrcSt.Age + pNRandf(PS->SrcSt.AgeSigma);
    P.mass = PS->SrcSt.Mass;
    P.data = data;
    // Note that we pass in the particle user data of the Vertex call, even if it's the default value.
    // We don't pass the PS->SrcSt data. Note that this creates an inconsistency if building an action list.

    PS->PGroups[PS->pgroup_id].Add(P);
}

void PContextActions_t::Vortex(
            const pVec &center, ///< tip of the vortex
            const pVec &axis, ///< the ray along the center of the vortex
            const float tightnessExponent, ///< like a Phong exponent that gives a curve to the vortex silhouette; 1.8 is good.
            const float max_radius, ///< defines the infinite cylinder of influence of this action. No particle further than max_radius from the axis is affected.
            const float inSpeed, ///< inward acceleration of particles outside the vortex
            const float upSpeed, ///< vertical acceleration of particles inside the vortex. Can be negative to counteract gravity.
            const float aroundSpeed) ///< acceleration around vortex of particles inside the vortex
{
    PAVortex *A = new PAVortex;

    A->tip = center;
    A->axis = axis;
    A->tightnessExponent = tightnessExponent;
    A->max_radius = max_radius;
    A->inSpeed = inSpeed;
    A->upSpeed = upSpeed;
    A->aroundSpeed = aroundSpeed;

    A->SetKillsParticles(false);
    A->SetDoNotSegment(false);

    PS->SendAction(A);
}

};
