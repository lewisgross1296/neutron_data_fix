#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <algorithm>

int main(){

  // Duplicates may be due to lack of angular photon distributions
  // perhaps the XSS is all zeros if it is isotropic data, need to investigate landp, andp and ldlwp, dlwp

  // change to get nxs, jxs and xss using FRENSIE

// 43099.710nc 
  std::vector<int> d_nxs = { 729323, 43099, 53631, 62, 34, 201, 2, 0, 0, 43, 99, 0, 0, 0, 0, 0};

  std::vector<int> d_jxs = { 1, 0, 268156, 268218, 268280, 268342, 268404, 380213,
   380248, 455081, 455115, 555798, 609429, 609630, 609831, 612009,
   612210, 612210, 612411, 661765, 0, 661820, 552494, 0, 
   0, 0, 0, 0, 0, 661821, 661823, 661825};
// */

/* 92235.710nc 
        1   382591   382914   382962   383010   383058   383106   619790
   619836   684809   684854   757533   834051   834084   834117   835405
   835438   835438   835471   837478   383196   837481   745853   747702
   747717   747759   747765        0        0        0        0        0
// */


/* 94237.711nc 
        1     3781     3800     3836     3872     3908     3944    11455
    11490    82925    82959   180170   180926   180961   180996   181762
    181797   181797   181832   279756     4014   279791        0        0
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


  // add only the blocks with data that exist 
  // (alternative) maybe don't add anything past 26 since we don't use these in frensie, best way to do this


  int last_block = dned;//  d_jxs.size() except we probably don't want anything past dned
  std::vector<std::pair<int,int> > available_blocks;
   for(int block = 0 ; block < last_block ; block++) {
    if(d_jxs[block]>=0) {
      available_blocks.push_back(std::make_pair(d_jxs[block],block));
    }
  }

  // for unsorted printing
  for(int block = 0 ; block < available_blocks.size() ; block++) {
    std::cout << "The location of block " << available_blocks[block].second << 
    " is "  << available_blocks[block].first << std::endl;
  } // /*

  // sort pairs by first, seems to default to this with simple sort
  std::sort(available_blocks.begin(),available_blocks.end());

  std::cout << std::endl;
  std::cout << "AFTER SORTING" << std::endl;

  // print sorted pairs and verify that the sorted pairs are indeed increasing
  for(int block = 0 ; block < available_blocks.size() ; block++) {
    std::cout << "The location of block " << available_blocks[block].second << 
    " is "  << available_blocks[block].first << std::endl;
  }

  // monotone check
  for(int idx = 0 ; idx < available_blocks.size()-1 ; idx++) {
    // don't do check on last bc last block is end and it doesn't have a size
    if(available_blocks[idx].first > available_blocks[idx+1].first ) {
      // current block's location  happens after the next
      // blocks are not sorted in monotone order
      std::cout << "monotone check failed" << std::endl;
      std::cout << "curr block "<< available_blocks[idx].second << " , jxs[block] = " << available_blocks[idx].first << std::endl;
      std::cout << "next block "<< available_blocks[idx+1].second  <<  " , jxs[block+1] = "<< available_blocks[idx+1].first << std::endl;

    } else {
      std::cout << "monotone check passed for block " << available_blocks[idx].second << std::endl; // can likely comment out in FRENSIE
  }


  std::cout << std::endl;
  std::cout << "good to here"  << std::endl;

  // this map takes a block id key and returns value pair of the start and length corresponding to the block/key
  std::map<int, std::pair<int,int> > block_to_start_length_pair; // first parameter is the block's start, second parameter is the length of that block
  for(std::vector<std::pair<int,int> >::iterator soi=available_blocks.begin() ; soi<available_blocks.end() -1 ; soi++ ) {
      // soi stands for sorted order iterator 
      int block_id = soi->second;    // grab the block corresponding to the first value in the pair
      int start = soi->first;       // grab the jxs position corresponding to the current block
      int next_start = (soi+1)->first;   // grab the jxs position corresponding to the current block
      int length = next_start - start ;    // the difference next - curr is the length of the block curr
      block_to_start_length_pair.insert(std::make_pair(block_id,std::make_pair(start,length)));
  }

  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "Map Test" << std::endl;
  // traverse map
  for(auto it : block_to_start_length_pair) {
    std::cout  << "block id "  << it.first; // way to get enum to display name?
    auto pair = it.second;
    std::cout << " start: " << pair.first << " length: " << pair.second << std::endl;;
  } // */

  return 0;
}