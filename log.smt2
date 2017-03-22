***********************************************
*                 initGrammar                 *
-----------------------------------------------
Input
$OREXPRESSION = $COMPARAISON | $EXPRESSION $OROP $EXPRESSION 

$EXPRESSION = $OREXPRESSION | $NOTOP $EXPRESSION

$COMPARAISON = $TERM $COMPOP $TERM 

$COMPOP = " > " | " = " | " < " 

$OROP = " or " 

$NOTOP = " not "  

$TERM = $NUMBER | $STRING | $QUOTE $TERM $QUOTE 

$NUMBER = [0-9]+ 

$STRING = [a-z]+ 

$QUOTE = "\"" 


165 $COMPARAISON: (((((\"))*([0-9]+))~(((\"))*([a-z]+)))((\"))*)((( > )~( = )~( < )))(((((\"))*([0-9]+))~(((\"))*([a-z]+)))((\"))*)
165 $COMPOP: (( > )~( = )~( < ))
165 $EXPRESSION: (( not ))*(( not ))*((((((\"))*([0-9]+))~(((\"))*([a-z]+)))((\"))*)((( > )~( = )~( < )))(((((\"))*([0-9]+))~(((\"))*([a-z]+)))((\"))*))(( or )(( not ))*(( not ))*((((((\"))*([0-9]+))~(((\"))*([a-z]+)))((\"))*)((( > )~( = )~( < )))(((((\"))*([0-9]+))~(((\"))*([a-z]+)))((\"))*)))*
165 $NOTOP:  not 
165 $NUMBER: [0-9]+
165 $OREXPRESSION: (( not ))*((((((\"))*([0-9]+))~(((\"))*([a-z]+)))((\"))*)((( > )~( = )~( < )))(((((\"))*([0-9]+))~(((\"))*([a-z]+)))((\"))*))(( or )(( not ))*(( not ))*((((((\"))*([0-9]+))~(((\"))*([a-z]+)))((\"))*)((( > )~( = )~( < )))(((((\"))*([0-9]+))~(((\"))*([a-z]+)))((\"))*)))*
165 $OROP:  or 
165 $QUOTE: \"
165 $STRING: [a-z]+
165 $TERM: ((((\"))*([0-9]+))~(((\"))*([a-z]+)))((\"))*
Input file: nonsql2.smt2

Grammar file: sql.grm

262 creating /tmp/fat_str_convert/: OK
***********************************************
*              initGraph             *
-----------------------------------------------
 w,
(assert (RegexIn w (RegexStar (Str2Reg "abcabc"))))

 i,
(assert (RegexIn i (RegexStar (Str2Reg "abcabc"))))

 w,
(assert (RegexIn w (RegexStar (Str2Reg "abcabcabc"))))

 w, j,
(assert (= w (Concat "abc" j)))

 g, w,
(assert (= g (Concat "def" w))) 

 t, w,
(assert (= t (Concat "ghi123" w)))
(check-sat)
***********************************************
*              convertFile             *
-----------------------------------------------
244 creating /tmp/fat_str_convert/: OK
***********************************************
*              fat_theory                     *
-----------------------------------------------
String Input Var Set
***********************************************
w
i
j
g
t

***********************************************
Input loaded:
-----------------------------------------------
(and (RegexIn w (RegexStar (Str2Reg __cOnStStR__x61_x62_x63_x61_x62_x63)))
     (RegexIn i (RegexStar (Str2Reg __cOnStStR__x61_x62_x63_x61_x62_x63)))
     (RegexIn w
              (RegexStar (Str2Reg __cOnStStR__x61_x62_x63_x61_x62_x63_x61_x62_x63)))
     (= w (Concat __cOnStStR__x61_x62_x63 j))
     (= g (Concat __cOnStStR__x64_x65_x66 w))
     (= t (Concat __cOnStStR__x67_x68_x69_x31_x32_x33 w)))
-----------------------------------------------


>> cb_reduce_app(): Str2Reg("abcabc")


>> cb_reduce_app(): RegexStar((Str2Reg abcabc)) --> NULL


>> RegexIn(w, (RegexStar (Str2Reg abcabc)))
 --> 
w  \in  (abcabc)*


>> cb_reduce_app(): RegexIn(w, (RegexStar (Str2Reg abcabc))) ==> (= w (NonDet_AutomataDef |(abcabc)*| 0))


>> RegexIn(i, (RegexStar (Str2Reg abcabc)))
 --> 
i  \in  (abcabc)*


>> cb_reduce_app(): RegexIn(i, (RegexStar (Str2Reg abcabc))) ==> (= i (NonDet_AutomataDef |(abcabc)*| 1))


>> cb_reduce_app(): Str2Reg("abcabcabc")


>> cb_reduce_app(): RegexStar((Str2Reg abcabcabc)) --> NULL


>> RegexIn(w, (RegexStar (Str2Reg abcabcabc)))
 --> 
w  \in  (abcabcabc)*


>> cb_reduce_app(): RegexIn(w, (RegexStar (Str2Reg abcabcabc))) ==> (= w (NonDet_AutomataDef |(abcabcabc)*| 2))


>> cb_reduce_app(): Concat("abc", j)
>> cb_reduce_app(): Concat((AutomataDef abc), j)
False update 
---------------------
Assertion Add(@1422, Level 0):
(let ((a!1 (>= (Length (Concat (AutomataDef abc) j)) 0))
      (a!2 (= (Length (Concat (AutomataDef abc) j))
              (+ (Length (AutomataDef abc)) (Length j)))))
  (and (= (Length (AutomataDef abc)) 3)
       (>= (Length (AutomataDef abc)) 0)
       (>= (Length j) 0)
       a!1
       a!2))
---------------------


convert to: (Concat (AutomataDef abc) j)


>> cb_reduce_eq: w = (Concat (AutomataDef abc) j)


 converted to : (and (>= (Length w) 0) (= w (Concat (AutomataDef abc) j)))

>> cb_reduce_app(): Concat("def", w)
>> cb_reduce_app(): Concat((AutomataDef def), w)
False update 
---------------------
Assertion Add(@1422, Level 0):
(let ((a!1 (>= (Length (Concat (AutomataDef def) w)) 0))
      (a!2 (= (Length (Concat (AutomataDef def) w))
              (+ (Length (AutomataDef def)) (Length w)))))
  (and (= (Length (AutomataDef def)) 3)
       (>= (Length (AutomataDef def)) 0)
       (>= (Length w) 0)
       a!1
       a!2))
---------------------


convert to: (Concat (AutomataDef def) w)


>> cb_reduce_eq: g = (Concat (AutomataDef def) w)


 converted to : (and (>= (Length g) 0) (= g (Concat (AutomataDef def) w)))

>> cb_reduce_app(): Concat("ghi123", w)
>> cb_reduce_app(): Concat((AutomataDef ghi123), w)
False update 
---------------------
Assertion Add(@1422, Level 0):
(let ((a!1 (>= (Length (Concat (AutomataDef ghi123) w)) 0))
      (a!2 (= (Length (Concat (AutomataDef ghi123) w))
              (+ (Length (AutomataDef ghi123)) (Length w)))))
  (and (= (Length (AutomataDef ghi123)) 6)
       (>= (Length (AutomataDef ghi123)) 0)
       (>= (Length w) 0)
       a!1
       a!2))
---------------------


convert to: (Concat (AutomataDef ghi123) w)


>> cb_reduce_eq: t = (Concat (AutomataDef ghi123) w)


 converted to : (and (>= (Length t) 0) (= t (Concat (AutomataDef ghi123) w)))

>> cb_reduce_app(): Concat((AutomataDef abc), j)
False update 

>> cb_reduce_app(): Concat((AutomataDef def), w)
False update 

>> cb_reduce_app(): Concat((AutomataDef ghi123), w)
False update 

>> cb_reduce_eq: w = (NonDet_AutomataDef |(abcabc)*| 0)


 converted to : (and (>= (Length w) 0)
     (>= (Length (NonDet_AutomataDef |(abcabc)*| 0)) 0)
     (= w (NonDet_AutomataDef |(abcabc)*| 0)))

>> cb_reduce_eq: i = (NonDet_AutomataDef |(abcabc)*| 1)


 converted to : (and (>= (Length i) 0)
     (>= (Length (NonDet_AutomataDef |(abcabc)*| 1)) 0)
     (= i (NonDet_AutomataDef |(abcabc)*| 1)))

>> cb_reduce_eq: w = (NonDet_AutomataDef |(abcabcabc)*| 2)


 converted to : (and (>= (Length w) 0)
     (>= (Length (NonDet_AutomataDef |(abcabcabc)*| 2)) 0)
     (= w (NonDet_AutomataDef |(abcabcabc)*| 2)))

>> cb_reduce_eq: w = (Concat (AutomataDef abc) j)


>> cb_reduce_eq: g = (Concat (AutomataDef def) w)


>> cb_reduce_eq: t = (Concat (AutomataDef ghi123) w)


>> cb_reduce_app(): Concat((AutomataDef abc), j)
False update 

>> cb_reduce_app(): Concat((AutomataDef def), w)
False update 

>> cb_reduce_app(): Concat((AutomataDef ghi123), w)
False update 

>> cb_reduce_eq: w = (NonDet_AutomataDef |(abcabc)*| 0)


>> cb_reduce_eq: i = (NonDet_AutomataDef |(abcabc)*| 1)


>> cb_reduce_eq: w = (NonDet_AutomataDef |(abcabcabc)*| 2)


>> cb_reduce_eq: w = (Concat (AutomataDef abc) j)


>> cb_reduce_eq: g = (Concat (AutomataDef def) w)


>> cb_reduce_eq: t = (Concat (AutomataDef ghi123) w)


>> cb_reduce_app(): Concat((AutomataDef abc), j)
False update 

>> cb_reduce_app(): Concat((AutomataDef def), w)
False update 

>> cb_reduce_app(): Concat((AutomataDef ghi123), w)
False update 

>> cb_reduce_eq: w = (NonDet_AutomataDef |(abcabc)*| 0)


>> cb_reduce_eq: i = (NonDet_AutomataDef |(abcabc)*| 1)


>> cb_reduce_eq: w = (NonDet_AutomataDef |(abcabcabc)*| 2)


>> cb_reduce_eq: w = (Concat (AutomataDef abc) j)


>> cb_reduce_eq: g = (Concat (AutomataDef def) w)


>> cb_reduce_eq: t = (Concat (AutomataDef ghi123) w)



Var In Length = {}
***********************************************
*               Starting Search               *
-----------------------------------------------
(let ((a!1 (* (- 1) (Length (Concat (AutomataDef abc) j))))
      (a!3 (* (- 1) (Length (Concat (AutomataDef def) w))))
      (a!5 (* (- 1) (Length (Concat (AutomataDef ghi123) w))))
      (a!7 (>= (Length (Concat (AutomataDef abc) j)) 0))
      (a!8 (>= (Length (Concat (AutomataDef def) w)) 0))
      (a!9 (>= (Length (Concat (AutomataDef ghi123) w)) 0)))
(let ((a!2 (= (+ (Length (AutomataDef abc)) (Length j) a!1) 0))
      (a!4 (= (+ (Length w) (Length (AutomataDef def)) a!3) 0))
      (a!6 (= (+ (Length w) (Length (AutomataDef ghi123)) a!5) 0)))
  (and (= (Length (AutomataDef abc)) 3)
       a!2
       (= (Length (AutomataDef def)) 3)
       a!4
       (= (Length (AutomataDef ghi123)) 6)
       a!6
       (>= (Length j) 0)
       a!7
       (>= (Length w) 0)
       a!8
       a!9
       (>= (Length (NonDet_AutomataDef |(abcabc)*| 0)) 0)
       (= w (NonDet_AutomataDef |(abcabc)*| 0))
       (>= (Length i) 0)
       (>= (Length (NonDet_AutomataDef |(abcabc)*| 1)) 0)
       (= i (NonDet_AutomataDef |(abcabc)*| 1))
       (>= (Length (NonDet_AutomataDef |(abcabcabc)*| 2)) 0)
       (= w (NonDet_AutomataDef |(abcabcabc)*| 2))
       (= w (Concat (AutomataDef abc) j))
       (>= (Length g) 0)
       (= g (Concat (AutomataDef def) w))
       (>= (Length t) 0)
       (= t (Concat (AutomataDef ghi123) w)))))




=================================================================================
** cb_new_eq(): @0
(NonDet_AutomataDef |(abcabc)*| 0)  = w


** @2812 checkLengthConsistency

>> checkLengthConsistency: Passed
< = > A B C D E F G H I J K L M N O P Q R S T U V W X Y a b c d e f g h i j k l m n o p q r s t u v w x y 
** @3516 Cross Check and Update: (NonDet_AutomataDef |(abcabc)*| 0) == w

>> @3336 Eval Intersection size = 2
>> @3382 at Number of elements: 1 
(NonDet_AutomataDef |(abcabc)*| 0)


>> @3144 Eval Node (isIndependence = false): @0 (NonDet_AutomataDef |(abcabc)*| 0)
532 at ../src/regex.cpp: Create Automaton of: known


>> @3405 at __../src/StringTheory.cpp:Update interstion list = 1 -->  1


>> @3420  Element 0: 
 Automaton known:
States: 
0 1 3 4 5 6 7 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 7 

>> @3433 at __../src/StringTheory.cpp: Result intersection: Automaton known:
States: 
0 1 3 4 5 6 7 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 7  @3525 at After all: 
Automaton known:
States: 
0 1 3 4 5 6 7 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 7 

>> @2986 update Equal Map
w
(NonDet_AutomataDef |(abcabc)*| 0)


** 2907 Propagate node: w
 parents_filtered 
(Concat (AutomataDef def) w)
(Concat (AutomataDef ghi123) w)



>> @3029 at __../src/StringTheory.cpp: Update Node: @0 (Concat (AutomataDef def) w)

>> @3277 Eval Concat: (AutomataDef def) *concat* w

>> @3144 Eval Node (isIndependence = false): @0 (AutomataDef def)
532 at ../src/regex.cpp: Create Automaton of: known

>> @3144 Eval Node (isIndependence = false): @0 w


>> @3204 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 3 4 5 6 7 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 7 

>> @3300 at __../src/StringTheory.cpp: Finish Concat
(Concat (AutomataDef def) w)
>> @3091 at __../src/StringTheory.cpp: updated Concat value
 Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 12 
@3554 at ../src/StringTheory.cpp Cross Check: (Concat (AutomataDef def) w)

>> @3336 Eval Intersection size = 1
>> @3382 at Number of elements: 1 
(Concat (AutomataDef def) w)


>> @3141 Eval Node (isIndependence = true): @0 (Concat (AutomataDef def) w)

>> @3277 Eval Concat: (AutomataDef def) *concat* w

>> @3144 Eval Node (isIndependence = false): @0 (AutomataDef def)


>> @3204 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 3 4 
Labels: 
100 101 102 
Inits: 
0 
Accepts: 
4 

>> @3144 Eval Node (isIndependence = false): @0 w


>> @3204 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 3 4 5 6 7 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 7 

>> @3300 at __../src/StringTheory.cpp: Finish Concat


>> @3405 at __../src/StringTheory.cpp:Update interstion list = 1 -->  1


>> @3420  Element 0: 
 Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 12 

>> @3433 at __../src/StringTheory.cpp: Result intersection: Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 12  @3563 at __../src/StringTheory.cpp: After all: 
Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 12 

** 2907 Propagate node: (Concat (AutomataDef def) w)
 parents_filtered 



>> @3029 at __../src/StringTheory.cpp: Update Node: @0 (Concat (AutomataDef ghi123) w)

>> @3277 Eval Concat: (AutomataDef ghi123) *concat* w

>> @3144 Eval Node (isIndependence = false): @0 (AutomataDef ghi123)
532 at ../src/regex.cpp: Create Automaton of: known

>> @3144 Eval Node (isIndependence = false): @0 w


>> @3204 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 3 4 5 6 7 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 7 

>> @3300 at __../src/StringTheory.cpp: Finish Concat
(Concat (AutomataDef ghi123) w)
>> @3091 at __../src/StringTheory.cpp: updated Concat value
 Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 
Labels: 
0 49 50 51 97 98 99 103 104 105 
Inits: 
0 
Accepts: 
8 15 
@3554 at ../src/StringTheory.cpp Cross Check: (Concat (AutomataDef ghi123) w)

>> @3336 Eval Intersection size = 1
>> @3382 at Number of elements: 1 
(Concat (AutomataDef ghi123) w)


>> @3141 Eval Node (isIndependence = true): @0 (Concat (AutomataDef ghi123) w)

>> @3277 Eval Concat: (AutomataDef ghi123) *concat* w

>> @3144 Eval Node (isIndependence = false): @0 (AutomataDef ghi123)


>> @3204 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 2 3 4 5 6 7 
Labels: 
49 50 51 103 104 105 
Inits: 
0 
Accepts: 
7 

>> @3144 Eval Node (isIndependence = false): @0 w


>> @3204 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 3 4 5 6 7 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 7 

>> @3300 at __../src/StringTheory.cpp: Finish Concat


>> @3405 at __../src/StringTheory.cpp:Update interstion list = 1 -->  1


>> @3420  Element 0: 
 Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 
Labels: 
0 49 50 51 97 98 99 103 104 105 
Inits: 
0 
Accepts: 
8 15 

>> @3433 at __../src/StringTheory.cpp: Result intersection: Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 
Labels: 
0 49 50 51 97 98 99 103 104 105 
Inits: 
0 
Accepts: 
8 15  @3563 at __../src/StringTheory.cpp: After all: 
Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 
Labels: 
0 49 50 51 97 98 99 103 104 105 
Inits: 
0 
Accepts: 
8 15 

** 2907 Propagate node: (Concat (AutomataDef ghi123) w)
 parents_filtered 


=================================================================================
** implyEqualityForConcatMember(): @0





=================================================================================
** cb_new_eq(): @0
(NonDet_AutomataDef |(abcabc)*| 1)  = i


** @2812 checkLengthConsistency

>> checkLengthConsistency: Passed
< = > A B C D E F G H I J K L M N O P Q R S T U V W X Y a b c d e f g h i j k l m n o p q r s t u v w x y 
** @3516 Cross Check and Update: (NonDet_AutomataDef |(abcabc)*| 1) == i

>> @3336 Eval Intersection size = 2
>> @3382 at Number of elements: 1 
(NonDet_AutomataDef |(abcabc)*| 1)


>> @3144 Eval Node (isIndependence = false): @0 (NonDet_AutomataDef |(abcabc)*| 1)
532 at ../src/regex.cpp: Create Automaton of: known


>> @3405 at __../src/StringTheory.cpp:Update interstion list = 1 -->  1


>> @3420  Element 0: 
 Automaton known:
States: 
0 1 3 4 5 6 7 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 7 

>> @3433 at __../src/StringTheory.cpp: Result intersection: Automaton known:
States: 
0 1 3 4 5 6 7 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 7  @3525 at After all: 
Automaton known:
States: 
0 1 3 4 5 6 7 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 7 

>> @2986 update Equal Map
i
(NonDet_AutomataDef |(abcabc)*| 1)


** 2907 Propagate node: i
 parents_filtered 


=================================================================================
** implyEqualityForConcatMember(): @0





=================================================================================
** cb_new_eq(): @0
w  = (NonDet_AutomataDef |(abcabcabc)*| 2)


** @2812 checkLengthConsistency

>> checkLengthConsistency: Passed
< = > A B C D E F G H I J K L M N O P Q R S T U V W X Y a b c d e f g h i j k l m n o p q r s t u v w x y 
** @3516 Cross Check and Update: w == (NonDet_AutomataDef |(abcabcabc)*| 2)

>> @3336 Eval Intersection size = 3
>> @3382 at Number of elements: 2 
(NonDet_AutomataDef |(abcabc)*| 0)
(NonDet_AutomataDef |(abcabcabc)*| 2)


>> @3144 Eval Node (isIndependence = false): @0 (NonDet_AutomataDef |(abcabc)*| 0)


>> @3204 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 3 4 5 6 7 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 7 

>> @3144 Eval Node (isIndependence = false): @0 (NonDet_AutomataDef |(abcabcabc)*| 2)
532 at ../src/regex.cpp: Create Automaton of: known


>> @3405 at __../src/StringTheory.cpp:Update interstion list = 2 -->  2


>> @3420  Element 0: 
 Automaton known:
States: 
0 1 3 4 5 6 7 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 7 

>> @3425  Element 1: 
 Automaton known:
States: 
0 1 3 4 5 6 7 8 9 10 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 10 

>> @3433 at __../src/StringTheory.cpp: Result intersection: Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 18  @3525 at After all: 
Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 18 

>> @2986 update Equal Map
(NonDet_AutomataDef |(abcabcabc)*| 2)
w
(NonDet_AutomataDef |(abcabc)*| 0)


** 2907 Propagate node: w
 parents_filtered 
(Concat (AutomataDef def) w)
(Concat (AutomataDef ghi123) w)



>> @3029 at __../src/StringTheory.cpp: Update Node: @0 (Concat (AutomataDef def) w)

>> @3277 Eval Concat: (AutomataDef def) *concat* w

>> @3144 Eval Node (isIndependence = false): @0 (AutomataDef def)


>> @3204 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 3 4 
Labels: 
100 101 102 
Inits: 
0 
Accepts: 
4 

>> @3144 Eval Node (isIndependence = false): @0 w


>> @3204 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 18 

>> @3300 at __../src/StringTheory.cpp: Finish Concat
(Concat (AutomataDef def) w)
>> @3091 at __../src/StringTheory.cpp: updated Concat value
 Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 23 
@3554 at ../src/StringTheory.cpp Cross Check: (Concat (AutomataDef def) w)

>> @3336 Eval Intersection size = 1
>> @3382 at Number of elements: 1 
(Concat (AutomataDef def) w)


>> @3141 Eval Node (isIndependence = true): @0 (Concat (AutomataDef def) w)

>> @3277 Eval Concat: (AutomataDef def) *concat* w

>> @3144 Eval Node (isIndependence = false): @0 (AutomataDef def)


>> @3204 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 3 4 
Labels: 
100 101 102 
Inits: 
0 
Accepts: 
4 

>> @3144 Eval Node (isIndependence = false): @0 w


>> @3204 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 18 

>> @3300 at __../src/StringTheory.cpp: Finish Concat


>> @3405 at __../src/StringTheory.cpp:Update interstion list = 1 -->  1


>> @3420  Element 0: 
 Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 23 

>> @3433 at __../src/StringTheory.cpp: Result intersection: Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 23  @3563 at __../src/StringTheory.cpp: After all: 
Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 23 

** 2907 Propagate node: (Concat (AutomataDef def) w)
 parents_filtered 



>> @3029 at __../src/StringTheory.cpp: Update Node: @0 (Concat (AutomataDef ghi123) w)

>> @3277 Eval Concat: (AutomataDef ghi123) *concat* w

>> @3144 Eval Node (isIndependence = false): @0 (AutomataDef ghi123)


>> @3204 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 2 3 4 5 6 7 
Labels: 
49 50 51 103 104 105 
Inits: 
0 
Accepts: 
7 

>> @3144 Eval Node (isIndependence = false): @0 w


>> @3204 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 18 

>> @3300 at __../src/StringTheory.cpp: Finish Concat
(Concat (AutomataDef ghi123) w)
>> @3091 at __../src/StringTheory.cpp: updated Concat value
 Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 
Labels: 
0 49 50 51 97 98 99 103 104 105 
Inits: 
0 
Accepts: 
8 26 
@3554 at ../src/StringTheory.cpp Cross Check: (Concat (AutomataDef ghi123) w)

>> @3336 Eval Intersection size = 1
>> @3382 at Number of elements: 1 
(Concat (AutomataDef ghi123) w)


>> @3141 Eval Node (isIndependence = true): @0 (Concat (AutomataDef ghi123) w)

>> @3277 Eval Concat: (AutomataDef ghi123) *concat* w

>> @3144 Eval Node (isIndependence = false): @0 (AutomataDef ghi123)


>> @3204 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 2 3 4 5 6 7 
Labels: 
49 50 51 103 104 105 
Inits: 
0 
Accepts: 
7 

>> @3144 Eval Node (isIndependence = false): @0 w


>> @3204 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 18 

>> @3300 at __../src/StringTheory.cpp: Finish Concat


>> @3405 at __../src/StringTheory.cpp:Update interstion list = 1 -->  1


>> @3420  Element 0: 
 Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 
Labels: 
0 49 50 51 97 98 99 103 104 105 
Inits: 
0 
Accepts: 
8 26 

>> @3433 at __../src/StringTheory.cpp: Result intersection: Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 
Labels: 
0 49 50 51 97 98 99 103 104 105 
Inits: 
0 
Accepts: 
8 26  @3563 at __../src/StringTheory.cpp: After all: 
Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 
Labels: 
0 49 50 51 97 98 99 103 104 105 
Inits: 
0 
Accepts: 
8 26 

** 2907 Propagate node: (Concat (AutomataDef ghi123) w)
 parents_filtered 


=================================================================================
** implyEqualityForConcatMember(): @0





=================================================================================
** cb_new_eq(): @0
w  = (Concat (AutomataDef abc) j)
(AutomataDef abc): length = 3 


** @2812 checkLengthConsistency

>> checkLengthConsistency: Passed
< = > A B C D E F G H I J K L M N O P Q R S T U V W X Y a b c d e f g h i j k l m n o p q r s t u v w x y 
** @3516 Cross Check and Update: w == (Concat (AutomataDef abc) j)

>> @3336 Eval Intersection size = 4
>> @3382 at Number of elements: 3 
(NonDet_AutomataDef |(abcabcabc)*| 2)
(NonDet_AutomataDef |(abcabc)*| 0)
(Concat (AutomataDef abc) j)


>> @3144 Eval Node (isIndependence = false): @0 (NonDet_AutomataDef |(abcabcabc)*| 2)


>> @3204 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 18 

>> @3144 Eval Node (isIndependence = false): @0 (NonDet_AutomataDef |(abcabc)*| 0)


>> @3204 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 18 

>> @3144 Eval Node (isIndependence = false): @0 (Concat (AutomataDef abc) j)

>> @3277 Eval Concat: (AutomataDef abc) *concat* j

>> @3144 Eval Node (isIndependence = false): @0 (AutomataDef abc)
532 at ../src/regex.cpp: Create Automaton of: known

>> @3144 Eval Node (isIndependence = false): @0 j

>> @3336 Eval Intersection size = 1
>> @3382 at Number of elements: 0 


>> @3399 at __../src/StringTheory.cpp: UNKNOWN (0 elements)

>> @3155 Value of variable: @0: uNkNoWn 


>> @3405 at __../src/StringTheory.cpp:Update interstion list = 2 -->  1


>> @3420  Element 0: 
 Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 18 

>> @3433 at __../src/StringTheory.cpp: Result intersection: Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 18  @3525 at After all: 
Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 18 

>> @2986 update Equal Map
(Concat (AutomataDef abc) j)
(NonDet_AutomataDef |(abcabcabc)*| 2)
w
(NonDet_AutomataDef |(abcabc)*| 0)


** 2907 Propagate node: w
 parents_filtered 
(Concat (AutomataDef def) w)
(Concat (AutomataDef ghi123) w)



>> @3029 at __../src/StringTheory.cpp: Update Node: @0 (Concat (AutomataDef def) w)

>> @3277 Eval Concat: (AutomataDef def) *concat* w

>> @3144 Eval Node (isIndependence = false): @0 (AutomataDef def)


>> @3204 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 3 4 
Labels: 
100 101 102 
Inits: 
0 
Accepts: 
4 

>> @3144 Eval Node (isIndependence = false): @0 w


>> @3204 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 18 

>> @3300 at __../src/StringTheory.cpp: Finish Concat
(Concat (AutomataDef def) w)
>> @3091 at __../src/StringTheory.cpp: updated Concat value
 Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 23 
@3554 at ../src/StringTheory.cpp Cross Check: (Concat (AutomataDef def) w)

>> @3336 Eval Intersection size = 1
>> @3382 at Number of elements: 1 
(Concat (AutomataDef def) w)


>> @3141 Eval Node (isIndependence = true): @0 (Concat (AutomataDef def) w)

>> @3277 Eval Concat: (AutomataDef def) *concat* w

>> @3144 Eval Node (isIndependence = false): @0 (AutomataDef def)


>> @3204 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 3 4 
Labels: 
100 101 102 
Inits: 
0 
Accepts: 
4 

>> @3144 Eval Node (isIndependence = false): @0 w


>> @3204 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 18 

>> @3300 at __../src/StringTheory.cpp: Finish Concat


>> @3405 at __../src/StringTheory.cpp:Update interstion list = 1 -->  1


>> @3420  Element 0: 
 Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 23 

>> @3433 at __../src/StringTheory.cpp: Result intersection: Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 23  @3563 at __../src/StringTheory.cpp: After all: 
Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 23 

** 2907 Propagate node: (Concat (AutomataDef def) w)
 parents_filtered 



>> @3029 at __../src/StringTheory.cpp: Update Node: @0 (Concat (AutomataDef ghi123) w)

>> @3277 Eval Concat: (AutomataDef ghi123) *concat* w

>> @3144 Eval Node (isIndependence = false): @0 (AutomataDef ghi123)


>> @3204 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 2 3 4 5 6 7 
Labels: 
49 50 51 103 104 105 
Inits: 
0 
Accepts: 
7 

>> @3144 Eval Node (isIndependence = false): @0 w


>> @3204 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 18 

>> @3300 at __../src/StringTheory.cpp: Finish Concat
(Concat (AutomataDef ghi123) w)
>> @3091 at __../src/StringTheory.cpp: updated Concat value
 Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 
Labels: 
0 49 50 51 97 98 99 103 104 105 
Inits: 
0 
Accepts: 
8 26 
@3554 at ../src/StringTheory.cpp Cross Check: (Concat (AutomataDef ghi123) w)

>> @3336 Eval Intersection size = 1
>> @3382 at Number of elements: 1 
(Concat (AutomataDef ghi123) w)


>> @3141 Eval Node (isIndependence = true): @0 (Concat (AutomataDef ghi123) w)

>> @3277 Eval Concat: (AutomataDef ghi123) *concat* w

>> @3144 Eval Node (isIndependence = false): @0 (AutomataDef ghi123)


>> @3204 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 2 3 4 5 6 7 
Labels: 
49 50 51 103 104 105 
Inits: 
0 
Accepts: 
7 

>> @3144 Eval Node (isIndependence = false): @0 w


>> @3204 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 18 

>> @3300 at __../src/StringTheory.cpp: Finish Concat


>> @3405 at __../src/StringTheory.cpp:Update interstion list = 1 -->  1


>> @3420  Element 0: 
 Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 
Labels: 
0 49 50 51 97 98 99 103 104 105 
Inits: 
0 
Accepts: 
8 26 

>> @3433 at __../src/StringTheory.cpp: Result intersection: Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 
Labels: 
0 49 50 51 97 98 99 103 104 105 
Inits: 
0 
Accepts: 
8 26  @3563 at __../src/StringTheory.cpp: After all: 
Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 
Labels: 
0 49 50 51 97 98 99 103 104 105 
Inits: 
0 
Accepts: 
8 26 

** 2907 Propagate node: (Concat (AutomataDef ghi123) w)
 parents_filtered 


=================================================================================
** implyEqualityForConcatMember(): @0





=================================================================================
** cb_new_eq(): @0
(Concat (AutomataDef def) w)  = g


** @2812 checkLengthConsistency

>> checkLengthConsistency: Passed
< = > A B C D E F G H I J K L M N O P Q R S T U V W X Y a b c d e f g h i j k l m n o p q r s t u v w x y 
** @3516 Cross Check and Update: (Concat (AutomataDef def) w) == g

>> @3336 Eval Intersection size = 2
>> @3382 at Number of elements: 1 
(Concat (AutomataDef def) w)


>> @3144 Eval Node (isIndependence = false): @0 (Concat (AutomataDef def) w)


>> @3204 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 23 


>> @3405 at __../src/StringTheory.cpp:Update interstion list = 1 -->  1


>> @3420  Element 0: 
 Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 23 

>> @3433 at __../src/StringTheory.cpp: Result intersection: Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 23  @3525 at After all: 
Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 23 

>> @2986 update Equal Map
g
(Concat (AutomataDef def) w)


** 2907 Propagate node: (Concat (AutomataDef def) w)
 parents_filtered 


=================================================================================
** implyEqualityForConcatMember(): @0





=================================================================================
** cb_new_eq(): @0
(Concat (AutomataDef ghi123) w)  = t


** @2812 checkLengthConsistency

>> checkLengthConsistency: Passed
< = > A B C D E F G H I J K L M N O P Q R S T U V W X Y a b c d e f g h i j k l m n o p q r s t u v w x y 
** @3516 Cross Check and Update: (Concat (AutomataDef ghi123) w) == t

>> @3336 Eval Intersection size = 2
>> @3382 at Number of elements: 1 
(Concat (AutomataDef ghi123) w)


>> @3144 Eval Node (isIndependence = false): @0 (Concat (AutomataDef ghi123) w)


>> @3204 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 
Labels: 
0 49 50 51 97 98 99 103 104 105 
Inits: 
0 
Accepts: 
8 26 


>> @3405 at __../src/StringTheory.cpp:Update interstion list = 1 -->  1


>> @3420  Element 0: 
 Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 
Labels: 
0 49 50 51 97 98 99 103 104 105 
Inits: 
0 
Accepts: 
8 26 

>> @3433 at __../src/StringTheory.cpp: Result intersection: Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 
Labels: 
0 49 50 51 97 98 99 103 104 105 
Inits: 
0 
Accepts: 
8 26  @3525 at After all: 
Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 
Labels: 
0 49 50 51 97 98 99 103 104 105 
Inits: 
0 
Accepts: 
8 26 

>> @2986 update Equal Map
t
(Concat (AutomataDef ghi123) w)


** 2907 Propagate node: (Concat (AutomataDef ghi123) w)
 parents_filtered 


=================================================================================
** implyEqualityForConcatMember(): @0




vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
                cb_final_check @ Level [0] 
=============================================================
Connected Variables
w

4151 g is a root.
4151 i is a root.
4151 t is a root.
 parse regex 
abc
(abc)*

g =
	"def" 	"abc" 	j 
	"def" 	"(abcabcabc)*" 
	"def" 	"(abcabc)*" 

i =
	"(abcabc)*" 

t =
	"ghi123" 	"abc" 	j 
	"ghi123" 	"(abcabcabc)*" 
	"ghi123" 	"(abcabc)*" 

1272 Connected Variables:
j at "def" "abc" j 

g =
	"defabc" 	j 
	"def" 	"(abcabcabc)*__0" 
	"def" 	"(abcabc)*__1" 

t =
	"ghi123abc" 	j 
	"ghi123" 	"(abcabcabc)*__2" 
	"ghi123" 	"(abcabc)*__3" 

1215 Const map:
(abcabc)*__1: const_4
(abcabc)*__3: const_9
(abcabcabc)*__0: const_2
(abcabcabc)*__2: const_7
def: const_3
defabc: const_0
ghi123: const_8
ghi123abc: const_5

1624 Max list size: 2
>> equalities to SMT 
defabc.-1 defabc.-2 j.0 j.1 = def.-1 def.-2 (abcabcabc)*__0.-100 
Number of flats: 4 flats = 3 flats

454 Calculating all possible cases: 0.000 seconds, 11 cases.
Checking case
9999999 9999999 9999999 100000000 
  3   3   3 
Checking case
  0   0   0 100000000 
100000000   3   3 
Checking case
100000000   2   2   2 
  0   0 100000000 
677Accepted
1 - 2 - 
------------
Accepted
2 - 1 - 
------------
677Accepted
3 - -6 - 
------------
Accepted
0 - 999 - 
------------
Correct case
100000000   2   2   2 
  0   0 100000000 
479 (and 
 (= len_const_0_1 (+ len_const_3_1 len_const_3_2 )) (and (= len_const_0_1 3) (= (+ len_const_3_1 len_const_3_2) 3) )
 (= len_const_2_100 (+ len_const_0_2 len_j_0 len_j_1 )) (or (and (= len_const_0_2 0) (forall ((i Int)) (implies (and (< i (+ len_j_0 len_j_1 )) (>= i 0)) (= (select arr_j (+ i 0)) (select arr_const_2 (mod (+ i len_const_0_2) 9))))) (= (mod (+ len_j_0 len_j_1 ) 9) 0) ) (and (= len_const_0_2 3) (forall ((i Int)) (implies (and (< i (+ len_j_0 len_j_1 )) (>= i 0)) (= (select arr_j (+ i 0)) (select arr_const_2 (mod (+ i len_const_0_2) 9))))) (= (mod (+ len_j_0 len_j_1 ) 9) 6) ) )
)
Checking case
9999999 100000000   2   2 
  1   1 100000000 
677Checking case
  1   1   2   2 
9999999 100000000 100000000 
Checking case
  0   1   2   2 
  0   1 100000000 
Checking case
  2   2   2   2 
9999999 9999999 100000000 
Checking case
9999999 9999999 100000000   2 
  2   2   3 
Checking case
  0   1   1   2 
  0 100000000   3 
677Accepted
0 - 0 - 
------------
Correct case
  0   1   1   2 
  0 100000000   3 
479 (and 
 (= len_const_3_2 (+ len_const_0_2 len_j_0 )) (and (= len_const_0_2 0)  (= len_j_0 0) )
(= len_const_0_1 len_const_3_1) (<= len_const_0_1 3) (= len_j_1 len_const_2_100) (forall ((i Int)) (implies (and (< i len_const_2_100) (>= i 0)) (= (select arr_j (+ i len_j_0)) (select arr_const_2 (mod i 9))))) 
)
Checking case
  1   1   1   2 
9999999 100000000   3 
Checking case
  0   0   1   2 
100000000   2   3 
 print cases
(and 
 (= len_const_0_1 (+ len_const_3_1 len_const_3_2 )) (and (= len_const_0_1 3) (= (+ len_const_3_1 len_const_3_2) 3) )
 (= len_const_2_100 (+ len_const_0_2 len_j_0 len_j_1 )) (or (and (= len_const_0_2 0) (forall ((i Int)) (implies (and (< i (+ len_j_0 len_j_1 )) (>= i 0)) (= (select arr_j (+ i 0)) (select arr_const_2 (mod (+ i len_const_0_2) 9))))) (= (mod (+ len_j_0 len_j_1 ) 9) 0) ) (and (= len_const_0_2 3) (forall ((i Int)) (implies (and (< i (+ len_j_0 len_j_1 )) (>= i 0)) (= (select arr_j (+ i 0)) (select arr_const_2 (mod (+ i len_const_0_2) 9))))) (= (mod (+ len_j_0 len_j_1 ) 9) 6) ) )
)
(and 
 (= len_const_3_2 (+ len_const_0_2 len_j_0 )) (and (= len_const_0_2 0)  (= len_j_0 0) )
(= len_const_0_1 len_const_3_1) (<= len_const_0_1 3) (= len_j_1 len_const_2_100) (forall ((i Int)) (implies (and (< i len_const_2_100) (>= i 0)) (= (select arr_j (+ i len_j_0)) (select arr_const_2 (mod i 9))))) 
)

1683 Convert to SMT: 0.000 seconds.

>> equalities to SMT 
defabc.-1 defabc.-2 j.0 j.1 = def.-1 def.-2 (abcabc)*__1.-100 
Number of flats: 4 flats = 3 flats

454 Calculating all possible cases: 0.000 seconds, 11 cases.
Checking case
9999999 9999999 9999999 100000000 
  3   3   3 
Checking case
  0   0   0 100000000 
100000000   3   3 
Checking case
100000000   2   2   2 
  0   0 100000000 
677Accepted
1 - 2 - 
------------
Accepted
2 - 1 - 
------------
677Accepted
3 - -3 - 
------------
Accepted
0 - 999 - 
------------
Correct case
100000000   2   2   2 
  0   0 100000000 
479 (and 
 (= len_const_0_1 (+ len_const_3_1 len_const_3_2 )) (and (= len_const_0_1 3) (= (+ len_const_3_1 len_const_3_2) 3) )
 (= len_const_4_100 (+ len_const_0_2 len_j_0 len_j_1 )) (or (and (= len_const_0_2 0) (forall ((i Int)) (implies (and (< i (+ len_j_0 len_j_1 )) (>= i 0)) (= (select arr_j (+ i 0)) (select arr_const_4 (mod (+ i len_const_0_2) 6))))) (= (mod (+ len_j_0 len_j_1 ) 6) 0) ) (and (= len_const_0_2 3) (forall ((i Int)) (implies (and (< i (+ len_j_0 len_j_1 )) (>= i 0)) (= (select arr_j (+ i 0)) (select arr_const_4 (mod (+ i len_const_0_2) 6))))) (= (mod (+ len_j_0 len_j_1 ) 6) 3) ) )
)
Checking case
9999999 100000000   2   2 
  1   1 100000000 
677Checking case
  1   1   2   2 
9999999 100000000 100000000 
Checking case
  0   1   2   2 
  0   1 100000000 
Checking case
  2   2   2   2 
9999999 9999999 100000000 
Checking case
9999999 9999999 100000000   2 
  2   2   3 
Checking case
  0   1   1   2 
  0 100000000   3 
677Accepted
0 - 0 - 
------------
Correct case
  0   1   1   2 
  0 100000000   3 
479 (and 
 (= len_const_3_2 (+ len_const_0_2 len_j_0 )) (and (= len_const_0_2 0)  (= len_j_0 0) )
(= len_const_0_1 len_const_3_1) (<= len_const_0_1 3) (= len_j_1 len_const_4_100) (forall ((i Int)) (implies (and (< i len_const_4_100) (>= i 0)) (= (select arr_j (+ i len_j_0)) (select arr_const_4 (mod i 6))))) 
)
Checking case
  1   1   1   2 
9999999 100000000   3 
Checking case
  0   0   1   2 
100000000   2   3 
 print cases
(and 
 (= len_const_0_1 (+ len_const_3_1 len_const_3_2 )) (and (= len_const_0_1 3) (= (+ len_const_3_1 len_const_3_2) 3) )
 (= len_const_4_100 (+ len_const_0_2 len_j_0 len_j_1 )) (or (and (= len_const_0_2 0) (forall ((i Int)) (implies (and (< i (+ len_j_0 len_j_1 )) (>= i 0)) (= (select arr_j (+ i 0)) (select arr_const_4 (mod (+ i len_const_0_2) 6))))) (= (mod (+ len_j_0 len_j_1 ) 6) 0) ) (and (= len_const_0_2 3) (forall ((i Int)) (implies (and (< i (+ len_j_0 len_j_1 )) (>= i 0)) (= (select arr_j (+ i 0)) (select arr_const_4 (mod (+ i len_const_0_2) 6))))) (= (mod (+ len_j_0 len_j_1 ) 6) 3) ) )
)
(and 
 (= len_const_3_2 (+ len_const_0_2 len_j_0 )) (and (= len_const_0_2 0)  (= len_j_0 0) )
(= len_const_0_1 len_const_3_1) (<= len_const_0_1 3) (= len_j_1 len_const_4_100) (forall ((i Int)) (implies (and (< i len_const_4_100) (>= i 0)) (= (select arr_j (+ i len_j_0)) (select arr_const_4 (mod i 6))))) 
)

1683 Convert to SMT: 0.000 seconds.

>> equalities to SMT 
def.-1 def.-2 (abcabcabc)*__0.-100 = def.-1 def.-2 (abcabc)*__1.-100 
Number of flats: 3 flats = 3 flats

454 Calculating all possible cases: 0.000 seconds, 7 cases.
Checking case
9999999 9999999 100000000 
  2   2   2 
Checking case
  0   0 100000000 
100000000   2   2 
677Accepted
0 - 999 - 
------------
677Accepted
1 - 2 - 
------------
Accepted
2 - 1 - 
------------
Correct case
  0   0 100000000 
100000000   2   2 
479 (and 
 (= len_const_2_100 (+ len_const_3_2 len_const_4_100 )) (and (= len_const_3_2 0) (= (mod len_const_4_100 9) 0) )
 (= len_const_3_1 (+ len_const_3_1 len_const_3_2 )) (and (= len_const_3_1 3) (= (+ len_const_3_1 len_const_3_2) 3) )
)
Checking case
100000000   2   2 
  0   0 100000000 
677Accepted
1 - 2 - 
------------
Accepted
2 - 1 - 
------------
677Accepted
0 - 999 - 
------------
Correct case
100000000   2   2 
  0   0 100000000 
479 (and 
 (= len_const_3_1 (+ len_const_3_1 len_const_3_2 )) (and (= len_const_3_1 3) (= (+ len_const_3_1 len_const_3_2) 3) )
 (= len_const_4_100 (+ len_const_3_2 len_const_2_100 )) (and (= len_const_3_2 0) (= (mod len_const_2_100 6) 0) )
)
Checking case
  2   2   2 
9999999 9999999 100000000 
Checking case
9999999 100000000   2 
  1   1   2 
677Checking case
  1   1   2 
9999999 100000000   2 
677Checking case
  0   1   2 
  0   1   2 
Correct case
  0   1   2 
  0   1   2 
479 (and 
(= len_const_3_1 len_const_3_1) (= len_const_3_2 len_const_3_2) (= len_const_2_100 len_const_4_100) (= (mod len_const_2_100 18) 0) 
)
 print cases
(and 
 (= len_const_2_100 (+ len_const_3_2 len_const_4_100 )) (and (= len_const_3_2 0) (= (mod len_const_4_100 9) 0) )
 (= len_const_3_1 (+ len_const_3_1 len_const_3_2 )) (and (= len_const_3_1 3) (= (+ len_const_3_1 len_const_3_2) 3) )
)
(and 
 (= len_const_3_1 (+ len_const_3_1 len_const_3_2 )) (and (= len_const_3_1 3) (= (+ len_const_3_1 len_const_3_2) 3) )
 (= len_const_4_100 (+ len_const_3_2 len_const_2_100 )) (and (= len_const_3_2 0) (= (mod len_const_2_100 6) 0) )
)
(and 
(= len_const_3_1 len_const_3_1) (= len_const_3_2 len_const_3_2) (= len_const_2_100 len_const_4_100) (= (mod len_const_2_100 18) 0) 
)

1683 Convert to SMT: 0.000 seconds.

1624 Max list size: 2
>> equalities to SMT 
ghi123abc.-1 ghi123abc.-2 j.0 j.1 = ghi123.-1 ghi123.-2 (abcabcabc)*__2.-100 
Number of flats: 4 flats = 3 flats

454 Calculating all possible cases: 0.000 seconds, 11 cases.
Checking case
9999999 9999999 9999999 100000000 
  3   3   3 
Checking case
  0   0   0 100000000 
100000000   3   3 
Checking case
100000000   2   2   2 
  0   0 100000000 
677Accepted
1 - 5 - 
------------
Accepted
2 - 4 - 
------------
Accepted
3 - 3 - 
------------
Accepted
4 - 2 - 
------------
Accepted
5 - 1 - 
------------
677Accepted
3 - -6 - 
------------
Accepted
0 - 999 - 
------------
Correct case
100000000   2   2   2 
  0   0 100000000 
479 (and 
 (= len_const_5_1 (+ len_const_8_1 len_const_8_2 )) (and (= len_const_5_1 6) (= (+ len_const_8_1 len_const_8_2) 6) )
 (= len_const_7_100 (+ len_const_5_2 len_j_0 len_j_1 )) (or (and (= len_const_5_2 0) (forall ((i Int)) (implies (and (< i (+ len_j_0 len_j_1 )) (>= i 0)) (= (select arr_j (+ i 0)) (select arr_const_7 (mod (+ i len_const_5_2) 9))))) (= (mod (+ len_j_0 len_j_1 ) 9) 0) ) (and (= len_const_5_2 3) (forall ((i Int)) (implies (and (< i (+ len_j_0 len_j_1 )) (>= i 0)) (= (select arr_j (+ i 0)) (select arr_const_7 (mod (+ i len_const_5_2) 9))))) (= (mod (+ len_j_0 len_j_1 ) 9) 6) ) )
)
Checking case
9999999 100000000   2   2 
  1   1 100000000 
677Checking case
  1   1   2   2 
9999999 100000000 100000000 
Checking case
  0   1   2   2 
  0   1 100000000 
Checking case
  2   2   2   2 
9999999 9999999 100000000 
Checking case
9999999 9999999 100000000   2 
  2   2   3 
Checking case
  0   1   1   2 
  0 100000000   3 
677Accepted
0 - 0 - 
------------
Correct case
  0   1   1   2 
  0 100000000   3 
479 (and 
 (= len_const_8_2 (+ len_const_5_2 len_j_0 )) (and (= len_const_5_2 0)  (= len_j_0 0) )
(= len_const_5_1 len_const_8_1) (<= len_const_5_1 6) (= len_j_1 len_const_7_100) (forall ((i Int)) (implies (and (< i len_const_7_100) (>= i 0)) (= (select arr_j (+ i len_j_0)) (select arr_const_7 (mod i 9))))) 
)
Checking case
  1   1   1   2 
9999999 100000000   3 
Checking case
  0   0   1   2 
100000000   2   3 
 print cases
(and 
 (= len_const_5_1 (+ len_const_8_1 len_const_8_2 )) (and (= len_const_5_1 6) (= (+ len_const_8_1 len_const_8_2) 6) )
 (= len_const_7_100 (+ len_const_5_2 len_j_0 len_j_1 )) (or (and (= len_const_5_2 0) (forall ((i Int)) (implies (and (< i (+ len_j_0 len_j_1 )) (>= i 0)) (= (select arr_j (+ i 0)) (select arr_const_7 (mod (+ i len_const_5_2) 9))))) (= (mod (+ len_j_0 len_j_1 ) 9) 0) ) (and (= len_const_5_2 3) (forall ((i Int)) (implies (and (< i (+ len_j_0 len_j_1 )) (>= i 0)) (= (select arr_j (+ i 0)) (select arr_const_7 (mod (+ i len_const_5_2) 9))))) (= (mod (+ len_j_0 len_j_1 ) 9) 6) ) )
)
(and 
 (= len_const_8_2 (+ len_const_5_2 len_j_0 )) (and (= len_const_5_2 0)  (= len_j_0 0) )
(= len_const_5_1 len_const_8_1) (<= len_const_5_1 6) (= len_j_1 len_const_7_100) (forall ((i Int)) (implies (and (< i len_const_7_100) (>= i 0)) (= (select arr_j (+ i len_j_0)) (select arr_const_7 (mod i 9))))) 
)

1683 Convert to SMT: 0.000 seconds.

>> equalities to SMT 
ghi123abc.-1 ghi123abc.-2 j.0 j.1 = ghi123.-1 ghi123.-2 (abcabc)*__3.-100 
Number of flats: 4 flats = 3 flats

454 Calculating all possible cases: 0.000 seconds, 11 cases.
Checking case
9999999 9999999 9999999 100000000 
  3   3   3 
Checking case
  0   0   0 100000000 
100000000   3   3 
Checking case
100000000   2   2   2 
  0   0 100000000 
677Accepted
1 - 5 - 
------------
Accepted
2 - 4 - 
------------
Accepted
3 - 3 - 
------------
Accepted
4 - 2 - 
------------
Accepted
5 - 1 - 
------------
677Accepted
3 - -3 - 
------------
Accepted
0 - 999 - 
------------
Correct case
100000000   2   2   2 
  0   0 100000000 
479 (and 
 (= len_const_5_1 (+ len_const_8_1 len_const_8_2 )) (and (= len_const_5_1 6) (= (+ len_const_8_1 len_const_8_2) 6) )
 (= len_const_9_100 (+ len_const_5_2 len_j_0 len_j_1 )) (or (and (= len_const_5_2 0) (forall ((i Int)) (implies (and (< i (+ len_j_0 len_j_1 )) (>= i 0)) (= (select arr_j (+ i 0)) (select arr_const_9 (mod (+ i len_const_5_2) 6))))) (= (mod (+ len_j_0 len_j_1 ) 6) 0) ) (and (= len_const_5_2 3) (forall ((i Int)) (implies (and (< i (+ len_j_0 len_j_1 )) (>= i 0)) (= (select arr_j (+ i 0)) (select arr_const_9 (mod (+ i len_const_5_2) 6))))) (= (mod (+ len_j_0 len_j_1 ) 6) 3) ) )
)
Checking case
9999999 100000000   2   2 
  1   1 100000000 
677Checking case
  1   1   2   2 
9999999 100000000 100000000 
Checking case
  0   1   2   2 
  0   1 100000000 
Checking case
  2   2   2   2 
9999999 9999999 100000000 
Checking case
9999999 9999999 100000000   2 
  2   2   3 
Checking case
  0   1   1   2 
  0 100000000   3 
677Accepted
0 - 0 - 
------------
Correct case
  0   1   1   2 
  0 100000000   3 
479 (and 
 (= len_const_8_2 (+ len_const_5_2 len_j_0 )) (and (= len_const_5_2 0)  (= len_j_0 0) )
(= len_const_5_1 len_const_8_1) (<= len_const_5_1 6) (= len_j_1 len_const_9_100) (forall ((i Int)) (implies (and (< i len_const_9_100) (>= i 0)) (= (select arr_j (+ i len_j_0)) (select arr_const_9 (mod i 6))))) 
)
Checking case
  1   1   1   2 
9999999 100000000   3 
Checking case
  0   0   1   2 
100000000   2   3 
 print cases
(and 
 (= len_const_5_1 (+ len_const_8_1 len_const_8_2 )) (and (= len_const_5_1 6) (= (+ len_const_8_1 len_const_8_2) 6) )
 (= len_const_9_100 (+ len_const_5_2 len_j_0 len_j_1 )) (or (and (= len_const_5_2 0) (forall ((i Int)) (implies (and (< i (+ len_j_0 len_j_1 )) (>= i 0)) (= (select arr_j (+ i 0)) (select arr_const_9 (mod (+ i len_const_5_2) 6))))) (= (mod (+ len_j_0 len_j_1 ) 6) 0) ) (and (= len_const_5_2 3) (forall ((i Int)) (implies (and (< i (+ len_j_0 len_j_1 )) (>= i 0)) (= (select arr_j (+ i 0)) (select arr_const_9 (mod (+ i len_const_5_2) 6))))) (= (mod (+ len_j_0 len_j_1 ) 6) 3) ) )
)
(and 
 (= len_const_8_2 (+ len_const_5_2 len_j_0 )) (and (= len_const_5_2 0)  (= len_j_0 0) )
(= len_const_5_1 len_const_8_1) (<= len_const_5_1 6) (= len_j_1 len_const_9_100) (forall ((i Int)) (implies (and (< i len_const_9_100) (>= i 0)) (= (select arr_j (+ i len_j_0)) (select arr_const_9 (mod i 6))))) 
)

1683 Convert to SMT: 0.000 seconds.

>> equalities to SMT 
ghi123.-1 ghi123.-2 (abcabcabc)*__2.-100 = ghi123.-1 ghi123.-2 (abcabc)*__3.-100 
Number of flats: 3 flats = 3 flats

454 Calculating all possible cases: 0.000 seconds, 7 cases.
Checking case
9999999 9999999 100000000 
  2   2   2 
Checking case
  0   0 100000000 
100000000   2   2 
677Accepted
0 - 999 - 
------------
677Accepted
1 - 5 - 
------------
Accepted
2 - 4 - 
------------
Accepted
3 - 3 - 
------------
Accepted
4 - 2 - 
------------
Accepted
5 - 1 - 
------------
Correct case
  0   0 100000000 
100000000   2   2 
479 (and 
 (= len_const_7_100 (+ len_const_8_2 len_const_9_100 )) (and (= len_const_8_2 0) (= (mod len_const_9_100 9) 0) )
 (= len_const_8_1 (+ len_const_8_1 len_const_8_2 )) (and (= len_const_8_1 6) (= (+ len_const_8_1 len_const_8_2) 6) )
)
Checking case
100000000   2   2 
  0   0 100000000 
677Accepted
1 - 5 - 
------------
Accepted
2 - 4 - 
------------
Accepted
3 - 3 - 
------------
Accepted
4 - 2 - 
------------
Accepted
5 - 1 - 
------------
677Accepted
0 - 999 - 
------------
Correct case
100000000   2   2 
  0   0 100000000 
479 (and 
 (= len_const_8_1 (+ len_const_8_1 len_const_8_2 )) (and (= len_const_8_1 6) (= (+ len_const_8_1 len_const_8_2) 6) )
 (= len_const_9_100 (+ len_const_8_2 len_const_7_100 )) (and (= len_const_8_2 0) (= (mod len_const_7_100 6) 0) )
)
Checking case
  2   2   2 
9999999 9999999 100000000 
Checking case
9999999 100000000   2 
  1   1   2 
677Checking case
  1   1   2 
9999999 100000000   2 
677Checking case
  0   1   2 
  0   1   2 
Correct case
  0   1   2 
  0   1   2 
479 (and 
(= len_const_8_1 len_const_8_1) (= len_const_8_2 len_const_8_2) (= len_const_7_100 len_const_9_100) (= (mod len_const_7_100 18) 0) 
)
 print cases
(and 
 (= len_const_7_100 (+ len_const_8_2 len_const_9_100 )) (and (= len_const_8_2 0) (= (mod len_const_9_100 9) 0) )
 (= len_const_8_1 (+ len_const_8_1 len_const_8_2 )) (and (= len_const_8_1 6) (= (+ len_const_8_1 len_const_8_2) 6) )
)
(and 
 (= len_const_8_1 (+ len_const_8_1 len_const_8_2 )) (and (= len_const_8_1 6) (= (+ len_const_8_1 len_const_8_2) 6) )
 (= len_const_9_100 (+ len_const_8_2 len_const_7_100 )) (and (= len_const_8_2 0) (= (mod len_const_7_100 6) 0) )
)
(and 
(= len_const_8_1 len_const_8_1) (= len_const_8_2 len_const_8_2) (= len_const_7_100 len_const_9_100) (= (mod len_const_7_100 18) 0) 
)

1683 Convert to SMT: 0.000 seconds.

