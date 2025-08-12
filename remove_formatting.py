import sys
import re

def replace(target, new_str, start, end):
    result = target[:start] + new_str + target[end:]

    return result

with open(sys.argv[1], "r") as f:
    lines = f.readlines()

labels = {}

new_lines = []

for line in lines:
    if line != "\n":
        line = re.sub(" *\n", "\n", line)

        new_lines.append(line)

lines = new_lines

for i in range(len(lines)):
    res = re.search(r" -(.*)", lines[i])

    if res:
        labels[res.group(1)] = i

    lines[i] = re.sub(r" -(.*)", "", lines[i])

for i in range(len(lines)):
    res_pos = re.search(r" \?\+(.)", lines[i])

    if res_pos:
        lines[i] = replace(lines[i], str(i + int(res_pos.group(1))), res_pos.start(), res_pos.end())

    res_neg = re.search(r" \?-(.)", lines[i])

    if res_neg:
        lines[i] = replace(lines[i], str(i - int(res_neg.group(1))), res_neg.start(), res_neg.end())

for i in range(len(lines)):
    for label in labels.keys():
        res = re.search(r"(" + re.escape(label) + r")\W", lines[i])

        if res:
            lines[i] = replace(lines[i], str(labels[label]), res.start(1), res.end(1))

with open(sys.argv[2], "w") as f:
    f.writelines(lines)