//
// Created by jakub on 12/6/15.
//

#include <gtest/gtest.h>
#include <pso.h>

//-----------------------------------------------------------//
//  DECLARATIONS
//-----------------------------------------------------------//

/*
 * Creates a specific small particle
 * Word: 011 ends in state 2.
 * Word: 0 ends in state 1.
 */
Particle* createSmallParticle();

//-----------------------------------------------------------//
//  DEFINITIONS
//-----------------------------------------------------------//

Particle* createSmallParticle(){
    unsigned int stateCount = 4;
    unsigned int symbolCount = 2;

    double posMin = 0.0f;
    double posMax = 5.0f;

    double maxVel = 1.0f;

    Point<double> pos(8);
    pos[0] = 2.0f;
    pos[1] = 3.0f;
    pos[2] = 3.0f;
    pos[3] = 4.0f;

    pos[4] = 4.0f;
    pos[5] = 3.0f;
    pos[6] = 3.0f;
    pos[7] = 4.0f;

    Point<double> vel(8);

    double encodingDelta = 0.5;
    ParticleDecoder particleDecoder(stateCount, symbolCount, encodingDelta);

    Particle* p = new Particle (pos, vel,
                               posMin, posMax,
                               maxVel,
                               &particleDecoder);
    return p;
}

TEST(ParticleDecoder, ParticleDecodedToDFA_ComputeMediumWord_ProperState) {
    Particle* p = createSmallParticle();

    const DFA* dfa = p->getCurrentDFA();

    std::vector<int> word_entries{0,1,1};
    Word w(word_entries);

    int expectedState = 2;
    int actualState = dfa->compute(w);

    EXPECT_EQ(expectedState, actualState);

    delete p;
}

TEST(ParticleDecoder, ParticleDecodedToDFA_ComputeSmallWord_ProperState) {
    Particle* p = createSmallParticle();

    const DFA* dfa = p->getCurrentDFA();

    std::vector<int> word_entries2{0};
    Word w2(word_entries2);

    int expectedState = 1;
    int actualState = dfa->compute(w2);

    EXPECT_EQ(expectedState, actualState);

    delete p;
}
