/// pAPI.h
///
/// Copyright 1997-2007 by David K. McAllister
/// http://www.ParticleSystems.org
///
/// Include this file in all applications that use the Particle System API.
/// The Particle System API is distributed under the GNU LGPL.

#ifndef particle_api_h
#define particle_api_h

#include "pDomain.h"

namespace PAPI {
    /// This is the major and minor version number of this release of the API.
    const int P_VERSION = 220;

    /// A very large float value used as a default arg passed into functions
    const float P_MAXFLOAT = 1.0e16f; // Actually this must be < sqrt(MAXFLOAT) since we store this value squared.

    /// A very small float value added to some physical calculations to dampen them and improve stability
    const float P_EPS = 1e-3f;

    /// A very large number used as the default max number of particles to operate on
    const size_t P_MAXINT = 0x7fffffff;

    /// This is the type of the particle death callback function that you can register.
    typedef void (*P_PARTICLE_CALLBACK)(struct Particle_t &particle, puint64 data);

    class PInternalState_t; // The API-internal struct containing the context's state. Don't try to use it.
    class PInternalSourceState_t; // The API-internal struct containing the context's source state. Don't try to use it.

    /// These functions set the current state needed by Source() and Vertex() actions.
    ///
    /// These calls dictate the properties of particles to be created by Source() or Vertex().
    /// When particles are created within a NewActionList() / EndActionList() block, they will
    /// receive attributes from the state that was current when the action list was created (unlike OpenGL).
    /// When in immediate mode (not creating or calling an action list), particles are created
    /// with attributes from the current state.
    class PContextSourceState_t
    {
    public:
        /// Specify the color of particles to be created.
        ///
        /// This call is short-hand for Color(PDPoint(color), PDPoint(pVec(alpha)).
        ///
        /// The default color is 1,1,1,1 (opaque white if you interpret it as RGBA).
        void Color(const pVec &color, const float alpha = 1.0f);

        /// Specify the color of particles to be created.
        ///
        /// This call is short-hand for Color(PDPoint(color), PDPoint(pVec(alpha)).
        ///
        /// The default color is 1,1,1,1 (opaque white if you interpret it as RGBA).
        void Color(const float red, const float green, const float blue, const float alpha = 1.0f);

        /// Specify the domain for colors of particles to be created.
        ///
        /// Your application can interpret the color triple in any color space you choose. RGB is the most common, with colors ranging on 0.0 -> 1.0.
        /// For example, the PDLine(pVec(1, 0, 0), pVec(1, 1, 0)) will choose points on a line between red and yellow. Points outside the 0.0 -> 1.0
        /// range will not be clamped by the Particle System API. Some renderers may use colors on the range 0 -> 255, so the domain used to choose 
        /// the colors can be on that range. The alpha value is usually used for transparency.
        ///
        /// The particle color does not necessarily need to be used to represent color. It can be interpreted as an arbitrary three-vector.
        ///
        /// The default color is 1,1,1,1 (opaque white).
        void Color(const pDomain &cdom);

        /// Specify the domain for colors and alpha value of new particles.
        ///
        /// Your application can interpret the color triple in any color space you choose. RGB is the most common, with colors ranging on 0.0 -> 1.0.
        /// For example, the PDLine(pVec(1, 0, 0), pVec(1, 1, 0)) will choose points on a line between red and yellow. Points outside the 0.0 -> 1.0
        /// range will not be clamped by the Particle System API. Some renderers may use colors on the range 0 -> 255, so the domain used to choose
        /// the colors can be on that range. The alpha value is usually used for transparency.
        ///
        /// The particle color does not necessarily need to be used to represent color. It can be interpreted as an arbitrary three-vector.
        ///
        /// The default color is 1,1,1,1 (opaque white).
        void Color(const pDomain &cdom, ///< The color domain.
            const pDomain &adom ///< The X dimension of the alpha domain is used for alpha.
            );

        /// Specify the user data of particles to be created.
        ///
        /// All new particles will have the given user data value. This value could be cast from a pointer or could be any other useful value.
        ///
        /// The default user data is 0.
        void Data(const puint64 data);

        /// Specify the size of particles to be created.
        ///
        /// This call is short-hand for Size(PDPoint(size)).
        ///
        /// The default size is 1,1,1.
        void Size(const pVec &size);

        /// Specify the domain for the size of particles to be created.
        ///
        /// All new particles will have a size chosen randomly from within the specified domain. The size values may be negative.
        ///
        /// The size is not mass. It does not affect any particle dynamics, including acceleration and bouncing. It is merely a triple of rendering
        /// attributes, like color, and can be interpreted at the whim of the application programmer (that’s you). In particular, the three
        /// components do not need to be used together as three dimensions of the particle’s size. For example, one could be interpreted as radius,
        /// another as length, and another as density.
        ///
        /// The default size is 1,1,1.
        void Size(const pDomain &dom);

        /// Specify the mass of particles to be created.
        ///
        /// The mass is used in the particle dynamics math, such as F=m*a. It doesn't affect size for bouncing, etc.
        ///
        /// The default mass is 1.
        void Mass(const float mass);

        /// Specify the initial rotational velocity vector of particles to be created.
        void RotVelocity(const pVec &v);

        /// Specify the domain for the initial rotational velocity vector of particles to be created.
        ///
        /// For particles that will be rendered with complex shapes, like boulders, a rotation frame may be defined. The frame consists of the
        /// velocity vector, the Up vector, and the cross product of those, which you compute yourself.
        ///
        /// The default rotational velocity is 0,0,0.
        void RotVelocity(const pDomain &dom);

        /// Specify the initial age of particles to be created.
        ///
        /// The age parameter can be positive, zero, or negative. Giving particles different starting ages allows KillOld() to distinguish between
        /// which to kill in interesting ways. Setting sigma to a non-zero value will give the particles an initial age with a normal distribution
        /// with mean age and standard deviation sigma. When many particles are created at once this allows a few particles to die at each time step,
        /// yielding a more natural effect.
        ///
        /// The default age is 0 and its sigma is 0.
        void StartingAge(const float age, ///< mean starting age of particles
            const float sigma = 0.0f ///< standard deviation of particle starting age
            );

