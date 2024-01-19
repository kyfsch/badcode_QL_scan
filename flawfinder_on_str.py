

import subprocess
import sys


#Usage: [your program that outputs a code string] | python3 flawfinder_on_str.py
def run_flawfinder(): 
  # pipes the given string into flawfinder using a temporary file and cleans up, STDIO output
  txt_in = sys.stdin.read()
  command = "tmppipe=$(mktemp /tmp/ff.XXXX); echo '{0}' > $tmppipe; flawfinder $tmppipe; rm $tmppipe".format(txt_in)
  result = subprocess.run(command,shell=True, capture_output=True, text=True)
  print(result.stdout)

def main():
    run_flawfinder()

main()