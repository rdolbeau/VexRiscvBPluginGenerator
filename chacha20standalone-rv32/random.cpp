#include <random>
#include <functional>

std::default_random_engine generator;
std::uniform_int_distribution<unsigned char> distribution(0,255);
auto rbyte = std::bind ( distribution, generator );

extern "C" {
  void kernelrandombytes(unsigned char *x,unsigned long long xlen)
  {
    int i;

    while (xlen > 0) {
      *x = rbyte();
      x++;
      xlen--;
    }
  }
}
