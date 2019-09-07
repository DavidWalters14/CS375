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
  int listPrice = -1;
};


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
    //cout << "numcards :" << numcards << endl;
    for(int i = 0 ; i < numcards ; i++){
      card baseballcard;
      string name;
      int mprice;
      marketfile >> name;
      marketfile >> mprice;
      baseballcard.playerName = name;
      baseballcard.marketPrice = mprice;
      gurtiescards.push_back(baseballcard);
      //cout << "name :  " << gurtiescards[i].playerName << " market price: "<< gurtiescards[i].marketPrice << endl;
    }
    if(gurtiescards.size()==numcards){
      break;
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
  int playerprice;
  while(!pricefile.eof() && !pricefile.fail()){
    pricefile >> cardselling;
    //cout << "cardselling : " << cardselling << endl;
    pricefile >> budget;
    for(int i = 0 ; i < cardselling ; i++){
      pricefile >> playerpricename;
      pricefile >> playerprice;
      //cout << "player price name: " << playerpricename << endl;
      //cout << "player price : " << playerprice << endl;
      for(int j = 0 ; j < gurtiescards.size() ; j++){
        //cout << "gurties cards of " << j << " is " << gurtiescards[j].playerName << endl;
        //cout << "player price name : " << playerpricename << endl;
        if(playerpricename.compare(gurtiescards[j].playerName)==0){
          //cout << "this is price: " << price << endl;
          gurtiescards[j].listPrice = playerprice;
        }
      }
    }
    pricefile.close();
    for(int i = 0 ; i < gurtiescards.size() ; i++){
        //cout << "name :  " << gurtiescards[i].playerName << " market price: "<< gurtiescards[i].marketPrice << " list price : " << gurtiescards[i].listPrice<<endl;
    }
  }
  int maxProfit = 0;
  vector<card> currentset;
  vector<card> subset;
  int sumprice = 0;
  cout << gurtiescards.size() << endl;
  for(int i = 0 ; i < gurtiescards.size(); i++){
    if(gurtiescards[i].listPrice!=-1){
      //cout << " i : " << i << endl;
      //cout << "name :  " << gurtiescards[i].playerName << " market price: "<< gurtiescards[i].marketPrice << " list price : " << gurtiescards[i].listPrice<<endl;
      int x = gurtiescards[i].marketPrice;
      cout << x << endl;
      int y = gurtiescards[i].listPrice;
      cout << y << endl;
      sumprice+=y;
      cout << sumprice << endl;
      cout << budget << endl;
    }
  }
  /*if(sumprofit < budget || sumprofit == budget){
    cout << "flag" << endl;
    subset = gurtiescards;
    maxProfit = sumprofit - budget;
  }*/
  if(sumprice < budget || sumprice == budget){
    for(int i = 0 ; i < gurtiescards.size(); i++){
      if(gurtiescards[i].listPrice!=-1){
        subset.push_back(gurtiescards[i]);
        maxProfit+=gurtiescards[i].marketPrice - gurtiescards[i].listPrice;
      }
    }
  }
  else{
    cout << "flag" << endl;
    int iter1 = 0;
    int iter2 = 1;
    while(iter1 < gurtiescards.size()){
      if(gurtiescards[iter1].listPrice!=-1){
        currentset.push_back(gurtiescards[iter1]);
        break;
      }
      iter1++;
    }
      if(currentset[0].listPrice < budget){
        if(currentset[0].marketPrice > maxProfit){
          maxProfit = currentset[0].marketPrice;
          subset = currentset;
        }
      }
      while(iter2 < gurtiescards.size()){
        int currentsum = 0;
        if(gurtiescards[iter2].listPrice!=-1){
          currentset.push_back(gurtiescards[iter2]);
          for(int i = 0 ; i < currentset.size() ; i++){
            currentsum+=currentset[i].listPrice;
          }
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
  for(int i = 0 ; i < subset.size() ; i++){
    cout << subset[i].playerName << endl;
    cout << maxProfit << endl;
  }
}
