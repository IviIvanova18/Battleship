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
	literal l;
	for (k = 0; k < BoatCount; k++){
		int boatSize = matchKBoatToNSizeofK(k);
		for(j = 0; j < GridSizeWidth ;j++){
			for (i = 0; i <= GridSizeHeight-boatSize; i++){
				clause c;
				c.size =0;
				for(n = 0; n <= boatSize-1;n++){
					l.name = 100*(i+n)+10*j+k;
					l.negation = true;
					
					add_element_Clause(&c,l);
				}
				l.name = 1000+100*i+10*j+k;
				l.negation = false;
				add_element_Clause(&c,l);
				add_element_List_Clause(clauseList,&c);
			}
			
		}
	}
}

// (¬X1 ∨ ¬X2 ∨ ¬X3 ∨ ¬X4 ∨ O)
void allNotCellVericalXandO(List_Clause *clauseList){
	int k,i,j,n;
	literal l;
	for (k = 0; k < BoatCount; k++){
		int boatSize = matchKBoatToNSizeofK(k);
		for(j = 0; j < GridSizeWidth ;j++){
			for (i = 0; i <= GridSizeHeight-boatSize; i++){
				clause c;
				c.size =0;
				for(n = 0; n <= boatSize-1;n++){
					l.name = 100*(i+n)+10*j+k;
					l.negation = true;					
					add_element_Clause(&c,l);
				}
				l.name = 2000+k;
				l.negation = false;
				add_element_Clause(&c,l);
				add_element_List_Clause(clauseList,&c);
			}
			
		}
	}
}

//   (¬X1 ∨ ¬X5 ∨ ¬X6 ∨ ¬X7 ∨ B) 
void allNotCellXHorizontalandB(List_Clause *clauseList){
	int k,i,j,n;
	literal l;
	for (k = 4; k < BoatCount; k++){
		int boatSize = matchKBoatToNSizeofK(k);
		for (i = 0; i < GridSizeHeight; i++){
            for(j = 0; j <= GridSizeWidth-boatSize ;j++){
				clause c;
				c.size =0;
				for(n = 0; n <= boatSize-1;n++){
					l.name = 100*i+10*(j+n)+k;
					l.negation = true;
					
					add_element_Clause(&c,l);
				}
				l.name = 1000+100*i+10*j+k;
				l.negation = false;
				add_element_Clause(&c,l);
				add_element_List_Clause(clauseList,&c);
			}
			
		}
	}
}

//    (¬X1 ∨ ¬X5 ∨ ¬X6 ∨ ¬X7 ∨ ¬O) 
void allNotCellXHorizontalandNotO(List_Clause *clauseList){
	int k,i,j,n;
	literal l;
	for (k = 4; k < BoatCount; k++){
		int boatSize = matchKBoatToNSizeofK(k);
		for (i = 0; i < GridSizeHeight; i++){
            for(j = 0; j <= GridSizeWidth-boatSize ;j++){
				clause c;
				c.size =0;
				for(n = 0; n <= boatSize-1;n++){
					l.name = 100*i+10*(j+n)+k;
					l.negation = true;
					add_element_Clause(&c,l);
				}
				l.name = 2000+k;
				l.negation = true;
				add_element_Clause(&c,l);
				add_element_List_Clause(clauseList,&c);
			}
			
		}
	}
}

// (¬Bi,j,k ∨ ¬O ∨ Xi,j) ∧ (¬Bi,j,k ∨ ¬O ∨ xi+1,j) ∧ (¬Bi,j,k ∨ ¬O ∨ xi+2,j) ∧ (¬Bi,j,k ∨ ¬O ∨ xi+3,j)
void notBnotOCellXVerical(List_Clause *clauseList){
    int k,i,j,n;
	literal l;
    
	for (k = 0; k < BoatCount; k++){
		int boatSize = matchKBoatToNSizeofK(k);  
        for(j = 0; j < GridSizeWidth ;j++){
		    for (i = 0; i <= GridSizeHeight-boatSize; i++){
                for(n = 0; n <= boatSize-1;n++){
                    clause c;
                    c.size = 0;
                    //-Bi,j,k  	
		    	    l.name = 1000+100*i+10*j+k;
		    	    l.negation = true;
		    	    add_element_Clause(&c,l);
                    //-Ok  	
		    	    l.name = 2000+k;
		    	    l.negation = true;
		    	    add_element_Clause(&c,l);
                    //Xi,j,k
		    	    l.name = 100*(i+n)+10*j+k;
		    	    l.negation = false;
		    	    add_element_Clause(&c,l);
                    add_element_List_Clause(clauseList,&c);
                }
		    	
		    }
            
        }
		
	}
}

//    (¬B ∨ O ∨ X1) ∧ (¬B ∨ O ∨ X5) ∧ (¬B ∨ O ∨ X6) ∧ (¬B ∨ O ∨ X7)
void notBOCellXVHorizontal(List_Clause *clauseList){
	int k,i,j,n;
	literal l;
	for (k = 0; k < BoatCount; k++){
		int boatSize = matchKBoatToNSizeofK(k);
		for (i = 0; i < GridSizeHeight; i++){
            for(j = 0; j <= GridSizeWidth-boatSize ;j++){
                for(n = 0; n <= boatSize-1;n++){
                    clause c;
                    c.size = 0;
                    //-Bi,j,k  	
		    	    l.name = 1000+100*i+10*j+k;
		    	    l.negation = true;
		    	    add_element_Clause(&c,l);
                    //Ok
		    	    l.name = 2000+k;
		    	    l.negation = false;
		    	    add_element_Clause(&c,l);
                    //Xi,j,k
		    	    l.name = 100*(i+n)+10*j+k;
		    	    l.negation = false;
		    	    add_element_Clause(&c,l);
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
	literal l;
	for (k = 0; k < BoatCount; k++){
		int boatSize = matchKBoatToNSizeofK(k);
		for (i = 0; i < GridSizeHeight; i++){
            for(j = 0; j < GridSizeWidth ;j++){
				clause c;
                c.size = 0;
				//Bi,j,k  
		    	l.name = 1000+100*i+10*j+k;
		    	l.negation = false;
				if((i<=GridSizeHeight-boatSize || j<=GridSizeWidth-boatSize)){
					add_element_Clause(&c,l);
                	add_element_List_Clause(clauseList,&c);
				}
                
            }
		}
	}
}

void thereIsAtMostOneBoatK(List_Clause *clauseList){
	int k,i,j,ip,jp;
	literal l;
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
		    				l.name = 1000+100*i+10*j+k;
		    				l.negation = true;
							add_element_Clause(&c,l);
							l.name = 1000+100*ip+10*jp+k;
		    				l.negation = true;
							//B_ip,jp,k 
							add_element_Clause(&c,l);
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
	literal l;
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
            			l.name = 100*i+10*j+k1;
		    			l.negation = true;
						add_element_Clause(&c,l);
						l.name = 1000+100*i+10*j+k2;
		    			l.negation = true;
						//-X_i1,j1,k2
						add_element_Clause(&c,l);
                		add_element_List_Clause(clauseList,&c);
					}
				}
			}

		}
	}
}

void allConstrants(List_Clause *clauseList){
	contiguousCell(clauseList);
    thereIsAtLeastOneBoatK(clauseList);
    thereIsAtMostOneBoatK(clauseList);
    oneBoatOrSectionOfBoat(clauseList);
}

