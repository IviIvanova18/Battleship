#include "types.h"	
#include "constraints.h"	
#include <stdio.h>	
#include <stdlib.h>	
#include <stdbool.h>	

int GridSizeHeight, GridSizeWidth;	
int StartBoat, BoatCount;	


/*depending on the k returns the size of thr boat	
* k in 1...3 -> TinyBoat -> 1	
* k in 4...6 -> SmallBoat -> 2	
* k in 7...8 -> MediumBoat -> 3	
* k in 9 -> BigBoat -> 4	
*/	
int matchKBoatToNSizeofK(int k) {	
    switch (k) {	
        case 0 ... 3:	
            return TinyBoatSize;	
            break;	
        case 4 ... 6:	
            return SmallBoatSize;	
            break;	
        case 7 ... 8:	
            return MediumBoatSize;	
            break;	
        case 9:	
            return BigBoatSize;	
            break;	
        default:	
            return 0;	
            break;	
    }	
}	

/*if isBoat == true :(¬X1 ∨ ¬X2 ∨ ¬X3 ∨ ¬X4 ∨ B)	
* else : (¬X1 ∨ ¬X2 ∨ ¬X3 ∨ ¬X4 ∨ O)*/	
void allNotCellXVericalandBorO(List_Clause *clauseList, bool isBoat) {	
    int k, i, j, n;	
    clause c;	

    for (k = StartBoat; k < BoatCount; k++) {	
        int boatSize = matchKBoatToNSizeofK(k);	
        for (i = 0; i <= GridSizeHeight - boatSize; i++) {	
            for (j = 0; j < GridSizeWidth; j++) {	
                c.size = 0;	
                for (n = 0; n <= boatSize - 1; n++) {	
                    //-Xi+n,j,k	
                    addCell(&c, i + n, j, k, true);	
                }	
                if (isBoat) {	
                    //Bi,j,k	
                    addBoat(&c, i, j, k, false);	

                } else {	
                    //Ok	
                    addOrientation(&c, k, false);	

                }	
                add_element_List_Clause(clauseList, &c);	
            }	

        }	
    }	
}	

/*if isBoat == true :  (¬X1 ∨ ¬X5 ∨ ¬X6 ∨ ¬X7 ∨ B) 	
* else (¬X1 ∨ ¬X5 ∨ ¬X6 ∨ ¬X7 ∨ ¬O) 	
*/	
void allNotCellXHorizontalandBorNotO(List_Clause *clauseList, bool isBoat) {	
    int k, i, j, n;	
    clause c;	
    for (k = StartBoat; k < BoatCount; k++) {	
        int boatSize = matchKBoatToNSizeofK(k);	
        for (i = 0; i < GridSizeHeight; i++) {	
            for (j = 0; j <= GridSizeWidth - boatSize; j++) {	

                reset_Clause(&c);	

                for (n = 0; n <= boatSize - 1; n++) {	
                    addCell(&c, i, j + n, k, true);	
                }	
                if (isBoat) {	
                    addBoat(&c, i, j, k, false);	
                } else {	
                    addOrientation(&c, k, true);	
                }	
                add_element_List_Clause(clauseList, &c);	
            }	

        }	
    }	
}	


// (¬Bi,j,k ∨ ¬O ∨ Xi,j) ∧ (¬Bi,j,k ∨ ¬O ∨ xi+1,j) ∧ (¬Bi,j,k ∨ ¬O ∨ xi+2,j) ∧ (¬Bi,j,k ∨ ¬O ∨ xi+3,j)	
void notBnotOCellXVerical(List_Clause *clauseList) {	
    int k, i, j, n;	
    clause c;	
    for (k = StartBoat; k < BoatCount; k++) {	
        int boatSize = matchKBoatToNSizeofK(k);	
        for (i = 0; i <= GridSizeHeight - boatSize; i++) {	
            for (j = 0; j < GridSizeWidth; j++) {	
                for (n = 0; n <= boatSize - 1; n++) {	
                    c.size = 0;	
                    //-Bi,j,k  	
                    addBoat(&c, i, j, k, true);	
                    //-Ok  	
                    addOrientation(&c, k, true);	
                    //Xi+n,j,k	
                    addCell(&c, i + n, j, k, false);	
                    add_element_List_Clause(clauseList, &c);	
                }	

            }	

        }	

    }	
}	

