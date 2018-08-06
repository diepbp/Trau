This is the [Trau](http://dl.acm.org/citation.cfm?id=3062384) string solver 

Requirements
---------------------------------
Before attempting to build Trau, you need to have the following installed and in your PATH:  

- [openfst](http://www.openfst.org/twiki/bin/view/FST/FstDownload)
- [ANTLR 4 runtime](http://www.antlr.org/download.html)

Getting & Building Trau on MacOS and Linux
---------------------------------
- Download the latest release/git version of Trau. The git version can be unstable at some point, but possibly more efficient. Please refer to [RELEASE NOTES](https://github.com/diepbp/FAT/blob/master/RELEASE%20NOTES) for more details.
- Install a custom Z3-4.4.1.0.
Extract z3-4.4.1.0.tar.gz and follow its README to install the custom Z3.

- Edit the file build/config.mk. You need to update paths for custom z3 and ANTLR:
```
	CUSTOM_Z3_LIB_PATH := /path/to/custom/Z3/lib
	CUSTOM_Z3_INCLUDE_PATH := /path/to/custom/Z3/include
	ANTLR_RUNTIME_PATH := /path/to/ANTLR/include/antlr4-runtime
``` 
	
- Download the latest release of Z3 [here](https://github.com/Z3Prover/z3/releases), and install it. Checking whether Z3 was successfully installed:
```
	z3 -version
```

- Replace the Z3 library by the custom Z3 library,
```
	cp /path/to/custom/Z3/lib /usr/local/lib   # replace the library
	export LD_LIBRARY_PATH="/usr/local/lib"    # export it
```

- Build Trau
```
	cd build; make 
```
	
Command-line Usage
---------------------------------
```
	./Trau [option] fileName
```	
The folllowing options are avaiable:
- -language [smt2.0 | smt2.5 | smt2.6]: specify the input language. Trau officially supports SMT2.0 (default input language). SMT2.5, SMT2.6 are under the development. 
- -model: print satisfying assignments if the result is SAT.
- -crosscheck [s3 | cvc4 | z3str3]: specify a string solver to either cross-check satisfying assignments produced by Trau if Trau returns SAT, or run with the input test if Trau returns UNSAT. S3 supports SMT2.0 language while CVC4 and Z3str3 support SMT2.5 and SMT2.6. Note that, "-crosscheck cvc4" works only if CVC4 is installed and in your PATH.
- -grm grammarFile: specify a grammar file.

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