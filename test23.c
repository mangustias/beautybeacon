# include <ctype.h>
# include <fcntl.h> 
# include <sys/stat.h>
# include <stdlib.h>
#include <unistd.h>
# include <stdio.h>
# include <math.h>


# include "constants22.h"
# include "auxfunctions.h"
# include "I22.h"



void testrcharunif(){
 int i;
 for (i=0;i<50;i++){
	printf("\n %i ",rcharunif(-2,2));
	}

}


void testrintunif(){
 int i;
 for (i=0;i<50;i++){
	printf("\n %i ",rintunif(2));
	}

}


void testrfloatunif(){
 int i;
 for (i=0;i<50;i++){
	printf("\n %f ",rfloatunif(0,2));
	}

}

void testmutateattr(){
 int a=rcharunif(0,maxattrvalues); 
 printf("a= %i  \n",a);
}




void testmakerandomI(){
   I a;  
 makerandomI(&a); 
 printI(&a);
}


void testmakeI(){
   I M, F, Ch;
   
    makezeroI(&M); 
   makezeroI(&F); 
   makezeroI(&Ch); 
   
   makeI(&M,&F,&Ch); 

 printf("M: \n");
 printI(&M);
 printf("F: \n");
 printI(&F);
 printf("C: \n");
 printI(&Ch);


    makerandomI(&M); 
    makerandomI(&F); 
   makeI(&M,&F,&Ch); 

 printf("M: \n");
 printI(&M);
 printf("F: \n");
 printI(&F);
 printf("C: \n");
 printI(&Ch);

}

void testmutateI(){
  I A; 
   makezeroI(&A); 
 printf("----------------\n");
 printI(&A);
 mutateI(&A);
 printI(&A);
 mutateI(&A);
 printI(&A);
 mutateI(&A);
 printI(&A);
 mutateI(&A);
 printI(&A);
 mutateI(&A);
 printI(&A);
 mutateI(&A);
 printI(&A);
 mutateI(&A);
 printI(&A);
 mutateI(&A);
 printI(&A);
 mutateI(&A);
 printI(&A);
 mutateI(&A);
 printI(&A);
}



void testsame(){

 attrtype a[]={20,20,20};
 attrtype b[]={20,20,20};
 printf("%i \n", samechar(a,b,3));

}






void testindfpreference(int strategy){
 int i,j;
 I M, F;
 numattrs=1;
 attrtype  glbeac[numattrs], binarybeac[numattrs], localbeac[numattrs];
 float floatavbeac[numattrs];
  for (j=0;j<20;j++){
	 makerandomI(&M);
	 makerandomI(&F);
	 F.strategy = strategy;
	 printf("M: \n");
	 printI(&M);
	 printf("F: \n");
	 printI(&F);
	 randomizebeacon(glbeac);
	 printf("\nglbeac:"); 
	 
	 for (i=0;i<numattrs;i++){	
		 printf("%i ", glbeac[i]); 
	 }

	 printf("\nbinbeac:");  
	 for (i=0;i<numattrs;i++){	
		binarybeac[i]=rintunif(2);	
		 printf("%i ", binarybeac[i]); 
	}
	 printf("\nlocbeac:");  
	 for (i=0;i<numattrs;i++){	
		localbeac[i]=rintunif(2);	
		 printf("%i ", localbeac[i]); 
	}

	 printf("\nfloatbeac:");  
	 for (i=0;i<numattrs;i++){	
		floatavbeac[i]=rfloatunif(0,maxattrvalues-1);	
		 printf("%f ", floatavbeac[i]); 
	}
	
 
	 printf("\npref: %f \n",indfpreference(&F,&M,binarybeac,glbeac,glbeac,localbeac,floatavbeac,floatavbeac));
   }
}






void testnumenabledstrategies(){

 printf("\n %i \n", numenabledstrategies());
}

void testselectMaxMfromrandbatch(int psize, int bsize, char strat){

  numattrs=2;
  I *M, F;
  int i;
  attrtype globalbeacon[numattrs], globalbeacon2[numattrs], binaryaveragebeac[numattrs];
     float floatavbeac[numattrs];
     
  M=malloc(psize*(sizeof(I)+1));


  randomizebeacon(globalbeacon); 	randomizebeacon(globalbeacon2); 	randomizebeacon(binaryaveragebeac); 

  
  for (i=0; i< psize; i++) {
    makerandomI(&M[i]); 
	  }

   makerandomI(&F); 

   F.strategy=strat;

	printf("Ms: \n");

  M[1].alive=0;
  for (i=0; i< psize; i++) {
//      printf("%i >>> \n", i);

	printI(&M[i]);
	}

   printf("F: \n");

   printI(&F);

 printf("\n floatbeac:");
 	 for (i=0;i<numattrs;i++){	
		floatavbeac[i]=rfloatunif(0,maxattrvalues-1);	
 		 printf("\n  %f",floatavbeac[i]);
		}
 printf("\n");

	lowDEBUG=1;

  selectMaxMfromrandbatch( &F, 0, M,  psize,  bsize,  binaryaveragebeac, globalbeacon, globalbeacon2,floatavbeac);


}


