# include <stdio.h>
# include <ctype.h>
# include <fcntl.h> 
# include <sys/stat.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <unistd.h>
# include <getopt.h>

# include "constants22.h"
# include "auxfunctions.h"
# include "I22.h"



void processinput(int argc, char *argv[]){
//  process command-line options. See README for  description of options

int opt;



 struct option longopts[] = { 
        { "AveragesFileName", required_argument, NULL, 'e' },
        { "PopulationSize", required_argument, NULL, 'p' },
        { "SnapshotStep", required_argument, NULL, 'P' },
        { "BatchSize", required_argument, NULL, 'b' },
        { "BeaconBatchSize", required_argument, NULL, 'B' },
        { "NumberOfAttributes", required_argument, NULL, 'a' },
        { "MaxAttributeValues", required_argument, NULL, 'v' },
        { "IndividualAttributeMutation", required_argument, NULL, 'm' },
        { "StrategyMutation", required_argument, NULL, 'q' },
        { "IdealAttributeMutation", required_argument, NULL, 'x' },
        { "LopsidedMutation", required_argument, NULL, 'y' },
        { "BeaconChangeStep", required_argument, NULL, 's' },
        { "BeaconChangeAttrs", required_argument, NULL, 'C' },
        { "2BeaconChangeStep", required_argument, NULL, 'S' },
        { "AttributeCost", required_argument, NULL, 'c' },
        { "RandomSeed", required_argument, NULL, 'r' },
        { "RunLength", required_argument, NULL, 'R' },
        { "NumberRepetitions", required_argument, NULL, 'N' },
        { "BeaconLookupCost", required_argument, NULL, 'l' },
        { "2BeaconLookupCost", required_argument, NULL, 'L' },
        { "InternalBeaconLookupCost", required_argument, NULL, 'o' },
        { "LocalBeaconLookupCost", required_argument, NULL, 'O' },
        { "LocalFloatBeaconLookupCost", required_argument, NULL, 'f' },
        { "FloatBeaconLookupCost", required_argument, NULL, 'F' },
        { "OwnIdealCost", required_argument, NULL, 'k' },
        { "ZeroInitialPopulation", no_argument, NULL, 'Z' },
        { "RandomInitialPopulation", no_argument, NULL, 'A' },
        { "DeferredDecimation", required_argument, NULL, 'D' },
        { "ZeroIdealRandomInitialPopulation", no_argument, NULL, 'I' },
        { 0 }
    };


  while((opt = getopt_long (argc, argv, "p:b:a:v:m:q:x:y:o:s:S:o:O:c:r:k:f:F:R:n:ZAID:e:C:P:", longopts, 0)) != -1) 
    { 
        switch(opt) 
        { 
            case 'p': 
                popsize= atoi(optarg);
                printf("PopulationSize: %i\n", popsize);
                break; 

            case 'P': 
                snapshotstep= atoi(optarg);
                printf("SnapshotStep: %i\n", snapshotstep);
                break; 

            case 'b': 
                batchsize= atoi(optarg);
                printf("BatchSize: %i\n", batchsize);
                break; 
            case 'B': 
                beaconbatchsize= atoi(optarg);
                printf("BeaconBatchSize: %i\n", beaconbatchsize);
                break; 
            case 'a': 
                numattrs= atoi(optarg);
                printf("NumberOfAttributes: %i\n", numattrs);
                break; 
            case 'v': 
                maxattrvalues= atoi(optarg);
                printf("MaxAttributeValues: %i\n", maxattrvalues);
                break; 
            case 'm': 
                indattrmutation= atof(optarg);
                printf("IndividualAttributeMutation: %f\n", indattrmutation);
                break; 
            case 'q': 
                stratmutation= atof(optarg);
                printf("StrategyMutation: %f\n", stratmutation);
                break; 
            case 'e': 
                strcpy(averagesfilename, optarg);
                printf("File name to output averages: %s\n", averagesfilename);
                break; 
            case 'x': 
                indidealmutation= atof(optarg);
                printf("IdealAttributeMutation: %f\n", indidealmutation);
                break; 
            case 'y': 
                lopsidedmutation= atof(optarg);
                printf("LopsidedMutation  (first arg): %f\n", lopsidedmutation);
                break; 
            case 's': 
                beaconchangestep= atoi(optarg);
                printf("BeaconChangeStep: %i\n", beaconchangestep);
                break; 
            case 'S': 
                beacon2changestep= atoi(optarg);
                printf("2BeaconChangeStep: %i\n", beacon2changestep);
                break; 
            case 'c': 
                costattr=atof(optarg);
                printf("AttributeCost: %f\n", costattr);
                break; 
            case 'r': 
                rseed= atoi(optarg);
                printf("RandomSeed: %i\n", rseed);
                break; 
            case 'R': 
                runlength= atoi(optarg);
                printf("RunLength: %i\n", runlength);
                break; 
            case 'C': 
                beacon1changeattrs= atoi(optarg);
                printf("Beacon1 number of attributes to chnage: %i\n", beacon1changeattrs);
                break; 
            case 'N': 
                numrepetitions= atoi(optarg);
                printf("NumberRepetitions: %i\n", numrepetitions);
                break; 
            case 'l': 
                strategycost[3]= atof(optarg); //Global independent incrementally updated (one attribute at a time) binary beacon; updated every %beaconchangestep
                printf("BeaconLookupCost: %f\n", strategycost[3]);
                break; 
            case 'L': 
                strategycost[6]= atof(optarg); //Global independent completely changed  (all  attributes at once) binary beacon; updated every %beacon2changestep
                printf("2BeaconLookupCost: %f\n", strategycost[6]);
                break; 
            case 'o': 
                strategycost[4]= atof(optarg); //Global binary  beacon based on the average of the "ideal" attributes of current Male population; updated every %beaconchangestep 
                printf("InternalBeaconLookupCost: %f\n", strategycost[4]);
                break; 
            case 'O': 
                strategycost[7]= atof(optarg); // Binary  beacon based on the average of SAMPLE of the "ideal" attributes of current Male population, sampled by each female 
                printf("LocalBeaconLookupCost: %f\n", strategycost[7]);
                break; 
            case 'f': 
                strategycost[8]= atof(optarg); // Float-point beacon based on the average of SAMPLE of the "ideal" attributes of current Male population, sampled by each female 
                printf("LocalFloatBeaconLookupCost: %f\n", strategycost[8]);
                break; 
            case 'F': 
                strategycost[1]= atof(optarg); //Global float-point  beacon based on the average of the "ideal" attributes of current Male population; updated every %beaconchangestep 
                printf("FloatBeaconLookupCost: %f\n", strategycost[1]);
                break; 
            case 'k': 
                strategycost[2]= atof(optarg); // Simple-Fisher strategy: comparing "ideal" attribute of the female with the potential mate
                printf("OwnIdealCost: %f\n", strategycost[2]);
                break; 
            case 'Z': 
                initialpopulation= 'Z';
                printf("Initial population set to all 0s, random choice (ignoring strategies with cost 1)\n");
                break; 
            case 'A': 
                initialpopulation= 'A';
                printf("Initial population uniformly random\n");
                break; 
            case 'I': 
                initialpopulation= 'I';
                printf("Initial population with 0 ideal,  uniformly random attributes and strategies (ignoring those with cost 1)\n");
                break; 
            case 'D': 
                initialpopulation= 'A';
                deferreddecimation= atoi(optarg);
                printf("Initial population random, deferred decimantion: %i\n", deferreddecimation);
                break; 


            case ':': 
                printf("option needs a value\n"); 
                break; 
            case '?': 
                printf("unknown option: %c\n", optopt);
                break; 
        } 
    } 

}


