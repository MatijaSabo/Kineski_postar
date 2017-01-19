#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

ifstream data ("podaci.txt");
ifstream data2 ("kombinacije.txt");

int main(){
	int a;
	int x, y, w;
	cout<<"Projekt iz kolegija DSTG - Matija Sabolic, Marko Srnec, Mario Selek"<<endl;
	cout<<"Problem kineskog postara"<<endl<<endl;
	
	data>>a;
	int matrica[a][a];
	
	for(int i=0; i<a; i++){
		for(int j=0; j<a; j++){
			if(i == j){
				matrica[i][j] = 0;
			} else{
				matrica[i][j] = -1;
			}
		}
	}
	
	while(!data.eof()){
		data>>x>>y>>w;
		
		matrica[x-1][y-1] = w;
		matrica[y-1][x-1] = w;
	}
	
	int broj = 0;
	int brojac;
	int neparni[a];
	
	cout<<endl<<"Pocetna martica"<<endl;
	for(int i = 0; i < a; i++){
		brojac = 0;
		for(int j = 0; j < a; j++){
			cout<< matrica[i][j] <<"\t";
			
			if(matrica[i][j] > 0) brojac++;
		}
		
		if(brojac%2 == 1){
			neparni[broj] = i+1;
			broj++;
		}
		
		cout<<endl;
	}
	
	cout << "Broj neparnih vrhova je: " << broj << endl;
	cout << "Neparni vrhovi: ";
	for(int i = 0; i < broj; i++){
		if(i != (broj-1)) cout << neparni[i] << ", " ;
		else cout << neparni[i] ;
		
	}
	
	int full_matrix[broj][broj];
	
	//Floyd - Warshall algoritam
	for(int i = 0; i < a; i++){
		
		for(int j = 0; j < a; j++){
			 for(int k = 0; k < a; k++){
			 	
			 	if ((matrica[j][i] != -1) && (matrica[i][k] != -1) && (j != k))
                {
                    
					if ((matrica[j][i] + matrica[i][k] < matrica[j][k]) || (matrica[j][k] == -1))
                    {
                        matrica[j][k] = matrica[j][i] + matrica[i][k];
                    }
                    
                }
                
			 }
		}
	}
	
	//Matrica neparnih vrhova s najkracim udaljenostima
	for(int i = 0; i < broj; i++){
		for(int j = 0; j < broj; j++){
			if(i != j){
				full_matrix[i][j] = matrica[neparni[i] - 1][neparni[j] - 1];
			} else{
				full_matrix[i][j] = 0;
			}	
		}
	}
	
	int length, combinations;
	data2>>length>>combinations;
	int combinations2[combinations][length*2];
	
	int najmanja_udaljenost = 0, udaljenost;
	int najmanje_sparivanje;
	
	for(int i = 0; i < combinations; i++){
		for(int j = 0; j < length*2; j++){
			data2>>combinations2[i][j];	
		}
	}
	
	for(int i = 0; i < combinations; i++){
		udaljenost = 0;
		for(int j = 0; j < (length*2)-1; j = j + 2){
			udaljenost += full_matrix[combinations2[i][j] - 1][combinations2[i][j+1] - 1];
		}
		
		if(i != 0){
			if(najmanja_udaljenost > udaljenost){
				najmanja_udaljenost = udaljenost;
				najmanje_sparivanje = i;
			}
		} else{
			najmanja_udaljenost = udaljenost;
			najmanje_sparivanje = i;
		}
	}
		
	cout << endl << "Najkrace sparivanje vrhova: ";
	for(int i = 0; i < length*2; i++){
		if(i % 2 == 1){
			cout << " - " << neparni[combinations2[najmanje_sparivanje][i] - 1];
		} else if(i == 0){
			cout << neparni[combinations2[najmanje_sparivanje][i] - 1];
		}else{
			cout << ", " << neparni[combinations2[najmanje_sparivanje][i] - 1];
		}
	}
	
	cout << endl << "Duzina najkraceg sparivanja : " << najmanja_udaljenost << endl << endl;
	system("pause");
	return 0;
}
