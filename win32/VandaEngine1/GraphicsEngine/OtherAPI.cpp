/// OtherAPI.cpp
///
/// Copyright 1997-2007 by David K. McAllister
/// http://www.ParticleSystems.org
///
/// This file implements the API calls that are not particle actions.
#include "stdafx.h"

#include "pAPI.h"
#include "PInternalState.h"

#include <iostream>

namespace PAPI {

    ////////////////////////////////////////////////////////
    // Source State setting calls

    void PContextSourceState_t::Color(const float red, const float green, const float blue, const float alpha)
    {
        Color(pVec(red, green, blue), alpha);
    }

    void PContextSourceState_t::Color(const pVec &color, const float alpha)
    {
        Color(PDPoint(color), PDPoint(pVec(alpha)));
    }

    void PContextSourceState_t::Color(const pDomain &cdom)
    {
        Color(cdom, PDPoint(pVec(1)));
    }

    void PContextSourceState_t::Color(const pDomain &cdom, const pDomain &adom)
    {
        delete PSS->Color;
        delete PSS->Alpha;
        PSS->Color = cdom.copy();
        PSS->Alpha = adom.copy();
    }

    void PContextSourceState_t::Data(const puint64 data)
    {
        PSS->Data = data;
    }

    void PContextSourceState_t::UpVec(const pVec &up)
    {
        delete PSS->Up;
        PSS->Up = new PDPoint(up);
    }

    void PContextSourceState_t::UpVec(const pDomain &dom)
    {
        delete PSS->Up;
        PSS->Up = dom.copy();
    }

    void PContextSourceState_t::Velocity(const pVec &v)
    {
        delete PSS->Vel;
        PSS->Vel = new PDPoint(v);
    }

    void PContextSourceState_t::Velocity(const pDomain &dom)
    {
        delete PSS->Vel;
        PSS->Vel = dom.copy();
    }

    void PContextSourceState_t::RotVelocity(const pVec &v)
    {
        delete PSS->RotVel;
        PSS->RotVel = new PDPoint(v);
    }

    void PContextSourceState_t::RotVelocity(const pDomain &dom)
    {
        delete PSS->RotVel;
        PSS->RotVel = dom.copy();
    }

    void PContextSourceState_t::VertexB(const pVec &v)
    {
        delete PSS->VertexB;
        PSS->VertexB = new PDPoint(v);
    }

    void PContextSourceState_t::VertexB(const pDomain &dom)
    {
        delete PSS->VertexB;
        PSS->VertexB = dom.copy();
    }


    void PContextSourceState_t::VertexBTracks(const bool trackVertex)
    {
        PSS->vertexB_tracks = trackVertex;
    }

    void PContextSourceState_t::Size(const pVec &size)
    {
        delete PSS->Size;
        PSS->Size = new PDPoint(size);
    }

    void PContextSourceState_t::Size(const pDomain &dom)
    {
        delete PSS->Size;
        PSS->Size = dom.copy();
    }

    void PContextSourceState_t::Mass(const float mass)
    {
        PSS->Mass = mass;
    }

    void PContextSourceState_t::StartingAge(const float age, const float sigma)
    {
        PSS->Age = age;
        PSS->AgeSigma = sigma;
    }

    void PContextSourceState_t::ResetSourceState()
    {
        PInternalSourceState_t tmp;
        PSS->set(tmp);
    }

    ////////////////////////////////////////////////////////
    // Action List Calls

    int PContextActionList_t::GenActionLists(const int action_list_count)
    {
        if(PS->in_new_list) throw PErrInNewActionList("Can't call GenActionLists while in NewActionList.");

        int ind = PS->GenerateALists(action_list_count);

        return ind;
    }

    void PContextActionList_t::NewActionList(const int action_list_num)
    {
        if(PS->in_new_list) throw PErrInNewActionList("Can't call NewActionList while in NewActionList.");

        PS->alist_id = action_list_num;
        if(PS->alist_id < 0 || PS->alist_id >= (int)PS->ALists.size()) throw PErrParticleGroup("Invalid action list number");

        PS->in_new_list = true;
        PS->ALists[PS->alist_id].resize(0); // Remove any old actions
    }

