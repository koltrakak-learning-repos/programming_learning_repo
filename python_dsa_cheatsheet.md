# Python DSA Cheatsheet

---

## Lists (Dynamic Array)

```python
lst = [3, 1, 4, 1, 5]
```

| Method / Operation | Description | Time |
|---|---|---|
| `lst.append(x)` | Add x to end | O(1) |
| `lst.pop()` | Remove & return last element | O(1) |
| `lst.pop(i)` | Remove & return element at index i | O(n) |
| `lst.insert(i, x)` | Insert x at index i | O(n) |
| `lst.remove(x)` | Remove first occurrence of x | O(n) |
| `lst[i]` | Access element at index i | O(1) |
| `lst[i:j]` | Slice from i to j (exclusive) | O(k) |
| `lst[i:j:step]` | Slice with step | O(k) |
| `lst[::-1]` | Reverse a list (returns copy) | O(n) |
| `lst.reverse()` | Reverse in-place | O(n) |
| `lst.sort()` | Sort in-place (ascending) | O(n log n) |
| `lst.sort(reverse=True)` | Sort descending in-place | O(n log n) |
| `sorted(lst)` | Return new sorted list | O(n log n) |
| `sorted(lst, key=fn)` | Sort by custom key function | O(n log n) |
| `len(lst)` | Number of elements | O(1) |
| `lst.index(x)` | Index of first occurrence of x | O(n) |
| `lst.count(x)` | Count occurrences of x | O(n) |
| `x in lst` | Membership check | O(n) |
| `lst.extend(other)` | Append all elements of other | O(k) |
| `lst + other` | Concatenate two lists | O(n+k) |
| `lst * k` | Repeat list k times | O(nk) |
| `min(lst)` / `max(lst)` | Min / max value | O(n) |
| `sum(lst)` | Sum all elements | O(n) |

```python
# Common patterns
lst = [0] * n                        # Initialize list of n zeros
matrix = [[0] * cols for _ in range(rows)]  # 2D matrix
pairs = sorted(lst, key=lambda x: x[1])     # Sort by second element
```

---

## Strings

```python
s = "hello world"
```

| Method / Operation | Description |
|---|---|
| `s[i]` | Character at index i |
| `s[i:j]` | Substring from i to j |
| `s[::-1]` | Reverse string |
| `len(s)` | Length |
| `s.split(sep)` | Split into list by separator (default: whitespace) |
| `sep.join(lst)` | Join list into string with separator |
| `s.strip()` | Remove leading/trailing whitespace |
| `s.lower()` / `s.upper()` | Case conversion |
| `s.replace(a, b)` | Replace all occurrences of a with b |
| `s.find(sub)` | Index of first occurrence (-1 if not found) |
| `s.count(sub)` | Count non-overlapping occurrences |
| `s.startswith(p)` / `s.endswith(p)` | Prefix/suffix check |
| `s.isdigit()` / `s.isalpha()` / `s.isalnum()` | Character type checks |
| `ord(c)` | Character → ASCII integer |
| `chr(n)` | ASCII integer → character |
| `sub in s` | Substring check |

```python
# Common patterns
chars = list(s)              # Mutable "string" as list
"".join(chars)               # Back to string
s.split(",")                 # ["a", "b", "c"]
", ".join(["a","b","c"])     # "a, b, c"
f"value is {x}"             # f-string formatting
```

---

## Dictionary (Hash Map)

```python
d = {"a": 1, "b": 2}
```

| Method / Operation | Description | Time |
|---|---|---|
| `d[key]` | Get value (KeyError if missing) | O(1) |
| `d.get(key, default)` | Get value with fallback | O(1) |
| `d[key] = val` | Set / update value | O(1) |
| `del d[key]` | Delete key | O(1) |
| `key in d` | Membership check | O(1) |
| `d.keys()` | All keys | O(1) |
| `d.values()` | All values | O(1) |
| `d.items()` | All (key, value) pairs | O(1) |
| `d.pop(key, default)` | Remove & return value | O(1) |
| `d.update(other)` | Merge another dict in | O(k) |
| `len(d)` | Number of key-value pairs | O(1) |

