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


165 $COMPARAISON: ((((("\""))*([0-9]+))|((("\""))*([a-z]+)))(("\""))*) (((" > ")|(" = ")|(" < "))) ((((("\""))*([0-9]+))|((("\""))*([a-z]+)))(("\""))*)
165 $COMPOP: ((" > ")|(" = ")|(" < "))
165 $EXPRESSION: ((" not "))*((" not "))*(((((("\""))*([0-9]+))|((("\""))*([a-z]+)))(("\""))*) (((" > ")|(" = ")|(" < "))) ((((("\""))*([0-9]+))|((("\""))*([a-z]+)))(("\""))*))((" or ")((" not "))*((" not "))*(((((("\""))*([0-9]+))|((("\""))*([a-z]+)))(("\""))*) (((" > ")|(" = ")|(" < "))) ((((("\""))*([0-9]+))|((("\""))*([a-z]+)))(("\""))*)))*
165 $NOTOP: " not "
165 $NUMBER: [0-9]+
165 $OREXPRESSION: ((" not "))*(((((("\""))*([0-9]+))|((("\""))*([a-z]+)))(("\""))*) (((" > ")|(" = ")|(" < "))) ((((("\""))*([0-9]+))|((("\""))*([a-z]+)))(("\""))*))((" or ")((" not "))*((" not "))*(((((("\""))*([0-9]+))|((("\""))*([a-z]+)))(("\""))*) (((" > ")|(" = ")|(" < "))) ((((("\""))*([0-9]+))|((("\""))*([a-z]+)))(("\""))*)))*
165 $OROP: " or "
165 $QUOTE: "\""
165 $STRING: [a-z]+
165 $TERM: (((("\""))*([0-9]+))|((("\""))*([a-z]+)))(("\""))*
Input file: nonsql.smt2

Grammar file: -model

262 creating /tmp/fat_str_convert/: OK
***********************************************
*              initGraph             *
-----------------------------------------------
 w,
(assert (RegexIn w (RegexStar (Str2Reg "abcabc"))))

 w,
(assert (RegexIn w (RegexStar (Str2Reg "abcabcabc"))))

 w, j,
(assert (= w (Concat "abc" j)))

 g, w,
(assert (= g (Concat "def" w)))

 g, h, i,
(assert (= g (Concat h i)))
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
j
g
h
i

***********************************************
Input loaded:
-----------------------------------------------
(and (RegexIn w (RegexStar (Str2Reg __cOnStStR__x61_x62_x63_x61_x62_x63)))
     (RegexIn w
              (RegexStar (Str2Reg __cOnStStR__x61_x62_x63_x61_x62_x63_x61_x62_x63)))
     (= w (Concat __cOnStStR__x61_x62_x63 j))
     (= g (Concat __cOnStStR__x64_x65_x66 w))
     (= g (Concat h i)))
-----------------------------------------------


>> cb_reduce_app(): Str2Reg("abcabc")


>> cb_reduce_app(): RegexStar((Str2Reg abcabc)) --> NULL


>> RegexIn(w, (RegexStar (Str2Reg abcabc)))
 --> 
w  \in  (abcabc)*


>> cb_reduce_app(): RegexIn(w, (RegexStar (Str2Reg abcabc))) ==> (= w (NonDet_AutomataDef |(abcabc)*| 0))


>> cb_reduce_app(): Str2Reg("abcabcabc")


>> cb_reduce_app(): RegexStar((Str2Reg abcabcabc)) --> NULL


>> RegexIn(w, (RegexStar (Str2Reg abcabcabc)))
 --> 
w  \in  (abcabcabc)*


>> cb_reduce_app(): RegexIn(w, (RegexStar (Str2Reg abcabcabc))) ==> (= w (NonDet_AutomataDef |(abcabcabc)*| 1))


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

>> cb_reduce_app(): Concat(h, i)
>> cb_reduce_app(): Concat(h, i)
False update 
---------------------
Assertion Add(@1422, Level 0):
(and (>= (Length h) 0)
     (>= (Length i) 0)
     (>= (Length (Concat h i)) 0)
     (= (Length (Concat h i)) (+ (Length h) (Length i))))
---------------------


convert to: (Concat h i)


