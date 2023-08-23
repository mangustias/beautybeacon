

typedef unsigned char attrtype;
//  Ornament and ornament beacon are arrays of this type. In the experiments, only binary loci are used (maxattrvalues=2) but it can be increased  to maxattrvalues 256 or more if this type is changed.



typedef struct  {
	attrtype *attr;
	attrtype *ideal;	
	unsigned char strategy;
	_Bool alive;
} I;

/*
This structure descrybes each individual, male or demale.
attr is the ornament. ideal is the beacon ornament. The other variables are self-explanatory
*/




void printI( I *M1){
/*
Prints out an individual to STDOUT in the following format: 
attr: <list of elements in the ornament>
idea: <list of elements in the ornament beacon>
alive: <0/1>
strategy: <strategy>
*/

	int i;
		
	printf(" attr: ");
	for (i=0;i<numattrs;i++){


		printf("%i ,", M1->attr[i]);
	      }
	printf("\n ideal: ");
	for (i=0;i<numattrs;i++){
		printf("%i ,", M1->ideal[i]);
	      }

	printf("\n alive %d , ",M1->alive);
	printf("\n strategy %i \n",M1->strategy);
}


void fprintI( I *M1, FILE *f){
/*
Same as printI but prints to file f instead
*/

	int i;

	fprintf(f," attr: ");
	for (i=0;i<numattrs;i++){
		printf("%i , ", M1->attr[i]);
	      }
	fprintf(f,"\n ideal: ");
	for (i=0;i<numattrs;i++){
		printf("%i , ", M1->ideal[i]);
	      }

	fprintf(f,"\n alive %d , ",M1->alive);
	fprintf(f,"\n strategy %i \n",M1->strategy);

}

void fprintIconcise( I *M1, FILE *f){
/* prints an individual to file in a concise format. space-separated ornament array followed by beacon ornamnet array then strategy. The format:
a: <list of elements in the ornament>
i: <list of elements in the ornament beacon> <strategy>
*/

	int i;
	fprintf(f,"a:");
	for (i=0;i<numattrs;i++){
		fprintf(f,"%i ", M1->attr[i]);
	      }
	fprintf(f,"\ni:");
	for (i=0;i<numattrs;i++){
		fprintf(f,"%i ", M1->ideal[i]);
	      }
	fprintf(f,",%i  \n",M1->strategy);


}


void fprintIpopulation( I *M1, FILE *f, int i){
// prints the whole population to a file, in the concise format described in fprintIconcise. Individuals separated by a ===== line
 if (i>=0){fprintf(f,"\n%i ===============================\n",i);}
 for (i=0;i<popsize;i++){
 	fprintIconcise(&M1[i],f);
 }

}

int assignrestrategy(int NEstrat){
// assigns a random strategy skipping those that have cost 1
  int i,t=0,r=0;
  int s =rintunif(NEstrat);
  for (t=0; t<=s;t++){
  	while (strategycost[r]==1){r++;} r++;
   }
 return --r;
}

int numenabledstrategies(){
// calculates the number of strategies whose cost is <1
  int i,r=0;
  for (i=0;i<numstrategies;i++){ if(strategycost[i]<1) {r++;}}
  return r;
	}

 void makerandomI(I *a){
// makes an individual of type I with random ornament and beacon ornament, random strategy (skipping those whose cost is 1) and alive=1
        int i;
        a->alive=1;
        a->attr=malloc(sizeof(attrtype)*numattrs);
        a->ideal=malloc(sizeof(attrtype)*numattrs);
	for (i=0;i<numattrs;i++){
		a->attr[i]=rintunif(maxattrvalues); 
		a->ideal[i]=rintunif(maxattrvalues); 
		}
	a->strategy=assignrestrategy(numenabledstrategies());
}


void makezeromixI(I *a) {
// makes an individual of type I with random ornament, zero beacon ornament, randomly selected strategy (skipping those whose cost is 1) and alive=1
// not used in the experiments
        int i;
        a->alive=1;
        a->attr=malloc(sizeof(attrtype)*numattrs);
        a->ideal=malloc(sizeof(attrtype)*numattrs);
	for (i=0;i<numattrs;i++){
		a->attr[i]=rintunif(maxattrvalues); 
		a->ideal[i]=0; 
		}
	a->strategy=rintunif(numstrategies);

}


