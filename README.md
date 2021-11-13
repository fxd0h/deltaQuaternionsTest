llvm-gcc -I . cqrlib.c -c -o cqrlib.o

llvm-gcc -I . -L . -lcqrlib.o -g fx_quat_test.c -o fx_quat_test && ./fx_quat_tes
