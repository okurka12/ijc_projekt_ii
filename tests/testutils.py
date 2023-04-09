# Created: 2023-03-30
#
# author: Vit Pavlik (https://github.com/okurka12/)
#
# This file contains my very simple toolkit for testing in python:
# run       - simple wrapper of a subprocess.run
# print_ok  - print successful test (behaves like print)
# print_err - print failed test (behaves like print)

import subprocess


class result_t:
    rcode: int
    stdout: str
    stderr: str


class colors:
    r"""Codes for ANSI colors, where:
    `\033`       is ESC (ASCII 27, octal escape)
    `91|92|...`  is ANSI code for a color
    `m`          is a mark for the end of ANSI code"""

    red = "\033[91m"
    green = "\033[92m"
    white = "\033[m"


def print_ok(*args, **kwargs) -> None:
    """print '[OK] ...', behaves like print"""
    print(f"{colors.green}[OK]", *args, colors.white, **kwargs)


def print_err(*args, **kwargs) -> None:
    """print '[Failed] ...', behaves like print"""
    print(f"{colors.red}[Failed]", *args, colors.white, **kwargs)


def run(command: str, input_str: str=None) -> result_t:
    """runs command and returns class result_t containing it's return code, 
    stdout and stderr, if input_str is specified, it is passed to the command's
    stdin"""
    result = subprocess.run(command.split(" "), 
                            stdout=subprocess.PIPE, 
                            stderr=subprocess.PIPE, 
                            text=True,
                            input=input_str)
    out = result_t()
    out.rcode = result.returncode
    out.stdout = result.stdout.strip()
    out.stderr = result.stderr.strip()
    return out
