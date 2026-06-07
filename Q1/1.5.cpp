#include<bits/stdc++.h>
#include<iostream>

//all strings are of type string other than line

using namespace std;

using Datatype = variant<int,vector<int>,string,float>;
using Attributes_DS = unordered_map<string,Datatype>;

class Operator;

class Tensor{
  
public:
  string name;
  vector <int> shape;
  string dtype;
  Operator *producer;
  vector <Operator*> consumers;
};

class Operator{

public:
  string name;
  vector <Tensor*> inputs;
  Tensor  *output;
  Attributes_DS attributes;
};

class Graph{
  
public:
  vector <Tensor*> input_tensors;
  vector <Tensor*> output_tensors;
  vector <Tensor*> tensors;

  vector <Operator*> operators;

  unordered_map<string,Tensor*> tensor_map;
  unordered_map<string,Operator*> operator_map;
};

void trimmer(char *line){

  char *ptr = line;
  while(*ptr != EOF && *ptr != '\n' ){
    ptr++;
  }
  *ptr = '\0';
}

int main(){
  
  FILE *ptr = fopen("input.txt","r");
  char line[1000];
  
  char *curr;

  //creating the graph and creating INPUTS
  Graph *graph = new Graph;

  fgets(line,sizeof(line),ptr);
  trimmer(line);
  curr = line;
  while(*curr!=':'){
    curr++;
  }
  curr = curr+2;
  
  Tensor *tensor = new Tensor;
  tensor->name = strtok(curr,",");
  tensor->producer = NULL;
  graph->input_tensors.push_back(tensor);
  graph->tensors.push_back(tensor);
  graph->tensor_map[tensor->name] = tensor;
  

  while(1){
    
    char *ptr = strtok(NULL,",");
    if(ptr==NULL){break;}

    tensor = new Tensor;
    tensor->name = ptr;
    tensor->producer = NULL;
    graph->input_tensors.push_back(tensor);
    graph->tensors.push_back(tensor);
    graph->tensor_map[tensor->name] = tensor;
  
  }

  //OUTPUTS
  //multiple outputs , solve it later
  fgets(line,sizeof(line),ptr);
  trimmer(line);
  strtok(line,": ");
  Tensor *ot = new Tensor;
  ot->name = strtok(NULL,": ");
  // wrong !! ot->consumers = NULL;
  //produce kisse ho rha hai baadme dekha jayega
  graph->output_tensors.push_back(ot);
  graph->tensors.push_back(ot);
  graph->tensor_map[ot->name] = ot;
  


  fgets(line,sizeof(line),ptr); // handling for the second line
  
  //solving rest of the lines.
  while(fgets(line,sizeof(line),ptr)!=NULL){
   
    //0. Tokenizing.
    trimmer(line);
    int args = 0;
    char *tokens[1000];
    tokens[0] = strtok(line,":(,) \t->");
    int i =1;
    while(1){
      tokens[i] = strtok(NULL,":(,) \t->");
      if(tokens[i]==NULL){break;}
      i++;
    }
    args = i;
    
    //1. Name of the node.
    Operator *node = new Operator;
    node->name = tokens[0];
    graph->operators.push_back(node);
    
    //2. Function
    node->attributes["function"] = tokens[1];
    
    //3. Inputs. Should be able to handle any number of inputs.

    int args_node = args - 3;
    for(int i =2 ; i<args_node+2;i++){
      //check whether it is there or not.
      char *tensor_name = tokens[i];
      auto it = graph->tensor_map.find(tensor_name);
      if(it!=graph->tensor_map.end()){
        
        //there
        it->second->consumers.push_back(node);
        node->inputs.push_back(it->second);
      }
      else{
        //not there
        Tensor *new_tensor = new Tensor;
        new_tensor->name = tokens[i];
        // going into an input but it is not an input so , It has a producer will be figured out later.
        new_tensor->consumers.push_back(node);
        node->inputs.push_back(new_tensor);
        graph->tensors.push_back(new_tensor);
        graph->tensor_map[tokens[i]]=new_tensor;
      }
    }
    
    //perfection.

    //4. Output
    //output can be created only once . So , It is not there in graph . We'll have to create it . but , if it is final output then , it is already created. so check whether final or not
    // checking whether final output or not.
    
    Tensor *flag = NULL;
    for(auto x : graph->output_tensors){

      if(x->name==tokens[args-1]){flag = x;break;}
    }
    if(flag!=NULL){

      //it is there
      flag->producer = node;
      node->output = flag;

    }
    else{

      //it is not there
      flag = new Tensor;
      node->output = flag;
      flag->producer = node;
      flag->name = tokens[args-1];
      graph->tensors.push_back(flag);
      graph->tensor_map[flag->name] = flag;
    }


  }

  //PRINTING.
  cout << "digraph v {" << endl;
  //printing based on tensors.
  for(auto x : graph->tensors){
    if(x->producer==NULL){
      //input tensors
      cout << "\t" << x->name  << "[shape = box, style = filled, fillcolor = lightgreen]"<<endl;
      for(auto y : x->consumers){
        cout << "\t" << x->name << "->" << y->name;
      }
    }
    else if(x->consumers.empty()){
      //output tensors
      cout << "\t" << x->name << "[shape = box, style = filled, fillcolor = red]" << endl;
      cout << "\t" << x->producer->name << "->" << x->name<< endl;
    }
    else {

      //central nodes.
      for(auto y : x->consumers){

        cout << "\t" << x->producer->name << "->" << y->name << "[label=" << "\""<<x->name << "\"]" << endl;
      }
    }
    
  }
  cout << "}" << endl;
  
  
}
