// C Program for Floyd Warshall Algorithm 
#include<stdio.h> 
#include <chrono>
#include <sys/time.h>
#include <stdlib.h>
#include "omp.h"

// Number of vertices in the graph 
#define V 5000
  
/* Define Infinite as a large enough value. This value will be used 
  for vertices not connected to each other */
#define INF 99999 


using namespace std::chrono; 
using namespace std; 
int *graph;
// // A function to print the solution matrix 
// void printSolution(int dist[][V]); 
  
// // Solves the all-pairs shortest path problem using Floyd Warshall algorithm 
void floydWarshall () 
{ 
    /* dist[][] will be the output matrix that will finally have the shortest  
      distances between every pair of vertices */
    int *dist, i, j, k; 
    dist=(int *) malloc(V * V * sizeof(int));
    /* Initialize the solution matrix same as input graph matrix. Or  
       we can say the initial values of shortest distances are based 
       on shortest paths considering no intermediate vertex. */
       
    for (i = 0; i < V; i++) 
        for (j = 0; j < V; j++) 
            dist[i*V+j] = graph[i*V+j]; 
  
    /* Add all vertices one by one to the set of intermediate vertices. 
      ---> Before start of an iteration, we have shortest distances between all 
      pairs of vertices such that the shortest distances consider only the 
      vertices in set {0, 1, 2, .. k-1} as intermediate vertices. 
      ----> After the end of an iteration, vertex no. k is added to the set of 
      intermediate vertices and the set becomes {0, 1, 2, .. k} */
   // #pragma omp parallel for schedule(dynamic)
    for (k = 0; k < V; k++) 
    { 
        // Pick all vertices as source one by one 
        for (i = 0; i < V; i++) 
        { 
            // Pick all vertices as destination for the 
            // above picked source 
           // #pragma omp parallel for
            for (j = 0; j < V; j++) 
            { 
                // If vertex k is on the shortest path from 
                // i to j, then update the value of dist[i][j] 
                if (dist[i*V+k] + dist[k*V+j] < dist[i*V+j]) 

                    dist[i*V+j] = dist[i*V+k] + dist[k*V+j]; 
            } 
        } 
    } 
  
    // Print the shortest distance matrix 
    //printSolution(dist); 
} 
  
// /* A utility function to print solution */
// void printSolution(int dist[][V]) 
// { 
//     printf ("The following matrix shows the shortest distances"
//             " between every pair of vertices \n"); 
//     for (int i = 0; i < V; i++) 
//     { 
//         for (int j = 0; j < V; j++) 
//         { 
//             if (dist[i][j] == INF) 
//                 printf("%5s", "INF"); 
//             else
//                 printf ("%5d", dist[i][j]); 
//         } 
//         printf("\n"); 
//     } 
// } 

void generateMatrix()
{
        graph = (int *) malloc(V * V * sizeof(int));
        printf ("Generate mattix\n");
        for(int i = 0;i < V;i++){
            for(int j = 0 ;j < V;j++){
                if(j<=i){
                    graph[i * V + j]=INF;
                }else{
                    graph[i * V + j] = rand()%1000;
                }
                //printf("%d ", graph[i * V + j]);
            }
            //printf("\n ");
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




    generateMatrix();
     //printSolution(graph);
     gettimeofday(&start, NULL);
    
    floydWarshall(); 

    gettimeofday(&end, NULL);
    double delta = ((end.tv_sec  - start.tv_sec) * 1000000u + 
    end.tv_usec - start.tv_usec) / 1.e6;
    printf("time : %lf \n",delta); 

    return 0; 
} 