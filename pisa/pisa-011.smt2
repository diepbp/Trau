(declare-fun s () String)
(declare-fun f () String)
(declare-fun ret () String) 


(assert (= ret (Replace s "<" "&lt;") ) )

(assert (= f (Concat  "jquery.js"  "\"></script>" ) ) )

(assert (= s  (Concat "aaaa<script src=\"" f ) ) )

(check-sat)
(get-model)
