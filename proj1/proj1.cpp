// Austin Sohn
// 10/15/22
// proj1.cpp

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

void output(vector<string> v){
  if(v.size() == 2){
    cout << "(" << v.at(0) << ", " << v.at(1) << ")\n";
  }
  else{
    cout << v.at(0) << endl;
  }
}

string rmOp(string s){
  vector<char> op = {'+', '-', '*', '/', '=', '(', ')' ,' '};

  for(int i = 0; i < op.size(); i++){
    s.erase(remove(s.begin(), s.end(), op.at(i)), s.end());
  }
  return s;
}

bool checkParallel(string s1, string s2){
  char out1 = s1.at(0);
  char out2 = s2.at(0);
  string in1 = s1.substr(1, s1.size());
  string in2 = s2.substr(1, s2.size());
  bool b = true;

  if(in1.find(out2) != string::npos){ // anti dependency
    b = false;
  }
  if(in2.find(out1) != string::npos){ // flow dependency
    b = false;
  }
  if(out1 == out2){ // output dependency
    b = false;
  }
  return b;
};

string calculate(string in, vector<string> block){
  vector<string> v;
  string ans;
  // remove whitespace and arithmetic operators
  for(int i = 0; i < block.size(); i++){
    v.push_back(rmOp(block.at(i)));
  }

  bool b1 = checkParallel(v.at(0), in); // in || I1?
  bool b2 = checkParallel(v.at(1), in); // in || I2?
  bool b3 = checkParallel(v.at(2), in); // in || I3?
  
  if(b1 == false && b2 == false && b3 == false){
    ans = "NONE";
  }
  else if(b1 == true){ 
    ans = block.at(0);
  }
  else if(b2 == true){ 
    ans = block.at(1);
  }
  else if(b3 == true){
    ans = block.at(2);
  }
  return ans;
}

vector<string> verify(vector<string> block){
  vector<string> ans;
  vector<string> v;

  // remove whitespace and arithmetic operators
  for(int i = 0; i < block.size(); i++){
    v.push_back(rmOp(block.at(i)));
  }
  bool b1 = checkParallel(v.at(0), v.at(1)); // I1 || I2?
  bool b2 = checkParallel(v.at(0), v.at(2)); // I1 || I3?
  bool b3 = checkParallel(v.at(1), v.at(2)); // I2 || I3?
  
  if(b1 == false && b2 == false && b3 == false){
    ans.push_back("NONE");
  }
  else if(b1 == true){ 
    ans.push_back(block.at(0));
    ans.push_back(block.at(1));
  }
  else if(b2 == true){ 
    ans.push_back(block.at(0));
    ans.push_back(block.at(2));
  }
  else if(b3 == true){
    ans.push_back(block.at(1));
    ans.push_back(block.at(2));
  }
  
  return ans;
}


int main(){
  string instruction = "d = b + ( c - d / e)";
  vector<string> block;
  string input;

  cout << "Enter block of < 11 instructions:\n";
  int MAX_INSTRUCTIONS = 3;

  // adds each line into a vector
  for (int i = 0; i < MAX_INSTRUCTIONS; i++){
    getline(cin, input);
    block.push_back(input);
  }
  cout << endl;

  // calculate function
  // gets rid of whitespace and arithmetic operations
  instruction = rmOp(instruction);
  cout << "CALCULATE:\n";
  cout << "The instruction that can be executed in parallel with d = b + ( c – d / e) is:\n";
  cout << calculate(instruction, block) << endl << "--------------\n";

  // verify function
  block = verify(block);
  cout << "VERIFY:\n";
  cout << "The instruction(s) that can be executed in parallel are:\n";
  output(block);
  return 0;
}