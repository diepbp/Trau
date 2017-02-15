This is the FAT string solver 

** Requirements
- Ubuntu 64 bits
- python
- openfst installed
http://www.openfst.org/twiki/bin/view/FST/FstDownload
- z3 4.5.0 installed
https://github.com/Z3Prover/z3/releases

** Build FAT
- Install customized z3
- Update makefile by changing the path to customized Z3 library, line 47
- make
- Update LD_LIBRARY_PATH by the following command
export LD_LIBRARY_PATH="/path/to/customized/Z3/build" 

** Run FAT
./FAT [fileName]