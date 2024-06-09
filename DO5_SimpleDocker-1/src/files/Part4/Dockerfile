FROM nginx
WORKDIR /home/

COPY ./nginx.conf /etc/nginx/nginx.conf
COPY ./server.c .
COPY ./run.sh .

RUN apt-get update
RUN apt-get install -y gcc spawn-fcgi libfcgi-dev

USER nginx
ENTRYPOINT ["sh", "./run.sh"]
HEALTHCHECK NONE
