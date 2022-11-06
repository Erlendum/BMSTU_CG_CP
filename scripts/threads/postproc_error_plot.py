import sys

try:
    while True:
        tokens = input().split()
        try:
            _avg, _min, _max = map(float, tokens)
            print(sys.argv[1][sys.argv[1].find("s") + 1:sys.argv[1].find(".")], _avg)
        except ValueError:
            continue
except EOFError:
    pass