// (¬B ∨ O ∨ X1) ∧ (¬B ∨ O ∨ X5) ∧ (¬B ∨ O ∨ X6) ∧ (¬B ∨ O ∨ X7)	
void notBOCellXHorizontal(List_Clause *clauseList) {	
    int k, i, j, n;	
    clause c;	
    for (k = StartBoat; k < BoatCount; k++) {	
        int boatSize = matchKBoatToNSizeofK(k);	
        for (i = 0; i < GridSizeHeight; i++) {	
            for (j = 0; j <= GridSizeWidth - boatSize; j++) {	
                for (n = 0; n <= boatSize - 1; n++) {	
                    c.size = 0;	
                    //-Bi,j,k  		
                    addBoat(&c, i, j, k, true);	
                    //Ok	
                    addOrientation(&c, k, false);	
                    //Xi,j+n,k	
                    addCell(&c, i, j + n, k, false);	
                    add_element_List_Clause(clauseList, &c);	
                }	
            }	
        }	
    }	
}	

void contiguousCell(List_Clause *clauseList) {	
    // =>	
    // (¬Bi,j,k ∨ ¬O ∨ Xi,j) ∧ (¬Bi,j,k ∨ ¬O ∨ xi+1,j) ∧ (¬Bi,j,k ∨ ¬O ∨ xi+2,j) ∧ (¬Bi,j,k ∨ ¬O ∨ xi+3,j)	
    notBnotOCellXVerical(clauseList);	
    //=>	
    //  (¬B ∨ O ∨ X1) ∧ (¬B ∨ O ∨ X5) ∧ (¬B ∨ O ∨ X6) ∧ (¬B ∨ O ∨ X7)	
    notBOCellXHorizontal(clauseList);	

}	

void thereIsAtLeastOneBoatK(List_Clause *clauseList) {	
    int k, i, j;	
    clause c, c2, c3;	
    for (k = StartBoat; k < BoatCount; k++) {	
        int boatSize = matchKBoatToNSizeofK(k);	
        reset_Clause(&c);	
        reset_Clause(&c2);	
        reset_Clause(&c3);	
        for (i = 0; i < GridSizeHeight; i++) {	
            for (j = 0; j < GridSizeWidth; j++) {	
                if ((i <= GridSizeHeight - boatSize || j <= GridSizeWidth - boatSize)) {	
                    addBoat(&c, i, j, k, false);	
                }	
                if (i <= GridSizeHeight - boatSize) {	
                    addBoat(&c2, i, j, k, false);	
                }	
                if (j <= GridSizeWidth - boatSize) {	
                    addBoat(&c3, i, j, k, false);	
                }	
            }	
        }	
        addOrientation(&c2, k, true);	
        addOrientation(&c3, k, false);	
        add_element_List_Clause(clauseList, &c);	
        add_element_List_Clause(clauseList, &c2);	
        add_element_List_Clause(clauseList, &c3);	
    }	
}	


void thereIsAtMostOneBoatK(List_Clause *clauseList) {	
    int k, i, j, ip, jp;	
    for (k = StartBoat; k < BoatCount; k++) {	
        int boatSize = matchKBoatToNSizeofK(k);	
        for (i = 0; i < GridSizeHeight; i++) {	
            for (j = 0; j < GridSizeWidth; j++) {	
                for (ip = 0; ip < GridSizeHeight; ip++) {	
                    for (jp = 0; jp < GridSizeWidth; jp++) {	
                        clause c;	
                        reset_Clause(&c);	
                        if ((i <= GridSizeHeight - boatSize || j <= GridSizeWidth - boatSize) &&	
                            (ip <= GridSizeHeight - boatSize || jp <= GridSizeWidth - boatSize) &&	
                            (i != ip || j != jp)) {	
                            //B_i,j,k	
                            addBoat(&c, i, j, k, true);	
                            //B_ip,jp,k	
                            addBoat(&c, ip, jp, k, true);	
                            add_element_List_Clause(clauseList, &c);	
                        }	
                    }	
                }	

            }	
        }	
    }	
}	


