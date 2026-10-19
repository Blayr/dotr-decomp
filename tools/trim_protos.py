"""Drop the function prototypes a preprocessed EE GCC file never uses (tools/cc.sh, before cc1). Usage: trim_protos.py FILE.i

EE GCC 2.96's code for a big function changes once the headers grow past a size (sdk/newlib_7.c's _vfprintf_r
with ~50 more prototypes in include/functions.h; fewer never changed it): the compiler's memory housekeeping
runs at another moment. The Sony and C library files need only the few prototypes they call, so the rest go;
each dropped line stays as an empty one, so line numbers hold."""
import re
import sys
from pathlib import Path

PROTO = re.compile(r"^(?:extern\s+)?[A-Za-z_][\w \t\*]*?\b(\w+)\s*\([^;{}()]*(?:\([^;{}()]*\)[^;{}()]*)*\)\s*;\s*$")
path = Path(sys.argv[1])
lines = path.read_text().split("\n")
uses: dict[str, int] = {}
for w in re.findall(r"\b[A-Za-z_]\w*\b", "\n".join(lines)):
    uses[w] = uses.get(w, 0) + 1
out = []
for ln in lines:
    m = PROTO.match(ln)
    if m and not ln.startswith("typedef") and uses.get(m.group(1), 0) == 1:
        out.append("")
    else:
        out.append(ln)
path.write_text("\n".join(out))
