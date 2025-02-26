#!/bin/bash

# Check if the hostPath argument is provided
if [ -z "$1" ]; then
  echo "Usage: $0 <Project dir> <Executable>"
  exit 1
fi

projectDir=$1

# Check if the provided path exists
if [ ! -d "$projectDir" ]; then
  echo "Error: The provided path ($projectDir) does not exist."
  exit 1
fi

piUserName=team02
piIpAddress=10.21.221.71
piPath=/home/team02
piPass=seameteam2

echo "build docker image to build app"
docker build -f ./JetsonNano/deploy/dockerfiles/DockerfileDeployJetson \
    --build-arg projectDir=/$projectDir \
    -t final-app .
echo "Remove tmpapp container if it is exist"
docker rm -f tmpapp
echo "Create a tmp container to copy binary"
docker create --name tmpapp final-app
echo "Copy the binary from tmp container"
docker cp tmpapp:/home/$projectDir/VehicleSystem ./VehicleSystem
docker cp tmpapp:/home/$projectDir/XboxController ./XboxController
echo "Send binary to rasp over scp"
sshpass -p "$piPass" scp VehicleSystem XboxController "$piUserName"@"$piIpAddress":"$piPath"
