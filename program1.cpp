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
    for(int i = 0 ; i < gurtiescards.size() ; i++){
      vector<card> currentset;
      int currprice = gurtiescards[i].listPrice;
      int currprofit = gurtiescards[i].marketPrice;
      if(currprice!=-1){
        if(currprice < budget){
          currentset.push_back(gurtiescards[i]);
          maxProfit = currprofit - currprice;
        }
      }
      for(int j = 0 ; j < pow(2,gurtiescards.size()) ; j++){
        if(gurtiescards[j].listPrice!=-1){
          currentset.push_back(gurtiescards[j]);
        }
          int setprofit = 0;
          for(int k = 0 ; k < currentset.size() ; k++){
            setprofit += currentset[k].marketPrice - currentset[k].listPrice;
          }
          if(setprofit > maxProfit){
            subset = currentset;
            setprofit = maxProfit;
          }
        }
      }
    }
  
  for(int i = 0 ; i < subset.size() ; i++){
    cout << subset[i].playerName << endl;
    cout << maxProfit << endl;
  }
}