void oneBoatOrSectionOfBoat(List_Clause *clauseList) {	
    int i, j, k1, k2;	
    clause c;	
    c.size = 0;	
    for (i = 0; i < GridSizeHeight; i++) {	
        for (j = 0; j < GridSizeWidth; j++) {	
            for (k1 = StartBoat; k1 < BoatCount; k1++) {	
                for (k2 = k1 + 1; k2 < BoatCount; k2++) {	
                    if (k1 != k2) {	
                        reset_Clause(&c);	
                        //-X_i,j,k1	
                        addCell(&c, i, j, k1, true);	
                        //-X_i,j,k2	
                        addCell(&c, i, j, k2, true);	
                        add_element_List_Clause(clauseList, &c);	
                    }	
                }	
            }	
        }	
    }	
}	



// There can not be two boats in the same square	
void onlyOneBoatInCell(List_Clause *clauseList) {	
    int i, j, k1, k2;	
    clause c;	
    for (i = 0; i < GridSizeHeight; i++) {	
        for (j = 0; j < GridSizeWidth; j++) {	
            for (k1 = StartBoat; k1 < BoatCount; k1++) {	
                for (k2 = k1 + 1; k2 < BoatCount; k2++) {	
                    if (k1 != k2) {	
                        c.size = 0;	
                        //-X_i,j,k1	
                        addBoat(&c, i, j, k1, true);	
                        //-X_i,j,k2	
                        addBoat(&c, i, j, k2, true);	
                        add_element_List_Clause(clauseList, &c);	
                    }	
                }	
            }	
        }	
    }	
}	


void read_game_file(FILE *f, int column_list[], int line_list[],int *L, int *H, int *startBoat, int *lastBoat) {	
    int x;	
    int count = 0;	
    fscanf(f, "%d", L);	
    fscanf(f, "%d", H);	
	fscanf(f, "%d", startBoat);	
    fscanf(f, "%d", lastBoat);	

    while (!feof(f) && count < *H) {	
        fscanf(f, "%d", &x);	
        column_list[count] = x;	
        count++;	

    }	
    count = 0;	
    while (!feof(f) && count < *L) {	
        fscanf(f, "%d", &x);	
        line_list[count] = x;	
        count++;	
    }	
    fclose(f);	

}	


//No boat touches anoter boat	
void noBoatTouchesAnother(List_Clause *clauseList) {	
    //Horizontal	
    //=>	
    NotBOAllNotSuroundingCellHorizintal(clauseList);	
    //Vertical	
    //=>	
    NotBOAllNotSuroundingCellVertical(clauseList);	

}	

