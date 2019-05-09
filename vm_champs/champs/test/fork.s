.name "fork"
.comment "test de la commande fork"

fork	%:l1
ld		%106,r2
aff		r2 # Print j

l1:
	ld		%65,r2
	aff		r2 # Print A
