#include <stdio.h>
#include <time.h>  

int main() {
    unsigned int i;
    unsigned int count[10] = {0,0,0,0,0,0,0,0,0,0};
    unsigned int perfectCount[10] = {0,0,0,0,0,0,0,0,0,0};
    unsigned int max = 101;
    srand(time(NULL));
    
    for(i=0;i<max;i++)
        count[rand() % 10]++;
        
    for(i=0;i<max;i++)
        perfectCount[i % 10]++;
    printf("Contagem distribuida----------\n");            
    for(i=0;i<10;i++)
        printf(" [%d] = %d \n",i+1,perfectCount[i]);
    printf("Contagem aleatória------------\n");            
    for(i=0;i<10;i++)
        printf(" [%d] = %d \n",i+1,count[i]);
        
    printf("------------------------\n");
    printf("\n");
    printf("\n");
    printf("Prob aleatória------------\n");            
    for(i=0;i<10;i++)
        printf(" [%d] = %f \n",i+1,(float)perfectCount[i]/(float)max);
    printf("---\n");
    for(i=0;i<10;i++)
        printf(" [%d] = %f \n",i+1,(float)count[i]/(float)max);
    printf("------------------------\n");


    for(i=0;i<10;i++)
        printf(" [%d] = %d \n",i+1,perfectCount[i] - count[i]);
    printf("Desvio---------\n");
    for(i=0;i<10;i++)
        printf(" [%i] = %f \n",i+1,1-((float)perfectCount[i]/(float)count[i]));
    return 0;
    
    
}