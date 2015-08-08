require 'fileutils'
require 'tempfile'

MRubyRCompilationFailed = Class.new(RuntimeError)
MRUBY_R_STATIC_LIB = 'vendor/mruby/build/host/lib/libmruby.a'
MRUBY_R_SHARED_LIB = 'build/mruby-r'
MRUBY_R_IS_CONTAINED_INTO = ->(file) { sh("nm -a #{file} | grep mruby_r_eval_internal") rescue false }

desc "Build mruby in a vendor directory"
task :vendor_mruby do
  FileUtils.mkdir_p('vendor')
  FileUtils.mkdir_p('build')

  chdir('vendor') do
    repo_path = ENV.fetch('MRUBY_REPO_PATH') do
       warn <<-EOS
       mruby-r will fetch a version of mruby from GitHub.
       Set MRUBY_REPO_PATH to local git repository to speed up this process.
       EOS
      'https://github.com/mruby/mruby.git'
    end
    sh "git clone --depth=1 #{repo_path} mruby"

    # build mruby
    chdir('mruby') do
      FileUtils.cp('../../config/build_config.rb', '.')
      sh "make"
    end
  end

  if MRUBY_R_IS_CONTAINED_INTO[MRUBY_R_STATIC_LIB]
    puts "mruby built..."
  else
    raise MRubyRCompilationFailed, "Can't seem to find a valid mruby_r_eval function in the mruby static binary. Aborting."
  end
end

desc "Build a mruby/r bridge"
task :build_bridge do
  Tempfile.open(%w(mruby_bridge_file .c)) do |source|
    source.puts <<-EOS
      extern void mruby_r_eval_internal(char **, char **);

      void mruby_r_eval(char** source, char **output) {
        mruby_r_eval_internal(source, output);
      }
    EOS
    source.rewind

    sh "cc -shared #{source.path} #{MRUBY_R_STATIC_LIB} -o #{MRUBY_R_SHARED_LIB}"
  end

  if MRUBY_R_IS_CONTAINED_INTO[MRUBY_R_SHARED_LIB]
    puts "Shared library built!"
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

task :default => [:clean, :vendor_mruby, :build_bridge, :test]
