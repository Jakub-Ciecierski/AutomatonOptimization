#!/bin/bash

MAIN_DIR_LOG="./logs/APPROX_C5"

DIR_LOG="APPROX_C5"

#############################################################
# Settings
#############################################################

MAX_ITER=100
SWARM_SIZE=50

PSO_STATES_LENGTH=5
PSO_STATES=(4 6 8 10 12)

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

CLASS_S20_PATH[0]='./res/approx/class_s20_r5/dfa_s20_r5_1/s20_r5.dfa'
CLASS_S20_PATH[1]='./res/approx/class_s20_r5/dfa_s20_r5_2/s20_r5.dfa'
CLASS_S20_PATH[2]='./res/approx/class_s20_r5/dfa_s20_r5_3/s20_r5.dfa'
CLASS_S20_PATH[3]='./res/approx/class_s20_r5/dfa_s20_r5_4/s20_r5.dfa'
CLASS_S20_PATH[4]='./res/approx/class_s20_r5/dfa_s20_r5_5/s20_r5.dfa'
CLASS_S20_PATH[5]='./res/approx/class_s20_r5/dfa_s20_r5_6/s20_r5.dfa'
CLASS_S20_PATH[6]='./res/approx/class_s20_r5/dfa_s20_r5_7/s20_r5.dfa'
CLASS_S20_PATH[7]='./res/approx/class_s20_r5/dfa_s20_r5_8/s20_r5.dfa'
CLASS_S20_PATH[8]='./res/approx/class_s20_r5/dfa_s20_r5_9/s20_r5.dfa'
CLASS_S20_PATH[9]='./res/approx/class_s20_r5/dfa_s20_r5_10/s20_r5.dfa'

CLASS_S30_PATH[0]='./res/approx/class_s30_r5/dfa_s30_r5_1/s30_r5.dfa'
CLASS_S30_PATH[1]='./res/approx/class_s30_r5/dfa_s30_r5_2/s30_r5.dfa'
CLASS_S30_PATH[2]='./res/approx/class_s30_r5/dfa_s30_r5_3/s30_r5.dfa'
CLASS_S30_PATH[3]='./res/approx/class_s30_r5/dfa_s30_r5_4/s30_r5.dfa'
CLASS_S30_PATH[4]='./res/approx/class_s30_r5/dfa_s30_r5_5/s30_r5.dfa'
CLASS_S30_PATH[5]='./res/approx/class_s30_r5/dfa_s30_r5_6/s30_r5.dfa'
CLASS_S30_PATH[6]='./res/approx/class_s30_r5/dfa_s30_r5_7/s30_r5.dfa'
CLASS_S30_PATH[7]='./res/approx/class_s30_r5/dfa_s30_r5_8/s30_r5.dfa'
CLASS_S30_PATH[8]='./res/approx/class_s30_r5/dfa_s30_r5_9/s30_r5.dfa'
CLASS_S30_PATH[9]='./res/approx/class_s30_r5/dfa_s30_r5_10/s30_r5.dfa'

CLASS_S50_PATH[0]='./res/approx/class_s50_r5/dfa_s50_r5_1/s50_r5.dfa'
CLASS_S50_PATH[1]='./res/approx/class_s50_r5/dfa_s50_r5_2/s50_r5.dfa'
CLASS_S50_PATH[2]='./res/approx/class_s50_r5/dfa_s50_r5_3/s50_r5.dfa'
CLASS_S50_PATH[3]='./res/approx/class_s50_r5/dfa_s50_r5_4/s50_r5.dfa'
CLASS_S50_PATH[4]='./res/approx/class_s50_r5/dfa_s50_r5_5/s50_r5.dfa'
CLASS_S50_PATH[5]='./res/approx/class_s50_r5/dfa_s50_r5_6/s50_r5.dfa'
CLASS_S50_PATH[6]='./res/approx/class_s50_r5/dfa_s50_r5_7/s50_r5.dfa'
CLASS_S50_PATH[7]='./res/approx/class_s50_r5/dfa_s50_r5_8/s50_r5.dfa'
CLASS_S50_PATH[8]='./res/approx/class_s50_r5/dfa_s50_r5_9/s50_r5.dfa'
CLASS_S50_PATH[9]='./res/approx/class_s50_r5/dfa_s50_r5_10/s50_r5.dfa'

CLASS_S80_PATH[0]='./res/approx/class_s80_r5/dfa_s80_r5_1/s80_r5.dfa'
CLASS_S80_PATH[1]='./res/approx/class_s80_r5/dfa_s80_r5_2/s80_r5.dfa'
CLASS_S80_PATH[2]='./res/approx/class_s80_r5/dfa_s80_r5_3/s80_r5.dfa'
CLASS_S80_PATH[3]='./res/approx/class_s80_r5/dfa_s80_r5_4/s80_r5.dfa'
CLASS_S80_PATH[4]='./res/approx/class_s80_r5/dfa_s80_r5_5/s80_r5.dfa'
CLASS_S80_PATH[5]='./res/approx/class_s80_r5/dfa_s80_r5_6/s80_r5.dfa'
CLASS_S80_PATH[6]='./res/approx/class_s80_r5/dfa_s80_r5_7/s80_r5.dfa'
CLASS_S80_PATH[7]='./res/approx/class_s80_r5/dfa_s80_r5_8/s80_r5.dfa'
CLASS_S80_PATH[8]='./res/approx/class_s80_r5/dfa_s80_r5_9/s80_r5.dfa'
CLASS_S80_PATH[9]='./res/approx/class_s80_r5/dfa_s80_r5_10/s80_r5.dfa'

#############################################################
# Run
#############################################################

#
# $1: Tool Path
# $2: States
# $3: Log dir
#
run_optimizer(){
	echo "---------------------"
	echo "Starting Optimizer"
	echo "Tool Path: " $1
	echo "States: " $2
	echo "Log Dir: " $3
	echo "---------------------"
	
	./optimizer -E 0 -A $1 \
		-q $2 -Q $2 \
		--log-dir $3 \
		--log-main-dir ${MAIN_DIR_LOG} \
		-W ${WORD_SET_PATH} \
		-S ${SWARM_SIZE} \
		-I ${MAX_ITER}
}

for i in `seq 0 ${CLASS_MAX}`;do
	for s in `seq 0 ${STATE_MAX}`;do
		run_optimizer ${CLASS_S20_PATH[$i]} ${PSO_STATES[$s]} "${DIR_LOG}_cl20_s${PSO_STATES[$s]}_$i"
		run_optimizer ${CLASS_S30_PATH[$i]} ${PSO_STATES[$s]} "${DIR_LOG}_cl30_s${PSO_STATES[$s]}_$i"
	done
done

