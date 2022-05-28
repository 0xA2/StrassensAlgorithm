#include <chrono>
#include <cstring>
#include <iostream>
#include <vector>

#include <math.h>
#include <unistd.h>

using namespace std;
using namespace std::chrono;

// Read matrix file into vector
vector<vector<int>> readMatrix(){
	int rows, cols;
	cin >> rows;
	cin >> cols;
	vector<vector<int>> matrix;
	for(int i = 0; i<rows; i++){
		vector<int> curRow;
		for(int j = 0; j<cols; j++){
			int curN; cin >> curN;
			curRow.push_back(curN);
		}
		matrix.push_back(curRow);
	}
	return matrix;
}


// Print matrix from vector
void printMatrix(vector<vector<int>> matrix){
	for(unsigned long i = 0; i<matrix.size(); i++){
		for(unsigned long j = 0; j<matrix[i].size(); j++){
			cout << matrix[i][j] << " ";
		}
		cout << '\n';
	}
}


// Multiply two matrices using naive bruteforce method
void naiveMatrixMult(vector<vector<int>> m1, vector<vector<int>> m2, vector<vector<int>>& res){
	for(unsigned long i = 0; i<m1.size(); i++){
		for(unsigned long j = 0; j<m2[0].size(); j++){
			for(unsigned long k = 0; k<m1[0].size(); k++){
				res[i][j] += m1[i][k]*m2[k][j];
			}
		}
	}
}

// Multiply element from the first matrix by the correspondent row on the second matrix
void matrixMultLine(vector<vector<int>> m1, vector<vector<int>> m2, vector<vector<int>>& res){
	for(unsigned long i = 0; i<m1.size(); i++){
		for(unsigned long k = 0; k<m1[0].size(); k++){
			for(unsigned long j = 0; j<m2[0].size(); j++){
				res[i][j] += m1[i][k]*m2[k][j];
			}
		}
	}
}


// Add two matrices
void addMatrices(vector<vector<int>> m1, vector<vector<int>> m2, vector<vector<int>>& res){
	if(m1.size() != m2.size() || m1[0].size() != m2.size()){
		cout << "Error: undefined result trying to add matrices with different dimensions" << endl;
	}
	for(unsigned long i = 0; i<m1.size(); i++){
		for(unsigned long j = 0; j<m1[0].size(); j++){
			res[i][j] = m1[i][j] + m2[i][j];
		}
	}
}

// Subtract two matrices
void subMatrices(vector<vector<int>> m1, vector<vector<int>> m2, vector<vector<int>>& res){
	if(m1.size() != m2.size() || m1[0].size() != m2.size()){
		cout << "Error: undefined result trying to subtract matrices with different dimensions" << endl;
	}
	for(unsigned long i = 0; i<m1.size(); i++){
		for(unsigned long j = 0; j<m1[0].size(); j++){
			res[i][j] = m1[i][j] - m2[i][j];
		}
	}
}


