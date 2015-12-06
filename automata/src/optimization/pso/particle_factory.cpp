//
// Created by jakub on 12/5/15.
//

#include "particle_factory.h"

ParticleFactory::ParticleFactory(){

}

ParticleFactory::~ParticleFactory(){

}


std::vector<Particle*>
ParticleFactory::generateUniformParticles(unsigned int count,
                                          unsigned int particleDimension,
                                          double posIntervalMin,
                                          double posIntervalMax,
                                          double velIntervalMin,
                                          double velIntervalMax,
                                          double maxVelocity,
                                          ParticleDecoder* pDecoder){
    std::vector<Particle*> particles(count);

    for(unsigned int i = 0; i < count; i++){
        Point<double> position(particleDimension);
        Point<double> velocity(particleDimension);

        for(unsigned int j = 0; j < particleDimension; j++){
            position[j] = utils::generateRandomNumber(posIntervalMin,
                                                      posIntervalMax);
            velocity[j] = utils::generateRandomNumber(velIntervalMin,
                                                      velIntervalMax);
        }

        Particle* particle = new Particle(position, velocity,
                                            posIntervalMin, posIntervalMax,
                                            maxVelocity, pDecoder);
        particles[i] = particle;
    }
    return particles;
}