void makezeroI(I *a)
// makes an individual of type I with zero ornament, zero beacon ornament,  strategy=0  (random choice) and alive=1
  {
        int i;
        a->alive=1;
        a->attr=malloc(sizeof(attrtype)*numattrs);
        a->ideal=malloc(sizeof(attrtype)*numattrs);
	for (i=0;i<numattrs;i++){
		a->attr[i]=0; 
		a->ideal[i]=0; 
		}
	a->strategy=0;
  }




attrtype mutateattrinc(attrtype a){
// mutate and individual attribute incrimentally, either up or down
// not used in the experiments
	if (rand()>RAND_MAX/2) {
		if(a==maxattrvalues-1){a=0;} else a++;}
		 else  
		 	{if(a==0){a=maxattrvalues-1;}else a--;}
	
	return a;
}




attrtype mutateattruni(attrtype a){
// mutate and individual attribute uniformly at random
	return rintunif(maxattrvalues);
}



void randomizebeacon(attrtype *beac){
// makes a uniformly random beacon
 int i;

 for (i=0;i<numattrs;i++){
	beac[i]=rintunif(maxattrvalues);	
	}

}


void updatebeacon(attrtype *beac){
// updates beacon1changeattrs elements of a beacon with uniformly random numbers. Used in the first global beacon
 int i,j;
 for (j=0;j<beacon1changeattrs;j++){
	 i= rintunif(numattrs);
		beac[i]=rintunif(maxattrvalues);	
	}

}


double averageattr(attrtype *a){
// calculates the average of the elements of an array of size numattrs. Used to calculate the cost of male
 unsigned int i, suma=0;
 
 for (i=0;i<numattrs;i++){
	suma+=a[i];	
	}

  if ((maxattrvalues-1)) {
	  double r= (double)suma/((maxattrvalues-1)*numattrs);
	  return r;
	  }
   else {return 0;}
   
}


void killM(I *M){
// kills a male with probability calculated according to its ornament and   costattr: the probability is costattr* average beacon attribute

 if  (costattr) {
  	  double t=averageattr(M->attr);
	  if ( (double)(rand())/RAND_MAX<t*costattr )
  		{
		M->alive=0;
		  }

	}
}


void killF(I *F){
// kills a female with the probability  corresponding  to the cost of her strategy
 int i;
 float kill=(float)(rand())/RAND_MAX;
 
 for (i=0;i<numstrategies; i++){
  	 if  (F->strategy==i) {
	 	if (kill<strategycost[i]) 	 	
 		 {
			F->alive=0;
    
		  }
		 return; 
        }
    }

}


void decimatepopulation(I *A, unsigned char who){
// decimates a population of either males or females, as specified in the parameter who. If who=='M' then these are males, else these are females.
// In the case all of the population ends up killed, it resurrects them all (alive=1) spitting out "ALL DEAD!!!!!" to the standard output. 
// This would not happen with parameters used in the experiments, but may of course happen with small populations
 int i;
 unsigned char AllDead=1;
 typedef (*killfunction) (I *a); 
 killfunction	 killA;

 if (who=='M'){ killA=killM;}
 	else {killA=killF;}


 for (i=0;i<popsize;i++){
 	killA(&A[i]);
 }
 
 i=0; 
 while(i<popsize && AllDead){
	  if (A[i].alive){ AllDead=0;}
 		else {i++;}
  }
 
 if (AllDead) { 
 printf("ALL DEAD!!!!!!!!!!(resurrecting)\n");
 for (i=0;i<popsize;i++){
	A[i].alive=1;
	}
	
 }

}




