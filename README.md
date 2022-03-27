# gun2fun

`gun2fun` is a simple `Gunpaint` to `Funpaint 2` IFLI graphic format converter utility.

It accepts a [Gunpaint](https://commodore.software/downloads/download/43-hi-res-graphics-editors/15394-gunpaint) file on the input.

It produces an unpacked [Funpaint 2](https://commodore.software/downloads/download/43-hi-res-graphics-editors/15476-funpaint-ii) file on the output.

## Version

Version 1.0.0 (2022-03-27)

## Installation

Install prerequisite libraries:

    $ sudo dnf install boost-devel

Clone the repository:

    $ git clone git@github.com:pawelkrol/gun2fun.git

Compile and run the program:

    $ cd gun2fun
    $ make
    $ ./gun2fun <input-file.gun> <output-file.fun>

## Copyright and Licence

Copyright (C) 2022 by Pawel Krol.

This software is distributed under the terms of the MIT license. See [LICENSE](https://github.com/pawelkrol/gun2fun/blob/master/LICENSE.md) for more information.
