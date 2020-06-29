#include <iostream>
#include <string>
#include <tuple>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
  NEW,          // новая
  IN_PROGRESS,  // в разработке
  TESTING,      // на тестировании
  DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
  // Получить статистику по статусам задач конкретного разработчика
  const TasksInfo& GetPersonTasksInfo(const string& person) const;
  
  // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
  void AddNewTask(const string& person);
  
  // Обновить статусы по данному количеству задач конкретного разработчика,
  // подробности см. ниже
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(
    const string& person, int task_count);

private:
  map<string, TasksInfo> TASKS;

  // Чтобы каждый раз не писать static_cast<TaskStatus>
  TaskStatus Cast(const int& value) {
    if (value >= 0 && value <= 4) {
      return static_cast<TaskStatus>(value);
    } else {
      throw runtime_error("dumb");
    }
  }
};

const TasksInfo& TeamTasks::GetPersonTasksInfo(const string& person) const {
  return TASKS.at(person);
}

void TeamTasks::AddNewTask(const string& person) {
  TASKS[person][TaskStatus::NEW]++;
}

tuple<TasksInfo, TasksInfo> TeamTasks::PerformPersonTasks(
  const string& person, int task_count) {
  TasksInfo updated_TaskInfo, old_TaskInfo;

  // Если вдруг чувака нет в списке
  if (TASKS.count(person) == 0) {
    return make_tuple(updated_TaskInfo, old_TaskInfo);
  }

  old_TaskInfo = TASKS[person];

  for (int item = 0; item < 3 && task_count != 0; item++) {
    if (TASKS[person].count(Cast(item)) != 0) {
      // Создаем список обновленных задач (2 строки)
      updated_TaskInfo[Cast(item + 1)] = min(task_count, TASKS[person][Cast(item)]);
      task_count -= updated_TaskInfo[Cast(item + 1)];
      // Убираем выполненные задачи из старого списка
      old_TaskInfo[Cast(item)] -= updated_TaskInfo[Cast(item + 1)];
      // Избавляемся от нулей
      if (old_TaskInfo[Cast(item)] == 0) {
        old_TaskInfo.erase(Cast(item));
      }
    }
  }

  // Обновляем данные у чувака, сначала все очистим
  TASKS[person].clear();
  // Занесем в список сделанные задачи из старых
  if (old_TaskInfo.count(TaskStatus::DONE) != 0) {
    TASKS[person][TaskStatus::DONE] = old_TaskInfo[TaskStatus::DONE];
    // Удаляем выполненные задачи из старых (по условию)
    old_TaskInfo.erase(TaskStatus::DONE);
  }

  // Заносим инфу об остальных статусах
  for (int item = 0; item < 3; item++) {
    if (old_TaskInfo.count(Cast(item)) != 0) {
      TASKS[person][Cast(item)] = old_TaskInfo[Cast(item)];
    }
    if (updated_TaskInfo.count(Cast(item)) != 0) {
      TASKS[person][Cast(item)] += updated_TaskInfo[Cast(item)];
    }
  }

  // Занесем в список сделанные задачи из обновленных
  if (updated_TaskInfo.count(TaskStatus::DONE) != 0) {
    TASKS[person][TaskStatus::DONE] += updated_TaskInfo[TaskStatus::DONE];
  }

  // Возвращаем обновленные задачи и старые без выполненных
  return make_tuple(updated_TaskInfo, old_TaskInfo);
}

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
  cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
      ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
      ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
      ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
  TeamTasks tasks;
  tasks.AddNewTask("Ilia");
  for (int i = 0; i < 3; ++i) {
    tasks.AddNewTask("Ivan");
  }
  cout << "Ilia's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
  cout << "Ivan's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
  
  TasksInfo updated_tasks, untouched_tasks;
  
  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);
  
  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);

  return 0;
}