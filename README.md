This is the FAT string solver 

Requirements
---------------------------------
Before attempting to build FAT, you must have the following installed:
- Ubuntu 64 bits
- git (must be on your PATH)
- python (must be on your PATH)
- openfst (must be on your PATH). You can find the lastest version of openfst [here](http://www.openfst.org/twiki/bin/view/FST/FstDownload)
- Z3 4.5.0 (must be on your PATH). You can find the Z3 [here](https://github.com/Z3Prover/z3/releases). Checking whether Z3 was successfully installed
	z3 -version
	

Getting & Building FAT
---------------------------------
	git clone https://github.com/diepbp/FAT.git
	cd FAT	
- Install customized Z3 by following the instruction
	
- Update makefile by changing the path to customized Z3 library, line 47. Then,
	make
- Update LD_LIBRARY_PATH:
	export LD_LIBRARY_PATH="/path/to/customized/Z3/build" 

Command-line Usage
---------------------------------
	./FAT [fileName]