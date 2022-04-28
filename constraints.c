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
/*depending on the k returns the size of thr boat*/
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

// (¬X1 ∨ ¬X2 ∨ ¬X3 ∨ ¬X4 ∨ B)
void allNotCellXVericalandB(List_Clause *clauseList){
	int k,i,j,n;
	for (k = 0; k < BoatCount; k++){
		int boatSize = matchKBoatToNSizeofK(k);
		for(j = 0; j < GridSizeWidth ;j++){
			for (i = 0; i <= GridSizeHeight-boatSize; i++){
				clause c;
				c.size =0;
				for(n = 0; n <= boatSize-1;n++){
					// l.name = 100*(i+n)+10*j+k;
					// l.negation = true;
					// add_element_Clause(&c,l);
					addCell(&c,i+n,j,k,true);
				}
				// l.name = 1000+100*i+10*j+k;
				// l.negation = false;
				// add_element_Clause(&c,l);
				addBoat(&c,i,j,k,false);
				add_element_List_Clause(clauseList,&c);
			}
			
		}
	}
}

// (¬X1 ∨ ¬X2 ∨ ¬X3 ∨ ¬X4 ∨ O)
void allNotCellVericalXandO(List_Clause *clauseList){
	int k,i,j,n;
	// literal l;
	for (k = 0; k < BoatCount; k++){
		int boatSize = matchKBoatToNSizeofK(k);
		for(j = 0; j < GridSizeWidth ;j++){
			for (i = 0; i <= GridSizeHeight-boatSize; i++){
				clause c;
				c.size =0;
				for(n = 0; n <= boatSize-1;n++){
					// l.name = 100*(i+n)+10*j+k;
					// l.negation = true;					
					// add_element_Clause(&c,l);
					addCell(&c,i+n,j,k,true);
				}
				// l.name = 2000+k;
				// l.negation = false;
				// add_element_Clause(&c,l);
				addOrientation(&c,k,false);
				add_element_List_Clause(clauseList,&c);
			}
			
		}
	}
}

//   (¬X1 ∨ ¬X5 ∨ ¬X6 ∨ ¬X7 ∨ B) 
void allNotCellXHorizontalandB(List_Clause *clauseList){
	int k,i,j,n;
	// literal l;
	for (k = 4; k < BoatCount; k++){
		int boatSize = matchKBoatToNSizeofK(k);
		for (i = 0; i < GridSizeHeight; i++){
            for(j = 0; j <= GridSizeWidth-boatSize ;j++){
				clause c;
				c.size =0;
				for(n = 0; n <= boatSize-1;n++){
					// l.name = 100*i+10*(j+n)+k;
					// l.negation = true;
					// add_element_Clause(&c,l);
					addCell(&c,i,j+n,k,true);
				}
				// l.name = 1000+100*i+10*j+k;
				// l.negation = false;
				// add_element_Clause(&c,l);
				addBoat(&c,i,j,k,false);
				add_element_List_Clause(clauseList,&c);
			}
			
		}
	}
}

//    (¬X1 ∨ ¬X5 ∨ ¬X6 ∨ ¬X7 ∨ ¬O) 
void allNotCellXHorizontalandNotO(List_Clause *clauseList){
	int k,i,j,n;
	// literal l;
	for (k = 4; k < BoatCount; k++){
		int boatSize = matchKBoatToNSizeofK(k);
		for (i = 0; i < GridSizeHeight; i++){
            for(j = 0; j <= GridSizeWidth-boatSize ;j++){
				clause c;
				c.size =0;
				for(n = 0; n <= boatSize-1;n++){
					addCell(&c,i,j+n,k,true);
					// l.name = 100*i+10*(j+n)+k;
					// l.negation = true;
					// add_element_Clause(&c,l);
				}
				addOrientation(&c,k,true);
				// l.name = 2000+k;
				// l.negation = true;
				// add_element_Clause(&c,l);
				add_element_List_Clause(clauseList,&c);
			}
			
		}
	}
}

