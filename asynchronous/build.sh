echo -e "[\033[0;31mSTART\033[0m]"

gcc -g -c event_loop.c -o event_loop.o
gcc -g -c demo_app.c -o demo_app.o
gcc -g -c demo_app_mul_sum.c -o demo_app_mul_sum.o
gcc -g event_loop.o demo_app.o -o demo_app -lpthread
gcc -g event_loop.o demo_app_mul_sum.o -o demo_app_mul_sum -lpthread

echo -e "[\033[1;32mCOMPLETED\033[0m]"