//Horizintal	
//(¬B ∨ O ∨ ¬X0) ∧ (¬B ∨ O ∨ ¬X1) ∧ (¬B ∨ O ∨ ¬X2) ∧ (¬B ∨ O ∨ ¬X3))	
void NotBOAllNotSuroundingCellHorizintal(List_Clause *clauseList) {	

    int k, i, j, r, t, k1;	
    clause c, c2, c3;	
    for (k = StartBoat; k < BoatCount; k++) {	
        int boatSize = matchKBoatToNSizeofK(k);	
        for (i = 0; i < GridSizeHeight; i++) {	
            for (j = 0; j <= GridSizeWidth - boatSize; j++) {	
                for (r = i - 1; r <= i + 1; r += 2) {	
                    for (t = j - 1; t <= j + boatSize; t++) {	
                        if (r >= 0 && r <= GridSizeHeight - 1 && t >= 0 && t <= GridSizeWidth - 1) {	
                            for (k1 = StartBoat; k1 < BoatCount; k1++) {	
                                if (k1 != k) {	

                                    reset_Clause(&c);	
                                    reset_Clause(&c2);	
                                    reset_Clause(&c3);	
                                    //-Xrtk	
                                    addBoat(&c3, i, j, k, true);	
                                    addOrientation(&c3, k, false);	
                                    addCell(&c3, r, t, k1, true);	

                                    addBoat(&c, i, j, k, true);	
                                    addOrientation(&c, k, false);	
                                    addBoat(&c, r, t, k1, true);	
                                    addOrientation(&c, k1, false);	

                                    addBoat(&c2, i, j, k, true);	
                                    addOrientation(&c2, k, false);	
                                    addBoat(&c2, r, t, k1, true);	
                                    addOrientation(&c2, k1, true);	

                                    add_element_List_Clause(clauseList, &c);	
                                    add_element_List_Clause(clauseList, &c2);	
                                    add_element_List_Clause(clauseList, &c3);	
                                }	
                            }	
                        }	
                    }	
                }	
                if (j - 1 >= 0) {	
                    for (k1 = StartBoat; k1 < BoatCount; k1++) {	
                        //-Xrtk	
                        reset_Clause(&c);	
                        reset_Clause(&c2);	
                        reset_Clause(&c3);	

                        addBoat(&c3, i, j, k, true);	
                        addOrientation(&c3, k1, false);	
                        addCell(&c3, i, j - 1, k1, true);	

                        addBoat(&c, i, j, k, true);	
                        addOrientation(&c, k, false);	
                        addBoat(&c, i, j - 1, k1, true);	
                        addOrientation(&c, k1, false);	

                        addBoat(&c2, i, j, k, true);	
                        addOrientation(&c2, k, false);	
                        addBoat(&c2, i, j - 1, k1, true);	
                        addOrientation(&c2, k1, true);	

                        add_element_List_Clause(clauseList, &c);	
                        add_element_List_Clause(clauseList, &c2);	
                        add_element_List_Clause(clauseList, &c3);	
                    }	

                }	
                if (j + boatSize < GridSizeWidth) {	
                    for (k1 = StartBoat; k1 < BoatCount; k1++) {	

                        // -Xrtk	
                        reset_Clause(&c);	
                        reset_Clause(&c2);	
                        reset_Clause(&c3);	

                        addBoat(&c3, i, j, k, true);	
                        addOrientation(&c3, k, false);	
                        addCell(&c3, i, j + boatSize, k1, true);	

                        addBoat(&c, i, j, k, true);	
                        addOrientation(&c, k, false);	
                        addBoat(&c, i, j + boatSize, k1, true);	
                        addOrientation(&c, k1, false);	

                        addBoat(&c2, i, j, k, true);	
                        addOrientation(&c2, k, false);	
                        addBoat(&c2, i, j + boatSize, k1, true);	
                        addOrientation(&c2, k1, true);	

                        add_element_List_Clause(clauseList, &c);	
                        add_element_List_Clause(clauseList, &c2);	
                        add_element_List_Clause(clauseList, &c3);	

                    }	

                }	

            }	

        }	
    }	
}	