void testupdatebeacon(int n){
  int i,j;
  attrtype b[numattrs];

  printf("\n new:\n");
  
  for (i=0;i<numattrs;i++) {
  	b[i]=rintunif(maxattrvalues);
  	printf("%i ", b[i]);
  	
  	}
  printf("\nupdates: \n");

  for (i=0;i<n;i++) {
	updatebeacon(b);
	  for (j=0;j<numattrs;j++) {
	  	printf("%i ", b[j]);
			}
 	  printf("\n");

  }
  
  printf("\n"); 

}

void testaverageattr(){
	double t;

	I M; makezeroI(&M);

  	t=averageattr(M.attr);
 	printI(&M);
	printf("averageattr %f \n",t);
	 makerandomI(&M);

  	t=averageattr(M.attr);
 	printI(&M);
	printf("averageattr %f \n",t);
	 makerandomI(&M);

  	t=averageattr(M.attr);
 	printI(&M);
	printf("averageattr %f \n",t);

 
}

void testkillM(){
 int i;
 I a;   makerandomI(&a); 

 printI(&a);
 printf("\nav attr %f chance %f\n",averageattr(a.attr),averageattr(a.attr)*costattr);
 for (i=0;i<5;i++){
	killM(&a);
 	if (a.alive==0){printf("\nKilled!%i\n",i);
		  printI(&a);
	  	a.alive=1;
	  } 
 	}

  makezeroI(&a); 

 printI(&a);
 printf("\nav attr %f chance %f\n",averageattr(a.attr),averageattr(a.attr)*costattr);

 for (i=0;i<5;i++){
	killM(&a);
 	if (a.alive==0){printf("\nKilled!%i\n",i);
		  printI(&a);
	  	a.alive=1;
	  } 
	
   }
}


void testkillF(int strategy){
 int i; I a;
 for (i=0;i<10;i++){
	 makerandomI(&a);
	 a.strategy=strategy; 
	 printI(&a);
	 killF(&a);
	 printI(&a);
    }

}

void testdecimatepopulation(){
	int i;
	int size=popsize;
  I *M;

       M=malloc(size*(sizeof(I)+1));

	for (i=0;i<size;i++){
		makerandomI(&M[i]);
		printI(&M[i]);
	 }

	decimatepopulation(M,'F');

  printf("\nAFTER:\n");

	for (i=0;i<size;i++){

		printI(&M[i]);
	 }
  
}


/*

void testgetmaxvalue(){
	int i;
	int size=2000;
	float averages[numstrategies];
	long double aa;
	I *M;

       M=malloc(size*(sizeof(I)+1));

	for (i=0;i<size;i++){
		M[i]=makerandomI();
		printI(&M[i]);
	 }
	
	aa= getmaxvalue(M, size);

	printf("%Lf",aa);




	printf("\n");

}

void testgetminvalue(){
	int i;
	int size=2000;
	float averages[numstrategies];
	long double aa;
	I *M;

       M=malloc(size*(sizeof(I)+1));

	for (i=0;i<size;i++){
		M[i]=makerandomI();
		printI(&M[i]);
	 }
	
	aa= getminvalue(M, size);

	printf("%Lf",aa);




	printf("\n");

}

*/

void testgetaverages(long int size){
	long int i;
	float averagestr[numstrategies];
	float averageattr[numattrs], averageideal[numattrs];
	long double averagehowmanyattr;
	I *M;
//	printf("Size of I: %i \n ", sizeof(I));

       M=malloc(size*(sizeof(I)+1));

	for (i=0;i<size;i++){
		makerandomI(&M[i]);
		printI(&M[i]);
	 }
	
	 getaverages(M, averageattr, averageideal, averagestr,size);

//	printf("%Lf ",aa);

	printf("Strategies: ");

	for (i=0;i<numstrategies;i++){	
		printf("%f ",averagestr[i]);
		}

	printf("\n Attrs: \n");

	for (i=0;i<numattrs;i++){	
		printf("%f ",averageattr[i]);
		}

	printf("\n Ideal: \n");


	for (i=0;i<numattrs;i++){	
		printf("%f ",averageideal[i]);
		}

//	averagehowmanyattr=getaveragehowmanyattr(M,size);
	
	printf("\n howmanyattr %Lf \n",averagehowmanyattr);


}

void testgetrlivebatch(int psize, int bsize){
   I *M;
   int i;
       M=malloc(psize*(sizeof(I)+1));
//  int  *indexpop=malloc(size*(sizeof(int)));
  
  int batchind[bsize]; 
  
//  for (i=0;i<size;i++){indexpop[i]=i;}
  
	for (i=0;i<psize;i++){
		makerandomI(&M[i]);

	 }


 M[1].alive=0;
 
	for (i=0;i<psize;i++){

		printI(&M[i]);
	 }
 
 
 getrlivebatch(M, batchind, bsize,  psize);

 printf("\nBatch: \n");
	for (i=0;i<bsize;i++){
		 printf("%i ", batchind[i]);
    	}
 printf(" \n");

 
	for (i=0;i<bsize;i++){
		printI(&M[batchind[i]]);
	 }


}


