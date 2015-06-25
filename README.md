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
2. Create a R script like the following:

  ```r
  # script.r
  # This script will generate 100 strings
  dyn.load('mruby')
  .C("mruby_r_eval", source="source.rb", output=rep(c(''),each=100))

  foos <- values[2]
  foos
  ```

3. Create a Ruby script like the following:

  ```ruby
  class DataSource
    def initialize
      @count = 0
      @elements = (0..100).map { |i| sprintf("e%03d", i) }
    end

    def next
      if @count < 1000
        @count += 1
        @elements.sample.to_s
      else
        nil
      end
    end
  end

  DataSource # Don't forget to return the class at the end of the script
  ```

4. Execute `R --slave --no-restore-data -f script.r`
   The output should look like:

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
