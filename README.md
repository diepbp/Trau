This is the [Trau](http://dl.acm.org/citation.cfm?id=3062384) string solver 

Installing Trau
------------------ 
```
	sudo sh install.sh
```
Then update the LD_LIBRARY_PATH by running: 
```
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:'/usr/share/workspace/custom-z3/lib:/usr/local/lib'
``` 
	
Command-line Usage
---------------------------------
```
	trau [option] fileName
```	
The folllowing options are avaiable:
- -language [smt2.0 | cvc4 | smt2.6]: specify the input language. Trau officially supports SMT2.0 (default input language). CVC4 language version, SMT2.6 are under the development. 
- -model: print satisfying assignments if the result is SAT.
- -crosscheck [s3 | cvc4 | z3str3]: specify a string solver to either cross-check satisfying assignments produced by Trau if Trau returns SAT, or run with the input test if Trau returns UNSAT. S3 supports SMT2.0 language while cvc4 and z3str3 support CVC4 language and SMT2.6. Note that, "-crosscheck cvc4" works only if CVC4 is installed and in your PATH.
- -grm grammarFile: specify a grammar file.

Running Example(s)
---------------------------------
```
	trau -model examples/concat-006
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