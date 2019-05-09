.name        "Bomb_platform"
.comment    "This doesn't work"

	fork %:brain
	st r1, 6
loop:
	live %6
	ld %0, r2
	zjmp %:loop
brain:
	ld %100, r5
	ld %9, r4
bomb:
	live %6
	add r5, r4, r5
	sti r5, r5, %50
	sti r5, r5, %2200
	and r1, %0, r1
	zjmp %:bomb
