(defun gps-line ()
  (interactive)
  (let ((start (point-min))
	(n (line-number-at-pos))
	(numlines (how-many "\n" (point-min) (point-max))))
    (if (= start 1)
	(message "Line %d/%d" n numlines)
      (save-excursion
	(save-restriction
	  (widen)
	  (message "line %d (narrowed line %d)"
		   (+ n (line-number-at-pos start) -1) n))))))
