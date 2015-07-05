# mruby-r -- Use mruby for returning data to R

Generating datasets can be rather inconvenient and doing it directly in Ruby
can be simpler for some.

# Requirements

* compile tools (clang or tool that `mruby` requires to build)
* R (not needed at compile-time)

# Installation

## TL;DR

Run

    rake

in a terminal. This should build everything you need and this also runs some
examples (located in `examples`).


## Longer explanation

`mruby-r` makes use of `mruby`. The `Rakefile` provided with `mruby-r` will:

  * Clone
  * Configure
  * Build

`mruby` for you. The configuration file used by this process lives in the
`config/build_config.rb` file. Feel free to edit it to include other gems or
change some of the compile parameters

Running `rake` should produce `mruby` binary into the `build` directory.

Here are the current Rake tasks available (`rake -T`):

    rake clean         # Clean vendor
    rake test          # Run test
    rake vendor_mruby  # Build mruby in a vendor directory

# Usage

`mruby-r` will make use of the `mruby` binary you previously built.
Referring to this binary in a `dyn.load` function, from a R source file, gives
access to Ruby/mruby.

Given this R source file:

```r
# script.r
# This script will generate 100 strings
dyn.load("/path/to/build/mruby")
values <- .C("mruby_r_eval", source="/any/source.rb", output=rep(c(''),each=1000))

dist <- values[2]

table(dist)
plot(table(dist))
```

and this Ruby script:

```ruby
class DataSource
  def initialize
    @count = 0
    @elements = (0..100).map { |i| sprintf("e%03d", i) }
  end

  def next
    if @count < 1_000
      @count += 1
      @elements.sample.to_s
    else
      nil
    end
  end
end

DataSource # Don't forget to return the class at the end of the script
```

Executing `R --slave --no-restore-data -f script.r` should output:

  ```
  dist
  e000 e001 e002 e003 e004 e005 e006 e007 e008 e009 e010 e011 e012 e013 e014 e015
    11   14   12    9    9   13    7   10   12   11    9   10   13   13    9   10
  e016 e017 e018 e019 e020 e021 e022 e023 e024 e025 e026 e027 e028 e029 e030 e031
     9   11    8   10   11    6   15   11    6    6   10   13   12    5    9   12
  e032 e033 e034 e035 e036 e037 e038 e039 e040 e041 e042 e043 e044 e045 e046 e047
     8   13    9   12    9   13    6   11   18    7    8   10    8   10    8    7
  e048 e049 e050 e051 e052 e053 e054 e055 e056 e057 e058 e059 e060 e061 e062 e063
     8    4   13   10   13    6   13    7   11    9   11   15    8   11   16   11
  e064 e065 e066 e067 e068 e069 e070 e071 e072 e073 e074 e075 e076 e077 e078 e079
    13    8   10    9   10   12   14    9    4    7    7    7   10    6   12   16
  e080 e081 e082 e083 e084 e085 e086 e087 e088 e089 e090 e091 e092 e093 e094 e095
    14    7   16    6   11   10   12   16    7   10   10    3    8   10    8   16
  e096 e097 e098 e099 e100
     5    5    8   12    3
  ```

  And a plot should have been generated:

<img src="https://raw.githubusercontent.com/franckverrot/mruby-r/master/doc/plot_table_dist.png">

# Known limitations / Design choices

1. Scripts can only return single strings (`MRB_TT_STRING`)

# License

Copyright (c) 2015 Franck Verrot. MIT LICENSE. See LICENSE.md for details.
