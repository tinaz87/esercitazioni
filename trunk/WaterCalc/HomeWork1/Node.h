#pragma once
#include <vector>


struct simpleNode{

	float value;
	struct simpleNode* up;
	struct simpleNode* down;
	struct simpleNode* left;
	struct simpleNode* right;

};

struct simpleNode* NewNode(float data) {
	struct simpleNode* node = new(struct simpleNode);    // "new" is like "malloc"
	node->value = data;
	node->left = NULL;
	node->right = NULL;
	node->down=NULL;
	node->up=NULL;

	return(node);
} 


class MatrixNodes{
	
	public:
		
		explicit MatrixNodes():p_col(1),p_row(1){

			node = NewNode(-1.0f);
		}

		MatrixNodes(const int row,const int col){

			this->p_row=1;
			this->p_col=1;
			this->columns=col;
			this->rows=row;
			node=NewNode(-1);
			createMatrixNodes(std::vector<float>(row*col,0));


		}

		void setLimitsRowsColumns(const int i_rows,const int i_columns){
			rows= i_rows;
			columns = i_columns;
		}
		
		float getValueAtPosition(const int r,const int c) const{

			goToPosition(r,c);
			return node->value;

		}
		
		void createMatrixNodes(std::vector<float> i_vector){

			std::vector<float>::iterator it;
			it = i_vector.begin();
			

			for(int k=0;k<rows*columns;++k){
				
					
					if( p_col > columns){

						++p_row;
						--k;
						p_col=1;
						node=node->down;

					}else{

						if(p_row==1){

							simpleNode* tempNode_1= new simpleNode();
							simpleNode* tempNode_2= new simpleNode();

							if(p_col!=columns && p_row!=rows){

								tempNode_1->left = node;

								node->right=  tempNode_1;

								tempNode_2->up = node;

								node->down = tempNode_2;

								node->value= it[k];

								node=node->right;

							}else{

								node->down = tempNode_2;

								tempNode_2->up = node;

								node->value= it[k];

								
							}

						}else{

							if((p_row%2)==0){ // da dx a sx

								if(p_col!=columns && p_row!=rows){

									node->left=node->up->left->down;

									node->up->left->down->right=node;

									node->value=it[p_row*columns-p_col];

									node->down=new simpleNode();

									node->down->up= node;

									node=node->left;

								}else{ // da dx a sx

									if(p_col==columns && p_row!=rows){ // sono alla prima/ultima colonna e non all'ultima riga

										node->down=new simpleNode();

										node->down->up=node;
										
										node->value= it[p_row*columns-p_col];

									}else{
										
										if(p_col!=columns && p_row==rows){

											node->left=node->up->left->down;

											node->up->left->down->right=node;

											node->value= it[p_row*columns-p_col];

											node= node->left;

										}

										if(p_col==columns && p_row==rows)
											node->value= it[p_row*columns-p_col];

										
									}

								}
							}else //da sx a dx
							{

								if(p_col!=columns && p_row!=rows){

									node->right=node->up->right->down;

									node->up->right->down->left=node;

									node->value=it[k];

									node->down=new simpleNode();

									node->down->up= node;

									node=node->right;

								}else{ // da sx a dx

									if(p_col==columns && p_row!=rows){ // sono alla prima/ultima colonna e non all'ultima riga

										node->down=new simpleNode();

										node->down->up=node;

										node->value= it[k];

										

									}else{

										if(p_col!=columns && p_row==rows){

											node->right=node->up->right->down;

											node->up->right->down->left=node;

											node->value= it[k];

											node=node->right;
										}

										if(p_col==columns && p_row==rows)
											node->value= it[k];


									}

								}


							}


						}

						++p_col;

					}
			}

			p_col=(p_row%2==0)?1:p_col-1;

			goToPosition(1,1);

		}


private:
		void goToPosition(const int i_row,const int i_col) const{


			while(p_row!=i_row){

				if(p_row>i_row){
					node=node->up;
					--p_row;
				}
				if(p_row<i_row){
					node=node->down;
					++p_row;
				}
			}

			while(p_col!=i_col){

				if(p_col>i_col){
					node=node->left;
					--p_col;
				}
				if(p_col<i_col){
					node=node->right;
					++p_col;
				}

			}

		}

		mutable simpleNode* node;


		mutable int p_row;
		mutable int p_col;

		float value;
		int rows;
		int columns;


};

