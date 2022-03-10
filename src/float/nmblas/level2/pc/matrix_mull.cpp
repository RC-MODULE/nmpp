void matrix_mull(
	const int N,//rows of the first matrix
	const int K,//collums of the first matrix
	const int M,//collums of the second matrix
	float *matrix_1,//address of the first matrix
	const int STRIDE_1, 
	float *matrix_2,
	const int STRIDE_2,
	float *out,
	const int STRIDE_3
)
{
	float temp;
	int row_pntr_1,row_pntr_2,coll_pntr_1,coll_pntr_2;
	int row_pntr_wrt,coll_pntr_wrt;
	int i,z,j;
	int next_row_1;
	for(i=0,next_row_1=0,row_pntr_wrt=0;i<N;i++,next_row_1+=STRIDE_1,row_pntr_wrt+=STRIDE_3){
		for(j=0,coll_pntr_2=0,coll_pntr_wrt=0;j<M;j++,coll_pntr_2++,coll_pntr_wrt++){
			temp =0;
			for(z=0,row_pntr_1=next_row_1,coll_pntr_1=0,row_pntr_2=0;   z<K;     z++,coll_pntr_1++,row_pntr_2+=STRIDE_2){
				temp += matrix_1[row_pntr_1+coll_pntr_1]*matrix_2[row_pntr_2+coll_pntr_2];
			}
				out[row_pntr_wrt+coll_pntr_wrt] = temp;
		}
	}

};
/*#include <stdio.h>	
float matrix_1[3][4];
float matrix_2[3][12];
float matrix_3[3][8];
int  main(){
	for(int i=0;i<3;i++){
		for(int j=0;j<4;j++){
			matrix_1[i][j] = 1;
		}
	}
	matrix_1[0][2] = 0;
	matrix_1[1][0] = 0;
	matrix_1[2][1] = 0;
	matrix_1[2][2] = 0;

	printf("the first matrix is desplayed row by row\n");
	for(int i=0;i<3;i++){
		printf("\n");
		for(int j=0;j<3;j++){
			printf("%f\n  ", matrix_1[i][j]);
		}
	}

	printf("the second matrix\n");

	for(int i=0;i<12;i++){
		printf("\n");
		for(int j=0;j<3;j++){
			matrix_2[j][i] = i;
			printf("%f\n  ", matrix_2[j][i]);
		}
	}


	matrix_mull(3,3,8,(float*)matrix_1,4,(float*)matrix_2,12,(float*)matrix_3,8);
	printf("the therd matrix\n");

	for(int i=0;i<3;i++){
		printf("\n");
		for(int j=0;j<8;j++){
			printf("%f\n  ", matrix_3[i][j]);
		}
	}
}*/