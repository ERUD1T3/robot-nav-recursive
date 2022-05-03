/*

  Author: Josias Moukpe
  Email: jmoukpe2016@my.fit.edu 
  Course: cse2010
  Section: 14
  Description: Program gets list of destinations from a file and output 
  the combination of the destination that yields the shortest route from
  and to the packing station and goes through all the destinations
  
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "robot_utils.h"

int main(int argc, char** argv)
{

  //keeps track of the length of the lines
  size_t len = 0;             

  //the input line charracter array                   
  char* input_line = NULL; 

  //capture the input file name as second command line argument                       
  char* infile = argv[1];                         

  //pointer the input file
  FILE* fp = fopen(infile, "r");                  

  //tracks the number of destination for the robot to go to 
  uint n_dest = 0;                                

  /*
    L36-41: exits program if file ptr is null ie no file was found
   */
  if(fp == NULL) {
      printf("\nError: failed to open file.\n");
      exit(EXIT_FAILURE);
  }


  /*
    L47-48: read the first input line to obtain the number of destination
    to which we then add 1 since robot has to return to starting position
   */  
  getline(&input_line, &len, fp);
  n_dest = 1 + atoi(input_line);

  //creating minpath list to track the destination sequence that yielded that minimal length
  LocList* minpath = initLocList(); 

  //creating unvisited list to store the destination
  LocList* unvisited = initLocList();


  /*
    L62-66: read the input file exactly number of destination times
    and store the destination a pointer to a location struct in unvisited
    Last pushback at L66 adds start station at the end of unvisited
  */ 
  for(uint i = 0; i < n_dest - 1; ++i) {
    getline(&input_line, &len, fp);
    pushback(unvisited, getLocation(parseWords(input_line)));
  }
  pushback(unvisited, getAt(unvisited, 0));


  //tracks the length of the min_dist, is originally set the max double value
  double min_dist = __DBL_MAX__;
  
  /*
    L78-79: calls pathFinder to obtain the mininum path 
    then print the minpath as well as its length
    the path is printed by path_length(args....)
  */ 
  pathFinder(&min_dist, n_dest, minpath, unvisited);
  printf("%.2lf\n", path_length(minpath, true));

  /*
    L85-87:garbage collection through deallocation of memory 
    and closing of file pointer
  */
  destroy(minpath);
  destroy(unvisited);
  fclose(fp);

  return EXIT_SUCCESS;
}
