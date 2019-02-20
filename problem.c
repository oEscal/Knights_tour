#include<stdio.h>
#include<stdlib.h>

#define SAVE_DOC 1                                                                                                      //boolean value: if true (>0), the horse's routes are saved to a file; if false (<=0), nothing is saved

const unsigned long MAX_SAVE = 100;                                                                                     //max number of grids to save (because, in some cases, there are a lot of routes, wich resuts in a big data file if all of them are saved)
unsigned long num_paths_saved = 0;                                                                                      //current number of saved paths
FILE *file;

const short MOVEMENT_1 = 2;
const short MOVEMENT_2 = 1;

unsigned int grid_size[2];
unsigned int **grid;

int horse_position[2];
int target_position[2];


/* Recursive function, where are calculated all the horse's possible moviments for a giver chess board (grid)
 *
 * Arguments:
 *    -> short move_x: horse's movement in grid's x axes
 *    -> short move_y: horse's movement in grid's y axes
 *    -> int step: current horse's step (useful to store in grid's array)
 *    -> short pass_throw_every_sqare: boolean value -> if true (>0), the horse is forced to visit every sqare of chess board; if false (<=0), the horse isn't forced to do that
 * Return:
 *    -> number of all different possible routes
 */
unsigned long long move(short move_x, short move_y, int step, short pass_throw_every_sqare){

   int new_position[] = {horse_position[0] + move_x,                                                                    //calc of new possible horse's position in the board
                         horse_position[1] + move_y};

   if(new_position[0] == target_position[0] &&                                                                          //verify if the horse reached the target (if so, the number of possible routes is increased by one and if SAVE_DOC > 0, the grid with that route is stored in the data file)
      new_position[1] == target_position[1]){

      if(!pass_throw_every_sqare ||                                                                                     //verify if the grid is completely filled (because if pass_throw_every_sqare > 0, the horse must visit all board's squares)
         grid[horse_position[0]][horse_position[1]] == grid_size[0]*grid_size[1]){
         
         if(SAVE_DOC && (num_paths_saved < MAX_SAVE)){
            num_paths_saved++;
            for(int n1 = 0; n1 < grid_size[0]; n1++){
               for(int n2 = 0; n2 < grid_size[1]; n2++)
                  fprintf(file, "%d\t", grid[n1][n2]);
               fprintf(file, "\n");
            }
            fprintf(file, "\n");
         }
         
         return 1;
      }

   }

   if(new_position[0] < 0 || new_position[1] < 0 ||                                                                     //verify if horse don't go outside the grid
      new_position[0] > (grid_size[0] - 1) || new_position[1] > (grid_size[1] - 1) ||                                   //verify if horse don't go outside the grid
      grid[new_position[0]][new_position[1]] != 0)                                                                      //verify if the horse already has been in that position
      return 0;


   unsigned long long num_success = 0;                                                                                  //variable where is stored all the horse's routes for all the recursive calls of this function

   int last_horse_position[] = {horse_position[0], horse_position[1]};                                                  //for backtracking
   
   horse_position[0] = new_position[0];                                                                                 //update horse's x position
   horse_position[1] = new_position[1];                                                                                 //update horse's y position
   
   grid[horse_position[0]][horse_position[1]] = ++step;                                                                 //save new horse's position in the grid's array (with current step)
   int last_horse_position_marked[] = {horse_position[0], horse_position[1]};                                           //for backtracking

   /**************** all possible movements ****************/
   num_success += move(MOVEMENT_1, MOVEMENT_2, step, pass_throw_every_sqare);
   num_success += move(MOVEMENT_1, -MOVEMENT_2, step, pass_throw_every_sqare);
   num_success += move(-MOVEMENT_1, -MOVEMENT_2, step, pass_throw_every_sqare);
   num_success += move(-MOVEMENT_1, MOVEMENT_2, step, pass_throw_every_sqare);

   num_success += move(MOVEMENT_2, MOVEMENT_1, step, pass_throw_every_sqare);
   num_success += move(MOVEMENT_2, -MOVEMENT_1, step, pass_throw_every_sqare);
   num_success += move(-MOVEMENT_2, -MOVEMENT_1, step, pass_throw_every_sqare);
   num_success += move(-MOVEMENT_2, MOVEMENT_1, step, pass_throw_every_sqare);


   /**************** backtracking ****************/
   horse_position[0] = last_horse_position[0];
   horse_position[1] = last_horse_position[1];
   grid[last_horse_position_marked[0]][last_horse_position_marked[1]] = 0;


   return num_success;

}

int main(){
   /**************** initializations ****************/
   short PASS_THROW_EVERY_SQUARE = 0;                                                                                   //boolean value -> if true (>0), the horse is forced to visit every sqare of chess board; if false (<=0), the horse isn't forced to do that

   grid_size[0] = 5;                                                                                                    //width of chess board in number of squares 
   grid_size[1] = 5;                                                                                                    //height of chess board in number of squares

   grid = (unsigned int **)malloc(grid_size[0]*sizeof(unsigned int *));                                                 //chess board initialized with zeros in all squares
   for(int num = 0; num < grid_size[0]; num++)
      grid[num] = (unsigned int *)calloc(grid_size[1], sizeof(unsigned int));

   horse_position[0] = 2;                                                                                               //x coordinate of horse (initialized with its initial position), according to board's size in squares
   horse_position[1] = grid_size[1] - 1;                                                                                //y coordinate of horse (initialized with its initial position), according to board's size in squares

   target_position[0] = grid_size[0];                                                                                   //x coordinate of target (initialized with its initial position), according to board's size in squares
   target_position[1] = 2;                                                                                              //y coordinate of target (initialized with its initial position), according to board's size in squares


   /**************** problem's resolution ****************/
   if(SAVE_DOC){                                                                                                        //open the file where is to be stored the data about the horse's route
      char *file_name = malloc(10);
      sprintf(file_name, "%dx%d.txt", grid_size[0], grid_size[1]);
      file = fopen(file_name, "w");
      free(file_name);
   }

   printf("%llu\n", move(0, 0, 0, PASS_THROW_EVERY_SQUARE));                                                            //start the horse's course, with no movement, because the initial position of the horse is not stored in the grid

   if(SAVE_DOC)                                                                                                         //close the file where is to be stored the data about the horse's route
      fclose(file);

}