#define BACKWARD_HAS_DW  1
#include "backward.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace backward;

void d(StackTrace &st) { st.load_here(); }

void c(StackTrace &st) { return d(st); }

void b(StackTrace &st) { return c(st); }

NOINLINE void a(StackTrace &st) { return b(st); }

int main() {
  Printer printer;

  StackTrace st;
  a(st);

  printer.print(st, std::cout);
}
