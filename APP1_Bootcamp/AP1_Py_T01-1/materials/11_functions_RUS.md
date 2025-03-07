# Функции

Функция - это блок кода, который имеет имя, принимает аргументы (входные данные), выполняет определенную задачу и, возможно, возвращает результат.
Функции позволяют организовывать код, делать его более читаемым, и избегать дублирования кода.

```python
def приветствие(имя):
    """Функция, которая приветствует по имени."""
    print(f"Привет, {имя}!")


# Использование функции
приветствие("Анна")
```

Рекурсия - это концепция, когда функция вызывает саму себя. Рекурсия обычно используется для решения задач,
которые могут быть разбиты на более мелкие подзадачи. Например, рекурсивно можно посчитать факториал некоторого числа n.
Факториал числа n - это произведение всех целых чисел от 1 до n.

```python
def факториал(n):
    """Рекурсивная функция для вычисления факториала числа."""
    if n == 0 or n == 1:
        return 1
    else:
        return n * факториал(n - 1)


# Использование функции
результат = факториал(5)
print(результат)
```

При использовании рекурсии важно предусмотреть базовый случай (в данном примере, когда n равно 0 или 1),
чтобы избежать бесконечного вызова функции.

Также важно учитывать, что глубина рекурсии в Python ограничена. Это ограничение можно менять,
используя функцию `setrecursionlimit()` из стандартной библиотеки `sys`, однако так делают только в крайних случаях,
поскольку это совершенно небезопасно, и по возможности используют итеративные алгоритмы.
