import os
from conans import ConanFile, tools

class SmoothyConan(ConanFile):
    name = "smoothy"
    settings = "os", "compiler", "build_type", "arch"
    description = "an optimization toolbox in C++"
    url = "https://github.com/vermosen/smoothy"
    license = ""
    author = "vermosen@yahoo.com"
    topics = None
    generators = 'cmake'

    cmake_files = ['%sConfig.cmake'        % name
                  ,'%sConfigVersion.cmake' % name
                  ,'%sTargets.cmake'       % name
                  ,'%sTargets-*.cmake'     % name]

    def build_requirements(self):
        self.build_requires("boost/[>=1.72.0]@%s/%s" % (self.user, self.channel))
        self.build_requires("pfr/1.0.0@%s/%s" % (self.user, self.channel))
        self.build_requires("eigen/3.3.7@%s/%s" % (self.user, self.channel))

    def source(self):
        self.run('git clone --recursive %s' % self.url)


    def _configure_cmake(self):

        cmake = CMake(self, set_cmake_flags=True)
        
        if self.settings.compiler == 'gcc':
            if self.settings.compiler.version in ['8', '8.4']:
                cmake.definitions["CMAKE_PROFILE"] = 'gcc84'
            elif self.settings.compiler.version in ['9', '9.3']:
                cmake.definitions["CMAKE_PROFILE"] = 'gcc93'
            else:
                self.output.info('compiler %s %s not supported' % 
                  (self.settings.compiler, self.settings.compiler.version))
        else:
            self.output.info('compiler %s %s not supported' % 
              (self.settings.compiler, self.settings.compiler.version))            
            exit(1)

        # cannot run conan command inside the build process
        cmake.definitions["SKIP_CONAN_PACKAGE"] = 'ON'
        cmake.configure(source_folder=self._source_subfolder)
        return cmake

    def build(self):
        self._runbuild = True
        cmake = self._configure_cmake()
        cmake.build()
        cmake.install()

    def package(self):
        self.copy("*.h"  , dst="include/smoothy", src="include/smoothy", keep_path=True)

        if self.settings.os == 'Linux':
            try:
                with open("build/%sTargets.cmake" % self.name) as f:
                    content = f.read()
                    self.output.info('read build/%sTargets.cmake content (size: %s)' % (self.name, len(content)))

                import re, glob
                m = re.search(r'set\(_IMPORT_PREFIX \"([^\"]+)\"\)', content)
                self.output.info('found prefix %s' % m.group(1))
                files = glob.glob('build/%sTargets*.cmake' % self.name)

                for f in files:
                    self.output.info('replacing prefix path in %s' % f)
                    tools.replace_in_file(f, m.group(1),
                        '${CONAN_%s_ROOT}' % self.name.upper(), strict=False)

                # step 2: substitute LIB_PATH
                with open("build/%sConfig.cmake" % self.name) as f:
                    content = f.read()
                    self.output.info('read build/%sTargets.cmake content (size: %s)' % (self.name, len(content)))

                m = re.search(r'set\(%s_LIBS_DIRS_HINT\s+\"([^\"]+)\"\s+\)' % self.name.upper(), content)
                self.output.info('found lib install location: %s' % m.group(1))

                for f in files:
                    self.output.info('replacing lib install location in %s' % f)
                    tools.replace_in_file(f, m.group(1),
                        '${CONAN_%s_ROOT}/lib' % self.name.upper(), strict=False)

                # step 3: copy the cmake config files
                self.output.info('looking for modified files in %s/build ...' % os.getcwd())

                for f in self.cmake_files:
                    self.copy("%s" % f, src="./build", keep_path=False)

            except:
                # always fails on the second lookup
                # self.output.info('failed to parse cmake install files!')
                pass

    def package_id(self):
        self.info.header_only()