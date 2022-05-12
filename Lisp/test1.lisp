(setf a (list 1 2 3 (list 4 5 6) (`last_item)))
(= (car a) (first a))
(/= (cdr a) (rest a))
(setf x (second a))
(setf y (third a))
(+ x y)
bye
