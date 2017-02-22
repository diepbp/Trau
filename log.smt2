***********************************************
*                 initGrammar                 *
-----------------------------------------------
Input
$OREXPRESSION = $COMPARAISON | $COMPARAISON $OROP $COMPARAISON 

$ANDEXPRESSION = $COMPARAISON | $OREXPRESSION | $NOTOP $ANDEXPRESSION

$COMPARAISON = $TERM $COMPOP $TERM 

$COMPOP = > | = | < 

$OROP =  or  

$NOTOP =  not  

$TERM = $NUMBER | $STRING | $QUOTE $TERM $QUOTE 

$NUMBER = [0-9]+ 

$STRING = [a-z]+ 

$QUOTE = " 


nonterminal
$ANDEXPRESSION
$COMPARAISON
$COMPOP
$NOTOP
$NUMBER
$OREXPRESSION
$OROP
$QUOTE
$STRING
$TERM

>> 
$COMPARAISON

>> 
$COMPARAISON $OROP $COMPARAISON

>> 
$COMPARAISON

>> 
$OREXPRESSION

>> 
$NOTOP
$ANDEXPRESSION

>> 
$TERM $COMPOP $TERM

>> 
>

>> 
=

>> 
<

>> 
 or 

>> 
 not 

>> 
$NUMBER

>> 
$STRING

>> 
$QUOTE
$TERM
$QUOTE

>> 
[0-9]+

>> 
[a-z]+

>> 
"

