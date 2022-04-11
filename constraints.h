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

void allConstrants(List_Clause *clauseList);

#endif 