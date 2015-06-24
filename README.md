# mruby-r -- Use mruby for returning data to R

Generating datasets can be rather inconvenient and doing it directly in Ruby
can be simpler for some.

# Requirements

* compile tools (clang or tool that `mruby` requires to build)
* R (not needed at compile-time)

# Installation

First, you will have to clone `mruby`:

    git clone git@github.com/mruby/mruby.git
    cd mruby

mruby doesn't use traditional Ruby gems. Each gem will be required at
compile-time to avoid missing dependencies at runtime. So Like any typical
mruby gem, you will first have to update your `build_config.rb` to add this
line:

    conf.gem :git => 'git@github.com:franckverrot/mruby-r.git', :branch => 'master'

Then you will be able to build your mruby distribution:

    make

This should produce a `mruby` binary into the `build/host/bin/` directory.

# Usage

`mruby-r` will make use of the `mruby` binary you previously built.

1. Copy the `mruby` binary to the current directory
2. Create a R file like the following:

```r
# script.r
# This script will generate 100 strings
dyn.load('mruby')
.C("mruby_r_eval", source="
  class Foo
    def initialize
      @count = 0
    end
    def next
      if @count < 100
        @count+=1
        \"foo#{@count}\"
      else
        nil
      end
    end
  end
  Foo.new
  ", output=rep(c(''),each=100))

foos <- values[2]
foos
```

3. Execute `R --slave --no-restore-data -f script.r`
   The output should look like:

```
$output
  [1] "foo1"   "foo2"   "foo3"   "foo4"   "foo5"   "foo6"   "foo7"   "foo8"
  [9] "foo9"   "foo10"  "foo11"  "foo12"  "foo13"  "foo14"  "foo15"  "foo16"
 [17] "foo17"  "foo18"  "foo19"  "foo20"  "foo21"  "foo22"  "foo23"  "foo24"
 [25] "foo25"  "foo26"  "foo27"  "foo28"  "foo29"  "foo30"  "foo31"  "foo32"
 [33] "foo33"  "foo34"  "foo35"  "foo36"  "foo37"  "foo38"  "foo39"  "foo40"
 [41] "foo41"  "foo42"  "foo43"  "foo44"  "foo45"  "foo46"  "foo47"  "foo48"
 [49] "foo49"  "foo50"  "foo51"  "foo52"  "foo53"  "foo54"  "foo55"  "foo56"
 [57] "foo57"  "foo58"  "foo59"  "foo60"  "foo61"  "foo62"  "foo63"  "foo64"
 [65] "foo65"  "foo66"  "foo67"  "foo68"  "foo69"  "foo70"  "foo71"  "foo72"
 [73] "foo73"  "foo74"  "foo75"  "foo76"  "foo77"  "foo78"  "foo79"  "foo80"
 [81] "foo81"  "foo82"  "foo83"  "foo84"  "foo85"  "foo86"  "foo87"  "foo88"
 [89] "foo89"  "foo90"  "foo91"  "foo92"  "foo93"  "foo94"  "foo95"  "foo96"
 [97] "foo97"  "foo98"  "foo99"  "foo100"
```

# Known limitations / Design choices

1. Scripts can only return single strings (`MRB_TT_STRING`)

# License

Copyright (c) 2015 Franck Verrot. MIT LICENSE. See LICENSE.md for details.
