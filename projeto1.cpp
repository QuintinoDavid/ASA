/*
Projeto 1 de Análise e Sintese de Algoritmos
    Realizado por:
    - Carlota Ribeiro Domingos ist1107016
    - David Costa Quintino ist1107095
*/
#include <iostream>
#include <list>
#include <vector>
#include <cmath>

int calculateprice(int x, int y, std::list<std::vector<int>> pieces){
    if(y<x){
       int temp= y;
       y=x;
       x=temp; 
    }
    std::vector<int> lines(y+1);
    std::vector<std::vector<int>> subpiece_max(x+1,lines);

    for(int i=0; i<=y; i++){
        subpiece_max[0][i]=0;
    }

    for(int i=1; i<=x; i++){
        for(int j=i;i<=y;j++){
            //ver as peças e ver se alguma encaixa na tabela e apaga-a
            int cur_max=0;
            if(!pieces.empty()){
                for(std::list<std::vector<int>>::iterator it= pieces.begin();it !=pieces.end(); it++){
                    if( ((*it)[0]==j&&(*it)[1]==i) || ((*it)[1]==j&&(*it)[0]==i) ){
                        if((*it)[2]>cur_max){ // peças tamanho igual valor !=
                            cur_max= (*it)[2];
                        }
                        pieces.erase(it);
                    }
                }
            }
            
            //ver combinations das peças
            //1 vertical, 1 horizontal, iterar até floor da metade
            //if valor n ta na tabela, buscar o simetrico
            for(int a=j-1; a>=i; a--){
                if(int val=subpiece_max[i][a]+subpiece_max[i][j-i] > cur_max){ 
                        cur_max= val;
                }
            } // VALOR DA PROPRIO COISO

            if(i!=j) {//se não for quadrado
                for(double b=i-1; b>=j; b--){
                    if(int val=subpiece_max[j][b]+subpiece_max[j][i-b] > cur_max){
                        cur_max= val;
                    }
                }    
            }
        subpiece_max[x][y]= cur_max;   
        }
    }
    return subpiece_max[x][y];
}

int main(){
    unsigned int x,y,n;
    std::cin>>x>>y;
    std::cin>>n;

    
    std::list<std::vector<int>> pieces;

    while(n>0){
        int x1, y1, price1;
        std::cin>>x1>>y1>>price1;
        std::vector<int> piece {x1,y1,price1};
        pieces.push_back(piece);
        n--;
    }

    int max_price = calculateprice(x,y,pieces);
    std::cout<<max_price<<std::endl;
    
    return 0;
}
