double accmul32_64f(double* a, double* b, double* c, double* d,int size){
	int i;
	for	(i=0; i<size; i++){
		d[i]=a[i]*b[i]+c[i];
	}
	return d[0];
}
