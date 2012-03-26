#include <iostream>
#include <fstream>
#include <sstream>
#include "Pool.h"
//#include <time.h>
#if DEBUG
#include <ctime>
#endif


#define WIDHT 1
#define HEIGHT 1


vector<float> ReadFileMatrix(ifstream& infile,int& out_rows,int& out_columns){

	int temp_columns=out_columns;
	string number;
	char next;

	infile.get(next);
	char prev = next;

	float current_number=0;

	vector<float> matrix;


	while(! infile.eof()){

		if( ( next == ' ' || next=='\t' ) && !(prev == ' ' || prev == '\t')  ){

			stringstream(number) >> current_number;

			matrix.push_back(current_number);

			temp_columns += 1;
			number="";
			prev=next;
			infile.get(next);
		}
		else{

			if( (next>='0' && next<= '9') || ( next=='.' || next==',' ) ){

				number+= ( next==',') ? '.' : next;

			}else{

				if(next == '\n'){

					if(out_rows == 1){

						out_columns = temp_columns;

					} else{

						if(temp_columns!=out_columns){
							cout<<"Error: Number Columns Conflict.\nPress Enter to close"<<endl;
							matrix.clear();
							getchar();
							abort();
							//return matrix;
						}
					}


					out_rows +=1;
					temp_columns = 1;

					stringstream(number) >> current_number;

					matrix.push_back(current_number);

					number="";
					
				}else{
					cout<<"Error: Matrix format problem. \nPress Enter to close"<<endl;
					//matrix.clear();
					getchar();
					abort();
					//return matrix;
				}
			}

			prev=next;
			infile.get(next);

			if (infile.eof())
			{
				stringstream(number) >> current_number;

				matrix.push_back(current_number);
			}

		}

	}

	infile.close();

	return matrix;

}


int main(int argc, char** argv){

	
	vector<float> matrix;

	if(argc!= 2){
		cout<<"Error, insert file name. Try: \"test.exe filename\" "<<endl;
		return 0;
	}
	
	ifstream infile(argv[1],std::ios::in);
	
	

	//ifstream infile("input12.txt",std::ios::in);

	int rows=1;
	int columns=1;

	
	matrix = ReadFileMatrix(infile,rows,columns);

	if(matrix.empty())
		return 0;


	Pool pool(HEIGHT,WIDHT);
	
	PersonalMatrix loadedMatrix(matrix,rows,columns);
	
	cout<<"BLOCK DIMENSION: \n\t\t"<<"WIDTH: "<<WIDHT<<"m\n\t\tHEIGHT: "<<HEIGHT<<"m"<<endl;

	cout<<"\n_ _ MATRIX _ _ \n"<<endl;

	loadedMatrix.printMatrix();

	PersonalMatrix water = pool.FindPool(loadedMatrix);

	cout<<"\n\n_ _ WATER PUDDLE PROFONDITY AND POSITION _ _ \n"<<endl;

	water.printMatrix();

	cout<<"\n_ _ WATER PUDDLE CAPACITY _ _ \n"<<endl;

	water *= pool.getBlockArea();

	water.printMatrix();

	cout<<"\n\nM^3 of Water: "<<pool.getM3water()*pool.getBlockArea()<<endl;
	

	getchar();
}