        /// Specify the initial up vector of particles to be created.
        ///
        /// This call is short-hand for UpVec(PDPoint(v)).
        ///
        /// The default Up vector is 0,1,0.
        void UpVec(const pVec &v);

        /// Specify the domain for the initial up vector of particles to be created.
        ///
        /// For particles that will be rendered with complex shapes, like boulders, a rotation frame may be defined. The frame consists of the
        /// velocity vector, the Up vector, and the cross product of those, which you compute yourself.
        ///
        /// The default Up vector is 0,1,0.
        void UpVec(const pDomain &dom);

        /// Specify the initial velocity vector of particles to be created.
        ///
        /// This call is short-hand for Velocity(PDPoint(vel)).
        ///
        /// The default Velocity vector is 0,0,0.
        void Velocity(const pVec &vel);

        /// Specify the domain for the initial velocity vector of particles to be created.
        ///
        /// The default Velocity vector is 0,0,0.
        void Velocity(const pDomain &dom);

        /// Specify the initial secondary position of new particles.
        ///
        /// The PositionB attribute is used to store a destination position for the particle. This is designed for actions such as Restore().
        ///
        /// The default PositionB is 0,0,0.
        void VertexB(const pVec &v);

        /// Specify the domain for the initial secondary position of new particles.
        ///
        /// The PositionB attribute is used to store a destination position for the particle. This is designed for actions such as Restore().
        ///
        /// The default PositionB is 0,0,0.
        void VertexB(const pDomain &dom);

        /// Specify that the initial secondary position of new particles be the same as their position.
        ///
        /// If true, the PositionB attribute of new particles comes from their position, rather than from the VertexB domain.
        ///
        /// The default value of VertexBTracks is true.
        void VertexBTracks(const bool track_vertex = true);

        /// Reset all particle creation state to default values.
        ///
        /// All state set by the PContextSourceState_t functions will be reset.
        void ResetSourceState();

    protected:
        PInternalSourceState_t *PSS;
        void InternalSetup(PInternalSourceState_t *Sr);
    };

    /// Action List Calls
    ///
    /// These calls create and operate on action lists, which are scripts of many actions
    /// to be applied together as a block to the current particle group. An empty action
    /// list is first created using GenActionLists(), and is then filled or compiled by calling
    /// NewActionList(), then calling Actions, then calling EndActionList(). Once the action
    /// list is filled, it is run via CallActionList(). Thus, an action list is sort of a
    /// higher-level action. Complex behaviors can be stored in an action list and then
    /// called later, even as part of another action list. Action lists cannot be edited.
    /// They can only be created or destroyed. To destroy an action list, call DeleteActionLists().
    ///
    /// When in immediate mode (not creating or calling an action list), particles are created
    /// with attributes from the current state. However, when particles are created within a 
    /// NewActionList() / EndActionList() block, they will receive attributes from the state that was
    /// current when the action list was created (unlike OpenGL).
    ///
    /// The time step length, dt, uses the value that is current when CallActionList() is executed, not the
    /// value of dt when the action list was created. This allows dt to be modified without recompiling action
    /// lists. Maybe this isn't a good idea. If it should be the other way in the future, let me know.
    class PContextActionList_t
    {
    public:
        /// Set the random number seed.
        ///
        /// The Particle API uses a pseudo-random number generator. The returned number is a function of the numbers already returned. If you start
        /// two threads, each with a ParticleContext_t they will both generate the same particles if given the same commands. If this is not desired,
        /// call Seed() on both of them with different seed values.
        /// The API currently uses the C standard library random number generator, whose state is per-thread, so all contexts in the thread share
        /// the same random number seed.
        void Seed(const unsigned int seed);

        /// Specify the time step length.
        ///
        /// The Particle System API uses a discrete time approximation to all actions. This means that actions are applied to the particles at a
        /// particular instant in time as if the action's effect accumulated over a small time interval, dt, with the world being constant over the
        /// interval. The clock is then "ticked" by the length of the interval and the actions can then be reapplied with the particles having their
        /// updated values. This is the standard method of doing almost all time-varying simulations in computer science.
        ///
        /// How does the time step, dt, relate to the application's frame rate? The easiest method is to apply the actions once per frame. If the
        /// application prefers to keep time in terms of seconds, dt can be set to (1 / frames_per_second). But more often, it is easier for a time
        /// unit to be one frame instead of one second. In this case, dt should be 1.0, which is the default.
        ///
        /// For higher quality, the application can apply particle actions more than once per frame. This provides smoother, more realistic results
        /// in many subtle ways. Suppose the application wanted to compute three animation steps for each rendered frame. Set dt to 1/3 its previous
        /// value using TimeStep(), then loop three times over all the action code that gets executed per frame, including the calls to Move. If using
        /// action lists, this can be simply a loop over the CallActionList() call. The run-time results should be about the same, but with fewer
        /// discrete approximation artifacts. Depending on how much non-particle work is done per frame, increasing the number of time steps per frame
        /// may or may not affect the frame rate very much.
        ///
        /// In terms of numerical integration, particle actions can be thought of as the first derivative of unknown functions dictating the particle
        /// attributes (such as position) over time. In order to compute the particle attributes these derivative functions must be integrated. Since
        /// closed form integration doesn't make sense for most actions, Euler's method is used instead. Euler's method is simply the method just 
        /// described – the evaluation of the derivative functions at a particular time and then incrementing the current particle values by these 
        /// derivative results times dt. In Euler's method, the smaller the dt, the more accurate the results.
        ///
        /// Unlike with other state setting calls, action lists execute using the current dt value set by TimeStep(), rather than the time step value 
        /// that was current when the action list was created. Making action lists independent of time step size allows the time step to be changed 
        /// without recompiling the action list.
        ///
        /// In general, it is folly to call TimeStep() in between other actions of a simulation frame. For example, calling Bounce(); TimeStep(); Move();
        /// can cause cause particles to pass through the bounce domain instead of bouncing off it.
        void TimeStep(const float new_dt);

