pipeline {
  agent none
  stages { stage('OpenScop') { matrix{
    agent {
      label "${PLATFORM}"
    }
    axes{
      axis{
        name 'PLATFORM'
        values 'lin', 'mac'
      }
      axis{
        name 'BUILD_SYSTEM'
        values 'Configure', 'CMake'
      }
    }
    stages{
      when { expression { env.PLATFORM == 'mac' } }
      stage('Tools (Mac)'){
        steps{
          sh 'brew install automake libtool'
        }
      }
      stage('Prepare'){
        steps {
          sh './autogen.sh; ./configure;'
        }
      }
      stage('Build ('Configure')'){
        when { expression { env.BUILD_SYSTEM == 'Configure' } }
        steps {
          sh 'make -j'
        }
      }
      stage('Build ('CMake')'){
        steps {
          sh 'mkdir build; cd build; cmake ..; make -j;'
        }
      }
      stage('Test'){
        steps {
          sh 'make check -j'
        }
      }
    }
  }}}
}
