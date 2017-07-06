This is the Trau string solver 

Requirements
---------------------------------
Before attempting to build Trau, you must have the following installed:
- Ubuntu 64 bits
- git (must be on your PATH)
- python (must be on your PATH)
- openfst (must be on your PATH). You can find the lastest version of openfst [here](http://www.openfst.org/twiki/bin/view/FST/FstDownload)

Getting & Building Trau
---------------------------------
```
	git clone https://github.com/diepbp/FAT.git
	cd FAT	
```	
- Install customized Z3-4.4.1.0 by following the instruction. You can find the customized Z3-4.4.1.0 in FAT folder.
```
	./configure
	cd build/
	make
	make install
```
- Update makefile by changing the path to customized Z3 library, line 47. Then,
```
	export LD_LIBRARY_PATH="/path/to/customized/Z3/build" 
```	
- Download Z3 4.5.0 [here](https://github.com/Z3Prover/z3/releases), and install it. Checking whether Z3 was successfully installed
```
	z3 -version
```
	
Command-line Usage
---------------------------------
```
	./Trau [option] fileName
```	
The folllowing options are avaiable:
- -model: print the concrete model if it is SAT
- -grm grammarFile: specify a grammar file

Running Example(s)
---------------------------------
```
	./Trau -model examples/concat-006
```	
where the file "examples/concat-006" contents are the following:
```
	(declare-fun a () String)
	(assert (= (Concat a "hello") "testhello"))
	(check-sat)
```	
When Trau terminates, it prints results as follows:
```
	=================================
	>> SAT
	---------------------------------
	a: string -> "test"
	=================================
```	
More examples are in the subfolder "examples". We create those examples based on examples we found in Z3-str2 tool.

License
---------------------------------

Trau is licensed under MIT License.

Contact/ Bug Report
---------------------------------

Feedback, questions or bug reports should go to Bui Phi Diep (bui.phi-diep@it.uu.se).