>> cb_reduce_eq: g = (Concat h i)


 converted to : (and (>= (Length g) 0) (= g (Concat h i)))

>> cb_reduce_app(): Concat((AutomataDef abc), j)
False update 

>> cb_reduce_app(): Concat((AutomataDef def), w)
False update 

>> cb_reduce_app(): Concat(h, i)
False update 

>> cb_reduce_eq: w = (NonDet_AutomataDef |(abcabc)*| 0)


 converted to : (and (>= (Length w) 0)
     (>= (Length (NonDet_AutomataDef |(abcabc)*| 0)) 0)
     (= w (NonDet_AutomataDef |(abcabc)*| 0)))

>> cb_reduce_eq: w = (NonDet_AutomataDef |(abcabcabc)*| 1)


 converted to : (and (>= (Length w) 0)
     (>= (Length (NonDet_AutomataDef |(abcabcabc)*| 1)) 0)
     (= w (NonDet_AutomataDef |(abcabcabc)*| 1)))

>> cb_reduce_eq: w = (Concat (AutomataDef abc) j)


>> cb_reduce_eq: g = (Concat (AutomataDef def) w)


>> cb_reduce_eq: g = (Concat h i)


>> cb_reduce_app(): Concat((AutomataDef abc), j)
False update 

>> cb_reduce_app(): Concat((AutomataDef def), w)
False update 

>> cb_reduce_app(): Concat(h, i)
False update 

>> cb_reduce_eq: w = (NonDet_AutomataDef |(abcabc)*| 0)


>> cb_reduce_eq: w = (NonDet_AutomataDef |(abcabcabc)*| 1)


>> cb_reduce_eq: w = (Concat (AutomataDef abc) j)


>> cb_reduce_eq: g = (Concat (AutomataDef def) w)


>> cb_reduce_eq: g = (Concat h i)


>> cb_reduce_app(): Concat((AutomataDef abc), j)
False update 

>> cb_reduce_app(): Concat((AutomataDef def), w)
False update 

>> cb_reduce_app(): Concat(h, i)
False update 

>> cb_reduce_eq: w = (NonDet_AutomataDef |(abcabc)*| 0)


>> cb_reduce_eq: w = (NonDet_AutomataDef |(abcabcabc)*| 1)


>> cb_reduce_eq: w = (Concat (AutomataDef abc) j)


>> cb_reduce_eq: g = (Concat (AutomataDef def) w)


>> cb_reduce_eq: g = (Concat h i)



Var In Length = {}
***********************************************
*               Starting Search               *
-----------------------------------------------
(let ((a!1 (* (- 1) (Length (Concat (AutomataDef abc) j))))
      (a!3 (* (- 1) (Length (Concat (AutomataDef def) w))))
      (a!5 (+ (Length h) (Length i) (* (- 1) (Length (Concat h i)))))
      (a!6 (>= (Length (Concat (AutomataDef abc) j)) 0))
      (a!7 (>= (Length (Concat (AutomataDef def) w)) 0)))
(let ((a!2 (= (+ (Length (AutomataDef abc)) (Length j) a!1) 0))
      (a!4 (= (+ (Length w) (Length (AutomataDef def)) a!3) 0)))
  (and (= (Length (AutomataDef abc)) 3)
       a!2
       (= (Length (AutomataDef def)) 3)
       a!4
       (= a!5 0)
       (>= (Length j) 0)
       a!6
       (>= (Length w) 0)
       a!7
       (>= (Length h) 0)
       (>= (Length i) 0)
       (>= (Length (Concat h i)) 0)
       (>= (Length (NonDet_AutomataDef |(abcabc)*| 0)) 0)
       (= w (NonDet_AutomataDef |(abcabc)*| 0))
       (>= (Length (NonDet_AutomataDef |(abcabcabc)*| 1)) 0)
       (= w (NonDet_AutomataDef |(abcabcabc)*| 1))
       (= w (Concat (AutomataDef abc) j))
       (= g (Concat (AutomataDef def) w))
       (>= (Length g) 0)
       (= g (Concat h i)))))




=================================================================================
** cb_new_eq(): @0
(NonDet_AutomataDef |(abcabc)*| 0)  = w


** @2702 checkLengthConsistency

