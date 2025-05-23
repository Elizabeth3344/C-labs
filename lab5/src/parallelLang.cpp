#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>
#include <memory>
#include <sstream>
#include <ctime>
#include <atomic>

using namespace std;
using namespace std::chrono;

mutex console_mutex;
atomic<int> thread_counter(0);

// Базовый класс для команд
class Command
{
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};

// Команда вывода в консоль
class PrintCommand : public Command
{
    string message;

public:
    PrintCommand(const string &msg) : message(msg) {}
    void execute() override
    {
        lock_guard<mutex> lock(console_mutex);
        cout << message << endl;
    }
};

// Команда вывода в файл (добавление)
class FileAppendCommand : public Command
{
    string filename;
    string content;

public:
    FileAppendCommand(const string &fn, const string &cnt)
        : filename(fn), content(cnt) {}
    void execute() override
    {
        ofstream file(filename, ios::app);
        if (file)
        {
            file << content << endl;
        }
        else
        {
            lock_guard<mutex> lock(console_mutex);
            cerr << "Error opening file: " << filename << endl;
        }
    }
};

// Команда арифметической операции
class ArithmeticCommand : public Command
{
    char op;
    double a, b;

public:
    ArithmeticCommand(char operation, double x, double y)
        : op(operation), a(x), b(y) {}
    void execute() override
    {
        double result = 0;
        switch (op)
        {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            result = b != 0 ? a / b : 0;
            break;
        }
        lock_guard<mutex> lock(console_mutex);
        cout << a << " " << op << " " << b << " = " << result << endl;
    }
};

// Команда счетного цикла
class ForLoopCommand : public Command
{
    int start, end, step;
    vector<shared_ptr<Command>> commands;

public:
    ForLoopCommand(int s, int e, int st) : start(s), end(e), step(st) {}
    void addCommand(shared_ptr<Command> cmd)
    {
        commands.push_back(cmd);
    }
    void execute() override
    {
        for (int i = start; i <= end; i += step)
        {
            for (auto &cmd : commands)
            {
                cmd->execute();
            }
        }
    }
};

// Функция для парсинга и выполнения команд в потоке
void executeCommands(const vector<string> &commandLines, int lineNum)
{
    int thread_id = ++thread_counter;
    auto start_time = system_clock::now();
    time_t start_time_t = system_clock::to_time_t(start_time);

    {
        lock_guard<mutex> lock(console_mutex);
        cout << "Thread for line " << lineNum << " (ID: " << thread_id
             << ") started at: " << ctime(&start_time_t);
    }

    vector<shared_ptr<Command>> commands;
    shared_ptr<ForLoopCommand> currentLoop;

    for (const auto &line : commandLines)
    {
        istringstream iss(line);
        string cmd;
        iss >> cmd;

        if (cmd == "print")
        {
            string message;
            getline(iss, message);
            if (currentLoop)
            {
                currentLoop->addCommand(make_shared<PrintCommand>(message));
            }
            else
            {
                commands.push_back(make_shared<PrintCommand>(message));
            }
        }
        else if (cmd == "fileappend")
        {
            string filename, content;
            iss >> filename;
            getline(iss, content);
            if (currentLoop)
            {
                currentLoop->addCommand(make_shared<FileAppendCommand>(filename, content));
            }
            else
            {
                commands.push_back(make_shared<FileAppendCommand>(filename, content));
            }
        }
        else if (cmd == "arith")
        {
            char op;
            double a, b;
            iss >> a >> op >> b;
            if (currentLoop)
            {
                currentLoop->addCommand(make_shared<ArithmeticCommand>(op, a, b));
            }
            else
            {
                commands.push_back(make_shared<ArithmeticCommand>(op, a, b));
            }
        }
        else if (cmd == "for")
        {
            int start, end, step = 1;
            iss >> start >> end;
            if (!iss.eof())
                iss >> step;
            currentLoop = make_shared<ForLoopCommand>(start, end, step);
        }
        else if (cmd == "endfor")
        {
            if (currentLoop)
            {
                commands.push_back(currentLoop);
                currentLoop.reset();
            }
        }
    }

    // Выполнение всех команд
    for (auto &cmd : commands)
    {
        cmd->execute();
    }

    auto end_time = system_clock::now();
    time_t end_time_t = system_clock::to_time_t(end_time);
    duration<double> elapsed = end_time - start_time;

    {
        lock_guard<mutex> lock(console_mutex);
        cout << "Thread for line " << lineNum << " (ID: " << thread_id
             << ") finished at: " << ctime(&end_time_t)
             << "Execution time: " << elapsed.count() << " seconds\n";
    }
}

int main()
{
    vector<vector<string>> commandBlocks;
    vector<string> currentBlock;
    string line;

    cout << "Enter commands (type 'run' to execute, 'exit' to quit):\n";

    while (true)
    {
        getline(cin, line);
        if (line == "run")
        {
            if (!currentBlock.empty())
            {
                commandBlocks.push_back(currentBlock);
                currentBlock.clear();
            }
            break;
        }
        else if (line == "exit")
        {
            return 0;
        }
        else if (!line.empty())
        {
            currentBlock.push_back(line);
        }
    }

    vector<thread> threads;
    for (size_t i = 0; i < commandBlocks.size(); ++i)
    {
        threads.emplace_back(executeCommands, commandBlocks[i], i + 1);
    }

    for (auto &t : threads)
    {
        t.join();
    }

    return 0;
}