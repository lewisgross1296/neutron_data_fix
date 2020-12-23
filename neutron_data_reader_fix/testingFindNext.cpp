#include <iostream>
#include <vector>
#include <array>
#include <map>
using namespace std;

int main(){

  vector<int> d_nxs = {206450, 18040, 23603, 42, 30, 0, 0, 0, 0, 18, 40, 0, 0, 0, 0, 0};
  vector<int> d_jxs = {1, 0 , 118016 , 118058, 118100, 118142, 118184, 176941, 176972, 199042, 199072, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 206450, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  // Adjust the indices in the JXS array so that they correspond to a C-array
  for( size_t i = 0; i < d_jxs.size(); ++i )
    d_jxs[i] -= 1; 


  enum blockId  {  esz, // 0
                    nu, // 1 
                    mtr, // 2
                    lqr, // 3
                    tyr, // 4
                    lsig, // 5
                    sig, // 6
                    landb, // 7
                    andb, // 8
                    ldlw, // 9
                    dlw, // 10
                    gpd, // 11
                    mtrp, // 12
                    lsigp, // 13
                    sigp, // 14
                    landp, // 15
                    andp, // 16
                    ldlwp, // 17
                    dlwp, // 18
                    yp, // 19
                    fis, // 20
                    end, // 21
                    lunr, // 22
                    dnu, // 23
                    bdd, //24
                    dnedl, // 25
                    dned // 26 
                    }; 
  // maps block to starting value in the jxs array
  map<int,int> positions;

  positions[esz]   = d_jxs[esz];
  positions[nu]    = d_jxs[nu];
  positions[mtr]   = d_jxs[mtr];
  positions[lqr]   = d_jxs[lqr];
  positions[tyr]   = d_jxs[tyr];
  positions[lsig]  = d_jxs[lsig];
  positions[sig]   = d_jxs[sig];
  positions[landb] = d_jxs[landb]; // added b suffix to correspond locators to actutal angular dist in naming convention
  positions[andb]  = d_jxs[andb];  // added b suffix because of reserved word and, i.e. and block
  positions[ldlw]  = d_jxs[ldlw];
  positions[dlw]   = d_jxs[dlw];
  positions[lunr]  = d_jxs[lunr];  // referred to as iurpt in NJOY
  positions[dnu]   = d_jxs[dnu];   // referred to as nud in NJOY 
  positions[bdd]   = d_jxs[bdd];   // referred to as dndat in NJOY
  positions[dnedl] = d_jxs[dnedl]; // referred to as ,]ldnd in NJOY
  positions[dned]  = d_jxs[dned];  // referred to as dnd in NJOY
  positions[gpd]   = d_jxs[gpd];
  positions[mtrp]  = d_jxs[mtrp];
  positions[lsigp] = d_jxs[lsigp];
  positions[sigp]  = d_jxs[sigp];
  positions[landp] = d_jxs[landp];
  positions[andp]  = d_jxs[andp];
  positions[ldlwp]  = d_jxs[ldlwp];
  positions[dlwp]  = d_jxs[dlwp];
  positions[yp]    = d_jxs[yp];
  positions[fis]   = d_jxs[fis];
  positions[end]   = d_jxs[end]; 


  cout << "Negative Check" << endl;
  for(int block=d_jxs.size() - 1 ; block>=0 ; block--) {
    if(d_jxs[block]<0){
      cout << block << " contains the number " << d_jxs[block] << endl;
      positions.erase(block);
    }
    else{
      cout << block << " did not contain a negative number, instead it has " << d_jxs[block] << endl;
    }
  } 

  cout << endl;
  cout << endl;

  cout << "Check the positions map after eliminating the negative numbers" << endl;
  for(map<int,int>::iterator it=positions.begin() ; it!=positions.end(); ++it)
    cout <<  "block " << it->first << " has value " << it->second << endl;
  // */

  return 0;
}