#include "types.h"
#include "constraints.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// x1 = xi,j
// x2 = xi+1,j
// x3 = xi+2,j
// x4 = xi+3,j
// x5 = xi,j+1
// x6 = xi,j+2
// x7 = xi,j+3

// for ship n =4
// (¬X1 ∨ ¬X2 ∨ ¬X3 ∨ ¬X4 ∨ B) ∧ 
// (¬X1 ∨ ¬X2 ∨ ¬X3 ∨ ¬X4 ∨ O) ∧ 
// (¬B ∨ ¬O ∨ X1) ∧ (¬B ∨ ¬O ∨ X2) ∧
//  (¬B ∨ ¬O ∨ X3) ∧ (¬B ∨ ¬O ∨ X4) ∧
//   (¬X1 ∨ ¬X5 ∨ ¬X6 ∨ ¬X7 ∨ B) ∧
//    (¬X1 ∨ ¬X5 ∨ ¬X6 ∨ ¬X7 ∨ ¬O) ∧ 
//    (¬B ∨ O ∨ X1) ∧ (¬B ∨ O ∨ X5) ∧ 
//    (¬B ∨ O ∨ X6) ∧ (¬B ∨ O ∨ X7)

/*depending on the k returns the size of thr boat
* k in 1...3 -> TinyBoat -> 1
* k in 4...6 -> SmallBoat -> 2
* k in 7,8 -> MediumBoat ->3
* k in 9 -> BigBoat -> 4
*/
int matchKBoatToNSizeofK(int k){
	switch (k)
	{
	case 0:
	case 1:
	case 2:
	case 3:
		return TinyBoatSize;
		break;
	case 4: 
	case 5: 
	case 6: 
		return SmallBoatSize;
		break;
	case 7: 
	case 8: 
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
///works ///
// void allNotCellXVericalandBorO(List_Clause *clauseList,bool isBoat){
// 	int k,i,j,n;
// 	clause c;

// 	for (k = StartBoat; k < BoatCount; k++){
// 		int boatSize = matchKBoatToNSizeofK(k);
// 		//GridSizeWidth
// 		for(j = 0; j < GridSizeWidth;j++){
// 			//GridSizeHeight-boatSize
// 			for (i = 0; i <= GridSizeHeight-boatSize; i++){
// 				c.size=0;
// 				//if (i+n<=GridSizeHeight-boatSize)
// 				for(n = 0; n <= boatSize-1;n++){
// 					addCell(&c,i+n,j,k,true);
// 				}
// 				if(isBoat){
// 					addBoat(&c,i,j,k,false);

// 				}else{
// 					addOrientation(&c,k,false);

// 				}
// 				add_element_List_Clause(clauseList,&c);
// 			}
			
// 		}
// 	}
// }


void allNotCellXVericalandBorO(List_Clause *clauseList,bool isBoat){
	int k,i,j,n;
	clause c;

	for (k = StartBoat; k < BoatCount; k++){
		int boatSize = matchKBoatToNSizeofK(k);
		//GridSizeWidth
		for(i = 0; i <= GridSizeHeight-boatSize;i++){
			//GridSizeHeight-boatSize
			for (j = 0; j < GridSizeWidth; j++){
				c.size=0;
				//if (i+n<=GridSizeHeight-boatSize)
				for(n = 0; n <= boatSize-1;n++){
					addCell(&c,i + n,j,k,true);
				}
				if(isBoat){
					addBoat(&c,i,j,k,false);

				}else{
					addOrientation(&c,k,false);

				}
				add_element_List_Clause(clauseList,&c);
			}
			
		}
	}
}

/*if isBoat == true :  (¬X1 ∨ ¬X5 ∨ ¬X6 ∨ ¬X7 ∨ B) 
* else (¬X1 ∨ ¬X5 ∨ ¬X6 ∨ ¬X7 ∨ ¬O) 
*/

//works//
void allNotCellXHorizontalandBorNotO(List_Clause *clauseList, bool isBoat){
	int k,i,j,n;
	clause c;
	for (k = StartBoat; k < BoatCount; k++){
		int boatSize = matchKBoatToNSizeofK(k);
		for (i = 0; i < GridSizeHeight; i++){
            for(j = 0; j <= GridSizeWidth-boatSize ;j++){

				c.size=0;

				for(n = 0; n <= boatSize-1;n++){
					addCell(&c,i,j+n,k,true);
				}
				if(isBoat){
					addBoat(&c,i,j,k,false);
				}else{
					addOrientation(&c,k,true);
				}
				add_element_List_Clause(clauseList,&c);
			}
			
		}
	}
}



// (¬Bi,j,k ∨ ¬O ∨ Xi,j) ∧ (¬Bi,j,k ∨ ¬O ∨ xi+1,j) ∧ (¬Bi,j,k ∨ ¬O ∨ xi+2,j) ∧ (¬Bi,j,k ∨ ¬O ∨ xi+3,j)

//works//
void notBnotOCellXVerical(List_Clause *clauseList){
    int k,i,j,n;
	for (k = StartBoat; k < BoatCount; k++){
		int boatSize = matchKBoatToNSizeofK(k);  
        for(i = 0; i <= GridSizeHeight-boatSize ;i++){
			//GridSizeHeight-boatSize
		    for (j = 0; j < GridSizeWidth; j++){
                for(n = 0; n <= boatSize-1;n++){
                    clause c;
                    c.size=0;
                    //-Bi,j,k  
					addBoat(&c,i,j,k,true);	
                    //-Ok  
					addOrientation(&c,k,true);	
                    //Xi+n,j,k
					addCell(&c,i+n,j,k,false);
                    add_element_List_Clause(clauseList,&c);
                }
		    	
		    }
            
        }
		
	}
}

//    (¬B ∨ O ∨ X1) ∧ (¬B ∨ O ∨ X5) ∧ (¬B ∨ O ∨ X6) ∧ (¬B ∨ O ∨ X7)
void notBOCellXHorizontal(List_Clause *clauseList){
	int k,i,j,n;
	for (k = StartBoat; k < BoatCount; k++){
		int boatSize = matchKBoatToNSizeofK(k);
		//GridSizeHeight
		for (i = 0; i < GridSizeHeight; i++){
			//GridSizeWidth-boatSize
            for(j = 0; j <= GridSizeWidth-boatSize ;j++){
                for(n = 0; n <= boatSize-1;n++){
                    clause c;
                    c.size=0;
                    //-Bi,j,k  	
					addBoat(&c,i,j,k,true);
                    //Ok
					addOrientation(&c,k,false);
                    //Xi,j+n,k
					addCell(&c,i,j+n,k,false);
                    add_element_List_Clause(clauseList,&c);
                }
            }
		}
	}
}

void contiguousCell(List_Clause *clauseList){
	// (¬X1 ∨ ¬X2 ∨ ¬X3 ∨ ¬X4 ∨ B)
	allNotCellXVericalandBorO(clauseList,true);
	// (¬X1 ∨ ¬X2 ∨ ¬X3 ∨ ¬X4 ∨ O)
	allNotCellXVericalandBorO(clauseList,false);
	// (¬Bi,j,k ∨ ¬O ∨ Xi,j) ∧ (¬Bi,j,k ∨ ¬O ∨ xi+1,j) ∧ (¬Bi,j,k ∨ ¬O ∨ xi+2,j) ∧ (¬Bi,j,k ∨ ¬O ∨ xi+3,j)
    notBnotOCellXVerical(clauseList);
    // (¬X1 ∨ ¬X5 ∨ ¬X6 ∨ ¬X7 ∨ B) 
   	// allNotCellXHorizontalandBorNotO(clauseList,true);
    // (¬X1 ∨ ¬X5 ∨ ¬X6 ∨ ¬X7 ∨ ¬O) 
    // allNotCellXHorizontalandBorNotO(clauseList,false);
    //  (¬B ∨ O ∨ X1) ∧ (¬B ∨ O ∨ X5) ∧ (¬B ∨ O ∨ X6) ∧ (¬B ∨ O ∨ X7)
    notBOCellXHorizontal(clauseList);
	
}
void thereIsAtLeastOneBoatK(List_Clause *clauseList){
	int k,i,j;
	clause c;
	for (k = StartBoat; k < BoatCount; k++){
		int boatSize = matchKBoatToNSizeofK(k);
		reset_Clause(&c);
		for (i = 0; i < GridSizeHeight; i++){
            for(j = 0; j < GridSizeWidth ;j++){
				if((i<=GridSizeHeight-boatSize || j<=GridSizeWidth-boatSize)){
					addBoat(&c,i,j,k,false);
				}   
            }
		}
    	add_element_List_Clause(clauseList,&c);
	}

}


void thereIsAtMostOneBoatK(List_Clause *clauseList){
	int k,i,j,ip,jp;
	// literal l;
	for (k = StartBoat; k < BoatCount; k++){
		int boatSize = matchKBoatToNSizeofK(k);
		for (i = 0; i < GridSizeHeight; i++){
            for(j = 0; j < GridSizeWidth ;j++){
				for (ip = 0; ip < GridSizeHeight; ip++){
           			for(jp = 0; jp < GridSizeWidth ;jp++){
						clause c;
                		reset_Clause(&c);
						if((i<=GridSizeHeight-boatSize || j<=GridSizeWidth-boatSize)&&(ip<=GridSizeHeight-boatSize || jp<=GridSizeWidth-boatSize)&&(i!=ip || j!=jp)){
							//B_i,j,k  
							addBoat(&c,i,j,k,true);
							//B_ip,jp,k 
							addBoat(&c,ip,jp,k,true);
                			add_element_List_Clause(clauseList,&c);
						}
					}
				}
                
            }
		}
	}
}


void oneBoatOrSectionOfBoat(List_Clause *clauseList){
	int i,j,k1,k2;
	clause c;
	c.size = 0;
	for(i = 0; i < GridSizeHeight ;i++){
		for (j = 0; j < GridSizeWidth; j++){
			for (k1 = StartBoat; k1 < BoatCount; k1++){
				// int boatSizeK1 = matchKBoatToNSizeofK(k1);
				for(k2 = k1+1; k2 < BoatCount ;k2++){
					// int boatSizeK2 = matchKBoatToNSizeofK(k2);
					// if((i<=GridSizeHeight-boatSizeK1 || j<=GridSizeWidth-boatSizeK1)&&(i<=GridSizeHeight-boatSizeK2 || j<=GridSizeWidth-boatSizeK2)){
					if (k1 != k2){
						// c.size=0;
						c.size = 0;
						//-X_i,j,k1
						addCell(&c,i,j,k1,true);
						//-X_i,j,k2
						addCell(&c,i,j,k2,true);
        				add_element_List_Clause(clauseList,&c);
					}
				}
			}
		}
	}
}


////Test contstr//
// there can not be two boats in the same square
void TestConstr(List_Clause *clauseList){
	int i,j,k1,k2;
	for(i = 0; i < GridSizeHeight ;i++){
		for (j = 0; j < GridSizeWidth; j++){
			for (k1 = StartBoat; k1 < BoatCount; k1++){
				// int boatSizeK1 = matchKBoatToNSizeofK(k1);
				for(k2 = k1+1; k2 < BoatCount ;k2++){
					// int boatSizeK2 = matchKBoatToNSizeofK(k2);
					// if((i<=GridSizeHeight-boatSizeK1 || j<=GridSizeWidth-boatSizeK1)&&(i<=GridSizeHeight-boatSizeK2 || j<=GridSizeWidth-boatSizeK2)){
					if (k1 != k2){
						clause c;
						c.size=0;
						//-X_i,j,k1
						addBoat(&c,i,j,k1,true);
						//-X_i,j,k2
						addBoat(&c,i,j,k2,true);
        				add_element_List_Clause(clauseList,&c);
					}
				}
			}
		}
	}
}
/////

void read_game_file(FILE* f, int column_list[], int line_list[]){
	int x;
	int count = 0;
	int L,H;
	fscanf(f, "%d", &L);
	fscanf(f, "%d", &H);

    while (!feof(f) && count<H) {
        fscanf(f, "%d", &x);
		column_list[count] = x;
		count++;
       
    }
	count = 0;
	while (!feof(f) && count<L) {
        fscanf(f, "%d", &x);
		line_list[count] = x;
		count++;
    }
	fclose(f);
	
}

void createCombination(int r,combination_list* comb_list,int lenght)
{   

	int *arr = malloc(sizeof(int)*(lenght-1));
	for(int i = 0;i<lenght;i++){
		arr[i]=i;
	}

    int n = lenght;
    int data[r];
    combinationUtil(arr, data, 0, n-1, 0, r,comb_list);
}
void combinationUtil(int arr[], int data[], int start, int end,int index, int r,combination_list *comb_list){
    if (index == r)
    {   
        int j=0;
		combination combination;
		combination.size = 0;
        for (j=0; j<r; j++){
			combination.size++;
			combination.tab[combination.size-1] = data[j];
		}
		comb_list->size++;
		comb_list->tab[comb_list->size-1] = combination;
        return;
    }

    for (int i=start; i<=end && end-i+1 >= r-index; i++)
    {
        data[index] = arr[i];
        combinationUtil(arr, data, i+1, end, index+1, r,comb_list);
    }
}



void NChosesK(List_Clause *clauseList,int column_list[]){
	
}


//No boat touches anoter boat
void noBoatTouchesAnother(List_Clause *clauseList){
	//Horizontal 
	//=>
	// NotBOAllNotSuroundingCellHorizintal(clauseList);
	//<=
	// SuroundingCellAndClauseHorizintal(clauseList,true);
	// SuroundingCellAndClauseHorizintal(clauseList,false);

	//Vertical
	//=>
	NotBOAllNotSuroundingCellVertical(clauseList);
	//<=
    // SuroundingCellAndClauseVertical(clauseList,true);
    // SuroundingCellAndClauseVertical(clauseList,false);

}
//Horizintal
//(¬B ∨ O ∨ ¬X0) ∧ (¬B ∨ O ∨ ¬X1) ∧ (¬B ∨ O ∨ ¬X2) ∧ (¬B ∨ O ∨ ¬X3))
void NotBOAllNotSuroundingCellHorizintal(List_Clause *clauseList){

	int k,i,j,r,t,k1;
	clause c;		
	for (k = 2; k < 4; k++){
	int boatSize = matchKBoatToNSizeofK(k);
	// printf("%d\n",boatSize);
		for (i = 0; i < GridSizeHeight; i++){	
            for(j = 0; j <= GridSizeWidth-boatSize;j++){
				for(r=i-1; r<=i+1;r+=2){
					for(t=j-1; t<=j+boatSize;t++){
						if(r>=0 && r<=GridSizeHeight-1 && t>=0 && t<=GridSizeWidth-1){
							c.size=0;

							for(k1 =StartBoat;k1<BoatCount;k1++){
								//-Xrtk
								addCell(&c,r,t,k1,true);
							}
							//-Bi,j,k
							addBoat(&c,i,j,k,true);
							//Ok
							addOrientation(&c,k,false);
							add_element_List_Clause(clauseList,&c);
							
						}
					}
				}
				if (j-1>=0){
					c.size=0;
					for(k1 =StartBoat;k1<BoatCount;k1++){
					//-Xrtk
						addCell(&c,r,t,k1,true);
					}
					//-Xi,j-1,k
					addCell(&c,i,j-1,k,true);
					//-Bi,j,k
					addBoat(&c,i,j,k,true);
					//Ok
					addOrientation(&c,k,false);
					add_element_List_Clause(clauseList,&c);
				}
				if(j+boatSize < GridSizeWidth){
					c.size=0;
					for(k1 =StartBoat;k1<BoatCount;k1++){
					//-Xrtk
						addCell(&c,r,t,k1,true);
					}
					//-Xi,j+n,k
					addCell(&c,i,j+boatSize,k,true);
					//-Bi,j,k
					addBoat(&c,i,j,k,true);
					//Ok
					addOrientation(&c,k,false);
					// print_Clause(c);
					add_element_List_Clause(clauseList,&c);
				}
				
			}
			
		}
	}
}
//((X0 ∨ X1 ∨ X2 ∨ X3 ∨ B) ∧ (X0 ∨ X1 ∨ X2 ∨ X3 ∨ ¬O) 
// if additionalLiteral == true -> boat in clause
// else -> orientation in clause
void SuroundingCellAndClauseHorizintal(List_Clause *clauseList, bool additionalLiteral){
	int k,i,j,r,t;
	clause c;
	for (k = StartBoat; k < BoatCount; k++){
		int boatSize = matchKBoatToNSizeofK(k);
		//GridSizeHeight
		for (i = 0; i < GridSizeHeight; i++){	
			//GridSizeWidth-boatSize
            for(j = 0; j <= GridSizeWidth-boatSize;j++){
				c.size=0;
				for(r=i-1; r<=i+1;r+=2){
					for(t=j-1; t<=j+boatSize;t++){
						if(r>=0 && r<=GridSizeHeight-1 && t>=0 && t<=GridSizeWidth-1){
							//Xrtk
							addCell(&c,r,t,k,false);
						}
					}
				}
				if(j+boatSize < GridSizeWidth){
					//Xi,j+n,k
					addCell(&c,i,j+boatSize,k,false);
				}
				if (j-1>=0){
					//Xi,j-1,k
					addCell(&c,i,j-1,k,false);
				}
				if(additionalLiteral){
					//Bi,j,k
					addBoat(&c,i,j,k,false);
				}else {
					//-Ok
					addOrientation(&c,k,true);
				}
				
				add_element_List_Clause(clauseList,&c);
			}
			
		}
	}
}
////////////////////////////////////////
//Vertical//
void NotBOAllNotSuroundingCellVertical(List_Clause *clauseList){

	int k,i,j,r,t,k1;

	clause c;
	for (k = StartBoat; k < BoatCount; k++){
	int boatSize = matchKBoatToNSizeofK(k);
		for (i = 0; i <= GridSizeHeight-boatSize; i++){	
            for(j = 0; j < GridSizeWidth;j++){
				for(t=i-1; t<=i+boatSize;t++){
					for(r=j-1; r<=j+1;r+=2){
						if(r>=0 && r<=GridSizeHeight-1 && t>=0 && t<=GridSizeWidth-1){
							c.size=0;
							for(k1 =StartBoat;k1<BoatCount;k1++){
								//-Xrtk
								addCell(&c,r,t,k1,true);
							}
							//-Xrtk
							addCell(&c,t,r,k,true);
							//-Bi,j,k
							addBoat(&c,i,j,k,true);
							//-Ok
							addOrientation(&c,k,true);
							add_element_List_Clause(clauseList,&c);
						}
					}
				}
				
				if (i-1>=0){
					c.size=0;
					for(k1 =StartBoat;k1<BoatCount;k1++){
					//-Xrtk
						addCell(&c,r,t,k1,true);
					}
					//-Xi-1,j,k
					addCell(&c,i-1,j,k,true);
					//-Bi,j,k
					addBoat(&c,i,j,k,true);
					//-Ok
					addOrientation(&c,k,true);
					//curr clause : -Xi-1,j,k + -Bi,j,k + -Ok
					add_element_List_Clause(clauseList,&c);
				}
				if(i+boatSize < GridSizeHeight){
					c.size=0;
					for(k1 =StartBoat;k1<BoatCount;k1++){
					//-Xrtk
						addCell(&c,r,t,k1,true);
					}
					//-Xi,j+n,k
					addCell(&c,i+boatSize,j,k,true);
					//-Bi,j,k
					addBoat(&c,i,j,k,true);
					//-Ok
					addOrientation(&c,k,true);
					//curr clause : -Xi+n,j,k + -Bi,j,k + -Ok
					add_element_List_Clause(clauseList,&c);
				}

				
				
			}
			
		}
	}
}
//((X0 ∨ X1 ∨ X2 ∨ X3 ∨ B) ∧ (X0 ∨ X1 ∨ X2 ∨ X3 ∨ O) 
// if additionalLiteral == true -> boat in clause
// else -> orientation in clause
void SuroundingCellAndClauseVertical(List_Clause *clauseList, bool additionalLiteral){
	int k,i,j,r,t;
	clause c;
	// int testI = 7,testJ = 4;
	for (k = StartBoat; k < BoatCount; k++){
		int boatSize = matchKBoatToNSizeofK(k);
		for (i = 0; i <= GridSizeHeight-boatSize; i++){	
            for(j = 0; j < GridSizeWidth;j++){
				c.size=0;
				for(t=i-1; t<=i+boatSize;t++){
					for(r=j-1; r<=j+1;r+=2){
						if(r>=0 && r<=GridSizeHeight-1 && t>=0 && t<=GridSizeWidth-1){
							//Xrtk
							addCell(&c,t,r,k,false);
						}
					}
				}
				if(i+boatSize < GridSizeHeight){
					//Xi+n,j,k
					addCell(&c,i+boatSize,j,k,false);
				}
				if (i-1>=0){
					//Xi-1,j,k
					addCell(&c,i-1,j,k,false);
				}
				if(additionalLiteral){
					//Bi,j,k
					addBoat(&c,i,j,k,false);
				}else {
					//Ok
					addOrientation(&c,k,false);
				}
				
				add_element_List_Clause(clauseList,&c);
			}
			
		}
	}
}

void nonExistingBoat(List_Clause *clauseList){
	int k;
	clause c;
	c.size=0;
	addBoat(&c,7,7,9,true);
	add_element_List_Clause(clauseList,&c);
	c.size=0;
	addBoat(&c,7,8,9,true);
	add_element_List_Clause(clauseList,&c);
	c.size=0;
	addBoat(&c,7,9,9,true);
	add_element_List_Clause(clauseList,&c);
	c.size=0;
	addBoat(&c,8,7,9,true);
	add_element_List_Clause(clauseList,&c);
	for (k = 7; k < BoatCount; k++){
		c.size=0;
		addBoat(&c,8,8,k,true);
		add_element_List_Clause(clauseList,&c);
	}
	for (k = 7; k < BoatCount; k++){
		c.size=0;
		addBoat(&c,8,9,k,true);
		add_element_List_Clause(clauseList,&c);
	}
	c.size=0;
	addBoat(&c,9,7,9,true);
	add_element_List_Clause(clauseList,&c);
	for (k = 7; k < BoatCount; k++){
		c.size=0;
		addBoat(&c,9,8,k,true);
		add_element_List_Clause(clauseList,&c);
	}
	for (k = 4; k < BoatCount; k++){
		c.size=0;
		addBoat(&c,9,9,k,true);
		add_element_List_Clause(clauseList,&c);
	}
}

void KChosesNCNF(List_Clause *clauseList, int row_list[],bool row){
	combination_list combList;
	combList.size = 0;
	combination currComb;
	clause newClause;
	int l,c,i,j,k,n;
	int p = 0;
	for(j=0;j<GridSizeHeight;j++){
		n = row_list[j];
		printf("n is %d\n",n);
		if(n<-1){
			printf("Error");
			return;
		}
		if(GridSizeHeight<n){
			printf("Error");
			return;
		}
		for(l=0; l<=GridSizeWidth;l++){
			if(l!=n){
				combList.size = 0;
				createCombination(l,&combList,GridSizeHeight);
				// printf("l = %d\n",l);
				// print_all_combinations(combList);
				for(c=0;c<combList.size;c++){
					currComb = combList.tab[c];
					for(k=StartBoat;k<BoatCount;k++){
						newClause.size = 0;
						for(i=0;i<GridSizeHeight;i++){
							if(i == currComb.tab[p] && l>0){
								// printf("%d",currComb.tab[p]);
								if(row){
									addCell(&newClause,i,j,k,true);
								}else{
									addCell(&newClause,j,i,k,true);
								}
								p++;
							}else{
								if(row){
									addCell(&newClause,i,j,k,false);
								}else{
									addCell(&newClause,j,i,k,false);
								}
							}
						}
						p=0;
						// print_Clause(newClause);
						// printf("\n");
						add_element_List_Clause(clauseList, &newClause);

					}
					
				}

			}
		}
	}
}


/////////////////////////
void allConstraints(List_Clause *clauseList,int column_list[],int line_list[]){
	contiguousCell(clauseList);
    thereIsAtLeastOneBoatK(clauseList);
    thereIsAtMostOneBoatK(clauseList);
    oneBoatOrSectionOfBoat(clauseList);
	noBoatTouchesAnother(clauseList);
	nonExistingBoat(clauseList);
	TestConstr(clauseList);

}

void print_In_DIMACS_Format(List_Clause *clauseList, FILE *fileOut){
	assert (clauseList); 
    Node_Clause *c;
    c = clauseList->first;
	fprintf(fileOut,"p cnf 2010 %d\n",clauseList->size);
    while (c!=NULL) {
        if(c->next==NULL){
            print_Clause_DIMACS_Format(c->data,fileOut);
        }else{
			print_Clause_DIMACS_Format(c->data,fileOut);
            fprintf(fileOut,"\n");
        }
        c = c->next;
    }
}

void print_Clause_DIMACS_Format(clause c, FILE *fileOut){
	int k;
	int n = c.size;
	literal l;
	
	for (k = 0; k < n; k++)
	{	
		l = c.tab[k];
		if(l.negation){
			fprintf(fileOut,"-%d ",l.name);

		}else{
			fprintf(fileOut,"%d ",l.name);
		}

	} 
	fprintf(fileOut,"0");
}



