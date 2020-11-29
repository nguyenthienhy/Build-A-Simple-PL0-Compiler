f = open("t.proc1.pl0", "r")
codes = f.readlines()
codes = [line.replace("\n", "") for line in codes]

codes = [" ".join(line.split()) for line in codes]

line_one = ""

for line in codes:
    line_one = line_one + " " + line

print(line_one)

with open("test.pl0", "w") as f:
    f.write(line_one)