>> checkLengthConsistency: Passed
< = > A B C D E F G H I J K L M N O P Q R S T U V W X Y a b c d e f g h i j k l m n o p q r s t u v w x y 
** @3406 Cross Check and Update: (NonDet_AutomataDef |(abcabc)*| 0) == w

>> @3226 Eval Intersection size = 2
>> @3272 at Number of elements: 1 
(NonDet_AutomataDef |(abcabc)*| 0)


>> @3034 Eval Node (isIndependence = false): @0 (NonDet_AutomataDef |(abcabc)*| 0)
532 at ../src/regex.cpp: Create Automaton of: known


>> @3295 at __../src/StringTheory.cpp:Update interstion list = 1 -->  1


>> @3310  Element 0: 
 Automaton known:
States: 
0 1 3 4 5 6 7 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 7 

>> @3323 at __../src/StringTheory.cpp: Result intersection: Automaton known:
States: 
0 1 3 4 5 6 7 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 7  @3415 at After all: 
Automaton known:
States: 
0 1 3 4 5 6 7 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 7 

>> @2876 update Equal Map
w
(NonDet_AutomataDef |(abcabc)*| 0)


** 2797 Propagate node: w
 parents_filtered 
(Concat (AutomataDef def) w)



>> @2919 at __../src/StringTheory.cpp: Update Node: @0 (Concat (AutomataDef def) w)

>> @3167 Eval Concat: (AutomataDef def) *concat* w

>> @3034 Eval Node (isIndependence = false): @0 (AutomataDef def)
532 at ../src/regex.cpp: Create Automaton of: known

>> @3034 Eval Node (isIndependence = false): @0 w


>> @3094 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 3 4 5 6 7 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 7 

>> @3190 at __../src/StringTheory.cpp: Finish Concat
(Concat (AutomataDef def) w)
>> @2981 at __../src/StringTheory.cpp: updated Concat value
 Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 12 
@3444 at ../src/StringTheory.cpp Cross Check: (Concat (AutomataDef def) w)

>> @3226 Eval Intersection size = 1
>> @3272 at Number of elements: 1 
(Concat (AutomataDef def) w)


>> @3031 Eval Node (isIndependence = true): @0 (Concat (AutomataDef def) w)

>> @3167 Eval Concat: (AutomataDef def) *concat* w

>> @3034 Eval Node (isIndependence = false): @0 (AutomataDef def)


>> @3094 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 3 4 
Labels: 
100 101 102 
Inits: 
0 
Accepts: 
4 

>> @3034 Eval Node (isIndependence = false): @0 w


>> @3094 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 3 4 5 6 7 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 7 

>> @3190 at __../src/StringTheory.cpp: Finish Concat


>> @3295 at __../src/StringTheory.cpp:Update interstion list = 1 -->  1


>> @3310  Element 0: 
 Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 12 

>> @3323 at __../src/StringTheory.cpp: Result intersection: Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 12  @3453 at __../src/StringTheory.cpp: After all: 
Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 12 

** 2797 Propagate node: (Concat (AutomataDef def) w)
 parents_filtered 





=================================================================================
** cb_new_eq(): @0
w  = (NonDet_AutomataDef |(abcabcabc)*| 1)


** @2702 checkLengthConsistency

>> checkLengthConsistency: Passed
< = > A B C D E F G H I J K L M N O P Q R S T U V W X Y a b c d e f g h i j k l m n o p q r s t u v w x y 
** @3406 Cross Check and Update: w == (NonDet_AutomataDef |(abcabcabc)*| 1)

>> @3226 Eval Intersection size = 3
>> @3272 at Number of elements: 2 
(NonDet_AutomataDef |(abcabc)*| 0)
(NonDet_AutomataDef |(abcabcabc)*| 1)


>> @3034 Eval Node (isIndependence = false): @0 (NonDet_AutomataDef |(abcabc)*| 0)


>> @3094 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 3 4 5 6 7 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 7 

>> @3034 Eval Node (isIndependence = false): @0 (NonDet_AutomataDef |(abcabcabc)*| 1)
532 at ../src/regex.cpp: Create Automaton of: known


>> @3295 at __../src/StringTheory.cpp:Update interstion list = 2 -->  2