// Multiply two matrices using Strassen's algorithm
void StrassenMult(vector<vector<int>> m1, vector<vector<int>> m2, vector<vector<int>>& res, unsigned long n){

	// Auxiliary vectors

	vector<vector<int>> A11, A12, A21, A22;
	vector<vector<int>> B11, B12, B21, B22;
	vector<vector<int>> C11, C12, C21, C22;
	vector<vector<int>> M1, M2, M3, M4, M5, M6, M7;
	vector<vector<int>> tmp1, tmp2;


	// Base case: when matrix has dimensions 2x2 or can't be divided into 4 submatrices of the same size apply naive multiplication algorithm
	if(n <= 2 || n%2 != 0){
		matrixMultLine(m1,m2,res);
	}
	else{

		for(unsigned long i = 0; i<n/2; i++){

			vector<int> curRowA11;
			vector<int> curRowA12;
			vector<int> curRowA21;
			vector<int> curRowA22;

			vector<int> curRowB11;
			vector<int> curRowB12;
			vector<int> curRowB21;
			vector<int> curRowB22;

			vector<int> curRowC11(n/2);
			vector<int> curRowC12(n/2);
			vector<int> curRowC21(n/2);
			vector<int> curRowC22(n/2);

			vector<int> curRowM1(n/2);
			vector<int> curRowM2(n/2);
			vector<int> curRowM3(n/2);
			vector<int> curRowM4(n/2);
			vector<int> curRowM5(n/2);
			vector<int> curRowM6(n/2);
			vector<int> curRowM7(n/2);

			vector<int> curRowTmp1(n/2);
			vector<int> curRowTmp2(n/2);

			for(unsigned long j = 0; j<n/2; j++){
				curRowA11.push_back(m1[i][j]);
				curRowA12.push_back(m1[i][j+n/2]);
				curRowA21.push_back(m1[i+n/2][j]);
				curRowA22.push_back(m1[i+n/2][j+n/2]);

				curRowB11.push_back(m2[i][j]);
				curRowB12.push_back(m2[i][j+n/2]);
				curRowB21.push_back(m2[i+n/2][j]);
				curRowB22.push_back(m2[i+n/2][j+n/2]);
			}

			A11.push_back(curRowA11);
			A12.push_back(curRowA12);
			A21.push_back(curRowA21);
			A22.push_back(curRowA22);

			B11.push_back(curRowB11);
			B12.push_back(curRowB12);
			B21.push_back(curRowB21);
			B22.push_back(curRowB22);

			C11.push_back(curRowC11);
			C12.push_back(curRowC12);
			C21.push_back(curRowC21);
			C22.push_back(curRowC22);

			M1.push_back(curRowM1);
			M2.push_back(curRowM2);
			M3.push_back(curRowM3);
			M4.push_back(curRowM4);
			M5.push_back(curRowM5);
			M6.push_back(curRowM6);
			M7.push_back(curRowM7);

			tmp1.push_back(curRowTmp1);
			tmp2.push_back(curRowTmp2);
		}


		// M1 = (A11 + A22) * (B11 + B22)
		addMatrices(A11,A22,tmp1);
		addMatrices(B11,B22,tmp2);
		StrassenMult(tmp1, tmp2, M1, n/2);

		// M2 = (A21 + A22) * B11
		addMatrices(A21,A22,tmp1);
		StrassenMult(tmp1, B11, M2, n/2);

		// M3 = A11 * (B12 - B22)
		subMatrices(B12, B22, tmp2);
		StrassenMult(A11, tmp2, M3, n/2);

		// M4 = A22 * (B21 - B11)
		subMatrices(B21, B11, tmp2);
		StrassenMult(A22, tmp2, M4, n/2);

		// M5 = (A11 + A12) * B22
		addMatrices(A11, A12, tmp1);
		StrassenMult(tmp1, B22, M5, n/2);

		// M6 = (A21 - A11) * (B11 + B12)
		subMatrices(A21, A11, tmp1);
		addMatrices(B11, B12, tmp2);
		StrassenMult(tmp1, tmp2, M6, n/2);

		// M7 = (A12 - A22) * (B21 + B22)
		subMatrices(A12, A22, tmp1);
		addMatrices(B21, B22, tmp2);
		StrassenMult(tmp1, tmp2, M7, n/2);


		// C11 = M1 + M4 - M5 + M7
		addMatrices(M1, M4, tmp1);
		subMatrices(M7, M5, tmp2);
		addMatrices(tmp1, tmp2, C11);

		// C12 = M3 + M5
		addMatrices(M3, M5, C12);

		// C21 = M2 + M4
		addMatrices(M2, M4, C21);

		// C22 = M1 - M2 + M3 + M6
		subMatrices(M1, M2, tmp1);
		addMatrices(M3, M6, tmp2);
		addMatrices(tmp1, tmp2, C22);

		// Save results to res
		for(unsigned long i = 0; i<n/2; i++){
			for(unsigned long j = 0; j<n/2; j++){
				res[i][j] = C11[i][j];
				res[i][j+n/2] = C12[i][j];
				res[i+n/2][j] = C21[i][j];
				res[i+n/2][j+n/2] = C22[i][j];
			}
		}
	}
}

