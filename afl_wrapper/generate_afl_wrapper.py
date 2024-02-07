import pycparser
import sys

original_source = None
with open(sys.argv[1], 'r') as f:
    original_source = f.read()

class Func(object):
    pass

class Param(object):
    pass

funcs = []

class FunctionVisitor(pycparser.c_ast.NodeVisitor):
    def visit_FuncDef(self, node):
        func = Func()
        func.name = node.decl.name
        func.args = []
        
        for param in node.decl.type.args.params:
            p = Param()
            p.indirections = 0
            p.name = param.name
            p.type = param.type
            p.direct_type = p.type
            while type(p.direct_type) == pycparser.c_ast.PtrDecl:
                p.direct_type = p.direct_type.type
                p.indirections += 1
            p.direct_type = p.direct_type.type.names[0]
            p.type = p.direct_type + '*' * p.indirections
            func.args.append(p)

        funcs.append(func)       

ast = pycparser.parse_file(sys.argv[1], use_cpp=True)
v = FunctionVisitor()
v.visit(ast)

print("""
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
""")
print(original_source)
print("""

// BEGIN GENERATED MAIN FUNCTION
int main(int argc, char* argv[])
{
    """)

for i, func in enumerate(funcs):
    for j, arg in enumerate(func.args):
        arg_name = 'arg_f' + str(i) + 'p' + str(j)
        if arg.type == 'char*':
            print('    char ' + arg_name + '[1000];')
        else:
            print('    ' + arg.direct_type + ' ' + arg_name + ';')
        print('    char ' + arg_name + '_line[1000];')
        print('    fgets(' + arg_name + '_line, 990, stdin);')
        if arg.type == 'char*':
            print('    sscanf(' + arg_name + """_line, "%980s", """ + arg_name + ');')
        else:
            print('    sscanf(' + arg_name + """_line, "%i", &""" + arg_name + ');')
        print('    ')

print('    ')


for i, func in enumerate(funcs):
    print('    ' + func.name + '(', end='')
    for j, arg in enumerate(func.args):
        if j != 0:
            print(', ', end='')
        if arg.type != 'char*':
            for k in range(arg.indirections):
                print('&', end='')

        arg_name = 'arg_f' + str(i) + 'p' + str(j)
        print(arg_name, end='')
    print(');')

print('    return 0;')
print('}')

