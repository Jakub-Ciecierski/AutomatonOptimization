#!/bin/bash

MAIN_DIR_LOG="./logs/RECONS_C5"
DIR_LOG="RECONS_C5"

#############################################################
# Settings
#############################################################

MAX_ITER=100
SWARM_SIZE=50

START_Q=3
END_Q=15

CLASS_SIZE=10
ONE=1
CLASS_MAX=$((CLASS_SIZE - ONE))
STATE_MAX=$((PSO_STATES_LENGTH - ONE))

#############################################################
# Paths to Words
#############################################################

WORD_SET_PATH='./res/words_C5_Train8000_Test10000.txt'

#############################################################
# Paths to DFA Tools
#############################################################

CLASS_S4_PATH[0]='./res/recons/class_s4_r5/dfa_s4_r5_1/s4_r5.dfa'
CLASS_S4_PATH[1]='./res/recons/class_s4_r5/dfa_s4_r5_2/s4_r5.dfa'
CLASS_S4_PATH[2]='./res/recons/class_s4_r5/dfa_s4_r5_3/s4_r5.dfa'
CLASS_S4_PATH[3]='./res/recons/class_s4_r5/dfa_s4_r5_4/s4_r5.dfa'
CLASS_S4_PATH[4]='./res/recons/class_s4_r5/dfa_s4_r5_5/s4_r5.dfa'
CLASS_S4_PATH[5]='./res/recons/class_s4_r5/dfa_s4_r5_6/s4_r5.dfa'
CLASS_S4_PATH[6]='./res/recons/class_s4_r5/dfa_s4_r5_7/s4_r5.dfa'
CLASS_S4_PATH[7]='./res/recons/class_s4_r5/dfa_s4_r5_8/s4_r5.dfa'
CLASS_S4_PATH[8]='./res/recons/class_s4_r5/dfa_s4_r5_9/s4_r5.dfa'
CLASS_S4_PATH[9]='./res/recons/class_s4_r5/dfa_s4_r5_10/s4_r5.dfa'

CLASS_S6_PATH[0]='./res/recons/class_s6_r5/dfa_s6_r5_1/s6_r5.dfa'
CLASS_S6_PATH[1]='./res/recons/class_s6_r5/dfa_s6_r5_2/s6_r5.dfa'
CLASS_S6_PATH[2]='./res/recons/class_s6_r5/dfa_s6_r5_3/s6_r5.dfa'
CLASS_S6_PATH[3]='./res/recons/class_s6_r5/dfa_s6_r5_4/s6_r5.dfa'
CLASS_S6_PATH[4]='./res/recons/class_s6_r5/dfa_s6_r5_5/s6_r5.dfa'
CLASS_S6_PATH[5]='./res/recons/class_s6_r5/dfa_s6_r5_6/s6_r5.dfa'
CLASS_S6_PATH[6]='./res/recons/class_s6_r5/dfa_s6_r5_7/s6_r5.dfa'
CLASS_S6_PATH[7]='./res/recons/class_s6_r5/dfa_s6_r5_8/s6_r5.dfa'
CLASS_S6_PATH[8]='./res/recons/class_s6_r5/dfa_s6_r5_9/s6_r5.dfa'
CLASS_S6_PATH[9]='./res/recons/class_s6_r5/dfa_s6_r5_10/s6_r5.dfa'

CLASS_S10_PATH[0]='./res/recons/class_s10_r5/dfa_s10_r5_1/s10_r5.dfa'
CLASS_S10_PATH[1]='./res/recons/class_s10_r5/dfa_s10_r5_2/s10_r5.dfa'
CLASS_S10_PATH[2]='./res/recons/class_s10_r5/dfa_s10_r5_3/s10_r5.dfa'
CLASS_S10_PATH[3]='./res/recons/class_s10_r5/dfa_s10_r5_4/s10_r5.dfa'
CLASS_S10_PATH[4]='./res/recons/class_s10_r5/dfa_s10_r5_5/s10_r5.dfa'
CLASS_S10_PATH[5]='./res/recons/class_s10_r5/dfa_s10_r5_6/s10_r5.dfa'
CLASS_S10_PATH[6]='./res/recons/class_s10_r5/dfa_s10_r5_7/s10_r5.dfa'
CLASS_S10_PATH[7]='./res/recons/class_s10_r5/dfa_s10_r5_8/s10_r5.dfa'
CLASS_S10_PATH[8]='./res/recons/class_s10_r5/dfa_s10_r5_9/s10_r5.dfa'
CLASS_S10_PATH[9]='./res/recons/class_s10_r5/dfa_s10_r5_10/s10_r5.dfa'

CLASS_S15_PATH[0]='./res/recons/class_s15_r5/dfa_s15_r5_1/s15_r5.dfa'
CLASS_S15_PATH[1]='./res/recons/class_s15_r5/dfa_s15_r5_2/s15_r5.dfa'
CLASS_S15_PATH[2]='./res/recons/class_s15_r5/dfa_s15_r5_3/s15_r5.dfa'
CLASS_S15_PATH[3]='./res/recons/class_s15_r5/dfa_s15_r5_4/s15_r5.dfa'
CLASS_S15_PATH[4]='./res/recons/class_s15_r5/dfa_s15_r5_5/s15_r5.dfa'
CLASS_S15_PATH[5]='./res/recons/class_s15_r5/dfa_s15_r5_6/s15_r5.dfa'
CLASS_S15_PATH[6]='./res/recons/class_s15_r5/dfa_s15_r5_7/s15_r5.dfa'
CLASS_S15_PATH[7]='./res/recons/class_s15_r5/dfa_s15_r5_8/s15_r5.dfa'
CLASS_S15_PATH[8]='./res/recons/class_s15_r5/dfa_s15_r5_9/s15_r5.dfa'
CLASS_S15_PATH[9]='./res/recons/class_s15_r5/dfa_s15_r5_10/s15_r5.dfa'

#############################################################
# Run
#############################################################

#
# $1: Tool Path
# $2: Start State
# $3: End States
# $4: Log dir
#
run_optimizer(){
	echo "---------------------"
	echo "Starting Optimizer"
	echo "Tool Path: " $1
	echo "Start Q: " $2
	echo "End Q: " $3
	echo "DIR: " $4
	echo "---------------------"
	
	./optimizer -E 0 -A $1 \
		-q $2 -Q $3 \
		-I ${MAX_ITER} \
		--log-dir $4 \
		--log-main-dir ${MAIN_DIR_LOG} \
		-S ${SWARM_SIZE} \
		-W ${WORD_SET_PATH}
}

for i in `seq 0 ${CLASS_MAX}`;do
	run_optimizer ${CLASS_S4_PATH[$i]} ${START_Q} ${END_Q} ${D} "${DIR_LOG}_cl4_$i"
	run_optimizer ${CLASS_S6_PATH[$i]} ${START_Q} ${END_Q} ${D} "${DIR_LOG}_cl6_$i"
done