void mutateI(I *A){
/*
Mutatation of an individual. Each attribute is mutated with probability indattrmutation 
either uniformly or incrementally, as per the symbol at ('u' or not). In the experiments, only at='u' is used.
In addition, the whole ornament is mutated with totalattrmutation (unused in the experiments)
Extra mutation is applied to beacon ornament attributes whose value is positive, with probability lopsidedmutation
The strategy is mutated with probability stratmutation
*/

	int i;
	typedef (*mutfunction) (int a); 
	mutfunction  mutat;
	
       	
	if(at=='u') {mutat=mutateattruni;} else 	{mutat=mutateattrinc;}


	
	for (i=0;i<numattrs;i++){
		if ((float)(rand())/RAND_MAX<indattrmutation){
			A->attr[i]=mutat(A->attr[i]); 
			 }

		if ((float)(rand())/RAND_MAX<indidealmutation){
			A->ideal[i]=mutat(A->ideal[i]); 
			 }

		}



	if ((float)(rand())/RAND_MAX<stratmutation){
		A->strategy=assignrestrategy(numenabledstrategies());
		}



	if (totalattrmutation) {

		if ((float)(rand())/RAND_MAX<totalattrmutation){

			for (i=0;i<numattrs;i++){
					A->attr[i]=rintunif(maxattrvalues); 
					A->ideal[i]=rintunif(maxattrvalues); 

		}


		}
	}


	if (lopsidedmutation){
		if (A->attr[0]>0 && (float)(rand())/RAND_MAX<lopsidedmutation){
			A->attr[0]=0;
			}
		} 

}


 void makeI( I *M,  I *F, I *Inew){
/*
This is breeding. M and F are parents, and Inew is child. Each of the ornament, beacon ornament, and strategy is inherited with probability 
1/2 from either of the parents. Ornament and beacon ornament arrays are inherited in full from the same parent.
Mutation is applied after breeding.
Alive =1 in the child
*/
	int i;
	Inew->alive=1;

        if (rand()>RAND_MAX/2)
            {	
		for (i=0;i<numattrs;i++){
			Inew->attr[i]=M->attr[i]; }
		}
		else {
		for (i=0;i<numattrs;i++){
			Inew->attr[i]=F->attr[i]; }
		}

        if (rand()>RAND_MAX/2)
            {	
		for (i=0;i<numattrs;i++){
			Inew->ideal[i]=M->ideal[i]; }
		}
		else {
		for (i=0;i<numattrs;i++){
			Inew->ideal[i]=F->ideal[i]; }
		}



        if (rand()>RAND_MAX/2) {	
		Inew->strategy=F->strategy;
		}
	else{
		Inew->strategy=M->strategy;
		}

	mutateI(Inew);
}










void getaverageideal(I *M,  float *averageideal, int size, int *index){
// Calculates the avearage ideal (beacon ornament) over a batch of males. The batch is supplied in the index array, which is of size size.
// The array is of indices in the population M. If index is NULL then all of M is used; in this case size must be popsize
	int i,j; 
	long long int  sumideal[numattrs];

	for (i=0;i<numattrs;i++){ sumideal[i]=0;}

	if (index==NULL){index=indexpop;} //indexpop is the dummy array 1..popsize



	for (i=0;i<size;i++){
			        if (lowDEBUG){printf("i %i index %i \n",i, index[i]);
			        printI(&M[index[i]]);
			        }

		for (j=0;j<numattrs;j++){
			        if (lowDEBUG){printf("xxxxx %i\n",j);			        }
			sumideal[j]+=M[index[i]].ideal[j]; 
			}
	}

	
	for (i=0;i<numattrs;i++){ 
	 averageideal[i]= (float) sumideal[i]/size;
	 }

}



void makebinarybeaconfromideals(I *A, attrtype *result, int size, int *ind){
// takes an array of individuals, calculates the average ornament beacon (ideal) and then makes a binary array of it
	int i;
	float averageideal[numattrs];	
	attrtype t[size];
	float middle= ((float)maxattrvalues-1)/2;

	getaverageideal (A, averageideal, size, ind);


	
	for (i=0;i<numattrs;i++){
		if ( (averageideal[i]>middle) || (  (averageideal[i]==middle) && (rand()>RAND_MAX/2)  )   ) {
			t[i]=maxattrvalues-1;
			} 
		else {t[i]=0;}
	}
	for (i=0;i<numattrs;i++){result[i]=t[i];}

}


