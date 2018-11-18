#include"mpi.h"
#include<iostream>
#include<string>

using namespace std;

char* SplitString(char* str, int proc_num, int proc_rank, int& lenght) {
	int len = strlen(str);
	int split_lenght = len / proc_num;
	int remains = len % proc_num;

	int start = 0;
	char* result;
    int remains = len % proc_num;

	int start = 0;
	char* result;

	
	
	for (int i = 0; i <= proc_rank; i++) {
		lenght = split_lenght + (i < remains) + (i > 0);
		start += lenght - 1;
	}
	
	
	for (int i = 0; i <= proc_rank; i++) {
		lenght = split_lenght + (i < remains) + (i > 0);
		start += lenght - 1;
	}

	start -= lenght - 1;

	return &str[start];
}

int Check(char* start, int lenght) {
	for (int i = 1; i < lenght; i++) {
		if ((int)start[i - 1] > (int)start[i])
			for (int j = 1; j < lenght; j++) {
		       if ((int)start[i - 1] > (int)start[i])
			return 0;
	}

	return 1;
}

int main(int argc, char* argv[]) {
	
	char str1[] = "abcdefghijklmnopq";// correct
	char str2[] = "abefghaaalmnopq";// not correct

	int ProcNum, ProcRank, RecvRank;
	MPI_Status Status;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

	int lenght1,lenght2;

	char* adress = SplitString(str1,ProcNum,ProcRank,lenght1);
	int code_error1 = Check(adress, lenght1);


	int result1,result2;
	int sum1 = code_error1,sum2 = code_error2;

	if (ProcRank == 0) {
		
		
		for (int i = 1; i < ProcNum; i++) {
			MPI_Recv(&result1, 1, MPI_INT, MPI_ANY_SOURCE,0, MPI_COMM_WORLD, &Status);
			MPI_Send(&code_error1, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		    MPI_Recv(&result2, 1, MPI_INT, MPI_ANY_SOURCE,1, MPI_COMM_WORLD, &Status);
			adress = SplitString(str2, ProcNum, ProcRank, lenght2);
	        int code_error2 = Check(adress, lenght2);
			sum1 += result1;
			sum2 += result2;
		}

		
		for (int i = 1; i < lenght; i++) {
		if ((int)start[i - 1] > (int)start[i])
			return 0;	
		
	}
	else {
		MPI_Send(&code_error1, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		MPI_Recv(&result2, 1, MPI_INT, MPI_ANY_SOURCE,1, MPI_COMM_WORLD, &Status);
		MPI_Send(&code_error2, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
	}
	
	MPI_Finalize();
	return 0;
}