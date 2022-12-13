#!/usr/local/cs/bin/python3

from ast import arguments
import random, sys, string
from argparse import ArgumentParser

class randline:
  def __init__(self, filename):
    f = open(filename, 'r')
    self.lines = f.readlines()
    f.close()

def main():
  usage_msg = """shuf [OPTION]... [FILE]
  or:  shuf -e [OPTION]... [ARG]...
  or:  shuf -i LO-HI [OPTION]...
Write a random permutation of the input lines to standard output.

With no FILE, or when FILE is -, read standard input.

Mandatory arguments to long options are mandatory for short options too."""

  parser = ArgumentParser(usage=usage_msg)  #constructor

  parser.add_argument(  
    "-e",
    "--echo",
    action="store",
    nargs = '*',
    dest="echo",
    help="treat each ARG as an input line"
    )

  parser.add_argument(
    "-i",
    "--input-range",
    action="store",
    #nargs = 1,
    dest="input_range",
    help="treat each number LO through HI as an input line"
    )

  parser.add_argument(
    "-n",
    "--head-count", 
    action="store",
    #nargs = 1,
    type = int,
    dest="head_count",
    help="output at most COUNT lines"
    )

  parser.add_argument(
    "-r",
    "--repeat",
    default=False,
    action="store_true",
    dest="repeat",
    help="output lines can be repeated"
    )

  
  #args = parser.parse_args(sys.argv[1:])  #takes in the arguments and their values (default is used if not initialized)
  args, other_args = parser.parse_known_args(sys.argv[1:])
  #print(args)
  #print(other_args)

  hc_num = None 
  out_lines = []

  if args.echo and args.input_range:
    parser.error("cannot combine -e and -i options")
  
  if other_args and other_args[0] == "-h":
    parser.error("invalid option -- 'h' \n Try 'shuf --help' for more information.")

  #### ECHO #####
  if args.echo is not None:
    #print(args.echo)
    out_lines = args.echo
    if len(other_args) != 0:
      out_lines.extend(other_args)
    random.shuffle(out_lines)
    for x in out_lines:
      sys.stdout.write(str(x) + "\n")
    exit(0)

  #### HEAD COUNT ####
  try:
      if args.head_count is not None:
        hc_num = int(args.head_count)
        #print(hc_num)
  except:
    parser.error("invalid head count: {0}".format(args.head_count))

  if hc_num != None and hc_num < 0:
    parser.error("invalid line count: {0}".format(args.head_count))
  
    ### INPUT RANGE #####
  if args.input_range is not None:
    try:
      ir_val = str(args.input_range)
      split_str = ir_val.split("-")
      if len(split_str) != 2:
        raise Exception
      LO = int(split_str[0])
      HI = int(split_str[1])
      #print(split_str)
      #print(LO)
      #print(HI)
      if LO >= 0 and HI >= 0 and LO - HI <= 1:
        out_lines = list(range(LO, HI + 1))
      else:
        raise Exception
    except:
      parser.error("invalid input range: {0}".format(args.input_range))

  ### - ####
  if args.input_range is None:

    if len(other_args) == 0 or other_args[0] == "-":
      out_lines = sys.stdin.readlines() 
      
    else:
      ### FILE ###
      input_file = other_args[0]
      fileLines = randline(input_file)
      out_lines = fileLines.lines

    out_lines_temp = []
    for m in out_lines:
        out_lines_temp.append(m.rstrip())
    out_lines = out_lines_temp

  elif args.input_range is None and len(other_args) > 1:
      parser.error("extra operand '" + other_args[0] + "'")

  else:
    if len(other_args) != 0:
      parser.error("extra operand '" + other_args[0] + "'")

  random.shuffle(out_lines)

   #### REPEAT ###
#using structural pattern matching
  match [args.repeat, (bool(args.head_count == None))]:
    case [False, True]: # no r no n
      if hc_num is None:  
        hc_num = len(out_lines)
      for i in range(0, hc_num):  
        sys.stdout.write(str(out_lines[i]) + "\n")
        
    case [False, False]:
      if hc_num is None:  
        hc_num = len(out_lines)
      if hc_num > len(out_lines):
        hc_num = len(out_lines)
      for i in range(0, hc_num):  # no r, n present
        sys.stdout.write(str(out_lines[i]) + "\n")

    case [True, True]:
       while hc_num != 0:  #both r and n present
        sys.stdout.write(out_lines[0] + "\n")
        random.shuffle(out_lines)

    case [True, False]:
      while hc_num != 0:  #both r and n present
        sys.stdout.write(out_lines[0] + "\n")
        random.shuffle(out_lines)
        hc_num -= 1
    
  
if __name__ == "__main__":
  main()