void main(int argc, char *argv[])  {
/*

The logic of the main is as follows. It has 3 modes of operation: 
 - run one trial of runlength generations
 - run numrepetitions trials (of the same length)
 - try to find the highest cost with which the target strategy survives (and dominates population) with the parameters provided. 
   This latter one is a crude optimization procedure. 
 
 Which mode to operate in depends on the parameter numrepetitions and the cost of the strategies.
 If numrepetitions is 0 then the first mode is used.
 Otherwise, if the cost of every non-random (positive index) strategy is positive, then the second mode is used.
  Else, the third mode is used. 
 
  snaptshotstep is only enabled in the first mode. 
  
  The optimization procedure in the third mode consists of running multiple series of trials. Each series is of size numrepetitions and each trial is of length runlength generations. 
  The procedure  tries to find the highest cost for this strategy with which it persists above the threshold targetvalue. 
This is done by running numrepetitions runs starting with cost startvalue, with decreasing step (starting with the varialble step) until either maxiterations is reached or the difference between values tried is less than epsilon

In all the cases, the actual (series of) trials is run via the function runtrials(..)

*/

 int i;

  processinput(argc, argv); //process command line options

  
 float val=startvalue; //used in optimization
int targetstrategy=0;
int iterations =0;

  long double sumsumstrat[numstrategies],      sderr[numstrategies]; // stats over several independent runs of simulations. Used with numrepetitions>0. These are average strategies and standard error of these

  
// initialization starts here 

  srand(rseed);  //initialize the random seet with the value provided in the command line

FILE *fmout; //averages written here every snapshotstep 
fmout = fopen("mout", "w");
FILE *fmout2; // M population dumped here every populationsnapshotstep
fmout2 = fopen("mout2", "w");
FILE *fmout3; //F  population dumped here every populationsnapshotstep
fmout3 = fopen("mout3", "w");
FILE *faverages=NULL; // averages over numrepetitions are written here; the file name is specified as a command line option in averagesfilename


  indexpop=malloc(popsize*(sizeof(int)));
    for (i=0;i<popsize;i++){indexpop[i]=i;}
// dummy index 0..popsize-1 for the whole population

 



int findtargetstr(){
// if there is only one non-random strategy (>0) whose cost is exactly 0, then this will be the target for a crude optimization of cost
	  int j, numfound=0, res=0;
  
  	for (j=1;j<numstrategies;j++){
	 	 if (strategycost[j]==0){numfound++; res=j;}
	   }
	
	  if (numfound==1) {return res;} else {return 0;}
	}


  for (i=0; i< numstrategies; i++) { sumsumstrat[i]=0; }
//initiliaze averages

  if (numrepetitions) { 
  //at least one series of trials of size numrepetitions  will be run with the same parameters. In this case snapshotstep is disabled
     	snapshotstep=runlength;

	  targetstrategy=findtargetstr();
	  if (targetstrategy){
 // if there is only one non-random strategy (>0) whose cost is exactly 0, then this will be the target for a crude optimization of cost
 // it starts with the cost == startvalue , then halves it and goes up or down according to whether the strategy was above or below targetvalue in the last series.
	      printf("Optimizing for strategy %i\n", targetstrategy);
		while (step >epsilon/2 && iterations<maxiterations) {

   		  	for (i=0; i< numstrategies; i++) { sumsumstrat[i]=0; } //initialize averages
	
			strategycost[targetstrategy]=val; //set the cost for the series of trials

			runtrials (fmout, fmout2, fmout3, sumsumstrat,sderr);  //this is where the trial series is run			

			printf("average strategies over trials, cost %f, iteration %i: av value  %Lf \n", strategycost[targetstrategy], iterations,sumsumstrat[targetstrategy]);
			if (sumsumstrat[targetstrategy]>targetvalue){  //set the cost for the next iteration
			    val+=step;
			 }	else {val-=step;}
			
			step=step/2; iterations++;
		
		}
	
	   }
	   else{ printf("Not optimizing\n"); //running a single series of numrepetitions trials
    runtrials (fmout, fmout2, fmout3, sumsumstrat,sderr); 
	   	} 
  } 
 
 
 else {  //running a single trial, not a series
 runtrials (fmout, fmout2, fmout3, sumsumstrat,sderr); 
   }
   
   // if the trials are repeated but not looking to optimize the cost of a strategy, write some averages
   if(numrepetitions && targetstrategy==0){
	

	 faverages=fopen(averagesfilename,"a"); //file for dumping averages
   
   	for (i=1;i<numstrategies;i++){ // find the  non-random strategy with cost <1; if there's more than one then the last one will be selected
   		if(strategycost[i] <1  ){targetstrategy=i;}
   		}
	printf("average strategies over trials:\n");
	 for (i=0;i<numstrategies;i++){
	   printf("%Lf ",sumsumstrat[i]);	
	 }
	printf("\n");
	printf("Standard error:\n");
	 for (i=0;i<numstrategies;i++){
	   printf("%Lf ",sderr[i]);	
	 }
	printf("\n");
	printf("Sample size %i:\n",numrepetitions);

	fprintf(faverages,"%f %Lf %Lf %i\n",strategycost[targetstrategy],sumsumstrat[targetstrategy],sderr[targetstrategy],numrepetitions);
	fclose(faverages);
  }
  
 



fclose(fmout);
fclose(fmout2);
fclose(fmout3);
//close all files we opened for dumps


}