>> @3310  Element 0: 
 Automaton known:
States: 
0 1 3 4 5 6 7 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 7 

>> @3315  Element 1: 
 Automaton known:
States: 
0 1 3 4 5 6 7 8 9 10 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 10 

>> @3323 at __../src/StringTheory.cpp: Result intersection: Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 18  @3415 at After all: 
Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 18 

>> @2876 update Equal Map
(NonDet_AutomataDef |(abcabcabc)*| 1)
w
(NonDet_AutomataDef |(abcabc)*| 0)


** 2797 Propagate node: w
 parents_filtered 
(Concat (AutomataDef def) w)



>> @2919 at __../src/StringTheory.cpp: Update Node: @0 (Concat (AutomataDef def) w)

>> @3167 Eval Concat: (AutomataDef def) *concat* w

>> @3034 Eval Node (isIndependence = false): @0 (AutomataDef def)


>> @3094 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 3 4 
Labels: 
100 101 102 
Inits: 
0 
Accepts: 
4 

>> @3034 Eval Node (isIndependence = false): @0 w


>> @3094 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 18 

>> @3190 at __../src/StringTheory.cpp: Finish Concat
(Concat (AutomataDef def) w)
>> @2981 at __../src/StringTheory.cpp: updated Concat value
 Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 23 
@3444 at ../src/StringTheory.cpp Cross Check: (Concat (AutomataDef def) w)

>> @3226 Eval Intersection size = 1
>> @3272 at Number of elements: 1 
(Concat (AutomataDef def) w)


>> @3031 Eval Node (isIndependence = true): @0 (Concat (AutomataDef def) w)

>> @3167 Eval Concat: (AutomataDef def) *concat* w

>> @3034 Eval Node (isIndependence = false): @0 (AutomataDef def)


>> @3094 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 3 4 
Labels: 
100 101 102 
Inits: 
0 
Accepts: 
4 

>> @3034 Eval Node (isIndependence = false): @0 w


>> @3094 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 18 

>> @3190 at __../src/StringTheory.cpp: Finish Concat


>> @3295 at __../src/StringTheory.cpp:Update interstion list = 1 -->  1


>> @3310  Element 0: 
 Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 23 

>> @3323 at __../src/StringTheory.cpp: Result intersection: Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 23  @3453 at __../src/StringTheory.cpp: After all: 
Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 23 

** 2797 Propagate node: (Concat (AutomataDef def) w)
 parents_filtered 





=================================================================================
** cb_new_eq(): @0
w  = (Concat (AutomataDef abc) j)
(AutomataDef abc): length = 3 


** @2702 checkLengthConsistency

>> checkLengthConsistency: Passed
< = > A B C D E F G H I J K L M N O P Q R S T U V W X Y a b c d e f g h i j k l m n o p q r s t u v w x y 
** @3406 Cross Check and Update: w == (Concat (AutomataDef abc) j)

>> @3226 Eval Intersection size = 4
>> @3272 at Number of elements: 3 
(NonDet_AutomataDef |(abcabcabc)*| 1)
(NonDet_AutomataDef |(abcabc)*| 0)
(Concat (AutomataDef abc) j)


>> @3034 Eval Node (isIndependence = false): @0 (NonDet_AutomataDef |(abcabcabc)*| 1)


>> @3094 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 18 

>> @3034 Eval Node (isIndependence = false): @0 (NonDet_AutomataDef |(abcabc)*| 0)


>> @3094 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 18 

>> @3034 Eval Node (isIndependence = false): @0 (Concat (AutomataDef abc) j)

>> @3167 Eval Concat: (AutomataDef abc) *concat* j

>> @3034 Eval Node (isIndependence = false): @0 (AutomataDef abc)
532 at ../src/regex.cpp: Create Automaton of: known

>> @3034 Eval Node (isIndependence = false): @0 j

>> @3226 Eval Intersection size = 1
>> @3272 at Number of elements: 0 


>> @3289 at __../src/StringTheory.cpp: UNKNOWN (0 elements)

>> @3045 Value of variable: @0: uNkNoWn 


>> @3295 at __../src/StringTheory.cpp:Update interstion list = 2 -->  1


>> @3310  Element 0: 
 Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 18 

