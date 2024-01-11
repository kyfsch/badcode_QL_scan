
'''
src https://stackoverflow.com/questions/55078713/extract-function-code-from-c-sourcecode-file-with-python
'''

import subprocess
import glob
import os


def get_line_number(filename, funcname):
    print("GETTING LINE NUMBERS")
    start_lines = [] #a list of the line number every identified function starts on
    found = False
    cmd = "ctags -x --c-kinds=fp " + filename #+ " | grep " + funcname what if we don't grep func name

    output = subprocess.getoutput(cmd)
    print(output)
    lines = output.splitlines()

    #We just want to return the line number for every function, hack out the name matching
    for line in lines:
        '''
        if line.startswith(funcname + " "):    
            found = True
        '''
        if output.strip() != "":
            output = output.split(" ")
            lines = list(filter(None, output))
            line_num = lines[2]

            print("Function found in file " + filename + " on line: " + line_num)

            #return a list of line numbers instead of a single match
            start_lines.append(int(line_num))

        return start_lines


def process_file(filename, line_num):
    print("opening " + filename + " on line " + str(line_num))

    code = ""
    cnt_braket = 0
    found_start = False
    found_end = False

    with open(filename, "r") as f:
        for i, line in enumerate(f):
            if(i >= (line_num - 1)):
                code += line

                if line.count("{") > 0:
                    found_start = True
                    cnt_braket += line.count("{")

                if line.count("}") > 0:
                    cnt_braket -= line.count("}")

                if cnt_braket == 0 and found_start == True:
                    found_end = True
                    return code


#un-hardcode this later
folder = "/home/kali/Documents/LLMs/openwrt-main" #looks like this code already can grab every c file in a directory. Amazing.
funcname = "add_alias" #expects a specific function name, which means we need to enumerate names from ctags as well

print("CODE RUNNING")
print(folder)
c_files = []

for root, dirs, files in os.walk(folder, topdown=False):
    for name in files:
        if name.endswith(".c"):
            c_files.append(os.path.join(root, name))
            #we need the entire path for the linenums function though
#helps if you get the right filename

for filename in c_files:
    print(filename)
    line_nums = get_line_number(filename, funcname)
    #it's only returning the first result - why?
    print(line_nums)
    for num in line_nums:
        print(process_file(filename, num))