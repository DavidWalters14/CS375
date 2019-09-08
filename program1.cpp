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
  while(pricefile >> cardselling >> budget){
    for(int i = 0 ; i < cardselling ; i++){
      pricefile >> playerpricename;
      cout << "player price name : " << playerpricename << endl;
      pricefile >> playerprice;
      cout << "player price : " << playerprice << endl;
      cout << "i : " << i << endl;
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
      bool flag = pricefile.eof();
      cout << flag << endl;
    }
    pricefile.close();
    for(int i = 0 ; i < gurtiescards.size() ; i++){
        //cout << "name :  " << gurtiescards[i].playerName << " market price: "<< gurtiescards[i].marketPrice << " list price : " << gurtiescards[i].listPrice<<endl;
    }
  }
  int maxProfit = 0;
  vector<vector<card>> powerset;
  vector<card> subset1;
  int sumprice = 0;
  cout << gurtiescards.size() << endl;
  vector<card> gc2;
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
      gc2.push_back(gurtiescards[i]);
    }
    /*else{
      gurtiescards[i]=NULL;
    }*/
  }
  /*if(sumprofit < budget || sumprofit == budget){
    cout << "flag" << endl;
    subset = gurtiescards;
    maxProfit = sumprofit - budget;
  }*/
  vector<card> final;
  if(sumprice < budget || sumprice == budget){
    for(int i = 0 ; i < gc2.size(); i++){

        subset1.push_back(gc2[i]);
        maxProfit+=gc2[i].marketPrice - gc2[i].listPrice;

    }
    powerset.push_back(subset1);
  }
  else{
    for(int i = 0 ; i < pow(2,gc2.size()) ; i++){
      vector<card> subset;
      for(int j = 0 ; j < gc2.size() ; j++){
        if(i & (1 << j)){
          subset.push_back(gc2[j]);
        }
      }
      powerset.push_back(subset);
    }
    int currsum = 0;
    int currprice = 0;
    for(int i = 0 ; i < powerset.size() ; i++){
      vector<card> curr = powerset[i];
      for(int j = 0 ; j < powerset[i].size() ; j++){
        currsum += curr[j].marketPrice - curr[j].listPrice;
        currprice += curr[j].listPrice;
      }
      if(currprice < budget || currprice == budget){
        if(currsum > maxProfit){
          maxProfit=currsum;
          final = curr;
        }
      }
      currsum = 0;
      currprice = 0;
    }
  }

  for(int i = 0; i < final.size() ; i++){
    cout << "name : " << final[i].playerName << endl;
  }
  cout << "total profit : " << maxProfit << endl;
}
