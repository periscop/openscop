pipeline {
  environment{
    MACOS_TOOLS_COMMANDS = 'brew install automake libtool'

    CMAKE_BUILD_COMMANDS = 'mkdir build && cd build && cmake .. && cmake --build'
    CMAKE_CHECK_COMMANDS = 'cd build && cmake --build . --target check'

    AUTOM_BUILD_COMMANDS = './autogen.sh && ./configure && make -j'
    AUTOM_CHECK_COMMANDS = 'make check -j'
  }
  agent none
  stages{
    stage('OpenScop'){
      matrix{
        agent {
          label "${OS}"
        }
        axes{
          axis{
            name 'OS'
            values 'Ubuntu', 'macOS', 'CentOS'
          }
          axis{
            name 'BuildSystem'
            values 'GNU Autotools'//, 'CMake'
          }
        }
        stages{
          stage('Tools'){
            steps{
              script{
                if(env.OS == 'macOS')
                  sh MACOS_TOOLS_COMMANDS
              }
            }
          }
          stage('Build'){
            steps{
              script{
                if(env.BuildSystem == 'GNU Autotools')
                  sh AUTOM_BUILD_COMMANDS
                if(env.BuildSystem == 'CMake')
                  sh CMAKE_BUILD_COMMANDS
              }
            }
          }
          stage('Test'){
            steps{
              script {
                if(env.BuildSystem == 'GNU Autotools')
                  sh AUTOM_CHECK_COMMANDS
                if(env.BuildSystem == 'CMake')
                  sh CMAKE_CHECK_COMMANDS
              }
            }
          }
        }
      }
    }
  }
}