//Vertical//	
void NotBOAllNotSuroundingCellVertical(List_Clause *clauseList) {	

    int k, i, j, r, t, k1;	
    clause c, c2, c3;	
    for (k = StartBoat; k < BoatCount; k++) {	
        int boatSize = matchKBoatToNSizeofK(k);	
        for (i = 0; i <= GridSizeHeight - boatSize; i++) {	
            for (j = 0; j < GridSizeWidth; j++) {	
                for (r = i - 1; r <= i + boatSize; r++) {	
                    for (t = j - 1; t <= j + 1; t += 2) {	
                        if (r >= 0 && r <= GridSizeHeight - 1 && t >= 0 && t <= GridSizeWidth - 1) {	
                            for (k1 = StartBoat; k1 < BoatCount; k1++) {	
                                reset_Clause(&c);	
                                reset_Clause(&c2);	
                                reset_Clause(&c3);	

                                addBoat(&c3, i, j, k, true);	
                                addOrientation(&c3, k, true);	
                                addCell(&c3, r, t, k1, true);	

                                addBoat(&c, i, j, k, true);	
                                addOrientation(&c, k, true);	
                                addBoat(&c, r, t, k1, true);	
                                addOrientation(&c, k1, true);	

                                addBoat(&c2, i, j, k, true);	
                                addOrientation(&c2, k, true);	
                                addBoat(&c2, r, t, k1, true);	
                                addOrientation(&c2, k1, false);	

                                add_element_List_Clause(clauseList, &c);	
                                add_element_List_Clause(clauseList, &c2);	
                                add_element_List_Clause(clauseList, &c3);	
                            }	
                        }	
                    }	
                }	

                if (i - 1 >= 0) {	
                    for (k1 = StartBoat; k1 < BoatCount; k1++) {	

                        reset_Clause(&c);	
                        reset_Clause(&c2);	
                        reset_Clause(&c3);	

                        addBoat(&c3, i, j, k, true);	
                        addOrientation(&c3, k, true);	
                        addCell(&c3, i - 1, j, k1, true);	

                        addBoat(&c, i, j, k, true);	
                        addOrientation(&c, k, true);	
                        addBoat(&c, i - 1, j, k1, true);	
                        addOrientation(&c, k1, true);	

                        addBoat(&c2, i, j, k, true);	
                        addOrientation(&c2, k, true);	
                        addBoat(&c2, i - 1, j, k1, true);	
                        addOrientation(&c2, k1, false);	

                        add_element_List_Clause(clauseList, &c);	
                        add_element_List_Clause(clauseList, &c2);	
                        add_element_List_Clause(clauseList, &c3);	
                    }	

                }	
                if (i + boatSize < GridSizeHeight) {	
                    for (k1 = StartBoat; k1 < BoatCount; k1++) {	

                        reset_Clause(&c);	
                        reset_Clause(&c2);	
                        reset_Clause(&c3);	

                        addBoat(&c3, i, j, k, true);	
                        addOrientation(&c3, k, true);	
                        addCell(&c3, i + boatSize, j, k1, true);	

                        addBoat(&c, i, j, k, true);	
                        addOrientation(&c, k, true);	
                        addBoat(&c, i + boatSize, j, k1, true);	
                        addOrientation(&c, k1, true);	

                        addBoat(&c2, i, j, k, true);	
                        addOrientation(&c2, k, true);	
                        addBoat(&c2, i + boatSize, j, k1, true);	
                        addOrientation(&c2, k1, false);	

                        add_element_List_Clause(clauseList, &c);	
                        add_element_List_Clause(clauseList, &c2);	
                        add_element_List_Clause(clauseList, &c3);	
                    }	

                }	


            }	

        }	
    }	
}	


void nonExistingBoat(List_Clause *clauseList) {	
    int k;	
    clause c;	
    c.size = 0;	
    addBoat(&c, 7, 7, 9, true);	
    add_element_List_Clause(clauseList, &c);	
    c.size = 0;	
    addBoat(&c, 7, 8, 9, true);	
    add_element_List_Clause(clauseList, &c);	
    c.size = 0;	
    addBoat(&c, 7, 9, 9, true);	
    add_element_List_Clause(clauseList, &c);	
    c.size = 0;	
    addBoat(&c, 8, 7, 9, true);	
    add_element_List_Clause(clauseList, &c);	
    for (k = 7; k < BoatCount; k++) {	
        c.size = 0;	
        addBoat(&c, 8, 8, k, true);	
        add_element_List_Clause(clauseList, &c);	
    }	
    for (k = 7; k < BoatCount; k++) {	
        c.size = 0;	
        addBoat(&c, 8, 9, k, true);	
        add_element_List_Clause(clauseList, &c);	
    }	
    c.size = 0;	
    addBoat(&c, 9, 7, 9, true);	
    add_element_List_Clause(clauseList, &c);	
    for (k = 7; k < BoatCount; k++) {	
        c.size = 0;	
        addBoat(&c, 9, 8, k, true);	
        add_element_List_Clause(clauseList, &c);	
    }	
    for (k = 4; k < BoatCount; k++) {	
        c.size = 0;	
        addBoat(&c, 9, 9, k, true);	
        add_element_List_Clause(clauseList, &c);	
    }	
}	

void createCombination(int r, combination_list *cl, int lenght) {	

    // int *arr = malloc(sizeof(int) * lenght);	
    int arr[lenght];	
    for (int i = 0; i < lenght; i++) {	
        arr[i] = i;	
    }	

    int n = lenght;	
    int data[r];	

    combinationUtil(arr, data, 0, n - 1, 0, r, cl);	
}	

void combinationUtil(int arr[], int data[], int start, int end, int index, int r, combination_list *cl) {	
    if (index == r) {	

        combination c;	
        c.size = 0;	
        for (int j = 0; j < r; j++) {	

            c.size++;	
            c.tab[c.size - 1] = data[j];	
        }	
        add_element_combination_list(cl, &c);	

        return;	
    }	

    for (int i = start; i <= end && end - i + 1 >= r - index; i++) {	
        data[index] = arr[i];	
        combinationUtil(arr, data, i + 1, end, index + 1, r, cl);	
    }	
}	

