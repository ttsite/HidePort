# HidePort
Hide Port In Windows

功能：在Windows上隐藏端口。  
说明：端口主要是指侦听状态的本地端口。其实还可以隐藏远端的IPv4/6, 甚至基于进程的隐藏网络信息。  
隐藏：主要是指通过常规的手法的隐藏，对于暴力搜索（如：句柄），协议（或流量）分析的手法例外。  

隐藏端口是一个常用的功能。  

XP和2003的端口隐藏在TDI过滤驱动中即可实现。  
这里主要实现Vista及以后的端口隐藏。  
思路和TDI过滤一样，即附加"\\Device\\Nsi".  

分析思路：  
从GetTcpTable2/GetTcp6Table2等类似的API一步一步，跨越几个应用层的DLL，到内核还要分析几个驱动。  

有时，仅仅IDA静态逆向和windbg动态调试还不过瘾，那都来编码拦截观察吧！  

此工程的优点：  
1. 不会触发Windows的PG/KPP.  
2. 不影响正常的网络通讯。  
3. 大部分情况下都可以卸载。  

定制：针对进程的网络信息的隐藏。  

2022/10/10
