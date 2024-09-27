class Grid:
    def __init__(self, size):
        # 构造函数，初始化网格大小和数据
        self.size_ = size
        self.data_ = [[0] * size for _ in range(size)]

    # 设置网格中的值
    def setValue(self, row, col, value):
        self.data_[row][col] = value

    # 获取网格中的值
    def getValue(self, row, col):
        return self.data_[row][col]

    # 获取网格的大小
    def getSize(self):
        return self.size_

    # 检查给定的值是否可以在指定位置放置
    def isValid(self, row, col, value):
        # 检查行和列
        for i in range(self.size_):
            if self.data_[row][i] == value or self.data_[i][col] == value:
                return False

        # 检查3x3方块
        boxRow = row - row % 3
        boxCol = col - col % 3
        for i in range(3):
            for j in range(3):
                if self.data_[boxRow + i][boxCol + j] == value:
                    return False

        return True


class Sudoku:
    def __init__(self, input):
        self.hasValidSolution = True
        self.grid_ = Grid(9)
        self.parse(input)

    # 克隆方法，返回新对象的副本
    def clone(self):
        newSudoku = Sudoku("")  # 创建一个新的Sudoku对象
        newSudoku.hasValidSolution = self.hasValidSolution  # 复制hasValidSolution
        for i in range(9):
            for j in range(9):
                newSudoku.grid_.setValue(i, j, self.grid_.getValue(i, j))  # 深度复制网格
        return newSudoku

    # 解析输入字符串，初始化数独游戏
    def parse(self, input):
        if len(input) != 81:
            raise ValueError("输入字符串长度必须为81")
        for c in input:
            if c < '0' or c > '9':
                raise ValueError("输入字符串只能包含0-9的数字")
        index = 0
        for i in range(9):
            for j in range(9):
                self.grid_.setValue(i, j, int(input[index]))
                index += 1

    # 根据已知信息进行推理，尝试填充空格
    def getInference(self):
        if not self.dfs(0, 0):
            self.hasValidSolution = False  # 修改标志
            print("no valid solution")  # 输出提示

    # 使用深度优先搜索（DFS）填充空格
    def dfs(self, row, col):
        if row == 9:
            return True
        if col == 9:
            return self.dfs(row + 1, 0)
        if self.grid_.getValue(row, col) != 0:
            return self.dfs(row, col + 1)
        candidates = self.getCandidates(row, col)
        for candidate in candidates:
            self.grid_.setValue(row, col, candidate)
            if self.dfs(row, col + 1):
                return True
            self.grid_.setValue(row, col, 0)
        return False

    # 获取指定位置的候选数
    def getCandidates(self, row, col):
        candidates = []
        for i in range(1, 10):
            if self.grid_.isValid(row, col, i):
                candidates.append(i)
        return candidates

    # 打印数独游戏的当前状态
    def print(self):
        for i in range(9):
            for j in range(9):
                print(self.grid_.getValue(i, j), end=" ")
            print()

    # 允许其他类成员获取grid中的数值
    def getGridValue(self, row, col):
        return self.grid_.getValue(row, col)

def main():
    test_input = "017903600000080000900000507072010430000402070064370250701000065000030000005601720"
    sudoku = Sudoku(test_input)
    sudoku.getInference()
    sudoku.print()
    if sudoku.hasValidSolution:
        print("有解")
    else:
        print("无解")

if __name__ == "__main__":
    main()
