#Small OS

<h3>项目目的</h3>
项目的目的学习操作系统原理

<h3>目录结构</h3>

<pre><code>
.
├── Makefile 
├── boot
│   └── boot.s
├── floppy.img //安装好grub的软盘镜像
├── include
│   └── types.h
├── init
│   └── entry.c
├── mount //这是文件挂载点
└── scripts
    ├── bochsrc.txt //bochs的配置文件
    └── kernel.ld
</pre></code>

