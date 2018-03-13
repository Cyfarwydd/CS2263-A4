#include <stdlib.h>
#include <time.h>
#include <stdio.h>
void buildBlob(int blob[], int row, int col);
void blobToString(int blob[], int row, int col);
int recBlobCount(int blob[], int row, int col, int cRow, int cCol);
void reset(int blob[], int row, int col);
int count(int blob[], int row, int col);
int main(int argc, char **ARGV){
	int i, j, total;
	char* x;
	if(argc > 2){
		i = strtol(ARGV[1], &x,10);
		j = strtol(ARGV[2], &x, 10);
	}else{
		exit(0);
	}
	int blob[i*j];
	buildBlob(blob, i, j);
	blobToString(blob, i, j);
	total = count(blob, i, j);
	int err = 1;
	int row = 0;
	int col = 0;
	do{
		printf("enter coordinate i,j (non-numeric to quit): ");
		int row, col, cnt;
		err = scanf("%d,%d", &row, &col);
		if(err == 2 && (row < i && row >= 0 && col < j && col >= 0)){
			cnt = recBlobCount(blob, i, j, row, col);
			double x = (float)cnt/total;
			x = x*100;
			printf("Blob size: %d (%f %% of all 1's)\n", cnt, x);
			reset(blob, i, j);
		}
	}while(err == 2 && (row < j && row >= 0 && col < i && col >= 0));
	return 0;

}
void buildBlob(int blob[], int row, int col){
	srand(time(NULL));
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			int s = rand();
			if(s%2){
				blob[(i*col) + j] = 1;
			}else{
				blob[(i*col) + j] = 0;
			}
		}
	}
}
void blobToString(int blob[], int row, int col){
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			printf("%d ", blob[(i*col) + j]);
		}
		printf("\n");
	}
}
int recBlobCount(int blob[], int row, int col, int cRow, int cCol){
	//cRow = row coord of the spot you want to check
	//cCol = column coord of the spot you want to check
	if(blob[cRow*col + cCol] == 1 && (cRow < row && cCol < col) && (cRow >= 0 && cCol >= 0)){
		blob[cRow*col + cCol] = -1;
		return 1	+ recBlobCount(blob, row, col, cRow, cCol - 1)
				+ recBlobCount(blob, row, col, cRow + 1, cCol -1)
				+ recBlobCount(blob, row, col, cRow + 1, cCol)
				+ recBlobCount(blob, row, col, cRow + 1, cCol + 1)
				+ recBlobCount(blob, row, col, cRow, cCol + 1)
				+ recBlobCount(blob, row, col, cRow - 1, cCol + 1)
				+ recBlobCount(blob, row, col, cRow - 1, cCol)
				+ recBlobCount(blob, row, col, cRow - 1, cCol - 1);

	}else{ 
		return 0;
	}
}
int count(int blob[], int row, int col){
	int cnt = 0;
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			if(blob[(i * col) + j] == 1){
				cnt++;
			}
		}
	}
	return cnt;
}
void reset(int blob[], int row, int col){
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			if(blob[(i * col) + j] == -1){
				blob[(i * col) + j] = 1;
			}
		}
	}
}