165 $ANDEXPRESSION: (( not ))*(((("))*([0-9]+)~((("))*([a-z]+))(("))*) ((>)~(=)~(<)) ((("))*([0-9]+)~((("))*([a-z]+))(("))*))~((( not ))*(((((("))*([0-9]+)~((("))*([a-z]+))(("))*) ((>)~(=)~(<)) ((("))*([0-9]+)~((("))*([a-z]+))(("))*)))~((((("))*([0-9]+)~((("))*([a-z]+))(("))*) ((>)~(=)~(<)) ((("))*([0-9]+)~((("))*([a-z]+))(("))*)) ( or ) (((("))*([0-9]+)~((("))*([a-z]+))(("))*) ((>)~(=)~(<)) ((("))*([0-9]+)~((("))*([a-z]+))(("))*)))))
165 $COMPARAISON: ((("))*([0-9]+)~((("))*([a-z]+))(("))*) ((>)~(=)~(<)) ((("))*([0-9]+)~((("))*([a-z]+))(("))*)
165 $COMPOP: (>)~(=)~(<)
165 $NOTOP:  not 
165 $NUMBER: [0-9]+
165 $OREXPRESSION: ((((("))*([0-9]+)~((("))*([a-z]+))(("))*) ((>)~(=)~(<)) ((("))*([0-9]+)~((("))*([a-z]+))(("))*)))~((((("))*([0-9]+)~((("))*([a-z]+))(("))*) ((>)~(=)~(<)) ((("))*([0-9]+)~((("))*([a-z]+))(("))*)) ( or ) (((("))*([0-9]+)~((("))*([a-z]+))(("))*) ((>)~(=)~(<)) ((("))*([0-9]+)~((("))*([a-z]+))(("))*)))
165 $OROP:  or 
165 $QUOTE: "
165 $STRING: [a-z]+
165 $TERM: (("))*([0-9]+)~((("))*([a-z]+))(("))*
Input file: nonsql.smt2

Grammar file: -model

262 creating /tmp/fat_str_convert/: OK
***********************************************
*              initGraph             *
-----------------------------------------------
 g, h, i,
(assert (= g (Concat h i)))

 w, j, g,
(assert (= w (Concat j g)))

 w,
(assert (= w "teest"))

 h,
(assert (= h "ee"))
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
g
h
i
w
j

***********************************************
Input loaded:
-----------------------------------------------
(and (= g (Concat h i))
     (= w (Concat j g))
     (= w __cOnStStR__x74_x65_x65_x73_x74)
     (= h __cOnStStR__x65_x65))
-----------------------------------------------


>> cb_reduce_app(): Concat(h, i)
>> cb_reduce_app(): Concat(h, i)
False update 
---------------------
Assertion Add(@1471, Level 0):
(and (>= (Length h) 0)
     (>= (Length i) 0)
     (>= (Length (Concat h i)) 0)
     (= (Length (Concat h i)) (+ (Length h) (Length i))))
---------------------


convert to: (Concat h i)


>> cb_reduce_eq: g = (Concat h i)


 converted to : (and (>= (Length g) 0) (= g (Concat h i)))

>> cb_reduce_app(): Concat(j, g)
>> cb_reduce_app(): Concat(j, g)
False update 
---------------------
Assertion Add(@1471, Level 0):
(and (>= (Length j) 0)
     (>= (Length g) 0)
     (>= (Length (Concat j g)) 0)
     (= (Length (Concat j g)) (+ (Length j) (Length g))))
---------------------


convert to: (Concat j g)


>> cb_reduce_eq: w = (Concat j g)


 converted to : (and (>= (Length w) 0) (= w (Concat j g)))

>> cb_reduce_eq: w = __cOnStStR__x74_x65_x65_x73_x74

---------------------
Assertion Add(@1251, Level 0):
(= (Length (AutomataDef teest)) 5)
---------------------


 converted to : (and (>= (Length w) 0)
     (>= (Length __cOnStStR__x74_x65_x65_x73_x74) 0)
     (=> (= w (AutomataDef teest)) (= (Length w) 5))
     (= w (AutomataDef teest)))

>> cb_reduce_eq: h = __cOnStStR__x65_x65

---------------------
Assertion Add(@1251, Level 0):
(= (Length (AutomataDef ee)) 2)
---------------------


 converted to : (and (>= (Length h) 0)
     (>= (Length __cOnStStR__x65_x65) 0)
     (=> (= h (AutomataDef ee)) (= (Length h) 2))
     (= h (AutomataDef ee)))

>> cb_reduce_app(): Concat(h, i)
False update 

>> cb_reduce_app(): Concat(j, g)
False update 

>> cb_reduce_eq: g = (Concat h i)


>> cb_reduce_eq: w = (Concat j g)


>> cb_reduce_app(): Length( "teest" ) = 5


>> cb_reduce_eq: w = (AutomataDef teest)


>> cb_reduce_app(): Length( "ee" ) = 2


>> cb_reduce_eq: h = (AutomataDef ee)


>> cb_reduce_app(): Concat(h, i)
False update 

>> cb_reduce_app(): Concat(j, g)
False update 

>> cb_reduce_eq: g = (Concat h i)


>> cb_reduce_eq: w = (Concat j g)


>> cb_reduce_eq: w = (AutomataDef teest)


>> cb_reduce_eq: h = (AutomataDef ee)


>> cb_reduce_app(): Concat(h, i)
False update 

>> cb_reduce_app(): Concat(j, g)
False update 

>> cb_reduce_eq: g = (Concat h i)


>> cb_reduce_eq: w = (Concat j g)


>> cb_reduce_eq: w = (AutomataDef teest)


>> cb_reduce_eq: h = (AutomataDef ee)



Var In Length = {}
***********************************************
*               Starting Search               *
-----------------------------------------------
(let ((a!1 (+ (Length h) (Length i) (* (- 1) (Length (Concat h i)))))
      (a!2 (+ (Length g) (Length j) (* (- 1) (Length (Concat j g))))))
  (and (= a!1 0)
       (= a!2 0)
       (= (Length (AutomataDef teest)) 5)
       (= (Length (AutomataDef ee)) 2)
       (>= (Length h) 0)
       (>= (Length i) 0)
       (>= (Length (Concat h i)) 0)
       (>= (Length j) 0)
       (>= (Length g) 0)
       (>= (Length (Concat j g)) 0)
       (= g (Concat h i))
       (= w (Concat j g))
       (>= (Length w) 0)
       (= w (AutomataDef teest))
       (= h (AutomataDef ee))))




=================================================================================
** cb_new_eq(): @0
(Concat h i)  = g


** @2736 checkLengthConsistency

>> checkLengthConsistency: Passed
< = > A B C D E F G H I J K L M N O P Q R S T U V W X Y a b c d e f g h i j k l m n o p q r s t u v w x y 
** @3445 Cross Check and Update: (Concat h i) == g

>> @3265 Eval Intersection size = 2
>> @3311 at Number of elements: 1 
(Concat h i)


>> @3071 Eval Node (isIndependence = false): @0 (Concat h i)

>> @3206 Eval Concat: h *concat* i

>> @3071 Eval Node (isIndependence = false): @0 h

>> @3265 Eval Intersection size = 1
>> @3311 at Number of elements: 0 


>> @3328 at __../src/StringTheory.cpp: UNKNOWN (0 elements)

>> @3082 Value of variable: @0: uNkNoWn 

>> @3328 at __../src/StringTheory.cpp: UNKNOWN (1 elements)
@3454 at After all: 
uNkNoWn

>> @2910 update Equal Map
g
(Concat h i)


** 2831 Propagate node: (Concat h i)
 parents_filtered 
(Concat j g)



>> @2953 at __../src/StringTheory.cpp: Update Node: @0 (Concat j g)

>> @3206 Eval Concat: j *concat* g

>> @3071 Eval Node (isIndependence = false): @0 j

>> @3265 Eval Intersection size = 1
>> @3311 at Number of elements: 0 


>> @3328 at __../src/StringTheory.cpp: UNKNOWN (0 elements)

>> @3082 Value of variable: @0: uNkNoWn 
(Concat j g)
>> @3015 at __../src/StringTheory.cpp: updated Concat value
 uNkNoWn




=================================================================================
** cb_new_eq(): @0
(Concat j g)  = w
w: length = 5 


** @2736 checkLengthConsistency

>> checkLengthConsistency: Passed
< = > A B C D E F G H I J K L M N O P Q R S T U V W X Y a b c d e f g h i j k l m n o p q r s t u v w x y 
** @3445 Cross Check and Update: (Concat j g) == w

>> @3265 Eval Intersection size = 2
>> @3311 at Number of elements: 1 
(Concat j g)


>> @3071 Eval Node (isIndependence = false): @0 (Concat j g)

>> @3206 Eval Concat: j *concat* g

>> @3071 Eval Node (isIndependence = false): @0 j

>> @3265 Eval Intersection size = 1
>> @3311 at Number of elements: 0 


>> @3328 at __../src/StringTheory.cpp: UNKNOWN (0 elements)

>> @3082 Value of variable: @0: uNkNoWn 

>> @3328 at __../src/StringTheory.cpp: UNKNOWN (1 elements)
@3454 at After all: 
uNkNoWn

>> @2910 update Equal Map
w
(Concat j g)


** 2831 Propagate node: (Concat j g)
 parents_filtered 





=================================================================================
** cb_new_eq(): @0
w  = (AutomataDef teest)
w: length = 5 
(AutomataDef teest): length = 5 


** @2736 checkLengthConsistency

>> checkLengthConsistency: Passed
< = > A B C D E F G H I J K L M N O P Q R S T U V W X Y a b c d e f g h i j k l m n o p q r s t u v w x y 
** @3445 Cross Check and Update: w == (AutomataDef teest)

>> @3265 Eval Intersection size = 3
>> @3311 at Number of elements: 2 
(Concat j g)
(AutomataDef teest)


>> @3071 Eval Node (isIndependence = false): @0 (Concat j g)

>> @3206 Eval Concat: j *concat* g

>> @3071 Eval Node (isIndependence = false): @0 j

>> @3265 Eval Intersection size = 1
>> @3311 at Number of elements: 0 


>> @3328 at __../src/StringTheory.cpp: UNKNOWN (0 elements)

>> @3082 Value of variable: @0: uNkNoWn 

>> @3071 Eval Node (isIndependence = false): @0 (AutomataDef teest)
532 at ../src/regex.cpp: Create Automaton of: known


>> @3334 at __../src/StringTheory.cpp:Update interstion list = 1 -->  1


>> @3349  Element 0: 
 Automaton known:
States: 
0 2 3 4 5 6 
Labels: 
101 115 116 
Transitions: 
	0--(116)--2
	2--(101)--3
	3--(101)--4
	4--(115)--5
	5--(116)--6

Inits: 
0 
Accepts: 
6 

>> @3362 at __../src/StringTheory.cpp: Result intersection: Automaton known:
States: 
0 2 3 4 5 6 
Labels: 
101 115 116 
Inits: 
0 
Accepts: 
6  @3454 at After all: 
Automaton known:
States: 
0 2 3 4 5 6 
Labels: 
101 115 116 
Inits: 
0 
Accepts: 
6 

>> @2910 update Equal Map
(AutomataDef teest)
w
(Concat j g)


** 2831 Propagate node: w
 parents_filtered 





=================================================================================
** cb_new_eq(): @0
(AutomataDef ee)  = h
h: length = 2 


** @2736 checkLengthConsistency

>> checkLengthConsistency: Passed
< = > A B C D E F G H I J K L M N O P Q R S T U V W X Y a b c d e f g h i j k l m n o p q r s t u v w x y 
** @3445 Cross Check and Update: (AutomataDef ee) == h

>> @3265 Eval Intersection size = 2
>> @3311 at Number of elements: 1 
(AutomataDef ee)


>> @3071 Eval Node (isIndependence = false): @0 (AutomataDef ee)
532 at ../src/regex.cpp: Create Automaton of: known


>> @3334 at __../src/StringTheory.cpp:Update interstion list = 1 -->  1


>> @3349  Element 0: 
 Automaton known:
States: 
0 1 2 
Labels: 
101 
Transitions: 
	0--(101)--1
	1--(101)--2

Inits: 
0 
Accepts: 
2 

>> @3362 at __../src/StringTheory.cpp: Result intersection: Automaton known:
States: 
0 1 2 
Labels: 
101 
Inits: 
0 
Accepts: 
2  @3454 at After all: 
Automaton known:
States: 
0 1 2 
Labels: 
101 
Inits: 
0 
Accepts: 
2 

>> @2910 update Equal Map
h
(AutomataDef ee)


** 2831 Propagate node: (AutomataDef ee)
 parents_filtered 
(Concat h i)



>> @2953 at __../src/StringTheory.cpp: Update Node: @0 (Concat h i)

>> @3206 Eval Concat: h *concat* i

>> @3071 Eval Node (isIndependence = false): @0 h


>> @3133 at __../src/StringTheory.cpp:known node value Automaton known:
States: 
0 1 2 
Labels: 
101 
Inits: 
0 
Accepts: 
2 

>> @3071 Eval Node (isIndependence = false): @0 i

>> @3265 Eval Intersection size = 1
>> @3311 at Number of elements: 0 


>> @3328 at __../src/StringTheory.cpp: UNKNOWN (0 elements)

>> @3082 Value of variable: @0: uNkNoWn 
(Concat h i)
>> @3015 at __../src/StringTheory.cpp: updated Concat value
 uNkNoWn



vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
                cb_final_check @ Level [0] 
=============================================================
Connected Variables

4021 g = :
Start 

(AutomataDef ee)
i

4021 j = :
Start 

j

4021 w = :
Start 

(AutomataDef teest)


** Reset():

** Delete()
