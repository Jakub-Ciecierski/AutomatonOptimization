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
                                          unsigned int numberOfStates,
                                          unsigned int numberOfSymbols,
                                          double posIntervalMin,
                                          double posIntervalMax,
                                          double velIntervalMin,
                                          double velIntervalMax,
                                          double maxVelocity){

    unsigned int length = numberOfStates * numberOfSymbols;

    std::vector<Particle*> particles(count);

    for(unsigned int i = 0; i < count; i++){
        Point<double> position(length);
        Point<double> velocity(length);

        for(unsigned int j = 0; j < length; j++){
            position[j] = utils::generateRandomNumber(posIntervalMin,
                                                      posIntervalMax);
            velocity[j] = utils::generateRandomNumber(velIntervalMin,
                                                      velIntervalMax);
        }

        Particle* particle = new Particle(numberOfStates, numberOfSymbols,
                                          posIntervalMin, posIntervalMax,
                                          maxVelocity,
                                          position, velocity);
        particles[i] = particle;
    }
    return particles;
}