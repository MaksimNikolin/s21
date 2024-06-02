## Запуск программы на **C** с использованием **FastCGI** и **nginx**.

С помощью API, предоставляемого заголовкочным файлом <fcgiapp.h>, можно указать информацию о сокете.

Пример получения файлового дескриптора TCP-сокета:
`int sockfd = FCGX_OpenSocket("127.0.0.1:9000", 100);`

...или используя Unix-сокеты:
`int sockfd = FCGX_OpenSocket("/var/run/fcgi.sock", 100);`

С полученным сокетом можно написать следующее: 
```c
FCGX_Request req;
FCGX_InitRequest(&req, sockfd, 0);

while (FCGX_Accept_r(&req) >= 0) {
  FCGX_FPrintF(req.out, "Content-Type: text/html\n\n");
  FCGX_FPrintF(req.out, "hello world");
  FCGX_Finish_r(&req);
}
```

После компиляции бинарный файл может быть запущен напрямую без использования *spawn-fcgi* or *cgi-fcgi*.
