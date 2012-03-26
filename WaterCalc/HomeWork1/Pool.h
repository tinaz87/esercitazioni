#pragma once

#include "PersonalMatrix.h"
#include <algorithm>

#define MIN_VALUE std::numeric_limits<float>::max()

class Pool{

public:
	
	Pool(float height,float width):m_3_water(0),P_pool(){	area = height*width; }

	explicit Pool():m_3_water(0),P_pool(){	area = 1; }

	PersonalMatrix FindPool(const PersonalMatrix& originalMatrix);

	float getM3water(){
		return m_3_water;
	}

	float getBlockArea(){
		return area;
	}

private:

	PersonalMatrix PrepareSupportsMatrix(const PersonalMatrix& originalMatrix);

	/*
		isHis mi dice se il minimo che hotrovato appartiene all' intorno della cella considerata (OriginalMatrix(i,j))
	*/
	float touchNeighborsPoolAndFindMin(std::vector<pair<int,int>>& vector_touch,const PersonalMatrix& originalMatrix,PersonalMatrix& node_visited_matrix,int i,int j,float min,bool& isHis);

	//void fixPool(const PersonalMatrix& originalMatrix);

	//bool checkIAlone(int r,int c,const PersonalMatrix& originalMatrix);

	bool FindWall(vector<pair<int,int>>& i_vect,const PersonalMatrix& originalMatrix,const int min );

	PersonalMatrix P_pool;

	int p_rows;
	int p_columns;

	float area;
	float m_3_water;

};


/*
Il vettore contiene una serie di coppie che rappresentano il percorso dell'acqua, il minimo è la cella piu piu bassa che non puo contenere acqua 
trovata lungo il percorso.
*/
bool Pool::FindWall(vector<pair<int,int>>& i_vect,const PersonalMatrix& originalMatrix,const int min ){

vector<pair<int,int>> temp3;

bool isThereWall=false;

for (int k=0;k<i_vect.size();++k) // non mi serve guardare il primo o l'ultimo
{
	pair<int,int> p = i_vect[k];
	int r=p.first;
	int c=p.second;

	for (int i=-1;i<=1;++i)
	{
		for (int j=-1;j<=1;++j)
		{			
			if ( i!=0 || j!=0){

					if(i!=0)
						j=0;

					pair<int,int> near_=make_pair(i+r,j+c);

					vector<pair<int,int>>::iterator it;
				
					it = find(i_vect.begin(),i_vect.end(),near_); // se non trova corrispondenza torna last

					if( it != i_vect.end()){
						pair<int,int> val = *it;

						if( val.first == r-1 && val.second == c || val.first == r+1 && val.second == c ||
							val.first == r && val.second == c-1 || val.first == r && val.second == c+1 ){// se true ho trovato un vicino
							temp3.push_back(val);
					
							if (temp3.size()==2)
							{
								pair<int,int> near_1 = temp3.back();
								float val_1 = originalMatrix(near_1.first,near_1.second);
								temp3.pop_back();

								pair<int,int> near_2 = temp3.back();
								float val_2 = originalMatrix(near_2.first,near_2.second);
								temp3.pop_back();

								float wall = originalMatrix(r,c);
								if( min -  wall < 0 && val_1 < wall && val_2 < wall){

									//cout<<"WALL "<<r<<";"<<c<<endl;
									P_pool(r,c)=0;

									isThereWall = true;

								}else{
						
									if ( val_1 < wall )
										temp3.push_back(near_1);

									else
										temp3.push_back(near_2);



								}
							
							}

							
						}
					}

					if(i!=0)
						break;

				}

			}
		}

		temp3.clear();
	}

//std::cout<<"WALL \n\n"<<std::endl;
//P_pool.printMatrix();

//std::cout<<"\n\n"<<std::endl;
return isThereWall;

}



/************************************************************************/
/*	
	ORIGINAL MATRIX
	1 2 3 44 5 6
	2 22 2 22 0 234
	0 0 0 2 33 32
	0 2 33 4 4 55


	SUPPORT MATRIX
	0	0	0	0	0	0
	0	0	1	0	5	0
	0	0	0	0	0	0
	0	0	0	0	0	0
																		*/
