# C语言实现粗大误差数据处理

### 粗大误差
拉依达准则（3σ准则）：设对被测量进行等精度测量，独立得到x1，x2...,xn,算出其算术平均值x及剩余误差vi=xi-x（i=1,2，...,n）,并按贝塞尔公式算出标准偏差σ，若某个测量值xb的剩余误差vb（1<=b<=n）,满足下式
，|vb|=|xb-x|>3σ，则认为xb是含有粗大误差值的坏值，应予剔除。

### 标准偏差
贝塞尔公式：剩余误差的平方和除以n-1的差，再求其平方根，结果就是标准偏差
![image](https://user-images.githubusercontent.com/89961111/193377339-d9f1e784-2ac4-475a-b964-d448f1ac3416.png)
