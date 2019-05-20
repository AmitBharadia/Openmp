// C Program for Floyd Warshall Algorithm 
#include<stdio.h> 
#include <chrono>
#include <sys/time.h>
#include <stdlib.h>
#include "omp.h"
// Number of vertices in the graph 
#define V  1000
  
/* Define Infinite as a large enough value. This value will be used 
  for vertices not connected to each other */
#define INF 99999 


using namespace std::chrono; 
using namespace std; 
  
// A function to print the solution matrix 
void printSolution(int dist[][V]); 
  
// Solves the all-pairs shortest path problem using Floyd Warshall algorithm 
void floydWarshall (int graph[][V]) 
{ 
    /* dist[][] will be the output matrix that will finally have the shortest  
      distances between every pair of vertices */
    int dist[V][V], i, j, k; 
  
    /* Initialize the solution matrix same as input graph matrix. Or  
       we can say the initial values of shortest distances are based 
       on shortest paths considering no intermediate vertex. */
      
    for (i = 0; i < V; i++) 
        for (j = 0; j < V; j++) 
            dist[i][j] = graph[i][j]; 
  
    /* Add all vertices one by one to the set of intermediate vertices. 
      ---> Before start of an iteration, we have shortest distances between all 
      pairs of vertices such that the shortest distances consider only the 
      vertices in set {0, 1, 2, .. k-1} as intermediate vertices. 
      ----> After the end of an iteration, vertex no. k is added to the set of 
      intermediate vertices and the set becomes {0, 1, 2, .. k} */

    #pragma omp parallel for schedule(auto) 
    for (k = 0; k < V; k++) 
    { 
        // Pick all vertices as source one by one
       // #pragma omp parallel for 
        for (i = 0; i < V; i++) 
        { 
            // Pick all vertices as destination for the 
            // above picked source   
            //printf("Thread ID : (%d)\n",omp_get_thread_num());
            #pragma omp parallel for
            for (j = 0; j < V; j++) 
            { 
                // If vertex k is on the shortest path from 
                // i to j, then update the value of dist[i][j] 
                //printf("%d,%d + %d,%d => %d,%d  (%d)\n",i,k,k,j,i,j);
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    # pragma omp critical
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    } 
            } 
        } 
    } 
  
    // Print the shortest distance matrix 
    // printSolution(dist); 
} 
  
/* A utility function to print solution */
void printSolution(int dist[][V]) 
{ 
    printf ("The following matrix shows the shortest distances"
            " between every pair of vertices \n"); 
    for (int i = 0; i < V; i++) 
    { 
        for (int j = 0; j < V; j++) 
        { 
            if (dist[i][j] == INF) 
                printf("%5s", "INF"); 
            else
                printf ("%5d", dist[i][j]); 
        } 
        printf("\n"); 
    } 
} 

void generateMatrix(int graph[][V]){
       // printf ("Generate mattix\n");
        for(int i = 0;i < V;i++){
            for(int j = 0 ;j < V;j++){
                if(j<=i){
                    graph[i][j]=INF;
                }else{
                    graph[i][j] = rand()%1000;
                }
            }
        }
}
  
// driver program to test above function 
int main() 
{ 
     struct timeval start, end;
    /* Let us create the following weighted graph 
            10 
       (0)------->(3) 
        |         /|\ 
      5 |          | 
        |          | 1 
       \|/         | 
       (1)------->(2) 
            3           */
    // int vertices;
    // printf("Enter nuber of vertices:");
    // scanf("%d",&vertices);



    int graph[V][V];
    generateMatrix(graph);
    //printSolution(graph);
    gettimeofday(&start, NULL);
    // Print the solution 
    floydWarshall(graph); 

    gettimeofday(&end, NULL);
    double delta = ((end.tv_sec  - start.tv_sec) * 1000000u + 
    end.tv_usec - start.tv_usec) / 1;
    printf("time : %lf \n",delta); 

    return 0; 
} 