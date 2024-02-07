# %%
import re
from typing import List

input = """
z(jmax), zhe(jmax), e1356(jmax), e1304(jmax), e1027(jmax), e989(jmax), elbh(jmax)
"""


def format(input: str) -> str:
    input = input.replace(" &", "")
    inputs = input.split()
    outputs = []
    for i in inputs:
        outputs += i.split(", ")
    inputs = [i.strip() for i in inputs]

    def parse_fortran_arrays(declarations):
        result = {}

        for declaration in declarations:
            # Using regular expression to extract array name and dimensions
            match = re.match(r'\s*(\w+)\s*\(\s*([^)]+)\s*\)\s*', declaration)

            if match:
                array_name = match.group(1)
                dimensions = tuple(map(str.strip, match.group(2).split(',')))
                if dimensions not in result:
                    result[dimensions] = []
                result[dimensions].append(array_name)
                # result.append([array_name, dimensions])

        return result
    outputs = parse_fortran_arrays(outputs)

    output = ''
    for k, v in outputs.items():
        output += f"real,dimension({','.join(k)})::{','.join(v)}\n"

    return output


print(format(input))

# %%
cglow = {'real': {('16',): ['snoem_zin'],
                  ('33',): ['snoem_mlatin'],
                  ('33','16'): ['snoem_no_mean'],
                  ('33', '16', '3'): ['snoem_eofs']}}

with open('cglow_vars.f90', 'r') as file:
    line_continue = False
    dtype = None
    for line in file:
        line = line.split('!')[0].strip()
        line = line.replace(' ', '')
        line = line.lower()
        vars = []
        if '::' in line:  # if the line contains '::'
            line_continue = False
            definition = line.split('::')[0].strip()
            vars = line.split('::')[-1].strip()
            if '&' == vars[-1]:
                line_continue = True
                vars = vars.replace('&', '').strip()
            vars = vars.split(',')
            vars = [v.strip() for v in vars]
            vars = list(filter(lambda x: x != '', vars))
            dtype = definition.split(',', maxsplit=1)[0].strip()
            dim = None
            if 'dimension' in definition:
                dimensions = definition.split('dimension')[1].strip()
                dimensions = dimensions.split('(')[1].split(')')[0].split(',')
                dim = tuple([d.strip() for d in dimensions])
        elif line_continue:
            line_continue = False
            vars = line.strip()
            if '&' == vars[-1]:
                line_continue = True
                vars = vars.replace('&', '').strip()
            vars = vars.split(',')
            vars = [v.strip() for v in vars]
        if dtype is None:
            continue
        if dtype not in cglow.keys():
            cglow[dtype] = {}
        if dim not in cglow[dtype].keys():
            cglow[dtype][dim] = []
        cglow[dtype][dim] += vars
# %%

def find_in_cglow(inp: str)->List[str]:
    lines = inp.split('\n')
    lines = [l.strip().lower() for l in lines]
    lines = [l.split('!')[0].strip() for l in lines]
    lines = list(filter(lambda x: len(x) > 0, lines))
    line_cont = False
    vars = []
    for line in lines:
        if 'use' in line and 'cglow' in line and ':' in line: # use_cglow
            lvars = line.split(':')[-1]
            if lvars[-1] == '&':
                line_cont = True
                lvars = lvars.replace('&', '').strip()
            lvars = lvars.split(',')
            vars += [v.strip() for v in lvars]
        elif line_cont:
            line_cont = line[-1] == '&'
            line = line.replace('&', '').strip()
            lvars = line.split(',')
            vars += [v.strip() for v in lvars]
    vars = list(filter(lambda x: len(x) > 0, vars))
    vars = list(map(lambda x: x.split('=>')[-1], vars))
    return vars      
# %%
def cglow_to_def(inp: List[str], model: dict)->str:
    outs = {}
    for i in inp:
        for k, v in model.items():
            for kk, vv in v.items():
                if i in vv:
                    dtype = (k, kk)
                    if dtype not in outs:
                        outs[dtype] = []
                    outs[dtype].append(i)
    output = ''
    for k, v in outs.items():
        if k[-1 ] is None:
            output += f"{k[0]}::"
        else:
            dims = list(k[1])
            output += f"{k[0]},dimension({','.join(dims)})::"
        output += ','.join(v) + '\n'
    return output
# %%
inp = """use cglow,only: lmax,data_dir,wave1,wave2,sf_rflux,sf_scale1,sf_scale2
"""
print(cglow_to_def(find_in_cglow(inp), cglow))
# %%
