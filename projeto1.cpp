/*
Projeto 1 de Análise e Sintese de Algoritmos
    Realizado por:
    - Carlota Ribeiro Domingos ist1107016
    - David Costa Quintino ist1107095
*/
#include <iostream>
#include <vector>

int calculateprice(int x, int y, std::vector<std::vector<int>> pieces, std::vector<int> price){
    std::vector<int> lines(x+1);
    std::vector<std::vector<int>> subpiece_max(y+1,lines);

    if(x<y){
       int temp= y;
       y=x;
       x=temp; 
    }

    for(int i=0; i<=x;i++){
        subpiece_max[0][i]=0;
    }

    for(int i=1; i<=x; i++){
        for(int j=i;i<=y;j++){

        }
    }
}

int main(){
    unsigned int x,y,n,v;
    std::cin>>x>>y;
    std::cin>>n;

    std::vector<int> piece(2);
    std::vector<std::vector<int>> pieces(2*n,piece);
    std::vector<int> price(2*n);

    int count = 0;
    while(n>0){
        std::cin>>pieces[count][0]>>pieces[count][1]>>price[count];
        count++;
        if(pieces[count][0]!=pieces[count][1]){
            pieces[count].resize(2);
            pieces[count][0]=pieces[count-1][1];
            pieces[count][1]=pieces[count-1][0];
            price[count]=price[count-1];
            count++;
        }
        n--;
    }
    price.resize(count);
    pieces.resize(count);

    int max_price = calculateprice(x,y,pieces,price);
    std::cout<<max_price<<std::endl;
    
    return 0;
}
