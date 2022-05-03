#ifndef ROBOT_UTILS
#define ROBOT_UTILS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "SLinkedList.h" 
#include "LocList.h"




location* initLoc(char* loc_name, uint x, uint y); //location constructor
SLList* parseWords(char* line); //parse the words in line into a list
location* getLocation(SLList* cmd); //Creates a location struct from the command
double distance(location* loc1, location* loc2); //computes the distance between two locations
double path_length(LocList* path, bool to_print); //computes the minimum path
void pathFinder(double* min_dist, uint rem_dest, LocList* minpath, LocList* unvisited); //utilizes min path finder to output a path
void pathShuffler( //recursively find the path from and to start station
    double* min_dist, //reference to minimum path length
    uint rem_dest, //remaining destinations to visit
    LocList* minpath, //reference to the minimum path list 
    LocList* visited, //reference to the list of visited locations
    LocList* unvisited, //reference to the list of unvisited locations
    location* start_station); //reference to the starting station locatio






void pathFinder(double* min_dist, uint rem_dest, LocList* minpath, LocList* unvisited) {

    /*
    * Computes the minimum path by calling pathShuffler on unvisited without start station
    */

    LocList* reduced_unvisited = initLocList(); //to contain all destinations beside packing_station
    LocList* visited = initLocList();  //to contain the list of visited destinations

    //populates the reduced_unvisited list with all the destinations except packing_station
    for(uint i = 1; i < unvisited->size - 1; ++i) pushback(reduced_unvisited, getAt(unvisited, i));

    //call pathShuffler to shuffle the destinations combination around and output the mininum path
    pathShuffler(min_dist, rem_dest - 2, minpath, visited, reduced_unvisited, getAt(unvisited, 0));
    
    destroy(reduced_unvisited); //garbage collection of reduced_unvisited
    destroy(visited); //garbage collection of visited
    
}

void pathShuffler(double* min_dist, uint rem_dest, LocList* minpath, LocList* visited, LocList* unvisited, location* start_station) {
    /*
    * recursively find the path with the minimum distance
    */


    for(uint i = 0; i < unvisited->size; ++i) { //for all elements of unvisited
        location* curr_loc = popfront(unvisited);  //remove from unvisited
        pushback(visited, curr_loc); //to add to visited

        if(rem_dest == 1) { //all the destinations have be assigned to visited

            pushfront(visited, start_station); //add packing_station to start of path
            pushback(visited, start_station);  //add packing_station to end of path

            double curr_len = path_length(visited, false); //compute and store length visited path

            if(curr_len <= *min_dist) { //visied path length is shorter of equal to minimum path length
                *min_dist = curr_len; //update minimum path length with curr_len
                reset(minpath); //clear the previous minimum path
                
                LocList* reversed = reverseList(visited);  //reverse the visited path, to see if reversed alphabetically precedes 
                if(strcmp(((getAt(reversed, 1))->loc_name), 
                    ((getAt(visited, 1))->loc_name))  < 0) //true if reversed precedes
                    copy(minpath, reversed); //copy content of reversed into minpath
                else copy(minpath, visited); //otherwise, just copy visited into minpath
                destroy(reversed); //clean memory of reversed
                
            } 

            popfront(visited); //remove packing_station from start of visited
            popback(visited); //remove packing_station from end of visited so we can try another combination

        } 

        else { //not all destinations have been assigned

            //recursively call pathShuffler to continue assigning destinations
            pathShuffler(min_dist, rem_dest - 1, minpath, visited, unvisited, start_station); 

        }

        pushback(unvisited, curr_loc); //put the current location curr_loc at the back of unvisited
        popback(visited); //remove curr_loc from visied

    }
   
}


location* initLoc(char* loc_name, uint x, uint y) {
    /*
    *   Location constructor
    *   Creates a location pointer and assign its values
    */
    location* loc = (location*)malloc(sizeof(location)); //allocate memory for a location 
    strcpy(loc->loc_name, loc_name); //setup location name
    loc->loc_X = x; //setup location x coordinate
    loc->loc_Y = y; //setup location y coordinate
    return loc; //return pointer to location
}

SLList* parseWords(char* line) {
    /*
    * Parses the input line for relevant commands
    */ 
    SLList* tmp = initList(); //command created with be used by then freed by parseCmd()

    char* word_token;
    char* delim = " \n";

    //get the first token 
    word_token = strtok(line, delim);

    //walk through other tokens 
    while(word_token != NULL) {
        //add new words to end of the list
        _pushback(tmp, word_token); 
        word_token = strtok(NULL, delim);
    }

    return tmp; //return pointer to list containing commands
} 

location* getLocation(SLList* cmd) { 
    /*
    *  Creates a location struct from the list command cmd
    */
    location* loc = initLoc(
        _getAt(cmd,0), //gets location name
        atoi(_getAt(cmd,1)), //gets location x coordinate
        atoi(_getAt(cmd,2)) //gets location y coordinate
        );
    _destroy(cmd); //clear memory of the cmd
    return loc; //return pointer to created location 
}

double distance(location* loc1, location* loc2) {
    /*
    * Computes the staightline distance between two set of coordinates
    */
    return sqrt(
        pow(((double)loc2->loc_Y - loc1->loc_Y), 2) + 
        pow(((double)loc2->loc_X - loc1->loc_X), 2)
        );
}

double path_length(LocList* path, bool to_print) {
    /*
        computes a path length
    */

    if(path->size == 0) return 0.0; //return zero if the patn doesn't contain any destinations

    double total_len = 0; //tracks total path length
    
    if(to_print) { //if as you compute the path you want to print it
        printf("%s %d %d %.2lf\n", 
        path->head->data->loc_name, 
        path->head->data->loc_X, 
        path->head->data->loc_Y, 0.00);
    } 
    for(uint i = 0, j = 1; j < path->size; ++i, ++j) {
        double dist = distance(getAt(path, i), getAt(path, j));
        if(to_print) { //if as you compute the path you want to print it
            location* current = getAt(path, j);
            printf("%s %d %d %.2lf\n", current->loc_name, current->loc_X, current->loc_Y, dist);
        }
        total_len += dist;
    }
    return total_len; //tracks total path length
}

#endif //ROBOT_UTILS