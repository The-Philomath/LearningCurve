## About

A brief about Docker

----

* **Image** of an application is the set of dependent components, configurations and files which are required to run the application independently.

* **Container** is the image in execution.

* Out of the 3 layers hardware, kernel and application, a virtual machine virtualises 2 layers i.e. Kernel and Application.
But **Docker** virtualises only the application layer.

* A network of container is the one in which all the images can talk to each other. if two images are not part of a network they are simply isolated from each other.

#### Docker commands

Here is a brief list of commands which docker supports:

Pull a particular version of an image from the image directory.

    docker pull image:version

Pull the image if not present and then run it. If its already present then simply run the image. -d is to run it in detached mode.

    docker run -d image

To list down all the images present in the docker.

    docker images

To list down all the running containers. -a is for all, default it will show only running containers

    docker ps -a

Stop the running container with its ID

    docker stop containerID

Start the stopped container with its ID

    docker start containerID

Run an IMAGE_NAME with its run time name as NAME and its part of a network named as NET_NAME, with one environment variable SOME_ENV_VAR is provided with value as VALUE. PCPORT is mapped to CONT_PORT so that container can access the system files if required, like for dumping of logs.

    docker run -pPCPORT:CONT_PORT -e SOME_ENV_VAR=VALUE --name NAME --net NET_NAME IMAGE_NAME

Check the logs of container with its name or ID.

    docker logs containerID/name

Run a command in already running container with name or ID.

    docker exec -it containerID/name /bin/bash

List down all the networks

    docker network ls

create a network with name as NET_NAME

    docker network create NET_NAME

----

**Docker-Compose** is a simplified version of writing all of above commands in a yaml file.

After writing the commands in yaml file run it.

    docker-compose -f FILE_NAME.yaml up

Stop the yaml file execution.

    docker-compose -f FILE_NAME.yaml down
