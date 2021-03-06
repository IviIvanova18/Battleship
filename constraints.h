#include <stdio.h>	
#include <stdlib.h>	
#include <stdbool.h>	
#include <assert.h>	
#include <string.h>	
#include "types.h"	

#ifndef _CONSTRAINTS_H_	
#define _CONSTRAINTS_H_	

#define iTest 1	
#define jTest 1	
#define kTest 0	

extern int GridSizeHeight, GridSizeWidth;	
extern int StartBoat, BoatCount;	

/*Boat Existence*/	

/*depending on the k returns the size of thr boat	
* k in 1...3 -> TinyBoat -> 1	
* k in 4...6 -> SmallBoat -> 2	
* k in 7,8 -> MediumBoat ->3	
* k in 9 -> BigBoat -> 4	
*/	
int matchKBoatToNSizeofK(int k);	

/* if isBoat == true :(¬X1 ∨ ¬X2 ∨ ¬X3 ∨ ¬X4 ∨ B)	
* else : (¬X1 ∨ ¬X2 ∨ ¬X3 ∨ ¬X4 ∨ O)	
*/	
void allNotCellXVericalandBorO(List_Clause *clauseList, bool isBoat);	


/* if isBoat == true :  (¬X1 ∨ ¬X5 ∨ ¬X6 ∨ ¬X7 ∨ B)	
* else (¬X1 ∨ ¬X5 ∨ ¬X6 ∨ ¬X7 ∨ ¬O) 	
*/	
void allNotCellXHorizontalandBorNotO(List_Clause *clauseList, bool isBoat);	


void notBnotOCellXVerical(List_Clause *clauseList);	

void notBOCellXHorizontal(List_Clause *clauseList);	

/*The boat k occupies the cells such that*/	
void contiguousCell(List_Clause *clauseList);	

/*There is at least one boat k*/	
void thereIsAtLeastOneBoatK(List_Clause *clauseList);	

/*There can not be two boats in the same square*/	
void onlyOneBoatInCell(List_Clause *clauseList);	

/*There is at most one boat k*/	
void thereIsAtMostOneBoatK(List_Clause *clauseList);	

/*In every cell there is only one boat or section of boat.*/	
void oneBoatOrSectionOfBoat(List_Clause *clauseList);	

/*Reads the grid from file*/	
void read_game_file(FILE *f, int column_list[], int line_list[],int *L, int *H, int *startBoat, int *lastBoat);	

/*The numbers outside the grid show the number of cells occupied by battleships on that row/column.*/	
void combinationUtil(int arr[], int data[], int start, int end, int index, int r, combination_list *comb_list);	

/*All possible combination r out of array of size 'lenght'*/	
void createCombination(int r, combination_list *comb_list, int lenght);	

/*Transforms all combination in CNF format*/	
int KChosesNCNF(FILE *file, int row_list[], bool row);	

/*The boats are placed so that no boat touches any other boat,	
not even diagonally*/	
void noBoatTouchesAnother(List_Clause *clauseList);	

void NotBOAllNotSuroundingCellHorizintal(List_Clause *clauseList);	

void SuroundingCellAndClauseHorizintal(List_Clause *clauseList, bool additionalLiteral);	

void NotBOAllNotSuroundingCellVertical(List_Clause *clauseList);	

void SuroundingCellAndClauseVertical(List_Clause *clauseList, bool additionalLiteral);	

/*Calls all constraints one after another*/	
void allConstraints(List_Clause *clauseList, int column_list[], int line_list[]);	

void print_Clause_DIMACS_Format(clause c, FILE *fileOut);	

void print_Clause_DIMACS_Format2(clause c, FILE *fileOut);	

void print_In_DIMACS_Format(List_Clause *clauseList, FILE *fileOut, int count);	

/*Returns boats that can never be created because they won't fit inside the grid*/	
void nonExistingBoat(List_Clause *clauseList);	


#endif 	