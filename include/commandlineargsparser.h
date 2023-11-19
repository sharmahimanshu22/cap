#include <iostream>
#include <stdexcept>
#include <map>
#include <sstream>

using namespace std;
/**
 * Utility for parsing command line arguments
 */
struct CommandLineArgsParser
{


  std::map<std::string, std::string> args;


  CommandLineArgsParser(int argc, char** argv) {
    
    int i = 1;
    
    while(i < argc) {
      string arg = argv[i];
      string::size_type pos;

      if ((arg[0] == '-') && (arg[1] == '-')) {   // A valid key value input should always be handled inside this
	pos = arg.find('=');
	if((pos == string::npos) || (pos == arg.length() - 1)) {   // 'arg' is key only
	  if(pos == arg.length() - 1) {
	    arg = string(arg, 2, pos - 2);
	  } else {
	    arg = string(arg, 2);
	  }
	  if(arg.length() == 0) {
	    throw std::invalid_argument("Parameter name is not specified");
	  }

	  i = i+1;
	  if (i >= argc) {
	    throw std::invalid_argument("The last parameter has no value specified");
	  }
	  // We have a valid key

	  string val = argv[i];
	  if (val.compare("=") == 0) {  // this token is equalto sign. The next token should be the real value
	    i = i+1;
	    val = argv[i];
	  }
	  
	  if(val[0] == '=' && val.length() > 1) {
	    val = string(val, 1);
	  }

	  if (val[0] == '-' && val[1] == '-') {
	    throw std::invalid_argument(" One of the parameter has a missing value");
	  }

	  
	  args[arg] = val;
	  i = i+1;
	} 
        else {
	  string key = string(arg, 2, pos - 2);
	  string val = string(arg, pos + 1, arg.length() - 1); // do  qc on key and val
	  args[key] = val;
	  i = i+1;
	}

      } else {
	throw std::invalid_argument("Invalid parameter name. Parameter name should be preceded by two hiphens.");
      }
    }

  }



  // TODO: Is it safe to instantiate a template type ? What are possible issues ?
  template<typename T>
  T getCommandLineArg(const char* arg_name) {
    T val;
    if(args.find(string(arg_name)) != args.end()) {
      std::istringstream valstream(args[string(arg_name)]);
      valstream >> val;
      return val;
    }
    return NULL;
  }

  // TODO: Write a method to accept comma separated values (ie vectors) and return it as a vector

  void printAllArgs() const {
    std::map<std::string, std::string>::const_iterator it = args.begin(); 
  
    while (it != args.end()) { 
      std::string word = it->first; 
      std::string count = it->second; 
      std::cout << word << " :: " << count << std::endl; 
      it++; 
    } 
  }

};






