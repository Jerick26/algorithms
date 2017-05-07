#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <cassert>

using std::string;

char* last(char* s) {
  while (*s != '\0') {
	s++;
  }
  return --s;
}

void swap(char* a, char* b) {
  char t = *a;
  *a = *b;
  *b = t;
}

void reverse_str(char* s) {
  char* l = last(s);
  while (std::distance(s, l) > 0) {
	swap(s++, l--);
  }
}

void reverse_str(char* s, char* p) {
  while (std::distance(s, p) > 0) {
    swap(s++, p--);
  }
}

char* begin_word(char* s) {
  while (*s == ' ' || *s == '\t' || *s == '\n') {
	s++;
  }
  return s;
}

char* end_word(char* s) {
  while (*s == ' ' || *s == '\t') {
	s++;
  }
  while (*s != ' ' && *s != '\0' && *s != '\t' && *s != '\n') {
	s++;
  }
  return --s;
}

void reverse_sentense(char* s) {
  reverse_str(s);
  while (*s != '\0') {
	s = begin_word(s);
	if (*s == '\0')
	  return;
    char* w_e = end_word(s);
    reverse_str(s, w_e);
	s = ++w_e;
  }
}

int main(int argc, char* arg[])
{
//  std::cout << "hello, please enter your name..." << std::endl;
//  string name;
//  std::cin >> std::ws;
//  std::getline(std::cin, name);
  std::cout << "Hello, nice to meet you!" << std::endl;
  while (1) {
    std::cout << "hello, please enter you words..." << std::endl;
    string line;
    std::getline(std::cin, line, '\n');
    std::cout << "you have enter:\n" << line << std::endl;
	if (line.compare("quit") == 0)
		return 1;
    char* s = const_cast<char*>(line.c_str());
    //std::cout << "begin reverse ... " << std::endl;
    reverse_sentense(s);
    std::cout << "the reverse is:\n" << s << std::endl;
  }
  
  return 0;
}