float indfpreference(I *F, I *M,  attrtype *binaryaveragebeac, attrtype *globalbeac, attrtype *globalbeac2, attrtype *localbeacon, float *floataveragebeacon, float *floatlocalbeacon){
// calculates the individual preference of a female F for a male M. Takes as input all beacons: the two global beacons, and the female-estimated beacons, which can be used by the female or not
// if the resulting preference is less than minpref then return minpref


  float indpref=0; 
    

	switch (F->strategy)  // calculate the preference based on the  strategy of F
/*
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
	{
  	  case 0:  //random choice
  	  	indpref=1; 
  	  break;

  	  case 1: //floataveragebeacon
		indpref=1-l1distancef(floataveragebeacon,M->attr,numattrs,maxattrvalues);
	
  	  break;

  	  case 2: // own ideal

		indpref=1-l1distance(F->ideal,M->attr,numattrs,maxattrvalues);
  	  break;

  	  case 3: //globalbeacon

		indpref=1-l1distance(globalbeac,M->attr,numattrs,maxattrvalues);
		   if (lowDEBUG){ int i;
			   for (i=0;i<numattrs;i++) {
			   	printf("glbeac [%i]= %i ",i,globalbeac[i]);
			   	}
			   printf("ldist %f \n",l1distance(globalbeac,M->attr,numattrs,maxattrvalues)); 
			}

  	  break;

  	  case 4: //averagebinbeacon
		indpref=1-l1distance(binaryaveragebeac,M->attr,numattrs,maxattrvalues);
  	  break;

  	  case 5: // UNUSED 
		indpref =1;
  	  break;

  	  case 6: //globalbeacon2

		indpref=1-l1distance(globalbeac2,M->attr,numattrs,maxattrvalues);
  	  break;

  	  case 7: //localbeacon

		indpref=1-l1distance(localbeacon,M->attr,numattrs,maxattrvalues);
  	  break;

  	  case 8: //localfloatbeacon

		indpref=1-l1distancef(floatlocalbeacon,M->attr,numattrs,maxattrvalues);
  	  break;


	}

  if (basepref)  {indpref = (basepref+indpref)/2;} //unused
  if (indpref<minpref){indpref=minpref;} 

  return indpref;
}




void getrlivebatch(I *a, int *batchind, int batchsize, int psize){
// get a random batch of live individuals (males), either to select from or to calculate an average beacon ornament (ideal)
// a is the population array. The result is an array of indeces in this array.
// psize is the size of a (normally the population size)
	int i;

	for (i=0;i<batchsize;i++){

          do { batchind[i]=rintunif(psize); }
	  	while (a[batchind[i]].alive==0);

	}
}



int selectMaxMfromrandbatch(I *F, int findex,  I *M, int psize, int bsize,  attrtype *binaryaveragebeac, attrtype *globalbeac, attrtype *globalbeac2, float *floataveragebeacon){
// select a male from a batch according to the preferences of the female. F is the female, M is the male population from which a batch is to be selected. Pointers to all possible beacons are passed

  float evaluations[bsize];
  int ind[bsize];
  int i,max=0;

  int index[beaconbatchsize];
  
  attrtype localbeacon[numattrs];
  float floatlocalbeacon[numattrs];

    if (F->strategy==7){ //female-estimated binary beacon. get a batch for estimating a beacon and make a binary beacon

	  getrlivebatch(M,index,beaconbatchsize,psize);
	  makebinarybeaconfromideals(M,localbeacon,beaconbatchsize,index);
  }  

    if (F->strategy==8){ //female-estimated  beacon. get a batch  for estimating a beacon and make a beacon

	  getrlivebatch(M,index,beaconbatchsize,psize);
	  getaverageideal(M,floatlocalbeacon,beaconbatchsize,index);
  }  
 
 
  
 	  getrlivebatch(M,ind,bsize,psize); 
  //get a random batch of males to select from (not the same batch as for estimating a beacon)

  for (i=0;i<bsize;i++){

  //evaluate each male in the batch

  	evaluations[i]=indfpreference(F,&M[ind[i]],binaryaveragebeac, globalbeac, globalbeac2,localbeacon,floataveragebeacon,floatlocalbeacon);
   if (lowDEBUG){ printf("i %i ev %f",i,evaluations[i]);  }
  	}

   
  for (i=1;i<bsize;i++){     
 //find the maximum
     if (evaluations[i]>evaluations[max]) {max=i;}
   
  }

   if (lowDEBUG){  printf("\n>>>>>>>>inds "); for (i=0;i<bsize;i++){printf("%i, ",ind[i]);     }	printf("\n");
    }
   if (lowDEBUG){  printf("\nbatch: "); for (i=0;i<bsize;i++){printf("%i, ",ind[i]);    printI(&M[ind[i]]); printf("\n");  }	printf("\n");
    }

   if (lowDEBUG){  printf("evs "); for (i=0;i<bsize;i++){printf("%f, ",evaluations[i]);}	printf("\n"); }

  if (lowDEBUG){  printf("selected %i\n",ind[max]);}

  return ind[max];
  //return the index of the male with the maximum score

} 





void getaverageattrs(I *M, float *averageattr, int size){
// one of the functions for calculating the stats to ouput. This  one calcualtes the avearge attribute over a population M
// the output averageattr is an array of averages of size numattrs, each one corresponding to the average value of this locus over the population
	int i,j; 
	long long int  sumattr[numattrs];

	for (i=0;i<numattrs;i++){ sumattr[i]=0;}


	for (i=0;i<size;i++){

		for (j=0;j<numattrs;j++){
			sumattr[j]+=M[i].attr[j];
			}

	}
	
	for (i=0;i<numattrs;i++){ averageattr[i]= (float) sumattr[i]/size;}
	


}




void getaveragestrat(I *M,  float *averagestrat, int size){
// one of the functions for calculating the stats to ouput. This  one calcualtes the avearge strategy over a population M
// the output averagestrat is an array of averages of size numstrategies, each one corresponding to the percentage of females with this strategy in the population
	int i,j; 
	long long int  sumstrategy[numstrategies];

	for (i=0;i<numstrategies;i++){sumstrategy[i]=0;}

	for (i=0;i<size;i++){
		sumstrategy[M[i].strategy]++;	
		}
		
	for (i=0;i<numstrategies;i++){	
		averagestrat[i]= (float) sumstrategy[i]/ (float)size;
		}

}

void updatesumstrat (I *M,  long double *sumstrat, int size){
// update teh averages of strategies. This is used over a series of independent trials, to obtain an average over the series
  float averagestrat[numstrategies];
  int i;
  getaveragestrat (M, averagestrat, size);
    for (i=0; i< numstrategies; i++) {
    	sumstrat[i]+=averagestrat[i];

   }
   
}




void getaverages(I *M, float *averageattr, float *averageideal, float *averagestrat, int size){
	getaverageattrs (M, averageattr,size);
	getaverageideal (M, averageideal,size,NULL);
	getaveragestrat (M, averagestrat,size);
}






void fprintpopattrsentr (I *M, FILE *f){
	//print averages to files
	//print format: everages over population of:
	// each attribute; each strategy;  

	int i;
	float averagestr[numstrategies];
	float averageattr[numattrs], averageideal[numattrs];
	long double averagea, maxval, entrattr, entrideal, entrstrat=0, averagel1dist;


	getaverages(M, averageattr, averageideal, averagestr,popsize);

	for (i=0;i<numattrs;i++){	
		fprintf(f,"%f ",averageattr[i]);
		}
	for (i=0;i<numattrs;i++){	
		fprintf(f,"%f ",averageideal[i]);
		}


	for (i=0;i<numstrategies;i++){	
		fprintf(f,"%f ",averagestr[i]);
		}

	fprintf(f," \n");
		
}


void runtrials(FILE *fmout, FILE *fmout2, FILE *fmout3, long double *sumsumstrat, long double *sderr){
// this is the main function where everything happens.

  I *Fcur, *Mcur, *Fnext, *Mnext,  *Itemp;

  attrtype binaryaveragebeacon[numattrs], globalbeacon[numattrs], globalbeacon2[numattrs];
  // the global beacons used of the type attrtype
  
  float floataveragebeacon[numattrs]; //here the female-estiamted beacon is stored
  float averages[numstrategies];
  long double averagea,mina,maxa,avst;

  long double sumstrat[numstrategies], sumstratarray[numrepetitions][numstrategies];
  unsigned char reproduced;
  
  int i,j,k,m,l,n,NumRuns,count2,NewGenCount, FemsCount, fid,mid,selection,replaceid, inumreps=0;


   for (i=0; i< numrepetitions; i++) { 
//initialize  strategy stats for the series
	  for (j=0; j< numstrategies; j++) { 
 	  	sumstratarray[i][j]=0;
		  }
	  }
    

  do {  // while inumreps<numrepetitions;inumreps++
//run numrepetitions independent trials
	   

// initialization of the trial starts

// get memory for population. Mcur and Fcur are the current population that reproduces. Mnext and Fnext are the next population, where the offspring are stored
	   Mcur = malloc(popsize*(sizeof(I)+1));
	   Fcur = malloc(popsize*(sizeof(I)+1));

	   Mnext = malloc(popsize*(sizeof(I)+1));
	   Fnext = malloc(popsize*(sizeof(I)+1));



	  for (i=0;i<numattrs;i++){
// initialize beacons
       		 binaryaveragebeacon[i]=0;
	  	globalbeacon[i]=0;
	  	globalbeacon2[i]=0;
	  	floataveragebeacon[i]=0;
	   }

//initialize stats for the trial
	  for (i=0; i< numstrategies; i++) { 
	  	sumstrat[i]=0; sderr[i]=0; 
	  		  	
	  	}

 
	  for (i=0; i< popsize; i++) {
// initilize the current population according to the initialization specified
		switch ( initialpopulation) {
		 	case 'A': // random initialization
			   makerandomI(&Mcur[i]); 
		   	   makerandomI(&Fcur[i]); 
				
		 	break;		
		 	case 'Z': // zero initialization
			   makezeroI(&Mcur[i]); 
		   	   makezeroI(&Fcur[i]); 
				
		 	break;		
		 	case 'I': // mixed (unused)
   		        	makezeromixI(&Mcur[i]); 
		  	      makezeromixI(&Fcur[i]); 
				
		 	break;					
		
		
		}

// initialize the next population with 0s
	    makezeroI(&Mnext[i]); 
	    makezeroI(&Fnext[i]); 
	 }	

// initialization of the trial finished




	for (NumRuns=0;NumRuns<runlength+1;NumRuns++){ 	
//run the trial


	  if (lowDEBUG){
		printf(">>debug population snapshot Run%i >>\n",NumRuns);
		for (k=0;k <popsize;k++){
			printf("M %i \n",k);	
			printI(&Mcur[k]);
			printf("F %i \n",k);
			printI(&Fcur[k]);
			}
		}



	 if (!(NumRuns % beaconchangestep)) {
//update the global beacon 1, as well as the binaryaveragebeacon
		updatebeacon(globalbeacon);

		getaverageideal (Mcur, floataveragebeacon, popsize, NULL);
		makebinarybeaconfromideals(Mcur,binaryaveragebeacon, popsize, NULL);
		}

	
	 if (!(NumRuns % beacon2changestep)) {
//update the second global beacon.	
		randomizebeacon(globalbeacon2);
	
		}


	 if ( (NumRuns>0)&& !(NumRuns % snapshotstep)) {
//make snapshot of the stats
	       if (lowDEBUG){printf("snapshot %i\n",(NumRuns+1)/snapshotstep);}

	 	fprintpopattrsentr(Mcur,fmout);
 	
	 	updatesumstrat(Fcur,sumstrat,popsize);


	         for (i=0; i< numstrategies; i++) {
	         	avst=sumstrat[i]/(((float)NumRuns+1)/snapshotstep);
	         	sumsumstrat[i]+=avst;
			sumstratarray[inumreps][i]=avst;

			printf("%Lf ",avst );
		}
 	
		if (!numrepetitions) { printf(">>>generation %i\n",NumRuns); } 
			else { printf("\n");}

	
	 	}
 
	 if (populationsnapshotstep) {if (!(NumRuns % populationsnapshotstep)) {	
// population dumps
		         if (lowDEBUG){printf("SNAPSHOT DETOUR populationsnapshotstep %i\n",NumRuns/populationsnapshotstep);}

		 	fprintIpopulation(Mcur,fmout2,NumRuns);
	 		fprintIpopulation(Fcur,fmout3,NumRuns);

		}}


	        if (lowDEBUG){printf(">>>>> averagea %Lf\n",averagea);}

		if (NumRuns>=deferreddecimation){
// decimate the current population, unless deferred decimation is applied 
			decimatepopulation(Mcur,'M');
			decimatepopulation(Fcur,'F');
		}


		NewGenCount=0; 
// start counting how many offspring we made

		while (NewGenCount<popsize){
// we'll need popsize offspring male-female pairs
		        if (lowDEBUG){printf("--run %i NewGencount %i\n",NumRuns, NewGenCount);}
	
			fid=rintunif(popsize); //select a random female from the population, to reproduce her
			while(Fcur[fid].alive==0) //she should be alive. 
				{fid=rintunif(popsize);}

		        if (lowDEBUG){printf("Selected F %i\n",fid);
		        	printI(&Fcur[fid]);
			        }
		
			mid=selectMaxMfromrandbatch(&Fcur[fid], fid, Mcur,  popsize, batchsize,  binaryaveragebeacon, globalbeacon, globalbeacon2, floataveragebeacon);
			// select a male from the population according to this female's preferences			
	
	
			makeI(&Mcur[mid],&Fcur[fid],&Mnext[NewGenCount]);
			makeI(&Mcur[mid],&Fcur[fid],&Fnext[NewGenCount]);
		//	reproduce the selected couple

					        if (lowDEBUG){
							printf("Reproduced: parents\n");
							printf("M %i \n",mid);	
							printI(&Mcur[mid]);
							printf("F %i \n",fid);
							printI(&Fcur[fid]);
							printf("Reproduced: children NewGenCount%i\n",NewGenCount);
							printf("M %i \n",NewGenCount);	
							printI(&Mnext[NewGenCount]);
							printf("F %i \n",NewGenCount);
							printI(&Fnext[NewGenCount]);
						}

		 	NewGenCount++; //update the count of the generation
	
		
        	  }
	
		Itemp=Mcur;
		Mcur=Mnext;
		Mnext=Itemp;
		Itemp=Fcur;
		Fcur=Fnext;
		Fnext=Itemp;
  // the next generation becomes the current generation. And the current generation becomes the memory block for the next generation. As the next generation is made a-new, there's no need to initialize the new generation- just keep the same memory block.
		}





	free(Mcur);
	free(Fcur);

	free(Mnext); 
	free(Fnext);
	 
 // free the memory before the next trial is run.
	 
	 
   } while (++inumreps<numrepetitions);

	if (numrepetitions){
// if we are running more than one trial (a series), then we need to update the stats for the series
		
	  for (i=0; i< numstrategies; i++) { //update strategy stats
	  	sumsumstrat[i]=sumsumstrat[i]/numrepetitions;
		}
	  	

	   for (i=0; i<  numstrategies ; i++) { 	//update standard error stats
		  for (j=0; j<numrepetitions ; j++) { 
		     sderr[i]+=	(sumstratarray[j][i]-sumsumstrat[i])*(sumstratarray[j][i]-sumsumstrat[i]);
		  }
	  	sderr[i] = sqrt ( (sderr[i]/((float)numrepetitions-1))  )/(sqrt((float)numrepetitions));
	  	}


    }

}

