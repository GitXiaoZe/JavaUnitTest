# JavaUnitTest
Java单元测试

shell.sh的用法为:<br>
```
shell.sh src time-limit [classpath] 
```

src : 指定需要生成测试用例的java文件目录.<br>
time-limit : 用于使用开源的randoop生成测试用例的时间.<br>
[classpath] : 当源文件包含一些其他的库(非标准库)时，需要指定classpath，否则编译不通过.<br>
<br>
jar : 包含了randoop相关的jar包.<br>
<br>
Traversal.cpp : shell.sh会使用g++编译此文件，并且调用生成的程序来收集src指定的java文件对应的字节码文件, 并且生成一个
class.txt, txt文件作为randoop生成测试用例的--classlist的值<br>
<br>
pom.xml : 包含了junit, jacoco等插件，junit用于运行randoop生成的测试用例, jacoco根据测试用例的运行结果生成一个html文件，html文件
记录了测试用例对应的覆盖率，包括class, method, line等。还可以在pom.xml中添加关于复杂度等规则进行测试。


## 使用方法 :
1, 创建一个maven项目.<br>
2, 将要生成测试用例和测试的java文件放在src/main/java目录下，注意包的层次.<br>
3, 复制pom.xml, Traversal.cpp, shell.sh, jar到maven项目的根目录下.<br>
4, 执行shell.sh脚本, 就会创建src/main/test, 并且在该目录下生成测试用例.<br>
5, 执行mvn install test. 会生成target目录，并且进行测试.<br>
6, 在target/site/jacoco下生成index.html文件，使用浏览器就可以看到测试结果.<br>
