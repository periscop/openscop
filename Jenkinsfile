pipeline {
  agent none
  matrix{
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
        values 'configure', 'CMake'
      }
      stages{
        stage('Tools (Mac)'){
          when { expression { env.PLATFORM == 'mac' } }
          steps{
            sh 'brew install automake libtool'
          }
        }
        stage('Prepare'){
          steps {
            sh './autogen.sh; ./configure;'
          }
        }
        stage('Build'){
          steps {
            sh 'make -j'
          }
        }
        stage('Test'){
          steps {
            sh 'make check -j'
          }
        }
      }
    }
  }
}