/************************************************************************/
PersonalMatrix Pool::FindPool(const PersonalMatrix& originalMatrix ){

	
	P_pool = PrepareSupportsMatrix(originalMatrix);

	PersonalMatrix node_finish(p_rows,p_columns);

	PersonalMatrix node_visited(p_rows,p_columns);

	node_visited.Reset();

	std::vector<pair<int,int>> node_touched;
	std::vector<pair<int,int>> node_visited_vector;

	float min=MIN_VALUE;


	for(int i=1;i<p_rows;++i){

		for(int j=1;j<p_columns-1;++j){

			if( node_visited(i,j)<1 ){

				if (!node_touched.empty())
				{
					pair<int,int> t;

					t=node_touched.back();

					node_touched.pop_back();

					i=t.first;
					j=t.second;

				}else{

					bool wall = false;

					if(!node_visited_vector.empty())
						wall=FindWall(node_visited_vector,originalMatrix,min);

					if(!node_visited_vector.empty() && !wall){

						while (!node_visited_vector.empty())
						{
							pair<int,int> p;

							p=node_visited_vector.back();

							node_visited_vector.pop_back();

							int row=p.first;
							int col=p.second;

							float val=originalMatrix(row,col);
							float result = min - val; 


							if( result < 0 ){

								P_pool(row,col)=0;

								//if(!node_visited_vector.empty() && first){ // caso particolare
								//	
								//	p=node_visited_vector[node_visited_vector.size()-1];

								//	int r=p.first;
								//	int c=p.second;

								//	if( min - originalMatrix(r,c) < 0 ){
								//		
								//		P_pool(row,col)=1;	// do un'altra chance alla cella
								//		P_pool(r,c)=0;
								//		node_finish(r,c)=1;

								//	}else
								//		node_finish(row,col)=1;

								//}else{

								//
								//	node_finish(row,col)=1;
								//
								//
								//}

								//node_touched.clear();
								//node_visited_vector.clear();

								//node_finish(row,col)=1;

								//node_visited.Reset();

								//if(pre_row >= 0){
								//					
								//	
								//	bool alone = checkIAlone(pre_row,pre_col,originalMatrix);

								//	if(alone)
								//		m_3_water -= pre_res;

								//}

							}else{

								P_pool(row,col)=result;
								
								node_finish(row,col)=1;
								

								m_3_water += result;

							}

							//first = false;
							//pre_col = col;
							//pre_row = row;

						}

						min=MIN_VALUE;
						i=1;
						j=1;

					}else{


						node_touched.clear();
						node_visited_vector.clear();
						node_visited.Reset();

						min=MIN_VALUE;
						
						if(wall){
							i=1;
							j=1;
						}

					}


				}

				float v1=P_pool(i,j);

				if( v1 > 0 && node_visited(i,j) < 1 && node_finish(i,j) < 1 ){

					node_visited_vector.push_back(make_pair(i,j));
					node_visited(i,j)=1;

					bool isHis=false;
					min = touchNeighborsPoolAndFindMin(node_touched,originalMatrix,node_visited,i,j,min,isHis);

					if (originalMatrix(i,j) > min && isHis)
					{
						node_touched.clear();
						node_visited_vector.clear();
						node_visited.Reset();

						min=MIN_VALUE;
						P_pool(i,j)=0;

						i=1;
						j=1;

					}

				}

				

			}

		}

	}

	return P_pool;


}

/*****************
	Prepara le matrici colonna e riga di supporto per trovare poi le celle ad essere candidate ad essere contenitori d'acqua. 

	ROW SUPPORT MATRIX
	0	0	0	0	0	0
	0	0	20	0	22	0
	0	0	0	0	0	0
	0	0	0	0	0	0

	COL SUPPORT MATRIX
	0	0	0	0	0	0
	0	0	1	11	5	0
	0	2	3	0	0	0
	0	0	0	0	0	0

	SUPPORT MATRIX
	0	0	0	0	0	0
	0	0	1	0	5	0
	0	0	0	0	0	0
	0	0	0	0	0	0

*********************/
PersonalMatrix Pool::PrepareSupportsMatrix(const PersonalMatrix& originalMatrix){

	PersonalMatrix row_supportMatrix_1 = createSupportMatrix(originalMatrix);

	

	PersonalMatrix transposeMatrixtemp= originalMatrix.getTranspose();
		
	PersonalMatrix col_supportMatrix_2=createSupportMatrix(transposeMatrixtemp);
	
	col_supportMatrix_2.Transpose();
	
	
	p_rows= originalMatrix.getRow();
	p_columns= originalMatrix.getColumn();

	PersonalMatrix P_water(p_rows,p_columns);	// Matrice delle probabili pozzanghere

	for(int i=0;i<p_rows;++i){

		for(int j=0;j<p_columns;++j){

			float v1= row_supportMatrix_1(i,j);
			float v2= col_supportMatrix_2(i,j);

			if( v1>0 && v2>0 )
				P_water(i,j)= ( v1 <= v2  )  ? v1: v2;

			
		}
	}
	
	//cout<<"\n\n"<<endl;
	//P_water.printMatrix();
	return P_water;

}


/*****************
	Verifica se sono una singola cella e nel caso ritorna true e calcola m_3_water
*********************/
/*
bool Pool::checkIAlone(int r,int c,const PersonalMatrix& originalMatrix){

	bool valb =   ( P_pool(r,c)>0 && ( P_pool(r-1,c)==0 && P_pool(r,c-1)==0 && P_pool(r,c+1)==0 && P_pool(r+1,c)==0) ) ;

	if(  valb ){

		float min_temp = MIN_VALUE;

		for (int i=-1;i<=1;++i)
		{
			for (int j=-1;j<=1;++j)
			{
				if( i!=0 && j!=0 ){ // ||

					if(i!=0)
						j=0;

					float val=originalMatrix(i+r,j+c);



					if(val<min_temp)
						min_temp=val;

					if(i!=0)
						break;

				}

			}
		}

		P_pool(r,c)=min_temp - originalMatrix(r,c); //- P_pool(r,c); //modificata P_pool(r,c)=min_temp


		m_3_water += min_temp;
	}

	return valb;

}*/

/*****************
	Trova il minimo tra le celle!=0 attorno alla cella presa in considerazione.
	Mette quindi le celle!=0 nel vettore delle celle toccate.
*********************/

float Pool::touchNeighborsPoolAndFindMin(std::vector<pair<int,int>>& vector_touch,const PersonalMatrix& originalMatrix,PersonalMatrix& node_visited_matrix,int i,int j,float min,bool& isHis){

	for (int r=-1 ; r<=1;++r)
	{
		for (int c=-1; c<=1;++c)
		{
			if(r!=0)
				c=0;

			float near_= P_pool(i+r,j+c);

			if( (r!=0 || c!=0) && near_==0){

				float v2=originalMatrix(i+r,j+c);

				float v3=originalMatrix(i,j);

				if( v2 < min ){
					min=v2;
					isHis = true;

				}


			}else{

				if(  node_visited_matrix(i+r,j+c) < 1 ){

					pair<int,int> v=make_pair(i+r,j+c);

					vector_touch.push_back(v);
				}


			}

			if(r!=0)
				break;


		}
	}


	return min;

}