int KChosesNCNF(FILE *file, int row_list[], bool row) {	
    combination_list combList;	
    combList = create_empty_combination_list();	
    combination currComb;	
    clause newClause;	
    int l, i, j, k, n;	
    int p = 0;	
    int count = 0, countCombi = 0;	
    for (j = 0; j < GridSizeWidth; j++) {	
        n = row_list[j];	
        if (n < -1) {	
            printf("Error");	
            return -1;	
        }	
        if (GridSizeHeight < n) {	
            printf("Error");	
            return -1;	
        }	
        int len = GridSizeHeight * (BoatCount - StartBoat);	
        for (l = 0; l <= len; l++) {	
            if (l != n) {	
                combList = create_empty_combination_list();	
                createCombination(l, &combList, len);	
                countCombi += combList.size;	
                Node_Combination *c;	
                Node_Combination *prev;	
                c = combList.first;	
                while (c != NULL) {	
                    currComb.size = c->data.size;	
                    for (int s = 0; s < c->data.size; s++) {	
                        currComb.tab[s] = c->data.tab[s];	
                    }	
                    bool flag = true;	
                    newClause.size = 0;	
                    count = 0;	
                    p = 0;	
                    for (k = StartBoat; k < BoatCount; k++) {	
                        for (i = 0; i < GridSizeHeight; i++) {	
                            if (p == currComb.size) flag = false;	
                            if ((currComb.tab[p]) == count && flag) {	
                                p++;	
                                if (row) {	
                                    addCell(&newClause, i, j, k, true);	
                                } else {	
                                    addCell(&newClause, j, i, k, true);	
                                }	

                                if (p == currComb.size) flag = false;	

                            } else {	
                                if (row) {	
                                    addCell(&newClause, i, j, k, false);	
                                } else {	
                                    addCell(&newClause, j, i, k, false);	
                                }	
                            }	
                            count++;	
                        }	
                    }	

                    count = 0;	
                    print_Clause_DIMACS_Format2(newClause, file);	
                    fprintf(file, "0\n");	
                    prev = c;	
                    c = c->next;	

                    free(prev);	
                }	

            }	
        }	
    }	
    return countCombi;	
}	

void allConstraints(List_Clause *clauseList, int column_list[], int line_list[]) {	
    contiguousCell(clauseList);	
    thereIsAtLeastOneBoatK(clauseList);	
    thereIsAtMostOneBoatK(clauseList);	
    oneBoatOrSectionOfBoat(clauseList);	
    noBoatTouchesAnother(clauseList);	
    nonExistingBoat(clauseList);	
    onlyOneBoatInCell(clauseList);	
}	

void print_In_DIMACS_Format(List_Clause *clauseList, FILE *fileOut, int count) {	
    assert(clauseList);	
    Node_Clause *c;	
    Node_Clause *prev;	
    c = clauseList->first;	
    while (c != NULL) {	
        if (c->next == NULL) {	
            print_Clause_DIMACS_Format(c->data, fileOut);	
        } else {	
            print_Clause_DIMACS_Format(c->data, fileOut);	
            fprintf(fileOut, "\n");	
        }	
        prev = c;	
        c = c->next;	
        free(prev);	
    }	
    clauseList->first = NULL;	

}	

void print_Clause_DIMACS_Format(clause c, FILE *fileOut) {	
    int k;	
    int n = c.size;	
    literal l;	

    for (k = 0; k < n; k++) {	
        l = c.tab[k];	
        if (l.negation) {	
            fprintf(fileOut, "-%d ", l.name);	

        } else {	
            fprintf(fileOut, "%d ", l.name);	
        }	

    }	
    fprintf(fileOut, "0");	
}	


void print_Clause_DIMACS_Format2(clause c, FILE *fileOut) {	
    int k;	
    int n = c.size;	
    literal l;	

    for (k = 0; k < n; k++) {	
        l = c.tab[k];	
        if (l.negation) {	
            fprintf(fileOut, "-%d ", l.name);	

        } else {	
            fprintf(fileOut, "%d ", l.name);	
        }	

    }	
} 	
