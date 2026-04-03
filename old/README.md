# Lookup table db

make it like a couple boxes and prevent concurrent writes
- even have a visualization for the server in the command line that shows when two boxes are open at the same time

e.g.

```
TABLE A     | TABLE B    | TABLE C
 key 1 read | key 1 read |
 key 1 read |            |
 key 2 write|            |
```
implement:
- cache
- socket server
- multithreading for multiple clients
- multiple distributed servers/nodes
- eventually b trees
