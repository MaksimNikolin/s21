## Contents

Part 1. [Ready-made docker](#part-1-ready-made-docker) \
Part 2. [Operations with container](#part-2-operations-with-container) \
Part 3. [Mini web server](#part-3-mini-web-server) \
Part 4. [Your own docker](#part-4-your-own-docker) \
Part 5. [Dockle](#part-5-dockle) \
Part 6. [Basic Docker Compose](#part-6-basic-docker-compose)


## Part 1. Ready-made docker

As the final goal of your little practice you have immediately chosen to write a docker image for your own web server, so first you need to deal with a ready-made docker image for the server.
You chose a pretty simple **nginx**.

**== Task ==**

##### Take the official docker image from **nginx** and download it using `docker pull`.
![part1_1.jpg](screenshots/Part1/1_1.jpg)

##### Check for the docker image with `docker images`.
![part1_2.jpg](screenshots/Part1/1_2.jpg)

##### Run docker image with `docker run -d [image_id|repository]`.
##### Check that the image is running with `docker ps`.
![part1_3.jpg](screenshots/Part1/1_3.jpg)

##### View container information with `docker inspect [container_id|container_name]`.
![part1_4.jpg](screenshots/Part1/1_4.jpg)

##### From the command output define and write in the report the container size, list of mapped ports and container ip.
![part1_5.jpg](screenshots/Part1/1_5.jpg)

##### Stop docker image with `docker stop [container_id|container_name]`.
![part1_6.jpg](screenshots/Part1/1_6.jpg)

##### Check that the image has stopped with `docker ps`.
![part1_7.jpg](screenshots/Part1/1_7.jpg)

##### Run docker with ports 80 and 443 in container, mapped to the same ports on the local machine, with *run* command.
![part1_8.jpg](screenshots/Part1/1_8.jpg)
![part1_9.jpg](screenshots/Part1/1_9.jpg)

##### Check that the **nginx** start page is available in the browser at *localhost:80*.
![part1_10.jpg](screenshots/Part1/1_10.jpg)

##### Restart docker container with `docker restart [container_id|container_name]`.
##### Check in any way that the container is running.
![part1_11.jpg](screenshots/Part1/1_11.jpg)


## Part 2. Operations with container

Docker image and container are ready. Now we can look into **nginx** configuration and display page status.

**== Task ==**

##### Read the *nginx.conf* configuration file inside the docker container with the *exec* command.
![part2_1.jpg](screenshots/Part2/2_1.jpg)

##### Create a *nginx.conf* file on a local machine.
##### Configure it on the */status* path to return the **nginx** server status page.
![part2_2.jpg](screenshots/Part2/2_2.jpg)

##### Copy the created *nginx.conf* file inside the docker image using the `docker cp` command.
![part2_3.jpg](screenshots/Part2/2_3.jpg)

##### Restart **nginx** inside the docker image with *exec*.
![part2_4.jpg](screenshots/Part2/2_4.jpg)

##### Check that *localhost:80/status* returns the **nginx** server status page.
![part2_5.jpg](screenshots/Part2/2_5.jpg)

##### Export the container to a *container.tar* file with the *export* command.
##### Stop the container.
![part2_6.jpg](screenshots/Part2/2_6.jpg)

##### Delete the image with `docker rmi [image_id|repository]`without removing the container first.
![part2_7.jpg](screenshots/Part2/2_7.jpg)

##### Delete stopped container.
![part2_8.jpg](screenshots/Part2/2_8.jpg)

##### Import the container back using the *import*command.
##### Run the imported container.
![part2_9.jpg](screenshots/Part2/2_9.jpg)

##### Check that *localhost:80/status* returns the **nginx** server status page.
![part2_11.jpg](screenshots/Part2/2_10.jpg)


## Part 3. Mini web server

It's time to take a little break from the docker to prepare for the last stage. It's time to write your own server.

**== Task ==**

##### Write a mini server in **C** and **FastCgi** that will return a simple page saying `Hello World!`.
![part3_1.jpg](screenshots/Part3/3_1.jpg)

##### Write your own *nginx.conf* that will proxy all requests from port 81 to *127.0.0.1:8080*.
![part3_3.jpg](screenshots/Part3/3_3.jpg)
![part3_4.jpg](screenshots/Part3/3_4.jpg)

##### Put the *nginx.conf* file under *./nginx/nginx.conf* (you will need this later).
![part3_5.jpg](screenshots/Part3/3_5.jpg)

##### Run the written mini server via *spawn-fcgi* on port 8080.
![part3_2.jpg](screenshots/Part3/3_2.jpg)

##### Check that browser on *localhost:81* returns the page you wrote.
![part3_6.jpg](screenshots/Part3/3_6.jpg)


## Part 4. Your own docker

Now everything is ready. You can start writing the docker image for the created server.

**== Task ==**

*When writing a docker image avoid multiple calls of RUN instructions*

#### Write your own docker image that:
##### 1) builds mini server sources on FastCgi from [Part 3](#part-3-mini- web-server);
##### 2) runs it on port 8080;
##### 3) copies inside the image written *./nginx/nginx.conf*;
##### 4) runs **nginx**.
_**nginx** can be installed inside the docker itself, or you can use a ready-made image with **nginx** as base._
![part4_1.jpg](screenshots/Part4/4_1.jpg)
![part4_2.jpg](screenshots/Part4/4_2.jpg)

##### Build the written docker image with `docker build`, specifying the name and tag.
![part4_3.jpg](screenshots/Part4/4_3.jpg)

##### Check with `docker images` that everything is built correctly.
![part4_4.jpg](screenshots/Part4/4_4.jpg)

##### Run the built docker image by mapping port 81 to 80 on the local machine and mapping the *./nginx* folder inside the container to the address where the **nginx** configuration files are located (see [Part 2](#part-2-operations-with-container)).
![part4_4.jpg](screenshots/Part4/4_4.jpg)

##### Check that the page of the written mini server is available on localhost:80.
![part4_5.jpg](screenshots/Part4/4_5.jpg)

##### Add proxying of */status* page in *./nginx/nginx.conf* to return the **nginx** server status.
![part4_6.jpg](screenshots/Part4/4_6.jpg)

##### Restart docker image.
![part4_7.jpg](screenshots/Part4/4_7.jpg)

*If everything is done correctly, after saving the file and restarting the container, the configuration file inside the docker image should update itself without any extra steps
##### Check that *localhost:80/status* now returns a page with **nginx** status.
![part4_8.jpg](screenshots/Part4/4_8.jpg)

## Part 5. **Dockle**

Once you've written the image, it's never a bad idea to check it for security.

**== Task ==**

##### Check the image from the previous task with `dockle [image_id|repository]`.
![part5_1.jpg](screenshots/Part5/5_1.jpg)

##### Fix the image so that there are no errors or warnings when checking with **dockle**.
![part5_2.jpg](screenshots/Part5/5_2.jpg)

## Part 6. Basic **Docker Compose**

There, you've finished your warm-up. Wait a minute though...
Why not try experimenting with deploying a project consisting of several docker images at once?

**== Task ==**

##### Write a *docker-compose.yml* file, using which:
##### 1) Start the docker container from [Part 5](#part-5-dockle) _(it must work on local network, i.e., you don't need to use **EXPOSE** instruction and map ports to local machine)_.
##### 2) Start the docker container with **nginx** which will proxy all requests from port 8080 to port 81 of the first container.
##### Map port 8080 of the second container to port 80 of the local machine.
##### Stop all running containers.
##### Build and run the project with the `docker-compose build` and `docker-compose up` commands.
![part6_1.jpg](screenshots/Part6/6_1.jpg)

##### Check that the browser returns the page you wrote on *localhost:80* as before.
![part6_2.jpg](screenshots/Part6/6_2.jpg)