int main(int argc, char* argv[]){

	// If number of arguments is not correct print usage instructions
	if(argc != 2){
		cout << "Usage: $ ./matrixmult [OPTION]\nOptions: -m or --matrixMult\n         -l or --lineMult\n         -s or --strassen" << endl;
		exit(1);
	}

	// Read matrices to multiply from stdin in the following manner:
	/*
		-> 	First 2 integers (a and b) are the dimensions of the first matrix
		-> 	Next a*b integers are the values from the first matrix
		-> 	The same is done for the second matrix
		-> 	Input Example:
			3 3
			1 2 3
			4 5 6
			7 8 9
			3 3
			9 8 7
			6 5 4
			3 2 1
	*/

	vector<vector<int>> m1 = readMatrix();
	vector<vector<int>> m2 = readMatrix();

	// Verify that matrix multiplication is valid between provided matrices
	if(m1[0].size() != m2.size()){ cout << "Provided matrices can't be multiplied" << endl; exit(1); }

	// Create matrix to store result of calculations
	vector<vector<int>> res;
	for(unsigned long i = 0; i<m2[0].size(); i++){
		vector<int> tmp(int(m1.size()));
		res.push_back(tmp);
	}

	//cout << "Product of following Matrices:" << endl;
	//cout << "\nMatrix 1 " << endl;
	//printMatrix(m1);
	//cout << "\nMatrix 2" << endl;
	//printMatrix(m2);

	if(strcmp(argv[1],"-m") == 0 || strcmp(argv[1],"--matrixMult") == 0){

		// Naive Matrix Multiplication
		auto start = high_resolution_clock::now();
		naiveMatrixMult(m1, m2, res);
		auto stop = high_resolution_clock::now();

		//cout << "\nResult: " << endl;
		//printMatrix(res);

		auto duration = duration_cast<microseconds>(stop - start);
		double time = double(duration.count())/1000.0;
		cout << "\nTime: " << time << " milliseconds" << endl;
	}
	else if(strcmp(argv[1],"-l") == 0 || strcmp(argv[1],"--lineMult") == 0 ){

		// Line Multiplication
		auto start = high_resolution_clock::now();
		matrixMultLine(m1, m2, res);
		auto stop = high_resolution_clock::now();

		//cout << "\nResult: " << endl;
		//printMatrix(res);

		auto duration = duration_cast<microseconds>(stop - start);
		double time = double(duration.count())/1000.0;
		cout << "\nTime: " << time << " milliseconds" << endl;
	}
	else if(strcmp(argv[1],"-s") == 0 || strcmp(argv[1],"--strassen") == 0){

		// Make sure m1 and m2 are square matrices of the same size
		if(m1.size() != m1[0].size() || m1.size() != m2.size() || m1[0].size() != m2.size()){
			cout << "Error: this implementation of Strassen's Algorithm only works for square matrices of the same size." << endl;
		}

		// Strassen Algorithm for Matrix Multiplication
		auto start = high_resolution_clock::now();
		StrassenMult(m1, m2, res, m1.size());
		auto stop = high_resolution_clock::now();

		//cout << "\nResult: " << endl;
		//printMatrix(res);

		auto duration = duration_cast<microseconds>(stop - start);
		double time = double(duration.count())/1000.0;
		cout << "\nTime: " << time << " milliseconds" << endl;
	}
	else{
		cout << "Invalid Option" << endl;
		cout << "Usage: $ ./matrixmult [OPTION]\nOptions: -m or --matrixMult\n         -l or --lineMult\n         -s or --strassen" << endl;
		exit(1);
	}

	return 0;
}
