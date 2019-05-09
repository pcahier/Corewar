.name "zjmp"
.comment "test de la commande zjmp"

	st	r1, :live1+1
live1:	live %1
	zjmp %:live1
