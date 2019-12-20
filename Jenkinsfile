pipeline {
  agent none
  stages{
    stage('OpenScop'){
      parallel{
        stage('Linux'){
          agent{
            label "lin"
          }
          stages{
            stage('prepare') {
              steps {
                sh './autogen.sh; ./configure;'
              }
            }
            stage('build') {
              steps {
                sh 'make;'
              }
            }
            stage('test') {
              steps {
                sh 'make check;'
              }
            }
          }
        }
        stage('Mac OS'){
          agent{
            label "mac"
          }
          stages{
            stage('prepare') {
              steps {
                sh 'brew install automake libtool'
                sh './autogen.sh; ./configure;'
              }
            }
            stage('build') {
              steps {
                sh 'make -j 2;'
              }
            }
            stage('test') {
              steps {
                sh 'make check;'
              }
            }
          }
        }
      }
    }
  }
}
