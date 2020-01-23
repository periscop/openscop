pipeline {
  environment{
    MACOS_TOOLS_COMMANDS = 'brew install automake libtool'
  
    CMAKE_BUILD_COMMANDS = 'mkdir build && cd build && cmake .. && cmake --build'
    CMAKE_CHECK_COMMANDS = 'cd build && cmake --build . --target check'
    
    AUTOM_BUILD_COMMANDS = './autogen.sh && ./configure && make -j'
    AUTOM_CHECK_COMMANDS = 'make check -j'
  }
  agent none
  stages { stage('OpenScop') { matrix{
    agent {
      label "${PLATFORM}"
    }
    axes{
      axis{
        name 'PLATFORM'
        values 'lin', 'mac', 'win'
      }
      axis{
        name 'BUILD_SYSTEM'
        values 'CMake', 'Configure'
      }
    }
    excludes{
      exclude{
        axis{
          name 'PLATFORM'
          values 'win'
        }
        axis{
          name 'BUILD_SYSTEM'
          values 'Configure'
        }
      }
    }
    stages{
      stage('Tools'){
        steps{script{
          if(env.PLATFORM == 'mac'){
            sh MACOS_TOOLS_COMMANDS
          }
        }}
      }
      stage('Build'){
        steps{script{
          if(env.PLATFORM != 'win'){
            if(env.BUILD_SYSTEM == 'Configure')
              sh AUTOM_BUILD_COMMANDS
            if(env.BUILD_SYSTEM == 'CMake')
              sh CMAKE_BUILD_COMMANDS
          } else {
            if(env.BUILD_SYSTEM == 'CMake')
              bat CMAKE_BUILD_COMMANDS
          }
          
        }}
      }
      stage('Test'){
        steps {
          script {
            if(env.PLATFORM != 'win'){
              if(env.BUILD_SYSTEM == 'Configure')
                sh AUTOM_CHECK_COMMANDS
              if(env.BUILD_SYSTEM == 'CMake')
                sh CMAKE_CHECK_COMMANDS
            } else {
              if(env.BUILD_SYSTEM == 'CMake')
                bat CMAKE_CHECK_COMMANDS
            }
          }
        }
      }
    }
  }}}
}
