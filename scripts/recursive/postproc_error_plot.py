import sys

try:
    while True:
        tokens = input().split()
        try:
            _avg, _min, _max = map(float, tokens)
            print(sys.argv[1][:sys.argv[1].find(".txt")], _avg, _min, _max)
        except ValueError:
            continue
except EOFError:
    pass