        /// Execute the specified action list on the current particle group.
        ///
        /// Call the action functions as specified when this action list was created with NewActionList(). The actions are executed with the state
        /// values in effect when the action list was created, except the context's current value of dt is used, not the value of dt when the list
        /// was created.
        ///
        /// CallActionList() is the only function other than actions that can be stored in an action list. This allows action lists to become atomic
        /// operations in more complex action lists. When calling CallActionList() during the creation of a new action list, action_list_num does not
        /// need to indicate an existing action list.
        ///
        /// It is an error for action_list_num to not indicate an existing (generated) action list.
        void CallActionList(const int action_list_num);

        /// Delete one or more consecutive action lists.
        ///
        /// Deletes action_list_count action lists, with action_list_num being the list number of the first one. The lists must be numbered 
        /// sequentially, and must all exist. This removes the specified action lists from existence.
        void DeleteActionLists(const int action_list_num, ///< The handle of the first action list to delete
            const int action_list_count = 1 ///< How many action lists to delete
            );

        /// End the creation of a new action list.
        ///
        /// Obviously, it is an error to call EndActionList() without a corresponding call to NewActionList().
        void EndActionList();

        /// Generate a block of empty action lists.
        ///
        /// Returns the action list number of the first allocated list. All list numbers are in sequential order starting with the first list.
        /// Valid action list numbers are non-negative.
        int GenActionLists(const int action_list_count = 1 ///< How many action lists to create
            );

        /// Begin the creation of the specified action list.
        ///
        /// The action_list_num must have already been generated using GenActionLists. Most calls other than actions and state setting calls
        /// cannot be made between a call to NewActionList() and the corresponding call to EndActionList().
        /// If called on an action list that has previously been defined, the previous contents of the action list are destroyed and the action
        /// list will be created anew. This is as with glNewActionList() in OpenGL.
        void NewActionList(const int action_list_num);

    protected:
        PInternalState_t *PS; // The internal API data for this context is stored here.
        void InternalSetup(PInternalState_t *Sr); // Calls this after construction to set up the PS pointer
        PInternalState_t *getInternalState() const; // Return a pointer to the internal state
    };

    /// This class contains the API calls that operate on particle groups.
    ///
    /// A particle group is first created using GenParticleGroups(), which will create a sequentially-numbered
    /// set of particle groups and return the identifying number of the first generated
    /// particle group. You specify which group is current using CurrentGroup(). Unless otherwise
    /// stated, all other commands operate on the current particle group. The maximum number
    /// of particles in the group is specified using SetMaxParticles(). The particle group
    /// is then acted upon using the Actions.
    ///
    /// After the actions have been applied, the particles are rendered. This is done at
    /// the same stage of the application's execution as drawing other geometry. To draw
    /// a particle group in OpenGL, the application calls GetParticles() or GetParticlePointer()
    /// functions to get the vertex data, then sends it to OpenGL. When a particle group
    /// is no longer needed, it is deleted using DeleteParticleGroups().
    class PContextParticleGroup_t
    {
    public:
        /// Copy particles from the specified group into the current group.
        ///
        /// Copy particles from the specified particle group, p_src_group_num, to the current particle group. Only copy_count particles, starting 
        /// with number index are copied. Of course, the number of particles actually copied is bounded by the available space in the current
        /// particle group, and the number of particles actually in the source particle group. The particles are added, in sequential order, to the
        /// end of the current group. index is the index of the first particle in the source particle group to be copied.
        /// The group's BirthCallback(), if any, is called for each particle added to the list.
        void CopyGroup(const int p_src_group_num, ///< group number of the source particle group
            const size_t index = 0, ///< index of the first particle in the source list to copy
            const size_t copy_count = P_MAXINT ///< copy at most this many particles
            );

        /// Change which group is current.
        ///
        /// Makes p_group_num be the current particle group to which all actions and commands apply.
        void CurrentGroup(const int p_group_num);

        /// Delete one or more consecutive particle groups.
        ///
        /// Deletes p_group_count particle groups, with p_group_num being the particle group number of the first one. The groups must be numbered
        /// sequentially, and must all exist. This removes the specified particle groups from existence (and all their particles). It does not merely
        /// change the number of existing particles or the maximum size of the group.
        ///
        /// The DeathCallback is NOT called for the particles in the deleted groups. Should I change this?
        void DeleteParticleGroups(const int p_group_num, ///< handle of the first particle group to delete
            const int p_group_count = 1 ///< delete this many groups
            );

        /// Create particle groups, each with a maximum of max_particles.
        ///
        /// Generates p_group_count new particle groups and returns the particle group number of the first one. The groups are numbered sequentially,
        /// beginning with the number returned. Each particle group is set to have at most max_particles particles. Call SetMaxParticles() to change this.
        /// Particle group numbers of groups that have been deleted (using DeleteParticleGroups()) might be reused by GenParticleGroups().
        int GenParticleGroups(const int p_group_count = 1, ///< generate this many groups
            const size_t max_particles = 0 ///< each created group can have this many particles
            );

        /// Returns the number of particles existing in the current group.
        ///
        /// The number returned is less than or equal to the group's max_particles.
        size_t GetGroupCount();

        /// Return the maximum number of particles allowed in the current group.
        ///
        /// This can be changed with SetMaxParticles().
        size_t GetMaxParticles();

