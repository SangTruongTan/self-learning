#!/usr/bin/python3
import os
import sys

# Colour printing
def prRed(skk): print("\033[91m{}\033[00m" .format(skk))


def prGreen(skk): print("\033[92m{}\033[00m" .format(skk))


def prYellow(skk): print("\033[93m{}\033[00m" .format(skk))


def prLightPurple(skk): print("\033[94m{}\033[00m" .format(skk))


def prPurple(skk): print("\033[95m{}\033[00m" .format(skk))


def prCyan(skk): print("\033[96m{}\033[00m" .format(skk))


def prLightGray(skk): print("\033[97m{}\033[00m" .format(skk))


def prBlack(skk): print("\033[98m{}\033[00m" .format(skk))

def prWhite(skk): print(skk)

def build_and_execute_cpp(file_name):
    prGreen("Build the C++ program using g++")
    compile_command = f"g++ {file_name} -o {file_name + '.o'}"
    print(compile_command)
    compile_status = os.system(compile_command)

    if compile_status != 0:
        prRed("Compilation failed.")
        return

    prGreen("Execute the compiled program")
    execute_command = f"./{file_name + '.o'}"
    if len(sys.argv) > 2:
        for i in range(2, len(sys.argv)):
            execute_command = f"{execute_command + ' ' + sys.argv[i]}"
            i = i + 1
    prCyan(execute_command)
    os.system(execute_command)

# Usage example
if len(sys.argv) < 2:
    prPurple("Please provide the C++ file as an argument.")
else:
    cpp_file = sys.argv[1]
    build_and_execute_cpp(cpp_file)
