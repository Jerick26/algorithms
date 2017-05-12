/******************************************************************************
 *  Compilation:  g++ -o squeeze main.cpp -std=c++0x -g
 *  Execution:    ./squeeze < input.txt
 *  Dependencies: std::in cout fstream
 *
 *  Takes a string command line argument and removes adjacent spaces.
 *
 *  $ more squeeze.data
 *  this is   a    test   
 *  Hello     world  !  
 *  Hello world !
 *
 *  $ ./queeze < squeeze.data
 *  this is a test
 *
 ******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>

using std::string;

void squeeze(string* s) {
  auto d_it = s->begin() + 1;
  for (auto s_it=s->begin()+1; s_it!=s->end(); ++s_it) {
    *d_it = *s_it;
    if (*d_it != '\n') {
      if (*d_it != ' ')
        ++d_it;
      else if (*(d_it-1) != ' ')
        ++d_it;
    } else {
      if (*(d_it-1) == ' ') {
        *(d_it-1) = *d_it;
      }
    }
  }
  s->resize(d_it - s->begin() + 1);
}

int main(int argc, char* argv[]) {
  if (argc < 1) {
    std::cout << "argument to main is insufficient!" << std::endl;
    return -1;
  }
  string s, p;
  while (std::getline(std::cin, p, '\n')) {
    s.append(p).append("\n");
  }
  std::cout << "the origin string is:\n" << s << std::endl;
  squeeze(&s);
  std::cout << "after squeeze, the string is:\n" << s << std::endl;
  std::ofstream out("result.txt");
  out << s;
  out.close();

  return 0;
}
