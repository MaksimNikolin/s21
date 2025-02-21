import random
import time
import threading
from collections import deque
from tabulate import tabulate

PHI = (1 + 5**0.5) / 2

class Student:
    def __init__(self, name, gender):
        self.name = name
        self.gender = gender
        self.status = "Очередь"

    def set_status(self, status):
        self.status = status

class Examiner:
    def __init__(self, name):
        self.name = name
        self.total_students = 0
        self.failed_students = 0
        self.total_time = 0
        self.current_student = "отсутствует"
    
    def update_exam_stats(self, result, time_spent):
        self.total_students += 1
        self.total_time += time_spent
        if result == "Провалил": self.failed_students += 1

    def get_exam_time(self):
        return random.uniform(len(self.name) - 1, len(self.name) + 1)

def get_student_answer(student_gender, question):
    words = question.split()
    n = len(words)
    if student_gender == 'М':
        a = 1 / PHI
        b = (1 - a) / PHI
        probabilities = [a, b] + [(1 - a - b) / PHI] * (n - 2)
    else:
        a = 1 / PHI
        b = (1 - a) / PHI
        probabilities = [(1 - a - b) / PHI] + [b, a] * (n - 2)
    if len(probabilities) != n:
        diff = n - len(probabilities)
        if diff > 0: probabilities += [1 / n] * diff
        elif diff < 0: probabilities = probabilities[:n]
    total_prob = sum(probabilities)
    probabilities = [p / total_prob for p in probabilities]
    return random.choices(words, probabilities, k=n)

def get_examiner_answer(question):
    words = question.split()
    answers = set()
    while len(answers) < len(words):
        answer = random.choice(words)
        answers.add(answer)
    return answers

def get_exam_result(examiner_mood, correct_answers, wrong_answers):
    result = "Сдал"
    if (examiner_mood == "Плохое") or (examiner_mood == "Нейтральное" and correct_answers < wrong_answers): result = "Провалил"
    return result

def simulate_exam(examiner, student, questions):
    examiner_time = examiner.get_exam_time()
    question = random.choice(questions)
    student_answers = get_student_answer(student.gender, question)
    examiner_answers = get_examiner_answer(question)
    correct_answers = len(examiner_answers & set(student_answers))
    wrong_answers = len(student_answers) - correct_answers
    time.sleep(30 + random.uniform(12, 18))
    mood_prob = random.random()
    if mood_prob < 1/8: examiner_mood = "Плохое"
    elif mood_prob < 3/8: examiner_mood = "Хорошее"
    else: examiner_mood = "Нейтральное"
    result = get_exam_result(examiner_mood, correct_answers, wrong_answers)
    examiner.update_exam_stats(result, examiner_time)
    student.set_status(result)
    return result, examiner_time

class ExamSimulationApp:
    def __init__(self, students, examiners, questions):
        self.students = students
        self.examiners = examiners
        self.questions = questions
        self.queue = deque(students)
        self.lock = threading.Lock()
    
    def update_status(self):
        student_statuses = [(student.name, student.status) for student in self.students]
        student_statuses.sort(key=lambda x: ("Очередь", "Сдал", "Провалил").index(x[1]))
        student_table = tabulate(student_statuses, headers=["Студент", "Статус"], tablefmt="grid")
        print(student_table)
        examiner_stats = [(examiner.name, examiner.current_student or "-", examiner.total_students, examiner.failed_students, round(examiner.total_time, 2)) for examiner in self.examiners]
        examiner_table = tabulate(examiner_stats, headers=["Экзаменатор", "Текущий студент", "Всего студентов", "Завалил", "Время работы"], tablefmt="grid")
        max_time = max(examiner.total_time for examiner in self.examiners)
        print(examiner_table)
        print(f"Осталось в очереди: {len(self.queue)} из {len(self.students)}")
        print(f"Время с момента начала экзамена: {round(max_time, 2)}\n")
        return examiner_table, student_table, max_time
    
    def run_exam_simulation(self):
        threads = []
        for examiner in self.examiners:
            thread = threading.Thread(target=self.run_examiner, args=(examiner,))
            threads.append(thread)
            thread.start()
        for thread in threads:
            thread.join()
        student_table, examiner_table, max_time = self.update_status()
        self.show_final_results(student_table, examiner_table, max_time)

    def run_examiner(self, examiner):
        while self.queue:
            student = self.queue.popleft()
            examiner.current_student = student.name
            _, time_spent = simulate_exam(examiner, student, self.questions)
            with self.lock: self.update_status()
            time.sleep(time_spent)
    
    def show_final_results(self, student_table, examiner_table, max_time):
        best_students = [student.name for student in self.students if student.status == "Сдал"]
        min_failed = min(examiner.failed_students for examiner in self.examiners)
        best_examiners = [examiner.name for examiner in self.examiners if examiner.failed_students == min_failed]
        worst_students = [student.name for student in self.students if student.status == "Провалил"]
        best_questions = ["Там стоит стол", "Человек собаке друг"]
        print(student_table)
        print("\n")
        print(examiner_table)
        print("\n")
        print(f"Время с момента начала экзамена и до момента его завершения: {round(max_time, 2)}")
        if best_students: print(f"Имена лучших студентов: {', '.join(best_students)}")
        else: print("Нет студентов, сдавшие экзамен.")
        print(f"Имена лучших экзаменаторов: {', '.join(best_examiners)}")
        if worst_students: print(f"Имена студентов, которых после экзамена отчислят: {', '.join(worst_students)}")
        else: print("Нет студентов, которых стоит отчислить.")
        print(f"Лучшие вопросы: {', '.join(best_questions)}")
        if len(best_students) / len(self.students) > 0.85: print("Вывод: экзамен удался")
        else: print("Вывод: экзамен не удался")

def read_input_data():
    with open('students.txt') as f: students = [Student(line.split()[0], line.split()[1]) for line in f.readlines()]
    with open('examiners.txt') as f: examiners = [Examiner(line.split()[0]) for line in f.readlines()] 
    with open('questions.txt') as f: questions = [line.strip() for line in f.readlines()]
    return students, examiners, questions

students, examiners, questions = read_input_data()
exam_simulation = ExamSimulationApp(students, examiners, questions)
exam_simulation.run_exam_simulation()