    void PContextActionList_t::EndActionList()
    {
        if(!PS->in_new_list) throw PErrInNewActionList("Can't call EndActionList while not in NewActionList.");

        PS->in_new_list = false;

        PS->alist_id = -1;
    }

    void PContextActionList_t::DeleteActionLists(const int action_list_num, const int action_list_count)
    {
        if(PS->in_new_list) throw PErrInNewActionList("Can't call DeleteActionLists while in NewActionList.");

        if(action_list_num < 0) throw PErrActionList("Invalid action list number.");

        if(action_list_num + action_list_count > (int)PS->ALists.size()) throw PErrActionList("Invalid action list number.");

        for(int i = action_list_num; i < action_list_num + action_list_count; i++) {
            PS->ALists[i].resize(0);
        }
    }

    void PContextActionList_t::CallActionList(const int action_list_num)
    {
        if(action_list_num < 0 || action_list_num >= (int)PS->ALists.size()) throw PErrActionList("Invalid action list number.");

        if(PS->in_new_list) {
            // Add this call as an action to the current list.
            PACallActionList *S = new PACallActionList;
            S->action_list_num = action_list_num;

            PS->SendAction(S);
        } else {
            // Execute the specified action list.
            PS->ExecuteActionList(PS->ALists[action_list_num]);
        }
    }

    void PContextActionList_t::TimeStep(const float newDT)
    {
        PS->dt = newDT;
    }

    // Sets the random seed. Unfortunately, it currently sets it for all contexts in this thread.
    void PContextActionList_t::Seed(const unsigned int seed)
    {
        pSRandf(seed);
    }

    ////////////////////////////////////////////////////////
    // Particle Group Calls

    // Create p_group_count particle groups, each with max_particles allocated.
    int PContextParticleGroup_t::GenParticleGroups(const int p_group_count, const size_t max_particles)
    {
        if(PS->in_new_list) throw PErrInNewActionList("Can't call GenParticleGroups while in NewActionList.");
        if(p_group_count < 0) throw PErrParticleGroup("Invalid particle group number 0");
        if(max_particles < 0) throw PErrParticleGroup("Invalid max_particles");

        int ind = PS->GeneratePGroups(p_group_count);

        for(int i = ind; i < ind + p_group_count; i++) {
            PS->PGroups[i].SetMaxParticles(max_particles);
        }

        return ind;
    }

    void PContextParticleGroup_t::DeleteParticleGroups(const int p_group_num, const int p_group_count)
    {
        if(PS->in_new_list) throw PErrInNewActionList("Can't call DeleteParticleGroups while in NewActionList.");
        if(p_group_num < 0) throw PErrParticleGroup("Invalid particle group number 1");
        if(p_group_count < 1) throw PErrParticleGroup("Invalid p_group_count");
        if(p_group_num + p_group_count > (int)PS->PGroups.size()) throw PErrParticleGroup("Invalid particle group number 2");

        for(int i = p_group_num; i < p_group_num + p_group_count; i++) {
            PS->PGroups[i].SetMaxParticles(0);
            PS->PGroups[i].GetList().resize(0);
        }
    }

    // Change which group is current.
    void PContextParticleGroup_t::CurrentGroup(const int p_group_num)
    {
        if(PS->in_new_list) throw PErrInNewActionList("Can't call CurrentGroup while in NewActionList.");
        if(p_group_num < 0 || p_group_num >= (int)PS->PGroups.size()) throw PErrParticleGroup("Invalid particle group number 3");

        PS->pgroup_id = p_group_num;
    }

