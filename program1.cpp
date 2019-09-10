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
#include <ctime>
#include <chrono>

using namespace std;

struct card{
  string playerName;
  int marketPrice;
  int listPrice = -1;
};

struct problem{
  int number;
  int bud;
  vector<card> cards;
};

struct solution{
  int numcards2;
  int profit2;
  int numcardspurchased;
  double time;
};

solution computeMaxProfit(problem p){
  std::chrono::time_point<std::chrono::system_clock> s, e; 
  s = std::chrono::system_clock::now();
  const clock_t begin_time = clock();
 
  int maxProfit = 0;
  vector<vector<card>> powerset;
  vector<card> subset1;
  int sumprice = 0;
  int budget = p.bud;
  for(int i = 0 ; i < p.cards.size(); i++){
    sumprice+=p.cards[i].listPrice;
  }
  vector<card> final;
  if(sumprice < budget || sumprice == budget){
    for(int i = 0 ; i < p.cards.size(); i++){

        subset1.push_back(p.cards[i]);
        maxProfit+=p.cards[i].marketPrice - p.cards[i].listPrice;

    }
    powerset.push_back(subset1);
    final = subset1;
  }
  else{
    for(int i = 0 ; i < pow(2,p.cards.size()) ; i++){
      vector<card> subset;
      for(int j = 0 ; j < p.cards.size() ; j++){
        if(i & (1 << j)){
          subset.push_back(p.cards[j]);
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
  solution s1;
  s1.numcardspurchased = final.size();
  s1.profit2 = maxProfit;
  s1.numcards2 = p.cards.size();
  e = std::chrono::system_clock::now(); 
  std::chrono::duration<double> els = e - s;
  s1.time = els.count(); 


  return s1;
};

int main(int argc, char** argv){
  int numcards = 0;
  ifstream marketfile;
  ifstream pricefile;
  string m = "-m";
  string p = "-p";
  vector<card> gurtiescards;
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
  vector<problem> problems;
  while(marketfile >> numcards){
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
  int playerprice;
  while(pricefile >> cardselling >> budget){
    problem p;
    p.number = cardselling;
    //cout << "cardselling : " << cardselling << endl;
    p.bud = budget;
    //cout << "budget : " << budget << endl;
    for(int i = 0 ; i < cardselling ; i++){
      pricefile >> playerpricename;
      //cout << "player price name : " << playerpricename << endl;
      pricefile >> playerprice;
      //cout << "player price : " << playerprice << endl;
      //cout << "i : " << i << endl;
      for(int j = 0 ; j < gurtiescards.size() ; j++){
        if(playerpricename.compare(gurtiescards[j].playerName)==0){
          gurtiescards[j].listPrice = playerprice;
          p.cards.push_back(gurtiescards[j]);
        }
      }
    }
    problems.push_back(p);
  }
  pricefile.close();
  vector<solution> solutions;
  ofstream output;
  output.open("output.txt");
  for(int i = 0 ; i < problems.size() ; i++){
      solution s = computeMaxProfit(problems[i]);
      output << "number of input cards : " << s.numcards2 << " , max profit : " << s.profit2 << " , number of cards bought : " << s.numcardspurchased << " , time taken : " << s.time << endl;

  }
  output.close();
}