// (¬Bi,j,k ∨ ¬O ∨ Xi,j) ∧ (¬Bi,j,k ∨ ¬O ∨ xi+1,j) ∧ (¬Bi,j,k ∨ ¬O ∨ xi+2,j) ∧ (¬Bi,j,k ∨ ¬O ∨ xi+3,j)
void notBnotOCellXVerical(List_Clause *clauseList){
    int k,i,j,n;
	// literal l;
    
	for (k = 0; k < BoatCount; k++){
		int boatSize = matchKBoatToNSizeofK(k);  
        for(j = 0; j < GridSizeWidth ;j++){
		    for (i = 0; i <= GridSizeHeight-boatSize; i++){
                for(n = 0; n <= boatSize-1;n++){
                    clause c;
                    c.size = 0;
                    //-Bi,j,k  
					addBoat(&c,i,j,k,true);	
		    	    // l.name = 1000+100*i+10*j+k;
		    	    // l.negation = true;
		    	    // add_element_Clause(&c,l);
                    //-Ok  
					addOrientation(&c,k,true);	
		    	    // l.name = 2000+k;
		    	    // l.negation = true;
		    	    // add_element_Clause(&c,l);
                    //Xi,j,k
					addCell(&c,i+n,j,k,false);
		    	    // l.name = 100*(i+n)+10*j+k;
		    	    // l.negation = false;
		    	    // add_element_Clause(&c,l);
                    add_element_List_Clause(clauseList,&c);
                }
		    	
		    }
            
        }
		
	}
}

//    (¬B ∨ O ∨ X1) ∧ (¬B ∨ O ∨ X5) ∧ (¬B ∨ O ∨ X6) ∧ (¬B ∨ O ∨ X7)
void notBOCellXVHorizontal(List_Clause *clauseList){
	int k,i,j,n;
	// literal l;
	for (k = 0; k < BoatCount; k++){
		int boatSize = matchKBoatToNSizeofK(k);
		for (i = 0; i < GridSizeHeight; i++){
            for(j = 0; j <= GridSizeWidth-boatSize ;j++){
                for(n = 0; n <= boatSize-1;n++){
                    clause c;
                    c.size = 0;
                    //-Bi,j,k  	
					addBoat(&c,i,j,k,true);
		    	    // l.name = 1000+100*i+10*j+k;
		    	    // l.negation = true;
		    	    // add_element_Clause(&c,l);
                    //Ok
					addOrientation(&c,k,false);
		    	    // l.name = 2000+k;
		    	    // l.negation = false;
		    	    // add_element_Clause(&c,l);
                    //Xi,j,k
					addCell(&c,i+n,j,k,false);
		    	    // l.name = 100*(i+n)+10*j+k;
		    	    // l.negation = false;
		    	    // add_element_Clause(&c,l);
                    add_element_List_Clause(clauseList,&c);
                }
            }
		}
	}
}

void contiguousCell(List_Clause *clauseList){
	// (¬X1 ∨ ¬X2 ∨ ¬X3 ∨ ¬X4 ∨ B)
	allNotCellXVericalandB(clauseList);
	// (¬X1 ∨ ¬X2 ∨ ¬X3 ∨ ¬X4 ∨ O)
	allNotCellVericalXandO(clauseList);
    // (¬X1 ∨ ¬X5 ∨ ¬X6 ∨ ¬X7 ∨ B) 
    allNotCellXHorizontalandB(clauseList);
    // (¬X1 ∨ ¬X5 ∨ ¬X6 ∨ ¬X7 ∨ ¬O) 
    allNotCellXHorizontalandNotO(clauseList);
    // (¬Bi,j,k ∨ ¬O ∨ Xi,j) ∧ (¬Bi,j,k ∨ ¬O ∨ xi+1,j) ∧ (¬Bi,j,k ∨ ¬O ∨ xi+2,j) ∧ (¬Bi,j,k ∨ ¬O ∨ xi+3,j)
    notBnotOCellXVerical(clauseList);
    //  (¬B ∨ O ∨ X1) ∧ (¬B ∨ O ∨ X5) ∧ (¬B ∨ O ∨ X6) ∧ (¬B ∨ O ∨ X7)
    notBOCellXVHorizontal(clauseList);
	
}

