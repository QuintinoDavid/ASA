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
    int val, cur_max;
    if(y==0||x==0||pieces.empty())
        return 0;

    //criacao da tabela
    std::vector<int> lines(y+1);
    std::vector<std::vector<int>> subpiece_max(x+1,lines);
    int i,j, a, min;
    for(i=1; i<=x; i++){
        for(j=i;j<=y;j++){
            val= 0, cur_max=0;

            //ver as peças e ver se alguma encaixa na tabela e apaga-a
            std::list<std::vector<int>>::iterator it= pieces.begin();
            while(!pieces.empty() && (*it)[0]==i && (*it)[1]==j){ //caso a peça tenha as dimensões da tabela atual
                if((*it)[2]>cur_max) // peças tamanho igual valor !=
                    cur_max= (*it)[2];
                it++;
                pieces.pop_front();
            }
            
            
            //ver combinaçoes das peças
            //iterar desde o fim até o ceilling da metade, dividindo a placa verticalmente
            min = (i+1)>>1;
            for(a=i-1; a>=min; a--){
                val=subpiece_max[a][j] + subpiece_max[i-a][j];
                if(cur_max<val)
                    cur_max= val;
            } 

            if(i!=j) {//se não for quadrado
                //fazer o mesmo que há pouco mas agora horizontalmente
                min = (j+1)>>1;
                for(a=j-1; a>=min; a--){
                    if(j-a<=i) //verificar se o primeiro valor é menor que o segundo
                        val = subpiece_max[j-a][i];
                    else
                        val = subpiece_max[i][j-a];
                    if(a<=i)
                        val += subpiece_max[a][i];
                    else
                        val += subpiece_max[i][a];
                    if(cur_max < val)
                        cur_max= val;
                } 
            }
            subpiece_max[i][j]= cur_max;    
        }
    }
    return subpiece_max[x][y];
}

int main(){
    int x,y,n;
    int x1, y1, price1;
    std::list<std::vector<int>> pieces;

    scanf("%d%d",&x,&y);
    scanf("%d",&n);

    if(y<x){//por convenção fazemos o x sempre menor ou igual que o y
        int temp= y;
        y=x;
        x=temp; 
    }
    
    while(n>0){
        scanf("%d%d%d",&x1,&y1,&price1);
        if(y1<x1){ //x menor que y por convencao
            int temp= y1;
            y1=x1;
            x1= temp;
        }
        if(x1<=x && y1<=y){
            std::vector<int> piece {x1,y1,price1};
            pieces.push_back(piece);
        }
        n--;
    }

    pieces.sort();
    std::cout<<calculateprice(x,y,pieces)<<std::endl;
    return 0;
}