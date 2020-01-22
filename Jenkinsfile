pipeline {
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
            {
              sh './autogen.sh'
              sh './configure'
              sh 'make -j'
            }
            if(env.BUILD_SYSTEM == 'CMake')
            {
              sh 'mkdir build'
              dir('build') {
                sh 'cmake ..'
                sh 'make -j'
              }
            }
          } else {
            if(env.BUILD_SYSTEM == 'CMake')
            {
              bat 'mkdir build'
              dir('build'){
                bat 'cmake ..'
              }
            }
          }
          
        }}
      }
      stage('Test'){
        steps {
          script {
            if(env.PLATFORM != 'win'){
              if(env.BUILD_SYSTEM == 'Configure')
              {
                sh 'make check -j'
              }
              if(env.BUILD_SYSTEM == 'CMake')
              {
                dir('build'){
                  sh 'make check -j'
                }
              }
            } else {
              if(env.BUILD_SYSTEM == 'CMake')
              {
                
              }
            }
          }
        }
      }
    }
  }}}
}
