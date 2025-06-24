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
            // Ensure all remote branches are fetched
            sh 'git fetch origin +refs/heads/*:refs/remotes/origin/*'

            def base = sh(
                script: "git merge-base origin/${env.CHANGE_TARGET} origin/${env.CHANGE_BRANCH}",
                returnStdout: true
            ).trim()

            def changedFiles = sh(
                script: "git diff --name-only --diff-filter=d ${base} origin/${env.CHANGE_BRANCH}",
                returnStdout: true
            ).trim()

            if (changedFiles) {
                echo "Changed files:\n${changedFiles}"
            } else {
                echo "No changes detected."
                currentBuild.description = "No file changes"
                currentBuild.result = 'SUCCESS'
            }
        } else {
            echo "Not a PR context, skipping diff."
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