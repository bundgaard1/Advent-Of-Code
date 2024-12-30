from collections import deque

valves = {}
tunnels = {}

for line in open("input.txt"):
    line = line.strip()
    valve = line.split()[0]
    flow = int(line.split(' ')[1])
    targets = line.split(" :")[1].split(' ')
    valves[valve] = flow
    tunnels[valve] = targets

dists = {}
nonempty = []

for valve in valves:
    if valve != "AA" and not valves[valve]:
        continue

    if valve != "AA":
        nonempty.append(valve)

    dists[valve] = {valve: 0, "AA": 0}

    visited = {valve}

    queue = deque([(0, valve)])

    while queue:
        distance, position = queue.popleft()

        for neighbor in tunnels[position]:
            if neighbor in visited:
                continue

            visited.add(neighbor)
            if valves[neighbor]:
                dists[valve][neighbor] = distance + 1
            queue.append((distance + 1, neighbor))

    del dists[valve][valve]
    if valve != "AA":
        del dists[valve]["AA"]

# print(dists)

indicies = {}

for index, element in enumerate(nonempty):
    indicies[element] = index

cache = {}


def dfs(time, valve, bitmask):
    if (time, valve, bitmask) in cache:
        return cache[(time, valve, bitmask)]
    maxval = 0
    for neighbor in dists[valve]:
        bit = 1 << indicies[neighbor]
        if bitmask & bit:
            continue

        remtime = time - dists[valve][neighbor] - 1
        if remtime <= 0:
            continue

        maxval = max(maxval, dfs(remtime, neighbor, bitmask |
                                 bit) + valves[neighbor] * remtime)
    cache[(time, valve, bitmask)] = maxval
    return maxval


b = (1 << len(nonempty)) - 1
m = 0

for i in range(b + 1):
    m = max(m, dfs(26, "AA", i) + dfs(26, "AA", b ^ i))


print(m)