>> @3323 at __../src/StringTheory.cpp: Result intersection: Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 18  @3415 at After all: 
Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 18 

>> @2876 update Equal Map
(Concat (AutomataDef abc) j)
(NonDet_AutomataDef |(abcabcabc)*| 1)
w
(NonDet_AutomataDef |(abcabc)*| 0)


** 2797 Propagate node: w
 parents_filtered 
(Concat (AutomataDef def) w)



>> @2919 at __../src/StringTheory.cpp: Update Node: @0 (Concat (AutomataDef def) w)

>> @3167 Eval Concat: (AutomataDef def) *concat* w

>> @3034 Eval Node (isIndependence = false): @0 (AutomataDef def)


>> @3094 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 3 4 
Labels: 
100 101 102 
Inits: 
0 
Accepts: 
4 

>> @3034 Eval Node (isIndependence = false): @0 w


>> @3094 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 18 

>> @3190 at __../src/StringTheory.cpp: Finish Concat
(Concat (AutomataDef def) w)
>> @2981 at __../src/StringTheory.cpp: updated Concat value
 Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 23 
@3444 at ../src/StringTheory.cpp Cross Check: (Concat (AutomataDef def) w)

>> @3226 Eval Intersection size = 1
>> @3272 at Number of elements: 1 
(Concat (AutomataDef def) w)


>> @3031 Eval Node (isIndependence = true): @0 (Concat (AutomataDef def) w)

>> @3167 Eval Concat: (AutomataDef def) *concat* w

>> @3034 Eval Node (isIndependence = false): @0 (AutomataDef def)


>> @3094 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 3 4 
Labels: 
100 101 102 
Inits: 
0 
Accepts: 
4 

>> @3034 Eval Node (isIndependence = false): @0 w


>> @3094 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
Labels: 
97 98 99 
Inits: 
0 
Accepts: 
0 18 

>> @3190 at __../src/StringTheory.cpp: Finish Concat


>> @3295 at __../src/StringTheory.cpp:Update interstion list = 1 -->  1


>> @3310  Element 0: 
 Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 23 

>> @3323 at __../src/StringTheory.cpp: Result intersection: Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 23  @3453 at __../src/StringTheory.cpp: After all: 
Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 23 

** 2797 Propagate node: (Concat (AutomataDef def) w)
 parents_filtered 





=================================================================================
** cb_new_eq(): @0
(Concat (AutomataDef def) w)  = g


** @2702 checkLengthConsistency

>> checkLengthConsistency: Passed
< = > A B C D E F G H I J K L M N O P Q R S T U V W X Y a b c d e f g h i j k l m n o p q r s t u v w x y 
** @3406 Cross Check and Update: (Concat (AutomataDef def) w) == g

>> @3226 Eval Intersection size = 2
>> @3272 at Number of elements: 1 
(Concat (AutomataDef def) w)


>> @3034 Eval Node (isIndependence = false): @0 (Concat (AutomataDef def) w)


>> @3094 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 23 


>> @3295 at __../src/StringTheory.cpp:Update interstion list = 1 -->  1


>> @3310  Element 0: 
 Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 23 

>> @3323 at __../src/StringTheory.cpp: Result intersection: Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 23  @3415 at After all: 
Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 23 

>> @2876 update Equal Map
g
(Concat (AutomataDef def) w)


** 2797 Propagate node: (Concat (AutomataDef def) w)
 parents_filtered 





=================================================================================
** cb_new_eq(): @0
g  = (Concat h i)


** @2702 checkLengthConsistency

>> checkLengthConsistency: Passed
< = > A B C D E F G H I J K L M N O P Q R S T U V W X Y a b c d e f g h i j k l m n o p q r s t u v w x y 
** @3406 Cross Check and Update: g == (Concat h i)

>> @3226 Eval Intersection size = 3
>> @3272 at Number of elements: 2 
(Concat (AutomataDef def) w)
(Concat h i)


>> @3034 Eval Node (isIndependence = false): @0 (Concat (AutomataDef def) w)


>> @3094 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 23 

>> @3034 Eval Node (isIndependence = false): @0 (Concat h i)

>> @3167 Eval Concat: h *concat* i

>> @3034 Eval Node (isIndependence = false): @0 h

