require 'fileutils'

MRubyRCompilationFailed = Class.new(RuntimeError)

desc "Build mruby in a vendor directory"
task :vendor_mruby do
  FileUtils.mkdir_p('vendor')
  chdir('vendor') do
    sh "git clone git@github.com:mruby/mruby.git mruby"
    chdir('mruby') do
      FileUtils.cp('../../config/build_config.rb', '.')
      sh "make"
    end
  end

  target = 'vendor/mruby/build/host/bin/mruby'

  contains_mruby_r = begin
                       sh "nm -a #{target} | grep mruby_r_eval"
                     rescue
                       false
                     end

  if contains_mruby_r
    FileUtils.mkdir_p('build')
    FileUtils.cp(target, 'build')
  else
    raise MRubyRCompilationFailed, "Can't seem to find a valid mruby_r_eval function in the mruby binary. Aborting."
  end
end

desc "Clean vendor"
task :clean do
  FileUtils.rm_rf('vendor')
  FileUtils.rm_rf('build')
end

desc "Run test"
task :test do
  Dir.glob('examples/*/').each do |dir|
    chdir dir do
      sh "R --slave --no-restore-data -f script.r"
    end
  end
end

task :default => [:clean, :vendor_mruby, :test]
