# script.r
dyn.load('../../build/mruby-r')
values <- .C("mruby_r_eval", source="./source.rb", output=rep(c(''),each=1000))

Chars <- data.frame(values[2])

table(Chars)
plot(table(Chars))
