#include <bits/stdc++.h>
#include <time.h>

using namespace std;

void geraMatriz(double **M, int rows, int col){ 
    srand( (unsigned)time(NULL) ); // seed 
    for(int i = 0; i < rows; i++){ 
        for(int j = 0; j < col; j++){ 
            M[i][j] = (double)(rand() % 1000 + 1)/100; //(0~100 double)
        }
    }
    return;
}

void help(){
    cout << "Execução do programa: " << endl;
    cout << "                 ./matrix l c -o|-t" << endl << endl;
    cout << "                 Onde:" << endl;
    cout << "                    l     -> numero de linhas " << endl;
    cout << "                    c     -> numero de colunas" << endl;
    cout << "                    -o|-t -> (-o)multiplicação convencional ou(-t) M2 transposta" << endl << endl;                                
    cout << "                 Outros parametros:" << endl;
    cout << "                    -h = Ajuda (se eu nao soubesse...)" << endl;
    cout << "                    -s = Mostrar Matriz" << endl;
}

/*checar parametros corretos*/
void checkParam(int argc){
    if (argc != 4){
        cout << "Falta de parametros" << endl;
        cout << "Use -h para mais informações" << endl;
        exit(0);
    }
}

void checkParamEmpty(int argc){
	if (argc == 1){
    	cout << "Use -h para mais informações" << endl;
    	exit(0);
    }
}

double** allocMat(int rows, int col){
    double **M = (double **)malloc(rows * sizeof(double*));

    for (int i = 0; i < col; i++)
        M[i] = (double *)malloc(col * sizeof(double));

    geraMatriz(M, rows, col);
    return M;
}

void printMat(double **M, int rows, int col){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < col; j++){
            cout << M[i][j] << "          ";
        }
        cout << endl;
    }

}

double** transpostaM(double **M, int rows, int col){ 
    int i, j; 
    double aux; 
    for (i = 0; i < rows; i++) { 
        for (j = i+1; j < col; j++) { 
            if (j != i) { 
                aux     = M[i][j]; 
                M[i][j] = M[j][i]; 
                M[j][i] = aux;
            } 
        } 
    }
    return M; 
}

/*Operacoes*/

void multO(double **mat1, double **mat2, int rows, int col){
    double **mat3 = allocMat(rows, col);
    float sum = 0.0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < col; j++) {
            for (int k = 0; k < rows; k++) {
                sum = sum + mat1[i][k]*mat2[k][j];
            }
            mat3[i][j] = sum;
            sum = 0;
        }
    }
    free(mat3);
}

void mutlT(double **mat1, double **m2t, int rows, int col){
    double **mat3 = allocMat(rows, col);
    float sum = 0.0;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < col; j++){
            for (int k = 0; k < rows; k++) {
                sum = sum + mat1[i][k]*m2t[i][k];
            }
            mat3[i][j] = sum;
            sum = 0;  
        }    
    }
    free(mat3);
}

int main(int argc, char **argv){
    float tempo = 0.0;
    clock_t inicio, fim;

    float tempot = 0.0;
    clock_t iniciot, fimt;
    
    checkParamEmpty(argc);

    if (strcmp(argv[1], "-h") == 0){
        help();
    }else{
        checkParam(argc); //impede seg fault

        int rows = atoi(argv[1]);
        int col = atoi(argv[2]);
        
        double **mat1 = allocMat(rows, col);
        double **mat2 = allocMat(rows, col);
        
        if (strcmp(argv[3], "-s") == 0){
            if (rows > 15 && col > 15) {
                cout << "Matriz muito grande para impressão" << endl;
            }else{
                cout << "Matriz 1: " << endl;
                printMat(mat1, rows, col);
                cout << endl << endl << "Matriz 2:" << endl;
                printMat(mat2, rows, col); 
            }
        }else if (strcmp(argv[3], "-o") == 0){
            inicio = clock();
            multO(mat1, mat2, rows, col);
            fim = clock();
        }else if (strcmp(argv[3], "-t") == 0){
        	inicio = clock();
        	iniciot = clock();
            double **m2t = transpostaM(mat2, rows, col);
            fimt = clock();
            tempot = (float) (((fimt-iniciot) + 0.0) / CLOCKS_PER_SEC);
        	cout << "Tempo dA transposta: " << tempot<< endl;
            mutlT(mat1, m2t, rows, col);
            fim = clock();
            //free(m2t);
        }
        tempo = (float) (((fim-inicio) + 0.0) / CLOCKS_PER_SEC);
        cout << "Tempo de execução: " << tempo << endl;
        free(mat1);
        free(mat2);
    }   
}