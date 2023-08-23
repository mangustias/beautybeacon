# Beauty Beacon

This code was used in the experiments for the paper ``Beauty beacon: correlated strategies for the Fisher runaway proces.''

It provides a simulation model described in the paper

# Description
The program runs simulated  reproduction-mutation-decimation cycles for a population of fixed size consisting of an equal number of males and females.
Discrete generations are used, where on each generation the population is fully regenerated. Each breeding pair produces exactly one male and one female
offspring. Individuals are haploid, inheritance is with equal probability from each parent. Each individual consists of: strategy (char), and two arrays 
of chars which represent the ornament and the beacon ornament as described in the paper. Each array is inherited in its entirety from one of the parents.

## Female strategies

The female strategy can take a number of values whose meaning is as follows:
0  random choice
1  female-estimated beacon with the whole population of males used to estimate it; results in a global beacon (same for all females)
2  The beacon ornament of the female is used as a "beacon" she compares the males' ornament to. This results in the classic runaway process with biased mutation.
3  Global beacon 1. This uses the variable globalbeacon , updated according to beaconchangestep and beacon1changeattrs
4  same  as 1 but each attribute is thresholded to 0 or 1. This is not used in the reported experiments.
5  unused
6  Global beacon 2. This uses the variable globalbeacon2. This beacon changes completely every beacon2changestep steps.
7  Same as 8 but each attribute is thresholded to 0 or 1. This is not used in the reported experiments.
8  Female-estimated beacon. Each female uses a random batch of males size beaconbatchsize to construct her estimate of the beacon using their beacon ornaments

The global beacons are realized as global arrays of variables of the same size  and kind as the ornament.


## Modes of operation

The simulation has  3 modes of operation: 
 - run a single  trial, whose number of generations is specified in the variable runlength
 - run a series  trials (of the same length). The number of trials in the series is specified in numrepetitions
 - try to find the highest cost with which the target strategy survives (and dominates population) with the parameters provided. 
   This latter one is a crude optimization procedure. The length of each trial and of each series are specified in the same two variables.
   
 
 Which mode to operate in depends on the parameter numrepetitions and the cost of the strategies.
 If numrepetitions is 0 then the first mode is used.
 Otherwise, if the cost of every non-random (positive index) strategy is positive, then the second mode is used.
  Else, the third mode is used. 

## List of files 
bb.c 	 the main file to compile
I22.h  	contains most of the functions and code
constants.h  contains all of the parameters, both those that can be configured via command line and those that can not
auxfunctions.h contains some auxiliary functions
test23.c  contains some testing procedures (undocumented)


## Output
 The output depends on the mode of operation.
 In the first (single trial) mode, the average numbers of females with each strategy are output each snapshotstep generations. 
 In addition, the following is written to the file  mout: space-separated, followed by EOL
  for each ornament  locus, the average value of this locus over population
  for each beacon ornament  locus, the average value of this locus over population
  for each strategy, the number of females with this strategy devided by the total number of females.

  Furthermore, the whole population is dumped in two files, mout and fmout (for males and females) every populationsnapshotstep generations
  The format is as follows:
  one line per indiviudal
 Each ornament attribute, followed by each each beacon ornament attribute, followed by the strategy

  
 In the second and third modes, snapshotstep and the corresponding output  is disabled. The population dumps are as before.
 The trials statistics are output to STDOUT.
 
 In the second mode, the series stats are output in the file specified with the command line option --AveragesFileName. These stats are as follows:
 For each series, the average of the tested strategy at the end of the trial, followed by the standard error, followed by the number of trials in the series.
 
 

# Installation
The code can be compiled directly by running
	gcc bb.c -lm


# Running the simulation

## Example usage

./a.out --PopulationSize 1000 --BatchSize 20 --BeaconBatchSize 100 --NumberOfAttributes 100 --MaxAttributeValues 2 --IndividualAttributeMutation 0.01 --IdealAttributeMutation 0.01 --StrategyMutation 0.01 --BeaconChangeStep 1 --2BeaconChangeStep 50 --AttributeCost 0.01 --BeaconLookupCost 1  --InternalBeaconLookupCost 1 --LocalBeaconLookupCost 1  --2BeaconLookupCost 1 --OwnIdealCost 1 --LocalFloatBeaconLookupCost 1 --FloatBeaconLookupCost 0.31 --RandomSeed 16 --NumberRepetitions 50 --RunLength 5000 --DeferredDecimation 50 --AveragesFileName AveragesFile

The above runs the simulation with 50 trials, the stats written into the file AveragesFile. The costs of all non-random strategies are set to except 
for female-estimated beacon which is set to 0.31. 


./a.out --PopulationSize 1000 --BatchSize 20 --BeaconBatchSize 100 --NumberOfAttributes 100 --MaxAttributeValues 2 --IndividualAttributeMutation 0.01 --IdealAttributeMutation 0.01 --StrategyMutation 0.01 --BeaconChangeStep 1 --2BeaconChangeStep 50 --AttributeCost 0.01 --BeaconLookupCost 0.1  --InternalBeaconLookupCost 1 --LocalBeaconLookupCost 1  --2BeaconLookupCost 1 --OwnIdealCost 1 --LocalFloatBeaconLookupCost 1 --FloatBeaconLookupCost 1 --RandomSeed 16 --NumberRepetitions 0

