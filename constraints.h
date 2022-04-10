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
void contiguousCell(List_Clause *clauseList);
void notBnotOCellXVerical(List_Clause *clauseList);
void notBOCellXVHorizontal(List_Clause *clauseList);
#endif 