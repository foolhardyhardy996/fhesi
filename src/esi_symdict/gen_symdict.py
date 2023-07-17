#!/usr/bin/env python3

"""Generate symbol dictionary header and source code"""

import argparse as ap

cli_args_parser = ap.ArgumentParser(
    prog="gen_symdict",
    description="Generate symbol dictionary header and source code"
)

cli_args_parser.add_argument("-p", "--prefix", help="prefix to symbols", required=False)
symbol_specifier_group = cli_args_parser.add_mutually_exclusive_group(required=True)
symbol_specifier_group.add_argument("-l", "--symbol-list", help="comma-separated list of symbol names")
symbol_specifier_group.add_argument("-f", "--symbol-file", help="a file containing comma-separated list of symbol names")
cli_args_parser.add_argument('-t', "--val-type", help="type of dict keyed value", required=True)

args = cli_args_parser.parse_args()

