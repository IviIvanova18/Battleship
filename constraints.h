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
//good
void allNotCellXVericalandBorO(List_Clause *clauseList,bool isBoat);


//good
/* if isBoat == true :  (¬X1 ∨ ¬X5 ∨ ¬X6 ∨ ¬X7 ∨ B) 
* else (¬X1 ∨ ¬X5 ∨ ¬X6 ∨ ¬X7 ∨ ¬O) 
*/
void allNotCellXHorizontalandBorNotO(List_Clause *clauseList, bool isBoat);

//good
void notBnotOCellXVerical(List_Clause *clauseList);
void notBOCellXHorizontal(List_Clause *clauseList);
/*The boat k occupies the cells such that*/
void contiguousCell(List_Clause *clauseList);

/*There is at least one boat k*/
//good
void thereIsAtLeastOneBoatK(List_Clause *clauseList);

/*There is at most one boat k*/
//good
void thereIsAtMostOneBoatK(List_Clause *clauseList);

/*In every cell there is only one boat or section of boat.*/
//good
void oneBoatOrSectionOfBoat(List_Clause *clauseList);

void read_game_file(FILE* f, int column_list[], int line_list[]);

/*The numbers outside the grid show the number of cells occu-
pied by battleships on that row/column.*/
///No idea what is going on here///
void combinationUtil(int arr[], int data[], int start, int end,int index, int r,combination_list *comb_list);
void createCombination(int r,combination_list* comb_list);
////first two okay////
void NChosesKColumnFirstPart(List_Clause *clauseList,int column_list[]);
void NChosesKColumnSecondPart(List_Clause *clauseList,int column_list[]);
void NChosesKColumn(List_Clause *clauseList,int column_list[]);
void NChosesKLineFirstPart(List_Clause *clauseList,int line_list[]);
void NChosesKLineSecondPart(List_Clause *clauseList,int line_list[]);
void NChosesKLine(List_Clause *clauseList,int line_list[]);

/*The boats are placed so that no boat touches any other boat,
not even diagonally*/
//// no mistakes ////
void noBoatTouchesAnother(List_Clause *clauseList);
void NotBOAllNotSuroundingCellHorizintal(List_Clause *clauseList);
void SuroundingCellAndClauseHorizintal(List_Clause *clauseList, bool additionalLiteral);
void NotBOAllNotSuroundingCellVertical(List_Clause *clauseList);
void SuroundingCellAndClauseVertical(List_Clause *clauseList, bool additionalLiteral);
////////////////////

void allConstraints(List_Clause *clauseList,int column_list[],int line_list[]);

void print_Clause_DIMACS_Format(clause c, FILE *fileOut);
void print_In_DIMACS_Format(List_Clause *clauseList, FILE *fileOut);

void nonExistingBoat(List_Clause *clauseList);
void nonExistingCell(List_Clause *clauseList);


#endif 