The above is the same but only one simulation is run, and the only enabled strategy (with cost less than 1) is the first global beacon (with cost 0.1)

## Enabling the different modes of operation

The first mode, single trial, is enabled by specifying --NumberRepetitions 0

The third mode, optimization,  is enabled by setting the latter option non-0 and specifying the cost of exactly one non-random strategy as 0 and the rest of strategies as 1.
For example, the following set of options enables optimization on the first global beacon strategy, with series of trials of length 50 each: 
 --BeaconLookupCost 0  --InternalBeaconLookupCost 1 --LocalBeaconLookupCost 1  --2BeaconLookupCost 1 --OwnIdealCost 1 --LocalFloatBeaconLookupCost 1 --FloatBeaconLookupCost 1 --NumberRepetitions 50

If neither the first nor the third modes are enabled then the second mode (single series of length NumberRepetitions) is used.

## Command line options
The following are the command-line options:

--AveragesFileName <string>  default value: "averages"
 the filename where to output averages over several simulation runs.
 This is only used in conjunction with NumberRepetitions option, in case the latter is non-zero, and in case there is one strategy whose cost is between 0 and 1 (but not 0 and not 1).
 The averages are output in the following format:
 A B C 
 wher A is the cost of the strategy, B is the average, and C is the standard error
 
--PopulationSize <interger>  default value: 1000
  1/2 of the population size. There will be this number of females and this number of males in the population.
  
--BatchSize <interger>  default value: 20
  A parameter of all the choosy strategies: the size of the batch of males to select from.
  
-- BeaconBatchSize <interger>  default value: 100
  A parameter for the female-estimated beacon. The batch of this size is used to construct the beacon estimate by each female.
  
--NumberOfAttributes <interger>  default value: 100
	The number of attributes (loci) in the ornament; the same value is used for the beacon ornament
	
--MaxAttributeValues <interger>  default value: 2 
	The maximum number of different values an attribute locus can take. In all the experiments reported in the paper this value is 2 (binary loci).
	
--IndividualAttributeMutation <float>  default value: 0.01
  probability of mutation of each individual attribute (locus) in the ornament
  
--StrategyMutation <float>  default value: 0.01
  probability of mutation of the strategy

--IdealAttributeMutation <float>  default value: 0.01
  probability of mutation of each individual attribute (locus) in the beacon ornament. 
  In the reported  experiments this is the same as IndividualAttributeMutation
  
--LopsidedMutation <float>  default value: 0
  Extra mutation applied to each ornament attribute whose value is 1 (transforming it to 0).
  This is used in the baseline strategy with a single attribute locus in the ornament. 


--BeaconChangeStep  <interger>  default value: 1
   The number of generations after which the first beacon changes
   
--BeaconChangeAttrs  <interger>  default value: 1
  The number of loci to change in the first beacon when it changes
  
--2BeaconChangeStep  <interger>  default value: 50
   The number of generations after which the second beacon changes
 
--AttributeCost <float>  default value: 0.01
  the cost applied to the males. The average value of the ornament is multiplied by this parameter to obtain the cost.
  
--RandomSeed <integer>  default value: 1
   Random seed initialization 
   
--RunLength <integer>  default value: 5000
 The number of generations in each trial run
 
--NumberRepetitions <integer>  default value: 0
  The number of independent runs to do with the same parameter values. If 0 then just one run is used. If positive then the average values over the runs
  are recorded in the "averages" file. (See --AveragesFileName )
  
--BeaconLookupCost <float>  default value: 1
	The cost of the beacon strategy that uses the first beacon

--2BeaconLookupCost  <float>  default value: 1
	The cost of the beacon strategy that uses the second beacon
	
--InternalBeaconLookupCost <float>  default value: 1
	The cost of the beacon strategy that uses female-estimated beacon, estimated over the whole population and then made binary using a simple threshold.
	This strategy is not used in the experiments reported in the paper.

--LocalBeaconLookupCost <float>  default value: 1
	The cost of the beacon strategy that uses female-estimated beacon, estimated over a random batch and then made binary using a simple threshold.
	This strategy is not used in the experiments reported in the paper.
	
--LocalFloatBeaconLookupCost <float>  default value: 1
	The cost of the beacon strategy that uses female-estimated beacon, estimated over a random batch.
	
--FloatBeaconLookupCost <float>  default value: 1
	The cost of the beacon strategy that uses female-estimated beacon, estimated over the whole population.
	
--OwnIdealCost  <float>  default value: 1
	The cost of the "simple runaway" strategy, where each female uses its own beacon (stored in the beacon ornament) to match the ornament of the males.
	This strategy is used as the baseline strategy with lopsided mutation and 1 attribute in the ornament.
	
--ZeroInitialPopulation  no argument. 
	Initiliaze the population with all 0s. This means the strategy locus is 0 (random strategy) and all ornaments/beacons are set to 0.

--RandomInitialPopulation  no argument. 
	Initiliaze the population uniformly at random.
	
--DeferredDecimation <integer>  default value: 50
 		Initiliaze the population uniformly at random, and set the cost 0 until the generation specified. This is only applied to the strategy whose cost is not 0 and not 1, provided there is only one such strategy.

--ZeroIdealRandomInitialPopulation no argument. 
	Initialize the population uniformly at random, except for the beacon ornament that is uniformly 0.
	This initialization is not used in the experiments reported in the paper.

