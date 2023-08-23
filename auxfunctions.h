

float rfloatunif(float a, float b){
	return ((float)(rand())/RAND_MAX)*(b-a)+a;
}

int rcharunif(int a, int b){
	if (a<0) { if (b<0) {return (int)(((float)(rand())/RAND_MAX)*(b+1-a)+a-1);} 
			else {return (int)(((float)(rand())/RAND_MAX)*(b+2-a)+a-1);}
		 } 
		else {return (int)(((float)(rand())/RAND_MAX)*(b+1-a)+a);}
}

int rintunif(int a){
     	int r=(int)(((float)(rand())/RAND_MAX)*a);
     	if (r==a){r=0;}
	return r;
}




void selectrbatch(int *batchind, int size){
	int i;

	for (i=0;i<size;i++){
	  batchind[i]=	rintunif(popsize);
	}

}


float l1distance (unsigned char *a, unsigned  char *b, int size, int maxval){

	int i; int t=0;
	
	for (i=0;i<size;i++){
		t+= abs( (int) a[i] - (int) b[i]);
		}
	if (size) {return (float) t/ (size*(maxval-1));}
	 else {return 1;}
}

float l1distancef (float *a, unsigned  char *b, int size, int maxval){

	int i;  double t=0;
	
	for (i=0;i<size;i++){
		t+= fabs( (double) a[i] - (double) b[i]); 
		}
	if (size) {return (float) t/ (size*(maxval-1));}
	 else {return 1;}
}


char samechar(unsigned char *a, unsigned  char *b, int size){

 int i=0; 
	for (i=0;i<size;i++){
 	 	if (a[i]!=b[i]) {return 0;}
	}
  return 1;
}



void getrbatch(int *batchind, int batchsize, int psize){
	int i;

	for (i=0;i<batchsize;i++){
	  batchind[i]=	rintunif(psize);
	}

}