>> @3226 Eval Intersection size = 1
>> @3272 at Number of elements: 0 


>> @3289 at __../src/StringTheory.cpp: UNKNOWN (0 elements)

>> @3045 Value of variable: @0: uNkNoWn 


>> @3295 at __../src/StringTheory.cpp:Update interstion list = 1 -->  1


>> @3310  Element 0: 
 Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 23 

>> @3323 at __../src/StringTheory.cpp: Result intersection: Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 23  @3415 at After all: 
Automaton known:
States: 
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 
Labels: 
0 97 98 99 100 101 102 
Inits: 
0 
Accepts: 
5 23 

>> @2876 update Equal Map
(Concat h i)
g
(Concat (AutomataDef def) w)


** 2797 Propagate node: g
 parents_filtered 




vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
                cb_final_check @ Level [0] 
=============================================================
Connected Variables

4037 "(abcabcabc)*" is a root.
4037 g is a root.
 parse regex 
abc
(abc)*

"(abcabcabc)*" =
	"abc" 	j 
	"(abcabc)*" 
	"(abcabcabc)*" 

g =
	"def" 	"(abcabcabc)*" 

"(abcabcabc)*" =
	"abc" 	j 
	"(abcabc)*__0" 
	"(abcabcabc)*__1" 

1215 Const map:
(abcabc)*__0: const_1
(abcabcabc)*__1: const_2
abc: const_0

1624 Max list size: 2
>> equalities to SMT 
abc.-1 abc.-2 j.0 j.1 = (abcabc)*__0.-100 
Number of flats: 4 flats = 1 flats

454 Calculating all possible cases: 0.000 seconds, 1 cases.
Checking case
  0   0   0   0 
100000000 
876Accepted
1 - 2 - -3 - 
------------
Accepted
2 - 1 - -3 - 
------------
Correct case
  0   0   0   0 
100000000 
479 (and 
 (= len_const_1_100 (+ len_const_0_1 len_const_0_2 len_j_0 len_j_1 ))  (and (= (+ len_const_0_1 len_const_0_2) 3) (= (mod (+ len_j_0 len_j_1 ) 6) 3) )
)
 print cases
(and 
 (= len_const_1_100 (+ len_const_0_1 len_const_0_2 len_j_0 len_j_1 ))  (and (= (+ len_const_0_1 len_const_0_2) 3) (= (mod (+ len_j_0 len_j_1 ) 6) 3) )
)

1683 Convert to SMT: 0.000 seconds.

>> equalities to SMT 
abc.-1 abc.-2 j.0 j.1 = (abcabcabc)*__1.-100 
Number of flats: 4 flats = 1 flats

454 Calculating all possible cases: 0.000 seconds, 1 cases.
Checking case
  0   0   0   0 
100000000 
876Accepted
1 - 2 - -6 - 
------------
Accepted
2 - 1 - -6 - 
------------
Correct case
  0   0   0   0 
100000000 
479 (and 
 (= len_const_2_100 (+ len_const_0_1 len_const_0_2 len_j_0 len_j_1 ))  (and (= (+ len_const_0_1 len_const_0_2) 3) (= (mod (+ len_j_0 len_j_1 ) 9) 6) )
)
 print cases
(and 
 (= len_const_2_100 (+ len_const_0_1 len_const_0_2 len_j_0 len_j_1 ))  (and (= (+ len_const_0_1 len_const_0_2) 3) (= (mod (+ len_j_0 len_j_1 ) 9) 6) )
)

1683 Convert to SMT: 0.000 seconds.

>> equalities to SMT 
(abcabc)*__0.-100 = (abcabcabc)*__1.-100 
Number of flats: 1 flats = 1 flats

454 Calculating all possible cases: 0.000 seconds, 1 cases.
Checking case
  0 
  0 
Correct case
  0 
  0 
479 (and 
(= len_const_1_100 len_const_2_100) (= (mod len_const_1_100 18) 0) 
)
 print cases
(and 
(= len_const_1_100 len_const_2_100) (= (mod len_const_1_100 18) 0) 
)

1683 Convert to SMT: 0.000 seconds.

1822 output with length: /tmp/fat_str_convert/w_l_nonsql.smt2

** Reset():

** Delete()