```python
from collections import defaultdict, Counter, OrderedDict

# defaultdict — no KeyError on missing keys
d = defaultdict(int)       # default 0
d = defaultdict(list)      # default []
d = defaultdict(set)       # default set()
d["x"] += 1                # works without initializing

# Counter — frequency map
c = Counter("banana")      # Counter({'a': 3, 'n': 2, 'b': 1})
c = Counter([1,2,2,3])
c.most_common(2)           # [(2, 2), (1, 1)]  top 2
c["z"]                     # 0 (no KeyError)

# Merge / intersection
c1 + c2                    # combine counts
c1 & c2                    # min counts (intersection)
c1 | c2                    # max counts (union)

# Dict comprehension
squares = {x: x**2 for x in range(5)}
filtered = {k: v for k, v in d.items() if v > 0}
```

---

## Set (Hash Set)

```python
s = {1, 2, 3}
```

| Method / Operation | Description | Time |
|---|---|---|
| `s.add(x)` | Add element | O(1) |
| `s.remove(x)` | Remove x (KeyError if missing) | O(1) |
| `s.discard(x)` | Remove x (no error if missing) | O(1) |
| `s.pop()` | Remove & return arbitrary element | O(1) |
| `x in s` | Membership check | O(1) |
| `len(s)` | Number of elements | O(1) |
| `s1 \| s2` | Union | O(n+m) |
| `s1 & s2` | Intersection | O(min(n,m)) |
| `s1 - s2` | Difference (in s1, not s2) | O(n) |
| `s1 ^ s2` | Symmetric difference | O(n+m) |
| `s1.issubset(s2)` | Is s1 ⊆ s2? | O(n) |
| `s1.issuperset(s2)` | Is s1 ⊇ s2? | O(m) |

```python
# Common patterns
seen = set()
seen.add(x)

unique = list(set(lst))      # deduplicate (order not preserved)
```

---

## Tuple

```python
t = (1, 2, 3)
```

- Immutable sequence — useful as dict keys or hashable pairs
- `t[i]`, `len(t)`, `x in t`, unpacking: `a, b, c = t`
- `t.count(x)`, `t.index(x)`

```python
# Common patterns
point = (x, y)                         # coordinate pair
graph[node] = (weight, neighbor)       # edge with weight
a, b = b, a                            # swap without temp variable
```

---

## Stack

Python lists double as stacks (LIFO).

```python
stack = []
stack.append(x)   # push — O(1)
stack.pop()       # pop  — O(1)
stack[-1]         # peek — O(1)
not stack         # is empty?
```

---

## Queue

Use `collections.deque` — O(1) on both ends.

```python
from collections import deque

q = deque()
q.append(x)        # enqueue right  — O(1)
q.appendleft(x)    # enqueue left   — O(1)
q.popleft()        # dequeue left   — O(1)
q.pop()            # dequeue right  — O(1)
q[0]               # peek left      — O(1)
q[-1]              # peek right     — O(1)
not q              # is empty?
len(q)

# BFS template
q = deque([start])
visited = {start}
while q:
    node = q.popleft()
    for neighbor in graph[node]:
        if neighbor not in visited:
            visited.add(neighbor)
            q.append(neighbor)
```

---

## Heap (Priority Queue)

Python's `heapq` is a **min-heap** by default.

```python
import heapq

heap = []
heapq.heappush(heap, x)       # push       — O(log n)
heapq.heappop(heap)            # pop min    — O(log n)
heap[0]                        # peek min   — O(1)
heapq.heapify(lst)             # in-place   — O(n)
heapq.nsmallest(k, lst)        # k smallest — O(n + k log n)
heapq.nlargest(k, lst)         # k largest  — O(n + k log n)

# Max-heap: negate values
heapq.heappush(heap, -x)
max_val = -heapq.heappop(heap)

# Heap of tuples (sorted by first element)
heapq.heappush(heap, (priority, value))
pri, val = heapq.heappop(heap)
```