void thereIsAtLeastOneBoatK(List_Clause *clauseList){
	int k,i,j;
	// literal l;
	for (k = 0; k < BoatCount; k++){
		int boatSize = matchKBoatToNSizeofK(k);
		for (i = 0; i < GridSizeHeight; i++){
            for(j = 0; j < GridSizeWidth ;j++){
				clause c;
                c.size = 0;
				//Bi,j,k  
		    	// l.name = 1000+100*i+10*j+k;
		    	// l.negation = false;
				if((i<=GridSizeHeight-boatSize || j<=GridSizeWidth-boatSize)){
					//add_element_Clause(&c,l);
					addBoat(&c,i,j,k,false);
                	add_element_List_Clause(clauseList,&c);
				}
                
            }
		}
	}
}

void thereIsAtMostOneBoatK(List_Clause *clauseList){
	int k,i,j,ip,jp;
	// literal l;
	for (k = 4; k < 5; k++){
		int boatSize = matchKBoatToNSizeofK(k);
		for (i = 0; i < GridSizeHeight; i++){
            for(j = 0; j < GridSizeWidth ;j++){
				for (ip = 0; ip < GridSizeHeight; ip++){
           			for(jp = 0; jp < GridSizeWidth ;jp++){
						clause c;
                		c.size = 0;
						if((i<=GridSizeHeight-boatSize || j<=GridSizeWidth-boatSize)&&(ip<=GridSizeHeight-boatSize || jp<=GridSizeWidth-boatSize)){
							//B_i,j,k  
							addBoat(&c,i,j,k,true);
		    				// l.name = 1000+100*i+10*j+k;
		    				// l.negation = true;
							// add_element_Clause(&c,l);
							//B_ip,jp,k 
							addBoat(&c,ip,jp,k,true);
							// l.name = 1000+100*ip+10*jp+k;
		    				// l.negation = true;
							// add_element_Clause(&c,l);
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
	for (i = 0; i < GridSizeHeight; i++){
		for(j = 0; j < GridSizeWidth ;j++){
			for (k1 = 0; k1 < BoatCount; k1++){
				for(k2 = k1+1; k2 < BoatCount ;k2++){
					int boatSizeK1 = matchKBoatToNSizeofK(k1);
					int boatSizeK2 = matchKBoatToNSizeofK(k2);
					if((i<=GridSizeHeight-boatSizeK1 || j<=GridSizeWidth-boatSizeK1)&&(i<=GridSizeHeight-boatSizeK2 || j<=GridSizeWidth-boatSizeK2)){

						clause c;
						c.size = 0;
						//-X_i,j,k1
            			// l.name = 100*i+10*j+k1;
		    			// l.negation = true;
						// add_element_Clause(&c,l);
						addCell(&c,i,j,k1,true);

						//-X_i1,j1,k2
						// l.name = 1000+100*i+10*j+k2;
		    			// l.negation = true;
						// add_element_Clause(&c,l);
						addBoat(&c,i,j,k1,true);
                		add_element_List_Clause(clauseList,&c);
					}
				}
			}

		}
	}
}


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

void createCombination(int r,combination_list* comb_list)
{   
	int arr[]={0,1,2,3,4,5,6,7,8,9};
    int n = sizeof(arr)/sizeof(arr[0]);
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

void NChosesKColumnFirstPart(List_Clause *clauseList,int column_list[]){
	int i,j,c,l,k;
	int currR;
	combination_list comb_list;
	combination currComb;
	comb_list.size = 0;
	for(j=0; j<GridSizeHeight; j++){
		currR = column_list[j];
    	int m = currR +1;
        comb_list.size = 0;
    	createCombination(m,&comb_list);
		//for every possible combination
		for(c=0; c<comb_list.size; c++){
			clause clause;
			clause.size = 0;
			//the current combination 
			currComb = comb_list.tab[c];
			//for every element in the current combination
			for(l=0; l<currComb.size; l++){
				i = currComb.tab[l];
				for(k=0;k<BoatCount;k++){
					addCell(&clause,i,j,k,true);
				}
			}
            add_element_List_Clause(clauseList,&clause);
		}

	}

	
}

void NChosesKColumnSecondPart(List_Clause *clauseList,int column_list[]){
	int i,j,c,l,k;
	int currR;
	combination_list comb_list;
	combination currComb;
	comb_list.size = 0;
	for(j=0; j<GridSizeHeight; j++){
		currR = column_list[j];	
    	int m = GridSizeHeight-currR+1;
        comb_list.size = 0;
    	createCombination(m,&comb_list);
		//for every possible combination
		for(c=0; c<comb_list.size; c++){
			clause clause;
			clause.size = 0;
			//the current combination 
			currComb = comb_list.tab[c];
			//for every element in the current combination
			for(l=0; l<currComb.size; l++){
				i = currComb.tab[l];
				for(k=0;k<BoatCount;k++){
					addCell(&clause,i,j,k,false);
					// literal.name = 100*i+10*j+k;
					// literal.negation = false;
					// add_element_Clause(&clause,literal);
				}
			}
            add_element_List_Clause(clauseList,&clause);

		}
	}
}

void NChosesKColumn(List_Clause *clauseList,int column_list[]){
	NChosesKColumnFirstPart(clauseList,column_list);
	NChosesKColumnSecondPart(clauseList,column_list);

}

void NChosesKLineFirstPart(List_Clause *clauseList,int line_list[]){
	int i,j,c,l,k;
	int currR;
	combination_list comb_list;
	combination currComb;
	comb_list.size = 0;
	for(i=0; i<GridSizeWidth; i++){
		currR = line_list[j];
    	int m = currR +1;
        comb_list.size = 0;
    	createCombination(m,&comb_list);
		//for every possible combination
		for(c=0; c<comb_list.size; c++){
			clause clause;
			clause.size = 0;
			//the current combination 
			currComb = comb_list.tab[c];
			
			//for every element in the current combination
			for(l=0; l<currComb.size; l++){
				j = currComb.tab[l];
				for(k=0;k<BoatCount;k++){
					addCell(&clause,i,j,k,true);
					// literal.name = 100*i+10*j+k;
					// literal.negation = true;
					// add_element_Clause(&clause,literal);
				}
			}
            add_element_List_Clause(clauseList,&clause);

		}
	}
	
}

void NChosesKLineSecondPart(List_Clause *clauseList,int line_list[]){
	int i,j,c,l,k,m;
	int currR;
	combination_list comb_list;
	combination currComb;
	comb_list.size = 0;
	for(i=0; i<GridSizeWidth; i++){
		currR = line_list[j];
    	m = GridSizeHeight-currR+1;
        comb_list.size = 0;
    	createCombination(m,&comb_list);
		//for every possible combination
		for(c=0; c<comb_list.size; c++){
			clause clause;
			clause.size = 0;
			//the current combination 
			currComb = comb_list.tab[c];
			
			//for every element in the current combination
			for(l=0; l<currComb.size; l++){
				j = currComb.tab[l];
				for(k=0;k<BoatCount;k++){
					addCell(&clause,i,j,k,false);
					// literal.name = 100*i+10*j+k;
					// literal.negation = false;
					// add_element_Clause(&clause,literal);
				}
			}
            add_element_List_Clause(clauseList,&clause);
		}
	}
}

void NChosesKLine(List_Clause *clauseList,int line_list[]){
	NChosesKLineFirstPart(clauseList,line_list);
	NChosesKLineSecondPart(clauseList,line_list);
}

//No boat touches anoter boat

/////////////////////////
void allConstrants(List_Clause *clauseList,int column_list[],int line_list[]){
	contiguousCell(clauseList);
    thereIsAtLeastOneBoatK(clauseList);
    thereIsAtMostOneBoatK(clauseList);
    oneBoatOrSectionOfBoat(clauseList);
	NChosesKColumn(clauseList,column_list);
    NChosesKLine(clauseList,line_list);
	// noBoatTouchesAnother(clauseList);
}

void print_In_DIMACS_Format(List_Clause *clauseList, FILE *fileOut){
	assert (clauseList); 
    Node_Clause *c;
    c = clauseList->first;
	fprintf(fileOut,"p cnf 2009 %d\n",clauseList->size);
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