        /// Copy particles from the current group to application memory.
        ///
        /// Copies at most count particles beginning with the index-th particle in the current particle group into memory already allocated by the
        /// application. Three floats are returned for the position of each particle, representing its x,y,z location. Four floats are returned for
        /// the color of each particle, representing its R,G,B,A color. Three floats are returned for the velocity of each particle, representing
        /// its dx,dy,dz direction vector. Three floats are returned for the size of each particle, representing whatever the application wants them
        /// to. One float is returned for the age of each particle.
        ///
        /// GetParticles() returns the number of particles copied to application memory. Of course, the number of particles actually returned is
        /// bounded by count and by the number of particles actually in the particle group minus index.
        /// If verts, color, vel, size or age is NULL then the respective field will not be returned. index and count must be at least 0 and less
        /// than the number of particles. index + count must be less than the number of particles.
        /// As with all arrays in C, the index of the first particle is zero.
        ///
        /// The following code gets the position of all particles:
        ///
        /// int cnt = GetGroupCount();
        /// float *ppos = new float[cnt * 3];
        /// int num_ret = GetParticles(0, cnt, ppos);
        size_t GetParticles(const size_t index, ///< index of the first particle to return
            const size_t count, ///< max number of particles to return
            float *position = NULL, ///< location to store 3 floats per particle for position
            float *color = NULL, ///< location to store 4 floats per particle for color and alpha
            float *vel = NULL, ///< location to store 3 floats per particle for velocity
            float *size = NULL, ///< location to store 3 floats per particle for size
            float *age = NULL ///< location to store 1 float per particle for age
            );

        /// Return a pointer to particle data stored in API memory.
        ///
        /// This function exposes the internal storage of the particle data to the application. It provides a much higher performance way to render
        /// particles because it avoids copying. In fact, the returned pointers can typically be passed directly to OpenGL or D3D without the
        /// application ever owning a copy of the data.
        ///
        /// Writing to the returned memory is obviously unsafe. There may be auxiliary data that depend on the current values of the particle data.
        /// You can try it if you want to, but your code may break against future API versions.
        size_t GetParticlePointer(float *&ptr, ///< the returned pointer to the particle data
            size_t &stride, ///< the number of floats from one particle's value to the next particle's value
            size_t &pos3Ofs, ///< the number of floats from returned ptr to the first particle's position parameter
            size_t &posB3Ofs, ///< the number of floats from returned ptr to the first particle's positionB parameter
            size_t &size3Ofs, ///< the number of floats from returned ptr to the first particle's size parameter
            size_t &vel3Ofs, ///< the number of floats from returned ptr to the first particle's velocity parameter
            size_t &velB3Ofs, ///< the number of floats from returned ptr to the first particle's velocityB parameter
            size_t &color3Ofs, ///< the number of floats from returned ptr to the first particle's color parameter
            size_t &alpha1Ofs, ///< the number of floats from returned ptr to the first particle's alpha parameter
            size_t &age1Ofs, ///< the number of floats from returned ptr to the first particle's age parameter
            size_t &up3Ofs, ///< the number of floats from returned ptr to the first particle's up parameter
            size_t &rvel3Ofs, ///< the number of floats from returned ptr to the first particle's rvel parameter
            size_t &upB3Ofs, ///< the number of floats from returned ptr to the first particle's upB parameter
            size_t &mass1Ofs, ///< the number of floats from returned ptr to the first particle's mass parameter
            size_t &data1Ofs ///< the number of floats from returned ptr to the first particle's data parameter, which is a 64-bit integer, not a float
        );

        /// Change the maximum number of particles in the current group.
        ///
        /// If necessary, this will delete particles from the end of the particle group, but no other particles will be deleted.
        /// The DeathCallback() of deleted particles WILL be called.
        /// Call SetMaxParticles(0) to empty the group.
        void SetMaxParticles(const size_t max_count);

        /// Specify a particle creation callback.
        ///
        /// Specify a callback function within your code that should be called every time a particle is created. The callback is associated only
        /// with the particle group that is current at the time you make the BirthCallback() call. You can optionally pass a pointer to arbitrary
        /// data of your own, which is returned to your callback.
        ///
        /// The API's internal Particle_t struct is passed back to your callback function, so your application will have to include
        /// "ParticleLib/Particle.h", which it normally should not do.
        void BirthCallback(P_PARTICLE_CALLBACK callback, ///< Pointer to function of yours to call
            puint64 group_data = 0 ///< Arbitrary per-group data of yours to pass into your function
            );

        /// Specify a particle death callback.
        ///
        /// Specify a callback function within your code that should be called every time a particle is killed. The callback is associated only
        /// with the particle group that is current at the time you make the DeathCallback() call. You can optionally pass a pointer to arbitrary
        /// data of your own, which is returned to your callback.
        ///
        /// The API's internal Particle_t struct is passed back to your callback function, so your application will have to include
        /// "ParticleLib/Particle.h", which it normally should not do.
        void DeathCallback(P_PARTICLE_CALLBACK callback, ///< Pointer to function of yours to call
            puint64 group_data = 0 ///< Arbitrary per-group data of yours to pass into your function
            );

        /// Set the number of particles that fit in the CPU's cache
        ///
        /// You probably don't need to call this function. It is the number of bytes in the working set. Most action lists apply several actions to
        /// the working set of particles, then load the next working set of particles and apply the same actions to them. This allows particles to
        /// stay resident in the CPU's cache for a longer period of time, potentially increasing performance dramatically.
        ///
        /// You specify the working set size in bytes. The default is 768KB.
        void SetWorkingSetSize(const int set_size_bytes);

    protected:
        PInternalState_t *PS; // The internal API data for this context is stored here.
        void InternalSetup(PInternalState_t *Sr); // Calls this after construction to set up the PS pointer
    };