---

## `collections` Module

```python
from collections import deque, defaultdict, Counter, OrderedDict, namedtuple

# namedtuple — lightweight struct
Point = namedtuple("Point", ["x", "y"])
p = Point(1, 2)
p.x, p.y          # 1, 2

# OrderedDict — dict that remembers insertion order (useful for LRU)
od = OrderedDict()
od.move_to_end(key)         # move key to end
od.move_to_end(key, last=False)  # move key to front
od.popitem(last=True)       # remove last item
od.popitem(last=False)      # remove first item
```

---

## `bisect` Module (Binary Search on Sorted Lists)

```python
import bisect

bisect.bisect_left(lst, x)    # leftmost index where x can be inserted
bisect.bisect_right(lst, x)   # rightmost index where x can be inserted
bisect.insort_left(lst, x)    # insert x keeping list sorted — O(n)

# Check if x exists in sorted list
i = bisect.bisect_left(lst, x)
exists = i < len(lst) and lst[i] == x

# Count elements < x
count_less = bisect.bisect_left(lst, x)

# Count elements <= x
count_lte = bisect.bisect_right(lst, x)
```

---

## `itertools` Module

```python
import itertools

itertools.permutations(lst, r)        # all r-length permutations
itertools.combinations(lst, r)        # all r-length combinations (no repeat)
itertools.combinations_with_replacement(lst, r)
itertools.product(lst, repeat=2)      # cartesian product
itertools.chain(lst1, lst2)           # flatten iterables
itertools.accumulate(lst)             # running totals [1,3,6,10,...]
itertools.groupby(sorted_lst, key)    # group consecutive elements by key
itertools.islice(iterable, n)         # take first n elements lazily
```

---

## `functools` Module

```python
from functools import lru_cache, reduce, cmp_to_key

# Memoization — top-down DP
@lru_cache(maxsize=None)
def fib(n):
    if n < 2: return n
    return fib(n-1) + fib(n-2)

# Reset cache between test cases
fib.cache_clear()

# Reduce
reduce(lambda acc, x: acc + x, lst, 0)   # fold left

# Custom comparator for sorting
import functools
def cmp(a, b): return -1 if a < b else 1
lst.sort(key=functools.cmp_to_key(cmp))
```

---

## Classes (for Linked Lists, Trees, Graphs, etc.)

```python
# Linked List Node
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

# Binary Tree Node
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

# Graph (adjacency list)
from collections import defaultdict
graph = defaultdict(list)
graph[u].append(v)
graph[v].append(u)

# Union-Find (Disjoint Set)
class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n

    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])  # path compression
        return self.parent[x]

    def union(self, x, y):
        px, py = self.find(x), self.find(y)
        if px == py: return False
        if self.rank[px] < self.rank[py]: px, py = py, px
        self.parent[py] = px
        if self.rank[px] == self.rank[py]:
            self.rank[px] += 1
        return True
```

---

## Built-in Functions

