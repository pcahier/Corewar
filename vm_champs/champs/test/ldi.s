.name "ldi"
.comment "test de la commande ldi"

ld	%1, r15
ld	%1, r14
ld	%18, r13
ldi   r15, r14, r13
st	r13, 5