    /// This class contains the actual Action API calls.
    ///
    /// Actions modify the position, color, velocity, size, age, and other attributes of
    /// particles. All actions apply to the current particle group, as set by CurrentGroup().
    /// Some actions will add particles to or delete them from the particle group, and others
    /// will modify the particles in other ways. Typically, a series of actions will be
    /// applied to each particle group once (or more) per rendered frame.
    ////
    /// Remember that the amount of effect of an action call depends on the time step size,
    /// dt, as set by TimeStep. See TimeStep() for an explanation of time steps.
    ///
    /// Some functions have parameters with a default value of the constant P_EPS. P_EPS is a very small
    /// floating point constant that is most often used as the default value of the epsilon
    /// parameter to actions whose influence on a particle is relative to the inverse square
    /// of its distance from something. If that distance is very small, the amount of influence
    /// approaches infinity. Since all actions are computed using Euler's method, this can
    /// cause unsatisfying results in which particles are accelerated way too much. So this
    /// epsilon parameter is added to the distance before taking its inverse square, thus
    /// keeping the acceleration within reasonable limits. By varying epsilon, you specify
    /// what is reasonable. Larger epsilon make particles accelerate less.
    class PContextActions_t
    {
    public:
        /// Steer particles away from a domain of space.
        ///
        /// Particles are tested to see whether they will pass from being outside the specified domain to being inside it within look_ahead time
        /// units from now if the next Move() action were to occur now. The specific direction and amount of turn is dependent on the kind of
        /// domain being avoided.
        ///
        /// At present the only domains for which Avoid() is implemented are PDSphere, PDRectangle, PDTriangle, PDDisc and PDPlane.
        void Avoid(float magnitude, ///< how drastically the particle velocities are modified to avoid the obstacle at each time step.
            const float epsilon, ///< The amount of acceleration falls off inversely with the squared distance to the edge of the domain. But when that distance is small, the acceleration would be infinite, so epsilon is always added to the distance.
            const float look_ahead, ///< how far forward along the velocity vector to look for the obstacle
            const pDomain &dom ///< the space to avoid
            );

        /// Bounce particles off an object defined by a domain.
        ///
        /// Particles are tested to see whether they will pass from being outside the specified domain to being inside it if the next Move()
        /// action were to occur now. If they would pass through the surface of the domain, they are instead bounced off it. That is, their 
        /// velocity vector is decomposed into components normal to the surface and tangent to the surface. The direction of the normal component
        /// is reversed, and friction, resilience and cutoff are applied to the components. They are then recomposed into a new velocity heading
        /// away from the surface.
        ///
        /// Since particles are tested to see whether they would pass through the domain if Move() were called now, it is best to have Bounce()
        /// be the last action that modifies a particle's velocity before calling Move().
        /// Also, actions such as RandomDisplace() that modify a particle's position directly, rather than modifying its velocity vector, may yield
        /// unsatisfying results when used with Bounce().
        ///
        /// At present the only domains for which Bounce() is implemented are PDSphere, PDRectangle, PDTriangle, PDDisc and PDPlane. For spheres,
        /// the particle bounces off either the inside or the outside of the sphere. For planes, triangles and discs, the particles bounce off
        /// either side of the surface. For rectangles, particles bounce off either side of the diamond-shaped patch whose corners are o, o+u, o+u+v,
        /// and o+v. See the documentation on domains for further explanation.
        ///
        /// Bounce() doesn't work correctly with small time step sizes for particles sliding along a surface. The friction and resilience parameters
        /// should not be scaled by dt, since a bounce happens instantaneously. On the other hand, they should be scaled by dt because particles
        /// sliding along a surface will hit more often if dt is smaller. Adjust these parameters manually when you change dt.
        void Bounce(float friction, ///< The tangential component of the outgoing velocity vector is scaled by (1 - friction).
            const float resilience, ///< The normal component of the outgoing velocity vector is scaled by resilience.
            const float cutoff, ///< Only apply friction if the outgoing tangential velocity is greater than cutoff. This can allow particles to glide smoothly along a surface without sticking.
            const pDomain &dom ///< Bounce off the surface of this domain.
            );

        /// Call an arbitrary user-provided function on each particle in the group.
        ///
        /// The function will receive both your call data and the full Particle_t struct, which contains per-particle user data.
        void Callback(P_PARTICLE_CALLBACK callback, ///< Pointer to function of yours to call
            puint64 call_data = 0 ///< Arbitrary data of yours to pass into your function
            );

        /// Set the secondary position and velocity from current.
        void CopyVertexB(const bool copy_pos = true, ///< If true, sets the PositionB of each particle to the current position of that particle. This makes each particle remember this position so it can later return to it using the Restore() action.
            const bool copy_vel = false ///< If true, sets the velocityB of each particle to the current velocity of that particle. This can be useful for computing the orientation of the particle by copying a particle's velocity at the beginning of each time step. Then when drawing a particle, the cross-product velocity and velocityB yields a tangent vector.
            );

        /// Simulate air by dampening particle velocities.
        ///
        /// If a particle's velocity magnitude is within vlow and vhigh, then multiply each component of the velocity by the respective damping constant.
        /// Typically, the three components of damping will have the same value.
        ///
        /// There are no bounds on the damping constants. Thus, by giving values greater than 1.0 they may be used to speed up particles instead of slow them down.
        void Damping(const pVec &damping, ///< Component-wise multiply this vector by the velocity vector
            const float vlow = 0.0f, const float vhigh = P_MAXFLOAT);

        /// Simulate air by dampening rotational velocities.
        ///
        /// If a particle's rotational velocity magnitude is within vlow and vhigh, then multiply each component of the rotational velocity by
        /// the respective damping constant. Typically, the three components of damping will have the same value.
        ///
        /// There are no bounds on the damping constants. Thus, by giving values greater than 1.0 they may be used to speed up particles instead of slow them down.
        void RotDamping(const pVec &damping, ///< Component-wise multiply this vector by the rotational velocity vector
            const float vlow = 0.0f, const float vhigh = P_MAXFLOAT);

