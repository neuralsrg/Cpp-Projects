(setf x (list (`hello) (`world)))
(setf some_expr1 (list (quote car) (quote x)))
(setf some_expr2 (list (quote cadr) (`x)))
(eval some_expr1)
(eval some_expr2)
(eval who_am_i)
bye
