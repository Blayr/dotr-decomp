# Third-party notices

Some C functions in `src/` were adapted from two public PlayStation 2 decompilation projects
under the MIT licence. Each one carries a one-line comment above it naming where it came from
and pointing to this file. The licence texts below must stay with the code.

| Source | Licence | What came from it |
|---|---|---|
| kfiv-decomp, `src/sce/` (github.com/Voicedrew11/kfiv-decomp, commit 1535613) | MIT | Sony SDK library functions (libkernl, libgraph, libdma, libdev, libipu, libmpeg, libcdvd, libpad) and C library functions |
| the ICO decompilation (github.com/nathanialf/ico), where kfiv's `src/sce/` tree came from | MIT, with a scope notice | the same kfiv files, except the ones kfiv wrote itself (libdev, `strcasecmp`) |
| gt4-decomp (github.com/gustavocanepa/gt4-decomp, commit c2e6ef51) | MIT | a few Sony SDK and newlib functions |
| newlib 1.9.0, inside gt4-decomp's newlib files | BSD-style, file by file | `__sfvwrite`, `strcasecmp`, `strncasecmp` |
| newlib 1.9.0 source release (sourceware.org, md5-checked) | BSD-style; AT&T for strtod.c and dtoa.c | `__svfscanf` (stdio/vfscanf.c), `_strtod_r` (stdlib/strtod.c), `_dtoa_r` (stdlib/dtoa.c, func_00195480) |

The kfiv C library functions (`malloc`, `free`, `__sfvwrite`, `__sbprintf` and their helpers) are
the ICO project's rebuilds of newlib; the newlib notices below are kept for them too.

These licences cover the decompilation projects' own work. They grant no rights in Sony's SDK
libraries, whose machine code these functions reproduce, nor in any game.

## kfiv-decomp

```
MIT License

Copyright (c) 2026 the kfiv-decomp contributors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

## The ICO decompilation (kfiv-decomp's `tools/LICENSE.ico`)

```
MIT License

Copyright (c) 2026 the ico decompilation contributors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

-------------------------------------------------------------------------------

NOTICE — SCOPE OF THIS LICENSE

This MIT license applies ONLY to the original source code, build scripts, and
documentation in this repository. It does NOT grant any rights in:

  - the ICO disc image, the SLUS-20218 ELF, or any portion of either,
  - any audio, image, model, text, or other asset extracted from the disc,
  - the ICO, Team Ico, or PlayStation 2 trademarks,
  - any other intellectual property of Sony Interactive Entertainment Inc.
    (formerly Sony Computer Entertainment Inc.), Sony Group, Team Ico, or
    their affiliates.

The authors and contributors of this repository are not affiliated with any
of those entities. To build the project you must legally provide your own
copy of the disc image; see docs/LEGAL.md and docs/BUILDING.md.
```

## gt4-decomp

```
MIT License

Copyright (c) 2026 Gustavo Canepa and gt4-decomp contributors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

## newlib 1.9.0

The stdio and stdlib files of newlib come from 4.4BSD and carry this notice (`__sfvwrite`'s
`fvwrite.c` and `__svfscanf`'s `vfscanf.c` among them):

```
Copyright (c) 1990 The Regents of the University of California.
All rights reserved.

Redistribution and use in source and binary forms are permitted
provided that the above copyright notice and this paragraph are
duplicated in all such forms and that any documentation,
advertising materials, and other materials related to such
distribution and use acknowledge that the software was developed
by the University of California, Berkeley.  The name of the
University may not be used to endorse or promote products derived
from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
```

A newlib file without a notice of its own (`strcasecmp.c`, `strncasecmp.c`) is covered by
section (9) of newlib's COPYING.NEWLIB:

```
Copyright (c) 1994, 1997 Cygnus Solutions. All rights reserved.

Redistribution and use in source and binary forms are permitted
provided that the above copyright notice and this paragraph are
duplicated in all such forms and that any documentation,
advertising materials, and other materials related to such
distribution and use acknowledge that the software was developed
at Cygnus Solutions. Cygnus Solutions may not be used to endorse
or promote products derived from this software without specific
prior written permission. THIS SOFTWARE IS PROVIDED ``AS IS'' AND
WITHOUT ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, WITHOUT
LIMITATION, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
FOR A PARTICULAR PURPOSE.
```

`_strtod_r` comes from newlib's `stdlib/strtod.c`, David M. Gay's code, under this notice:

```
The author of this software is David M. Gay.

Copyright (c) 1991 by AT&T.

Permission to use, copy, modify, and distribute this software for any
purpose without fee is hereby granted, provided that this entire notice
is included in all copies of any software which is or includes a copy
or modification of this software and in all copies of the supporting
documentation for such software.

THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
WARRANTY.  IN PARTICULAR, NEITHER THE AUTHOR NOR AT&T MAKES ANY
REPRESENTATION OR WARRANTY OF ANY KIND CONCERNING THE MERCHANTABILITY
OF THIS SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR PURPOSE.
```