        /// Exert force on each particle away from explosion center.
        ///
        /// Causes an explosion by accelerating all particles away from the center. Particles are accelerated away from the center by an amount proportional to magnitude.
        /// The shock wave of the explosion has a gaussian magnitude. The peak of the wave front travels spherically outward from the center
        /// at the specified velocity. So at a given time step, particles at a distance (velocity * age) from center will receive the most
        /// acceleration, and particles not at the peak of the shock wave will receive a lesser outward acceleration.
        ///
        /// radius is the current radius of the explosion wave's peak. It is up to the application to increment the radius for each call to
        /// Explosion(). For Explosion() calls in action lists, this means you will need to recreate the action list each time step.
        ///
        /// You can set up a standing wave by not incrementing the radius.
        void Explosion(const pVec &center, ///< center point of shock wave
            const float radius, ///< current radius of wave peak
            const float magnitude, ///< scales the acceleration applied to particles
            const float sigma, ///< standard deviation of the gaussian; the sharpness or broadness of the strength of the wave.
            const float epsilon = P_EPS ///< The amount of acceleration falls off inversely with the squared distance to the edge of the domain. But when that distance is small, the acceleration would be infinite, so epsilon is always added to the distance.
            );

        /// Accelerate toward the next particle in the list.
        ///
        /// This allows snaky effects where the particles follow each other. Each particle is accelerated toward the next particle in the group.
        /// The Follow() action does not affect the last particle in the group. This allows controlled effects where the last particle in the group
        /// is killed after each time step and replaced by a new particle at a slightly different position. See KillOld() to learn how to kill
        /// the last particle in the group after each step.
        void Follow(float magnitude = 1.0f, ///< scales each particle's acceleration
            const float epsilon = P_EPS, ///< The amount of acceleration falls off inversely with the squared distance to the edge of the domain. But when that distance is small, the acceleration would be infinite, so epsilon is always added to the distance.
            const float max_radius = P_MAXFLOAT ///< defines the sphere of influence of this action. No particle further than max_radius from its predecessor is affected.
            );

        /// Accelerate each particle toward each other particle.
        ///
        /// Each particle is accelerated toward each other particle.
        /// This action is more computationally intensive than the others are because each particle is affected by each other particle.
        void Gravitate(const float magnitude = 1.0f, ///< scales each particle's acceleration
            const float epsilon = P_EPS, ///< The amount of acceleration falls off inversely with the squared distance to the edge of the domain. But when that distance is small, the acceleration would be infinite, so epsilon is always added to the distance.
            const float max_radius = P_MAXFLOAT ///< defines the sphere of influence of this action. No particle further than max_radius from another particle is affected.
            );

        /// Accelerate particles in the given direction.
        ///
        /// The gravity acceleration vector is simply added to the velocity vector of each particle at each time step. The magnitude of the
        /// gravity vector is the acceleration due to gravity.
        void Gravity(const pVec &dir);

        /// For particles in the domain of influence, accelerate them with a domain.
        ///
        /// For each particle within the jet's domain of influence, dom, Jet() chooses an acceleration vector from the domain acc and applies
        /// it to the particle's velocity.
        void Jet(const pDomain &dom, ///< apply jet to particles in this domain
            const pDomain &acc); ///< acceleration vector comes from this domain

        /// Get rid of older particles.
        ///
        /// Removes all particles older than age_limit. But if kill_less_than is true, it instead removes all particles newer than age_limit.
        /// age_limit is not clamped, so negative values are ok. This can be used in conjunction with StartingAge(-n) to create and then kill a particular set of particles.
        ///
        /// In order to kill a particular particle, set StartingAge() to a number that will never be a typical age for any other particle in the
        /// group, for example -1.0. Then emit the particle using Source() or Vertex(). Then do the rest of the particle actions and finally call
        /// KillOld(-0.9, true) to kill the special particle because it is the only one with an age less than -0.9.
        void KillOld(const float age_limit,
            const bool kill_less_than = false ///< true to kill particles younger than age_limit
            );

        /// Modify each particle’s velocity to be similar to that of its neighbors.
        ///
        /// Each particle is accelerated toward the weighted mean of the velocities of the other particles in the group.
        ///
        /// Using an epsilon similar in size to magnitude can increase the range of influence of nearby particles on this particle.
        void MatchVelocity(const float magnitude = 1.0f, ///< scales each particle's acceleration
            const float epsilon = P_EPS, ///< The amount of acceleration falls off inversely with the squared distance to the edge of the domain. But when that distance is small, the acceleration would be infinite, so epsilon is always added to the distance.
            const float max_radius = P_MAXFLOAT ///< defines the sphere of influence of this action. No particle further than max_radius from another particle is affected.
            );

        /// Modify each particle’s rotational velocity to be similar to that of its neighbors.
        ///
        /// Each particle is accelerated toward the weighted mean of the rotational velocities of the other particles in the group.
        ///
        /// Using an epsilon similar in size to magnitude can increase the range of influence of nearby particles on this particle.
        void MatchRotVelocity(const float magnitude = 1.0f, ///< scales each particle's acceleration
            const float epsilon = P_EPS, ///< The amount of acceleration falls off inversely with the squared distance to the edge of the domain. But when that distance is small, the acceleration would be infinite, so epsilon is always added to the distance.
            const float max_radius = P_MAXFLOAT ///< defines the sphere of influence of this action. No particle further than max_radius from another particle is affected.
            );

        /// Apply the particles' velocities to their positions, and age the particles.
        ///
        /// This action actually updates the particle positions by adding the current velocity to the current position and the current rotational
        /// velocity to the current up vector. This is typically the last particle action performed in an iteration of a particle simulation, and 
        /// typically only occurs once per iteration.
        ///
        /// The velocity is multiplied by the time step length, dt, before being added to the position. This implements Euler's method of numerical
        /// integration with a constant but specifiable step size. See TimeStep() for more on varying the time step size.
        void Move(const bool move_velocity = true, ///< apply velocity to position.
            const bool move_rotational_velocity = true ///< apply rotational velocity to Up vector. This is an optimization.
            );

