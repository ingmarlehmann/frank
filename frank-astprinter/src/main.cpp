#include <iostream>
#include <vector>
#include <cstring>

#include "ast/ast_node_list.h"
#include "ast/enum_decl.h"
#include "ast/identifier.h"
#include "ast/int_constant.h"
#include "ast/root.h"
#include "parser.h"

#include "ast_print_visitor.h"

void print_usage(const std::string& program_name)
{
    std::cout << "usage: " << program_name << " <file> [--debug]" << "\n";
}

int main(int argc, char** argv)
{
  if (argc < 2)
  {
    std::string program_name(argv[0]);
    std::cerr << "ERROR: no input file specified." << "\n";
    print_usage(program_name);

    return -1;
  }

  bool debug = false;
  if(argc > 2)
  {
    std::cout << "DEBUG: enabled" << "\n";
    debug = (strcmp(argv[2], "--debug") == 0);   
  }

  std::string filename(argv[1]);

  fparser::FidlParser parser;
  fparser::ParserStatus status = parser.parse(filename, debug);
  if(fparser::ParserStatus::SUCCESS != status)
  {
      std::cout << "Failed to parse file '" << filename << "'" << "\n";
      return -1;
  }

  fparser::ast::Root* root_node = parser.root();

  if (root_node != nullptr)
  {
    ASTPrintVisitor ast_print_visitor(2, ' ');
    root_node->accept(ast_print_visitor);
  }

  return 0;
}
