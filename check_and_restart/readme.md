### 实现开机自启动，并且实时监测进程，进程退出则拉起
#### 注意要保证脚本都具有可执行权限

1. 首先准备main.cpp和可执行程序mytest
2. 编写监控脚本check_ailab.sh，监测程序如果挂掉则自动拉起
3. 创建一个 systemd 启动服务 auto_run_script.service，并把它放置在 /etc/systemd/system/ 目录下
4. 然后执行下面操作
```bash
systemctl daemon-reload
systemctl enable auto_run_script.service
```
5. 最后重启系统，执行```reboot```即可