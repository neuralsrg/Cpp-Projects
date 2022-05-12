(setf lambda_func (lambda (p1 p2) (= p1 p2)))
(defun func (x y z) (* x y z))
(setf lst (list -0.1 -0.01 -0.01))
(lambda_func (first lst) (second lst))
(func (first lst) (first lst))
(func (first lst) (second lst) (third lst))
(lambda_func nil (caar lst))
bye
