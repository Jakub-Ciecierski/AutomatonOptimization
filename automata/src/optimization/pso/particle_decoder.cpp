//
// Created by jakub on 12/6/15.
//

#include "particle_decoder.h"

ParticleDecoder::ParticleDecoder(unsigned int numberOfStates,
                                 unsigned int numberOfSymbols,
                                 double encodingDelta){
    this->_numberOfStates = numberOfStates;
    this->_numberOfSymbols = numberOfSymbols;

    this->_encodingDelta = encodingDelta;

}
ParticleDecoder::~ParticleDecoder(){

}

TransitionFunction* ParticleDecoder::decodeToTransitionFunction(
        Particle *particle){
    const Point<double>* position = particle->getPosition();
    int size = position ->size();

    vector<int> decodedParticle(size);

    for (int i = 0; i < size; i++) {
        int encodedValue;
        double delta;

        encodedValue = (int)(*position)[i];
        delta = (*position)[i] - encodedValue;
        if (delta >= global_settings::ENCODING_DELTA)
            encodedValue++;

        // We enumerate from 0
        decodedParticle[i] = encodedValue - 1;
    }

    TransitionFunction* tf = new TransitionFunction(this->_numberOfStates,
                                                    this->_numberOfSymbols,
                                                    decodedParticle);

    return tf;
}