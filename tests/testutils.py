# Created: 2023-03-30
#
# This file contains my very simple toolkit for testing in python:
# run       - simple wrapper of a subprocess.run
# print_ok  - print successful test (behaves like print)
# print_err - print failed test (behaves like print)

import subprocess


class colors:
    r"""Codes for ANSI colors, where:
    `\033`       is ESC (ASCII 27, octal escape)
    `91|92|...`  is ANSI code for a color
    `m`          is a mark for the end of ANSI code"""

    red = "\033[91m"
    green = "\033[92m"
    white = "\033[m"


def print_ok(text: str) -> None:
    print(f"{colors.green}[OK] {text}{colors.white}")


def print_err(text: str) -> None:
    print(f"{colors.red}[Failed] {text}{colors.white}")


def run(command: str, input_str: str=None) -> (int, str, str):
    """runs command and returns tuple of it's return code, stdout and stderr,
    if input_str is specified, it is passed to the command's stdin"""
    result = subprocess.run(command, 
                            stdout=subprocess.PIPE, 
                            stderr=subprocess.PIPE, 
                            text=True,
                            input=input_str)
    return (result.returncode, result.stdout.strip(), result.stderr.strip())
