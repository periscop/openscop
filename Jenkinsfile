pipeline {
  environment{
    CMAKE_BUILD_COMMANDS = 'mkdir build && cd build && cmake .. && cmake --build'
    CMAKE_CHECK_COMMANDS = 'cd build && cmake --build . --target check'
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
            sh 'brew install automake libtool'
          }
        }}
      }
      stage('Build'){
        steps{script{
          if(env.PLATFORM != 'win'){
            if(env.BUILD_SYSTEM == 'Configure')
              sh './autogen.sh && ./configure && make -j'
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
                sh 'make check -j'
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
