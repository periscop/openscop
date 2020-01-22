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
      stage('Tools'){
        steps{script{
          if(env.PLATFORM == 'mac'){
            sh 'brew install automake libtool'
          }
        }}
      }
      stage('Build'){
        steps{script{
          if(env.BUILD_SYSTEM == 'Configure')
          {
            sh './autogen.sh'
            sh './configure'
            sh 'make -j'
          }
          if(env.BUILD_SYSTEM == 'CMake')
          {
            sh 'mkdir build'
            sh 'cd build'
            sh 'cmake ..'
            sh 'make -j'
          }
        }}
      }
      stage('Test'){
        steps {
          sh 'make check -j'
        }
      }
    }
  }}}
}
