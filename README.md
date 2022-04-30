## 编译原理第二次作业——语法分析器

使用说明

1. 点击`Syntactic_analysis.exe` 运行

2. 在窗口输入想要进行词法分析的文件路径

   ```
   Please enter the path to the test file(Less than a hundred characters)
   D:\\大三下\\编译原理\\第一次作业\\demo.c
   ```

3. 在窗口输入输出文件保存路径

   ```
   Please enter the path to the output file(Less than a hundred characters)
   D:\\大三下\\编译原理\\第一次作业\\tokens.txt
   ```

   当文件存在时会询问您是否进行覆盖

   ```
   The file already exists. Whether to overwrite it
   Yes(1) /t NO(0)
   ```

   若不存在则会自动创建输出文件。

4. 接下来输入使用LL文法还是使用LR文法进行结果检验
   输入1 使用LL文法
   输入2 使用LR文法

5. 等待输出
