#include <stdio.h>
#include <time.h>  
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define LEFTMASK 15 // 00001111
#define RIGHTMASK 240 // 11110000
#define SEEDPAD 100


//funções da encriptação e decriptação
unsigned char sbox4bits(unsigned char bits);
unsigned char inv_sbox4bits(unsigned char bits);
void applySbox(unsigned char *bits16); //pega 16 bits e aplica a SBox
void inv_applySbox(unsigned char *bits16); //pega 16 bits e aplica a SBox
void perm16bits(unsigned char *bits16); //pega 16 bits e aplica permutação
void inv_perm16bits(unsigned char *bits16);
void oneRound(unsigned char *m ,unsigned char *key, unsigned char msgSize);
void inv_oneRound(unsigned char *m , unsigned char *key , unsigned char msgSize);
void encryptMessage(unsigned char msgSize,unsigned char **keys,unsigned char rounds);
void decryptMessage(unsigned char msgSize,unsigned char **keys,unsigned char rounds);

//Funções de teste
void genMessages(int n , int msgSize , int seed); //n: quantidade de msg|msgSize: tamanho de cada msg
unsigned char** genRandomBit(int rounds,int keySize,int seed); //gera chaves aleatórias e retorna a matriz rounds x keySize

//Funções de análise
unsigned char* getLinComb4Bits();
unsigned char** getLinAproxTab(unsigned char *linComb, unsigned char intBitsQty , unsigned char outBitsQty);
void showLineAproxTable16Bits(unsigned char **linAprox);
int main() {
    int i , j;
    int qntMsg = 4000;
    int rounds = 5;
    int keySize = 2;
    unsigned char msgSize = 2;
    unsigned char **keys = NULL;
    unsigned char **message = NULL;
    unsigned char *crypted = NULL;
    unsigned char *linComb = NULL;
    unsigned char **linAprox = NULL;
    
    
    unsigned char vector8bits[3] = {'M','A','\0'};
    unsigned char key[3] = {3,28,'\0'};
    //printf("%s\n",vector8bits);
    //printf("%d|%d\n",vector8bits[0],vector8bits[1]);
    //applySbox(vector8bits);
    //printf("%d|%d\n",vector8bits[0],vector8bits[1]);
    
   // genMessages(qntMsg,msgSize,SEEDPAD);
    
    
    
   keys = genRandomBit(rounds,keySize,SEEDPAD+1);

/*
    char c;
    FILE *fp;    
    fp = fopen("message.txt","r");
        while(1){
            c = fgetc(fp);
            if( feof(fp) ){ 
                break ;
            }
            if(c == '\n')
                printf("\n");
            else
                printf("%d ", c);
        }
    printf("\n%c = %d",3,3);
*/
    
    linComb = getLinComb4Bits();
    
    linAprox = getLinAproxTab(linComb , 4 , 4);
    //showLineAproxTable16Bits(linAprox);
    
    /*
    
    for(i=0;i<16;i++){
        for(j=0;j<16;j++){
            printf("%d \t" ,((int)linAprox[i][j]) - 8);
        }
        printf("\n");
    }
    */
    /*
    FILE *m;
    unsigned char c;
    char stopper = 1;
    m = fopen("message.txt","r");
    while(stopper){
        c = fgetc(m);
        if(feof(m)){
            stopper = 0;
            printf("Aqui chamado");
            break;
        }
        printf("%d ",c);
    }
    */
    
    /*
    FILE *m;
    unsigned char c;
    int nnnn;
    int controle = 0;;
    m = fopen("message.txt","w+");
    while(controle == 0){
        printf("Ini\n");
        scanf("%d",&nnnn);
        c = nnnn;
        fputc(c,m);
        printf("\n Controls");
        scanf("%d",&controle);
    }
    fclose(m);
    */
    
    encryptMessage(msgSize,keys,rounds);
    decryptMessage(msgSize,keys,rounds);
    
    /*
    unsigned char c[] = {'H','A'};
    unsigned char **ckey = malloc(2*sizeof(unsigned char *));
    ckey[0] = malloc(2*sizeof(unsigned char));
    ckey[1] = malloc(2*sizeof(unsigned char));
    ckey[0][0] = 'S';
    ckey[0][1] = 'H';
    ckey[1][0] = 'A';
    ckey[1][1] = 'D';
    
    encryptMessage(msgSize,ckey,(unsigned char)2);
    decryptMessage(msgSize,ckey,(unsigned char)2);
    */
    
    
    return 0;
    
    
}

unsigned char sbox4bits(unsigned char bits){
    unsigned char sbox[16] = {2,8,13,5,4,10,12,15,14,3,11,9,7,1,6,0};
    bits = sbox[bits];
    return bits;
}

unsigned char inv_sbox4bits(unsigned char bits){
    unsigned char sbox[16] = {15,13,0,9,4,3,14,12,1,11,5,10,6,2,8,7};
    bits = sbox[bits];
    return bits;
}

