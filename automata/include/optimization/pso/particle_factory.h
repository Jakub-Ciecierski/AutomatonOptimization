//
// Created by jakub on 12/5/15.
//

#ifndef AC_PARTICLE_FACTORY_H
#define AC_PARTICLE_FACTORY_H

#include <entities/particle.h>

/*
 * Creates Particles for PSO algorithm
 */

class ParticleFactory {
private:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

public:
    ParticleFactory();

    ~ParticleFactory();

    /*
     * Generates Particles by uniform distribution.
     */
    std::vector<Particle*> generateUniformParticles(unsigned int count,
                                              unsigned int particleDimension,
                                              double posIntervalMin,
                                              double posIntervalMax,
                                              double velIntervalMin,
                                              double velIntervalMax,
                                              double maxVelocity,
                                              ParticleDecoder* pDecoder);
};


#endif //AC_PARTICLE_FACTORY_H
