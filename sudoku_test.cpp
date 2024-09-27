#include <cassert>
#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>

#include "sudoku.cpp"

bool isValidSudoku(const Sudoku& sudoku) {
    for (int i = 0; i < 9; ++i) {
        std::unordered_set<int> rowSet, colSet, boxSet;
        for (int j = 0; j < 9; ++j) {
            // 检查行
            int rowValue = sudoku.getGridValue(i, j);
            if (rowValue != 0 && !rowSet.insert(rowValue).second) {
                return false;
            }
            // 检查列
            int colValue = sudoku.getGridValue(j, i);
            if (colValue != 0 && !colSet.insert(colValue).second) {
                return false;
            }
            // 检查3x3方块
            int boxRow = 3 * (i / 3), boxCol = 3 * (i % 3);
            int boxValue = sudoku.getGridValue(boxRow + j / 3, boxCol + j % 3);
            if (boxValue != 0 && !boxSet.insert(boxValue).second) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    // 测试数据
    std::vector<std::string> testInputs = {
        "017903600000080000900000507072010430000402070064370250701000065000030000005601720",
        "530070000600195000098000060800060003400000100000168000000000000000000000000000000",
        "000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    };

    for (size_t i = 0; i < testInputs.size(); ++i) {
        Sudoku sudoku(testInputs[i]);
        sudoku.getInference();
        sudoku.print();
        if(sudoku.hasValidSolution){
            assert(isValidSudoku(sudoku)); // 验证数独规则
        }
    }

    return 0;
}