        /// Accelerate particles toward the closest point on the given line.
        ///
        /// For each particle, this action computes the vector to the closest point on the line, and accelerates the particle in that direction.
        void OrbitLine(const pVec &p, ///< a point on the line
            const pVec &axis, ///< any vector parallel to the line
            const float magnitude = 1.0f, ///< scales each particle's acceleration
            const float epsilon = P_EPS, ///< The amount of acceleration falls off inversely with the squared distance to the edge of the domain. But when that distance is small, the acceleration would be infinite, so epsilon is always added to the distance.
            const float max_radius = P_MAXFLOAT ///< defines the cylinder of influence of this action. No particle further than max_radius from the line is affected.
            );

        /// Accelerate particles toward the given center point.
        ///
        /// For each particle, this action computes the vector to the center point, and accelerates the particle in the vector direction.
        void OrbitPoint(const pVec &center, ///< accelerate toward this point
            const float magnitude = 1.0f, ///< scales each particle's acceleration
            const float epsilon = P_EPS, ///< The amount of acceleration falls off inversely with the squared distance to the edge of the domain. But when that distance is small, the acceleration would be infinite, so epsilon is always added to the distance.
            const float max_radius = P_MAXFLOAT ///< defines the sphere of influence of this action. No particle further than max_radius from the center is affected.
            );

        /// Accelerate particles in random directions.
        ///
        /// For each particle, chooses an acceleration vector from the specified domain and adds it to the particle's velocity.
        /// Reducing the time step, dt, will make a higher probability of being near the original velocity after unit time. Smaller dt approach
        /// a normal distribution of velocity vectors instead of a square wave distribution.
        void RandomAccel(const pDomain &dom);

        /// Immediately displace position by a random amount.
        ///
        /// Chooses a displacement vector from the specified domain and adds it to the particle's position.
        /// Reducing the time step, dt, will make a higher probability of being near the original position after unit time. Smaller dt approach a
        /// normal distribution of particle positions instead of a square wave distribution.
        ///
        /// Since this action changes particle positions, rather than changing their velocities and depending on the Move() action to change the
        /// positions, unsatisfying results may occur when used with the Avoid() or Bounce() actions.
        /// In particular, particles may be displaced to the opposite side of the surface without bouncing off it.
        void RandomDisplace(const pDomain &dom);

        /// Replace particle velocity with a random velocity.
        ///
        /// For each particle, sets the particle's velocity vector to a random vector in the specified domain.
        /// This function is not affected by dt.
        void RandomVelocity(const pDomain &dom);

        /// Immediately assign a random rotational velocity.
        ///
        /// For each particle, sets the particle's rotational velocity vector to a random vector in the specified domain.
        /// This function is not affected by dt.
        void RandomRotVelocity(const pDomain &dom);

        /// Over time, restore particles to their target positionB and upB.
        ///
        /// If vel is true, computes a new velocity for each particle that will make the particle arrive at its positionB at the specified amount
        /// of time in the future. If rvel is true, computes a new rotational velocity that moves up toward upB.
        ///
        /// The curved path that the particles take is a parametric quadratic. Once the specified amount of time has passed, Restore() instead sets
        /// position and Up to equal positionB and upB and sets velocity and rotational velocity to 0 to freeze them in place.
        ///
        /// It is the application's responsibility to decrease time_left by dt on each call. When in an action list, this means you need to
        /// recreate the action list each time step.
        ///
        /// The positionB attribute of each particle is typically the particle's position when it was created, or it can be specified within a
        /// domain. This is controlled by VertexBTracks(), and VertexB(). The positionB can be set at any time to the particle's current position
        /// using the CopyVertexB() action.
        ///
        /// Restore(0) is the opposite of CopyVertexB(); it sets each particle's position to be equal to its positionB. However, this has the side
        /// effect of setting each particle's velocity to 0.
        void Restore(const float time, ///< how long more until particles should arrive at target position and orientation
            const bool vel = true, ///< restore positions
            const bool rvel = true ///< restore up vectors
            );

        /// Kill particles that have positions on wrong side of the specified domain.
        ///
        /// If kill_inside is true, deletes all particles inside the given domain. If kill_inside is false, deletes all particles outside the given domain.
        void Sink(const bool kill_inside, ///< true to kill particles inside the domain
            const pDomain &dom);

        /// Kill particles that have velocities on wrong side of the specified domain.
        ///
        /// If kill_inside is true, deletes all particles whose velocity vectors are inside the given domain. If kill_inside is false, deletes all
        /// particles whose velocity vectors are outside the given domain.
        /// This allows particles to die when they turn around, get too fast or too slow, etc. For example, use a sphere domain centered at the
        /// origin with a radius equal to the minimum velocity to kill particles that are too slow.
        void SinkVelocity(const bool kill_inside, ///< true to kill particles with velocities inside the domain
            const pDomain &dom);

        /// Sort the particles by their projection onto the look vector.
        ///
        /// Many rendering systems require rendering transparent particles in back-to-front order. The ordering is defined by the eye point and the
        /// look vector. These are the same vectors you pass into gluLookAt(), for example. The vector from the eye point to each particle's
        /// position is computed, then projected onto the look vector. Particles are sorted back-to-front by the result of this dot product.
        void Sort(const pVec &eye,
            const pVec &look,
            const bool front_to_back = false, ///< true to sort in front-to-back order instead of back-to-front
            const bool clamp_negative = false ///< true to set negative dot product values to zero before sorting. This speeds up sorting time. Particles behind the viewer won't be visible so their relative order doesn't matter.
            );

        /// Add particles with positions in the specified domain.
        ///
        /// Adds new particles to the current particle group. The particle positions are chosen from the given domain. All the other particle
        /// attributes such as color and velocity are chosen according to their current domains.
        ///
        /// When the Source action is called within an action list, the particle attribute domains used are those that were current when the Source
        /// command was called within the NewActionList() / EndActionList() block instead of when CallActionList() was called. Note that this is unlike OpenGL display lists.
        ///
        /// If particle_rate / dt is not an integer then Source() adjusts the number of particles to add during this time step so that the average
        /// number added per unit time is particle_rate.
        ///
        /// If too few particles seem to be added each frame, it is probably because the particle group is already full. If this is bad, you can
        /// grow the group using SetMaxParticles().
        void Source(const float particle_rate, ///< how many particles to add per unit time
            const pDomain &dom ///< particle positions are chosen from this domain
            );