void testmakebinarybeaconfromideals (int size, int bsize){

	long int i; int t;
	float averagestr[numstrategies];
	float averageattr[numattrs], averageideal[numattrs];
	attrtype binarybeac[numattrs];
	I *M;
//	printf("Size of I: %i \n ", sizeof(I));
//	float averageideal[numattrs];

       M=malloc(size*(sizeof(I)+1));
  int  *indexpop=malloc(size*(sizeof(int)));
  
  for (i=0;i<size;i++){indexpop[i]=i;}
  
	for (i=0;i<size;i++){
		makerandomI(&M[i]);
		printI(&M[i]);
	 }

	
	getaverageideal (M, averageideal, size, indexpop);

	printf("\n average ideal \n: ");
	
	for (i=0;i<numattrs;i++){
  		printf("%f ", averageideal[i]);
	
	}
	

	makebinarybeaconfromideals(M, binarybeac, size, indexpop);

	printf("\n Beacon: \n");
	
	for (i=0;i<numattrs;i++){
  		printf("%i ", binarybeac[i]);
	
	}
	printf("\n ");


       attrtype localbeacon[numattrs];
       int index[bsize];

 for (t=0;t<3;t++){
       getrbatch(index,bsize,size);

      printf("Batch %i:", t);
	for (i=0;i<bsize;i++){
  		printf("%i ", index[i]);
	
	}
	printf("\n ");

       makebinarybeaconfromideals(M,localbeacon,bsize,index);


	printf("\n Beacon: \n");
	
	for (i=0;i<numattrs;i++){
  		printf("%i ", localbeacon[i]);
	
	}
	printf("\n ");
  }
}

void testassignrestrategy(int n, int NEstrat){
  int i;
  for (i=0;i<n;i++){
	 printf("\n %i\n", assignrestrategy(NEstrat));
  }
}


void testfprintpopattrsentr(int size){
    I *M;
    int i;

    M = malloc(size*(sizeof(I)+1));
    
	for (i=0;i<size;i++){
		makerandomI(&M[i]);
//		printI(&M[i]);
	 }
 

    fprintpopattrsentr(M, stdout);

}


void testl1distance(){
	attrtype a[numattrs], b[numattrs];
	int i;
	for (i=0; i<numattrs;i++) { a[i]=rintunif(maxattrvalues); printf("%i ", a[i]);}
	 printf("\n");
	for (i=0; i<numattrs;i++) { b[i]=rintunif(maxattrvalues); printf("%i ", b[i]);}
	
	 printf("\n %f \n", l1distance(a,b,numattrs,maxattrvalues));

	for (i=0; i<numattrs;i++) { a[i]=maxattrvalues-1; printf("%i ", a[i]);}
	 printf("\n");
	for (i=0; i<numattrs;i++) { b[i]=0; printf("%i ", b[i]);}
	
	 printf("\n %f \n", l1distance(a,b,numattrs,maxattrvalues));


}


void testl1distancef(){

	attrtype b[numattrs];
	float a[numattrs];
	int i;

	 printf("\na:");  
	 for (i=0;i<numattrs;i++){	
		a[i]=rfloatunif(0,maxattrvalues-1);	
		 printf("%f ", a[i]); 
	}

	 printf("\n");

	for (i=0; i<numattrs;i++) { b[i]=rintunif(maxattrvalues); printf("%i ", b[i]);}

	 printf("\n");

	 printf("\n %f \n", l1distancef(a,b,numattrs,maxattrvalues));

}



void main()  {
srand(2);
int i,j,k;

//  int indexpop[popsize];
//  for (i=0;i<popsize;i++){indexpop[i]=i;}
//  int NEstrat=numenabledstrategies();

//testconfidenceint();

testupdatebeacon(5);


//testgetrlivebatch(3,30);


//testonerpopgauss(0,30,1000);


//testselectMaxMfromrandbatch(5,5,2);

// testgetaveragel1distance();
//testgetsecondmostfrequent(10);

//testindfpreference(1);

//testselectMaxMfromrandbatch(5,50,1);


//testassignrestrategy(20,NEstrat);
//testnumenabledstrategies();
//testdistrans(20);

//testgetrlivebatch(5,2);


//testl1distancef();

//testindfpreference(4);
//testmakebinarybeaconfromideals(400000,200);


//printf ("%Lf \n",log2(1025));

//testkillF(0);

//testgetaverages(44444);

//testgetdifferentattrarrays();


//testgetaverages(10);
//testindfpreference(1);

//testl1distance();

//testmakeI();

//testindfpreference(2);
// printf ("%i \n",21 % 20);
//testmakerandomI();



}
