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

    for(double i=1; i<=x; i++){
        for(double j=i;j<=y;j++){
            //ver as peças e ver se alguma encaixa na tabela e apaga-a
            int cur_max=0;
            if(!pieces.empty()){
                for(std::list<std::vector<int>>::iterator it= pieces.begin();it !=pieces.end();){
                    if(((*it)[0]==j&&(*it)[1]==i) || ((*it)[1]==j&&(*it)[0]==i) ){
                        if((*it)[2]>cur_max){ // peças tamanho igual valor !=
                            cur_max= (*it)[2];
                        }
                        it = pieces.erase(it);
                    } else {
                        it++;
                    }
                }
            }
            
            
            //ver combinations das peças
            //1 vertical, 1 horizontal, iterar até floor da metade
            //if valor n ta na tabela, buscar o simetrico
            // VALOR DA PROPRIO COISO
            for(double a=i-1; a>=ceil(i/2); a--){
                if(int val=subpiece_max[a][j]+subpiece_max[i-a][j] > cur_max){
                    cur_max= val;
                }
            } 

            if(i!=j) {//se não for quadrado
                for(double a=j-1; a>=ceil(j/2); a--){
                    if(int val=subpiece_max[a][i]+subpiece_max[j-a][i] > cur_max){ 
                        cur_max= val;
                    }
                } 
            }
            subpiece_max[i][j]= cur_max;   
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