void applySbox(unsigned char *bits16){
    unsigned char one = LEFTMASK & (*bits16 >> 4); //4 + significativo
    unsigned char two = LEFTMASK & (*bits16);
    
    //printf("8 primeiros bits em decimal: %d\n",*bits);
    *bits16++;
    //printf("8 últimosbits em decimal: %d\n",*bits);
    
    unsigned char three = LEFTMASK & (*bits16 >> 4);
    unsigned char four = LEFTMASK & (*bits16); //4 - significativo
    /*
    printf("one: %d\n",one);
    printf("two: %d\n",two);
    printf("three: %d\n",three);
    printf("four: %d\n",four);
    printf("one: %d\n",sbox4bits(one));
    printf("two: %d\n",sbox4bits(two));
    printf("three: %d\n",sbox4bits(three));
    printf("four: %d\n",sbox4bits(four));
    */
    unsigned char left = (sbox4bits(one) << 4) | sbox4bits(two);
    unsigned char right = (sbox4bits(three) << 4) | sbox4bits(four);
    /*
    printf("left: %d\n",left);
    printf("right: %d\n",right);
    //(left << 8) | right
    */
    *bits16 = right;
    *bits16--;
    *bits16 = left;
}

void inv_applySbox(unsigned char *bits16){

    unsigned char one = LEFTMASK & (*bits16 >> 4); //4 + significativo
    unsigned char two = LEFTMASK & (*bits16);
    
    *bits16++;
    
    unsigned char three = LEFTMASK & (*bits16 >> 4);
    unsigned char four = LEFTMASK & (*bits16); //4 - significativo
   
    unsigned char left = (inv_sbox4bits(one) << 4) | inv_sbox4bits(two);
    unsigned char right = (inv_sbox4bits(three) << 4) | inv_sbox4bits(four);

    *bits16 = right;
    *bits16--;
    *bits16 = left;
}


void perm16bits(unsigned char *bits16){
    unsigned char permArray[16] = {0,4,8,12,1,5,9,13,2,6,10,14,3,7,11,15};
    unsigned int result = 0;
    int i = 0;
    
    for(i=0;i<8;i++){
        result = ((((1 << (7-i)) & *bits16) >> (7-i)) << 15-permArray[i]) | result;
    }
    bits16++;
    for(i=0;i<8;i++){
        result = ((((1 << (7-i)) & *bits16) >> (7-i)) << 15-permArray[i+8]) | result;
        
    }
    *bits16 = result & 255 ; // Apaga os 8 bits significativos
    bits16--;
    *bits16 = (result >> 8); //Desloca os 8 bits significativos para direita;
    
}

void inv_perm16bits(unsigned char *bits16){ // para este caso a inversa da permutação é ela mesma
    perm16bits(bits16);
}

void oneRound(unsigned char *m , unsigned char *key , unsigned char msgSize){
    int i;
    for(i=0;i<msgSize;i++)
        m[i] ^= key[i];

    applySbox(m);

    perm16bits(m);

}



void inv_oneRound(unsigned char *m , unsigned char *key , unsigned char msgSize){
   
    int i;

    inv_perm16bits(m);
    inv_applySbox(m);    
    
    
    for(i=0;i<msgSize;i++)
        m[i] ^= key[i]; 

    

}


void encryptMessage(unsigned char msgSize,unsigned char **keys,unsigned char rounds){
    int i;
    unsigned char c,*m;
    char stopper = 1;
    m = malloc(msgSize*sizeof(unsigned char));
    FILE *message,*cyph;    
    cyph =  fopen("cyph.txt","w+");
    message = fopen("message.txt","r");
        while(stopper){
            for(i=0;i<msgSize;i++){
                m[i] =0;
                
            }
                
            for(i=0;i<msgSize;i++){
                c = fgetc(message);
                m[i] = c;
                if( feof(message) ){ 
                    stopper = 0;
                    m[i] = 0;
                    if(i==0){
                        fclose(cyph);
                        fclose(message);
                        return;
                    }
                }
                
            }
            
            for(i=0;i<rounds-1;i++)
                oneRound(m,keys[i],msgSize);
            
            
            for(i=0;i<msgSize;i++)
                m[i] ^= keys[rounds-1][i];   
            
            for(i=0;i<msgSize;i++)
                fputc(m[i],cyph);    
            
            
        }
    fclose(message);
    fclose(cyph);
}

void decryptMessage(unsigned char msgSize,unsigned char **keys,unsigned char rounds){
    int i;
    unsigned char c,*m;
    char stopper = 1;
    m = malloc(msgSize*sizeof(unsigned char));
    FILE *message,*cyph;    
    cyph =  fopen("cyph.txt","r");
    message = fopen("DecrMessage.txt","w+");
        while(stopper){
            for(i=0;i<msgSize;i++)
                m[i] =0;
                
                
            for(i=0;i<msgSize;i++){
                c = fgetc(cyph);
                m[i] = c;
                if( feof(cyph) ){ 
                    stopper = 0;
                    m[i] = 0;
                    if(i==0){
                        fclose(cyph);
                        fclose(message);
                        return;
                    }
                    
                }
            }
            
            
            for(i=0;i<msgSize;i++)
                m[i] ^= keys[rounds-1][i];   
            
                
            for(i=0;i<rounds-1;i++)
                inv_oneRound(m,keys[rounds-2-i],msgSize);
                
                
            for(i=0;i<msgSize;i++)
                fputc(m[i],message);    
                
                
            
        }
    fclose(message);
    fclose(cyph);
}

