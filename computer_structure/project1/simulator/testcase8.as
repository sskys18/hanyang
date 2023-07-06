 lw 0 1 one
 lw 0 2 two
 lw 0 3 three
 lw 0 4 done
 nor 1 0 5
 nor 2 0 6
 add 5 6 7
 sw 0 5 11
 sw 0 6 12
 sw 0 7 13
 jalr 4 1
 noop
done halt
one .fill 1
two .fill 2
three .fill 3
ten .fill 10
neg1 .fill -1
