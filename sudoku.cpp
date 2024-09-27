#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class Grid {
public:
    // 构造函数，初始化网格大小和数据
    Grid(int size) : size_(size), data_(size_, std::vector<int>(size_, 0)) {}

    // 设置网格中的值
    void setValue(int row, int col, int value) {
        data_[row][col] = value;
    }

    // 获取网格中的值
    int getValue(int row, int col) const {
        return data_[row][col];
    }

    // 获取网格的大小
    int getSize() const {
        return size_;
    }

    // 检查给定的值是否可以在指定位置放置
    bool isValid(int row, int col, int value) const {
        // Check row and column
        for (int i = 0; i < size_; ++i) {
            if (data_[row][i] == value || data_[i][col] == value) {
                return false;
            }
        }

        // Check 3x3 box
        int boxRow = row - row % 3;
        int boxCol = col - col % 3;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (data_[boxRow + i][boxCol + j] == value) {
                    return false;
                }
            }
        }

        return true;
    }

private:
    int size_;
    std::vector<std::vector<int>> data_;
};

class Sudoku {
public:
    bool hasValidSolution = true;

    // 构造函数，初始化数独游戏
    Sudoku(const std::string& input) : grid_(9) {
        parse(input);
    }

    // 克隆方法，返回新对象的副本
    Sudoku clone() const {
        Sudoku newSudoku(""); // 创建一个新的Sudoku对象
        newSudoku.hasValidSolution = this->hasValidSolution; // 复制hasValidSolution
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                newSudoku.grid_.setValue(i, j, this->grid_.getValue(i, j)); // 深度复制网格
            }
        }
        return newSudoku;
    }

    // 解析输入字符串，初始化数独游戏
    void parse(const std::string& input) {
        if (input.length() != 81) {
            throw std::invalid_argument("输入字符串长度必须为81");
        }
        for (char c : input) {
            if (c < '0' || c > '9') {
                throw std::invalid_argument("输入字符串只能包含0-9的数字");
            }
        }
        int index = 0;
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                grid_.setValue(i, j, input[index++] - '0');
            }
        }
    }

    // 根据已知信息进行推理，尝试填充空格
    void getInference() {
        if (!dfs(0, 0)) {
            hasValidSolution = false; // 修改标志
            std::cout << "no valid solution" << std::endl; // 输出提示
        }
    }

    // 使用深度优先搜索（DFS）填充空格
    bool dfs(int row, int col) {
        if (row == 9) {
            return true;
        }
        if (col == 9) {
            return dfs(row + 1, 0);
        }
        if (grid_.getValue(row, col) != 0) {
            return dfs(row, col + 1);
        }
        std::vector<int> candidates = getCandidates(row, col);
        for (int candidate : candidates) {
            grid_.setValue(row, col, candidate);
            if (dfs(row, col + 1)) {
                return true;
            }
            grid_.setValue(row, col, 0);
        }
        return false;
    }

    // 获取指定位置的候选数
    std::vector<int> getCandidates(int row, int col) const {
        std::vector<int> candidates;
        for (int i = 1; i <= 9; ++i) {
            if (grid_.isValid(row, col, i)) {
                candidates.push_back(i);
            }
        }
        return candidates;
    }

    // 打印数独游戏的当前状态
    void print() const {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                std::cout << grid_.getValue(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }

    // 允许其他类成员获取grid中的数值
    int getGridValue(int row, int col) const {
        return grid_.getValue(row, col);
    }

private:
    Grid grid_;
};
