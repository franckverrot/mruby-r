# script.r
# This script will generate 100 strings
dyn.load('../../build/mruby')
values <- .C("mruby_r_eval", source="./source.rb", output=rep(c(''),each=1000))

dist <- values[2]

table(dist)
plot(table(dist))
