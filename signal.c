
#include <signal.h>
#include <setjmp.h>

jmp_buf jb;

static void sighandler(int x)
{
     longjmp(jb, 1);
}

static void (*oldsig)(int);

void installillhandler(void) {
  oldsig = signal(SIGILL, sighandler);
}
