This is the [Trau](http://dl.acm.org/citation.cfm?id=3062384) string solver 

Requirements
---------------------------------
Before attempting to build Trau, you need to have the following installed and in your PATH:  

- [openfst](http://www.openfst.org/twiki/bin/view/FST/FstDownload)
- [ANTLR 4 runtime](http://www.antlr.org/download.html)

Getting & Building Trau
---------------------------------
```
	git clone https://github.com/diepbp/FAT.git
	cd FAT	
```	
- Install a custom Z3-4.4.1.0. You can find z3-4.4.1.0.tar.gz in the FAT folder.
Extract z3-4.4.1.0.tar.gz and follow its README to install the custom Z3.

- Update Trau's makefile by changing the path to the custom Z3 library, line 47. Then,
```
	export LD_LIBRARY_PATH="/path/to/custom/Z3/build" 
```	
- Download the latest release of Z3 [here](https://github.com/Z3Prover/z3/releases), and install it. Checking whether Z3 was successfully installed:
```
	z3 -version
```
- Build Trau
```
	cd build
	make clean; make 
```
	
Command-line Usage
---------------------------------
```
	./Trau [option] fileName
```	
The folllowing options are avaiable:
- -model: print satisfying assignments if the result is SAT
- -doublecheck: use the S3P string solver to double-check satisfying assignments produced by Trau
- -grm grammarFile: specify a grammar file

Running Example(s)
---------------------------------
```
	./Trau -model examples/concat-006
```	
where the file "examples/concat-006" contents are the following:
```
	(declare-fun a () String)
	(declare-fun b () String)
	(assert (= (Concat a "hello") b))
	(assert (= b "testhello"))
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