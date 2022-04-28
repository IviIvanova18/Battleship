#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "types.h"

#ifndef _CONSTRAINTS_H_
#define _CONSTRAINTS_H_

void allNotCellXVericalandB(List_Clause *clauseList);
void allNotCellVericalXandO(List_Clause *clauseList);
void allNotCellXHorizontalandB(List_Clause *clauseList);
void allNotCellXHorizontalandNotO(List_Clause *clauseList);
void notBnotOCellXVerical(List_Clause *clauseList);
void notBOCellXVHorizontal(List_Clause *clauseList);
/*The boat k occupies the cells such that*/
void contiguousCell(List_Clause *clauseList);

/*There is at least one boat k*/
void thereIsAtLeastOneBoatK(List_Clause *clauseList);

/*There is at most one boat k*/
void thereIsAtMostOneBoatK(List_Clause *clauseList);

/*In every cell there is only one boat or section of boat.*/
void oneBoatOrSectionOfBoat(List_Clause *clauseList);

void read_game_file(FILE* f, int column_list[], int line_list[]);


void combinationUtil(int arr[], int data[], int start, int end,int index, int r,combination_list *comb_list);

void createCombination(int r,combination_list* comb_list);

void NChosesKColumnFirstPart(List_Clause *clauseList,int column_list[]);
void NChosesKColumnSecondPart(List_Clause *clauseList,int column_list[]);
void NChosesKColumn(List_Clause *clauseList,int column_list[]);

void NChosesKLineFirstPart(List_Clause *clauseList,int line_list[]);
void NChosesKLineSecondPart(List_Clause *clauseList,int line_list[]);
void NChosesKLine(List_Clause *clauseList,int line_list[]);




void allConstrants(List_Clause *clauseList,int column_list[],int line_list[]);

void print_Clause_DIMACS_Format(clause c, FILE *fileOut);
void print_In_DIMACS_Format(List_Clause *clauseList, FILE *fileOut);


#endif 