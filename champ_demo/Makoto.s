.name		"Makoto"
.comment	"Wait... Useless ?"

initiate:
	ld %1, r2
	zjmp %:liveloop
	st r3, -8
	fork %:prep
	st r1, 6
liveloop:
	live %6
	ld %0, r2
	zjmp %:liveloop
prep:
	ld %0, r2
	ld %0, r3
	ld %0, r4
	ld %0, r5
	ld %0, r6
	ld %0, r7
	ld %880, r8
	ld %218230531, r9
	ld %1879966190, r10
	ld %57675521, r11
	ld %3976265743, r12
	ld %1111425680, r13
	ld %0, r14
	ld %34144672, r15
	st r1, 507
	st r2, 506
	st r3, 505
	st r4, 504
	st r5, 503
	st r6, 502
	st r7, 501
	st r8, 500
	st r9, 499
	st r10, 498
	st r11, 497
	st r12, 496
	st r13, 495
	st r14, 494
	st r15, 493
	live %999999
	ld %0, r2
	zjmp %416