    // Change the maximum number of particles in the current group.
    void PContextParticleGroup_t::SetMaxParticles(const size_t max_count)
    {
        if(PS->in_new_list) throw PErrInNewActionList("Can't call SetMaxParticles while in NewActionList.");
        if(max_count < 0) throw PErrParticleGroup("Invalid max_count.");

        // This can kill them and call their death callback.
        PS->PGroups[PS->pgroup_id].SetMaxParticles(max_count);
    }

    // Copy from the specified group to the current group.
    void PContextParticleGroup_t::CopyGroup(const int p_src_group_num, const size_t index, const size_t copy_count)
    {
        if(PS->in_new_list) throw PErrInNewActionList("Can't call CopyGroup while in NewActionList.");
        if(index < 0) throw PErrInNewActionList("index invalid in CopyGroup.");
        if(p_src_group_num < 0 || p_src_group_num >= (int)PS->PGroups.size()) throw PErrParticleGroup("Invalid particle group number 4");

        ParticleGroup &srcgrp = PS->PGroups[p_src_group_num];

        ParticleGroup &destgrp = PS->PGroups[PS->pgroup_id];

        // Find out exactly how many to copy.
        size_t ccount = copy_count;
        if(ccount > srcgrp.size() - index)
            ccount = srcgrp.size() - index;
        if(ccount > destgrp.GetMaxParticles() - destgrp.size())
            ccount = destgrp.GetMaxParticles() - destgrp.size();
        if(ccount<0)
            ccount = 0;

        // Directly copy the particles to the current list.
        for(size_t i=0; i<ccount; i++) {
            destgrp.Add(srcgrp.GetList()[index+i]);
        }
    }

    // Copy from the current group to application memory.
    size_t PContextParticleGroup_t::GetParticles(const size_t index, const size_t cnt, float *verts,
        float *color, float *vel, float *size, float *age)
    {
        if(PS->in_new_list) throw PErrInNewActionList("Can't call GetParticles while in NewActionList.");
        if(PS->pgroup_id < 0 || PS->pgroup_id >= (int)PS->PGroups.size()) throw PErrParticleGroup("GetParticles: Invalid pgroup_id");
        if(index < 0 || cnt < 0) throw PErrParticleGroup("GetParticles: Invalid index or count.");

        ParticleGroup &pg = PS->PGroups[PS->pgroup_id];

        size_t count = cnt;

        if(index + count > pg.size()) {
            count = pg.size() - index;
            if(count < 0) throw PErrParticleGroup("GetParticles: index out of bounds.");
        }

        int vi = 0, ci = 0, li = 0, si = 0, ai = 0;

        // This should be optimized.
        for(size_t i=index; i<index+count; i++) {
            const Particle_t &m = pg.GetList()[i];

            if(verts) {
                verts[vi++] = m.pos.x();
                verts[vi++] = m.pos.y();
                verts[vi++] = m.pos.z();
            }

            // XXX I should think about whether color means color3, color4, or what. For now, it means color4.
            if(color) {
                color[ci++] = m.color.x();
                color[ci++] = m.color.y();
                color[ci++] = m.color.z();
                color[ci++] = m.alpha;
            }

            if(vel) {
                vel[li++] = m.vel.x();
                vel[li++] = m.vel.y();
                vel[li++] = m.vel.z();
            }

            if(size) {
                size[si++] = m.size.x();
                size[si++] = m.size.y();
                size[si++] = m.size.z();
            }

            if(age) {
                age[ai++] = m.age;
            }
        }

        return count;
    }

