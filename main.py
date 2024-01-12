
'''
src https://stackoverflow.com/questions/55078713/extract-function-code-from-c-sourcecode-file-with-python
'''

import subprocess
import glob
import os


def get_line_number(filename, funcname):
    #print("GETTING LINE NUMBERS")
    start_lines = {} #a dict keyed on the line number every identified function starts on, correlated with the function name
    found = False
    cmd = "ctags -x --c-kinds=fp " + filename #+ " | grep " + funcname what if we don't grep func name

    output = subprocess.getoutput(cmd)
    lines = output.splitlines()


    #We just want to return the line number for every function, hack out the name matching
    for line in lines:
        '''
        if line.startswith(funcname + " "):    
            found = True
        '''
        if line.strip() != "":
            line = line.split()
            line_num = line[2]

            #print("Function found in file " + filename + " on line: " + line_num)

            #return a list of line numbers instead of a single match
            start_lines[(int(line_num))] = line[0]

    return start_lines


def process_file(filename, line_num):
    #print("opening " + filename + " on line " + str(line_num))

    code = ""
    cnt_braket = 0
    found_start = False
    found_end = False

    with open(filename, "r", encoding="utf8", errors='ignore') as f:
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


def write_extracted_function(name, path, func_body):
    filename = path + '/' + name + ".txt"
    with open(filename, "w") as f:
        f.write(func_body)

#un-hardcode this later
folder = "/home/kali/Documents/LLMs/openwrt-main" 
funcname = "function"

folder_for_storing_functions = "/home/kali/Documents/LLMs/badcode/extracted_functions"

print(folder)
c_files = []
func_count = 0
file_count = 0

for root, dirs, files in os.walk(folder, topdown=False):
    for name in files:
        if name.endswith(".c"):
            c_files.append(os.path.join(root, name))
            #we need the entire path for the linenums function though
#helps if you get the right filename

for filename in c_files:
    line_nums = get_line_number(filename, funcname)
    for num in line_nums.keys():
        func_body = process_file(filename, num)
        if func_body != None:
            write_extracted_function(line_nums[num], folder_for_storing_functions, func_body)
            func_count += 1
    file_count += 1

print("Total functions processed: ", func_count)
print("Files processed: ",file_count)