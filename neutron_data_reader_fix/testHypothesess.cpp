#include <string>
#include <iostream>


int main() {
    std::string data_directory_path = "/home/software/mcnpdata/xdata/endf71x";
    std::cout << data_directory_path << std::endl;

// WITH FRENSIE, perhaps in this directory: FRENSIE/packages/data/ace/test
// extract the nxs,jxs, and xss blocks using Data::XSSNeutronDataExtractor for each isotope
// run sort given to compute sizes of everything

//...........................................................................//
// do following checks for each isotope

// ESZ
// size == 5*nxs[2]

// MTR
// size == nxs[3]

// MTRP
// size == nxs[5]

// LQR
// size == nxs[3]

// TYR
// size == nxs[3]

// LSIG
// size == nxs[3]

// LSIGP
// size == nxs[5]

// LAND
// size == nxs[4] + 1

// LDLW
// size ==  nxs[4]

// LDLWP
// size ==  nxs[5]

// DNEDL
// size == nxs[7]

// GPD 
// size = 600 + nxs[3] TODO: double check, see Table F.15

// LANDP
// size == nxs[5]

// YP
// size == xss[jxs[19]] + 1

// FIS
// size == xss[jxs[20]] + 2

    return 0;
}