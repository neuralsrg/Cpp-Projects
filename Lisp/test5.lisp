(setf print_a (lambda () (`a)))
(defun print_b () (`b))
(setf l (list (`print_a) (quote print_b) (quote something_rest)))
((eval (car l)))
((eval (second l)))
(rest (cdr l))
(cddr (cdr l))
(setf l1 (list (list 1 2 3) 4 5 6))
(cdar l1)
bye