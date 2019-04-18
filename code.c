// A Multithreaded Program that implements the banker's algorithm.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

int nResources,nProcesses;
int *resources;
int **allocated;
int **maxRequired;
int **need;
int *safeSeq;
int nProcessRan = 0;

pthread_mutex_t lockResources;
pthread_cond_t condition;

// get safe sequence is there is one else return false
bool getSafeSeq();
// process function
void* processCode(void* );

int main(int argc, char** argv) {
	srand(time(NULL));

        printf("\nNumber of processes? ");
        scanf("%d", &nProcesses);

        printf("\nNumber of resources? ");
        scanf("%d", &nResources);

        resources = (int *)malloc(nResources * sizeof(*resources));
        printf("\nCurrently Available resources (R1 R2 ...)? ");
        int i;
        for(i=0; i<nResources; i++)
                scanf("%d", &resources[i]);

        allocated = (int **)malloc(nProcesses * sizeof(*allocated));
        for(i=0; i<nProcesses; i++)
                allocated[i] = (int *)malloc(nResources * sizeof(**allocated));

        maxRequired = (int **)malloc(nProcesses * sizeof(*maxRequired));
        for(i=0; i<nProcesses; i++)
                maxRequired[i] = (int *)malloc(nResources * sizeof(**maxRequired));

        // allocated
        printf("\n");
        for(i=0; i<nProcesses; i++) {
                printf("\nResource allocated to process %d (R1 R2 ...)? ", i+1);
                int j;
				for(j=0; j<nResources; j++)
                        scanf("%d", &allocated[i][j]);
        }
        printf("\n");

	// maximum required resources
        for(i=0; i<nProcesses; i++) {
                printf("\nMaximum resource required by process %d (R1 R2 ...)? ", i+1);
                int j;
				for(j=0; j<nResources; j++)
                        scanf("%d", &maxRequired[i][j]);
        }
        printf("\n");
        // calculate need matrix
        need = (int **)malloc(nProcesses * sizeof(*need));
        for(i=0; i<nProcesses; i++)
                need[i] = (int *)malloc(nResources * sizeof(**need));

        for(i=0; i<nProcesses; i++)
                {
				int j;
				for(j=0; j<nResources; j++)
                        need[i][j] = maxRequired[i][j] - allocated[i][j];
}
	// get safe sequence
	safeSeq = (int *)malloc(nProcesses * sizeof(*safeSeq));
        for(i=0; i<nProcesses; i++) safeSeq[i] = -1;

        if(!getSafeSeq()) {
                printf("\nUnsafe State! The processes leads the system to a unsafe state.\n\n");
                exit(-1);
        }

        printf("\n\nSafe Sequence Found : ");
        for(i=0; i<nProcesses; i++) {
                printf("%-3d", safeSeq[i]+1);
        }

        printf("\nExecuting Processes...\n\n");
        sleep(1); 
	}
	