void genMessages(int n , int msgSize , int seed){
    FILE *fp;
    int i,j;
    char message;
    srand(seed);
    fp = fopen("message.txt","w+");
    fprintf(fp,"%d n msg de msgSize bytes",n);
    for(i = 0; i<n;i++){
        for(j=0;j<msgSize;j++){
            do{
               message = rand(); //n msg de tamanho msgSize*1byte por linha
            }
            while(message > 255 || message < 0);
            fputc(message,fp);
        }
    }
    fclose(fp);
}





unsigned char** genRandomBit(int rounds,int keySize,int seed){
    int i,j,tempKey;
    unsigned char **keys;
    srand(seed);
    
    keys = (unsigned char **)malloc(rounds*sizeof(unsigned char *));
    for(i=0;i<rounds;i++){
            keys[i] = (unsigned char *)malloc((1+keySize)*sizeof(unsigned char));
        
    }
    
    
    for(i=0;i<rounds;i++){
        for(j=0;j<keySize;j++){
                do{
                   tempKey = rand(); //n msg de tamanho msgSize*1byte por linha
                }
                while(tempKey > 255 || tempKey < 0);
                keys[i][j] = tempKey;
            }
             keys[i][j] = '\0';
    }
    return keys;
}


unsigned char* getLinComb4Bits(){
    unsigned char *linComb;
    int i;
    unsigned char bitsLength = 4;
    unsigned char decimalLimits = (1<<bitsLength);
    
    linComb = malloc(decimalLimits*sizeof(unsigned char));
    
    
    for(i=0;i<decimalLimits;i++){
        linComb[i] = sbox4bits(i); // Se for necessário garantir: linComb[i] = sbox4bits(i & (decimalLimits-1));
    }
    
    return linComb;
}



unsigned char** getLinAproxTab(unsigned char *linComb, unsigned char intBitsQty , unsigned char outBitsQty){
    unsigned char **linAprox;
    int i,j,k,l;
    unsigned char inQuery; //intBitsQty dim
    unsigned char outQuery; //outBitsQty dim
    unsigned int result;
    unsigned char inDecimalLimits = (1<<intBitsQty);
    unsigned char outDecimalLimits = (1<<outBitsQty);
    
    linAprox = malloc(inDecimalLimits*sizeof(unsigned char*));
    
    
    for(i=0;i<inDecimalLimits;i++){
        linAprox[i] = malloc(outDecimalLimits*sizeof(unsigned char));
    }
    
    for(j=0;j<inDecimalLimits;j++){
        for(k=0;k<outDecimalLimits;k++){
            linAprox[j][k] = 0;
        }
    }
    
    //j e k são os bits selecionados para análise
    
    for(j=0;j<inDecimalLimits;j++){
        for(k=0;k<outDecimalLimits;k++){
            for(i=0;i<inDecimalLimits;i++){
                
                inQuery = i & j;
                outQuery = linComb[i] & k;
                //resultQuery = (inQuery << outBitsQty) | outQuery;
                result = 0;
                for(l=0;l<intBitsQty;l++)
                    result = result ^ (1 & (inQuery>>l));
                for(l=0;l<outBitsQty;l++)
                    result = result ^ (1 & (outQuery>>l));
                
                if(result == 0)
                    linAprox[j][k]++; // Quando i & j = linComb[i] & k -> (i & j) ^ (linComb[i] & k) = 0;
            }
        }
    }
    
    return linAprox;
}


void showLineAproxTable16Bits(unsigned char **linAprox){
    int i , j;
    printf(" \t");
    for(i=0;i<16;i++)
        printf("%d \t",i);
    printf("\n");
    for(i=0;i<16;i++){
        printf("%d \t",i);
        for(j=0;j<16;j++){
            printf("%d \t" ,((int)linAprox[i][j]) - 8);
        }
        printf("\n");
    }
}

/*
void listFreq(unsigned int inLinComb , unsigned int outLinComb ,unsigned char msgSize){
    int i;
    unsigned char stopper = 1;
    char c;
    FILE *message,*cyph;    
    cyph =  fopen("cyph.txt","w+");
    message = fopen("message.txt","r");
        while(stopper){
            for(i=0;i<msgSize;i++)
                m[i] =0;
                
                
            for(i=0;i<msgSize;i++){
                c = fgetc(message);
                if( feof(message) ){ 
                    stopper = 0;
                }
                m[i] = c;
            }
            
                
            for(i=0;i<rounds;i++)
                oneRound(m,keys[i],msgSize);
                
                
            for(i=0;i<msgSize;i++)
                fputc(m[i],cyph);    
                
                
            
        }
    fclose(message);
    fclose(cyph);
}*/
