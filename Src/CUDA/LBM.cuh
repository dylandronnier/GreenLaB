#ifndef __LBM_CUH_
#define __LBM_CUH_


typedef float2 velocity;
typedef float2 particle;


// This method updates the velocity field 'v' using the two complex
// arrays from the previous step: 'vx' and 'vy'. Here we scale the
// real components by 1/(dx*dy) to account for an unnormalized FFT.
__global__ void
updateVelocity_k(velocity *v, float *vx, float *vy,
                 int dx, int pdx, int dy, int lb, size_t pitch);

// This method updates the particles by moving particle positions
// according to the velocity field and time step. That is, for each
// particle: p(t+1) = p(t) + dt * v(p(t)).
__global__ void
advectParticles_k(particle *part, velocity *v, int dx, int dy,
                  float dt, int lb, size_t pitch);


#endif
