//
// Created by jakub on 12/6/15.
//

#ifndef AC_PARTICLE_DECODER_H
#define AC_PARTICLE_DECODER_H

#include "transition_function.h"
#include "particle.h"

class Particle;

/*
 * Particle is a representation of an abstract object.
 * This class is responsible for decoding Particle position into
 * a object of interest.
 *
 * It contains methods which decode particle into a certain Object.
 *  Example
 *      decodeToTransitionFunction(Particle* p) decodes Particle to
 *      Transition Function object.
 */
class ParticleDecoder {
private:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    unsigned int _numberOfStates;
    unsigned int _numberOfSymbols;

    // Used to determine which integer value should given dimension be
    // decoded to
    double _encodingDelta;

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

public:
    ParticleDecoder(unsigned int numberOfStates, unsigned int numberOfSymbols,
                    double encodingDelta);

    ~ParticleDecoder();

    /*
     * Decodes particle into TransitionFunction.
     * Allocates memory for Transition Function
     */
    TransitionFunction* decodeToTransitionFunction(Particle *particle);
};


#endif //AC_PARTICLEDECODER_H
