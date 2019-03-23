## HttpSourceViewer
本项目来源于BiliBil视频网站，[Visual C++网络项目实战视频教程](https://www.bilibili.com/video/av23724274/)，十分感谢[初心不忘誓言封存](https://space.bilibili.com/22046211?spm_id_from=333.788.b_765f7570696e666f.2)的分享。
作者是Jhkdiy老师，可以参见他的[jhkdiy的CSDN博客](https://blog.csdn.net/jhkdiy)、
[jhkdiy的博客园](https://www.cnblogs.com/jhkdiy/)、
[VC黑客编程实战视频-破解网吧电影下载](https://www.cnblogs.com/jhkdiy/p/3363708.html)

### 1、HttpSourceViewer是一个使用Visual Studio2013创建的基于MFC的对话框应用程序，分析一个HTML网页，获取HTML头和内容，并对获取的HTML内容使用正则表达式(Boost库或ATL库)和常规搜索。

### 2、使用的技术：
#### (1)Winhttp库
WinHttpClient.h，可参考[ThirdParty/ATLRegExp/
](https://github.com/ccf19881030/HttpSourceViewer/tree/master/HttpSourceViewer/HttpSourceViewer/ThirdParty/ATLRegExp)目录下的源代码，
对Windows的Winhttp库进行C++封装，来源于CodeProject网站shicheng的C++库。
##### I、 [A Fully Featured Windows HTTP Wrapper in C++](https://www.codeprojec的om/Articles/66625/A-Fully-Featured-Windows-HTTP-Wrapper-in-C) .
##### II、 [A Simple Windows HTTP Wrapper Using C++](https://www.codeproject.com/Articles/28275/A-Simple-Windows-HTTP-Wrapper-Using-C).
#### (2)VC++ RichEdit控件的使用
#### (3)正则表达式
##### 使用boost::xpressive库
可参见[Boost库官网](https://www.boost.org/)

##### 使用ATL库

### 3、HttpSourceViewer 1.0.0.1 绿色版 软件介绍：
HttpSourceViewer是一款免费的网页html源码查看工具，通过这款软件你可以直接获取一个页面的html源码，包括html头及页面的html内容。HttpSourceViewer还支持源码提取，可以保存到本地,用原始的Http协议请求URL，获取服务器返回的html源代码,用户可以在html源代码中搜索自己感兴趣的信息。
#### (1)、HttpSourceViewer 1.0.0.1 绿色版下载
[HttpSourceViewer CSDN下载](https://download.csdn.net/download/nmgwddj/9474236)
[太平洋下载](https://dl.pconline.com.cn/download/2309623.html)
[西西软件园下载](https://www.cr173.com/soft/748168.html)

#### （2）、功能介绍：
1：全绿色，单文件，无需安装，解压即可运行。
2：支持正则表达式搜索html内容。
3：支持使用Boost库的正则表达式语法，ATL正则表达式语法。
4：使用正则表达式搜索内容后，可直接提取搜索内容。
5：直接调用迅雷进行下载，一步到位。

#### (3)、视频介绍：
相关视频见BiliBil视频网站，[Visual C++网络项目实战视频教程](https://www.bilibili.com/video/av23724274/)。



