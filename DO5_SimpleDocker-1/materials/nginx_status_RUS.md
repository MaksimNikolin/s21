## Модуль ngx_http_stub_status_module

Модуль ngx_http_stub_status_module предоставляет доступ к базовой информации о состоянии сервера.

По умолчанию этот модуль не собирается, его сборку необходимо разрешить с помощью конфигурационного параметра *--with-http_stub_status_module*.

Пример конфигурации:
```
location = /basic_status {
    stub_status;
}
```

В данной конфигурации создаётся простая веб-страница с основной информацией о состоянии, которая может выглядеть следующим образом:
```
Active connections: 291
server accepts handled requests
 16630948 16630948 31070465
Reading: 6 Writing: 179 Waiting: 106
```
