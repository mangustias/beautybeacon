int rseed=1;


int lowDEBUG=0;




int popsize=1000;
//  1/2 of the population size. There will be this number of females and this number of males in the population.
//  Can be configured as a command-line option --PopulationSize

int *indexpop;

int runlength=5000;
// The number of generations in each trial run
//  Can be configured as a command-line option --RunLength


int numrepetitions =0;
//  The number of independent runs to do with the same parameter values. If 0 then just one run is used. If positive then the average values over the runs
//  are recorded in the "averages" file. 
//   Can be configured as a command-line option --NumberRepetitions
// if non-zero then snapshotstep is set to runlength

int batchsize=20;
//   A parameter of all the choosy strategies: the size of the batch of males to select from.
//   Can be configured as a command-line option  --BatchSize


int beaconbatchsize=100;
//   A paramter for the female-estimated beacon. The batch of this size is used to construct the beacon estimate by each female.
//   Can be configured as a command-line option --BeaconBatchSize


int snapshotstep=10;

/* Every snapshotstep  generations, the population data is written to the file 'mout' and some data is written to STDOUT, 
 unless numrepetitions=0
 
These data are as follows:
 to mout: space-separated, followed by EOL
  for each ornament  locus, the average value of this locus over population
  for each beacon ornament  locus, the average value of this locus over population
  for each strategy, the number of females with this strategy devided by the total number of females.
 
 to STDOUT:
 for each strategy, the number of females with this strategy devided by the total number of females. Separated by space, followed by the 
  string >>>generation and the current generation number.
 
*/


# define populationsnapshotstep 0
/*  If positive, every populationsnapshotstep the whole male population is dumped into the file mout2 and the whole
female population is dumped into the file mout3
The format is as follows:
one line per indiviudal
 Each ornament attribute, followed by each each beacon ornament attribute, followed by the strategy
*/


int beaconchangestep=1;
//    The number of generations after which the first beacon changes
//   Can be configured as a command-line option  --BeaconChangeStep
// this one is also used to update binaryaveragebeacon

int beacon2changestep=50;
//    The number of generations after which the second beacon changes
//   Can be configured as a command-line option  --2BeaconChangeStep

int beacon1changeattrs=1;
//   The number of loci to change in the first beacon when it changes
//   Can be configured as a command-line option  --BeaconChangeAttrs




int numattrs=100;
//	The number of attrivutes (loci) in the ornament; the same value is used for the beacon ornament
//   Can be configured as a command-line option  --NumberOfAttributes

#define numstrategies 9
// The total number of female strategies. This include some strategies unused in the experiments. In each experiment, typically only 2 strategies
// are used. The rest have cost 1 and are excluded when generating new individuals


int maxattrvalues=2;
//	The maximum number of different values an attribute locus can take. In all the experiments reported in the paper this value is 2 (binary loci).
//   Can be configured as a command-line option  --MaxAttributeValues


# define  at 'u'
// This symbol is used to determine how mutation operates. 'u' means uniform and 'i' means increments. In all of the experiments, 
// only 'u' is used. 'i' may be used if maxattrvalues>2


char initialpopulation='A'; // A = random Z= all zero (including strategy: all set to random choice) I= Ideal set to 0, attribute and strategy random
/*   Can be configured with the following command line options:
	
--ZeroInitialPopulation  no argument. 
	Initiliaze the population with all 0s. This means the strategy locus is 0 (random strategy) and all ornaments/beacons are set to 0.

--RandomInitialPopulation  no argument. 
	Initiliaze the population uniformly at random.
	
--DeferredDecimation <integer>  default valie: 50
 		Initiliaze the population uniformly at random, and set the cost 0 until the generation specified. This is only applied to the strategy whose cost is not 0 and not 1, provided there is only one such strategy.

*/


float indattrmutation=0.01;
//   probability of mutation of each individual attribute (locus) in the ornament
//   Can be configured as a command-line option  --IndividualAttributeMutation


float indidealmutation=0.01;
//   probability of mutation of each individual attribute (locus) in the beacon ornament. 
// Can be configured as a command-line option --IdealAttributeMutation

float stratmutation=0.01;
//   probability of mutation of the strategy
// Can be configured as a command-line option  --StrategyMutation


float lopsidedmutation= 0;
//   Extra mutation applied to each ornament attribute whose value is 1 (transforming it to 0).
//  This is used in the baseline strategy with a single attribite locus in the ornament. 
// Can be configured as a command-line option --LopsidedMutation


int deferreddecimation=0;
// The number of generations to skip decemation for if DefferedDecimation initialization is used


# define totalattrmutation 0.0
// With this probability, the whole ornament array is mutated. Unused in the experiments.


#define minpref 0.01
// minimum preference for a male in a batch

#define basepref 0
// unused 



#define epsilon 0.01
#define startvalue 0.4
#define maxiterations 50
float targetvalue=0.85;
float step=0.2;

/*
There is a primitive procedure to  find an 'optimum' value of the cost that uses these 5 parameters.
If the simulation is run with numrepetitions>0 and with exactly one non-random strategy cost 0, with the rest of non-random strategy costs set to 1, 
then the simulator will try to find the highest cost for this strategy with which it persists above the threshold targetvalue. 
This is done by running numrepetitions runs starting with cost startvalue, with decreasing step (starting with the varialble step) until either maxiterations is reached or the difference between values tried is less than epsilon
*/



char averagesfilename[500]="averages";
/*
 the filename where to output averages over several simulation runs.
 This is only used in conjuction with NumberRepetitions option, in case the latter is non-zero, and in case there is one strategy whose cost is between 0 and 1 (but not 0 and not 1).

 Can be configured as a command-line option --AveragesFileName

*/


float costattr=0.01;
//   the cost applied to the males. The average value of the ornament is multiplied by this parameter to otbain the cost.
//  Can be configured as a command-line option --AttributeCost


//                random choice, floataveragebeacon,  own ideal, globalbeacon,binaryeveragebeacon,   unused,     globalbeacon2,   localbeacon,localfloatbeacon
float strategycost[] = {0,              1,                   1,           1,              1,              1,   		1,              1,          1    };
/* cost of each strategy
0  random choice
1  female-estimated beacon with the whole population of males used to estimate it; results in a global beacon (same for all females)
2  The beacon ornament of the female is used as a "beacon" she compares the males' ornament to. This results in the classic runaway process with biased mutation.
3  Global beacon 1. This uses the variable globalbeacon , updated according to beaconchangestep and beacon1changeattrs
4  same  as 1 but each attribute is thresholded to 0 or 1. This is not used in the reported experiments.
5  unused
6  Global beacon 2. This uses the variable globalbeacon2. This beacon changes completely every beacon2changestep steps.
7  Same as 8 but each attribute is thresholded to 0 or 1. This is not used in the reported experiments.
8  Female-estimated beacon. Each female uses a random batch of males size beaconbatchsize to construct her estimate of the beacon using their beacon ornaments
*/


# define  l1DEBUG 0
// making this positive triggers a lot of undocumented debug output

