// With Docker registry 
pipeline {
    agent none  
    stages {
        stage('pr') 
        {
            agent {
                docker {
                    image 'quay.io/fossid/fossid-cicd:0.3.2'
                    // args '-u root:root' 
                    // No credentials here, will be handled by withDockerRegistry
                }
            }
            environment {
                FOSSID_HOST = credentials('QUAY_USERNAME')     // Jenkins Credentials ID
                FOSSID_TOKEN = credentials('QUAY_PASSWORD')   // Jenkins Credentials ID
            }

            steps {
                script {
                    withDockerRegistry(
                        credentialsId: 'QUAY_CREDENTIALS_ID', // Replace with your Jenkins ID for Quay
                        url: 'https://quay.io'
                    ) {
                        checkout scm
                        sh '''
                            fossid-cicd \
                            diff-scan \
                            --fossid-host $FOSSID_HOST \
                            --fossid-token $FOSSID_TOKEN \
                            --fail-on-any-issues 1
                        '''
                    }
                }
            }
        }
    }

    post {
        failure {
            echo 'FossID scan failed. Check logs for details.'
        }
    }
}
