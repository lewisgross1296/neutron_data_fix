#include <iostream>
#include <vector>
#include <array>
#include <map>
using namespace std;

int main(){

  vector<int> d_nxs = {206450, 18040, 23603, 42, 30, 0, 0, 0, 0, 18, 40, 0, 0, 0, 0, 0};
  // vector<int> d_jxs = {1, 0 , 118016 , 118058, 118100, 118142, 118184, 176941, 176972, 199042, 199072, 
  //                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 206450, 200000, 0, 0, 0, 0, 0, 0, 0, 0, 0};


  vector<int> d_jxs = {1, 382591, 382914, 382962, 383010, 383058, 383106, 619790,
   619836, 684809, 684854, 757533, 834051, 834084, 834117, 835405,
   835438, 835438, 835471, 837478, 383196, 837481, 745853, 747702,
   747717, 747759, 747765, 0, 0, 0, 0, 0};


/* 43099.710nc ISSUE {}
        1        0   268156   268218   268280   268342   268404   380213
   380248   455081   455115   555798   609429   609630   609831   612009
   {612210   612210}   612411   661765        0   661820   552494        0
        0        0        0        0        0   661821   661823   661825
*/

/* 92235.710nc ISSUE {}
        1   382591   382914   382962   383010   383058   383106   619790
   619836   684809   684854   757533   834051   834084   834117   835405
   {835438   835438}   835471   837478   383196   837481   745853   747702
   747717   747759   747765        0        0        0        0        0
*/


/* 94237.711nc ISSUE {}
        1     3781     3800     3836     3872     3908     3944    11455
    11490    82925    82959   180170   180926   180961   180996   181762
   {181797   181797}   181832   279756     4014   279791        0        0
        0        0        0        0        0        0        0        0
*/

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


  // this is the order in which NJOY prints the blocks and is the order in which the values in the
  // jxs array are increasing monotonically (excluding -1 entries for missing blocks)
  // if this changes, change here and the rest should work
  // TODO FIND IF FIS GOES AFTER NU


  // previously thought monotone order from NJOY 
  vector<int> monotone_order = {esz,nu,mtr,lqr,tyr,lsig,sig,landb,andb,ldlw,dlw,lunr,dnu,bdd,dnedl,
                                dned,gpd,mtrp,lsigp,sigp,landp,andp,ldlwp,dlwp,yp,fis,end};
  // */


  // suspected monotone order from looking at fissionable isotopes
  vector<int> monotone_order = {esz,nu,mtr,lqr,tyr,lsig,sig,fis,landb,andb,ldlw,dlw,lunr,dnu,bdd,dnedl,
                                dned,gpd,mtrp,lsigp,sigp,landp,andp,ldlwp,dlwp,yp,end};
  // */


  for(int block = 0; block < monotone_order.size() ; block++){
    if(d_jxs[monotone_order[block]]>=0) {
      //cout<< "block " << monotone_order[block] << " starts at " << d_jxs[monotone_order[block]];
      if( monotone_order[block] !=0)
        cout << "previous block " <<  monotone_order[block-1] << " current block " << monotone_order[block]
             << " current position minus previous is: " << d_jxs[monotone_order[block]] - d_jxs[monotone_order[block-1]] << endl;
      else
        cout << "first block, block 0" << endl;
    }
  }

  // add only the blocks with data that exist in order from monotone order
  vector<pair<int,int> > available_blocks_sorted;
   for(int block = 0 ; block < monotone_order.size() ; block++) {
    if(d_jxs[monotone_order[block]]>=0) {
      available_blocks_sorted.push_back(std::make_pair(block,d_jxs[monotone_order[block]]));
    }
  }

  // this map takes a block id key and returns value pair of the start and length corresponding to the block/key
  map<int, pair<int,int> > block_to_start_length_pair; // first parameter is the block's start, second parameter is the length of that block
  for(vector<pair<int,int> >::iterator soi=available_blocks_sorted.begin() ; soi<available_blocks_sorted.end() -1 ; soi++ ) {
      // soi stands for sorted order iterator 
      int block_id = soi->first;    // grab the block corresponding to the first value in the pair
      int start = soi->second;       // grab the jxs position corresponding to the current block
      int next_start = (soi+1)->second;   // grab the jxs position corresponding to the current block
      int length = next_start - start ;    // the difference next - curr is the length of the block curr
      block_to_start_length_pair.insert(std::make_pair(block_id,std::make_pair(start,length)));
  }

  cout << endl;
  cout << endl;
  cout << "Map Test" << endl;
  // traverse map
  for(auto it : block_to_start_length_pair) {
    cout  << "block id " << it.first; // way to get enum to display name?
    auto pair = it.second;
    cout << " start: " << pair.first << " length: " << pair.second << endl;;
  }

  return 0;
}