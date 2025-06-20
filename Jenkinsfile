// Jenkinsfile - Scripted Pipeline version of your multi-stage declarative pipeline

node {
    docker.image('ubuntu:latest').inside {
        stage('FossIDDIFFPR'){

        // Set up environment variables using Jenkins credentials
        env.PROJECT_CODE = 'AgentTest1'
        env.API_URL = credentials('WB_User')
        env.API_TOKEN = credentials('WB_Token')
        env.QUAY_USERNAME = credentials('QuayLogin')
        env.QUAY_PASSWORD = credentials('Secret Text')

        // Checkout PR code
        checkout scm

        // Determine if there are any changed files
        def base = sh(script: "git merge-base origin/${env.CHANGE_TARGET} origin/${env.CHANGE_BRANCH}", returnStdout: true).trim()
        def changedFiles = sh(script: "git diff --name-only --diff-filter=d ${base} ${env.CHANGE_BRANCH}", returnStdout: true).trim()

        boolean hasChanges = false

        if (changedFiles == "") {
            currentBuild.description = "No file changes detected"
        } else {
            hasChanges = true
            sh "mkdir -p analyzed_code"
            changedFiles.split('\n').each { file ->
                def dir = "analyzed_code/" + file.take(file.lastIndexOf('/') + 1)
                sh "mkdir -p '${dir}'"
                sh "cp '${file}' 'analyzed_code/${file}'"
            }
        }

        if (hasChanges) {
            // Login to Quay
            sh """
                echo "$QUAY_PASSWORD" | docker login quay.io -u "$QUAY_USERNAME" --password-stdin
            """

            // Run the FossID delta scan
            sh """
                mkdir -p results
                docker pull quay.io/fossid/workbench-agent:0.4.2
                docker run --rm \
                    -v "\$(pwd)/analyzed_code:/tmp/analyzed_code" \
                    -v "\$(pwd)/results:/tmp/results" \
                    quay.io/fossid/workbench-agent:0.4.2 \
                    --api_url "$https://eval-eu.foss.id/cs-demo/" \
                    --api_token "$API_TOKEN" \
                    --project_code "$PROJECT_CODE" \
                    --scan_code "${env.GIT_COMMIT}" \
                    --blind_scan \
                    --path "/tmp/analyzed_code" \
                    --limit 1 \
                    --auto_identification_detect_declaration \
                    --auto_identification_detect_copyright \
                    --auto_identification_resolve_pending_ids \
                    --delta_only \
                    --path-result "/tmp/results/wb_result.json"
            """
        }
    }
}