    // Return a pointer to the particle data, together with the stride IN FLOATS
    // from one particle to the next and the offset IN FLOATS from the start of the particle
    // for each attribute's data. The number in the arg name is how many floats the attribute
    // consists of, for example vel3Ofs means the velocity consists of 3 floats.
    //
    // WARNING: This function gives the application access to memory allocated and controlled
    // by the Particle API. Don't do anything stupid with this power or you will regret it.
    size_t PContextParticleGroup_t::GetParticlePointer(float *&ptr, size_t &stride, size_t &pos3Ofs, size_t &posB3Ofs,
        size_t &size3Ofs, size_t &vel3Ofs, size_t &velB3Ofs, size_t &color3Ofs, size_t &alpha1Ofs, size_t &age1Ofs,
        size_t &up3Ofs, size_t &rvel3Ofs, size_t &upB3Ofs, size_t &mass1Ofs, size_t &data1Ofs)
    {
        ParticleGroup &pg = PS->PGroups[PS->pgroup_id];

        if(pg.size() < 1) throw PErrParticleGroup("GetParticlePointer called on empty particle group.");
        if(PS->in_new_list) throw PErrInNewActionList("Can't call GetParticlePointer while in NewActionList.");

        ParticleList::iterator it = pg.begin();
        Particle_t *p0 = &(*it);
        float *fp0 = (float *)p0;
        ptr = (float *)p0;

        if(pg.size() > 1) {
            Particle_t *p1 = &(*(it+1));
            float *fp1 = (float *)p1;
            stride = fp1 - fp0;
        } else
            stride = 0;

        pos3Ofs = (float *)&(p0->pos.x()) - fp0;
        posB3Ofs = (float *)&(p0->posB.x()) - fp0;
        size3Ofs = (float *)&(p0->size.x()) - fp0;
        vel3Ofs = (float *)&(p0->vel.x()) - fp0;
        velB3Ofs = (float *)&(p0->velB.x()) - fp0;
        color3Ofs = (float *)&(p0->color.x()) - fp0;
        alpha1Ofs = (float *)&(p0->alpha) - fp0;
        age1Ofs = (float *)&(p0->age) - fp0;
        up3Ofs = (float *)&(p0->up) - fp0;
        rvel3Ofs = (float *)&(p0->rvel) - fp0;
        upB3Ofs = (float *)&(p0->upB) - fp0;
        mass1Ofs = (float *)&(p0->mass) - fp0;
        data1Ofs = (float *)&(p0->data) - fp0;

        return pg.size();
    }

    // Returns the number of particles currently in the group.
    size_t PContextParticleGroup_t::GetGroupCount()
    {
        if(PS->pgroup_id < 0 || PS->pgroup_id >= (int)PS->PGroups.size()) throw PErrParticleGroup("GetGroupCount: Invalid particle group number");

        return PS->PGroups[PS->pgroup_id].size();
    }

    // Returns the maximum number of allowed particles
    size_t PContextParticleGroup_t::GetMaxParticles()
    {
        if(PS->pgroup_id < 0 || PS->pgroup_id >= (int)PS->PGroups.size()) throw PErrParticleGroup("GetMaxParticles: Invalid particle group number");

        return PS->PGroups[PS->pgroup_id].GetMaxParticles();
    }

    void PContextParticleGroup_t::BirthCallback(P_PARTICLE_CALLBACK callback, puint64 data)
    {
        if(PS->in_new_list) throw PErrInNewActionList("Can't call BirthCallback while in NewActionList.");

        PS->PGroups[PS->pgroup_id].SetBirthCallback(callback, data);
    }

    void PContextParticleGroup_t::DeathCallback(P_PARTICLE_CALLBACK callback, puint64 data)
    {
        if(PS->in_new_list) throw PErrInNewActionList("Can't call DeathCallback while in NewActionList.");

        PS->PGroups[PS->pgroup_id].SetDeathCallback(callback, data);
    }

    /// Set the number of particles that fit in the CPU's cache
    ///
    /// You probably don't need to call this function. It is the number of bytes in the working set. Most action lists apply several actions to the working set of particles, then load the next working set of particles and apply the same actions to them. This allows particles to stay resident in the CPU's cache for a longer period of time, potentially increasing performance dramatically.
    ///
    /// You specify the working set size in bytes. The default is 1.75 MB.
    void PContextParticleGroup_t::SetWorkingSetSize(const int set_size_bytes)
    {
        PS->PWorkingSetSize = set_size_bytes / sizeof(Particle_t);
    }

};
