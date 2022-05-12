(if (/= 0.1 -0.1) (`true) (`false))
(cond (#f (`first1) (`first2)) ((< 1 2 3 0) (`second1) (`second2)) (#t (`third1) (`third2) (`third3)))
(if nil (`nil_is_true) (`nil_is_false))
bye
