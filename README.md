This is the [Trau](http://dl.acm.org/citation.cfm?id=3062384) string solver 

Requirements
---------------------------------
Before attempting to build Trau, you must have the following installed:
- Ubuntu 64 bits 
- python (must be on your PATH)
- openfst (must be on your PATH). You can find the lastest version of openfst [here](http://www.openfst.org/twiki/bin/view/FST/FstDownload)

Getting & Building Trau
---------------------------------
```
	git clone https://github.com/diepbp/FAT.git
	cd FAT	
```	
- Install a custom Z3-4.4.1.0 by following the instruction. You can find z3-4.4.1.0.tar.gz in the FAT folder.
Extract z3-4.4.1.0.tar.gz and follow its README to install the custom Z3.

- Update Trau's makefile by changing the path to the custom Z3 library, line 47. Then,
```
	export LD_LIBRARY_PATH="/path/to/customized/Z3/build" 
```	
- Download Z3 4.5.0 [here](https://github.com/Z3Prover/z3/releases), and install it. Checking whether Z3 was successfully installed:
```
	z3 -version
```
- Build Trau
```
	cd build
	make 
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
More examples are in the subfolder "examples". We create those examples based on examples from [Z3-str2 tool](https://github.com/z3str/Z3-str).

License
---------------------------------

Trau is licensed under MIT License.

Contact/ Bug Report
---------------------------------

Feedback, questions or bug reports should go to [Bui Phi Diep](bui.phi-diep@it.uu.se).