pipeline {
  agent none
  stages{
    stage('OpenScop'){
      matrix{
        agent{ label "${OS}" }
        axes{
          axis{
            name 'OS'
            values 'Ubuntu', 'macOS', 'CentOS', 'fedora', 'Debian'
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
                  sh 'brew install automake libtool'
                if(env.OS == 'CentOS')
                  sh 'sudo yum install gmp-devel -y'
                if(env.OS == 'fedora')
                  sh 'sudo dnf install gmp-devel -y'
                if(env.OS == 'Debian')
                  sh 'sudo apt install autoconf libtool libgmp-dev make -y'
              }
            }
          }
          stage('Build'){
            steps{
              script{
                if(env.BuildSystem == 'GNU Autotools')
                  sh './autogen.sh && ./configure && make -j'
                if(env.BuildSystem == 'CMake')
                  sh 'mkdir build && cd build && cmake .. && cmake --build'
              }
            }
          }
          stage('Test'){
            steps{
              script {
                if(env.BuildSystem == 'GNU Autotools')
                  sh 'make check -j'
                if(env.BuildSystem == 'CMake')
                  sh 'cd build && cmake --build . --target check'
              }
            }
          }
        }
      }
    }
  }
}
