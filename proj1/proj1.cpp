// Austin Sohn
// 10/15/22
// proj1.cpp

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

void output(vector<string> v){
  if(v.empty()){
    cout << "NONE\n";
  }
  else if(v.size() > 1){
    cout << "(";
    for(int i = 0; i < v.size(); i++){
      if(i == v.size() - 1){
        cout << v.at(i) << ")\n";
        break;
      }
      cout << v.at(i) << ", ";  
    }
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

vector<string> calculate(string in, vector<string> block){
  vector<string> ans;
  // remove whitespace and arithmetic operators
  
  for(int i = 0; i < block.size(); i++){
    if(checkParallel(rmOp(in), rmOp(block.at(i)))){
      ans.push_back(block.at(i));
    }
    
  }

  return ans;
}

vector<string> verify(vector<string> block){
  vector<string> ans;

  // remove whitespace and arithmetic operators
  for(int i = 0; i < block.size(); i++){
    for(int j = i+1; j < block.size()-1; j++){
      if(checkParallel(rmOp(block.at(i)), rmOp(block.at(j))) && i != j){
        ans.push_back(block.at(i));
        ans.push_back(block.at(j));
      }
    }
  }
  return ans;
}


int main(){
  string instruction = "d = b + ( c - d / e)";
  vector<string> block;
  string input;
  int MAX_INSTRUCTIONS = 11;

  cout << "Enter block of < 11 instructions:\n";


  // adds each line into a vector
  while(getline(cin, input)){
    if(!input.empty()){
      block.push_back(input);
    }
    else{
      break;
    }
  }

  if(block.size() >= MAX_INSTRUCTIONS){
    cout << "\nERROR: Block is too large\n";
    return 0;
  }
  cout << "--------------\n";;

  // calculate function
  // gets rid of whitespace and arithmetic operations
  vector<string> calc = calculate(instruction, block);
  cout << "CALCULATE:\n";
  cout << "The instruction that can be executed in parallel with d = b + ( c – d / e) is:\n";
  output(calc);
  cout << "--------------\n";

  // verify function
  vector<string> ver = verify(block);
  cout << "VERIFY:\n";
  cout << "The instruction(s) that can be executed in parallel are:\n";
  output(ver);
  cout << "--------------\n";
  return 0;
}