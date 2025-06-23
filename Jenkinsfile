node {
    // Set up environment
    env.PROJECT_CODE = 'AgentTest1'
    env.API_URL = credentials('WB_User')
    env.API_TOKEN = credentials('WB_Token')
    env.QUAY_USERNAME = credentials('QuayLogin')
    env.QUAY_PASSWORD = credentials('Secret Text')

    stage('Checkout') {
        checkout scm
    }

    def hasChanges = false

stage('Detect Changes') {
    script {
        if (env.CHANGE_BRANCH && env.CHANGE_TARGET) {
            def base = sh(script: "git merge-base origin/${env.CHANGE_TARGET} origin/${env.CHANGE_BRANCH}", returnStdout: true).trim()
            def changedFiles = sh(script: "git diff --name-only --diff-filter=d ${base} ${env.CHANGE_BRANCH}", returnStdout: true).trim()
            
            if (changedFiles) {
                echo "Changed files:\n${changedFiles}"
                // could add scan logic here
                currentBuild.result = 'SUCCESS'
            } else {
                echo "No file changes detected."
                currentBuild.description = "No file changes"
                currentBuild.result = 'SUCCESS'  // Explicitly set to success
            }
        } else {
            echo "No PR context (env.CHANGE_BRANCH or env.CHANGE_TARGET is null). Skipping diff."
            currentBuild.description = "Skipped - Not a PR"
            currentBuild.result = 'SUCCESS'
            }
        }
    }

    if (hasChanges) {
        stage('Login to Quay') {
            sh '''
                echo "$QUAY_PASSWORD" | docker login quay.io -u "$QUAY_USERNAME" --password-stdin
            '''
        }

        stage('Run FossID Scan') {
            sh '''
                mkdir -p results
                docker pull quay.io/fossid/workbench-agent:0.4.2
                docker run --rm \
                    -v "$(pwd)/analyzed_code:/tmp/analyzed_code" \
                    -v "$(pwd)/results:/tmp/results" \
                    quay.io/fossid/workbench-agent:0.4.2 \
                    --api_url "https://eval-eu.foss.id/cs-demo/" \
                    --api_token "$API_TOKEN" \
                    --project_code "$PROJECT_CODE" \
                    --scan_code "$GIT_COMMIT" \
                    --blind_scan \
                    --path "/tmp/analyzed_code" \
                    --limit 1 \
                    --auto_identification_detect_declaration \
                    --auto_identification_detect_copyright \
                    --auto_identification_resolve_pending_ids \
                    --delta_only \
                    --path-result "/tmp/results/wb_result.json"
            '''
        }
    }
}