| Function | Description |
|---|---|
| `range(n)` | 0 to n-1 |
| `range(a, b)` | a to b-1 |
| `range(a, b, step)` | a to b-1 with step |
| `enumerate(lst)` | (index, value) pairs |
| `zip(a, b)` | pair up two iterables |
| `map(fn, lst)` | apply fn to each element |
| `filter(fn, lst)` | keep elements where fn is True |
| `any(lst)` | True if any element is truthy |
| `all(lst)` | True if all elements are truthy |
| `abs(x)` | absolute value |
| `divmod(a, b)` | (a // b, a % b) |
| `pow(base, exp, mod)` | modular exponentiation |
| `round(x, n)` | round to n decimal places |
| `reversed(lst)` | reverse iterator (no copy) |
| `isinstance(x, type)` | type check |

```python
# Common one-liners
list(range(5))              # [0, 1, 2, 3, 4]
list(enumerate("abc"))      # [(0,'a'), (1,'b'), (2,'c')]
list(zip([1,2], [3,4]))     # [(1,3), (2,4)]
list(map(int, ["1","2"]))   # [1, 2]
list(filter(None, lst))     # remove falsy values

# Unzip / transpose
rows = [(1,2), (3,4)]
cols = list(zip(*rows))     # [(1,3), (2,4)]
```

---

## Math & Number Tricks

```python
import math

math.inf                    # positive infinity
float("inf")               # same
math.floor(x)              # round down
math.ceil(x)               # round up
math.sqrt(x)               # square root
math.log(x, base)          # logarithm
math.gcd(a, b)             # greatest common divisor
math.lcm(a, b)             # least common multiple (Python 3.9+)
math.factorial(n)          # n!
math.comb(n, k)            # n choose k — C(n,k)
math.perm(n, k)            # n permute k — P(n,k)

# Integer tricks
x // y                     # floor division
x % y                      # modulo
x ** y                     # exponentiation
x & (x - 1)               # clear lowest set bit
x & (-x)                   # isolate lowest set bit
bin(x)                     # binary string e.g. '0b1010'
bin(x).count('1')          # popcount (number of set bits)
x << 1                     # multiply by 2
x >> 1                     # floor divide by 2
```

---

## Comprehensions

```python
# List
[x**2 for x in range(10) if x % 2 == 0]

# Dict
{k: v for k, v in pairs}

# Set
{x % 3 for x in lst}

# Generator (lazy — no brackets)
gen = (x**2 for x in range(10))
sum(x**2 for x in range(10))    # sum without building list

# Nested (flatten 2D matrix)
flat = [cell for row in matrix for cell in row]

# 2D comprehension
matrix = [[r * c for c in range(cols)] for r in range(rows)]
```

---

## Common Algorithm Patterns

```python
# Two pointers
l, r = 0, len(lst) - 1
while l < r:
    ...

# Sliding window
window = {}
l = 0
for r in range(len(s)):
    window[s[r]] = window.get(s[r], 0) + 1
    while <condition>:
        window[s[l]] -= 1
        l += 1

# Binary search
lo, hi = 0, len(lst) - 1
while lo <= hi:
    mid = (lo + hi) // 2
    if lst[mid] == target: ...
    elif lst[mid] < target: lo = mid + 1
    else: hi = mid - 1

# DFS (recursive)
def dfs(node, visited):
    visited.add(node)
    for neighbor in graph[node]:
        if neighbor not in visited:
            dfs(neighbor, visited)

# DFS (iterative)
stack = [start]
visited = {start}
while stack:
    node = stack.pop()
    for neighbor in graph[node]:
        if neighbor not in visited:
            visited.add(neighbor)
            stack.append(neighbor)

# Backtracking skeleton
def backtrack(state):
    if is_solution(state):
        results.append(state[:])
        return
    for choice in choices(state):
        state.append(choice)
        backtrack(state)
        state.pop()

# Top-down DP with memoization
from functools import lru_cache
@lru_cache(maxsize=None)
def dp(i, ...):
    # base cases
    # recursive case
    pass

# Bottom-up DP
dp = [0] * (n + 1)
dp[0] = base
for i in range(1, n + 1):
    dp[i] = ...
```

---

## Sorting Tricks

```python
lst.sort(key=lambda x: x[0])            # sort by first element
lst.sort(key=lambda x: (x[1], x[0]))    # sort by 2nd, then 1st
lst.sort(key=lambda x: -x)              # sort descending
lst.sort(key=lambda x: x.lower())       # case-insensitive
lst.sort(key=len)                        # sort by length

# Stable sort: equal keys keep original order
# Python's sort is always stable (Timsort)
```

---

## Input Parsing (Competitive Programming)

```python
# Single line of ints
nums = list(map(int, input().split()))

# Multiple lines
import sys
data = sys.stdin.read().split()
idx = 0
n = int(data[idx]); idx += 1
```
