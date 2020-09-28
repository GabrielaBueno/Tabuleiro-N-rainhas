#include<stdio.h> 
#include<stdbool.h> 
#include<time.h>

int **Aloca_matriz (int m, int n)
{
  int **v;  /* ponteiro para a matriz */
  int   i;    /* variavel auxiliar      */
  if (m < 1 || n < 1) { /* verifica parametros recebidos */
     printf ("** Erro: Parametro invalido **\n");
     return (NULL);
     }
  /* aloca as linhas da matriz */
  v = (int **) calloc (m, sizeof(int *));	// Um vetor de m ponteiros para int */
  if (v == NULL) {
     printf ("** Erro: Memoria Insuficiente **");
     return (NULL);
     }
  /* aloca as colunas da matriz */
  for ( i = 0; i < m; i++ ) {
      v[i] = (int*) calloc (n, sizeof(int));	/* m vetores de n int */
      if (v[i] == NULL) {
         printf ("** Erro: Memoria Insuficiente **");
         return (NULL);
         }
      }
  return (v); /* retorna o ponteiro para a matriz */
}



  
/* Função para imprimir solução*/
void imprimeSol(int **matz, int nu) 
{ 
    int **mat = matz; 
    int i;
    int j;
    int n=nu;
    for (i = 0; i < n; i++) 
    { 
        for (j = 0; j < n; j++) 
            printf(" %d  ", mat[i][j]); 
            printf("\n"); 
        
    } 
    
} 

void liberaQueen(int **mat,int n){ //Função para liberar casas do tabuleiro para a troca de posição
    int i,j; 
    int cont = 0;
    for (j = 0; j < n; j++){ // percorre a linha da matriz 
        for ( i = 0; i < n; i++){ // percorre a coluna da matriz
	       cont=i;
           mat[i][j] =0; // libera a casa do tabuleiro        
        }   
    }
}
/*Uma função para verificar se uma rainha pode
   ser colocada no tabuleiro [linha] [col]. Note que este
   função é chamada quando rainhas "col" são
   já colocado em colunas de 0 a col -1.
   Então, precisamos verificar apenas o lado esquerdo para
   atacando rainhas */

bool colocaQueen(int **mat, int row, int col, int nu) 
{ 
    int i; 
    int j; 
    int N = nu;

   //Verifique esta linha no lado esquerdo
       
    for (i = 0; i < col; i++) 
 
        if (mat[row][i]) 
         
          return false; 
  
   // Verifique a diagonal superior no lado esquerdo
    for (i=row, j=col; i>=0 && j>=0; i--, j--) 

        if (mat[i][j])
       
            return false; 

     //Verifique a diagonal inferior no lado esquerdo
      for (i=row, j=col; j>=0 && i<N; i++, j--) 

        if (mat[i][j])
       
            return false; 
  
    return true; 
} 

  
/* Uma função de utilidade recursiva para resolver N
   Problema da rainha */
bool resolveNRUtil(int **mat, int col, int nu) 
{ 
     int N = nu;
     
    if (col >= N) //caso base: Se todas as rainhas são colocadas então retorne verdadeiro
        return true; 
  

    int i;
   
    for (i = 0; i < N; i++)   //Considera esta coluna e tenta colocar a rainha em todas as linhas, uma a uma 
    { 
       
        if ( colocaQueen(mat, i, col, N) )  //Verifique se a rainha pode ser colocada no tabuleiro [i] [col]
        { 
            
            mat[i][col] = 2;  //Coloca essa rainha na casa [i] [col]
  
        
            if ( resolveNRUtil(mat, col + 1, N) )     //recorrer para colocar o resto das rainhas
                return true; 
  
                /* Se colocar a rainha na casa [i] [col]
                não leva a uma solução, então
                remova a rainha fazer quadro [i] [col] */
            mat[i][col] = 0; // BACKTRACK 
           // *back=*back+1;
        }
         
    } 
  
  //Se a rainha não pode ser colocada em qualquer linha em esta colum col retorna falsa
    return false; 
} 
  
/* Esta função resolve o problema N Queen usando
   Retrocesso. Utiliza principalmente resolveNQUtil () para
   resolva o problema. Ele retorna falso se rainhas
   não pode ser colocado, caso contrário, retornar true e
   imprime colocação de rainhas na forma de 2.
   Por favor, note que pode haver mais de um
   soluções, esta função imprime uma das
   soluções viáveis. */
bool resolveNR(int **matz, int n) 
{ 
    int **mat = matz; 
    int nu=n;
 
    liberaQueen(mat,nu);//libera o tabuleiro para troca de posição
    if ( resolveNRUtil(mat, 0, nu) == false ) // condicao para verificar se a solução do tabuleiro informado é possivel
    { 
      printf("Solução não existe"); 
      return false; 
    } 
    //printf("\nNumero de backtrack realizado: %d", back); 
    imprimeSol(mat,nu); // funcao para imprimir matriz com a soluçao final

    return true; 
} 
  
void zeramat(int **mat,int n){
    int i,j; 
    int cont = 0;
    for (j = 0; j < n; j++){ // percorre a linha da matriz 
        for ( i = 0; i < n; i++){ // percorre a coluna da matriz
	       cont=i;
           mat[i][j] =0; // atribui valor zero em todas as posições da matriz  
                         // zero simboliza casa vazia no tabuleiro       
        }   
    }
}
void preencheMat(int **mat,int n){
    int i,j; 
    int r = 0;
    int r1=0;
    srand( (unsigned)time(NULL) ); // A função srand (x) define a semente do algoritmo do gerador de números aleatórios 
                                   // usado pela função rand () no caso a semente é o timer do S.O.
    for ( i = 0; i < n; i++){ // percorre todas as colunas da matriz
        r=1+rand()%n;  //seta o valor randomico e atribui a variavel r;             
        if(r<n){ // compara se o valor gerado respeita o tamanho do tabuleiro
           mat[r][i]=2; //atribui valor 2 a uma das colunas sorteadas aleatoriamente.
                        // o valor 2 é simbolicamente a representação da rainha.
           r1=r1+1;  // soma mais 1 na rais do numero randomico;
        }
    }   
}     
  
// inicio
int main() 
{ 
    int n; //variavel para armazenar numero de rainhas.
    printf("\n informe numero de rainhas: "); 
    scanf("%d",&n); // le do usuario numero de rainhas.
    printf("\n");
    int **mat;  /* declara um ponteiro de ponteiro para armazenar as linhas e colulas da matriz 
                   a ser alocada para representar o total de casas do tabuleiro*/
   
    int   l, c;   /* variavel que armazena numero de linhas e colunas da matriz que é igual a n */
    int i, j;
    l=n;
    c=n; /* inicializacao para l e c */
       
    mat = Aloca_matriz (l, c); //variavel mat recebe matriz criada na função Aloca_matriz
   
    zeramat(mat,n);// Fução que inicializa o tabuleiro vazio.
    preencheMat(mat,n); //função para colocar as rainhas de modo aleatorio no primeiro tabuleiro
    printf("Tabuleiro inicial com numero de casas igual N rainhas: %d x %d \n\n", n,n);  
    imprimeSol(mat,n); //função para imprimir primeiro tabuleiro com n rainhas 
    printf("Tabuleiro final com a solucao para %d rainhas que nao se atacam. \n\n",n);
    resolveNR(mat,n); //função para encontrar e imprimir a solução do N-rainhas
   
    return 0; 
} 


