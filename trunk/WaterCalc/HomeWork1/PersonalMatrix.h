#pragma once
#include <stdio.h>
#include <vector>

using namespace std;


class PersonalMatrix{

public:

	explicit PersonalMatrix(){

		createMatrix(std::vector<float>(1,0),1,1);

	}

	PersonalMatrix(int row, int col){

		createMatrix(std::vector<float>(row*col,0),row,col);

	}

	PersonalMatrix(const std::vector<float>& i_matrix,int row, int col){

		createMatrix(i_matrix,row,col);

	}

	void createMatrix(const std::vector<float>& i_matrix,const int i_rows,const int i_columns){

		p_rows=i_rows;
		p_columns=i_columns;

		matrix = new float*[i_rows];

		std::vector<float>::const_iterator it=i_matrix.begin();

		for(int i=0;i<i_rows;++i){

			matrix[i]=new float[i_columns];

			for(int j=0;j<i_columns;++j){

				matrix[i][j]=it[i*i_columns + j];

			}

		}



	}

	void Reset(){

		for(int i=0;i<p_rows;++i){

			for (int j=0;j<p_columns;j++){

				matrix[i][j]=0;
			}

		}

	}


	void printMatrix(){

		for(int i=0;i<p_rows;++i){

			for (int j=0;j<p_columns;j++){

				cout<<matrix[i][j]<<"\t";
			}

			cout<<endl;

		}

		//cout<<"\n\n --------------------------------------------------------------------------------------"<<endl;

	}

	PersonalMatrix getTranspose() const{

		PersonalMatrix temp(this->p_columns,this->p_rows);

		for(int i=0;i<p_columns;i++){

			for(int j=0;j<p_rows;j++){

				temp(i,j) = matrix[j][i];


			}

		}

		return temp;

	}

	void Transpose(){

		*this=this->getTranspose();

	}

	int getRow() const{
		return this->p_rows;
	}

	int getColumn() const {
		return this->p_columns;
	}

	float& operator()(const int i_rows,const int i_columns) const {

		return matrix[i_rows][i_columns];

	}

	PersonalMatrix& operator*= (const float i_other){

		for (int i=0;i<p_rows;++i)
		{
			for(int j=0;j<p_columns;++j){

				matrix[i][j]*=i_other;

			}
		}

		return *this;
	}

private:

	float** matrix;
	int p_rows;
	int p_columns;


};


PersonalMatrix createSupportMatrix(const PersonalMatrix& matrix){

	PersonalMatrix rowsSupportMatrix(matrix.getRow(), matrix.getColumn());

	int x_max=1;
	int y_max=1;

	int i_rows=matrix.getRow();
	int i_columns=matrix.getColumn();

	for(int i=1;i<i_rows-1;i++){

		float maxValue = -1;

		for (int j = 0;j<i_columns;j++){

			float k=matrix(i,j);

			for(int s=j+1;s<=i_columns;++s){

				if(s<i_columns){

					float tempValue=matrix(i,s);

					if(tempValue>=k){

						for(int t = j+1;t<=s;++t){

							float l=matrix(i,t);

							float ins_vale= (   k - matrix(i,t)   < 0) ? 0 : k - matrix(i,t) ;

							rowsSupportMatrix(i,t)=ins_vale;

						}

						j=s;
						k=matrix(i,j);
						maxValue=-1;

					}else{

						if(maxValue<=tempValue){
							x_max=s;
							y_max=i;
							maxValue=tempValue;
						}
						
					}

				}
				else{

					if(j!=i_columns-1){

						for(int t=j;t<=x_max;++t){
							
							float l=matrix(i,t);

							float ins_vale= ( maxValue - matrix(i,t) < 0 || t==i_columns-1 ) ? 0 :maxValue - matrix(i,t) ;

							
							rowsSupportMatrix(i,t)=ins_vale;

						}

						if(x_max!=i_columns){

								int temp=s;
								maxValue = -1;
								k=matrix(i,x_max);

								s=x_max;
								j=x_max;
								x_max=temp;
								
							}else
								j=s;

						
					}

				}

			}

		}

	}
		
	return rowsSupportMatrix;

}