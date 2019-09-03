#include <string>
#include <string.h>
#include <vector>
#include <cstring>
#include <list>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <cfloat>
#include <limits>
#include <queue>

using namespace std;

struct card{
  string playerName;
  int marketPrice;
  int listPrice;
};

/*struct subset{
  vector<card> mysubset;
  int profit;
}*/

int computeProfit(vector<card> cards, int budget){
  int maxProfit = 0;
  vector<card> currentset;
  vector<card> subset;
  int sumprofit = 0;
  for(int i = 0 ; i < cards.size() ; i++){
    sumprofit+=cards[i].listPrice;
  }
  if(sumprofit < budget || sumprofit == budget){
    //return initial cards
  }
  int iter1 = 0;
  int iter2 = 1;
  while(iter1 < cards.size()){
    currentset.push_back(cards[iter1]);
    if(currentset[0].listPrice < budget){
      if(currentset[0].marketPrice > maxProfit){
        maxProfit = currentset[0].marketPrice;
        subset = currentset;
      }
    }
    while(iter2 < cards.size()){
      int currentsum = 0;
      currentset.push_back(cards[iter2]);
      for(int i = 0 ; i < currentset.size() ; i++){
        currentsum+=currentset[i].listPrice;
      }
      if(currentsum < budget){
        if(currentsum > maxProfit){
          maxProfit = currentsum;
          subset = currentset;
        }
      }
      iter2++;
    }
    iter1++;
  }

}
int main(int argc, char** argv){
  int numcards = 0;
  ifstream marketfile;
  ifstream pricefile;
  string m = "-m";
  string p = "-p";
  for(int i = 0 ; i < argc ; i++){
    string arg = argv[i];
    if(m.compare(arg)==0){
      marketfile.open(argv[i+1]);
    }
    if(p.compare(arg)==0){
      pricefile.open(argv[i+1]);
    }
  }
  if(!marketfile.is_open()){
		cout << "market file could not be opened" << endl;
	}
  vector<card> gurtiescards;
  while(!marketfile.eof() && !marketfile.fail()){
    marketfile >> numcards;
    for(int i = 0 ; i < numcards ; i++){
      card baseballcard;
      string name;
      int mprice;
      marketfile >> name;
      marketfile >> mprice;
      baseballcard.playerName = name;
      baseballcard.marketPrice = mprice;
      gurtiescards.push_back(baseballcard);
    }
  }
  marketfile.clear();
  marketfile.close();
  if(!pricefile.is_open()){
		cout << "market file could not be opened" << endl;
  }
  int cardselling;
  int budget;
  string playerpricename;
  while(!pricefile.eof() && !pricefile.fail()){
    pricefile >> cardselling;
    pricefile >> budget;
    for(int i = 0 ; i < cardselling ; i++){
      pricefile >> playerpricename;
      for(int j = 0 ; j < gurtiescards.size() ; j++){
        if(playerpricename.compare(gurtiescards[i].playerName)==0){
          int price;
          pricefile >> price;
          gurtiescards[i].listPrice = price;
        }
      }
    }
  }
}
