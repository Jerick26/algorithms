/*
 * Dijkstra's Two-Stack Algorithm for Expression Evaluation
 * Compilation: g++ -o evaluate evaluate.cpp -std=c++0x -g
 * Dependencies:
 * Execution: ./evaluate
 * ( ( 2 + ( ( 3 * 4 ) * 5 ) ) + ( 6 * sqrt ( 4 ) ) )
 * output:
 *   the result is: 74
 */
#include <stack>
#include <string>
#include <cmath>
#include <iostream>
#include <sstream>

using std::string;

int main(int argc, char* argv[]) {
  std::stack<string> ops;
  std::stack<double> vals;
  string expr;
  std::getline(std::cin, expr);
  std::istringstream iss(expr);
  while (iss.good()) {
    string elm;
    iss >> elm;
    if      (elm == "(")     ;
    else if (elm == "+")     ops.push(elm);
    else if (elm == "-")     ops.push(elm);
    else if (elm == "*")     ops.push(elm);
    else if (elm == "/")     ops.push(elm);
    else if (elm == "sqrt")  ops.push(elm);
    else if (elm == ")") {
      // pop, evaluate and push result if value is ")"
      string op = ops.top();
      double v = vals.top();
      ops.pop();
      vals.pop();
      if      (op == "+")    { v = vals.top() + v; vals.pop(); }
      else if (op == "-")    { v = vals.top() - v; vals.pop(); }
      else if (op == "*")    { v = vals.top() * v; vals.pop(); }
      else if (op == "/")    { v = vals.top() / v; vals.pop(); }
      else if (op == "sqrt") v = std::sqrt(v);
      vals.push(v);
    }  // Tlken is not operator or parenthesis, push double value
    else    vals.push(stod(elm));
  }
  std::cout << "the result is: " << vals.top() << std::endl;
}