        /// Clamp particle velocities to the given range.
        ///
        /// Computes each particle’s speed (the magnitude of its velocity vector) and if it is less than min_speed or greater than max_speed the
        /// velocity is scaled to within those bounds, while preserving the velocity vector’s direction.
        ///
        /// The vector [0,0,0] is an exception because it has no direction. Such vectors are not modified by SpeedLimit().
        void SpeedLimit(const float min_speed, const float max_speed = P_MAXFLOAT);

        /// Change color of all particles toward the specified color.
        ///
        /// Modifies the color and alpha of each particle to be scale percent of the way closer to the specified color and alpha. scale is 
        /// multiplied by dt before scaling the sizes. Thus, using smaller dt causes a slightly faster approach to the target color.
        ///
        /// This action makes all colors tend toward the specified, uniform color.
        /// The value of scale will usually be very small (less than 0.01) to yield a gradual transition.
        void TargetColor(const pVec &color, ///< target color
            const float alpha, ///< target alpha value
            const float scale ///< what percent of the way from the current color to the target color to transition in unit time
            );

        /// Change sizes of all particles toward the specified size.
        ///
        /// Modifies the size of each particle to be scale percent of the way closer to the specified size triple. This makes sizes grow
        /// asymptotically closer to the given size. scale is multiplied by dt before scaling the sizes. Thus, using smaller dt causes a slightly
        /// faster approach to the target size. The separate scales for each component allow only selected components to be scaled.
        ///
        /// This action makes all sizes tend toward the specified, uniform size. Future versions will have more actions that modify size.
        /// Please send me suggestions (perhaps with sample implementations).
        ///
        /// The value of scale will usually be very small (less than 0.01) to yield a gradual transition.
        void TargetSize(const pVec &size, ///< target size
            const pVec &scale ///< what percent of the way from the current size to the target size to transition in unit time
            );

        /// Change velocity of all particles toward the specified velocity.
        ///
        /// Modifies the velocity of each particle to be scale percent of the way closer to the specified velocity. This makes velocities
        /// grow asymptotically closer to the given velocity. scale is multiplied by dt before scaling the velocities. Thus, using smaller
        /// dt causes a slightly faster approach to the target velocity.
        ///
        /// This action makes all velocities tend toward the specified, uniform velocity.
        /// The value of scale will usually be very small (less than 0.01) to yield a gradual transition.
        void TargetVelocity(const pVec &vel, ///< target velocity
            const float scale ///< what percent of the way from the current velocity to the target velocity to transition in unit time
            );

        /// Change rotational velocity of all particles toward the specified rotational velocity.
        ///
        /// Modifies the rotational velocity of each particle to be scale percent of the way closer to the specified rotational velocity.
        /// This makes rotational velocities grow asymptotically closer to the given rotational velocity. scale is multiplied by dt before
        /// scaling the velocities. Thus, using smaller dt causes a slightly faster approach to the target rotational velocity.
        ///
        /// This action makes all rotational velocities tend toward the specified, uniform rotational velocity.
        /// The value of scale will usually be very small (less than 0.01) to yield a gradual transition.
        void TargetRotVelocity(const pVec &rvel, ///< rotational velocity
            const float scale ///< what percent of the way from the current rotational velocity to the target rotational velocity to transition in unit time
            );

        /// Add a single particle at the specified location.
        ///
        /// This action mostly is a shorthand for Source(1, PDPoint(x, y, z)) but allows different callback data per particle.
        ///
        /// When called in immediate mode, this action uses a slightly faster method to add a single particle to the current particle group.
        /// Also when in immediate mode, exactly one particle will be added per call, instead of an average of 1 / dt particles being added.
        /// Particle attributes are chosen according to their current domains, as with Source.
        ///
        /// The user data attribute is an exception. It always takes the attribute from the optional data parameter to Vertex(), overriding the source state value.
        ///
        /// This call is patterned after the glVertex() calls. It is useful for creating a particle group with exactly specified initial positions.
        /// For example, you can specify a geometrical model using Vertex calls, and then explode or deform it.
        void Vertex(const pVec &v, ///< position of particle to create
            puint64 data = 0 ///< application data to be passed to the birth and death callbacks
            );

        /// Accelerate particles in a vortex-like way.
        ///
        /// The vortex is a complicated action to use, but when done correctly it makes particles fly around like in a tornado.
        void Vortex(
            const pVec &center, ///< tip of the vortex
            const pVec &axis, ///< the ray along the center of the vortex
            const float tightnessExponent, ///< like a Phong exponent that gives a curve to the vortex silhouette; 1.0 is a cone; greater than 1.0 curves inward.
            const float max_radius, ///< defines the radius at the top of the vortex and the infinite cylinder of influence. No particle further than max_radius from the axis is affected.
            const float inSpeed, ///< inward acceleration of particles OUTSIDE the vortex
            const float upSpeed, ///< vertical acceleration of particles INSIDE the vortex. Can be negative to apply gravity.
            const float aroundSpeed ///< acceleration around vortex of particles INSIDE the vortex.
            );

    protected:
        PInternalState_t *PS; // The internal API data for this context is stored here.
        void InternalSetup(PInternalState_t *Sr); // Calls this after construction to set up the PS pointer
    };

    /// The Particle System API - Your app should have one of these.
    ///
    /// This is a complete instance of the Particle API. All API state is stored in the context.
    ///
    /// See the documentation of the four base classes for the description of all the API entry points.
    class ParticleContext_t : public PContextActionList_t, public PContextParticleGroup_t, public PContextActions_t, public PContextSourceState_t
    {
    public:
        /// The context's default constructor.
        ParticleContext_t();

        /// The context's destructor.
        ~ParticleContext_t();
    };

};

#endif
